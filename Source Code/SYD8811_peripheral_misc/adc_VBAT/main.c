#include "ARMCM0.h"
#include "timer.h"
#include "gpio.h"
#include "debug.h"
#include "lib.h"
#include <string.h>
#include "delay.h"
#include "config.h"
#include "gpadc.h"
#include "led_key.h"

extern  uint8_t channel;

volatile uint8_t adc_state=0;

int main()
{	
	__disable_irq();
	BleInit();
	dbg_init();
	UartEn(true);
	
	
	PIN_Set_GPIO(U32BIT(KEY1),PIN_SEL_GPIO);
	GPIO_Set_Input(U32BIT(KEY1),U32BIT(KEY1));
	PIN_Pullup_Enable(T_QFN_48, U32BIT(KEY1));
	GPIO_Input_Enable(U32BIT(KEY1));
	
	
	
	dbg_printf("SYD8811 GPADC test demo %s:%s\r\n",__DATE__ ,__TIME__);
	
	GPADC_Manual_Calibration(0x12);   //手动校准函数  改函数只是在前期工程样品上有用
	GPADC_Init(AVE_MODE);
	
	__enable_irq();	
	
	channel=8;
	GPADC_channel_sel(channel);	
	
	GPADC_start();
	while(1)
	{				
		//if(GPIO_Pin_Read(U32BIT(KEY1)))
		if(adc_state==1)
		{
			adc_state=0;
			dbg_printf("GPADC_start\r\n");
			//auto stop,so restart...
			#if 0
			channel++;
			if(channel >= GPADC_CH_MAX)
			{
				channel = 0;
			}
			GPADC_channel_sel(channel);	
			#endif
			GPADC_start();
			delay_ms(1000);
		}
	}	
}

