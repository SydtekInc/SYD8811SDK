#include "ARMCM0.h"
#include "timer.h"
#include "gpio.h"
#include "debug.h"
#include "lib.h"
#include <string.h>
#include "delay.h"
#include "led_key.h"
#include "config.h"

static void Timer_0_callback(void)
{
	GPIO_Pin_Turn(U32BIT(LED1));
	dbg_printf("Timer_0_callback\r\n");
}

static void Timer_1_callback(void)
{
	GPIO_Pin_Turn(U32BIT(LED2));
	dbg_printf("Timer_1_callback\r\n");
}

static void Timer_2_callback(void)
{
	GPIO_Pin_Turn(U32BIT(LED3));
	dbg_printf("Timer_2_callback\r\n");
}


int main()
{	

	__disable_irq();
	
	BleInit();
	MCUClockSwitch(SYSTEM_CLOCK_64M_RCOSC);
	ClockSwitch(SYSTEM_32K_CLOCK_RCOSC);
	delay_ms(500);
	LPOCalibration();						//这是内部RC32k晶振的校准函数	经过该函数后定时器能够得到一个比较准确的值
	
	GPIO_Set_Output(U32BIT(LED1));
	GPIO_Set_Output(U32BIT(LED2));
	GPIO_Set_Output(U32BIT(LED3));

	timer_0_enable(32768/2,  Timer_0_callback);//500ms
	timer_1_enable(32768,    Timer_1_callback);//1s
	timer_2_enable(32768*10, Timer_2_callback);//10s

	dbg_init();
	dbg_printf("SYD8811 Timer Test 2018-9-12\r\n");
	__enable_irq();	
	
	while(1)
	{				
		ble_sched_execute();
	}	
}

