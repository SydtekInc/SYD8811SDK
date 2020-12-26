#ifndef __USER_H__
#define __USER_H__

#include"system.h"

typedef void (*voidfunc)(void);

void msleep(uint32_t ms);
void msleepEx(voidfunc looper,uint32_t ms);
void msleepCustom(uint32_t ms);
bool queryMsleepEx(void);
void clrMsleepBits(void);
bool queryMsleep(void);
void stopSleep(void);

#endif
