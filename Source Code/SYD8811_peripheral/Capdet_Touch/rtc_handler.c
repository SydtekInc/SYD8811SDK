/*
*定时器事件:
*SYD8821   2018-4-13
*SYD-TEK
*
*/

#define  _RTC_HANDLER_C_
#include "softtimer.h"
#include <string.h>
#include "DebugLog.h"

struct SYD_sysRtc syd_rtc[RTCEVT_NUM] = {0};
struct SYD_HISTORY_SETTING  syd_history_setting_str;

#ifdef	RTCEVT_whole_minute
void RTC_Evt_whole_minute(void)
{
	RTC_EVT|=RTCEVT_whole_minute;
}
#endif

#ifdef	RTCEVT_10S
void RTC_Evt_10S(void)
{
	RTC_EVT|=RTCEVT_10S;
}
#endif

#ifdef	RTCEVT_185S
void RTC_Evt_185s(void)
{
	RTC_EVT|=RTCEVT_185S;
}
#endif

void RTC_Evt_List(void)
{
#ifdef	RTCEVT_whole_minute
//该定时器事件比较特殊，是一个整分钟的定时器事件，用于处理整分钟的任务，比如闹钟等，该事件默认设置的长度是60（1分钟）但是当有时间调整的事件发生的时候，
//比如APP更新了本地的事件，那么该定时器由RTC时钟系统把该事件自动调整回整分钟对齐，但是不可避免的造成当前分钟该事件的长度并不是1分钟了，所以该事件并不
//适合用于1分钟的准时定时器！
RTC_EVT_Creat(RTCEVT_whole_minute,60,RTC_Evt_whole_minute,RTCEVT_DISABLE_MODE);
RTC_EVT_whole_minute_setid(RTCEVT_whole_minute);	
#endif
	
#ifdef	RTCEVT_10S
	RTC_EVT_Creat(RTCEVT_10S,5,RTC_Evt_10S,RTCEVT_DISABLE_MODE);	 	 //生成触发事件
#endif

#ifdef	RTCEVT_185S
	RTC_EVT_Creat(RTCEVT_185S,185,RTC_Evt_185s,RTCEVT_DISABLE_MODE);		 //生成触发事件
#endif


#ifdef	RTCEVT_whole_minute
RTC_EVT_Start(RTCEVT_whole_minute);
#endif
#ifdef	RTCEVT_10S
	RTC_EVT_Start(RTCEVT_10S);
#endif

#ifdef	RTCEVT_185S
	RTC_EVT_Start(RTCEVT_185S);
#endif

}

