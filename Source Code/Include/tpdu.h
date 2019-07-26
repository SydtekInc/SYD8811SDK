/*
 * TPDU module
 *   TPDU state machine
 *   TPDU request helper
 */

#ifndef _TPDU_H_
#define _TPDU_H_

#include "armcm0.h"

enum HEADER_INDEX {
    CLA,
    INS,
    P1,
    P2,
    P3,
    HEADER_SIZE
};

enum STATUS_INDEX {
    SW1,
    SW2,
    SW_SIZE
};

typedef struct {
    uint8_t header[HEADER_SIZE];
    bool    writeCommand;
    uint8_t data[256];
    uint8_t sw[SW_SIZE];
} TPDU_COMMAND;

/* TPDU task state definition */
typedef enum {
    TT_IDLE,
    TT_SEND_HEADER,
    TT_DETERMINE_PROCEDURE,
    TT_WAIT_FOR_TX_FINISH,
    TT_DATA,
    TT_ERROR,
} TPDU_TASK_STATE;

/* TPDU callback definition */
typedef void (*TPDU_CALLBACK)(TPDU_COMMAND *command);

bool tpdu_request(TPDU_COMMAND *command, TPDU_CALLBACK callback);
void tpdu_reset(void);
TPDU_TASK_STATE tpdu_task(bool tx_finished);

#endif //_TPDU_H_

