/*
UART操作文件

作者：北京盛源达科技有限公司
日期：2016/7/8
*/
#include "syd8801_uart.h"
#include "syd8801_gpio.h"

//寄存器定义
UART_CTRL_TYPE * UART_0_CTRL = ((UART_CTRL_TYPE *) UART_0_CTRL_BASE);
UART_CTRL_TYPE * UART_1_CTRL = ((UART_CTRL_TYPE *) UART_1_CTRL_BASE);

//回调函数定义
static void (*uartrx_callback[2])(void);

/*
UART0配置函数
参数: uint8_t flowctrl 硬件流时候使能 0：失能硬件流 1：使能硬件流
			uint8_t baud  波特率参数 具体值查看UART_BAUD_SEL枚举定义
			void *  p_callback 串口中断回调函数
举例：uart_0_init(UART_RTS_CTS_DISABLE, UART_BAUD_115200, &uartRx_callback);
*/
void uart_0_init(uint8_t flowctrl, uint8_t baud, void *  p_callback)
{
	// pin26 & pin27  configured to uart mode.	
	PIN_CONFIG->PIN_26_SEL = PIN_SEL_UART_0_RXD;
	PIN_CONFIG->PIN_27_SEL = PIN_SEL_UART_0_TXD;	
	
	UART_0_CTRL->BAUDSEL = baud;
	UART_0_CTRL->FLOW = flowctrl;
	UART_0_CTRL->INT_MASK = 1;   //因为这里是debug 所以不需要输入
	uartrx_callback[0] = ((void (*)(void))p_callback);
	NVIC_EnableIRQ(UART0_IRQn);
}
/*
UART0串口写函数
参数: uint8_t data 要发送的数据
*/
void uart_0_write(uint8_t data)
{
	UART_0_CTRL->SUB= data;

	while(UART_0_CTRL->T1 == 0);
		
	UART_0_CTRL->T1  = 0;
}
/*
UART0串口读函数
返回值: uint8_t 接收到的数据
*/
uint8_t uart_0_read(void)
{
	return UART_0_CTRL->SUB;	
}
/*
UART0串口中断函数
调用回调函数
*/
void UART0_IRQHandler()
{ 	
	if ((UART_0_CTRL->R1) == 1)
	{			
		UART_0_CTRL->R1  = 0;

		if(uartrx_callback[0] != 0)
			(*uartrx_callback[0])();
	}else{
		UART_0_CTRL->T1  = 0;
	}
}
/*
UART0串口关闭函数，这里的意思是失能串口中断
*/
void uart_0_close()
{
	NVIC_DisableIRQ(UART0_IRQn);
}
/*
UART0配置函数
参数: uint8_t flowctrl 硬件流使能  注意：这里UART1并没有硬件流 所以这里是无用参数
			uint8_t baud  波特率参数 具体值查看UART_BAUD_SEL枚举定义
			void *  p_callback 串口中断回调函数
举例：uart_1_init(UART_RTS_CTS_DISABLE, UART_BAUD_115200, &uartRx_callback);
*/
void uart_1_init(uint8_t flowctrl, uint8_t baud, void *  p_callback)
{
	// pin22 & pin23  configured to uart mode.	
	PIN_CONFIG->PIN_22_SEL = PIN_SEL_UART_1_RXD;
	PIN_CONFIG->PIN_23_SEL = PIN_SEL_UART_1_TXD;	
	
	UART_1_CTRL->BAUDSEL = baud;
//	UART_1_CTRL->FLOW = flowctrl;
	UART_1_CTRL->INT_MASK = 0;

	uartrx_callback[1] = ((void (*)(void))p_callback);
	
	NVIC_EnableIRQ(UART1_IRQn);
}
/*
UART1串口写函数
参数: uint8_t data 要发送的数据
*/
void uart_1_write(uint8_t data)
{
	UART_1_CTRL->SUB= data;

	while(UART_1_CTRL->T1 == 0);
		
	UART_1_CTRL->T1  = 0;
}
/*
UART1串口读函数
返回值: uint8_t 接收到的数据
*/
uint8_t uart_1_read(void)
{
	return UART_1_CTRL->SUB;	
}
/*
UART1串口中断函数
调用回调函数
*/
void UART1_IRQHandler()
{ 	
	if ((UART_1_CTRL->R1) == 1)
	{			
		UART_1_CTRL->R1  = 0;

		if(uartrx_callback[1] != 0)
			(*uartrx_callback[1])();
	}else{
		UART_1_CTRL->T1  = 0;
	}
}
/*
UART1串口关闭函数，这里的意思是失能串口中断
*/
void uart_1_close()
{
	NVIC_DisableIRQ(UART1_IRQn);
}
/*
UART0发送字符串函数 
参数：unsigned char *date 要发送的字符串指针
*/
void USART0_Write_String(unsigned char *date)
{
	while((*(unsigned char*)date!='\0')&&(*(unsigned char*)date<=0X7F))    //判断是否写完 5F7F0
	{
		uart_0_write(*date);
		date++;
	}		
}
/*
UART1发送字符串函数 
参数：unsigned char *date 要发送的字符串指针
*/
void USART1_Write_String(unsigned char *date)
{
	while((*(unsigned char*)date!='\0')&&(*(unsigned char*)date<=0X7F))    //判断是否写完 5F7F0
	{
		uart_1_write(*date);
		date++;
	}		
}
