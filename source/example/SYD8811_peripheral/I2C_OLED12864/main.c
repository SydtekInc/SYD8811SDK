#include "ARMCM0.h"
#include "timer.h"
#include "gpio.h"
#include "debug.h"
#include "lib.h"
#include <string.h>
#include "delay.h"
#include "gpadc.h"
#include "i2c.h"
#include "oled.h"
#include "led_key.h"

int main()
{	
	__disable_irq();
	dbg_printf("SYD8811 I2C oled demo %s:%s\r\n",__DATE__ ,__TIME__);

	GPIO_Set_Output( U32BIT(LED1));	
	GPIO_Pin_Set(U32BIT(LED1));
	
	oled_init();
	
	oled_printf(0,0,"SYD Inc."); 
	oled_printf(0,2,"SYD8811 EVB"); 
	oled_printf(0,4,"oled demo"); 
	oled_printf(0,6,"%s",__DATE__); 
	__enable_irq();	

	while(1)
	{
		GPIO_Pin_Turn(U32BIT(LED1));
		delay_ms(1000);
	}	
}

