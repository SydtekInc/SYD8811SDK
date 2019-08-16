#ifndef _IR_Tx__H__
#define _IR_Tx__H__

#include "ARMCM0.h"

#define 	IR_CARR_FREQ			37910UL

extern void IR_Tx_Init(void);
extern void IR_Tx_SendData(uint16_t usrCode, uint8_t data);
uint8_t getTrState(void);

#endif

