#define  _HID_C

#include "config.h"
#include "timer.h"
#include "gpio.h"
#include "DebugLog.h"
#include "delay.h"
#include "uart.h"
#include "ota.h"
#include "SYD_ble_service_service.h"
#include <string.h>
#include "softtimer.h"
#include "led_key.h"
#include "debug.h"
#include "uart_ota.h"
#include "uart_ota_test.h"

#define SOFTWARE_REVISION_STR 'V','0','0','1'


//connection
uint8_t  connect_flag=0;
uint8_t latency_state = 0;
uint8_t update_latency_mode=0;

uint16_t uart_delay_cnt=0;

static struct gap_att_report_handle *g_report;   //GATT属性列表头,传入到协议栈中进行初始化
static uint8_t start_tx = 0;
uint8_t wechat_tx=0;
uint8_t battery_tx=0;

//adc battery
uint8_t battery_value =0;   //剩余电量百分比


void gpio_callback(void);



uint8_t BLE_SendData(uint8_t *buf, uint8_t len);

uint8_t ADV_DATA[] = {
		0x03,/*0 length*/
		0x19,/*1 */
		0x00,/*2 */
		0x00,/*3 */
		0x02,/*4 length */
		0x01,//5 AD Type: Flags
		0x05,//6 LE Limited Discoverable Mode & BR/EDR Not Supported
		0x03,// length
        0x03,// AD Type: Complete list of 16-bit UUIDs 
        0x01,// UUID: 0x0001
        0x00,// UUID: 0x0001
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

static void setup_adv_data()
{
	struct gap_adv_params adv_params;	
	static struct gap_ble_addr dev_addr;
	
	adv_params.type = ADV_IND;
	adv_params.channel = 0x07;    // advertising channel : 37 & 38 & 39
	adv_params.interval = 0x640;  // advertising interval : unit 0.625ms)
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

	#if defined(_DEBUG_)
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
			
		#if defined(_DEBUG_)
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

void ble_evt_callback(struct gap_ble_evt *p_evt)
{
	if(p_evt->evt_code == GAP_EVT_ADV_END)
	{		
		
		setup_adv_data();
		StartAdv();
		#if defined(_DEBUG_)
		DBGPRINTF(("ReStartAdv\r\n"));
		#endif
		
	}
	else if(p_evt->evt_code == GAP_EVT_CONNECTED)	 //连接事件
	{
		start_tx = 0;
        connect_flag=1;								 //连接状态
#ifdef _OTA_
		ota_variable_clear(true);
#endif
		//Timer_Evt_Start(EVT_2S);
		#if defined(_DEBUG_)
		DBGHEXDUMP("GAP_EVT_CONNECTED addr:",p_evt->evt.bond_dev_evt.addr,sizeof(p_evt->evt.bond_dev_evt.addr));
		#endif
	}
	else if(p_evt->evt_code == GAP_EVT_DISCONNECTED) //断连事件
	{	
		connect_flag=0;								 //连接状态
		start_tx = 0;
		//Timer_Evt_Stop(EVT_2S);
		StartAdv();
#ifdef _OTA_
        ota_variable_clear(true);
#endif
		#if defined(_DEBUG_)
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
                    #if defined(_DEBUG_)
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
		else if(p_evt->evt.att_handle_config_evt.uuid == BLE_WECHAT)
		{
			if((p_evt->evt.att_handle_config_evt.value & BLE_GATT_NOTIFICATION)||(p_evt->evt.att_handle_config_evt.value & BLE_GATT_INDICATION))
			{
				#if defined(_DEBUG_)
				DBGPRINTF(("wechat_tx enable\r\n"));
				#endif
				wechat_tx = 1;
			}
			else
			{			
				wechat_tx = 0;
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
		#if defined(_DEBUG_) 
			DBGPRINTF(("GAP_EVT_PAIRING_COMP\r\n"));
		#endif
	}
	else if(p_evt->evt_code == GAP_EVT_ENC_START)
	{
		#if defined(_DEBUG_)
			DBGPRINTF(("GAP_EVT_ENC_START\r\n"));
		#endif
	}
  else if(p_evt->evt_code == GAP_EVT_L2CAP_UPDATE_RSP)
	{
		
		switch(p_evt->evt.l2cap_update_rsp_evt.result)
		{
			case CONN_PARAMS_ACCEPTED:
				#if defined(_DEBUG_)
				DBGPRINTF(("update rsp ACCEPTED\r\n"));
				{
					struct gap_link_params  link_app;
					GetLinkParameters(&link_app);
					#if defined(_DEBUG_) 
					dbg_printf("interval:%x latency:%x\r\n",link_app.interval,link_app.latency);
					#endif
				}
				#endif
				break;
			case CONN_PARAMS_REJECTED:
				#if defined(_DEBUG_) 
				DBGPRINTF(("update rsp REJECTED\r\n"));
				#endif
				break;
			case CONN_PARAM_SMART_TIMEROUT:
				#if defined(_DEBUG_) 
				DBGPRINTF(("update rsp TIMEROUT\r\n"));
				#endif
				break;
			case CONN_PARAM_SMART_SUCCEED:
				#if defined(_DEBUG_) 
				DBGPRINTF(("update rsp SUCCEED\r\n"));
				#endif
				break;
			case CONN_PARAM_LATENCY_ENABLE:
				#if defined(_DEBUG_)  
				DBGPRINTF(("Enable latency\r\n"));
				#endif
				break;
			case CONN_PARAM_LATENCY_DISABLE:
				#if defined(_DEBUG_)  
				DBGPRINTF(("Disable latency\r\n"));
				#endif
				break;
		}
	}
}



void gpio_init(void)
{
	uint8_t i;
	uint32_t io_input=0,io_output=0,io_outlow=0,io_pull=0, io_invert=0;
	
    #ifdef USER_32K_CLOCK_RCOSC 
	PIN_CONFIG->PAD_INPUT_PULL_UP[0] = 0xff; //pull up 
	#else
    PIN_CONFIG->PAD_INPUT_PULL_UP[0] = 0xfc; //pull up  gpio 0 1 32K xosc
    #endif
    
  PIN_CONFIG->PAD_INPUT_PULL_UP[1] = 0xff; //pull up 
	PIN_CONFIG->PAD_INPUT_PULL_UP[2] = 0x9f; //pull up   pin22/pin21 UART
	PIN_CONFIG->PAD_INPUT_PULL_UP[3] = 0xcf; //pull up   pin29/pin28 SWD
	PIN_CONFIG->PAD_INPUT_PULL_UP[4] = 0xff; //pull up 
    

    for(i=0;i < 32;i++)
    {
			switch(i)
			{
				case GPIO_UART1_TX:
				case GPIO_UART1_RX:
				case GPIO_UART0_TX:
				case GPIO_UART0_RX:
				break;
				
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
		#ifndef USER_32K_CLOCK_RCOSC 
			case GPIO_0:
			case GPIO_1:
			break;
			#endif

				default:   //默认上拉输入
				io_input |=U32BIT(i);
				io_pull |=U32BIT(i);
				break;
			}
    }
  
//	BBRFWrite(0x7f, 0x00);    //设置GPIO21为IO口模式，而不是复位管脚
//	BBRFWrite(0x1a, 0x40);
  
	//DEFAULT OUT
	GPIO_Set_Output(io_output); 
	PIN_Pullup_Disable(T_QFN_48, io_output);
	//DEFAULT OUT HIGHT PIN
	GPIO_Pin_Set(io_output & (~io_outlow));
	//DEFAULT LOW LOW PIN
	GPIO_Pin_Clear(io_outlow);
	//INPORT PIN
	GPIO_Set_Input(io_input,io_invert);
	PIN_Pullup_Enable(T_QFN_48, io_pull);
}


static void ble_init()
{	
	struct gap_evt_callback evt;		
	struct smp_pairing_req sec_params;	
	struct gap_wakeup_config pw_cfg;

	BleInit();	
	SetWinWideMinusCnt(1);

	GetGATTReportHandle(&g_report);

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

	/* Bond Manager (MAX:10) */
	SetBondManagerIndex(0x00);

	setup_adv_data();
	/*
	当POWERDOWN_WAKEUP时，
	PW_CTRL->DSLP_LPO_EN = true，这些中断源才能唤醒并复位运行，
	如果是false就只有pin能唤醒并复位运行
	*/
	pw_cfg.wakeup_type = SLEEP_WAKEUP;
	pw_cfg.wdt_wakeup_en = (bool)false;
	pw_cfg.rtc_wakeup_en = (bool)false;
	pw_cfg.timer_wakeup_en = (bool)true;
	pw_cfg.gpi_wakeup_en = (bool)true;
	pw_cfg.gpi_wakeup_cfg = U32BIT(KEY1);	//中断唤醒pin
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
				break;
			default :
				break;
		}
	}
	#endif
}

void gpio_callback(void)
{
//	struct gap_ble_addr dev_addr;
//	/*get bluetooth address */
////	GetDevAddr(&dev_addr);
////	dev_addr.addr[0]++;
////	SetDevAddr_toflash(&dev_addr);
//	delay_ms(1000);
}

////////////////////////////////////////////////////////////////////


int main(void)
{
	__disable_irq();

//	RFWakeup();
//	DelayMS(100);
//	UartEn(true);
	ble_init();  //蓝牙初始化，系统主时钟初始化64M,32K时钟初始化为LPO
//	
//	#ifndef _DEBUG_
//	UartEn(false);
//	DelayMS(100);
//	#endif
	
	//根据需要重新设置时钟为4M并校准
	MCUClockSwitch(SYSTEM_CLOCK_64M_RCOSC);
	RCOSCCalibration();
	#ifdef USER_32K_CLOCK_RCOSC
	ClockSwitch(SYSTEM_32K_CLOCK_RCOSC);
	GAPBBDelayMS(500);
	LPOCalibration();						//这是内部RC32k晶振的校准函数	经过该函数后定时器能够得到一个比较准确的值
	#else
	ClockSwitch(SYSTEM_32K_CLOCK_XOSC);
	#endif
	
	//software:timr0   blelib timer1
	SYD_Timer_Init(EVT_NUM, syd_sysTimer);	
	Timer_Evt_List();

	SYD_RTC_Init(RTCEVT_NUM, syd_rtc);	
	RTC_Evt_List();
	
	gpio_init();	//低功耗时GPIO的初始统一设置
		
	GPIO_Set_Output( U32BIT(LED1));	
	GPIO_Pin_Set(U32BIT(LED1));
	
	//io_irq_enable(U32BIT(KEY1), gpio_callback);
	RFSleep();// StartAdv();	//开始广播
	
	
	
	
	#ifdef _SYD_RTT_DEBUG_
		DebugLogInit();
		dbg_printf("Syd8811 RTT LOG %s:%s\r\n",__DATE__ ,__TIME__);
	#elif defined(_DEBUG_)
		dbg_init();
		UartEn(true);
		//dbg_printf("Syd8811 UART0 LOG %s:%s\r\n",__DATE__ ,__TIME__);
		dbg_printf("Syd8811 UART OTA  %s:%s\r\n",__DATE__ ,__TIME__);
		//dbg_printf("Syd8811 UART SALAVE OTA  %s:%s\r\n",__DATE__ ,__TIME__);
		//dbg_printf("Syd8811 UART OTA test FW LOG %s:%s\r\n",__DATE__ ,__TIME__);
	#endif
	
	uart_0_init();
	uart_1_init();
	
	memset((void*)&uart_rx_buff, 0x00, sizeof(uart_rx_buff));
	__enable_irq();	
	
	//uart_master_ota_init(uart_ota_bin, sizeof(uart_ota_bin));
	
	while(1)
	{
		ble_sched_execute();	//协议栈任务
		
		//GPIO_Pin_Turn(U32BIT(LED1));
		
		//串口接收数据处理
		if(uart_rx_buff.flag == 2)
		{
			dbg_hexdump("uart rx data\r\n", (uint8_t *)uart_rx_buff.receive_buff, uart_rx_buff.all_len);
  		//slave处理OTA流程
			uart_slave_ota_handle((uint8_t *)(uart_rx_buff.receive_buff+1), uart_rx_buff.all_len-1);
		
			//master进入了OTA流程
			if(uart_master_ota_flag)
			{
				uart_master_ota_handle((uint8_t *)(uart_rx_buff.receive_buff+1), uart_rx_buff.all_len-1);
			}
			memset((void*)&uart_rx_buff, 0x00, sizeof(&uart_rx_buff));
		}
		
		//开始OTA
    if(GPIO_Pin_Read(U32BIT(KEY1)))
		{
			delay_ms(5);
			if(GPIO_Pin_Read(U32BIT(KEY1)))
			{
				#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
					dbg_printf("KEY1 Press\r\n");
				#endif
				memset((void*)&uart_rx_buff, 0x00, sizeof(uart_rx_buff));
				while(GPIO_Pin_Read(U32BIT(KEY1)));
				delay_ms(500);
				uart_master_ota_init(uart_ota_test, sizeof(uart_ota_test));
				uart_master_ota_start();
				
				#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
				dbg_printf("UART MASTER OTA Start\r\n");
				#endif
				
			} 
		}
		
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
				Timer_Evt_Clr(EVT_2S);
			}
			#endif
		}
		if(RTC_EVT) 
    {
			#ifdef	RTCEVT_whole_minute
			if(RTC_EVT&RTCEVT_whole_minute)
			{					
			#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
			Time_clock_Struct time;
			timeAppClockGet((void *)&time);
			 DBGPRINTF_TIMER(("RTCEVT_whole_minute:%d-%d-%d:%d:%d:%d\r\n",time.year_low,time.month,time.day,time.hour,time.minutes,time.seconds));
			#endif

			RTC_EVT_Clr(RTCEVT_whole_minute);
			}
			#endif
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
	}
}

void HardFault_Handler(void)
{	
	DBGPRINTF(("ERR: HardFault!\r\n"));	
	while(1);
}

