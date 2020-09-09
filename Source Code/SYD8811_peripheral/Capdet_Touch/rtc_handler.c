/*
*��ʱ���¼�:
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
//�ö�ʱ���¼��Ƚ����⣬��һ�������ӵĶ�ʱ���¼������ڴ��������ӵ����񣬱������ӵȣ����¼�Ĭ�����õĳ�����60��1���ӣ����ǵ���ʱ��������¼�������ʱ��
//����APP�����˱��ص��¼�����ô�ö�ʱ����RTCʱ��ϵͳ�Ѹ��¼��Զ������������Ӷ��룬���ǲ��ɱ������ɵ�ǰ���Ӹ��¼��ĳ��Ȳ�����1�����ˣ����Ը��¼�����
//�ʺ�����1���ӵ�׼ʱ��ʱ����
RTC_EVT_Creat(RTCEVT_whole_minute,60,RTC_Evt_whole_minute,RTCEVT_DISABLE_MODE);
RTC_EVT_whole_minute_setid(RTCEVT_whole_minute);	
#endif
	
#ifdef	RTCEVT_10S
	RTC_EVT_Creat(RTCEVT_10S,5,RTC_Evt_10S,RTCEVT_DISABLE_MODE);	 	 //���ɴ����¼�
#endif

#ifdef	RTCEVT_185S
	RTC_EVT_Creat(RTCEVT_185S,185,RTC_Evt_185s,RTCEVT_DISABLE_MODE);		 //���ɴ����¼�
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

