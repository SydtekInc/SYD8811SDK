#include "ARMCM0.h"
#include "timer.h"
#include "softtimer.h"
#include "gpio.h"
#include "debug.h"
#include "delay.h"
#include "ota.h"
#include "config.h"
#include "lib.h"
#include "led_key.h"
#include "DebugLog.h"
#include <string.h>
#include "SYD_ble_service_Profile.h"
#include "ancs.h"



#define BondManagerIndex 0x00
static struct gap_att_report_handle *g_report;

extern uint32_t TIMER_EVT;
//device type
uint8_t per_device_system=0;    //1:IOS  0:not judge  2:android

//notify 标志 1代表已经使能 0代表未使能
static uint8_t start_tx=0;
uint8_t battery_tx=0;
uint8_t hid_key_tx=0;


//key status 0空闲 1按下 
uint8_t KEY1_Status = 0; 
uint8_t KEY2_Status = 0; 
uint8_t CAP_Status = 0; 

////key
uint32_t key_loop=0;
//connection
uint8_t  connect_flag=0;
uint8_t update_latency_mode=0;
uint8_t latency_state=0;


//ancs variable
//ancs uid
uint8_t phone_flag = 0;
uint8_t phone_uid[4] = {0};


//adc battery
uint8_t battery_value =0;   //剩余电量百分比


uint32_t delay_tick = 0;

/*
该变量为枚举SYD_NOSLEEP_CONTROL成员
SYD_NOSLEEP_ADC:ADC模块要求当前循环不进入睡眠
bit1:整60s事件(闹钟等)
bit2:校准时刻事件(整185s)
SYD_NOSLEEP_SW:不进入睡眠控制开关  1：当前循环不进入睡眠   0：当前循环进入睡眠
*/
uint8_t syd_nosleep_control=0; 


uint8_t BLE_SendData(uint8_t *buf, uint8_t len);

uint8_t ADV_DATA[] = {
		0x03,//0 length
		0x19,//1 
		0x00,//2
		0x00,//3
		0x02,//4 length
		0x01,//5 AD Type: Flags
		0x05,//6 LE Limited Discoverable Mode & BR/EDR Not Supported
		0x03,// length
		0x03,// AD Type: Complete list of 16-bit UUIDs 
		0x12,// UUID: 0x1812
		0x18,// UUID: 0x1812
		0X09,//11 length
		0XFF,//12 AD Type: MANUFACTURER SPECIFIC DATA
		0X00,//13 Company Identifier (0x00)
		0X00,//14 Company Identifier (0x00)
		0X00,//15
		0X00,//16
		0X00,//17
		0X00,//18
		0X00,//19
		0X00,//20
		Device_Name_Len+1,//21 length
		0x09,//22 AD Type: Complete local name
		Device_Name
};

uint16_t ADV_DATA_SZ = sizeof(ADV_DATA); 
uint8_t SCAN_DATA[]={
0x00

};
uint16_t SCAN_DATA_SZ = 0; 

static void ble_init(void);

static void gpio_callback(void);

void message_notification(void);

static void setup_adv_data()
{
	struct gap_adv_params adv_params;	
	static struct gap_ble_addr dev_addr;
	
	adv_params.type = ADV_IND;
	adv_params.channel = 0x07;    // advertising channel : 37 & 38 & 39
	adv_params.interval = 0x320;  // advertising interval : unit 0.625ms)
	adv_params.timeout = 0x3FFF;    // timeout : uint seconds
	adv_params.policy = 0x00;   

	SetAdvParams(&adv_params);

	/*get bluetooth address */
	GetDevAddr(&dev_addr);
	ADV_DATA[15] = dev_addr.addr[0];
	ADV_DATA[16] = dev_addr.addr[1];
	ADV_DATA[17] = dev_addr.addr[2];
	ADV_DATA[18] = dev_addr.addr[3];
	ADV_DATA[19] = dev_addr.addr[4];
	ADV_DATA[20] = dev_addr.addr[5];

	#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
	DBGHEXDUMP("device addr:",dev_addr.addr,BD_ADDR_SZ);
	#endif
	
	SetAdvData(ADV_DATA, ADV_DATA_SZ, SCAN_DATA, SCAN_DATA_SZ); 
}

/*
uint8_t target
0:ota
1:low energy
*/
void BLSetConnectionUpdate(uint8_t target){
	struct gap_smart_update_params smart_params;
	
	switch(target){
		case 0:   //0:ota
			/* connection parameters */
			smart_params.updateitv_target=0x0010;  //target connection interval (60 * 1.25ms = 75 ms)
			smart_params.updatesvto=0x00c8;  //supervisory timeout (400 * 10 ms = 4s)
			smart_params.updatelatency=0x0000;
			break;
		case 1:   //1:low energy
			/* connection parameters */
			smart_params.updateitv_target=0x0050;  //target connection interval (60 * 1.25ms = 75 ms)
			smart_params.updatesvto=0x0258;  //supervisory timeout (400 * 10 ms = 4s)
			smart_params.updatelatency=0x000A;
			break;
	}	
	smart_params.updatectrl=SMART_CONTROL_LATENCY | SMART_CONTROL_UPDATE;
	smart_params.updateadj_num=MAX_UPDATE_ADJ_NUM;
	gap_s_smart_update_latency(&smart_params);
   #if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
	dbg_printf("smart_params interval:%x latency:%x svto:%x\r\n",smart_params.updateitv_target,smart_params.updatelatency,smart_params.updatesvto);
	#endif
}

//void Connection_latency(void){
//		update_latency_mode++;
//		if(ENC_flag&0x80){
//	    if((update_latency_mode>=30) || (ENC_flag&0x40)){
//				ENC_flag =0;
//				update_latency_mode=1;
//			}
//		}else{
//			if(update_latency_mode>=2){
//				if(!latency_state){
//					if(per_device_system==1) {
//						BLSetConnectionUpdate(1);  //IOS
//						update_latency_mode=0;
//						Timer_Evt_Stop(EVT_2S);
//						latency_state=1;
//					}
//					else if(per_device_system==2){
//						BLSetConnectionUpdate(2);   //ANDROID
//						update_latency_mode=0;
//						latency_state=1;
//						Timer_Evt_Stop(EVT_2S);
//					}
//					else{     //not judge
//						#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
//						dbg_printf("ancs_service_enable\r\n");
//						#endif
//						if(connect_flag==1) ancs_service_enable();
//						else Timer_Evt_Stop(EVT_2S);
//						update_latency_mode=0;
//					}
//				}
//			}
//		}
//} 


static void ble_gatt_read(struct gap_att_read_evt evt)
{
	if(evt.uuid == BLE_DEVICE_NAME_UUID)
	{
		uint8_t gatt_buf[]={Device_Name};
		uint8_t gatt_buf_sz = sizeof(gatt_buf); 

		SetGATTReadRsp(gatt_buf_sz, gatt_buf);
	}
	else if(evt.uuid == BLE_APPEARANCE_UUID)
	{
		uint8_t gatt_buf[]={0xff, 0xff};
		uint8_t gatt_buf_sz = sizeof(gatt_buf); 

		SetGATTReadRsp(gatt_buf_sz, gatt_buf);
	}
	else if(evt.uuid == BLE_MANUFACTURER_NAME_STRING_UUID)
	{
		uint8_t gatt_buf[]={'S','Y','D',' ','I', 'n', 'c', '.'};
		uint8_t gatt_buf_sz = sizeof(gatt_buf); 

		SetGATTReadRsp(gatt_buf_sz, gatt_buf);
	}
	else if(evt.uuid == BLE_MODEL_NUMBER_STRING_UUID)
	{
		uint8_t gatt_buf[]={'B', 'L', 'E', ' ', '1', '.', '0'};
		uint8_t gatt_buf_sz = sizeof(gatt_buf); 

		SetGATTReadRsp(gatt_buf_sz, gatt_buf);
	}
	else if(evt.uuid == BLE_SERIAL_NUMBER_STRING_UUID)
	{
		uint8_t gatt_buf[]={'1','.','0','.','0'};
		uint8_t gatt_buf_sz = sizeof(gatt_buf); 

		SetGATTReadRsp(gatt_buf_sz, gatt_buf);
	}
	else if(evt.uuid == BLE_HARDWARE_REVISION_STRING_UUID)
	{
		uint8_t gatt_buf[]={'2','.','0','0'};
		uint8_t gatt_buf_sz = sizeof(gatt_buf); 

		SetGATTReadRsp(gatt_buf_sz, gatt_buf);
	}
	else if(evt.uuid == BLE_FIRMWARE_REVISION_STRING_UUID)
	{
		uint8_t gatt_buf[]={'3','.','0','0'};
		uint8_t gatt_buf_sz = sizeof(gatt_buf); 

		SetGATTReadRsp(gatt_buf_sz, gatt_buf);
	}
	else if(evt.uuid == BLE_SOFTWARE_REVISION_STRING_UUID)
	{
		uint8_t gatt_buf[]={SOFTWARE_REVISION_STR};
		uint8_t gatt_buf_sz = sizeof(gatt_buf); 

		SetGATTReadRsp(gatt_buf_sz, gatt_buf);
	}
	else if(evt.uuid == BLE_PNP_ID_UUID)
	{
		uint8_t gatt_buf[]={ 0x02, 						//		Vendor ID Source
						    0x3a,0x09,					//		USB Vendor ID
						    0x05,0x0a,					//		Product ID
						    0x02,0x00					//		Product Version
												 };
		uint8_t gatt_buf_sz = sizeof(gatt_buf); 

		SetGATTReadRsp(gatt_buf_sz, gatt_buf);
	}
	else if(evt.uuid == BLE_WECHAT_Read_UUID)
	{
		uint8_t buf[]={0x00,0x01,0x03,0x04};
		
		BLE_SendData(buf, 4);
	}
	#ifdef _OTA_
    else if(evt.uuid == BLE_OTA_Read_Write_UUID)
    {
        uint8_t sz=0;

        uint8_t rsp[sizeof(struct hci_evt)]= {0};

        ota_rsp(rsp, &sz);

        SetGATTReadRsp(sz, rsp);
    }
#endif
	else if(evt.uuid == BLE_BATTERY_SERVICE)
	{
		SetGATTReadRsp(0x01, &battery_value);
	}
}


//接收函数
static void ble_gatt_write(struct gap_att_write_evt evt)
{
	// rx data
	//evt.data是收取到的数据buf
	if(evt.uuid== BLE_UART_Write_UUID)
	{
		// rx data
		if((*(evt.data)==0xa1) && (*(evt.data+1)==0x01) && (*(evt.data+2)==0x01) && (*(evt.data+3)==0x01))
		{
				SecurityReq(1, 0);
				update_latency_mode=1;
		}
	
			
		#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_) 
		DBGHEXDUMP("msg:\r\n",evt.data,evt.sz);
		#endif
	}
	#ifdef _OTA_
	else if(evt.uuid== BLE_OTA_Read_Write_UUID)
	{
			update_latency_mode=0;
			ota_cmd(evt.data, evt.sz);
	}
	#endif
    
}

//发送函数
uint8_t BLE_SendData(uint8_t *buf, uint8_t len)
{
	if(start_tx == 1)
	{
		struct gap_att_report report;
		report.primary = BLE_UART;
		report.uuid = BLE_UART_NOTIFY_UUID;
		report.hdl = BLE_UART_NOTIFY_VALUE_HANDLE;					
		report.value = BLE_GATT_NOTIFICATION;
		return GATTDataSend(BLE_GATT_NOTIFICATION, &report, len, buf);
	}
	return 0;
}



//HID发送函数
//键值发送函数
uint8_t HID_Key_Vlaue_Send(uint16_t key_value)
{
        
	struct gap_att_report report;
	uint8_t buf[2] = {0};
    
	buf[0] = key_value&0xff;
	buf[1] = (key_value>>8)&0xff;
    
	if(hid_key_tx == 1)
	{
		report.primary = BLE_HIDO_SERVICE;
		report.uuid = BLE_Consumer_REPORT_UUID;
		report.config = BLE_Consumer_REPORT_VALUE_HANDLE +1;
		report.hdl = BLE_Consumer_REPORT_VALUE_HANDLE;					
		report.value = BLE_GATT_NOTIFICATION;
    return GATTDataSend(BLE_GATT_NOTIFICATION, &report, 2, buf);
	}
	return 0;
}




void ble_evt_callback(struct gap_ble_evt *p_evt)
{
	if(p_evt->evt_code == GAP_EVT_ADV_END)
	{		
		
		setup_adv_data();
		StartAdv();
		#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
		DBGPRINTF(("ReStartAdv\r\n"));
		#endif
	}
	else if(p_evt->evt_code == GAP_EVT_CONNECTED)	 //连接事件
	{
		start_tx = 0;
		hid_key_tx = 0;
    connect_flag=1;								 //连接状态
   
		per_device_system=0;
		ota_variable_clear(true);
		//Timer_Evt_Start(EVT_2S);
		#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_) 
		DBGHEXDUMP("GAP_EVT_CONNECTED addr:",p_evt->evt.bond_dev_evt.addr,sizeof(p_evt->evt.bond_dev_evt.addr));
		#endif
	}
	else if(p_evt->evt_code == GAP_EVT_DISCONNECTED) //断连事件
	{	
		connect_flag=0;								 //连接状态
		start_tx = 0;
		hid_key_tx = 0; 
		//Timer_Evt_Stop(EVT_2S);
		StartAdv();
		
		Timer_Evt_Stop(EVT_1S_OTA);
		#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_) 
		DBGPRINTF("GAP_EVT_DISCONNECTED %x\r\n", p_evt->evt.disconn_evt.reason);
		#endif
	}
	else if(p_evt->evt_code == GAP_EVT_ATT_HANDLE_CONFIGURE)
	{					
		if(p_evt->evt.att_handle_config_evt.uuid == BLE_UART)
		{
				if(p_evt->evt.att_handle_config_evt.hdl == (BLE_UART_NOTIFY_VALUE_HANDLE + 1))
				{
						if((p_evt->evt.att_handle_config_evt.value & BLE_GATT_NOTIFICATION)||(p_evt->evt.att_handle_config_evt.value & BLE_GATT_INDICATION))
						{
								#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_) 
								DBGPRINTF(("start_tx enable\r\n"));
								#endif
								start_tx = 1;
						}
						else
						{			
								start_tx = 0;
						}
				}
		}	
    else if(p_evt->evt.att_handle_config_evt.uuid == BLE_HIDO_SERVICE)
		{
				if(p_evt->evt.att_handle_config_evt.hdl == (BLE_Consumer_REPORT_VALUE_HANDLE + 1))
				{
            if(p_evt->evt.att_handle_config_evt.value& BLE_GATT_NOTIFICATION)
						{
								#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_) 
								DBGPRINTF(("hid_key_tx enable\r\n"));
								#endif
								hid_key_tx = ENABLE;
						}
						else
						{			
								hid_key_tx = DISABLE;
								#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_) 
								DBGPRINTF(("hid_key_tx disable\r\n"));
								#endif
						}
        }
		}        
		else if(p_evt->evt.att_handle_config_evt.uuid == BLE_BATTERY_SERVICE)
		{
			if(p_evt->evt.att_handle_config_evt.value & BLE_GATT_NOTIFICATION)
			{
				struct gap_att_report report;

				report.primary = BLE_BATTERY_SERVICE;
				report.uuid = BLE_BATTERY_SERVICE;
				report.hdl = BLE_Battry_Level_VALUE_HANDLE;
				report.value = BLE_GATT_NOTIFICATION;
				GATTDataSend(BLE_GATT_NOTIFICATION, &report, 0x01, &battery_value);
			}
			else
			{
			
			}
		}
		//DBGPRINTF(("GAP_EVT_ATT_HANDLE_CONFIGURE uuid:(%02x)\r\n",p_evt->evt.att_handle_config_evt.uuid));
	}
	else if(p_evt->evt_code == GAP_EVT_ATT_WRITE)
	{
		ble_gatt_write(p_evt->evt.att_write_evt);
		//DBGPRINTF(("GAP_EVT_ATT_WRITE uuid:(%02x)\r\n",p_evt->evt.att_write_evt.uuid));
	}
	else if(p_evt->evt_code == GAP_EVT_ATT_READ)
	{
		ble_gatt_read(p_evt->evt.att_read_evt);
    //DBGPRINTF(("GAP_EVT_ATT_READ uuid:(%02x)\r\n",p_evt->evt.att_write_evt.uuid));
	}
	else if(p_evt->evt_code == GAP_EVT_ATT_HANDLE_CONFIRMATION)
	{
		//DBGPRINTF(("GAP_EVT_ATT_HANDLE_CONFIRMATION uuid:(%02x)\r\n",p_evt->evt.att_handle_config_evt.uuid));
	}
	else if(p_evt->evt_code == GAP_EVT_PAIRING_COMP)
	{
		#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_) 
			DBGPRINTF(("GAP_EVT_PAIRING_COMP\r\n"));
		#endif
	}
	else if(p_evt->evt_code == GAP_EVT_ENC_START)
	{
		ancs_service_enable();
		#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_) 
			DBGPRINTF(("GAP_EVT_ENC_START\r\n"));
		#endif
		
	}
  else if(p_evt->evt_code == GAP_EVT_L2CAP_UPDATE_RSP)
	{
		
		switch(p_evt->evt.l2cap_update_rsp_evt.result)
		{
			case CONN_PARAMS_ACCEPTED:
				#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_) 
				DBGPRINTF(("update rsp ACCEPTED\r\n"));
				{
					struct gap_link_params  link_app;
					GetLinkParameters(&link_app);
					#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
					dbg_printf("interval:%x latency:%x\r\n",link_app.interval,link_app.latency);
					#endif
				}
				#endif
				break;
			case CONN_PARAMS_REJECTED:
				#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
				DBGPRINTF(("update rsp REJECTED\r\n"));
				#endif
				break;
			case CONN_PARAM_SMART_TIMEROUT:
				#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
				DBGPRINTF(("update rsp TIMEROUT\r\n"));
				#endif
				break;
			case CONN_PARAM_SMART_SUCCEED:
				#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
				DBGPRINTF(("update rsp SUCCEED\r\n"));
				#endif
				break;
			case CONN_PARAM_LATENCY_ENABLE:
				#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
				DBGPRINTF(("Enable latency\r\n"));
				#endif
				break;
			case CONN_PARAM_LATENCY_DISABLE:
				#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
				DBGPRINTF(("Disable latency\r\n"));
				#endif
				break;
		}
	}
}

void ble_attc_callback(struct attc_ble_evt *p_attc)
{
	ancs_service_att_data(p_attc);
}

static void ble_init()
{	
	struct gap_evt_callback evt;	
	struct gap_wakeup_config pw_cfg;
	struct smp_pairing_req sec_params;

	BleInit();
	
	/* security parameters */
	sec_params.io = IO_NO_INPUT_OUTPUT;
	sec_params.oob = OOB_AUTH_NOT_PRESENT;
	sec_params.flags = AUTHREQ_BONDING;
	sec_params.mitm = 0;
	sec_params.max_enc_sz = 16;
	sec_params.init_key = 0;
	sec_params.rsp_key = (SMP_KEY_MASTER_IDEN |SMP_KEY_ADDR_INFO);
	SetSecParams(&sec_params);

	evt.evt_mask=(GAP_EVT_CONNECTION_SLEEP|GAP_EVT_CONNECTION_INTERVAL);
	evt.p_callback=&ble_evt_callback;
	SetEvtCallback(&evt);
	
	ATTCSetCallback(&ble_attc_callback);

	GetGATTReportHandle(&g_report);

	/* Bond Manager (MAX:10) */
	SetBondManagerIndex(BondManagerIndex);
	
	setup_adv_data();

	//set MCU wakup source
	pw_cfg.wakeup_type = SLEEP_WAKEUP;
	pw_cfg.timer_wakeup_en = true;
	pw_cfg.gpi_wakeup_en = true;
	pw_cfg.wdt_wakeup_en = false;
	pw_cfg.rtc_wakeup_en = true;

	pw_cfg.gpi_wakeup_cfg =  U32BIT(KEY1) | U32BIT(KEY2); 

	WakeupConfig(&pw_cfg);
}



void  ota_manage(void){
	#ifdef _OTA_
	if(ota_state){
		switch(ota_state){
			case 1 : 
				CmdFwErase();
				#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
				dbg_printf("OTA start\r\n");
				#endif
				ota_state =2;
				ota_writecnt=0;
				break;
			case 2 : 
				ota_writecnt++;
				if(ota_writecnt>0x20)
				{
					#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
						dbg_printf("OTA faile\r\n");
					#endif
					Timer_Evt_Stop(EVT_1S_OTA);
				}
				break;
				
			case 3 : 
				ota_state=0;
				Timer_Evt_Stop(EVT_1S_OTA);
				#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
					dbg_printf("OTA finish\r\n");
				#endif
				delay_ms(1000);
			#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
				dbg_printf("Start Reset 1000s\r\n");
			#endif
				SystemReset();
			#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
				dbg_printf("Reset failed\r\n");
			#endif
				break;
			default :
				break;
		}
	}
	#endif
}

/*
ancs_result  调用ancs_service_enable后协议栈回馈ancs初始化结果
result: 0: 非法回应
        1: ancs end 对方设备是IOS 并且已经绑定了
        2: not ancs 对方设备不是IOS
        3: not band 对方设备是IOS 但是没有绑定
        4: not encryption 对方设备是IOS 但是没有加密
*/
void ancs_result(uint8_t result)
{
	switch(result)
	{
		case 1:
			per_device_system=1;
			#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
			DBGPRINTF(("ancs end\r\n"));
			#endif
			break;
		case 2:
			per_device_system=2;
			#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
			dbg_printf("not ancs\r\n");  
			#endif
			break;
		case 3:
			per_device_system=1;
			#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
			dbg_printf("not band\r\n");
			#endif
			break;
		case 4:
			per_device_system=1;
			#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
			dbg_printf("not encryption\r\n");   //这里可以重新加密
			#endif
			break;
		default : 
			break;
	}
}

void gpio_init(void)
{
    uint8_t i;
    uint32_t io_input=0,io_output=0,io_outlow=0,io_pull=0, io_invert=0;

    PIN_CONFIG->PAD_INPUT_PULL_UP[0] = 0xff; //pull up
    PIN_CONFIG->PAD_INPUT_PULL_UP[1] = 0xff; //pull up
    PIN_CONFIG->PAD_INPUT_PULL_UP[2] = 0xff; //pull up   pin22/pin21 UART
    PIN_CONFIG->PAD_INPUT_PULL_UP[3] = 0xcf; //pull up   pin29/pin28 SWD
    PIN_CONFIG->PAD_INPUT_PULL_UP[4] = 0xff; //pull up

    for(i=0; i < 32; i++)
    {
        switch(i)
        {
        //输入上拉取反,不取反
        //key 1,2,3,4
        case KEY1:
        case KEY2:
        case KEY3:
        case KEY4:
            io_input |=U32BIT(i);
            io_pull |=U32BIT(i);
            io_invert |=U32BIT(i);
        break;
         //UART
        case GPIO_6:
        case GPIO_8:
            break;
		#ifndef USER_32K_CLOCK_RCOSC 
		case GPIO_0:
		case GPIO_1:
		break;
		#endif
        
        //LED 2,3,4
        case LED1:
        case LED2:
        case LED3:
        case LED4:
            io_output |=U32BIT(i);   //默认输出高电平
        break;

        default:   //默认上拉输入
            io_input |=U32BIT(i);
            io_pull |=U32BIT(i);
            break;

        }
	}

	
	PIN_Set_GPIO(io_input|io_output,PIN_SEL_GPIO);

	//DEFAULT OUT
	GPIO_Set_Output(io_output);
	//DEFAULT OUT HIGHT PIN
	GPIO_Pin_Set(io_output & (~io_outlow));
	//DEFAULT LOW LOW PIN
	GPIO_Pin_Clear(io_outlow);
	
	
	//INPORT PIN
	//INPORT PIN
	GPIO_Set_Input(io_input,io_invert);
	PIN_Pullup_Enable(T_QFN_48, io_pull);
	GPIO_Input_Enable(io_input);
		//GPIO唤醒MCU初始化
	io_irq_enable(U32BIT(KEY1) | U32BIT(KEY2), &gpio_callback);
}


int main()
{	
	__disable_irq();

	ble_init();
	
	MCUClockSwitch(SYSTEM_CLOCK_64M_RCOSC);
	RCOSCCalibration();
	#ifdef USER_32K_CLOCK_RCOSC
	ClockSwitch(SYSTEM_32K_CLOCK_RCOSC);
	delay_ms(500);
	LPOCalibration();						//这是内部RC32k晶振的校准函数	经过该函数后定时器能够得到一个比较准确的值
	#else
	ClockSwitch(SYSTEM_32K_CLOCK_XOSC);
	#endif

	gpio_init();								 //gpio初始化
	
	#ifdef _SYD_RTT_DEBUG_
		DebugLogInit();
		dbg_printf("SYD RTT Init\r\n");
		UartEn(true);
	#endif
	
	#ifdef _DEBUG_
		dbg_init();
		UartEn(true);
	#endif
	
	#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
	dbg_printf("Syd8811_HID %s:%s\r\n",__DATE__ ,__TIME__);
	#endif
		
	SYD_Timer_Init(EVT_NUM, syd_sysTimer);	
	Timer_Evt_List();

	SYD_RTC_Init(RTCEVT_NUM, syd_rtc);	
	RTC_Evt_List();

	#ifdef _WDT_
	wdt_enable(128*15);    //256/32.768 = 7.8ms
	#endif

	
	__enable_irq();	
	
	//RFSleep();
	StartAdv();
	#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
	DBGPRINTF(("StartAdv\r\n"));
	#endif
	
    
	while(1)
	{				
		ble_sched_execute();
		
		//拒接电话
		if(GPIO_Pin_Read(U32BIT(KEY1)))
		{
			delay_ms(5);
			if(GPIO_Pin_Read(U32BIT(KEY1)))
			{
				
				#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
					dbg_printf("KEY1 Press\r\n");
				#endif
				
				if((connect_flag==1) && (phone_flag == 1))
				{
					phone_flag = 0;
					
					#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
					dbg_printf("reject the phone\r\n");
					#endif
					
					ancs_perform_notification_action(phone_uid, ACTION_ID_NEGATIVE);
				}
				while(GPIO_Pin_Read(U32BIT(KEY1)));
			}	
		}
		
		//接电话
    if(GPIO_Pin_Read(U32BIT(KEY2)))
		{
			delay_ms(5);
			if(GPIO_Pin_Read(U32BIT(KEY2)))
			{
				
				#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
					dbg_printf("KEY2 Press\r\n");
				#endif
				
				if((connect_flag==1) && (phone_flag == 1))
				{
					phone_flag = 0;

					#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
					dbg_printf("answer the phone\r\n");
					#endif

					ancs_perform_notification_action(phone_uid, ACTION_ID_POSITIVE);
				}
				while(GPIO_Pin_Read(U32BIT(KEY2)));
			} 
		}

		
		//ancs handle
		message_notification();

		if(TIMER_EVT) 
		{
			#ifdef	EVT_1S_OTA
			if(TIMER_EVT&EVT_1S_OTA)   
			{
				ota_manage();     //ota 过程管理 操作屏幕等
				Timer_Evt_Clr(EVT_1S_OTA);
				#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
				DBGPRINTF(("EVT_1S_OTA\r\n"));
				#endif
			}
			#endif
			
			#ifdef	EVT_2S
			if(TIMER_EVT&EVT_2S)   
			{
//				Connection_latency();   //连接参数相关设置
				Timer_Evt_Clr(EVT_2S);
				#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
				DBGPRINTF(("EVT_2S\r\n"));
				#endif
			}
			#endif
		}
		
		if(RTC_EVT) 
		{
			
			
			#ifdef	RTCEVT_185S
			if(RTC_EVT&RTCEVT_185S)
			{
				#ifdef USER_32K_CLOCK_RCOSC
					 //if(connect_flag && (latency_state==1)) gap_s_connection_latency_mode(0x00);
					 LPOCalibration();						//这是内部RC32k晶振的校准函数	经过该函数后定时器能够得到一个比较准确的值
					 //if(connect_flag && (latency_state==1)) gap_s_connection_latency_mode(0x01);
				#endif
                #if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
					 DBGPRINTF(("RTCEVT_185S\r\n"));
				#endif
				RTC_EVT_Clr(RTCEVT_185S);
			}
			#endif
		}
		
		if( ota_state == 1)  ota_manage();     //OTA擦除命令到来，马上擦除
		//SystemSleep();	
	}	
}


static void gpio_callback(void)
{
	if(start_tx & 0x01)		//connected
	{
		UartEn(true);	//不允许RF sleep时关闭XO
	}
}


void message_notification(void)
{
	if(ancs_msg.valid == 1)
	{
		char * name_offect=(char *)ancs_msg.msg;
		
		#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
			dbg_printf("appid_len:%d\r\n",ancs_msg.appid_len);
			dbg_printf("appid:%s\r\n",ancs_msg.appid);
			
			dbg_printf("title_len:%d\r\n",ancs_msg.title_len);
			dbg_printf("title:%s\r\n",ancs_msg.title);

			dbg_printf("msg len:%d  ",ancs_msg.msg_len);
			dbg_hexdump("msg: \r\n", ancs_msg.msg,ancs_msg.msg_len);
			dbg_hexdump("ancs_uid: \r\n", ancs_msg.ancs_uid,4);
		#endif
		
		//消息处理
		if (strstr((const char *)ancs_msg.appid,"mobilephone") != NULL)
		{
			phone_flag = 1;
			memcpy(phone_uid, ancs_msg.ancs_uid, 4);
		}		
		else if (strstr((const char *)ancs_msg.appid,"MobileSMS") != NULL) 
		{
			
		}
		else if (strstr((const char *)ancs_msg.appid,"Tweetie") != NULL) 
		{
			name_offect=strstr((const char *)ancs_msg.msg,":");
	
			if(name_offect!= NULL)
			{
				ancs_msg.title_len=((name_offect-(char *)ancs_msg.msg)<ANCS_TITLE_LEN)?(name_offect-(char *)ancs_msg.msg):ANCS_TITLE_LEN;
				memcpy(ancs_msg.title,ancs_msg.msg,ancs_msg.title_len);			
				ancs_msg.msg_len -=name_offect-(char *)ancs_msg.msg+1;
				name_offect +=1;
			}
			else
			{
				name_offect=(char *)ancs_msg.msg;
			}	
		}
		else if (strstr((const char *)ancs_msg.appid,"skype") != NULL) 
		{
			
			if(ancs_msg.valid == 1) 
			{ 
				name_offect=strstr((const char *)ancs_msg.msg,":");
			
			}
			else
			{
				uint8_t temp[2]={0x0a,'\0'};
				name_offect=strstr((const char *)ancs_msg.msg,(const char *)temp);
			}
			
			if(name_offect!= NULL)
			{
				ancs_msg.title_len=((name_offect-(char *)ancs_msg.msg)<ANCS_TITLE_LEN)?(name_offect-(char *)ancs_msg.msg):ANCS_TITLE_LEN;
				memcpy(ancs_msg.title,ancs_msg.msg,ancs_msg.title_len);			
				ancs_msg.msg_len -=name_offect-(char *)ancs_msg.msg+1;
				name_offect +=1;
			}else
			{
			name_offect=(char *)ancs_msg.msg;
			
			}
		}
		else if (strstr((const char *)ancs_msg.appid,"Line") != NULL) 
		{
			name_offect=strstr((const char *)ancs_msg.msg,":");
			if(name_offect!= NULL)
			{
				ancs_msg.title_len=((name_offect-(char *)ancs_msg.msg)<ANCS_TITLE_LEN)?(name_offect-(char *)ancs_msg.msg):ANCS_TITLE_LEN;
				memcpy(ancs_msg.title,ancs_msg.msg,ancs_msg.title_len);			
				ancs_msg.msg_len -=name_offect-(char *)ancs_msg.msg+1;
				name_offect +=1;
			}
			else
			{					
				name_offect=(char *)ancs_msg.msg;
			}	
		}
		else if (strstr((const char *)ancs_msg.appid,"WhatsApp") != NULL) 
		{
			if(ancs_msg.valid == 1)
			{
				name_offect=strstr((const char *)ancs_msg.msg,":");
				if(name_offect== NULL)
				{
					uint8_t temp[4]={0xef,0xbc,0x9a,'\0'};
					name_offect=strstr((const char *)ancs_msg.msg,(const char *)temp);
				}
				else
				{ 
					name_offect=(char *)ancs_msg.msg;
				}
			}
			else
			{
				name_offect=strstr((const char *)ancs_msg.msg," ");
			}
			if(name_offect!= NULL)
			{
				ancs_msg.title_len=((name_offect-(char *)ancs_msg.msg)<ANCS_TITLE_LEN)?(name_offect-(char *)ancs_msg.msg):ANCS_TITLE_LEN;
				memcpy(ancs_msg.title,ancs_msg.msg,ancs_msg.title_len);			
				
				if(ancs_msg.valid == 2)
				{
					ancs_msg.msg_len -=name_offect-(char *)ancs_msg.msg+1;
					name_offect +=1;
//									dbg_hexdump("data1:\r\n", (uint8_t *)name_offect,ancs_msg.msg_len);
				}
				else
				{
					ancs_msg.title_len -=3;
					memcpy(ancs_msg.title,ancs_msg.msg+3,ancs_msg.title_len);
					ancs_msg.msg_len -=name_offect-(char *)ancs_msg.msg+3;
					name_offect +=3;
				}
//								dbg_printf("title_len:%x msg_len:%x\r\n",ancs_msg.title_len,ancs_msg.msg_len);
			}
			else
			{ 
				name_offect=(char *)ancs_msg.msg;
			}
					
		}
		else if (strstr((const char *)ancs_msg.appid,"facebook") != NULL) 
		{
		
					name_offect=strstr((const char *)ancs_msg.msg," ");
					if(name_offect!= NULL)
					{
						ancs_msg.title_len=((name_offect-(char *)ancs_msg.msg)<ANCS_TITLE_LEN)?(name_offect-(char *)ancs_msg.msg):ANCS_TITLE_LEN;
						memcpy(ancs_msg.title,ancs_msg.msg,ancs_msg.title_len);			
						ancs_msg.msg_len -=name_offect-(char *)ancs_msg.msg+1;
						name_offect +=1;
					}
					else 
					{
						name_offect=(char *)ancs_msg.msg;
					}
					
				
		}
		else if (strstr((const char *)ancs_msg.appid,"xin") != NULL) 
		{
			name_offect=strstr((const char *)ancs_msg.msg,":");
			if(name_offect!= NULL){
				ancs_msg.title_len=((name_offect-(char *)ancs_msg.msg)<ANCS_TITLE_LEN)?(name_offect-(char *)ancs_msg.msg):ANCS_TITLE_LEN;
				memcpy(ancs_msg.title,ancs_msg.msg,ancs_msg.title_len);			
				ancs_msg.msg_len -=name_offect-(char *)ancs_msg.msg+1;
				name_offect +=1;
			}
			else
			{	
				name_offect=(char *)ancs_msg.msg;
			}
			
		}
		else if (strstr((const char *)ancs_msg.appid,"mqq") != NULL) 
		{
			name_offect=strstr((const char *)ancs_msg.msg,":");
			if(name_offect!= NULL){
				ancs_msg.title_len=((name_offect-(char *)ancs_msg.msg)<ANCS_TITLE_LEN)?(name_offect-(char *)ancs_msg.msg):ANCS_TITLE_LEN;
				memcpy(ancs_msg.title,ancs_msg.msg,ancs_msg.title_len);			
				ancs_msg.msg_len -=name_offect-(char *)ancs_msg.msg+1;
				name_offect +=1;
			}
			else 
			{
				name_offect=(char *)ancs_msg.msg;
			}
		}
		else{//other Message
			ancs_msg.valid =0;
			clr_ancs_msg();
		}
		//转接完一定要清楚 ancs_msg_t buffer，不然不能接收新消息
		clr_ancs_msg();
	}
}


