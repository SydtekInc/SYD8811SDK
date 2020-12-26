#include"user.h"
#include"timer.h"


static volatile uint8_t sleep_bits;

void timerHander(void)
{
	sleep_bits|=0x01;
}

void stopSleep(void)
{
	timer_1_disable();
}

void clrMsleepBits(void)
{
	sleep_bits&=~0x01;
}

bool queryMsleep(void)
{
	bool res=((sleep_bits&0x01)==0?false:true);
	if(res==true) stopSleep();
	return res;
}

bool queryMsleepEx(void)
{
	return ((sleep_bits&0x01)==0?false:true);
}


void msleep(uint32_t ms)
{
	clrMsleepBits();
	timer_1_enable(TIMER_INPUT_FEQ/1000.0*ms,timerHander);
	while(!(sleep_bits&0x01));
	stopSleep();
}

void msleepEx(voidfunc looper,uint32_t ms)
{
	clrMsleepBits();
	timer_1_enable(TIMER_INPUT_FEQ/1000.0*ms,timerHander);
	while(!(sleep_bits&0x01)){
		looper();
	}
	stopSleep();
}

void msleepCustom(uint32_t ms)
{
	clrMsleepBits();
	timer_1_enable(TIMER_INPUT_FEQ/1000.0*ms,timerHander);
}


