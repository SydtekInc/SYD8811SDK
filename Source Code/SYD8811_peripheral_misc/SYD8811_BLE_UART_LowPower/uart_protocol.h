#ifndef _UART_PROTOCOL_H_
#define _UART_PROTOCOL_H_

#include "config.h"

extern uint8_t uart_state;

extern void uartRx_callback(void);
extern void uart_cmd(uint8_t *p_cmd, uint8_t sz);

#endif

