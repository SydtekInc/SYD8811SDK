#include "gpadc.h"
#include "debug.h"
#include "gpio.h"

GPADC_CTRL_TYPE * GPADC	= ((GPADC_CTRL_TYPE *)	GPADC_CTRL_BASE);

uint8_t channel = 0;

/**********************************************************
		GPIO2				ADCGP_CH[0]
		GPIO3				ADCGP_CH[1]
		GPIO4				ADCGP_CH[2]
		GPIO5				ADCGP_CH[3]
		GPIO28			ADCGP_CH[4]
		GPIO29			ADCGP_CH[5]
		GPIO30			ADCGP_CH[6]
		GPIO31			ADCGP_CH[7]
		VBAT				ADCGP_CH[8]
		VDVDD_1.25	ADCGP_CH[9]
		VDCDC_1.1		ADCGP_CH[10]	
***********************************************************/
void GPADC_Init(GPADC_MODE mode)
{
//-----------------pin config-------------------
#if 1
	//ADCGP_CH[0] Pin Init
	PIN_CONFIG->PIN_2_SEL = PIN_SEL_GPIO;
	GPIO_CTRL->GPIO_2_DIR = 1;
	GPI_CTRL->GPI_2_InE = 0;
	PIN_CONFIG->PAD_2_INPUT_PULL_UP = 0;	  //上拉禁止
	
	PIN_CONFIG->PIN_2_SEL = PIN_SEL_ANALOG;	
#endif
#if 1
	//ADCGP_CH[1] Pin Init
	PIN_CONFIG->PIN_3_SEL = PIN_SEL_GPIO;
	GPIO_CTRL->GPIO_3_DIR = 1;
	GPI_CTRL->GPI_3_InE = 0;
	PIN_CONFIG->PAD_3_INPUT_PULL_UP = 0;	  //上拉禁止
	
	PIN_CONFIG->PIN_3_SEL = PIN_SEL_ANALOG;
#endif
#if 1
	//ADCGP_CH[2] Pin Init
	PIN_CONFIG->PIN_4_SEL = PIN_SEL_GPIO;
	GPIO_CTRL->GPIO_4_DIR = 1;
	GPI_CTRL->GPI_4_InE = 0;
	PIN_CONFIG->PAD_4_INPUT_PULL_UP = 0;	  //上拉禁止
	
	PIN_CONFIG->PIN_4_SEL = PIN_SEL_ANALOG;
#endif
#if 1
	//ADCGP_CH[3] Pin Init
	PIN_CONFIG->PIN_5_SEL = PIN_SEL_GPIO;
	GPIO_CTRL->GPIO_5_DIR = 1;
	GPI_CTRL->GPI_5_InE = 0;
	PIN_CONFIG->PAD_5_INPUT_PULL_UP = 0;	  //上拉禁止
	
	PIN_CONFIG->PIN_5_SEL = PIN_SEL_ANALOG;
#endif

#if 1
	//ADCGP_CH[4] Pin Init
	PIN_CONFIG->PIN_28_SEL = PIN_SEL_GPIO;
	GPIO_CTRL->GPIO_28_DIR = 1;
	GPI_CTRL->GPI_28_InE = 0;
	PIN_CONFIG->PAD_36_INPUT_PULL_UP = 0;	  //上拉禁止
	
	PIN_CONFIG->PIN_28_SEL = PIN_SEL_ANALOG;	
#endif
#if 1
	//ADCGP_CH[5] Pin Init
	PIN_CONFIG->PIN_29_SEL = PIN_SEL_GPIO;
	GPIO_CTRL->GPIO_29_DIR = 1;
	GPI_CTRL->GPI_29_InE = 0;
	PIN_CONFIG->PAD_37_INPUT_PULL_UP = 0;	  //上拉禁止
	
	PIN_CONFIG->PIN_29_SEL = PIN_SEL_ANALOG;	
#endif
#if 1
	//ADCGP_CH[6] Pin Init
	PIN_CONFIG->PIN_30_SEL = PIN_SEL_GPIO;
	GPIO_CTRL->GPIO_30_DIR = 1;
	GPI_CTRL->GPI_30_InE = 0;
	PIN_CONFIG->PAD_38_INPUT_PULL_UP = 0;	  //上拉禁止
	
	PIN_CONFIG->PIN_30_SEL = PIN_SEL_ANALOG;	
#endif
#if 1
	//ADCGP_CH[7] Pin Init
	PIN_CONFIG->PIN_31_SEL = PIN_SEL_GPIO;
	GPIO_CTRL->GPIO_31_DIR = 1;
	GPI_CTRL->GPI_31_InE = 0;
	PIN_CONFIG->PAD_39_INPUT_PULL_UP = 0;	  //上拉禁止
	
	PIN_CONFIG->PIN_31_SEL = PIN_SEL_ANALOG;
#endif

	GPADC->CLKRATE = 31;		// 64M/((31+1)*2)= 1M
	GPADC->DA_GPADC_EN = 1;

	GPADC->CHANNEL_SET_NUM = 1;
	GPADC->SCAN_COUNT = 1;		//只能设置为1
	GPADC_channel_sel(channel);
	GPADC->Continue_Scan = 0;

	//set time delay
	GPADC->START_SETTLE = 24;
	//GPADC->CHANNEL_SETTLE = 1; 	//7.52us
	//GPADC->CHANNEL_SETTLE = 2;	//11.29us
	GPADC->CHANNEL_SETTLE = 4;		//18.81us
	//GPADC->CHANNEL_SETTLE = 63;	//240.71us

	if(mode == AVE_MODE)
	{
		//一次scan采集data_length+1次数据,然后再取均值
		GPADC->AVERAGE = 7;
		GPADC->DATA_LENGTH = 7;
	}
	else
	{
		GPADC->AVERAGE = 1;
		GPADC->DATA_LENGTH = 0;
	}
	
	GPADC->EVENTS = 0;
	GPADC->INTENSET = 1;		//使能中断，标志位才能置位
	NVIC_EnableIRQ(GPADC_IRQn);
}

void GPADC_start(void)
{
	GPADC->DA_GPADC_EN = 1;
	GPADC->TASK_START = 1;
}

/*************************************************************
Note:
	STOP will reset Continue_Scan register
**************************************************************/
void GPADC_stop(void)
{
	if(GPADC->gpadc_fsm_cs)
	{
		GPADC->TASK_STOP = 1;
		//
		GPADC->INTENCLR = 1;		//disable INT
		GPADC->EVENTS = 0;			//clear INT flag
		while(GPADC->gpadc_fsm_cs);
		
		while(GPADC->EVENTS == 0);
		GPADC->EVENTS = 0;			//clr INT flag	

		GPADC->INTENSET = 1;		//Enable INT
	}
}

uint16_t GPADC_get_value(void)
{
	return GPADC->adc_data_hclk;
}

/****************************************************************************
function: select 1 GPADC channel when GPADC is stopped at oneshot/ave mode
para:
		  ch - 0 ~ 10 select channel 0 ~ channel 10
note:	  select GPADC channel when GPADC is stopped	
*********************************************************************************/
void GPADC_channel_sel(uint8_t ch)
{
	if(ch<=10)
	{
		GPADC->CHANNEL_SET0 = ch;
		GPADC->CHANNEL_SEL = ch;
	}
}

void GPADC_IRQHandler(void)
{
	if(GPADC->EVENTS)			//使能ADC中断，标志位才能置位
	{
		float vat=0.0;
		uint16_t adc = GPADC_get_value();	
		GPADC->EVENTS = 0;
		GPADC->DA_GPADC_EN = 0;

		vat=(float)adc*3.6/1024;  
		dbg_printf("ch:%02d adc : %04x vat: %4.3f\r\n",channel,adc,vat);
	}	
}

