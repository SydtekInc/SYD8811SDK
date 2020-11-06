#ifndef _TIMER_HANDLER_H_
#define _TIMER_HANDLER_H_

#include "config.h"

#define TIMER_NUM 5

typedef void (* TIMER_IRQ_CALLBACK_TYPE)(void);

typedef enum {
    TIMER_0 = 0,
    TIMER_1 ,
    TIMER_2 ,
		TIMER_3 ,
		TIMER_4 ,
} TIMER_ID;

struct SYD_HISTORY_SETTING{
	uint32_t SYD_timeSeconds;
};

extern struct SYD_HISTORY_SETTING  syd_history_setting_str;

#define  EVT_ENABLE_MODE ((uint8_t) 0x01)
#define  EVT_DISABLE_MODE ((uint8_t) 0x00)


#define  EVT_MAX_NUM  ((uint8_t) 0x1F)//定时器事件数

#define  RTCEVT_ENABLE_MODE ((uint8_t) 0x01)
#define  RTCEVT_DISABLE_MODE ((uint8_t) 0x00)


#define  RTCEVT_MAX_NUM  ((uint8_t) 0x1F)//定时器事件数

//0x80000000 作为系统计时事件使用

	struct Array_Node
	{  
		uint32_t evt_id; 
	};

	struct SYD_sysTimer{
		 struct Array_Node Evt_Array_Node; 
		 void (*Timer_Evt_Handle)(void);//void是函数数组元素返回类型，*是数组参数类型
		 uint32_t Evt_Array_Iterval;	 
		 uint8_t Evt_Array_On_Off_Mode;
		 uint32_t Evt_Array_Trigger_Loop;
		 uint32_t Evt_Loop_Start_Point;
	};
	
	extern void SYD_Timer_Init(uint8_t event_num, struct SYD_sysTimer p_sysTimer[]);
	extern void Timer_Evt_Init(void);
	extern void Timer_Evt_Start(uint32_t evt_id_para);
	extern void Timer_Evt_Stop(uint32_t evt_id_para);
	extern void Timer_Evt_Clr(uint32_t evt_id_para);
	extern uint8_t Timer_Get_State(uint32_t evt_id_para);
	extern void Timer_Evt_Creat(uint32_t evt_id_para,uint32_t evt_interval_para,void *evt_handle_para,uint8_t evt_mode_para);

typedef enum {
    RTC_INT_CMP0 = 1,
    RTC_INT_CMP1 = 2,
    RTC_INT_TICK = 4,
	RTC_INT_SECOND = 8,
    RTC_INT_ALL  = 0xF,
    RTC_INT_NUM  = 4,
} RTC_INT_TYPE;

typedef void (* RTC_IRQ_CALLBACK) (RTC_INT_TYPE type);

#pragma pack(push, 1)
typedef union {
    struct {
        uint8_t  second;
        uint8_t  minute;
        uint8_t  hour;
        uint8_t  day;
    } decimal_format;
    uint8_t  u8[4];
    uint32_t u32;
} RTC_TIME_TYPE;
#pragma pack(pop)


	struct RTC_Array_Node
	{  
		uint32_t RTCEVT_id; 
	};

	struct SYD_sysRtc{
		 struct RTC_Array_Node RTCEVT_Array_Node; 
		 void (*RTC_Evt_Handle)(void);//void是函数数组元素返回类型，*是数组参数类型
		 uint32_t RTCEVT_Array_Iterval;	 
		 uint8_t RTCEVT_Array_On_Off_Mode;
		 uint32_t RTCEVT_Array_Trigger_Loop;
		 uint32_t RTCEVT_Loop_Start_Point;
	};
	
extern uint32_t RTC_RUN(void);
extern void RTC_SET(uint32_t Iterval);
extern void SYD_RTC_Init(uint8_t event_num, struct SYD_sysRtc p_sysTimer[]);
extern void RTC_EVT_Init(void);
extern void RTC_EVT_Start(uint32_t RTCEVT_id_para);
extern void RTC_EVT_Stop(uint32_t RTCEVT_id_para);
extern void RTC_EVT_Clr(uint32_t RTCEVT_id_para);
extern uint8_t RTC_Get_State(uint32_t RTCEVT_id_para);
extern void RTC_EVT_Creat(uint32_t RTCEVT_id_para,uint32_t RTCEVT_interval_para,void *RTCEVT_handle_para,uint8_t RTCEVT_mode_para);
	
extern	void rtc_set_interrupt_callback(RTC_IRQ_CALLBACK cb);
extern	void rtc_int_clear(RTC_INT_TYPE type);
extern	void rtc_int_enable(RTC_INT_TYPE type);
extern	void rtc_int_disable(RTC_INT_TYPE type);
extern	void rtc_start(void);
extern	void rtc_stop(void);
extern	void rtc_clear(void);
extern	void rtc_set_prescaler(uint32_t tick, bool adjust_seconds_bit);
extern	void rtc_set_seconds_bit(uint32_t order);
extern	RTC_TIME_TYPE rtc_get_compare(int id);
extern	void rtc_set_compare(int id, RTC_TIME_TYPE *time);
extern	RTC_TIME_TYPE rtc_get_calendar(void);
extern	void rtc_set_calendar(RTC_TIME_TYPE *time);
extern	bool rtc_status(void);
extern	uint32_t rtc_interrupt_status(void);
extern	void rtc_init(uint32_t tick,RTC_IRQ_CALLBACK cb);
extern void RTC_EVT_whole_minute_setid(uint32_t RTCEVT_id_para);
extern void RTC_EVT_whole_minute_adj(void);	
	
	
extern struct SYD_sysTimer syd_sysTimer[EVT_NUM];
extern void Timer_Evt_List(void);
extern struct SYD_sysRtc syd_rtc[RTCEVT_NUM];	
extern void RTC_Evt_List(void);	
	
extern uint32_t TIMER_EVT;
extern uint32_t RTC_EVT;
	
#endif
