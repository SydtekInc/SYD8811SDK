#ifndef _GPADC_H_
#define _GPADC_H_

#include "ARMCM0.h"

#define GPADC_CH_MAX	11

typedef enum{
	ONESHOT_MODE,
	AVE_MODE,
}GPADC_MODE;

extern void GPADC_Init(GPADC_MODE adc_mode);
extern void GPADC_start(void);
extern void GPADC_stop(void);
extern void GPADC_channel_sel(uint8_t ch);
extern uint16_t GPADC_get_value(void);

#endif

