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
#include "uart_protocol.h"
#include "softtimer.h"
#include "oled.h"
#include "led_key.h"

//connection
uint8_t  connect_flag=0;
static uint8_t latency_state = 0;
uint8_t update_latency_mode=0;

static uint16_t uart_delay_cnt=0;

static struct gap_att_report_handle *g_report;   //GATT�����б�ͷ,���뵽Э��ջ�н��г�ʼ��
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

Uart_Rx_Buf_t uart_rx_buf;		//��ŴӴ����յ�������
Uart_Tx_Buf_t uart_tx_buf;		//��ŴӴ��ڷ���������

static void gpio_callback(void);

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
			#ifdef _GPIO_LED_CONTROL_
			case GPIO_LED_CONNECT:   
			case GPIO_LED_NOTIFYEN:
			case GPIO_LED_WRITEING:
			case GPIO_LED_READING:
				io_output |=U32BIT(i);   //����͵�ƽ
				io_outlow |=U32BIT(i);
			break;
			#endif
			
            case GPIO_UART_TX:
			case GPIO_UART_RX:
			break;
				
			
			default:   //Ĭ����������
			io_input |=U32BIT(i);
			io_pull |=U32BIT(i);
			break;
		}
    }
  
//	BBRFWrite(0x7f, 0x00);    //����GPIO21ΪIO��ģʽ�������Ǹ�λ�ܽ�
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

	*(uint8_t *)0x40020014 = 0x01;		//����ADV_PITVΪ1�����͹���
}

static void setup_scan_params()
{
	struct gap_scan_params scan_params;	
	
	scan_params.mode=ACTIVE_SCAN;
	scan_params.channel = 0x07;  // scan channel : 37 & 38 & 39
	scan_params.interval = 1600; // scan interval : 1000ms (1600 * 0.625ms)
	scan_params.window =1600; // scan window : 1000ms (1600 * 0.625ms)
	scan_params.timeout = 0x1e;  // timeout : 30s

	SetScanParams(&scan_params);	
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
		
		uint32_t i;
		uart_tx_buf.data[uart_tx_buf.header][0] = evt.sz;
		for(i=1; i<=evt.sz; i++)
		{
			uart_tx_buf.data[uart_tx_buf.header][i] = evt.data[i-1];
		}
		uart_tx_buf.header++;
		if(uart_tx_buf.header >= MAX_TX_LENGTH)
		{
			uart_tx_buf.header = 0;
		}
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

//�������յ�������һ�δ�uartȫ����ȥ
static void sendToUart(void)
{
	uint32_t header= uart_tx_buf.header;

	if(header != uart_tx_buf.tail)
	{
		while(header != uart_tx_buf.tail)
		{
			uart_cmd(&uart_tx_buf.data[uart_tx_buf.tail][1], uart_tx_buf.data[uart_tx_buf.tail][0]);
 
			uart_tx_buf.tail++;
			if(uart_tx_buf.tail >= MAX_TX_LENGTH)
			{
				uart_tx_buf.tail = 0;
			}
		}
	}
}

static void timer_1_callback(void)
{
	uart_delay_cnt++;
	if((uart_rx_buf.header == uart_rx_buf.tail) && (uart_delay_cnt>3))
	{
//		if(latency_state==1)
//		{
			latency_state=0;
//			GAPConnectionLatencyMode(true);
//			DBGPRINTF(("Latency Enabled!\r\n"));
			
			timer_1_disable();
//		}
	}
}

static void send_to_master(void)
{
	uint32_t len, header, tail;

	header = uart_rx_buf.header;
	tail   = uart_rx_buf.tail;
	
	if(header != tail)
	{
		if(latency_state==0)
		{
			//GAPConnectionLatencyMode(false);
			latency_state=1;
			//DBGPRINTF(("Latency Disabled!\r\n"));
			uart_delay_cnt = 0;
			timer_1_enable(32768/200, timer_1_callback);
		}
	}
	else
	{
		return;
	}

	//caculate len
	if(header >= tail)
	{
		len = header - tail;
	}
	else
	{
		len = header + MAX_RX_LENGTH - tail;
	}

	if(len>=20)
	{
		for(; len>=20; len-=20)
		{
			uint8_t send_data[20], i;
			
			uart_delay_cnt = 0;
		
			//memcpy 20 byte
			for(i=0; i<20; i++)
			{
				send_data[i] = uart_rx_buf.data[tail++];
				
				if(tail >= MAX_RX_LENGTH)
				{
					tail = 0;
				}
			}
			//DBGPRINTF(("BLE_Send 20\r\n"));
			//send
			if(BLE_SendUARTData(send_data, 20))
			{
				uart_rx_buf.tail = tail;
			}
			else
			{
				break;
			}
		}
	}
	else if(len >= 1)
	{
		if(uart_delay_cnt >= 3)
		{
			uint8_t send_data[20],i;
			//memcpy len byte
			for(i=0; i<len; i++)
			{
				send_data[i] = uart_rx_buf.data[tail++];
				
				if(tail >= MAX_RX_LENGTH)
				{
					tail = 0;
				}
			}
			//DBGPRINTF(("BLE_Send %x %x\r\n",len,uart_delay_cnt));
			//send
			if(BLE_SendUARTData(send_data, len))
			{
				uart_rx_buf.tail = tail;
			}
			
			uart_delay_cnt = 0;
		}
	}
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
		connect_flag=1;								 //����״̬
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
		
		//clr uart rx fifo
		uart_rx_buf.header = uart_rx_buf.tail;		
		Timer_Evt_Stop(EVT_1S_OTA);
		setup_adv_data();		//�Ͽ�����֮�󹦺Ĵ�10uA
		StartAdv();	
		
		#ifdef _GPIO_LED_CONTROL_
		GPIO_Pin_Clear(U32BIT(GPIO_LED_CONNECT));
		GPIO_Pin_Clear(U32BIT(GPIO_LED_NOTIFYEN));
		#endif
		
		UartEn(false);	//������RF sleepʱ�ر�XO
		DBGPRINTF(("start adv @ disc!\r\n")); 
	}
	else if(p_evt->evt_code == GAP_EVT_ATT_HANDLE_CONFIGURE)
	{
		if(p_evt->evt.att_handle_config_evt.uuid == BLE_UART)
		{
			if(p_evt->evt.att_handle_config_evt.value == BLE_GATT_NOTIFICATION)
			{
				start_tx |= 0x01;
				UartEn(true);	//������RF sleepʱ�ر�XO�����ߵ�ʱ����Ϊ32Mhz�����ڣ����Թ��ĺܸ�
				
				//clr uart rx fifo
				uart_rx_buf.header = uart_rx_buf.tail;
				
				#ifdef _GPIO_LED_CONTROL_
				GPIO_Pin_Set(U32BIT(GPIO_LED_NOTIFYEN));
				#endif
				
				DBGPRINTF(("UART notify Enabled!\r\n"));
			}
			else
			{
				start_tx &= ~0x01;
				UartEn(false);	//����Ӳ�����ɿ���32Mhz�������ߵ�ʱ�򹦺ĺܵ�
				
				#ifdef _GPIO_LED_CONTROL_
				GPIO_Pin_Clear(U32BIT(GPIO_LED_NOTIFYEN));
				#endif
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
	else if(p_evt->evt_code == GAP_EVT_SCAN_REPORT)
	{
		DBGPRINTF("SCAN_REPORT rssi:%x\r\n",p_evt->evt.scan_report_evt.rssi);
		DBGPRINTF("dev_adv type:%x addr:%02x:%02x:%02x:%02x:%02x:%02x\r\n",p_evt->evt.scan_report_evt.dev.peer_addr.type,p_evt->evt.scan_report_evt.dev.peer_addr.addr[5] \
		,p_evt->evt.scan_report_evt.dev.peer_addr.addr[4],p_evt->evt.scan_report_evt.dev.peer_addr.addr[3],p_evt->evt.scan_report_evt.dev.peer_addr.addr[2] \
		,p_evt->evt.scan_report_evt.dev.peer_addr.addr[1],p_evt->evt.scan_report_evt.dev.peer_addr.addr[0]
		);
		DBGHEXDUMP("DATA:",p_evt->evt.scan_report_evt.adv_data,p_evt->evt.scan_report_evt.data_len);
	}
	else if(p_evt->evt_code == GAP_EVT_SCAN_END)
	{
		StartScan();
		DBGPRINTF(("GAP_EVT_SCAN_END\r\n"));
	}
}

static void ble_init()
{	
	struct gap_evt_callback evt;		
	struct smp_pairing_req sec_params;	
	struct gap_wakeup_config pw_cfg;

	BleInit();	   //���õײ�ĳ�ʼ������
	SetWinWideMinusCnt(1);   //���õײ㴰�ڲ���

	GetGATTReportHandle(&g_report);   //��ȡ����ͷ

	/* security parameters */
	sec_params.io = IO_NO_INPUT_OUTPUT;   //û������Ҳû���������ʹ��passkey����ʽ���
	sec_params.oob = OOB_AUTH_NOT_PRESENT;
	sec_params.flags = AUTHREQ_BONDING;
	sec_params.mitm = 0;
	sec_params.max_enc_sz = 16;
	sec_params.init_key = 0;
	sec_params.rsp_key = (SMP_KEY_MASTER_IDEN |SMP_KEY_ADDR_INFO);
	SetSecParams(&sec_params);   //���ð�ȫ����
	
	evt.evt_mask=(GAP_EVT_CONNECTION_SLEEP|GAP_EVT_CONNECTION_INTERVAL);   //���������¼�����
	evt.p_callback=&ble_evt_callback;   //�����������Ӻ������������ײ�״̬�����ı䣨������ߡ����ߵȣ�����Э��ջ�����øù��Ӻ�������Ӧ�ó��������¼��仯��
	SetEvtCallback(&evt);   //�ѹ��Ӻ����������¼��������ø�����Э��ջ

	/* Bond Manager (MAX:10) */
	SetBondManagerIndex(0x00);

	setup_adv_data();  //���ù㲥����
	setup_scan_params();
	/*
	��POWERDOWN_WAKEUPʱ��
	PW_CTRL->DSLP_LPO_EN = true����Щ�ж�Դ���ܻ��Ѳ���λ���У�
	�����false��ֻ��pin�ܻ��Ѳ���λ����
	*/
	pw_cfg.wakeup_type = SLEEP_WAKEUP;
	pw_cfg.wdt_wakeup_en = (bool)false;
	pw_cfg.rtc_wakeup_en = (bool)false;
	pw_cfg.timer_wakeup_en = (bool)true;
	pw_cfg.gpi_wakeup_en = (bool)false;
	pw_cfg.gpi_wakeup_cfg = WAKEUP_PIN;	//�жϻ���pin
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





int main(void)
{
	uint8_t while_cnt=0;
	__disable_irq();   //�ر����ж�

	ble_init();  //������ʼ����ϵͳ��ʱ�ӳ�ʼ��64M,32Kʱ�ӳ�ʼ��ΪLPO
	
	//������Ҫ��������ʱ��Ϊ64M��У׼
	MCUClockSwitch(SYSTEM_CLOCK_64M_RCOSC);
	RCOSCCalibration();   //���ڲ�64MROSC����У׼
	#ifdef USER_32K_CLOCK_RCOSC
	ClockSwitch(SYSTEM_32K_CLOCK_RCOSC);   //�����ڲ�32.768Khzʱ����Ϊ���ٶ�ʱ�����Ź���ģ���ʱ��Դ
	GAPBBDelayMS(500);
	LPOCalibration();						//�����ڲ�RC32k�����У׼����	�����ú�����ʱ���ܹ��õ�һ���Ƚ�׼ȷ��ֵ
	#else
	ClockSwitch(SYSTEM_32K_CLOCK_XOSC);   //�����ⲿ32.768Khzʱ�Ӿ�����Ϊ���ٶ�ʱ�����Ź���ģ���ʱ��Դ
	#endif
	
	#ifdef _SYD_RTT_DEBUG_
		DebugLogInit();   //��ʼ��RTT
	#endif
	
	dbg_printf("Syd8811_UART %s:%s\r\n",__DATE__ ,__TIME__);   //ʹ��RTT���д�ӡ
	
	//software:timr0   blelib timer3
	SYD_Timer_Init(EVT_NUM, syd_sysTimer);	    //��ʼ�������ʱ���������ʱ��ʹ��TIMER0
	Timer_Evt_List();   //���������ʱ��

	SYD_RTC_Init(RTCEVT_NUM, syd_rtc);	  //��ʼ��RTC��ʱ������ΪRTCר����������ʱ�ӵģ���ʱ���Ĺ����Ƕ���ģ����Խ������ܳ��Ķ�ʱ������RTC��ʱ��������10 60S 600S��
	RTC_Evt_List();   //����RTC��ʱ��
	
	gpio_init();	//�͹���ʱGPIO�ĳ�ʼͳһ����
//	uart_0_init();	//����͸�����ܳ�ʼ��
	
	uart_tx_buf.header = 0;
	uart_tx_buf.tail = 0;
	
	oled_init();    //OLED��ʼ��
	
	oled_printf(0,0,"SYD Inc.");    //��ӡ
	oled_printf(0,2,"SYD8811_UART"); 
	oled_printf(0,4,"%s",__DATE__); 
	{
		struct gap_ble_addr dev_addr;
		/*get bluetooth address */
		GetDevAddr(&dev_addr);   
		oled_printf(0,6,"MAC:",__DATE__);  //��ӡ�豸��ַ
		oled_printf(4*8,6,"%02x",dev_addr.addr[5]);    
		oled_printf(6*8,6,"%02x",dev_addr.addr[4]); 
		oled_printf(8*8,6,"%02x",dev_addr.addr[3]); 
		oled_printf(10*8,6,"%02x",dev_addr.addr[2]); 
		oled_printf(12*8,6,"%02x",dev_addr.addr[1]); 
		oled_printf(14*8,6,"%02x",dev_addr.addr[0]); 
	}
	
	
	GPIO_Set_Output( U32BIT(LED1));	  //��ʼ��LED1
	GPIO_Pin_Set(U32BIT(LED1));
	
	//StartAdv();		//��ʼ�㲥
	StartScan();        //��ʼɨ��
	
	__enable_irq();	 //�������ж�
	
	while(1)
	{
		ble_sched_execute();	//Э��ջ����
		
		GPIO_Pin_Turn(U32BIT(LED1));  //��תLED1
		oled_printf(14*8,0,"%02x",while_cnt++); 
		
//		sendToUart();	//ͨ�����ڷ�������

		if(TIMER_EVT) 
		{
			#ifdef	EVT_1S_OTA
			if(TIMER_EVT&EVT_1S_OTA)     //��1S��ʱ��������ʱ��
			{
				ota_manage();     //ota ���̹��� ������Ļ��
				Timer_Evt_Clr(EVT_1S_OTA);
				#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
				DBGPRINTF(("EVT_1S_OTA\r\n"));
				#endif
			}
			#endif
			#ifdef	EVT_2S
			if(TIMER_EVT&EVT_2S)    //��2S��ʱ��������ʱ��
			{
				Connection_latency();   //���Ӳ����������
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
					 LPOCalibration();						//�����ڲ�RC32k�����У׼����	�����ú�����ʱ���ܹ��õ�һ���Ƚ�׼ȷ��ֵ
					 //if(connect_flag && (latency_state==1)) gap_s_connection_latency_mode(0x01);
				#endif
				#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
				 DBGPRINTF(("RTCEVT_185S\r\n"));
				#endif
				RTC_EVT_Clr(RTCEVT_185S);
			}
			#endif
		}
		
		if(start_tx & 0x01)		//connected
		{
			//UartEn(true);	//������RF sleepʱ�ر�XO
//			send_to_master();
		}
		else
		{
//			#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
//			 DBGPRINTF(("goto SystemSleep\r\n"));
//			#endif
			SystemSleep();				//ϵͳ˯��
		}	
	}
}



void HardFault_Handler(void)
{	
	DBGPRINTF(("ERR: HardFault!\r\n"));	
	while(1);
}

