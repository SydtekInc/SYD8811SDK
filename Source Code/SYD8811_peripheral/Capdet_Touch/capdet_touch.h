#ifndef _UART_H_
#define _UART_H_

#include "ARMCM0.h"
#include "config.h"
#include "capdet_alg_lib.h"

#ifdef _USE_SYD_CAPDET_TOUCH_

#define SYD_CAPDET_TOUCH_CHANNEL BIT0

typedef struct
{
	uint8_t press;
} SYD_CAPDET_TOUCH_KEY_t;

typedef enum _CAPDET_TOUCH_FORCE_CALIBRATION_TYPE_
{
	CALIBRATION_LCD_WACKLUP = 0,
	CALIBRATION_LCD_SLEEP ,
} CAPDET_TOUCH_FORCE_CALIBRATION_TYPE;


extern SYD_CAPDET_TOUCH_KEY_t syd_capdet_key;

//void capdet_init_all_256(void);
void CAP_IRQHandler(void);
void TOUCH_IRQHandler(void);

//extern uint8_t capdet_calibration(void);
//extern uint8_t capdet_clear(void);
//extern uint8_t capdet_monitoring(uint8_t num);
//extern void capdet_init_reg(void);
//extern uint8_t capdet_judg(void);
void CapDetForceWakeUp(void);

extern uint8_t rtc_10s_cnt;
extern uint8_t capdet_calibration_state ;
extern uint8_t capdet_calibration_cnt ;
extern void CapDet_touch_force_Calibration(CAPDET_TOUCH_FORCE_CALIBRATION_TYPE type);


extern void capdet_init_all_256(void);


#endif

#endif
