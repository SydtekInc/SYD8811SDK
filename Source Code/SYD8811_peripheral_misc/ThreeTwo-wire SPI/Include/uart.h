#ifndef _UART_H_
#define _UART_H_

#include "ARMCM0.h" 

enum UART_BAUD_SEL {
	UART_BAUD_1200		= 0x00,
	UART_BAUD_2400		= 0x01,
	UART_BAUD_4800		= 0x02,
	UART_BAUD_9600		= 0x03,
	UART_BAUD_14400		= 0x04,
	UART_BAUD_19200		= 0x05,
	UART_BAUD_38400		= 0x06,
	UART_BAUD_57600		= 0x07,
	UART_BAUD_115200		= 0x08,
	UART_BAUD_230400		= 0x09,
	UART_BAUD_460800		= 0x0A,
	UART_BAUD_921600		= 0x0B,
};

enum UART_FLOWCTRL {
	UART_RTS_CTS_ENABLE		= 0x01,
	UART_RTS_CTS_DISABLE		= 0x00,
};

#define	RX_BUF_LENGTH	128

typedef struct{
	uint8_t data[RX_BUF_LENGTH];
	uint32_t header,tail;
} Uart_Rx_Buf_t;

extern Uart_Rx_Buf_t uart_rx_buf;

extern void uart_0_init(void);
extern void uart_0_write(uint8_t  data);
extern void uart_0_read(uint8_t *pcnt, uint8_t *pbuf);
extern void uart_0_close(void);

extern void uart_1_init(void);
extern void uart_1_write(uint8_t  data);
extern void uart_1_read(uint8_t *pcnt, uint8_t *pbuf);
extern void uart_1_close(void);

#endif
