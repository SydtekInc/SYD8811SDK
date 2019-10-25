#include "tpdu.h"
#include "debug.h"
#include "queue.h"
#include <string.h>
#include "sc_reader.h"

static int residual_size;
static TPDU_TASK_STATE state;
static TPDU_CALLBACK notification;
static TPDU_COMMAND *command;

__STATIC_INLINE void tpdu_done(void);

bool tpdu_request(TPDU_COMMAND *c, TPDU_CALLBACK callback)
{
    // New request can be issue if in IDLE
    if (state != TT_IDLE || c == NULL)
        return false;
    
    command = c;
    state = TT_SEND_HEADER;
    notification = callback;
    
    return true;
}

TPDU_TASK_STATE tpdu_task(bool tx_finished)
{
    static uint8_t *buf;
    static uint8_t procedure;
    static uint8_t next_data_size;

    switch (state) {
        case TT_IDLE:
            // Nothing to do
            break;
        case TT_SEND_HEADER:
            sc_reader_send(command->header, sizeof(command->header));
            buf = command->data;
            next_data_size = 0;
            
            residual_size = command->header[P3];
            if (!command->writeCommand && residual_size == 0) // RX special size handle
                residual_size = 256;
            // Wait for Header to be sent
            state = TT_WAIT_FOR_TX_FINISH;
            break;
        case TT_WAIT_FOR_TX_FINISH:
            if (tx_finished) {
                // TX is done, check procedure bytes
                state = TT_DETERMINE_PROCEDURE;
            }
            break;
        case TT_DETERMINE_PROCEDURE:
            if (sc_reader_get(&procedure, 1) && procedure != 0x60) {
                // Status Bytes
                uint8_t tmp = procedure & 0xF0;
                if ((tmp == 0x60) || (tmp == 0x90)) { // SW1
                    command->sw[SW1] = procedure;
                    // polling SW2, should be received already
                    while(!sc_reader_get(&command->sw[SW2], 1));
                    tpdu_done();
                }
                else if (residual_size) { // Need data
                    state = TT_DATA;
                    if (procedure == command->header[INS]) { // All data
                        next_data_size = residual_size;
                    }
                    else if (procedure == (command->header[INS] ^ 0xFF)){ // Next byte
                        next_data_size = 1;
                    }
                    else
                        state = TT_ERROR;
                    residual_size -= next_data_size;
                }
                else
                    state = TT_ERROR;
            }
            break;
        case TT_DATA:
            // Process data if command requires data transfer
            if (next_data_size) {
                if (command->writeCommand) { // TX
                    sc_reader_send(buf, next_data_size);
                    buf += next_data_size;
                    // Wait for TX finish
                    state = TT_WAIT_FOR_TX_FINISH;
                }
                else if (sc_reader_get(buf, next_data_size)) { // RX
                    buf += next_data_size;
                    // All data received, check Status bytes
                    state = TT_DETERMINE_PROCEDURE;
                }
            }
            else {
                state = TT_ERROR;
            }
            break;
        default:
            break;
    }
    return state;
}

/* Trigger callback for TPDU finish */
__STATIC_INLINE void tpdu_done(void)
{
    tpdu_reset();
    if (notification) {
        notification(command);
    }
}

void tpdu_reset(void)
{
    state = TT_IDLE;
}
