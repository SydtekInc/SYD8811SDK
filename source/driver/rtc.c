#include "rtc.h"
#include "debug.h"
#include "delay.h"

static RTC_CTRL_TYPE * RTC_CTRL	= ((RTC_CTRL_TYPE *)	RTC_CTRL_BASE);
RTC_IRQ_CALLBACK irq_cb;
static bool enabled = false;

void rtc_int_clear(RTC_INT_TYPE type)
{
	RTC_CTRL->EVENTS_CLR |= type;
}

//可以动态设置RTC中断
void rtc_int_enable(RTC_INT_TYPE type)
{
    RTC_CTRL->EVENTS_EN |= type;
}

//可以动态设置RTC中断
void rtc_int_disable(RTC_INT_TYPE type)
{
    RTC_CTRL->EVENTS_EN &= ~type;
}

void rtc_start(void)
{
	if(enabled == false)
	{
		RTC_CTRL->START = 1;
		while (RTC_CTRL->START);
		//RTC_CTRL->LOAD = 1;						//load alarm	
		enabled = true;
	}
}

/* This will reset RTC counter for prescaler*/
void rtc_stop(void)
{
	if(enabled == true)	
	{
		RTC_CTRL->STOP = 1;
		while (RTC_CTRL->STOP);
		enabled = false;
	}
}

bool rtc_status(void)
{
    return enabled;
}

void rtc_clear(void)
{
    /* This clear COUNTER & CALENDAR */
    RTC_CTRL->CLEAR = 1;
    while (RTC_CTRL->CLEAR);
}

/***********************************************************************
功能: 设置RTC的tick分频
注意:
	  1.必须在停止状态才能设置，即先调用rtc_stop()函数
	  2.必须保证second时间准确，通过SECONDS_BIT
************************************************************************/
void rtc_set_prescaler(uint32_t tick, uint8_t adjust_seconds_bit)
{
    RTC_CTRL->PRESCALER = (tick - 1) & 0x7FFF;
    RTC_CTRL->SECONDS_BIT = adjust_seconds_bit & 0x0f;
}

RTC_TIME_TYPE rtc_get_alarm(int id)
{
    __IO uint32_t * compare = id ? &RTC_CTRL->COMPARE1 : &RTC_CTRL->COMPARE0;
    int i;
    RTC_TIME_TYPE time;
    
    time.u32 = *compare;
    
    // time format to decimal
    for (i=0 ; i<3; i++) 
	{
        uint8_t tmp = time.u8[i];
        time.u8[i] = (tmp >> 4) * 10;
        time.u8[i] += (tmp & 0xF);
    }
    
    return time;
}

/***********************************************************************
功能: 设置RTC闹钟
参数:
	  id : 0-选择闹钟0, 1 - 选择闹钟1
************************************************************************/
void rtc_set_alarm(int id, RTC_TIME_TYPE *time)
{
    __IO uint32_t * compare = id ? &RTC_CTRL->COMPARE1 : &RTC_CTRL->COMPARE0;
    int i;
	
    // Decimal to time format
    for (i=0; i<3; i++) 
	{
        uint8_t tmp = time->u8[i];
        time->u8[i] = (tmp / 10) << 4;
        time->u8[i] |= tmp % 10;
    }
    *compare = time->u32;

	delay_us(100);		//64M - delay 38us
	
	RTC_CTRL->LOAD = 1;		//load alarm
}

/****************************************************************************
功能: 删除RTC闹钟
参数:
	  id : 0-选择闹钟0, 1 - 选择闹钟1
*****************************************************************************/
void rtc_delete_alarm(int id)
{
    __IO uint32_t * compare = id ? &RTC_CTRL->COMPARE1 : &RTC_CTRL->COMPARE0;

    *compare = 0x00ffffff;
	RTC_CTRL->LOAD = 1;			//load alarm
}

/***********************************************************************
功能: 设置RTC时间，并启动RTC
注意:
	  先停止RTC,再设置相关寄存器，再启动RTC
************************************************************************/
void rtc_set_calendar(RTC_TIME_TYPE *time)
{
	int i;
	//rtc_stop();
	
    // Decimal to time format
    for (i=0; i<3; i++) 
	{
        uint8_t tmp = time->u8[i];
        time->u8[i] = (tmp / 10) << 4;
        time->u8[i] |= tmp % 10;
    }
    
	RTC_CTRL->CALENDAR_INI = time->u32;

	//rtc_start();
}

/***********************************************************************
功能: 获取当前的日历时间
************************************************************************/
RTC_TIME_TYPE rtc_get_calendar(void)
{
    int i;
    RTC_TIME_TYPE time;
    
    time.u32 = RTC_CTRL->CALENDAR;
    
    // time format to decimal
    for (i = 0 ; i < 3; i++) 
	{
        uint8_t tmp = time.u8[i];
        time.u8[i] = (tmp >> 4) * 10;
        time.u8[i] += (tmp & 0xF);
    }
    
    return time;
}  


void RTC_IRQHandler(void)
{
    RTC_INT_TYPE status = (RTC_INT_TYPE)RTC_CTRL->EVENTS;
	rtc_int_clear(status);
	
	if(status)
	{
		if(irq_cb)
		{
			irq_cb(status);
		}
	}
}


