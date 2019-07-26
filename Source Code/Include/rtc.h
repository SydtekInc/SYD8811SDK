#ifndef _RTC_H_
#define _RTC_H_

#include "ARMCM0.h"

#define RTC_CLK		32768UL		//…Ëº∆÷µ

#define 	ALARM_0				0
#define		ALARM_1				1

typedef enum {
    RTC_TICK_PRESCALER_1 			= 	RTC_CLK/32768,
    RTC_TICK_PRESCALER_2 			= 	RTC_CLK/16384,
    RTC_TICK_PRESCALER_4 			= 	RTC_CLK/8192,
    RTC_TICK_PRESCALER_8 			= 	RTC_CLK/4096,   
	RTC_TICK_PRESCALER_16 			= 	RTC_CLK/2048,
	RTC_TICK_PRESCALER_32 			= 	RTC_CLK/1024,
	RTC_TICK_PRESCALER_64 			= 	RTC_CLK/512,
	RTC_TICK_PRESCALER_128 			= 	RTC_CLK/256,
	RTC_TICK_PRESCALER_256 			= 	RTC_CLK/128,
	RTC_TICK_PRESCALER_512 			= 	RTC_CLK/64,
	RTC_TICK_PRESCALER_1024 		= 	RTC_CLK/32,
	RTC_TICK_PRESCALER_2048 		= 	RTC_CLK/16,
	RTC_TICK_PRESCALER_4096 		= 	RTC_CLK/8,
	RTC_TICK_PRESCALER_8192 		= 	RTC_CLK/4,
	RTC_TICK_PRESCALER_16384 		= 	RTC_CLK/2,
	RTC_TICK_PRESCALER_32768		= 	RTC_CLK/1	 
} RTC_TICK_PRESCALER;

typedef enum {
    RTC_INT_ALARM0 = 0x01,
    RTC_INT_ALARM1 = 0x02,
    RTC_INT_TICK   = 0x04,
    RTC_INT_SECOND = 0x08,
    RTC_INT_ALL    = 0x0F
} RTC_INT_TYPE;

typedef void (* RTC_IRQ_CALLBACK) (RTC_INT_TYPE type);

extern RTC_IRQ_CALLBACK irq_cb;

#pragma pack(push, 1)
typedef union {
    struct {
        uint8_t  second;
        uint8_t  minute;
        uint8_t  hour;
        uint8_t  week;
    } decimal_format;
	
    uint8_t  u8[4];
	
    uint32_t u32;
} RTC_TIME_TYPE;
#pragma pack(pop)

void rtc_int_clear(RTC_INT_TYPE type);
void rtc_int_enable(RTC_INT_TYPE type);
void rtc_int_disable(RTC_INT_TYPE type);
void rtc_start(void);
void rtc_stop(void);
bool rtc_status(void);
void rtc_clear(void);
void rtc_set_prescaler(uint32_t tick, uint8_t adjust_seconds_bit);
RTC_TIME_TYPE rtc_get_alarm(int id);
void rtc_set_alarm(int id, RTC_TIME_TYPE *time);
void rtc_delete_alarm(int id);
void rtc_set_calendar(RTC_TIME_TYPE *time);
RTC_TIME_TYPE rtc_get_calendar(void);
void rtc_init(uint32_t tick, uint8_t adjust_seconds_bit, RTC_IRQ_CALLBACK call_back);

#endif //_RTC_H_

