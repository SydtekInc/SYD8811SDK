#define  _TIMER_HANDLER_C_
#include "calender.h"
#include "softtimer.h"
#include "DebugLog.h"

struct SYD_sysTimer syd_sysTimer[EVT_NUM] = {0};


#ifdef	EVT_2S
void Timer_Evt_2s(void)
{
	TIMER_EVT|=EVT_2S;
}
#endif

#ifdef	EVT_1S_OTA
void Timer_EVT_1S_OTA(void)
{
	TIMER_EVT|=EVT_1S_OTA;
}
#endif

#ifdef	EVT_10MS
void Timer_EVT_10MS(void)
{
	TIMER_EVT|=EVT_10MS;
}
#endif


void Timer_Evt_List(void)
{
#ifdef	EVT_2S
	Timer_Evt_Creat(EVT_2S,2000,Timer_Evt_2s,EVT_DISABLE_MODE);	 	 //生成触发事件
#endif
	
#ifdef	EVT_1S_OTA
	Timer_Evt_Creat(EVT_1S_OTA,2000,Timer_EVT_1S_OTA,EVT_DISABLE_MODE);	 	 //生成触发事件
#endif
	
#ifdef	EVT_10MS
	Timer_Evt_Creat(EVT_10MS, 10, Timer_EVT_10MS, EVT_DISABLE_MODE);	 	 //生成触发事件
#endif	
}

