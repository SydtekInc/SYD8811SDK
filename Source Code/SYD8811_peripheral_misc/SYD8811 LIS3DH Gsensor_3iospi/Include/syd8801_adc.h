#ifndef _SYD8801_ADC_H_
#define _SYD8801_ADC_H_

#include "ARMCM0.h"

void adc_init(uint8_t cha);
uint16_t get_adcval(void);
void adc_close(void);
void adc_open(void);

#endif
