/*
串口调试操作文件

作者：北京盛源达科技有限公司
日期：2016/7/8
*/
#include "syd8801_debug.h"
#include "syd8801_uart.h"
#include <stdarg.h>
#include <stdio.h>


#define MAX_FORMAT_BUFFER_SIZE	(128)
static uint8_t s_formatBuffer[MAX_FORMAT_BUFFER_SIZE];

void dbg_init(void)
{
	uart_0_init(UART_RTS_CTS_DISABLE, UART_BAUD_115200, NULL);
}
void dbg_printf(char *format,...)
{
	uint8_t iWriteNum = 0,i=0;	
	va_list  ap;
	
	if(!format)
		return;
	
	va_start(ap,format);

	iWriteNum = vsprintf((char *)s_formatBuffer,format,ap);

	va_end(ap);
	
	if(iWriteNum > MAX_FORMAT_BUFFER_SIZE)
		iWriteNum = MAX_FORMAT_BUFFER_SIZE;
	
	for(i=0;i<iWriteNum;i++){
		uart_0_write(s_formatBuffer[i]);
	}
}

void dbg_hexdump(char *title, uint8_t *buf, uint16_t sz)
{
	int i = 0;
	
	if (title)
		dbg_printf((title));

	for(i = 0; i < sz; i++) 
	{
  		if((i%8) == 0)
			dbg_printf("[%04x] ",(uint16_t)i);

		dbg_printf("%02x ",(uint16_t)buf[i]);

		if(((i+1)%8) == 0)
			dbg_printf("\r\n");

	 } 

	if((i%8) != 0)
		dbg_printf("\r\n");
}

