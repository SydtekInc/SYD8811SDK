#include "ARMCM0.h"
#include "timer.h"
#include "gpio.h"
#include "debug.h"
#include "lib.h"
#include <string.h>
#include "delay.h"
#include "led_key.h"
#include "wdt.h"
#include "config.h"

uint8_t timer1_flag = 0;

static void Timer_1_callback(void)
{
	timer1_flag = 1;
	GPIO_Pin_Turn(U32BIT(LED2));
	dbg_printf("Timer_1_callback\r\n");
}


int main()
{	
	__disable_irq();
	
	BleInit();
	MCUClockSwitch(SYSTEM_CLOCK_64M_RCOSC);
	ClockSwitch(SYSTEM_32K_CLOCK_RCOSC);
	delay_ms(500);
	LPOCalibration();						//�����ڲ�RC32k�����У׼����	�����ú�����ʱ���ܹ��õ�һ���Ƚ�׼ȷ��ֵ
	
	GPIO_Set_Output(U32BIT(LED1));
	GPIO_Set_Output(U32BIT(LED2));
	GPIO_Set_Output(U32BIT(LED3));
	
	
	GPIO_Set_Input(U32BIT(KEY1), U32BIT(KEY1));

	timer_1_enable(32768, Timer_1_callback);//1s

	dbg_init();
	dbg_printf("SYD8811 Timer Test 2018-9-12\r\n");
	
	wdt_enable(128*5);//5s����ι������ 256/32.768 = 7.8ms  	
	__enable_irq();	

	while(1)
	{		
		if(timer1_flag)//1s
		{
			timer1_flag = 0;
			wdt_clear();//ιһ�ι�
		}
		
		ble_sched_execute();
	}	
}

