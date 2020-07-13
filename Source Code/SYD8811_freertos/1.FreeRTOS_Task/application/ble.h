#ifndef _BLE_H_
#define _BLE_H_

#include "ARMCM0.h"


/*
enum _MAC_INT_ST_{
	MAC_TX_INT			= 0x01,
	MAC_RX_INT			= 0x02,
	MAC_ADVEND_INT		= 0x04,
	MAC_CONNSET_INT		= 0x08,
	MAC_CONNLOST_INT		= 0x10,
	MAC_CONNEVTEND_INT	= 0x20,
	MAC_SLEEP_INT			= 0x40,
	MAC_WAKEUP_INT		= 0x80,

};
*/
enum _BLE_EVT_TYPE_{
	BLE_ADV_END                 = 0x01,
	BLE_CONNECTED               = 0x02,
	BLE_DISCONNECTED            = 0x04,
	BLE_PASSKEY_REQ             = 0x08,
	BLE_SHOW_PASSKEY_REQ        = 0x10,
};

typedef enum {
    SENSOR_HEARTRATE        = 0x01,
    SENSOR_PEDOMETER        = 0x02,
    SENSOR_ALL              = 0xFF,
}SENSOR_DATA_TYPE;

#if 0
enum _BLE_ADDRESS_TYPE_{
	PUBLIC_ADDRESS_TYPE		= 0x00,
	RANDOM_ADDRESS_TYPE 	= 0x01,
};


enum _ADV_CH_PKT_TYPE_{
	ADV_IND 		= 0x00,
	ADV_DIRECT_IND 	= 0x01,
	ADV_NOCONN_IND	= 0x02,
	SCAN_REQ		= 0x03,
	SCAN_RSP		= 0x04,
	CONNECT_REQ		= 0x05,
	ADV_SCAN_IND	= 0x06,
};
#endif

struct queue_att_write_data {
	uint16_t uuid;
	uint8_t	sz;
	uint8_t	data[20];
};


extern void ble_init(void);
extern void ble_task(void);
extern uint8_t BLE_SendData(uint8_t *buf, uint8_t len);
extern void BLSetConnectionUpdate(uint8_t target);

#endif

