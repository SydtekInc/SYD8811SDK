#include "timer.h"
#include "delay.h"

static TIMER_CTRL_TYPE * TIMER_CTRL = ((TIMER_CTRL_TYPE *) TIMER_CTRL_BASE);

//定时器回调函数定义 timer_x的回调函数是timer_callback[x]
static void (*timer_callback[3])(void);

/*
定时器0 配置函数
参数: 
	uint32_t interval  定时器是递减计数器 interval就是计数器初值
	void *  p_callback 定时器中断的回调函数
	定时器时钟: 32.768KHz
*/
void timer_0_enable(uint32_t interval, void *  p_callback)
{
	if(TIMER_CTRL->TIMER_0_EN== 1)
	{
		TIMER_CTRL->TIMER_0_EN = 0;	
  		delay_us(50);   //稍微延时 使定时器重启成功
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
定时器0 失能函数  关闭定时器0的中断
*/
void timer_0_disable(void)
{
	TIMER_CTRL->TIMER_0_EN = 0;
	NVIC_DisableIRQ(TIMER0_IRQn);
	TIMER_CTRL->TIMER_0_INT_CLR = 1;
}
/*
定时器0 延时 cnt个32us函数，单位为：32us  总延时 cnt*32 us
参数：uint32_t cnt 微秒数
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
定时器0 中断服务函数  这里调用了回调函数
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
定时器1 配置函数
参数: 
	uint32_t interval  定时器是递减计数器 interval就是计数器初值
	void *  p_callback 定时器中断的回调函数
	定时器时钟: 32.768KHz
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
定时器1 失能函数  关闭定时器1的中断
*/
void timer_1_disable(void)
{
	TIMER_CTRL->TIMER_1_EN = 0;
	NVIC_DisableIRQ(TIMER1_IRQn);
	TIMER_CTRL->TIMER_1_INT_CLR = 1; 
}
/*
定时器1 中断服务函数  这里调用了回调函数
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
定时器2 配置函数
参数: 
	uint32_t interval  定时器是递减计数器 interval就是计数器初值
	void *  p_callback 定时器中断的回调函数
	定时器时钟: 32.768KHz
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
定时器2 失能函数  关闭定时器2的中断
*/
void timer_2_disable(void)
{
	TIMER_CTRL->TIMER_2_EN = 0;
	NVIC_DisableIRQ(TIMER2_IRQn);
	TIMER_CTRL->TIMER_2_INT_CLR = 1; 
}
/*
定时器2 中断服务函数  这里调用了回调函数
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

/****************************************高速定时器***************************************************/
static H_TIMER_CTRL_TYPE * H_TIMER_CTRL = ((H_TIMER_CTRL_TYPE *) H_TIMER_CTRL_BASE);
static void (*htimer_callback)(void);

/*************************************************************
高速定时器 配置函数
参数: 
	uint16_t interval  interval就是计数器向上计数的最大值
	void *  p_callback 定时器中断的回调函数
	定时器时钟: 64M
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
高速定时器停止函数
**************************************************************/
void Htimer_disable(void)
{
	H_TIMER_CTRL->STOP = 1;			//clr H_TIMER_CTRL->BUSY
	while(H_TIMER_CTRL->BUSY);
}

/*************************************************************
高速定时器中断服务函数  这里调用了回调函数
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

