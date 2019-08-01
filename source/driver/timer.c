#include "timer.h"
#include "delay.h"

TIMER_CTRL_TYPE * TIMER_CTRL = ((TIMER_CTRL_TYPE *) TIMER_CTRL_BASE);

#ifndef _SOFT_TIMER_

//��ʱ���ص��������� timer_x�Ļص�������timer_callback[x]
static void (*timer_callback[3])(void);
/*
��ʱ��0 ���ú���
����: 
	uint32_t interval  ��ʱ���ǵݼ������� interval���Ǽ�������ֵ
	void *  p_callback ��ʱ���жϵĻص�����
	��ʱ��ʱ��: 32.768KHz
*/
void timer_0_enable(uint32_t interval, void *  p_callback)
{
	if(TIMER_CTRL->TIMER_0_EN== 1)
	{
		TIMER_CTRL->TIMER_0_EN = 0;	
  		delay_us(50);   //��΢��ʱ ʹ��ʱ�������ɹ�
	}

	TIMER_CTRL->TIMER_0_VAL = interval;
	TIMER_CTRL->TIMER_0_RGLR = 1;		//1:reload enable
	TIMER_CTRL->TIMER_0_INT_MASK = 0;	//1:mask int
	timer_callback[0] = ((void (*)(void))p_callback);

	TIMER_CTRL->TIMER_0_INT_CLR = 1; 
	NVIC_EnableIRQ(TIMER0_IRQn);
	
	TIMER_CTRL->TIMER_0_EN = 1;	
}

uint32_t timer_0_get_val(void)
{
	return TIMER_CTRL->TIMER_0_CNT;
}

/*
��ʱ��0 ʧ�ܺ���  �رն�ʱ��0���ж�
*/
void timer_0_disable(void)
{
	TIMER_CTRL->TIMER_0_EN = 0;
	NVIC_DisableIRQ(TIMER0_IRQn);
	TIMER_CTRL->TIMER_0_INT_CLR = 1;
}
/*
��ʱ��0 ��ʱ cnt��32us��������λΪ��32us  ����ʱ cnt*32 us
������uint32_t cnt ΢����
*/
void timer_0_delay_32us(uint32_t cnt)
{
	TIMER_CTRL->TIMER_0_VAL= cnt;
	TIMER_CTRL->TIMER_0_INT_MASK = 1;
	TIMER_CTRL->TIMER_0_INT_CLR = 1; 

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

		if(timer_callback[0] != 0)
			(*timer_callback[0])();
	} 
}

/*
��ʱ��1 ���ú���
����: 
	uint32_t interval  ��ʱ���ǵݼ������� interval���Ǽ�������ֵ
	void *  p_callback ��ʱ���жϵĻص�����
	��ʱ��ʱ��: 32.768KHz
*/
void timer_1_enable(uint32_t interval, void *  p_callback)
{
	if(TIMER_CTRL->TIMER_1_EN== 1)
	{
		TIMER_CTRL->TIMER_1_EN = 0; 
		delay_us(50);
	}
	
	TIMER_CTRL->TIMER_1_VAL= interval;
	TIMER_CTRL->TIMER_1_RGLR= 1;
	TIMER_CTRL->TIMER_1_INT_MASK = 0;
	timer_callback[1] = ((void (*)(void))p_callback);

	TIMER_CTRL->TIMER_1_INT_CLR = 1; 
	NVIC_EnableIRQ(TIMER1_IRQn);

	TIMER_CTRL->TIMER_1_EN = 1;
}

uint32_t timer_1_get_val(void)
{
	return TIMER_CTRL->TIMER_1_CNT;
}

/*
��ʱ��1 ʧ�ܺ���  �رն�ʱ��1���ж�
*/
void timer_1_disable(void)
{
	TIMER_CTRL->TIMER_1_EN = 0;
	NVIC_DisableIRQ(TIMER1_IRQn);
	TIMER_CTRL->TIMER_1_INT_CLR = 1; 
}
/*
��ʱ��1 �жϷ�����  ��������˻ص�����
*/
void TIMER1_IRQHandler(void)
{		 
	if(TIMER_CTRL->TIMER_1_INT_STATUS == 1)
	{
		TIMER_CTRL->TIMER_1_INT_CLR = 1; 

		if(timer_callback[1] != 0)
			(*timer_callback[1])();
	}  
}
/*
��ʱ��2 ���ú���
����: 
	uint32_t interval  ��ʱ���ǵݼ������� interval���Ǽ�������ֵ
	void *  p_callback ��ʱ���жϵĻص�����
	��ʱ��ʱ��: 32.768KHz
*/
void timer_2_enable(uint32_t interval, void *  p_callback)
{
	if(TIMER_CTRL->TIMER_2_EN== 1)
	{
		TIMER_CTRL->TIMER_2_EN = 0;
		delay_us(50);
	}
	
	TIMER_CTRL->TIMER_2_VAL= interval;
	TIMER_CTRL->TIMER_2_RGLR= 1;
	TIMER_CTRL->TIMER_2_INT_MASK = 0;
	timer_callback[2] = ((void (*)(void))p_callback);
	
	TIMER_CTRL->TIMER_2_INT_CLR = 1; 
	NVIC_EnableIRQ(TIMER2_IRQn);
	
	TIMER_CTRL->TIMER_2_EN = 1;
}

uint32_t timer_2_get_val(void)
{
	return TIMER_CTRL->TIMER_2_CNT;
}

/*
��ʱ��2 ʧ�ܺ���  �رն�ʱ��2���ж�
*/
void timer_2_disable(void)
{
	TIMER_CTRL->TIMER_2_EN = 0;
	NVIC_DisableIRQ(TIMER2_IRQn);
	TIMER_CTRL->TIMER_2_INT_CLR = 1; 
}
/*
��ʱ��2 �жϷ�����  ��������˻ص�����
*/
void TIMER2_IRQHandler(void)
{		 
	if(TIMER_CTRL->TIMER_2_INT_STATUS == 1)
	{
		TIMER_CTRL->TIMER_2_INT_CLR = 1; 

		if(timer_callback[2] != 0)
			(*timer_callback[2])();
	}  
}
#endif

/****************************************���ٶ�ʱ��***************************************************/
static H_TIMER_CTRL_TYPE * H_TIMER_CTRL = ((H_TIMER_CTRL_TYPE *) H_TIMER_CTRL_BASE);
static void (*htimer_callback)(void);

/*************************************************************
���ٶ�ʱ�� ���ú���
����: 
	uint16_t interval  interval���Ǽ��������ϼ��������ֵ
	void *  p_callback ��ʱ���жϵĻص�����
	��ʱ��ʱ��: 64M
**************************************************************/
void Htimer_enable(uint16_t interval, void (*p_callback)(void))
{
	if(H_TIMER_CTRL->BUSY == 1)
	{
		H_TIMER_CTRL->STOP = 1;
	}

	H_TIMER_CTRL->ONE_TIME = 0;
	H_TIMER_CTRL->COUNTER_TOP = interval;

	H_TIMER_CTRL->PRESCALER = H_TIMER_PERSCALER_1;	

	htimer_callback = p_callback;
	H_TIMER_CTRL->EVENT = 1;		//clr Int
	H_TIMER_CTRL->INTEN = 1;
	NVIC_EnableIRQ(HTIMER_IRQn);

	H_TIMER_CTRL->START = 1;		//set H_TIMER_CTRL->BUSY
}

uint16_t Htimer_get_val(void)
{
	return H_TIMER_CTRL->COUNTER;
}

/*************************************************************
���ٶ�ʱ��ֹͣ����
**************************************************************/
void Htimer_disable(void)
{
	H_TIMER_CTRL->STOP = 1;			//clr H_TIMER_CTRL->BUSY
	while(H_TIMER_CTRL->BUSY);
}

/*************************************************************
���ٶ�ʱ���жϷ�����  ��������˻ص�����
**************************************************************/
void HTIMER_IRQHandler(void)
{
	uint8_t status = (uint8_t)H_TIMER_CTRL->EVENT;
	H_TIMER_CTRL->EVENT = 1;		//clr Int

	if(htimer_callback != 0)
	{
		htimer_callback();
	}
}

