/*
��ʱ�������ļ�

���ߣ�����ʢԴ��Ƽ����޹�˾
���ڣ�2016/7/8
*/
#include "syd8801_timer.h"
#include "syd8801_delay.h"

//��ʱ���Ĵ�������
TIMER_CTRL_TYPE * TIMER_CTRL = ((TIMER_CTRL_TYPE *) TIMER_CTRL_BASE);

//��ʱ���ص��������� timer0�Ļص�������timer0_callback[0]
static void (*timer0_callback[3])(void);

/*
��ʱ��0 ���ú���
����: uint32_t interval  intervalҪ�����Ĵ���  ��ʱ��0�ǵݼ������� ���������interval���Ǽ��������������
			void *  p_callback   ��ʱ���жϵĻص�����
			timer_0_enable(0x20, timer0_callback); // 32 * 31.25 us = 1ms
*/
void timer_0_enable(uint32_t interval, void *  p_callback)
{
	if(TIMER_CTRL->TIMER_0_EN== 1)
		TIMER_CTRL->TIMER_0_EN = 0;	
  delay_us(100);   //��΢��ʱ ʹ��ʱ�������ɹ�
	
	TIMER_CTRL->TIMER_0_VAL= interval;

	timer0_callback[0] = ((void (*)(void))p_callback);

	TIMER_CTRL->TIMER_0_RGLR= 1;
	
	TIMER_CTRL->TIMER_0_EN = 1;

	NVIC_EnableIRQ(TIMER0_IRQn);
}
/*
��ʱ��0 ʧ�ܺ���  �رն�ʱ��0���ж�
*/
void timer_0_disable(void)
{
	TIMER_CTRL->TIMER_0_EN = 0;

	NVIC_DisableIRQ(TIMER0_IRQn);
}
/*
��ʱ��0 ��ʱ cnt��32us��������λΪ��32us  ����ʱ cnt*32 us
������uint32_t cnt ΢����
*/
void timer_0_delay_32us(uint32_t cnt)
{
	TIMER_CTRL->TIMER_0_VAL= cnt;

	TIMER_CTRL->TIMER_0_INT_CLR = 1; 

	TIMER_CTRL->TIMER_0_RGLR= 1;
	
	TIMER_CTRL->TIMER_0_EN = 1;

	while(TIMER_CTRL->TIMER_0_INT_STATUS==0);

	TIMER_CTRL->TIMER_0_EN = 0;

	TIMER_CTRL->TIMER_0_INT_CLR = 1; 
}
/*
��ʱ��0 �жϷ�����  ��������˻ص�����
*/
void TIMER0_IRQHandler(void)
{		 
	if(TIMER_CTRL->TIMER_0_INT_STATUS == 1)
	{
		TIMER_CTRL->TIMER_0_INT_CLR = 1; 

		if(timer0_callback[0] != 0)
			(*timer0_callback[0])();
	} 
}
/*
��ʱ��1 ���ú���
����: uint32_t interval  intervalҪ�����Ĵ���  ��ʱ��1�ǵݼ������� ���������interval���Ǽ��������������
			void *  p_callback   ��ʱ���жϵĻص�����
			timer_1_enable(0x20, timer0_callback); // 32 * 31.25 us = 1ms
*/
void timer_1_enable(uint32_t interval, void *  p_callback)
{
	if(TIMER_CTRL->TIMER_1_EN== 1)
		TIMER_CTRL->TIMER_1_EN = 0;	
	
	delay_us(100);   //��΢��ʱ ʹ��ʱ�������ɹ�
	
	TIMER_CTRL->TIMER_1_VAL= interval;

	timer0_callback[1] = ((void (*)(void))p_callback);

	TIMER_CTRL->TIMER_1_RGLR= 1;
	
	TIMER_CTRL->TIMER_1_EN = 1;

	NVIC_EnableIRQ(TIMER1_IRQn);
}
/*
��ʱ��1 ʧ�ܺ���  �رն�ʱ��0���ж�
*/
void timer_1_disable(void)
{
	TIMER_CTRL->TIMER_1_EN = 0;

	NVIC_DisableIRQ(TIMER1_IRQn);
}
/*
��ʱ��1 �жϷ�����  ��������˻ص�����
*/
void TIMER1_IRQHandler(void)
{		 
	if(TIMER_CTRL->TIMER_1_INT_STATUS == 1)
	{
		TIMER_CTRL->TIMER_1_INT_CLR = 1; 

		if(timer0_callback[1] != 0)
			(*timer0_callback[1])();
	}  
}
/*
��ʱ��2 ���ú���
����: uint32_t interval  intervalҪ�����Ĵ���  ��ʱ��2�ǵݼ������� ���������interval���Ǽ��������������
			void *  p_callback   ��ʱ���жϵĻص�����
			timer_2_enable(0x20, timer0_callback); // 32 * 31.25 us = 1ms
*/
void timer_2_enable(uint32_t interval, void *  p_callback)
{
	if(TIMER_CTRL->TIMER_2_EN== 1)
		TIMER_CTRL->TIMER_2_EN = 0;
	
	delay_us(100);   //��΢��ʱ ʹ��ʱ�������ɹ�
	
	TIMER_CTRL->TIMER_2_VAL= interval;

	timer0_callback[2] = ((void (*)(void))p_callback);

	TIMER_CTRL->TIMER_2_RGLR= 1;
	
	TIMER_CTRL->TIMER_2_EN = 1;

	NVIC_EnableIRQ(TIMER2_IRQn);
}
/*
��ʱ��2 ʧ�ܺ���  �رն�ʱ��0���ж�
*/
void timer_2_disable(void)
{
	TIMER_CTRL->TIMER_2_EN = 0;

	NVIC_DisableIRQ(TIMER2_IRQn);
}
/*
��ʱ��2 �жϷ�����  ��������˻ص�����
*/
void TIMER2_IRQHandler(void)
{		 
	if(TIMER_CTRL->TIMER_2_INT_STATUS == 1)
	{
		TIMER_CTRL->TIMER_2_INT_CLR = 1; 

		if(timer0_callback[2] != 0)
			(*timer0_callback[2])();
	}  
}

