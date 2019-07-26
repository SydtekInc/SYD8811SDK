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
#include "sc_reader.h"


int main()
{	
	__disable_irq();
	
	BleInit();	
	//根据需要重新设置时钟为4M并校准
	MCUClockSwitch(SYSTEM_CLOCK_64M_RCOSC);
	RCOSCCalibration();
	
	dbg_init();
	UartEn(true);
	dbg_printf("SYD8811 7816 Test demo %s:%s\r\n",__DATE__ ,__TIME__);
	dbg_printf("Please insert your card to active CARD_DETECT INT!\r\n");

	PIN_Set_GPIO(U32BIT(LED1) | U32BIT(LED2),PIN_SEL_GPIO);
	GPIO_Set_Output( U32BIT(LED1) | U32BIT(LED2));	
	GPIO_Pin_Set(U32BIT(LED1) | U32BIT(LED2));
	
	sc_reader_enable();
	__enable_irq();	

	while(1)
	{
		GPIO_Pin_Turn(U32BIT(LED1));

		sc_reader_task();
		
		//delay_ms(100);
	}	
}

