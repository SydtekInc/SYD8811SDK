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



static POWER_CTRL_TYPE * PW_CTRL = ((POWER_CTRL_TYPE *) PWRON_BASE);
static MISC_CTRL_TYPE * MISC_CTRL = ((MISC_CTRL_TYPE *) MISC_BASE);


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
	PIN_Set_GPIO(U32BIT(LED1) | U32BIT(LED2) | U32BIT(LED3) | U32BIT(LED4) ,PIN_SEL_GPIO);
	
	GPIO_Set_Input( U32BIT(KEY1) | U32BIT(KEY2) | U32BIT(KEY3) | U32BIT(KEY4),  U32BIT(KEY1) | U32BIT(KEY2) | U32BIT(KEY3) | U32BIT(KEY4));	
	PIN_Pullup_Enable(T_QFN_48, U32BIT(KEY1) | U32BIT(KEY2) | U32BIT(KEY3) | U32BIT(KEY4));
	GPIO_Input_Enable(U32BIT(KEY1) | U32BIT(KEY2) | U32BIT(KEY3) | U32BIT(KEY4));
	
	GPIO_Set_Output( U32BIT(LED1) | U32BIT(LED2) | U32BIT(LED3) | U32BIT(LED4) );	
	GPIO_Pin_Set(U32BIT(LED1) | U32BIT(LED2) | U32BIT(LED3) | U32BIT(LED4));

	__enable_irq();	

	
	PW_CTRL->DIG_DEBUG_EN = 0x01;
	MISC_CTRL->DEBUG_SW = 0x91;
	*((uint8_t *)(PWRON_BASE + 0x78)) = 0x1d;  //GPIO24-->mcu_clk  就是上面MCUClockSwitch接口设置的时钟频率
	*((uint8_t *)(PWRON_BASE + 0x8C)) |= 0x01;  //PAD_DRV32==1 提高输出能力
	while(1)
	{
		GPIO_Pin_Turn(U32BIT(LED1));
		delay_ms(1000);
	}	
}

