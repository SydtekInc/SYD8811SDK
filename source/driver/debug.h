#ifndef _DEBUG_H_
#define _DEBUG_H_

#include "ARMCM0.h"

#ifdef _DEBUG_
	#define DBGPRINTF_TIMER(s)			dbg_printf s
	#define DBGPRINTF(...)			 	dbg_printf( __VA_ARGS__)
	#define DBGHEXDUMP(title,buf,sz)	 	dbg_hexdump(title,buf,sz)

	void dbg_init(void);
	void dbg_printf(char *format,...);
	void dbg_hexdump(char *title, uint8_t *buf, uint16_t sz);
#else
	#ifndef _SYD_RTT_DEBUG_
		#define DBGPRINTF_TIMER(s)
		#define DBGPRINTF(...)	 		
		#define DBGHEXDUMP(title,buf,sz)
		#define dbg_init()
	#else
		#include"debug.h"
		#define dbg_init()	DebugLogInit()
	#endif
	
#endif

#endif
