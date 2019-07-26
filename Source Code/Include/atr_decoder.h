#ifndef _ATR_DECODER_H_
#define _ATR_DECODER_H_

#include "armcm0.h"
#include "sc_reader.h"

#define ATR_MAX_T_LENGTH    (31)
#define DEFAULT_FD          (0x11)

#pragma pack(push, 1)
typedef struct {
    uint8_t TS;
    uint8_t T0;
    uint8_t T[ATR_MAX_T_LENGTH];
	//
    uint8_t Check;
    uint8_t ILength;	//Interface characters length
    uint8_t HLength;	//Historical characters length
    uint8_t TotalLength;
    uint8_t Th_Start;
} SC_ATR;
#pragma pack(pop)

void atr_reset(void);
bool atr_decode(SC_ATR *atr);
uint8_t atr_decoder_get_extra_guard_time(void);
uint8_t atr_decoder_get_waiting_integer(void);
bool atr_decoder_get_clock_stop(bool *high);
bool atr_decoder_allow_pps(void);
bool atr_decoder_allow_switch_mode(void);
uint8_t atr_decoder_get_protocol(void);
uint8_t atr_decoder_get_FD(void);

#endif //_ATR_DECODER_H_
