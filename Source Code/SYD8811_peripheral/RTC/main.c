#include "ARMCM0.h"
#include "timer.h"
#include "gpio.h"
#include "debug.h"
#include "lib.h"
#include <string.h>
#include "delay.h"
#include "config.h"
#include "rtc.h"
#include "led_key.h"

uint32_t RTC_second_now = 0,RTC_second_last;

static void Timer_0_callback(void)
{
	GPIO_Pin_Turn(U32BIT(LED1));
	dbg_printf("Timer_0_callback\r\n");
}


uint32_t RTC_RUN(void)
{
	RTC_TIME_TYPE time_now;
	uint32_t second=0,second1=0;
	time_now=rtc_get_calendar();
	dbg_printf("n%d %d:%d:%d\r\n",time_now.decimal_format.week,time_now.decimal_format.hour,time_now.decimal_format.minute,time_now.decimal_format.second);
	second=(time_now.decimal_format.week-1)*86400+ time_now.decimal_format.hour*3600+time_now.decimal_format.minute*60+time_now.decimal_format.second;
	if(second>=RTC_second_now) second1=second-RTC_second_now;
  else second1=second+604800-RTC_second_now;
	RTC_second_now=second;
	
	return second1;
}
void RTC_SET(uint32_t Iterval)
{
	RTC_TIME_TYPE time;
	uint32_t second=Iterval+RTC_second_now;
	//init compare
    time.decimal_format.week    = second/86400+1;
	time.decimal_format.hour   = second%86400/3600;
	time.decimal_format.minute = second%3600/60;
	time.decimal_format.second = second%60;
	dbg_printf("C%d %d:%d:%d\r\n",time.decimal_format.week,time.decimal_format.hour,time.decimal_format.minute,time.decimal_format.second);
	rtc_set_alarm(0,&time);
}

static void RTC_IRQ_Handler(RTC_INT_TYPE type)
{
	if(type & RTC_INT_ALARM0)
	{
		RTC_RUN();
		RTC_SET(10);
		//dbg_printf("RTC_INT_ALARM0!\r\n");
	}
	
	if(type & RTC_INT_ALARM1)
	{
		dbg_printf("RTC_INT_ALARM1!\r\n");
	}

	if(type & RTC_INT_TICK)
	{
		dbg_printf("RTC_INT_TICK!\r\n");
	}
}

/***************************************************************************************
功能: RTC初始化 - 设置tick分频、second分频、中断使能
参数:
	tick - tick中断分频值，决定tick中断周期
	adjust_seconds_bit - 在tick分频基础上再次进行指数分频,决定second中断周期
注意:
	设置RTC时间需调用rtc_set_calendar()
****************************************************************************************/
void RTC_Init(uint32_t tick, uint8_t adjust_seconds_bit, RTC_IRQ_CALLBACK call_back)
{
	RTC_TIME_TYPE time;
	
	rtc_stop();

	//set clk division
	rtc_set_prescaler(tick, adjust_seconds_bit);

	time.decimal_format.week = 1;
	time.decimal_format.hour = 0;
	time.decimal_format.minute = 0;
	time.decimal_format.second = 0;
	rtc_set_calendar(&time);
	
	time.decimal_format.week = 1;
	time.decimal_format.hour = 0;
	time.decimal_format.minute = 0;
	time.decimal_format.second = 10;
	rtc_set_alarm(ALARM_0, &time);
	
	irq_cb = call_back;
	rtc_int_clear(RTC_INT_ALL);
	rtc_int_enable(RTC_INT_ALL);
	NVIC_EnableIRQ(RTC_IRQn);
	
	rtc_start();
	
	time=rtc_get_calendar();
	dbg_printf("START n%d %d:%d:%d\r\n",time.decimal_format.week,time.decimal_format.hour,time.decimal_format.minute,time.decimal_format.second);
	time=rtc_get_alarm(ALARM_0);
	dbg_printf("START C%d %d:%d:%d\r\n",time.decimal_format.week,time.decimal_format.hour,time.decimal_format.minute,time.decimal_format.second);
}


int main()
{	
//	struct gap_wakeup_config pw_cfg;
	__disable_irq();
	
	BleInit();
	MCUClockSwitch(SYSTEM_CLOCK_64M_RCOSC);
	ClockSwitch(SYSTEM_32K_CLOCK_RCOSC);
	delay_ms(500);
	LPOCalibration();						//这是内部RC32k晶振的校准函数	经过该函数后定时器能够得到一个比较准确的值
	
	GPIO_Set_Output(U32BIT(LED1));
	timer_0_enable(32768*10, Timer_0_callback);
		
	dbg_init();
	dbg_printf("SYD8811 Rtc Test 2018-9-12\r\n");
	

	
	RTC_Init(RTC_TICK_PRESCALER_1,0,RTC_IRQ_Handler);
	
	__enable_irq();	
	
//	//set MCU wakup source
//	pw_cfg.wakeup_type = SLEEP_WAKEUP;
//	pw_cfg.timer_wakeup_en = true;
//	pw_cfg.gpi_wakeup_en = true;
//	pw_cfg.wdt_wakeup_en = false;
//	pw_cfg.rtc_wakeup_en = true;
//	pw_cfg.gpi_wakeup_cfg= BIT6;
//	WakeupConfig(&pw_cfg);
	
	while(1)
	{				
		ble_sched_execute();
		
		
		//SystemSleep();	
	}	
}

