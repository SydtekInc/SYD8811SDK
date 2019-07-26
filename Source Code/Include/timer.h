#ifndef _TIMER_H_
#define _TIMER_H_

#include "ARMCM0.h"

extern void timer_0_enable(uint32_t interval, void *  p_callback); // 32.768KHz
extern void timer_0_disable(void);
extern void timer_0_delay_32us(uint32_t cnt);
extern uint32_t timer_0_get_val(void);
extern void timer_1_enable(uint32_t interval, void *  p_callback); // 32.768KHz
extern void timer_1_disable(void);
extern uint32_t timer_1_get_val(void);
extern void timer_2_enable(uint32_t interval, void *  p_callback); // 32.768KHz
extern void timer_2_disable(void);
extern uint32_t timer_2_get_val(void);
extern void timer_3_enable(uint32_t interval, void *  p_callback); // 32.768KHz
extern void timer_3_disable(void);
extern uint32_t timer_3_get_val(void);

typedef enum {
    H_TIMER_PERSCALER_1 = 0,
    H_TIMER_PERSCALER_2 = 1,
	H_TIMER_PERSCALER_4 = 2,
	H_TIMER_PERSCALER_8 = 3,
	H_TIMER_PERSCALER_16 = 4,
	H_TIMER_PERSCALER_32 = 5,
	H_TIMER_PERSCALER_64 = 6,
	H_TIMER_PERSCALER_128 = 7,
} H_TIMER_PERSCALER_TYPE;

extern void Htimer_enable(uint16_t interval, void (*p_callback)(void));
extern uint16_t Htimer_get_val(void);
extern void Htimer_disable(void);

#endif


