#ifndef _DEBUG_H_
#define _DEBUG_H_

#include "ARMCM0.h"

#define DBGPRINTF(s)	 							dbg_printf s
#define DBGHEXDUMP(title,buf,sz)	 				dbg_hexdump(title,buf,sz)

#ifdef _DEBUG_C_
#else
	extern void dbg_init(void);
	extern void dbg_printf(char *format,...) ;
	extern void dbg_hexdump(char *title, uint8_t *buf, uint16_t sz);
#endif
#endif

