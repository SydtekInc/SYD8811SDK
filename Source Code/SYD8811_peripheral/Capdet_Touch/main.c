#define  _HID_C

#include "config.h"
#include "timer.h"
#include "softtimer.h"
#include "gpio.h"
#include "DebugLog.h"
#include "delay.h"
#include "ota.h"
#include "SYD_ble_service_service.h"
#include "led_key.h"
#include "capdet_touch.h"
#include <string.h>

//connection
uint8_t  connect_flag=0;
uint8_t latency_state = 0;
uint8_t update_latency_mode=0;
uint16_t key_loop = 0;

static struct gap_att_report_handle *g_report;   //GATT属性列表头,传入到协议栈中进行初始化
static uint8_t start_tx = 0;

uint8_t ADV_DATA[] = {	0x02, // length
					  	0x01, // AD Type: Flags
					  	0x05, // LE Limited Discoverable Mode & BR/EDR Not Supported
					  	0x03, // length
					  	0x03, // AD Type: Complete list of 16-bit UUIDs 
					  	0x01, // UUID: Human Interface Device (0x1812)
					  	0x00, // UUID: Human Interface Device (0x1812)
	                    0X09,// length
					  	0XFF,// AD Type: MANUFACTURER SPECIFIC DATA
						0X00,// Company Identifier (0x00)
						0X00,// Company Identifier (0x00)
						0X00,
						0X00,
						0X00,
						0X00,
						0X00,
						0X00,
						Device_Name_Len+1,// length
						0x09,// AD Type: Complete local name
						Device_Name	  	
					  	};

uint8_t SCAN_DATA[]={
						0X09,// length
						0XFF,// AD Type: MANUFACTURER SPECIFIC DATA
						0X00,// Company Identifier (0x00)
						0X00,// Company Identifier (0x00)
						0X00,
						0X00,
						0X00,
						0X00,
						0X00,
						0X00,
						Device_Name_Len+1,// length
						0x09,// AD Type: Complete local name
						Device_Name
						};


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
    
	#ifdef _USE_SYD_CAPDET_TOUCH_
		PIN_CONFIG->PAD_INPUT_PULL_UP[0] &= (~U32BIT(KEY_INT_PIN)); //remove capdet pull up (key gpio6)
	#endif

    for(i=0;i < 32;i++)
    {
		switch(i)
		{
			#ifdef USER_32K_CLOCK_RCOSC 
			case LED1:
			case LED2:
			#endif
			case LED3:
			case LED4:
				io_output |=U32BIT(i);   //输出高电平
			break;

			case KEY1:
			case KEY2:
			case KEY3:
			case KEY4:
				io_input |=U32BIT(i);   //翻转输入上拉
				io_pull |=U32BIT(i);
				io_invert |=U32BIT(i);  //已上拉唤醒源,取反
			break;
			
			
			
			#ifdef _USE_SYD_CAPDET_TOUCH_
      case KEY_INT_PIN:
      #endif
			
      case GPIO_UART_TX:
			case GPIO_UART_RX:
			#ifndef USER_32K_CLOCK_RCOSC 
			case GPIO_0:
			case GPIO_1:
			#endif	
			break;
				
			
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
		
	PIN_Pullup_Disable(T_QFN_48, io_input & (~io_pull));	
	
	
		
		
	GPIO_Set_Input(io_input,io_invert);
	PIN_Pullup_Enable(T_QFN_48, io_pull);
}

static void setup_adv_data()
{
	struct gap_adv_params adv_params;	
	struct gap_ble_addr dev_addr;
	
	adv_params.type = ADV_IND;
	adv_params.channel = 0x07;  // advertising channel : 37 & 38 & 39
	adv_params.interval = 1600; // advertising interval : 1000ms (1600 * 0.625ms)
	adv_params.timeout = 0x1e;  // timeout : 30s

	SetAdvParams(&adv_params);	
	
//	/* bluetooth address */
//	dev_addr.type = PUBLIC_ADDRESS_TYPE;
//	dev_addr.addr[0] = 0x01;
//	dev_addr.addr[1] = 0x02;
//	dev_addr.addr[2] = 0x03;
//	dev_addr.addr[3] = 0x04;
//	dev_addr.addr[4] = 0x05;
//	dev_addr.addr[5] = 0xAA;
//	SetDevAddr(&dev_addr);
	
		/*get bluetooth address */
	GetDevAddr(&dev_addr);
	ADV_DATA[11] = dev_addr.addr[0];
	ADV_DATA[12] = dev_addr.addr[1];
	ADV_DATA[13] = dev_addr.addr[2];
	ADV_DATA[14] = dev_addr.addr[3];
	ADV_DATA[15] = dev_addr.addr[4];
	ADV_DATA[16] = dev_addr.addr[5];
	
	
	SCAN_DATA[4] = dev_addr.addr[0];
	SCAN_DATA[5] = dev_addr.addr[1];
	SCAN_DATA[6] = dev_addr.addr[2];
	SCAN_DATA[7] = dev_addr.addr[3];
	SCAN_DATA[8] = dev_addr.addr[4];
	SCAN_DATA[9] = dev_addr.addr[5];
	
	SetAdvData(ADV_DATA, sizeof(ADV_DATA), SCAN_DATA, sizeof(SCAN_DATA));

	*(uint8_t *)0x40020014 = 0x01;		//设置ADV_PITV为1，降低功耗
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

void Connection_latency(void){
	update_latency_mode++;
	if(update_latency_mode>=3){
		latency_state=0;
		
		BLSetConnectionUpdate(1);
		
		Timer_Evt_Stop(EVT_2S);
	}
} 


static void ble_gatt_read(struct gap_att_read_evt evt)
{
	if(evt.uuid == BLE_DEVICE_NAME_UUID)
	{
		uint8_t gatt_buf[]={Device_Name};
		uint8_t gatt_buf_sz = sizeof(gatt_buf); 

		SetGATTReadRsp(gatt_buf_sz, gatt_buf);
	}
	else if(evt.uuid == BLE_OTA_Read_Write_UUID)
	{
		uint8_t sz=0;
		uint8_t rsp[sizeof(struct hci_evt)]={0};

		ota_rsp(rsp, &sz);

		SetGATTReadRsp(sz, rsp);
	}
}

static void ble_gatt_write(struct gap_att_write_evt evt)
{
	if(evt.uuid == BLE_UART_Write_UUID)
	{
		// rx data
	}
	else if(evt.uuid== BLE_OTA_Read_Write_UUID)
	{
		ota_cmd(evt.data, evt.sz);
	}
}

uint8_t BLE_SendUARTData(uint8_t *buf, uint8_t len)
{
	if(start_tx & 0x01)
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
	if(p_evt->evt_code == GAP_EVT_ATT_WRITE)
	{
		#ifdef _GPIO_LED_CONTROL_
		GPIO_Pin_Turn(U32BIT(GPIO_LED_WRITEING));
		#endif
		
		ble_gatt_write(p_evt->evt.att_write_evt);
	}
	else if(p_evt->evt_code == GAP_EVT_ATT_READ)
	{
		#ifdef _GPIO_LED_CONTROL_
		GPIO_Pin_Turn(U32BIT(GPIO_LED_READING));
		#endif
		
		ble_gatt_read(p_evt->evt.att_read_evt);
	}
	else if(p_evt->evt_code == GAP_EVT_CONNECTED)
	{
		connect_flag=1;								 //连接状态
		update_latency_mode=0;
		
		Timer_Evt_Start(EVT_2S);
		
		#ifdef _GPIO_LED_CONTROL_
		GPIO_Pin_Set(U32BIT(GPIO_LED_CONNECT));
		#endif
		
		DBGHEXDUMP("Connected addr:",p_evt->evt.bond_dev_evt.addr,sizeof(p_evt->evt.bond_dev_evt.addr));
	}
	else if(p_evt->evt_code == GAP_EVT_DISCONNECTED)
	{		
		DBGPRINTF("Disconnected,reson:0x%02x\r\n", p_evt->evt.disconn_evt.reason);

		start_tx = 0;
		connect_flag=0;
		
		Timer_Evt_Stop(EVT_1S_OTA);
		setup_adv_data();		//断开连接之后功耗大10uA
		StartAdv();	
		
		#ifdef _GPIO_LED_CONTROL_
		GPIO_Pin_Clear(U32BIT(GPIO_LED_CONNECT));
		GPIO_Pin_Clear(U32BIT(GPIO_LED_NOTIFYEN));
		#endif
		
		UartEn(false);	//不允许RF sleep时关闭XO
		DBGPRINTF(("start adv @ disc!\r\n")); 
	}
	else if(p_evt->evt_code == GAP_EVT_ATT_HANDLE_CONFIGURE)
	{
		if(p_evt->evt.att_handle_config_evt.uuid == BLE_UART)
		{
			if(p_evt->evt.att_handle_config_evt.value == BLE_GATT_NOTIFICATION)
			{
				start_tx |= 0x01;
				DBGPRINTF(("UART notify Enabled!\r\n"));
			}
			else
			{
				start_tx &= ~0x01;
				DBGPRINTF(("UART notify Disabled!\r\n"));
			}
		}
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
	else if(p_evt->evt_code == GAP_EVT_CONN_UPDATE_COMP)
	{
		struct gap_link_params link;
		GetLinkParameters(&link);
		DBGPRINTF("CONN_UPDATE_COMP: %d, %d, %d\r\n", link.interval, link.latency, link.svto);
	}
	else if(p_evt->evt_code == GAP_EVT_ADV_END)
	{
		StartAdv();
		//DBGPRINTF(("GAP_EVT_ADV_END\r\n"));
	}
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
	pw_cfg.timer_wakeup_en = (bool)false;
	pw_cfg.gpi_wakeup_en = (bool)true;
	
	#ifdef _USE_SYD_CAPDET_TOUCH_
	pw_cfg.capdet_wakeup_en = true;
	#endif
	
	
	
	pw_cfg.gpi_wakeup_cfg = U32BIT(KEY1) | U32BIT(KEY2) | U32BIT(KEY3) | U32BIT(KEY4);	//中断唤醒pin
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

void Timer_Evt_Handle_20ms(void)
{
//	key事件处理
	#ifdef _USE_SYD_CAPDET_TOUCH_
	if(syd_capdet_key.press & SYD_CAPDET_TOUCH_CHANNEL)
	#else
	if(GPIO_Pin_Read(U32BIT(KEY_INT_PIN))==1)
	#endif
	{
		key_loop++;		

		if(key_loop == 1)
		{
			DBGPRINTF("Capdet Start Press\r\n");
		}
		
		if(key_loop==200)//4s
		{
			GPIO_Pin_Turn(U32BIT(LED4));
			DBGPRINTF("Capdet long Press\r\n");
		}
	}
	else
	{
		Timer_Evt_Stop(EVT_20MS);
		if((key_loop>=1)&&(key_loop<100))
		{
			DBGPRINTF("Capdet short Press\r\n");
			DBGPRINTF("Capdet Release\r\n");
			
			GPIO_Pin_Turn(U32BIT(LED3));
			
		}
		key_loop=0;
  }   
}


int main(void)
{
	__disable_irq();	

	ble_init();  //蓝牙初始化，系统主时钟初始化64M,32K时钟初始化为LPO
	
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
	
	#ifdef _SYD_RTT_DEBUG_
		DebugLogInit();
	#endif
	
	dbg_printf("Syd8811_UART %s:%s\r\n",__DATE__ ,__TIME__);
	
	//software:timr0   blelib timer1
	SYD_Timer_Init(EVT_NUM, syd_sysTimer);	
	Timer_Evt_List();

	SYD_RTC_Init(RTCEVT_NUM, syd_rtc);	
	RTC_Evt_List();
	
	gpio_init();	//低功耗时GPIO的初始统一设置

	delay_ms(10);
	
	StartAdv();		//开始广播

	__enable_irq();	
	
	
	#ifdef _USE_SYD_CAPDET_TOUCH_
		capdet_init_all_256();
	#endif
	
	
	while(1)
	{
		ble_sched_execute();	//协议栈任务
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
				Connection_latency();   //连接参数相关设置
				Timer_Evt_Clr(EVT_2S);
			}
			#endif
			#ifdef	EVT_20MS
			if(TIMER_EVT&EVT_20MS)
			{
				Timer_Evt_Handle_20ms();   //触摸事件处理函数
				Timer_Evt_Clr(EVT_20MS);
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
			#ifdef	RTCEVT_10S
			if(RTC_EVT&RTCEVT_10S)
			{
				#ifdef _WDT_
				 wdt_clear();
				#endif

				#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
				 DBGPRINTF(("RTCEVT_10S\r\n"));
				#endif

				RTC_EVT_Clr(RTCEVT_10S);
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
		
		
		#ifdef  _USE_SYD_CAPDET_AUTO_CALIBRATION_
		//if((capdet_calibration_state &BIT5) && (down_oled==0))//BIT5 :0 空闲状态   1：可以校准
		if(capdet_calibration_state &BIT5)//BIT5 :0 空闲状态   1：可以校准
		{
		 capdet_calibration_state &=~BIT5;
		 capdet_calibration_state |=BIT7;
		 capdet_calibration_cnt=0;
		 CapDetForceWakeUp();
		 DBGPRINTF(("capdet_calibration->init_all\r\n"));
		}
		#endif

	}
}

void HardFault_Handler(void)
{	
	DBGPRINTF(("ERR: HardFault!\r\n"));	
	while(1);
}

