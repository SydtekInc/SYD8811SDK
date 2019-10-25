/*
Rtt 头文件

作者：北京盛源达科技有限公司
日期：2018/5/9
*/
#ifndef __H_DEBUG_LOG_H__
#define __H_DEBUG_LOG_H__

#include "config.h"

#ifdef _SYD_RTT_DEBUG_


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


//#include "TypeDef.h"
//#include "PlatformConfig.h"
#if defined(_SYD_RTT_DEBUG_)
#define PLATFORM_DEBUG		(1)
#endif


/* debug log总开关 */
#if (defined(PLATFORM_DEBUG) && (1==PLATFORM_DEBUG))
	#define DEBUG_ENABLE	(1)
#else
	#define DEBUG_ENABLE	(0)
#endif


/* debug log输出方式类型定义 */
#define DEBUG_LOG_TYPE_NULL		(0)
#define DEBUG_LOG_TYPE_UART		(1)		// 通过uart输出debug log
#define DEBUG_LOG_TYPE_RTT		(2)		// 通过segger rtt打印debug log
#define DEBUG_LOG_TYPE_SWO		(3)		// 通过swo接口打印debug log
/* 定义debug log的打印方式 */
#define DEBUG_LOG_TYPE		(DEBUG_LOG_TYPE_RTT)


/* 定义debug log分类掩码 */
#define DEBUG_LOG_MASK_ALL			((uint32_t)0xFFFFFFFF)
#define DEBUG_LOG_MASK_NONE			((uint32_t)0x00000000)
#define DEBUG_LOG_MASK_ERROR		(((uint32_t)1)<<31)		// 错误log掩码
#define DEBUG_LOG_MASK_WARNING		(((uint32_t)1)<<30)		// 警告log掩码
#define DEBUG_LOG_MASK_NOTE			(((uint32_t)1)<<29)		// 提醒log掩码
#define DEBUG_LOG_MASK_TRACK_STAMP	(((uint32_t)1)<<28)		// 足迹标记log掩码
#define DEBUG_LOG_MASK_ERROR_WARNING		(DEBUG_LOG_MASK_ERROR | DEBUG_LOG_MASK_WARNING)
#define DEBUG_LOG_MASK_ERROR_NOTE 			(DEBUG_LOG_MASK_ERROR | DEBUG_LOG_MASK_NOTE)
#define DEBUG_LOG_MASK_ERROR_WARNING_NOTE 	(DEBUG_LOG_MASK_ERROR | DEBUG_LOG_MASK_WARNING | DEBUG_LOG_MASK_NOTE)
#define DEBUG_LOG_MASK_WARNING_NOTE			(DEBUG_LOG_MASK_WARNING | DEBUG_LOG_MASK_NOTE)

/* 定义默认debug log输出分类掩码 */
#ifndef DEBUG_LOG_MASK_DEFAULT
//	#define DEBUG_LOG_MASK_DEFAULT		(DEBUG_LOG_MASK_NONE)
	#define DEBUG_LOG_MASK_DEFAULT		(DEBUG_LOG_MASK_ERROR_WARNING_NOTE)
#endif /* DEBUG_LOG_MASK_DEFAULT */


#if (defined(DEBUG_ENABLE) && (1==DEBUG_ENABLE))
	#if (DEBUG_LOG_TYPE == DEBUG_LOG_TYPE_UART)
		/* 通过uart打印debug log */
		#error "Do Not Support Debug Log Use Uart."
//		#define CONFIG_UART_ENABLE
//		#include "debug.h"
//		#define QPRINTF(...)	dbg_printf_sel(0, __VA_ARGS__)
	#elif (DEBUG_LOG_TYPE == DEBUG_LOG_TYPE_RTT)
		/* 通过segger rtt打印debug log */
		#include "SEGGER_RTT.h"
		#include "SEGGER_RTT_Conf.h"
		#define DebugLogInit()		SEGGER_RTT_Init()
		#define QPRINTF(...)		SEGGER_RTT_printf(0, __VA_ARGS__)
		#define Qhexdump(title,buf, sz)		SEGGER_RTT_hexdump(0,title,buf,sz)
	#elif (DEBUG_LOG_TYPE == DEBUG_LOG_TYPE_SWO)
		/* 通过swo接口打印debug log */
		#error "Do Not Support Debug Log Use SWO."
	#else
		#define QPRINTF(...)
	#endif

	#define LogMask(mask, ...)		\
			do{	\
				if(mask & DEBUG_LOG_MASK_DEFAULT)	\
				{	\
					QPRINTF(__VA_ARGS__);	\
				}	\
			}while(0)
										
	#define LogError(...)		\
			do{	\
				if(DEBUG_LOG_MASK_ERROR & DEBUG_LOG_MASK_DEFAULT)	\
				{	\
					QPRINTF("Error:%s:L%d:", __FUNCTION__, __LINE__);	\
					QPRINTF(__VA_ARGS__);	\
				}	\
			}while(0)

	#define LogWarning(...)		\
			do{	\
				if(DEBUG_LOG_MASK_WARNING & DEBUG_LOG_MASK_DEFAULT)	\
				{	\
					QPRINTF("Warning:%s:L%d:", __FUNCTION__, __LINE__);	\
					QPRINTF(__VA_ARGS__);	\
				}	\
			}while(0)
									
	#define LogNote(...)		\
			do{	\
				if(DEBUG_LOG_MASK_NOTE & DEBUG_LOG_MASK_DEFAULT)	\
				{	\
					QPRINTF("Note:");	\
					QPRINTF(__VA_ARGS__);	\
				}	\
			}while(0)
									
	#define LogLevel(level, ...)	\
			do{	\
				if(level > 31)	\
				{	\
					LogError("Debug Log Level Error!!!\n");	\
				}	\
				else	\
				{	\
					LogMask(((uint32_t)1)<<level, "[%d]:", level);		\
					LogMask(((uint32_t)1)<<level, __VA_ARGS__);	\
				}	\
			}while(0)

	/* 足迹标记Log */
	#define LogTrackStamp()		\
			do{	\
				if(DEBUG_LOG_MASK_TRACK_STAMP & DEBUG_LOG_MASK_DEFAULT)	\
				{	\
					QPRINTF("Track:%s : %s : L%d\n", __FILE__, __FUNCTION__, __LINE__);	\
				}	\
			}while(0)

	/* 兼容SYD8821 SDK中定义的debug */
	#undef DBGPRINTF
	#define DBGPRINTF(...)		\
			do{	\
				QPRINTF(__VA_ARGS__);	\
			}while(0)

	#undef DBG
	#define DBG(...)	\
			do{	\
				QPRINTF(__VA_ARGS__);	\
			}while(0)
	#undef dbg_printf
	#define dbg_printf(...)	\
			do{	\
				QPRINTF(__VA_ARGS__);	\
			}while(0)
	#undef DBGHEXDUMP		
	#define DBGHEXDUMP(title,buf, sz)	\
	do{	\
		Qhexdump(title, buf,sz);	\
	}while(0) 		
										
#else
	/* DEBUG_ENABLE关闭 */
	#define DebugLogInit()
	#define QPRINTF(...)
	#define LogMask(mask, ...)
	#define LogError(...)
	#define LogWarning(...)
	#define LogNote(...)
	#define LogLevel(level, ...)
	#define LogTrackStamp()

	/* 兼容SYD8821 SDK中定义的debug */
	#undef DBGPRINTF
	#define DBGPRINTF(...)

	#undef DBG
	#define DBG(...)
	
#endif /* #if (defined(DEBUG_ENABLE) && (1==DEBUG_ENABLE)) */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */



#endif /* _SYD_RTT_DEBUG_ */
#endif /* ___DEBUG_LOG_H___ */


