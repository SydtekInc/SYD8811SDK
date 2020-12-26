#include "config.h"
#include "uart.h"
#include "uart_protocol.h"

void uartRx_callback(void)
{
	uint8_t cnt,i,temp[4];
	uart_0_read(&cnt,temp);
	
	for(i=0;i<cnt;i++)
	{
		uart_rx_buf.data[uart_rx_buf.header]=temp[i];
		uart_rx_buf.header++;
		if(uart_rx_buf.header >= MAX_RX_LENGTH)
		{
			uart_rx_buf.header = 0;
		}
	}
}

//处理app的写到 UART service的数据
void uart_cmd(uint8_t *p_cmd, uint8_t sz)
{
	unsigned char i;
	
	for(i=0; i<sz; i++) 
	{
		uart_0_write(p_cmd[i]);
	}
}


