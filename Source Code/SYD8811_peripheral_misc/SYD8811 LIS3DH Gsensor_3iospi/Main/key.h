#ifndef _KEY_H_
#define _KEY_H_

#include "ARMCM0.h"

#define KEY0 BIT8
#define KEY1 BIT9
#define KEY2 BIT10
#define KEY3 BIT11

extern uint8_t key_sta;

void key_config(void);
uint8_t get_key(void);
void keylong_config(void);

#endif
