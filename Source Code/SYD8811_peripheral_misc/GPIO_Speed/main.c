#include "ARMCM0.h"
#include "timer.h"
#include "gpio.h"
#include "debug.h"
#include "lib.h"
#include <string.h>
#include "delay.h"
#include "gpadc.h"
#include "led_key.h"
#include "config.h"

extern  uint8_t channel;

int main()
{	
	__disable_irq();

	BleInit();	
	MCUClockSwitch(SYSTEM_CLOCK_64M_RCOSC);
	RCOSCCalibration();
	
	dbg_init();
	UartEn(true);
	dbg_printf("SYD8811 GPIO test demo %s:%s\r\n", __DATE__ , __TIME__);
	
	PIN_Set_GPIO(U32BIT(KEY1) | U32BIT(KEY2) | U32BIT(KEY3) | U32BIT(KEY4),PIN_SEL_GPIO);
	PIN_Set_GPIO(U32BIT(LED1) | U32BIT(LED2) | U32BIT(LED3) | U32BIT(LED4),PIN_SEL_GPIO);
	
	GPIO_Set_Input( U32BIT(KEY1) | U32BIT(KEY2) | U32BIT(KEY3) | U32BIT(KEY4),  U32BIT(KEY1) | U32BIT(KEY2) | U32BIT(KEY3) | U32BIT(KEY4));	
	PIN_Pullup_Enable(T_QFN_48, U32BIT(KEY1) | U32BIT(KEY2) | U32BIT(KEY3) | U32BIT(KEY4));
	GPIO_Input_Enable(U32BIT(KEY1) | U32BIT(KEY2) | U32BIT(KEY3) | U32BIT(KEY4));
	
	GPIO_Set_Output( U32BIT(LED1) | U32BIT(LED2) | U32BIT(LED3) | U32BIT(LED4));	
	GPIO_Pin_Set(U32BIT(LED1) | U32BIT(LED2) | U32BIT(LED3) | U32BIT(LED4));

	__enable_irq();	

	while(1)
	{
//		GPO_CTRL->GPO |= U32BIT(LED1);
//		GPO_CTRL->GPO &= ~U32BIT(LED1);
//		*(uint32_t *)0x50001014UL |= U32BIT(LED1);
//		*(uint32_t *)0x50001014UL &= ~U32BIT(LED1);
		*(uint32_t *)0x50001014UL |= BIT0;
		*(uint32_t *)0x50001014UL &= 0xFFFFFFFE;
	}	
}

