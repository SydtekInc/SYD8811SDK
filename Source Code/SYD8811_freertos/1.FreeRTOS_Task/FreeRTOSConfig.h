/*
    FreeRTOS V6.0.5 - Copyright (C) 2010 Real Time Engineers Ltd.

    ***************************************************************************
    *                                                                         *
    * If you are:                                                             *
    *                                                                         *
    *    + New to FreeRTOS,                                                   *
    *    + Wanting to learn FreeRTOS or multitasking in general quickly       *
    *    + Looking for basic training,                                        *
    *    + Wanting to improve your FreeRTOS skills and productivity           *
    *                                                                         *
    * then take a look at the FreeRTOS eBook                                  *
    *                                                                         *
    *        "Using the FreeRTOS Real Time Kernel - a Practical Guide"        *
    *                  http://www.FreeRTOS.org/Documentation                  *
    *                                                                         *
    * A pdf reference manual is also available.  Both are usually delivered   *
    * to your inbox within 20 minutes to two hours when purchased between 8am *
    * and 8pm GMT (although please allow up to 24 hours in case of            *
    * exceptional circumstances).  Thank you for your support!                *
    *                                                                         *
    ***************************************************************************

    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation AND MODIFIED BY the FreeRTOS exception.
    ***NOTE*** The exception to the GPL is included to allow you to distribute
    a combined work that includes FreeRTOS without being obliged to provide the
    source code for proprietary components outside of the FreeRTOS kernel.
    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
    more details. You should have received a copy of the GNU General Public 
    License and the FreeRTOS license exception along with FreeRTOS; if not it 
    can be viewed here: http://www.freertos.org/a00114.html and also obtained 
    by writing to Richard Barry, contact details for whom are available on the
    FreeRTOS WEB site.

    1 tab == 4 spaces!

    http://www.FreeRTOS.org - Documentation, latest information, license and
    contact details.

    http://www.SafeRTOS.com - A version that is certified for use in safety
    critical systems.

    http://www.OpenRTOS.com - Commercial support, development, porting,
    licensing and training services.
*/

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#define configTICK_SOURCE FREERTOS_USE_SYSTICK
//#define configTICK_SOURCE FREERTOS_USE_RTC


/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE. 
 *
 * See http://www.freertos.org/a00110.html.
 *----------------------------------------------------------*/

//#define configUSE_PREEMPTION				1
//#define configUSE_IDLE_HOOK				0
//#define configUSE_TICK_HOOK				0
//#define configCPU_CLOCK_HZ				( ( unsigned long ) 64000000 )	
//#define configTICK_RATE_HZ				( ( portTickType ) 1000 )
//#define configMAX_PRIORITIES				( ( unsigned portBASE_TYPE ) 4 )
//#define configMINIMAL_STACK_SIZE			( ( unsigned short ) 64 )
////#define configTOTAL_HEAP_SIZE			( ( size_t ) ( 3328 ) )
////#define configTOTAL_HEAP_SIZE			( ( size_t ) ( 2048 ) )
//#define configTOTAL_HEAP_SIZE				( ( size_t ) ( 4096 ) )
//#define configMAX_TASK_NAME_LEN			( 5 )
//#define configUSE_TRACE_FACILITY			0
//#define configUSE_16_BIT_TICKS			0
//#define configIDLE_SHOULD_YIELD			1
//#define	configUSE_ALTERNATIVE_API		1
//#define configUSE_MUTEXES					1
//#define configUSE_RECURSIVE_MUTEXES		1
//#define configUSE_COUNTING_SEMAPHORES		1



#define configUSE_PREEMPTION 							1/* 置1：RTOS使用抢占式调度器；置0：RTOS使用协作式调度器（时间片）*/
#define configUSE_PORT_OPTIMISED_TASK_SELECTION 		0//优化优先级列表
#define configUSE_TICKLESS_IDLE 						0
#define configUSE_TICKLESS_IDLE_SIMPLE_DEBUG            0 /* See into vPortSuppressTicksAndSleep source code for explanation */
#define configCPU_CLOCK_HZ                              ( 64000000 )
#define configTICK_RATE_HZ                              1000
#define configMAX_PRIORITIES                            ( 10 )
#define configMINIMAL_STACK_SIZE                        ( 128 )
#define configTOTAL_HEAP_SIZE                           ( 1024*8 )
#define configMAX_TASK_NAME_LEN                         ( 5 )
#define configUSE_16_BIT_TICKS                          0
#define configIDLE_SHOULD_YIELD                         1 
#define configUSE_ALTERNATIVE_API                       0    /* Deprecated! */
#define configUSE_MUTEXES                               1
#define configUSE_RECURSIVE_MUTEXES                     1
#define configUSE_COUNTING_SEMAPHORES                   1

#define configQUEUE_REGISTRY_SIZE                       10/* 设置可以注册的信号量和消息队列个数 */
#define configUSE_QUEUE_SETS                            1 //启用队列
#define configUSE_TIME_SLICING                          0
#define configUSE_NEWLIB_REENTRANT                      0
#define configENABLE_BACKWARD_COMPATIBILITY             1

/* Hook function related definitions. */
#define configUSE_IDLE_HOOK                                                       0
#define configUSE_TICK_HOOK                                                       0
#define configCHECK_FOR_STACK_OVERFLOW                                            0
#define configUSE_MALLOC_FAILED_HOOK                                              0

/* Run time and task stats gathering related definitions. */
#define configGENERATE_RUN_TIME_STATS                                             0
#define configUSE_TRACE_FACILITY                                                  0
#define configUSE_STATS_FORMATTING_FUNCTIONS                                      0

/* Co-routine definitions. */
#define configUSE_CO_ROUTINES 							0
#define configMAX_CO_ROUTINE_PRIORITIES 	( 2 )



/* Software timer definitions. */
#define configUSE_TIMERS 													1
#define configTIMER_TASK_PRIORITY               ( 5 )
#define configTIMER_QUEUE_LENGTH                  32
#define configTIMER_TASK_STACK_DEPTH            ( 80 )



/* Set the following definitions to 1 to include the API function, or zero to exclude the API function. */
/* Optional functions - most linkers will remove unused functions anyway. */
#define INCLUDE_vTaskPrioritySet                   1
#define INCLUDE_uxTaskPriorityGet                  1
#define INCLUDE_vTaskDelete                        1
#define INCLUDE_vTaskSuspend                       1//Y
#define INCLUDE_xResumeFromISR                     1
#define INCLUDE_vTaskDelayUntil                    1//Y
#define INCLUDE_vTaskDelay                         1
#define INCLUDE_xTaskGetSchedulerState             1
#define INCLUDE_xTaskGetCurrentTaskHandle          1
#define INCLUDE_uxTaskGetStackHighWaterMark        1


#define INCLUDE_xTaskGetIdleTaskHandle             1
#define INCLUDE_xTimerGetTimerDaemonTaskHandle     1
#define INCLUDE_pcTaskGetTaskName                  1
#define INCLUDE_eTaskGetState                      1
#define INCLUDE_xEventGroupSetBitFromISR           1
#define INCLUDE_xTimerPendFunctionCall             1

/* Normal assert() semantics without relying on the provision of an assert.h
header file. */
#define configASSERT( x ) if( ( x ) == 0 ) { taskDISABLE_INTERRUPTS(); for( ;; ); }

/* The lowest interrupt priority that can be used in a call to a "set priority"
function. */
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY         0xf

/* The highest interrupt priority that can be used by any interrupt service
routine that makes calls to interrupt safe FreeRTOS API functions.  DO NOT CALL
INTERRUPT SAFE FREERTOS API FUNCTIONS FROM ANY INTERRUPT THAT HAS A HIGHER
PRIORITY THAN THIS! (higher priorities are lower numeric values. */
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY    _PRIO_APP_HIGH


/* Interrupt priorities used by the kernel port layer itself.  These are generic
to all Cortex-M ports, and do not rely on any particular library functions. */
#define configKERNEL_INTERRUPT_PRIORITY                 configLIBRARY_LOWEST_INTERRUPT_PRIORITY
/* !!!! configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to zero !!!!

See http://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html. */
#define configMAX_SYSCALL_INTERRUPT_PRIORITY            configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY

/* Definitions that map the FreeRTOS port interrupt handlers to their CMSIS
standard names - or at least those used in the unmodified vector table. */
/* Definitions that map the FreeRTOS port interrupt handlers to their CMSIS
standard names - or at least those used in the unmodified vector table. */
#define vPortSVCHandler 	SVC_Handler
#define xPortPendSVHandler 	PendSV_Handler
/*-----------------------------------------------------------
 * Settings that are generated automatically
 * basing on the settings above
 */
#if (configTICK_SOURCE == FREERTOS_USE_SYSTICK)
// do not define configSYSTICK_CLOCK_HZ for SysTick to be configured automatically to CPU clock source
    #define xPortSysTickHandler     SysTick_Handler
	
#elif (configTICK_SOURCE == FREERTOS_USE_RTC)
    #define configSYSTICK_CLOCK_HZ  ( 32768UL )
    #define xPortSysTickHandler     RTC_IRQHandler
#else
    #error  Unsupported configTICK_SOURCE value
#endif



/** Implementation note:  Use this with caution and set this to 1 ONLY for debugging
 * ----------------------------------------------------------
     * Set the value of configUSE_DISABLE_TICK_AUTO_CORRECTION_DEBUG to below for enabling or disabling RTOS tick auto correction:
     * 0. This is default. If the RTC tick interrupt is masked for more than 1 tick by higher priority interrupts, then most likely
     *    one or more RTC ticks are lost. The tick interrupt inside RTOS will detect this and make a correction needed. This is needed
     *    for the RTOS internal timers to be more accurate.
     * 1. The auto correction for RTOS tick is disabled even though few RTC tick interrupts were lost. This feature is desirable when debugging
     *    the RTOS application and stepping though the code. After stepping when the application is continued in debug mode, the auto-corrections of
     *    RTOS tick might cause asserts. Setting configUSE_DISABLE_TICK_AUTO_CORRECTION_DEBUG to 1 will make RTC and RTOS go out of sync but could be
     *    convenient for debugging.
     */
#define configUSE_DISABLE_TICK_AUTO_CORRECTION_DEBUG     0


/* BLE Task*/
#define THREAD_BLE_STACK_SIZE	configMINIMAL_STACK_SIZE	
#define THREAD_BLE_LL_PRIORITY	( tskIDLE_PRIORITY + 1 )
#define THREAD_BLE_LL_QUEUE		12
#define THREAD_BLE_LL_QUEUE_SIZE	1

#endif /* FREERTOS_CONFIG_H */

