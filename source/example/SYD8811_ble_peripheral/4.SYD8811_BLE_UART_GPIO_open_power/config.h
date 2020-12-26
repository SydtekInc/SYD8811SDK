#ifndef _CONFIG_H_
#define _CONFIG_H_ 

#include "ARMCM0.h"
#include "lib.h"

#define _SYD_RTT_DEBUG_

#define USER_32K_CLOCK_RCOSC

#define Device_Name 'S','Y','D','_','U','A','R','T',
#define Device_Name_Len 8

#define	MAX_RX_LENGTH	1024
#define	MAX_TX_LENGTH	50

#define	GPIO_UART_TX	GPIO_16
#define	GPIO_UART_RX	GPIO_15

#define GPIO_WAKEUP_BIT		BIT21
#define GPIO_WAKEUP_PIN		GPIO_21

#define _GPIO_LED_CONTROL_   //蓝牙状态指示灯是否打开的宏，注释本行SYD8811将不控制蓝牙状态管脚

#define	GPIO_LED_CONNECT	GPIO_9    //蓝牙连接状态指示灯，0：当前蓝牙处于断线状态 1：当前蓝牙处于连接状态
#define	GPIO_LED_NOTIFYEN	GPIO_8    //蓝牙notify开关的状态指示灯，0：当前未使能notify 1：当前使能了notify
#define	GPIO_LED_WRITEING	GPIO_7    //蓝牙发生了写操作的状态指示灯，APP对SYD8811进行一次写操作，SYD8811将翻转该管脚一次
#define	GPIO_LED_READING	GPIO_6    //蓝牙发生了读操作的状态指示灯，APP对SYD8811进行一次读操作，SYD8811将翻转该管脚一次

typedef struct{
	uint8_t data[MAX_RX_LENGTH];
	uint32_t header,tail;
} Uart_Rx_Buf_t;

typedef struct{
	uint8_t  data[MAX_TX_LENGTH][MAX_ATT_DATA_SZ];
	uint32_t header,tail;
} Uart_Tx_Buf_t;

extern Uart_Rx_Buf_t uart_rx_buf;
extern Uart_Tx_Buf_t uart_tx_buf;

#define  EVT_NUM  ((uint8_t) 0x02)//当前定时器事件数

#define  EVT_2S   ((uint32_t)    0x00000100)//定时器2s事件
#define  EVT_1S_OTA   ((uint32_t)    0x00000200)//定时器2s事件

#define  RTCEVT_NUM  ((uint8_t) 0x01)//当前定时器事件数

//#define  RTCEVT_10S  ((uint32_t)  0x00000001)//定时器1s事件
/*整分钟定时器事件，因为其余的事件追求的是时间的等长，但是在手环中还需要一个分钟的定时器，每次60秒的时候需要一个定时器事件，
比如60秒,120秒，180秒等，概况起来就是整（正）分钟*/
//#define  RTCEVT_whole_minute  ((uint32_t)  0x00000002)
#define  RTCEVT_185S  ((uint32_t) 0x0000004)//定时器185s事件

extern void BLSetConnectionUpdate(uint8_t target);

#endif

