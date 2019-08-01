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

#define _GPIO_LED_CONTROL_   //����״ָ̬ʾ���Ƿ�򿪵ĺ꣬ע�ͱ���SYD8811������������״̬�ܽ�

#define	GPIO_LED_CONNECT	GPIO_9    //��������״ָ̬ʾ�ƣ�0����ǰ�������ڶ���״̬ 1����ǰ������������״̬
#define	GPIO_LED_NOTIFYEN	GPIO_8    //����notify���ص�״ָ̬ʾ�ƣ�0����ǰδʹ��notify 1����ǰʹ����notify
#define	GPIO_LED_WRITEING	GPIO_7    //����������д������״ָ̬ʾ�ƣ�APP��SYD8811����һ��д������SYD8811����ת�ùܽ�һ��
#define	GPIO_LED_READING	GPIO_6    //���������˶�������״ָ̬ʾ�ƣ�APP��SYD8811����һ�ζ�������SYD8811����ת�ùܽ�һ��

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

#define  EVT_NUM  ((uint8_t) 0x02)//��ǰ��ʱ���¼���

#define  EVT_2S   ((uint32_t)    0x00000100)//��ʱ��2s�¼�
#define  EVT_1S_OTA   ((uint32_t)    0x00000200)//��ʱ��2s�¼�

#define  RTCEVT_NUM  ((uint8_t) 0x01)//��ǰ��ʱ���¼���

//#define  RTCEVT_10S  ((uint32_t)  0x00000001)//��ʱ��1s�¼�
/*�����Ӷ�ʱ���¼�����Ϊ������¼�׷�����ʱ��ĵȳ����������ֻ��л���Ҫһ�����ӵĶ�ʱ����ÿ��60���ʱ����Ҫһ����ʱ���¼���
����60��,120�룬180��ȣ��ſ���������������������*/
//#define  RTCEVT_whole_minute  ((uint32_t)  0x00000002)
#define  RTCEVT_185S  ((uint32_t) 0x0000004)//��ʱ��185s�¼�

extern void BLSetConnectionUpdate(uint8_t target);

#endif

