#ifndef _BLE_LIB_H_
#define _BLE_LIB_H_

#include "ARMCM0.h"

enum _RETURN_STATUS_ {
	_PARAM_ERROR_ = 0x00,
	_NO_ERROR_ = 0x01,
};

enum _COMPANY_ID_{
	COMPANY_ID_SYD	= 0x0,
};

enum _QFN_TYPE_{
	T_QFN_48 = 0,
	T_QFN_32 = 1,
};

#ifndef CONFIG_TARGET_LIB

#pragma pack(1)

#define MAX_ATT_REPORT_HDL	20
#define MAX_ATT_DATA_SZ	23
#define BD_ADDR_SZ 			6
#define MAX_KEY_SZ			16
#define MIN_KEY_SZ			7
#define MAX_RAND_SZ		8
#define MAX_EDIV_SZ			2
#define ACCESS_CODE_SZ		4
#define MAX_ADV_DATA_SZ	31
#define MAX_SCAN_DEV_NUM		8

#define DIR_IN		0
#define DIR_OUT		1

enum SCAN_TYPE {
	PASSIVE_SCAN	= 0x00,
	ACTIVE_SCAN	= 0x01,
};

enum _BLE_ADDRESS_TYPE_{
	PUBLIC_ADDRESS_TYPE	= 0x00,
	RANDOM_ADDRESS_TYPE 	= 0x01,
};

enum GAP_RET_STATUS{
	RET_FAIL			= 0x00,
	RET_SUCCESS		= 0x01,
};

enum _EVT_TYPE_{
	GAP_EVT	= 0x00,
};

enum _GAP_EVT_{
	GAP_EVT_ADV_END						= 0x00000001,
	GAP_EVT_CONNECTED					= 0x00000002,
	GAP_EVT_DISCONNECTED					= 0x00000004,
	GAP_EVT_PAIRING_COMP					= 0x00000008,
	GAP_EVT_PASSKEY_REQ					= 0x00000010,
	GAP_EVT_SHOW_PASSKEY_REQ			= 0x00000020,
	GAP_EVT_CONNECTION_INTERVAL			= 0x00000040,
	GAP_EVT_CONNECTION_SLEEP				= 0x00000080,
	GAP_EVT_ATT_READ						= 0x00000100,
	GAP_EVT_ATT_WRITE						= 0x00000200,
	GAP_EVT_ATT_PREPARE_WRITE			= 0x00000400,
	GAP_EVT_ATT_EXECUTE_WRITE			= 0x00000800,
	GAP_EVT_ATT_HANDLE_CONFIRMATION	= 0x00001000,
	GAP_EVT_ATT_HANDLE_CONFIGURE		= 0x00002000,
	GAP_EVT_ENC_START						= 0x00004000,
	GAP_EVT_L2CAP_UPDATE_RSP				= 0x00008000,
	GAP_EVT_CONN_UPDATE_COMP			= 0x00010000,
	GAP_EVT_SCAN_REPORT					= 0x00020000,
	GAP_EVT_SCAN_END						= 0x00040000,
	GAP_EVT_PAIRING_START					= 0x00080000,
};

enum _ADV_CH_PKT_TYPE_{
	ADV_IND 			= 0x00,
	ADV_DIRECT_IND 	= 0x01,
	ADV_NOCONN_IND	= 0x02,
	SCAN_REQ			= 0x03,
	SCAN_RSP			= 0x04,
	CONNECT_REQ		= 0x05,
	ADV_SCAN_IND		= 0x06,
};

enum BLE_SEND_TYPE {
	BLE_GATT_NOTIFICATION	= 0x0001,
	BLE_GATT_INDICATION	= 0x0002,
};

enum WAKEUP_TYPE {
	SLEEP_WAKEUP			= 0,
	POWERDOWN_WAKEUP	= 1,
};

enum SMP_IO_CAPABILITY {
	IO_DISPLAY_ONLY		= 0x00,
	IO_DISPLAY_YESNO		= 0x01,
	IO_KEYBOARD_ONLY		= 0x02,
	IO_NO_INPUT_OUTPUT	= 0x03,	
	IO_KEYBOARD_DISPLAY	= 0x04,	
};

enum SMP_OOB_FLAG {
	OOB_AUTH_NOT_PRESENT= 0x00,
	OOB_AUTH_PRESENT		= 0x01,
};

enum SMP_BONDING_FLAGS {
	AUTHREQ_NO_BONDING	= 0x00,
	AUTHREQ_BONDING		= 0x01,
};

enum SMP_KEY_DISTRIBUTION {
	SMP_KEY_MASTER_IDEN	= 0x01,
	SMP_KEY_ADDR_INFO	= 0x02,
	SMP_KEY_SIGNIN_INFO	= 0x04,
};

enum SMP_FAILED_CODE {
	SMP_RESERVED					= 0x00,
	SMP_PASSKEY_ENTRY_FAILED		= 0x01,
	SMP_OOB_NOT_AVAILABLE		= 0x02,
	SMP_AUTH_REQUIREMENTS		= 0x03,	
	SMP_CONFIRM_VALUE_FAILED		= 0x04,	
	SMP_PAIRING_NOT_SUPPORTED	= 0x05,
	SMP_ENCTYPTION_KEY_SZ		= 0x06,
	SMP_COMMAND_NOT_SUPPORTED	= 0x07,
	SMP_UNSPECIFIED_REASON		= 0x08,
	SMP_REPEATED_ATTEMPTS		= 0x09,
	SMP_INVALID_PARAMETERS		= 0x0A,
	SMP_FAIL_TIMEOUT				= 0xFF,
};

enum _SYSTEM_CLOCK_SEL_{
	SYSTEM_CLOCK_64M_RCOSC	= 0x00,
	SYSTEM_CLOCK_32M_RCOSC	= 0x01,
	SYSTEM_CLOCK_16M_RCOSC	= 0x02,
	SYSTEM_CLOCK_8M_RCOSC	= 0x03,
	SYSTEM_CLOCK_4M_RCOSC	= 0x04,
	SYSTEM_CLOCK_2M_RCOSC	= 0x05,
	SYSTEM_CLOCK_1M_RCOSC	= 0x06,
	SYSTEM_CLOCK_500k_RCOSC	= 0x07,
	SYSTEM_CLOCK_16M_XOSC	= 0x08,
};

enum _32K_CLOCK_SEL_{
	SYSTEM_32K_CLOCK_RCOSC	= 0x00,
	SYSTEM_32K_CLOCK_XOSC	= 0x01,
	SYSTEM_32K_CLOCK_32MXO_DIV	= 0x02,	
};

enum SOFT_TIMER_CTRL_TYPE{
	/* 0x0001 ~ 0x0010 internal used */ 
	SOFT_TIMER_0			= 0x0020,
	SOFT_TIMER_1			= 0x0040,
	SOFT_TIMER_2			= 0x0080,
	SOFT_TIMER_3			= 0x0100,
	SOFT_TIMER_4			= 0x0200,
};

typedef void (*sys_timer_cb)(void);

struct gap_ble_addr {
	uint8_t	type;	// \ref _BLE_ADDRESS_TYPE_
	uint8_t	addr[BD_ADDR_SZ];
};

struct gap_key_params{
	uint8_t	ediv[MAX_EDIV_SZ];
	uint8_t	rand[MAX_RAND_SZ];	
	uint8_t	ltk[MAX_KEY_SZ];
	uint8_t	iden[MAX_KEY_SZ];
};

struct gap_bond_dev {			
	struct gap_ble_addr		addr;
	struct gap_key_params		key;	
};

struct gap_adv_params {
	uint8_t				type;	// \ref _ADV_CH_PKT_TYPE_
	struct gap_ble_addr	peer_addr;
	uint8_t               		policy;
	uint8_t				channel;
	uint16_t              		interval;  /**< Between 0x0020 and 0x4000 in 0.625 ms units (20ms to 10.24s) */
	uint16_t              		timeout;	 /**< Between 0x0001 and 0x3FFF in seconds, 0x0000 is disable */
};

struct gap_scan_params{
	uint8_t mode;		// \ref SCAN_TYPE
	uint8_t channel;
	uint16_t interval;
	uint16_t window;
	uint16_t timeout;
};

struct gap_scan_dev{
	uint8_t	adv_type;	// \ref _ADV_CH_PKT_TYPE_
	struct gap_ble_addr	peer_addr;	
};

struct gap_scan_report_evt{
	struct gap_scan_dev dev;
	uint8_t data_len;
	uint8_t adv_data[MAX_ADV_DATA_SZ];
	uint8_t rssi;
};

struct gap_scan_end_evt{
	uint8_t dev_cnt;
	struct gap_scan_dev *p_dev_list;
};

struct gap_update_params {
	uint16_t  updateitv_min;
	uint16_t  updateitv_max;
	uint16_t  updatelatency;
	uint16_t  updatesvto;
};

struct gap_disconnected_evt {
	uint8_t	reason;	// HCI error codes
};

struct gap_pairing_comp_evt{
	uint8_t status;	// \ref GAP_RET_STATUS
	uint8_t dir;		// \ref DIR_IN or DIR_OUT
	uint8_t reason;	// \ref SMP_FAILED_CODE
	struct gap_key_params enc_key;
};

struct gap_att_read_evt {
	uint16_t	primary;
	uint16_t	uuid;
	uint16_t	hdl;
	uint16_t	offset;
};

struct gap_att_write_evt {
	uint16_t	primary;
	uint16_t	uuid;
	uint16_t	hdl;
	uint8_t	sz;
	uint8_t	data[MAX_ATT_DATA_SZ];
};

struct gap_att_pre_write_evt {
	uint16_t	primary;
	uint16_t	uuid;
	uint16_t	hdl;
	uint16_t	offset;
	uint8_t	sz;
	uint8_t	data[MAX_ATT_DATA_SZ];
};

struct gap_att_exec_write_evt {
	uint8_t	flags;
};

struct gap_att_handle_configure_evt {
	uint16_t	uuid;
	uint16_t	hdl;
	uint16_t	value;
};

enum L2CAP_UPDATE_RSP_RES{
	CONN_PARAMS_ACCEPTED	= 0x0000,
	CONN_PARAMS_REJECTED		= 0x0001,	
	CONN_PARAM_SMART_TIMEROUT	= 0x0002,   //该类型的事件并不是标准的BLE事件，而是随着smart_update功能而添加的，不使用smart_update功能不会上报该事件
	CONN_PARAM_SMART_SUCCEED	= 0x0003,   //该类型的事件并不是标准的BLE事件，而是随着smart_update功能而添加的，不使用smart_update功能不会上报该事件
    CONN_PARAM_LATENCY_ENABLE	= 0x0004,   //该类型的事件并不是标准的BLE事件，而是随着smart_update功能而添加的，不使用smart_update功能不会上报该事件
	CONN_PARAM_LATENCY_DISABLE	= 0x0005,   //该类型的事件并不是标准的BLE事件，而是随着smart_update功能而添加的，不使用smart_update功能不会上报该事
};

struct gap_l2cap_update_rsp_evt{
	uint16_t result;	// \ref L2CAP_UPDATE_RSP_RES
};

struct gap_link_params {	
	uint16_t	interval;
	uint16_t	latency;
	uint16_t	svto;
};

struct gap_ble_evt {
	uint8_t	evt_type;	// \ref _EVT_TYPE_
	uint32_t	evt_code;	// \ref _GAP_EVT_
	union
	{
		struct gap_disconnected_evt 		disconn_evt;		// \ref GAP_EVT_DISCONNECTED
		struct gap_ble_addr				bond_dev_evt;	// \ref GAP_EVT_CONNECTED
		struct gap_pairing_comp_evt		pairing_comp_evt;	// \ref GAP_EVT_PAIRING_COMP
		struct gap_att_read_evt			att_read_evt;	// \ref GAP_EVT_ATT_READ
		struct gap_att_write_evt			att_write_evt;	// \ref GAP_EVT_ATT_WRITE
		struct gap_att_pre_write_evt		att_pre_write_evt;		// \ref GAP_EVT_ATT_PREPARE_WRITE
		struct gap_att_exec_write_evt		att_exec_write_evt;		// \ref GAP_EVT_ATT_EXECUTE_WRITE
		struct gap_att_handle_configure_evt	att_handle_config_evt;	// \ref GAP_EVT_ATT_HANDLE_CONFIGURE
		struct gap_l2cap_update_rsp_evt	l2cap_update_rsp_evt;	// \ref GAP_EVT_L2CAP_UPDATE_RSP
		struct gap_link_params 			conn_update_complete_evt;		// \ref GAP_EVT_CONN_UPDATE_COMP
		struct gap_scan_report_evt			scan_report_evt;				// \ref GAP_EVT_SCAN_REPORT
		struct gap_scan_end_evt			scan_end_evt;			// \ref GAP_EVT_SCAN_END
	} evt; 
};

struct gap_evt_callback {
	uint32_t	evt_mask;
	void 	(*p_callback)(struct gap_ble_evt *p_evt);
};

struct gap_att_report {
	uint16_t	primary;
	uint16_t	uuid;
	uint16_t	hdl;
	uint16_t	config;
	uint16_t	value;
};

struct gap_att_report_handle {
	uint8_t	cnt;
	struct	gap_att_report report[MAX_ATT_REPORT_HDL];
};

struct gap_wakeup_config {
	uint8_t wakeup_type;
	bool timer_wakeup_en;
	bool gpi_wakeup_en;
	bool wdt_wakeup_en;
	bool rtc_wakeup_en;
	bool capdet_wakeup_en;
	bool ana_wakeup_en;
	uint32_t gpi_wakeup_cfg;
};

struct smp_pairing_req{
	uint8_t io;
	uint8_t oob;
	uint8_t flags:2;
	uint8_t mitm:1;
	uint8_t rsvd:5;
	uint8_t max_enc_sz;
	uint8_t init_key;
	uint8_t rsp_key;
};


/* attc */

enum ATT_CMD_CODE {
	ATT_ERR_RSP					= 0x01,
	ATT_MTU_REQ					= 0x02,
	ATT_MTU_RSP					= 0x03,
	ATT_FIND_INFO_REQ				= 0x04,
	ATT_FIND_INFO_RSP				= 0x05,
	ATT_FIND_BY_TYPE_VALUE_REQ	= 0x06,
	ATT_FIND_BY_TYPE_VALUE_RSP	= 0x07,	
	ATT_READ_BY_TYPE_REQ			= 0x08,
	ATT_READ_BY_TYPE_RSP			= 0x09,
	ATT_READ_REQ					= 0x0A,
	ATT_READ_RSP					= 0x0B,
	ATT_READ_BLOB_REQ				= 0x0C,
	ATT_READ_BLOB_RSP				= 0x0D,
	ATT_READ_MULTIPLE_REQ			= 0x0E,
	ATT_READ_MULTIPLE_RSP			= 0x0F,
	ATT_READ_BY_GROUP_TYPE_REQ	= 0x10,
	ATT_READ_BY_GROUP_TYPE_RSP	= 0x11,
	ATT_WRITE_REQ					= 0x12,
	ATT_WRITE_RSP					= 0x13,
	ATT_WRITE_CMD					= 0x52,
	ATT_PREPARE_WRITE_REQ		= 0x16,
	ATT_PREPARE_WRITE_RSP			= 0x17,
	ATT_EXECUTE_WRITE_REQ		= 0x18,
	ATT_EXECUTE_WRITE_RSP			= 0x19,
	ATT_HANDLE_VAL_NOTIFICATION	= 0x1B,
	ATT_HANDLE_VAL_INDICATION	= 0x1D,
	ATT_HANDLE_VAL_CONFIRMATION	= 0x1E,
	ATT_SIGNED_WRITE_CMD			= 0xD2,
};

enum ATT_ERROR_CODE {
	ATT_INVALID_HANDLE			= 0x01,
	ATT_READ_NOT_PEMITTED			= 0x02,
	ATT_WRITE_NOT_PEMITTED		= 0x03,
	ATT_INVALID_PDU				= 0x04,
	ATT_INSUFFICIENT_AUTHEN		= 0x05,
	ATT_REQ_NOT_SUPPORTED		= 0x06,
	ATT_INVALID_OFFSET				= 0x07,
	ATT_INSUFFICIENT_AUTHOR		= 0x08,
	ATT_PREPARE_QUEUE_FULL		= 0x09,
	ATT_ATTRIBUTE_NOT_FOUND		= 0x0A,
	ATT_ATTRIBUTE_NOT_LONG		= 0x0B,
	ATT_INSUFFICIENT_ENC_KEY_SZ	= 0x0C,
	ATT_INVALID_ATTRIBUTE_VAL_LEN= 0x0D,
	ATT_UNLIKELY_ERROR			= 0x0E,
	ATT_INSUFFICIENT_ENC			= 0x0F,
	ATT_UNSUPPORTED_GROUP_TYPE	= 0x10,
	ATT_INSUFFICIENT_RESOURCES	= 0x11,
};

enum ATT_CHAR_PROPERTY {
	ATT_CHAR_BROADCAST			= 0x01,
	ATT_CHAR_READ					= 0x02,
	ATT_CHAR_WEIRE_WO_RSP		= 0x04,
	ATT_CHAR_WEIRE				= 0x08,
	ATT_CHAR_NOTIFY				= 0x10,
	ATT_CHAR_INDICATE				= 0x20,
	ATT_CHAR_AUTH_SIGNED_WRITE	= 0x40,
	ATT_CHAR_EXTEND_PROPERTY 	= 0x80,	
};

struct att_err_rsp{
	uint8_t opcode;	// \ref ATT_CMD_CODE
	uint16_t hdl;
	uint8_t err;	// \ref ATT_ERROR_CODE
};

struct att_mtu_req{
	uint16_t mtu;
};

struct att_mtu_rsp{
	uint16_t mtu;
};

struct att_find_info_req{
	uint16_t start_hdl;
	uint16_t end_hdl;
};

struct att_find_info_16{
	uint16_t hdl;
	uint8_t uuid[2];
};

struct att_find_info_128{
	uint16_t hdl;
	uint8_t uuid[16];
};

union  att_find_info_payload {
	struct att_find_info_16   uuid16[5];
	struct att_find_info_128 uuid128;
};

struct att_find_info_rsp{
	uint8_t format;
	union att_find_info_payload pair;
};

enum _GATT_FIND_INFO_UUID_TYPE_{
	GATT_FIND_INFO_UUID_16 	= 0x01,
	GATT_FIND_INFO_UUID_128 	= 0x02,
};

struct att_find_by_type_val_req{
	uint16_t start_hdl;
	uint16_t end_hdl;
	uint16_t att_type;
	uint8_t att_val[MAX_ATT_DATA_SZ-7];
};

struct att_find_by_type_val_rsp{
	uint8_t list[MAX_ATT_DATA_SZ-1];
};

struct att_read_by_type_req{
	uint16_t start_hdl;
	uint16_t end_hdl;
	uint8_t att_type[16];
};


struct att_read_by_type_service_16{
	uint16_t hdl;
	uint8_t uuid[2];
};

struct att_read_by_type_service_128{
	uint16_t hdl;
	uint8_t uuid[16];
};

union  att_read_by_type_service_payload {
	struct att_read_by_type_service_16   uuid16[3];
	struct att_read_by_type_service_128 uuid128;
};

struct att_read_by_type_service_rsp{
	uint8_t length;
	union att_read_by_type_service_payload pair;
};

struct att_read_by_type_16{
	uint16_t hdl;
	uint8_t property;
	uint16_t val_hdl;
	uint8_t char_uuid[2];
};

struct att_read_by_type_128{
	uint16_t hdl;
	uint8_t property;
	uint16_t val_hdl;
	uint8_t char_uuid[16];
};

union  att_read_by_type_payload {
	struct att_read_by_type_16   uuid16[3];
	struct att_read_by_type_128 uuid128;
};

struct att_read_by_type_rsp{
	uint8_t length;
	union att_read_by_type_payload pair;
};

struct att_read_by_type_pair_val{
	uint16_t hdl;
	uint8_t val[10];
};

struct att_read_by_type_val_rsp{
	uint8_t length;
	struct att_read_by_type_pair_val pair[1];
};

struct att_read_by_type_chartextend_rsp{
	uint8_t length;
	uint16_t hdl;
	uint8_t val[MAX_ATT_DATA_SZ-4];
};

struct att_read_by_type_include_rsp{
	uint8_t length;
	uint16_t hdl;
	uint8_t buf[MAX_ATT_DATA_SZ-2];
};

struct att_read_req{
	uint16_t hdl;
};

struct att_read_rsp{
	uint8_t buf[MAX_ATT_DATA_SZ-1];
};

struct att_read_blob_req{
	uint16_t hdl;
	uint16_t offset;
};

struct att_read_blob_rsp{
	uint8_t buf[MAX_ATT_DATA_SZ-1];
};

struct att_read_multiple_req{
	uint16_t hdl[MAX_ATT_DATA_SZ-1];
};

struct att_read_multiple_rsp{
	uint8_t val[MAX_ATT_DATA_SZ-1];
};

struct att_read_by_group_type_req{
	uint16_t start_hdl;
	uint16_t end_hdl;
	uint8_t att_group_type[16];
};

struct att_read_by_group_type_16{
	uint16_t hdl;
	uint16_t end_hdl;
	uint8_t uuid[2];
};

struct att_read_by_group_type_128{
	uint16_t hdl;
	uint16_t end_hdl;
	uint8_t uuid[16];
};

union  att_read_by_group_type_payload {
	struct att_read_by_group_type_16   uuid16[3];
	struct att_read_by_group_type_128 uuid128;
};

struct att_read_by_group_type_rsp{
	uint8_t length;
	union  att_read_by_group_type_payload pair;
};

struct att_write_req{
	uint16_t hdl;
	uint8_t buf[MAX_ATT_DATA_SZ-3];
};

struct att_write_cmd{
	uint16_t hdl;
	uint8_t buf[MAX_ATT_DATA_SZ-3];
};

struct att_prepare_write_req{
	uint16_t hdl;
	uint16_t offset;
	uint8_t buf[MAX_ATT_DATA_SZ-5];
};

struct att_prepare_write_rsp{
	uint16_t hdl;
	uint16_t offset;
	uint8_t buf[MAX_ATT_DATA_SZ-5];
};

struct att_execute_write_req{
	uint8_t flags;
};

struct att_hdl_val_notifivation{
	uint16_t hdl;
	uint8_t buf[MAX_ATT_DATA_SZ-3];
};

struct att_hdl_val_indication{
	uint16_t hdl;
	uint8_t buf[MAX_ATT_DATA_SZ-3];
};

struct attc_ble_evt {
	uint8_t	attc_code;	// \ref ATT_CMD_CODE
	uint8_t	attc_sz;
	union
	{
		struct att_err_rsp AttErrRsp;
		struct att_mtu_rsp AttMtuRsp;
		struct att_find_info_rsp AttFindInfoRsp;
		struct att_find_by_type_val_rsp AttFindByTypeValRsp;
		struct att_read_by_type_rsp AttReadByTypeRsp;
		struct att_read_by_type_include_rsp AttReadByTypeIncludeRsp;
		struct att_read_by_type_val_rsp AttReadByTypeValRsp;
		struct att_read_by_type_service_rsp AttReadByTypeServiceRsp;
		struct att_read_by_type_chartextend_rsp AttReadByTypeChartExtendRsp;
		struct att_read_rsp AttReadRsp;
		struct att_read_blob_rsp AttReadBlobRsp;
		struct att_read_multiple_rsp AttReadMultipleRsp;
		struct att_read_by_group_type_rsp AttReadByGroupTypeRsp;
		struct att_hdl_val_notifivation AttHdlValNotification;
		struct att_hdl_val_indication AttHdlValIndication;
	} attc; 
};

typedef void (*p_attc_callback)(struct attc_ble_evt *p_evt);

/* attc end*/

#define CONFIRMATION_EVT_NUM		10
#define MAX_UPDATE_ADJ_NUM		4

enum GAP_SMART_UPDATE_DIRECTION {
	UPDATE_DIRECTION_UP	= 0x01,
	UPDATE_DIRECTION_DOWN	= 0x01,
};
enum GAP_SMART_UPDATE_STATE {
	UPDATE_STATE_LATENCY	= 0x80,
	UPDATE_STATE_TIMEROUT	= 0x40,
	UPDATE_STATE_ADJFINISH	= 0x20,
	UPDATE_STATE_WAITANCHOR	= 0x10,
	UPDATE_STATE_START	= 0x08,
	UPDATE_REQ_END	= 0x04,
	UPDATE_LATENCY_STATE	= 0x02,
	UPDATE_STATE_CHANGE	= 0x01,
};
enum GAP_SMART_CONTROL_SET {
	SMART_CONTROL_LATENCY	= 0x80,
	SMART_CONTROL_UPDATE	= 0x40,
};
struct gap_smart_update_params {
	uint8_t 	updatectrl;
	uint8_t 	updateadj_num;
	uint16_t  updateitv_target;
	uint16_t  updatelatency;
	uint16_t  updatesvto;
};
struct GAP_smart_update_ctrol {
	uint8_t	update_state;  
	uint8_t	update_direction;
	uint8_t updateadj_cnt;
	uint16_t loop_num;
	uint16_t updateitv_step;
	struct gap_smart_update_params update_params;
};

#pragma pack()

#endif

#ifdef _BLE_LIB_C
#else
	/* ble protocol */
	extern uint8_t BleInit(void);
	extern uint8_t DisConnect(void);
	
	extern uint8_t SetDevAddr(struct gap_ble_addr* p_dev_addr);	
	extern uint8_t GetDevAddr(struct gap_ble_addr* p_dev_addr);
	extern uint8_t SetLEFeature(uint8_t *p_feature);	
	extern uint8_t SetAdvParams(struct gap_adv_params *p_adv_params);
	extern uint8_t SetAdvData(uint8_t *p_adv, uint8_t adv_sz, uint8_t *p_scan, uint8_t sacn_sz);	
	extern uint8_t StartAdv(void);
	extern uint8_t StopAdv(void);
	
	extern uint8_t SetScanParams(struct gap_scan_params *p_scan_params);
	extern uint8_t StartScan(void);
	extern uint8_t StopScan(void);
	
	extern uint8_t SetSecParams(struct smp_pairing_req *p_sec_params);
	extern uint8_t SetPasskey(uint32_t passkey);	
	extern uint8_t SecurityReq(uint8_t flag, uint8_t mitm);
	
	extern uint8_t SetConnectionUpdate(struct gap_update_params *p_update_params);	
	extern uint8_t GetLinkParameters(struct gap_link_params* p_link);
	extern uint8_t SetWinWideMinusCnt(uint8_t cnt);
	extern uint8_t GAPConnectionLatencyMode(uint8_t en);	
	extern uint8_t SetEvtCallback(struct gap_evt_callback* p_callback);	
	
	extern uint8_t GetGATTReportHandle(struct gap_att_report_handle** p_hdl);
	extern uint8_t SetGATTReadRsp(uint8_t len,uint8_t *p_data);
	extern uint8_t CheckFIFOFull(void);
	extern uint8_t GATTDataSend(uint8_t type, struct gap_att_report* p_report, uint8_t len, uint8_t *p_data);

	extern uint8_t Rand(void);
	extern void DelayUS(uint16_t dly);
	extern void DelayMS(uint32_t dly);
	extern uint8_t GetCompanyID(void);
	extern uint8_t GetQFNType(void);
	extern void RFRead(uint8_t addr, uint8_t * data);
	extern void RFWrite(uint8_t addr, uint8_t data);

	extern void ble_sched_execute(void);
	extern bool ble_sched_finish(void);


	/* system clock */
	extern uint8_t LPOCalibration(void);
	extern uint8_t RCOSCCalibration(void);
	extern uint8_t MCUClockSwitch(uint8_t sel);
	extern uint8_t ClockSwitch(uint8_t sel);
	extern uint8_t GetMCUClock(uint8_t *p_sel);
	extern uint8_t GetClock(uint8_t *p_sel);

	/* timer */
	extern uint8_t TimerStart(uint16_t type, uint32_t timecnt_100ms, bool reload, sys_timer_cb pfnCallback);
	extern void TimerStop(uint16_t type);

	/* sleep & power down */
	extern uint8_t WakeupConfig(struct gap_wakeup_config *p_cfg);
	extern uint8_t LLSleep(void);
	extern uint8_t SystemSleep(void);
	extern uint8_t SystemPowerDown(void);
	extern uint8_t SystemReset(void);
	extern uint8_t RFSleep(void);
	extern uint8_t RFWakeup(void);
	extern uint8_t UartEn(uint8_t en);

	/* bond Manager */
	extern uint8_t SetBondManagerIndex(uint8_t idx);
	extern uint8_t GetBondDevice(struct gap_bond_dev *p_device);
	extern uint8_t AddBondDevice(struct gap_bond_dev *p_device);	
	extern uint8_t DelBondDevice(void);	
	extern uint8_t DelAllBondDevice(void);

	/* read&write flash */
	extern uint8_t ReadProfileData(uint16_t addr , uint16_t len, uint8_t *p_buf);
	extern uint8_t WriteProfileData(uint16_t addr , uint16_t len, uint8_t *p_buf);

	extern uint8_t EraseFlashData(uint32_t addr, uint8_t sector_num);
	extern uint8_t ReadFlashData(uint32_t addr, uint16_t len, uint8_t *p_buf);
	extern uint8_t WriteFlashData(uint32_t addr, uint16_t len, uint8_t *p_buf);

	/* fw upgrade */
	extern uint8_t CodeErase(void);
	extern uint8_t CodeWrite(uint32_t offset , uint32_t len, uint8_t *p_buf);
	extern uint8_t CodeUpdate(uint8_t *p_desc, uint8_t *p_ver, uint32_t sz, uint16_t checksum);
	/* att client */
	extern uint8_t ATTCSetCallback(p_attc_callback pfn_callback);
	extern uint8_t ATTCMTUReq(uint16_t mtu);
	extern uint8_t ATTCFindInfoReq(uint16_t start_hdl, uint16_t end_hdl);
	extern uint8_t ATTCFindByTypeValueReq(uint16_t start_hdl, uint16_t end_hdl, uint16_t type, uint8_t val_sz, uint8_t *p_val);
	extern uint8_t ATTCReadByTypeReq(uint16_t start_hdl, uint16_t end_hdl, uint16_t type_sz, uint8_t *p_type);
	extern uint8_t ATTCReadReq(uint16_t hdl);
	extern uint8_t ATTCReadBlobReq(uint16_t hdl, uint16_t offset);
	extern uint8_t ATTCReadMultipleReq(uint8_t hdl_sz, uint8_t *p_hdl);
	extern uint8_t ATTCReadByGroupTypeReq(uint16_t start_hdl, uint16_t end_hdl, uint16_t type_sz, uint8_t *p_type);
	extern uint8_t ATTCWriteReq(uint16_t hdl, uint16_t sz, uint8_t *p_buf);
	extern uint8_t ATTCWriteCmdReq(uint16_t hdl, uint16_t sz, uint8_t *p_buf);
	extern uint8_t ATTCPrepareWriteReq(uint16_t hdl, uint16_t offset, uint16_t sz, uint8_t *p_buf);
	extern uint8_t ATTCExecuteWriteReq(uint8_t flags);
	extern uint8_t ATTCConfirmation(void);

	extern void GPADC_Manual_Calibration(uint8_t trim);
	
	extern void BBRFWrite(uint8_t addr, uint8_t data);
	extern void BBRFRead(uint8_t addr, uint8_t* data);
	
	extern uint8_t APPtimer_enable(uint8_t id, uint32_t intv, void *  p_callback);
	extern uint8_t APPtimer_disable(uint8_t id);
	
	extern void GAPBBDelayUS(uint16_t us);
	extern void GAPBBDelayMS(uint32_t us);
	extern uint8_t Setting4kUpdate(uint8_t *data,  uint32_t checksum,  uint8_t Xor);
	
	extern uint8_t gap_s_smart_update_latency(struct gap_smart_update_params *p_smart_params);
	
	extern bool GAPGetRFAutoSleep(void);
	extern void GAPSetRFAutoSleep(bool en);
	extern bool GAPGetUartEn(void);
	extern void GAPUartEn(bool en);
	
	extern uint8_t Setting4kUpdate(uint8_t *data,  uint32_t checksum,  uint8_t Xor);
	extern void SetDevAddr_toflash(struct gap_ble_addr* p_dev);
#endif

#endif


