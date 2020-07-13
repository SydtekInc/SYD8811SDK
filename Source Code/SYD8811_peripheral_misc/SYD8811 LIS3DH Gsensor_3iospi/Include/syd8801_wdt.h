#ifndef _WDT_H_
#define _WDT_H_

#include "ARMCM0.h"

extern WDT_CTRL_TYPE * WDT_CTRL;

extern void wdt_enable(uint16_t count); // 8 ms
extern void wdt_clear(void);
extern void wdt_disable(void);

#endif

