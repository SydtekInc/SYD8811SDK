#ifndef _DEBUG_H_
#define _DEBUG_H_

#include "ARMCM0.h"
#include "config.h"



#ifdef _DEBUG_
	#define DBGPRINTF_TIMER(s)	 				dbg_printf s
	#define DBGPRINTF(...)	 						dbg_printf( __VA_ARGS__)
	#define DBGHEXDUMP(title,buf,sz)	 	dbg_hexdump(title,buf,sz)

	extern void dbg_init(void);
	extern void dbg_printf(char *format,...) ;
	extern void dbg_hexdump(char *title, uint8_t *buf, uint16_t sz);
#else
	#ifndef _SYD_RTT_DEBUG_
		#define DBGPRINTF_TIMER(s)	 	 
		//#define DBGPRINTF_TIMER(s)
		#define DBGPRINTF(...)	 		
		#define DBGHEXDUMP(title,buf,sz) 
	#endif
#endif

#endif
