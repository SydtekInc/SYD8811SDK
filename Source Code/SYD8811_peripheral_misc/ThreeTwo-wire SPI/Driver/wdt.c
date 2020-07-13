/*
���Ź������ļ�

���ߣ�����ʢԴ��Ƽ����޹�˾
���ڣ�2016/7/8
*/
#include "wdt.h"

WDT_CTRL_TYPE * WDT_CTRL = ((WDT_CTRL_TYPE *) WDT_BASE);
/*
���Ź���ʼ������
����: uint16_t count ���Ź���������ʼֵ �������ǵݼ������� ��λ��256/32.768 = 7.8ms
*/
void wdt_enable(uint16_t count)
{
	//dbg_printf("WDT_CTRL = 0x%08x\r\n", *(uint32_t *)WDT_CTRL);

	WDT_CTRL->WDT_CLR = 1;			/*�����*/
	WDT_CTRL->WDT_TIME = count;		/*timeԽ�̣�Խ���ײ��Ե�����*/
	WDT_CTRL->WDT_EN = 1;
}

/*
������Ź����� 
���ｫ��Ѽ�������ֵ���ûس�ʼֵ
*/
void wdt_clear()
{
	WDT_CTRL->WDT_CLR=1;
}

/*
���ÿ��Ź�
*/
void wdt_disable()
{
	WDT_CTRL->WDT_EN = 0;
}

