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

#define KEY_INT_PIN GPIO_6

#define _USE_SYD_CAPDET_TOUCH_
#ifdef _USE_SYD_CAPDET_TOUCH_
//#define _SYD_CAPDET_TOUCH_SENSITIVE_
#define _USE_SYD_CAPDET_AUTO_CALIBRATION_
#define _USE_SYD_CAPDET_POWERON_AWAYS_TOUCH_CALIBRATION_
#endif

//#define SYD_TOUCH_DEBUG


#define  EVT_NUM  ((uint8_t) 0x03)//当前定时器事件数

#define  EVT_2S   ((uint32_t)    0x00000100)//定时器2s事件
#define  EVT_1S_OTA   ((uint32_t)    0x00000200)//定时器2s事件
#define  EVT_20MS   ((uint32_t)    0x00000400)//定时器2s事件










#define  RTCEVT_NUM  ((uint8_t) 0x01)//当前定时器事件数

#define  RTCEVT_10S  ((uint32_t)  0x00000001)//定时器1s事件
/*整分钟定时器事件，因为其余的事件追求的是时间的等长，但是在手环中还需要一个分钟的定时器，每次60秒的时候需要一个定时器事件，
比如60秒,120秒，180秒等，概况起来就是整（正）分钟*/
//#define  RTCEVT_whole_minute  ((uint32_t)  0x00000002)
#define  RTCEVT_185S  ((uint32_t) 0x0000004)//定时器185s事件

extern void BLSetConnectionUpdate(uint8_t target);

#endif

