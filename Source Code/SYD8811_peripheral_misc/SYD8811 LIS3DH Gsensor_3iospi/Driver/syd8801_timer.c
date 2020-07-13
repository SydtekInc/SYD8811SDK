/*
定时器操作文件

作者：北京盛源达科技有限公司
日期：2016/7/8
*/
#include "syd8801_timer.h"
#include "syd8801_delay.h"

//定时器寄存器定义
TIMER_CTRL_TYPE * TIMER_CTRL = ((TIMER_CTRL_TYPE *) TIMER_CTRL_BASE);

//定时器回调函数定义 timer0的回调函数是timer0_callback[0]
static void (*timer0_callback[3])(void);

/*
定时器0 配置函数
参数: uint32_t interval  interval要计数的次数  定时器0是递减计数器 所以这里的interval就是计数器的溢出次数
			void *  p_callback   定时器中断的回调函数
			timer_0_enable(0x20, timer0_callback); // 32 * 31.25 us = 1ms
*/
void timer_0_enable(uint32_t interval, void *  p_callback)
{
	if(TIMER_CTRL->TIMER_0_EN== 1)
		TIMER_CTRL->TIMER_0_EN = 0;	
  delay_us(100);   //稍微延时 使定时器重启成功
	
	TIMER_CTRL->TIMER_0_VAL= interval;

	timer0_callback[0] = ((void (*)(void))p_callback);

	TIMER_CTRL->TIMER_0_RGLR= 1;
	
	TIMER_CTRL->TIMER_0_EN = 1;

	NVIC_EnableIRQ(TIMER0_IRQn);
}
/*
定时器0 失能函数  关闭定时器0的中断
*/
void timer_0_disable(void)
{
	TIMER_CTRL->TIMER_0_EN = 0;

	NVIC_DisableIRQ(TIMER0_IRQn);
}
/*
定时器0 延时 cnt个32us函数，单位为：32us  总延时 cnt*32 us
参数：uint32_t cnt 微秒数
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
定时器0 中断服务函数  这里调用了回调函数
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
定时器1 配置函数
参数: uint32_t interval  interval要计数的次数  定时器1是递减计数器 所以这里的interval就是计数器的溢出次数
			void *  p_callback   定时器中断的回调函数
			timer_1_enable(0x20, timer0_callback); // 32 * 31.25 us = 1ms
*/
void timer_1_enable(uint32_t interval, void *  p_callback)
{
	if(TIMER_CTRL->TIMER_1_EN== 1)
		TIMER_CTRL->TIMER_1_EN = 0;	
	
	delay_us(100);   //稍微延时 使定时器重启成功
	
	TIMER_CTRL->TIMER_1_VAL= interval;

	timer0_callback[1] = ((void (*)(void))p_callback);

	TIMER_CTRL->TIMER_1_RGLR= 1;
	
	TIMER_CTRL->TIMER_1_EN = 1;

	NVIC_EnableIRQ(TIMER1_IRQn);
}
/*
定时器1 失能函数  关闭定时器0的中断
*/
void timer_1_disable(void)
{
	TIMER_CTRL->TIMER_1_EN = 0;

	NVIC_DisableIRQ(TIMER1_IRQn);
}
/*
定时器1 中断服务函数  这里调用了回调函数
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
定时器2 配置函数
参数: uint32_t interval  interval要计数的次数  定时器2是递减计数器 所以这里的interval就是计数器的溢出次数
			void *  p_callback   定时器中断的回调函数
			timer_2_enable(0x20, timer0_callback); // 32 * 31.25 us = 1ms
*/
void timer_2_enable(uint32_t interval, void *  p_callback)
{
	if(TIMER_CTRL->TIMER_2_EN== 1)
		TIMER_CTRL->TIMER_2_EN = 0;
	
	delay_us(100);   //稍微延时 使定时器重启成功
	
	TIMER_CTRL->TIMER_2_VAL= interval;

	timer0_callback[2] = ((void (*)(void))p_callback);

	TIMER_CTRL->TIMER_2_RGLR= 1;
	
	TIMER_CTRL->TIMER_2_EN = 1;

	NVIC_EnableIRQ(TIMER2_IRQn);
}
/*
定时器2 失能函数  关闭定时器0的中断
*/
void timer_2_disable(void)
{
	TIMER_CTRL->TIMER_2_EN = 0;

	NVIC_DisableIRQ(TIMER2_IRQn);
}
/*
定时器2 中断服务函数  这里调用了回调函数
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

