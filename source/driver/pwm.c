#include "pwm.h"
#include "gpio.h"
#include "debug.h"

//static PWM_CTRL_TYPE *	PWM_0_CTRL	= ((PWM_CTRL_TYPE *)	PWM_0_CTRL_BASE);
//static PWM_CTRL_TYPE *	PWM_1_CTRL	= ((PWM_CTRL_TYPE *)	PWM_1_CTRL_BASE);
//static PWM_CTRL_TYPE *	PWM_2_CTRL	= ((PWM_CTRL_TYPE *)	PWM_2_CTRL_BASE);
//static HPWM_CTRL_TYPE * HPWM_CTRL	= ((HPWM_CTRL_TYPE *)	HPWM_CTRL_BASE);

#define  PWM_0_CTRL  ((PWM_CTRL_TYPE *)PWM_0_CTRL_BASE)
#define  PWM_1_CTRL  ((PWM_CTRL_TYPE *)PWM_1_CTRL_BASE)
#define  PWM_2_CTRL  ((PWM_CTRL_TYPE *)PWM_2_CTRL_BASE)
#define  HPWM_CTRL   ((HPWM_CTRL_TYPE *)HPWM_CTRL_BASE)

/*
pwm0 初始化函数
参数: PWM_x pwm_x 要初始化的pwm模块 参见PWM_MODE枚举
			PWM_PARAMETER pwm_parameter pwm参数 参见PWM_PARAMETER结构体
举例：	
	PWM_PARAMETER pwm_parameter;
	//Flash mode
	pwm_parameter.MODE=flash_mode;
	pwm_parameter.T1=0x10; 	//16 * 1/32=0.5s 实测0.768563250
	pwm_parameter.T2=0x20;  //32 * 1/32=1s	实测1.585201375
	pwm_parameter.T3=0x0000;
	pwm_parameter.N1=0x80;  //永久重复，没有T3
	pwm_parameter.N2=0x80;  //永久重复
  pwm_enable(PWM_0,pwm_parameter);	
*/
void pwm_enable(PWM_x pwm_x,PWM_PARAMETER pwm_parameter)
{
	PWM_CTRL_TYPE *	PWM_CTRL = 0;
	switch(pwm_x)
	{
		case PWM_0:
			PWM_CTRL = PWM_0_CTRL;
			break;
		case PWM_1:
			PWM_CTRL = PWM_1_CTRL;
			break;
		default:
			PWM_CTRL = PWM_2_CTRL;
			break;
	}

	PWM_CTRL->MODE= pwm_parameter.MODE;
	switch(pwm_parameter.MODE)
	{
		case pwm_mode:
			PWM_CTRL->PWM_M = pwm_parameter.PWM_M;
			PWM_CTRL->PWM_N = pwm_parameter.PWM_N;
			break;
		case flash_mode:
			PWM_CTRL->T1 = pwm_parameter.T1;
			PWM_CTRL->T2 = pwm_parameter.T2;
			PWM_CTRL->T3 = pwm_parameter.T3;
		  PWM_CTRL->N1 = pwm_parameter.N1;
			PWM_CTRL->N2 = pwm_parameter.N2;
			break;
		case breath_mode:
			PWM_CTRL->BR_TH_MAX = pwm_parameter.BR_TH_MAX;
			PWM_CTRL->BR_TH_MIN = pwm_parameter.BR_TH_MIN;
			PWM_CTRL->BR_SP = pwm_parameter.BR_SP;
			PWM_CTRL->T4 = pwm_parameter.T4; 
			 
			break;	
	}
	PWM_CTRL->PAUS= 1;
	PWM_CTRL->LED_PE= 1;
}

void pwm_disable(PWM_x pwm_x)
{
	switch(pwm_x){
		case PWM_0 :
			PWM_0_CTRL->LED_PE= 0;
			break;
		case PWM_1 :
			PWM_1_CTRL->LED_PE= 0;
			break;
		case PWM_2 :
			PWM_2_CTRL->LED_PE= 0;
			break;
	}
}

/*
HPWM 初始化函数
参数: 
	 HPWM_PARAMETER *parameter, 参见HPWM_PARAMETER结构体
*/
void Hpwm_Init(HPWM_PARAMETER *parameter)
{
	Hpwm_Stop();

	/*设计时钟频率64M*/
	HPWM_CTRL->PRESCALER = parameter->prescaler;
	HPWM_CTRL->MODE = parameter->mode;
	HPWM_CTRL->COUNTER_TOP = parameter->period;

	//dbg_printf("0:POLARITY = 0x%08x\r\n",HPWM_CTRL->POLARITY);
	switch(parameter->channel)
	{
		case HPWM_CH0:
			//PIN_CONFIG->PIN_3_SEL = PIN_SEL_HPWM_CH0;
			HPWM_CTRL->CMP_CH0 = parameter->duty;
			if(parameter->polarity == LOW_FIRST)
				HPWM_CTRL->POLARITY &= 0x0e;
			else
				HPWM_CTRL->POLARITY |= 0x01;
			
			break;
		case HPWM_CH1:
			//PIN_CONFIG->PIN_4_SEL = PIN_SEL_HPWM_CH1;
			HPWM_CTRL->CMP_CH1 = parameter->duty;
			if(parameter->polarity == LOW_FIRST)
				HPWM_CTRL->POLARITY &= 0x0d;
			else
				HPWM_CTRL->POLARITY |= 0x02;

			break;
		case HPWM_CH2:
			//PIN_CONFIG->PIN_5_SEL = PIN_SEL_HPWM_CH2;
			HPWM_CTRL->CMP_CH2 = parameter->duty;
			if(parameter->polarity == LOW_FIRST)
				HPWM_CTRL->POLARITY &= 0x0b;
			else
				HPWM_CTRL->POLARITY |= 0x04;

			break;
		default:
			//PIN_CONFIG->PIN_6_SEL = PIN_SEL_HPWM_CH3;
			HPWM_CTRL->CMP_CH3 = parameter->duty;
			if(parameter->polarity == LOW_FIRST)
				HPWM_CTRL->POLARITY &= 0x07;
			else
				HPWM_CTRL->POLARITY |= 0x08;

			break;
	}
	//dbg_printf("1:POLARITY = 0x%08x\r\n",HPWM_CTRL->POLARITY);
#if 0
	dbg_printf("CMP_CH0 = %d\r\n",HPWM_CTRL->CMP_CH0);
	dbg_printf("CMP_CH1 = %d\r\n",HPWM_CTRL->CMP_CH1);
	dbg_printf("CMP_CH2 = %d\r\n",HPWM_CTRL->CMP_CH2);
	dbg_printf("CMP_CH3 = %d\r\n",HPWM_CTRL->CMP_CH3);
#endif

	HPWM_CTRL->EVENTS = HPWM_INT_ALL;		//clr INT
	HPWM_CTRL->INTEN  = HPWM_INT_ALL;
	//HPWM_CTRL->INTEN  = HPWM_INT_PERIOD;
	//HPWM_CTRL->INTEN  = HPWM_INT_TASK_STOP;
	//HPWM_CTRL->INTEN  = HPWM_INT_NONE;

	NVIC_EnableIRQ(HPWM_IRQn);
}

void Hpwm_Set_duty(HPWM_CHx  channels, uint16_t compare)
{
	if(HPWM_CTRL->MODE == UP_MODE)
	{
		if(compare >= HPWM_CTRL->COUNTER_TOP)	//0 <= compare <= COUNTER_TOP-1
		{
			compare = HPWM_CTRL->COUNTER_TOP - 1;
		}
	}
	else
	{
		if(compare >= HPWM_CTRL->COUNTER_TOP-1)
		{
			compare = HPWM_CTRL->COUNTER_TOP-2; //0 <= compare <= COUNTER_TOP-2
		}
	}

	if(channels&HPWM_CH0)
	{
		HPWM_CTRL->CMP_CH0 = compare;
	}
	if(channels&HPWM_CH1)
	{
		HPWM_CTRL->CMP_CH1 = compare;
	}
	if(channels&HPWM_CH2)
	{
		HPWM_CTRL->CMP_CH2 = compare;
	}
	if(channels&HPWM_CH3)
	{
		HPWM_CTRL->CMP_CH3 = compare;
	}
}

//HPWM有4个通道，但这4个通道共用1个周期计数器
void Hpwm_Set_period(uint16_t period)
{
	if(period >= HPWM_CTRL->CMP_CH0)
	{
		HPWM_CTRL->COUNTER_TOP = period; 
	}
}

void Hpwm_Set_mode(HPWM_mode mode)
{
	HPWM_CTRL->MODE = mode;
}

void Hpwm_Start(void)
{
	HPWM_CTRL->START = 1;
}

void Hpwm_Stop(void)
{
	HPWM_CTRL->STOP = 1;
}

void HPWM_IRQHandler(void)
{
	//动态设置占空比
	static uint16_t compare = 1;
//	static uint32_t t = 0;
	
	dbg_printf("HPWM_IRQHandler\r\n");
	
	if(HPWM_CTRL->EVENTS & HPWM_INT_PERIOD)
	{	
		compare++;
		if(compare == HPWM_CTRL->COUNTER_TOP)
		{	
			compare = 1;
			
			dbg_printf("COUNTER_TOP Can stop pwm there!\r\n");
//			t++;
//			if(t == 4)
//			{
//				Hpwm_Stop();
//				return;
//			}
		}
		Hpwm_Set_duty(HPWM_CHALL, compare);
	}
	
	if(HPWM_CTRL->EVENTS & HPWM_INT_TASK_STOP)
	{

	}

	HPWM_CTRL->EVENTS = HPWM_INT_ALL;		//clr INT
}

