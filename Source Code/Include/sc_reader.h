#ifndef _SC_READER_H_
#define _SC_READER_H_

#include "armcm0.h"

typedef enum SC_CALL_BACK_TYPE {
    ACT_CB,
    DACT_CB,
    CALL_BACK_NUM,
}SC_CB;

typedef enum SC_PPS_CALL_BACK_TYPE {
    PPS_REQUEST_CB,
    PPS_FAIL_CB,
    PPS_CALL_BACK_NUM,
}SC_PPS_CB;

typedef struct {
    uint8_t PPSS;
    uint8_t PPS[4];
    uint8_t PCK;
    uint8_t R_PPSS;
    uint8_t R_PPS[4];
    uint8_t R_PCK;
} SC_PPS;

typedef void (*CALL_BACK)(void);
typedef bool (*PPS_CALLBACK)(SC_PPS *pps);

extern void sc_reader_enable(void);
extern void sc_reader_disable(void);
extern void sc_reader_task(void);
extern void sc_reader_config_vcc_level(bool en);
extern void sc_reader_add_callback(CALL_BACK c, SC_CB type);
extern void sc_reader_add_PPS_callback(PPS_CALLBACK c, SC_PPS_CB type);
//
extern void sc_reader_send(uint8_t *buf, int length);
extern bool sc_reader_get(uint8_t *buf, int length);


extern void sc_reader_warm_reset(void);

#endif //_SC_READER_H_
