#include "ARMCM0.h"
#include "timer.h"
#include "gpio.h"
#include "debug.h"
#include "lib.h"
#include <string.h>
#include "delay.h"
#include "gpadc.h"
#include "i2c.h"
#include "led_key.h"

int main()
{	
	__disable_irq();
	dbg_printf("SYD8811 SPIMaster FLASH demo %s:%s\r\n",__DATE__ ,__TIME__);

	GPIO_Set_Output( U32BIT(LED1));	
	GPIO_Pin_Set(U32BIT(LED1));
	
	
	__enable_irq();	

	while(1)
	{
		GPIO_Pin_Turn(U32BIT(LED1));
		delay_ms(1000);
	}	
}

