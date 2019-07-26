#ifndef _WDT_H_
#define _WDT_H_

#define  _WDT_

#include "ARMCM0.h"

#ifdef _WDT_
	extern void wdt_enable(uint16_t count);
	extern void wdt_clear(void);
	extern void wdt_disable(void);

#endif
#endif

