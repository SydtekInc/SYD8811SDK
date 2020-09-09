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


#define  EVT_NUM  ((uint8_t) 0x03)//��ǰ��ʱ���¼���

#define  EVT_2S   ((uint32_t)    0x00000100)//��ʱ��2s�¼�
#define  EVT_1S_OTA   ((uint32_t)    0x00000200)//��ʱ��2s�¼�
#define  EVT_20MS   ((uint32_t)    0x00000400)//��ʱ��2s�¼�










#define  RTCEVT_NUM  ((uint8_t) 0x01)//��ǰ��ʱ���¼���

#define  RTCEVT_10S  ((uint32_t)  0x00000001)//��ʱ��1s�¼�
/*�����Ӷ�ʱ���¼�����Ϊ������¼�׷�����ʱ��ĵȳ����������ֻ��л���Ҫһ�����ӵĶ�ʱ����ÿ��60���ʱ����Ҫһ����ʱ���¼���
����60��,120�룬180��ȣ��ſ���������������������*/
//#define  RTCEVT_whole_minute  ((uint32_t)  0x00000002)
#define  RTCEVT_185S  ((uint32_t) 0x0000004)//��ʱ��185s�¼�

extern void BLSetConnectionUpdate(uint8_t target);

#endif

