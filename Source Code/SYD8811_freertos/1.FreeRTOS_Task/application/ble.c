#define  _BLE_C
/* BLE */
#include "config.h"
#include "debug.h"
#include "SYD_ble_service_Profile.h"
#include "ble.h"
#include "lib.h"
#include "led_key.h"

/* freeRTOS */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"

#include <string.h>

//notify 标志 1代表已经使能 0代表未使能
static uint8_t start_tx=0;
static uint8_t wechat_tx=0;

//connection
uint8_t connect_flag=0;
uint8_t update_latency_mode=0;
uint8_t latency_state=0;

uint8_t ADV_DATA[] = {
						0x03,// length
						0x19,
						0x00,
						0x00,
						0x02,// length
						0x01,// AD Type: Flags
						0x05,// LE Limited Discoverable Mode & BR/EDR Not Supported
						0x03,// length
						0x03,// AD Type: Complete list of 16-bit UUIDs 
						0x01,// UUID: Human Interface Device (0x0001)//12
						0x00,// UUID: Human Interface Device (0x0001)//18
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
						0x06,// length
						0x09,// AD Type: Complete local name
						'U',
						'A',
						'R',
						'T',
						'F',
					  };

uint16_t ADV_DATA_SZ = sizeof(ADV_DATA); 
uint8_t SCAN_DATA[]={0x00};
uint16_t SCAN_DATA_SZ = 0; 

static void setup_adv_data(void)
{
	struct gap_adv_params adv_params;
	static struct gap_ble_addr dev_addr;
	
	uint8_t ScanData[] = {0x00};

	adv_params.type		= ADV_IND;
	adv_params.channel 	= 0x07;  	// advertising channel : 37 & 38 & 39
	adv_params.interval = 200; 		// advertising interval : 125ms (200 * 0.625ms)
	adv_params.timeout 	= 0x02;  	// timeout : 2s

	SetAdvParams(&adv_params);
	
	/* get bluetooth address */
	GetDevAddr(&dev_addr);
	ADV_DATA[15] = dev_addr.addr[0];
	ADV_DATA[16] = dev_addr.addr[1];
	ADV_DATA[17] = dev_addr.addr[2];
	ADV_DATA[18] = dev_addr.addr[3];
	ADV_DATA[19] = dev_addr.addr[4];
	ADV_DATA[20] = dev_addr.addr[5];

	SetAdvData(ADV_DATA, sizeof(ADV_DATA), ScanData, sizeof(ScanData));
}

/*
uint8_t target
0:fast
1:slow
*/
void BLSetConnectionUpdate(uint8_t target)
{
#if 0
	struct gap_link_params  link_app;
	struct gap_smart_update_params smart_params;
	uint8_t buffer_cha1[5]={0XFC,0X01,0X00,0X00,0X00};
	gap_s_link_parameters_get(&link_app);
	#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
	dbg_printf("interval:%x latency:%x\r\n",link_app.interval,link_app.latency);
	#endif
	switch(target){
		case 0: 
				if((link_app.latency !=0) && (link_app.interval >0x10)){
					latency_state=0;
					/* connection parameters */
						smart_params.updateitv_target=0x0010;  //target connection interval (60 * 1.25ms = 75 ms)
						smart_params.updatesvto=0x00c8;  //supervisory timeout (400 * 10 ms = 4s)
					smart_params.updatelatency=0x0000;
					smart_params.updatectrl=SMART_CONTROL_LATENCY | SMART_CONTROL_UPDATE;
					smart_params.updateadj_num=MAX_UPDATE_ADJ_NUM;
					gap_s_smart_update_latency(&smart_params);
				}
			  #if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
				DBGPRINTF(("SetUpdate ota link\r\n"));
			  #endif
				BLE_SendData(buffer_cha1,5);
		break;
		case 1:
				if((link_app.latency <0x000A) && (link_app.interval <0x0050)){
					/* connection parameters */
					smart_params.updateitv_target=0x0050;
					smart_params.updatelatency=0x000A;
					smart_params.updatesvto=0x0258;
					smart_params.updatectrl=SMART_CONTROL_LATENCY | SMART_CONTROL_UPDATE;
					smart_params.updateadj_num=MAX_UPDATE_ADJ_NUM;
					gap_s_smart_update_latency(&smart_params);	   
			#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
					DBGPRINTF(("SetUpdate ios link\r\n"));
			#endif
				}
		break;
	}
#endif
}

static void ble_gatt_read(struct gap_att_read_evt evt)
{
	if(evt.uuid == BLE_DEVICE_NAME_UUID)
	{
		uint8_t gatt_buf[]={'U', 'A', 'R', 'T','F'};
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
		uint8_t gatt_buf[]={'4','.','0','0'};
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
	else if(evt.uuid == BLE_SERVICE_UUID_OTA_READ_WRITE)
	{
		uint8_t sz=0;

		uint8_t rsp[sizeof(struct hci_evt)]={0};

		ota_rsp(rsp, &sz);
		
		SetGATTReadRsp(sz, rsp);
	}
	#endif
	else if(evt.uuid == BLE_Battry_Level_UUID)
	{
		//SetGATTReadRsp(0x01, 0X64);
	}
}




//接收函数
static void ble_gatt_write(struct gap_att_write_evt evt)
{
	#ifdef _OTA_
	if(evt.uuid== BLE_SERVICE_UUID_OTA_READ_WRITE)
	{
		update_latency_mode=0;
		ota_cmd(evt.data, evt.sz);
	} else
	#endif
	if(evt.uuid== BLE_UART_Write_UUID)
	{

	}
}


//发送函数
uint8_t BLE_SendData(uint8_t *buf, uint8_t len)
{
	if(start_tx == 1)
	{
		struct gap_att_report report;
		if(wechat_tx)
		{
			report.primary = BLE_WECHAT;
			report.uuid = BLE_WECHAT_Indication_UUID;
			report.hdl = BLE_WECHAT_Indication_VALUE_HANDLE;					
			report.value = BLE_GATT_INDICATION;
			if(len > 20) len = 20;
			return GATTDataSend(BLE_GATT_INDICATION, &report, len, buf);
		}
		else
		{
			report.primary = BLE_UART;
			report.uuid = BLE_UART_NOTIFY_UUID;
			report.hdl = BLE_UART_NOTIFY_VALUE_HANDLE;					
			report.value = BLE_GATT_NOTIFICATION;
			return GATTDataSend(BLE_GATT_NOTIFICATION, &report, len, buf);
		}
	}
	return 0;
}

//BLE IRQ_HANDLE
void ble_evt_callback(struct gap_ble_evt *p_evt)
{
	if(p_evt->evt_code == GAP_EVT_ADV_END)
	{		
		StartAdv();
		#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
		DBGPRINTF(("GAP_EVT_ADV_END\r\n"));
		#endif
	}
	else if(p_evt->evt_code == GAP_EVT_CONNECTED)	 //连接事件
	{
		start_tx = 0;
		connect_flag=1;								 //连接状态
		latency_state=0;
		update_latency_mode=0;
		
		#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_) 
		DBGHEXDUMP("GAP_EVT_CONNECTED addr:",p_evt->evt.bond_dev_evt.addr,sizeof(p_evt->evt.bond_dev_evt.addr));
		#endif
		
		BLSetConnectionUpdate(1);
	}
	else if(p_evt->evt_code == GAP_EVT_DISCONNECTED) //断连事件
	{	
		connect_flag=0;								 //连接状态
		start_tx = 0;
		#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_) 
		DBGPRINTF("GAP_EVT_DISCONNECTED(%02x)\r\n",p_evt->evt.disconn_evt.reason);
		#endif   
		StartAdv();
	}
	else if(p_evt->evt_code == GAP_EVT_ATT_HANDLE_CONFIGURE)
	{					
		if((p_evt->evt.att_handle_config_evt.uuid == BLE_WECHAT)||(p_evt->evt.att_handle_config_evt.uuid == BLE_UART))
		{
			if(p_evt->evt.att_handle_config_evt.hdl == (BLE_WECHAT_Indication_VALUE_HANDLE + 1))
			{			
				if(p_evt->evt.att_handle_config_evt.value == BLE_GATT_NOTIFICATION)
				{
					DBGPRINTF(("start_tx enable\r\n"));
					start_tx = 1;
				}
				else
				{			
					start_tx = 0;
				}
			}
		}	
		else if(p_evt->evt.att_handle_config_evt.uuid == BLE_UART)
		{
			if(p_evt->evt.att_handle_config_evt.hdl == (BLE_WECHAT_Indication_VALUE_HANDLE + 1))
			{
				if(p_evt->evt.att_handle_config_evt.value == BLE_GATT_NOTIFICATION)
					wechat_tx = 1;
				else
					wechat_tx = 0;
			}
		}
//DBGPRINTF(("GAP_EVT_ATT_HANDLE_CONFIGURE uuid:(%02x)\r\n",p_evt->evt.att_handle_config_evt.uuid));
	}
	else if(p_evt->evt_code == GAP_EVT_ATT_WRITE)
	{
		ble_gatt_write(p_evt->evt.att_write_evt);
//		DBGPRINTF(("GAP_EVT_ATT_WRITE uuid:(%02x)\r\n",p_evt->evt.att_write_evt.uuid));
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
	else if(p_evt->evt_code == GAP_EVT_ENC_START)
	{
		#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_) 
			DBGPRINTF(("GAP_EVT_ENC_START\r\n"));
		#endif
	}
	else if(p_evt->evt_code == GAP_EVT_L2CAP_UPDATE_RSP)
	{	
		switch(p_evt->evt.l2cap_update_rsp_evt.result)
		{
			case CONN_PARAMS_ACCEPTED:
			{
				dbg_printf("\r\nupdate rsp ACCEPTED.");
			}break;
			case CONN_PARAMS_REJECTED:
			{
				dbg_printf("update rsp REJECTED.");
			}break; 
			case CONN_PARAM_SMART_TIMEROUT:
			{
				dbg_printf("Update rsp TIMEROUT.");
			}break;
			case CONN_PARAM_SMART_SUCCEED:
			{
				struct gap_link_params  link_app;
				GetLinkParameters(&link_app);
				dbg_printf("\r\nupdate rsp SUCCEED.");
				dbg_printf("\r\ninterval:%fms, latency:%d.\r\n", (float)link_app.interval*1.25, link_app.latency);
			}break;
			case CONN_PARAM_LATENCY_ENABLE:
			{
				//dbg_printf("\r\nEnable latency.\r\n");
			}break;
			case CONN_PARAM_LATENCY_DISABLE:
			{
				//dbg_printf("\r\nDisable latency.");
			}break;
		}
	}
}


void ble_init(void)
{	
	struct gap_att_report_handle *g_report;
	struct smp_pairing_req sec_params;
	struct gap_evt_callback evt;	
	struct gap_wakeup_config pw_cfg;

	BleInit();

	GetGATTReportHandle(&g_report);

	/* security parameters */
	sec_params.io = IO_DISPLAY_ONLY;
	sec_params.oob = OOB_AUTH_NOT_PRESENT;
	sec_params.flags = AUTHREQ_BONDING;
	sec_params.mitm = 1;
	sec_params.max_enc_sz = 16;
	sec_params.init_key = 0;
	sec_params.rsp_key = (SMP_KEY_MASTER_IDEN | SMP_KEY_ADDR_INFO);
	SetSecParams(&sec_params);
	
	evt.evt_mask = (GAP_EVT_CONNECTION_SLEEP | GAP_EVT_CONNECTION_INTERVAL);
	evt.p_callback = &ble_evt_callback;
	SetEvtCallback(&evt);

	/* Bond Manager (MAX:10) */
	SetBondManagerIndex(0x00);

	setup_adv_data();
	
	/* Configure the wake up source */
	pw_cfg.wakeup_type     = SLEEP_WAKEUP;
	pw_cfg.wdt_wakeup_en   = false;
	pw_cfg.rtc_wakeup_en   = false;
	pw_cfg.timer_wakeup_en = true;
	pw_cfg.gpi_wakeup_en   = true;
	pw_cfg.gpi_wakeup_cfg  = U32BIT(KEY1);
	WakeupConfig(&pw_cfg);
}
