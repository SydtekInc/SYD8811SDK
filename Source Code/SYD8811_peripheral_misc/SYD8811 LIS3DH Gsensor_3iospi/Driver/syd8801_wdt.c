/*
���Ź������ļ�

���ߣ�����ʢԴ��Ƽ����޹�˾
���ڣ�2016/7/8
*/
#include "syd8801_wdt.h"

WDT_CTRL_TYPE * WDT_CTRL = ((WDT_CTRL_TYPE *) WDT_BASE);
/*
���Ź���ʼ������
����: uint16_t count ���Ź���������ʼֵ �������ǵݼ������� ��λ��1/32.768ms
*/
void wdt_enable(uint16_t count)
{
	WDT_CTRL->WDT_TIME = count;
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
ʧ�ܿ��Ź�  ���Ź������ܹ���λϵͳ
*/
void wdt_disable()
{
	WDT_CTRL->WDT_EN = 0;
}

