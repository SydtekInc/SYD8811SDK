#ifndef _LED_H_
#define _LED_H_

#include "ARMCM0.h"

#define LED0 BIT0
#define LED1 BIT1
#define LED2 BIT2
#define LED3 BIT3
#define LED4 BIT4
#define LED5 BIT5
#define LED6 BIT6
#define LED7 BIT7
#define LEDALL (BIT0 | BIT1 | BIT2 | BIT3 |BIT4 | BIT5 | BIT6 | BIT7)

void led_config(uint32_t led);
void led_open(uint32_t led);
void led_close(uint32_t led);
void led_turn(uint32_t led);

#endif
