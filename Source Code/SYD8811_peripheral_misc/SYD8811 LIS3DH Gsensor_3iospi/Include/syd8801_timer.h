#ifndef _SYD8801_TIMER_H_
#define _SYD8801_TIMER_H_

#include "ARMCM0.h"

extern TIMER_CTRL_TYPE * TIMER_CTRL;

extern void timer_0_enable(uint32_t interval, void *  p_callback); // 32.768KHz
extern void timer_0_disable(void);	
extern void timer_0_delay_32us(uint32_t cnt);
extern void timer_1_enable(uint32_t interval, void *  p_callback); // 32.768KHz
extern void timer_1_disable(void);	
extern void timer_2_enable(uint32_t interval, void *  p_callback); // 32.768KHz
extern void timer_2_disable(void);		

#endif


