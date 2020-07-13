/*
UART�����ļ�

���ߣ�����ʢԴ��Ƽ����޹�˾
���ڣ�2016/7/8
*/
#include "syd8801_uart.h"
#include "syd8801_gpio.h"

//�Ĵ�������
UART_CTRL_TYPE * UART_0_CTRL = ((UART_CTRL_TYPE *) UART_0_CTRL_BASE);
UART_CTRL_TYPE * UART_1_CTRL = ((UART_CTRL_TYPE *) UART_1_CTRL_BASE);

//�ص���������
static void (*uartrx_callback[2])(void);

/*
UART0���ú���
����: uint8_t flowctrl Ӳ����ʱ��ʹ�� 0��ʧ��Ӳ���� 1��ʹ��Ӳ����
			uint8_t baud  �����ʲ��� ����ֵ�鿴UART_BAUD_SELö�ٶ���
			void *  p_callback �����жϻص�����
������uart_0_init(UART_RTS_CTS_DISABLE, UART_BAUD_115200, &uartRx_callback);
*/
void uart_0_init(uint8_t flowctrl, uint8_t baud, void *  p_callback)
{
	// pin26 & pin27  configured to uart mode.	
	PIN_CONFIG->PIN_26_SEL = PIN_SEL_UART_0_RXD;
	PIN_CONFIG->PIN_27_SEL = PIN_SEL_UART_0_TXD;	
	
	UART_0_CTRL->BAUDSEL = baud;
	UART_0_CTRL->FLOW = flowctrl;
	UART_0_CTRL->INT_MASK = 1;   //��Ϊ������debug ���Բ���Ҫ����
	uartrx_callback[0] = ((void (*)(void))p_callback);
	NVIC_EnableIRQ(UART0_IRQn);
}
/*
UART0����д����
����: uint8_t data Ҫ���͵�����
*/
void uart_0_write(uint8_t data)
{
	UART_0_CTRL->SUB= data;

	while(UART_0_CTRL->T1 == 0);
		
	UART_0_CTRL->T1  = 0;
}
/*
UART0���ڶ�����
����ֵ: uint8_t ���յ�������
*/
uint8_t uart_0_read(void)
{
	return UART_0_CTRL->SUB;	
}
/*
UART0�����жϺ���
���ûص�����
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
UART0���ڹرպ������������˼��ʧ�ܴ����ж�
*/
void uart_0_close()
{
	NVIC_DisableIRQ(UART0_IRQn);
}
/*
UART0���ú���
����: uint8_t flowctrl Ӳ����ʹ��  ע�⣺����UART1��û��Ӳ���� �������������ò���
			uint8_t baud  �����ʲ��� ����ֵ�鿴UART_BAUD_SELö�ٶ���
			void *  p_callback �����жϻص�����
������uart_1_init(UART_RTS_CTS_DISABLE, UART_BAUD_115200, &uartRx_callback);
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
UART1����д����
����: uint8_t data Ҫ���͵�����
*/
void uart_1_write(uint8_t data)
{
	UART_1_CTRL->SUB= data;

	while(UART_1_CTRL->T1 == 0);
		
	UART_1_CTRL->T1  = 0;
}
/*
UART1���ڶ�����
����ֵ: uint8_t ���յ�������
*/
uint8_t uart_1_read(void)
{
	return UART_1_CTRL->SUB;	
}
/*
UART1�����жϺ���
���ûص�����
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
UART1���ڹرպ������������˼��ʧ�ܴ����ж�
*/
void uart_1_close()
{
	NVIC_DisableIRQ(UART1_IRQn);
}
/*
UART0�����ַ������� 
������unsigned char *date Ҫ���͵��ַ���ָ��
*/
void USART0_Write_String(unsigned char *date)
{
	while((*(unsigned char*)date!='\0')&&(*(unsigned char*)date<=0X7F))    //�ж��Ƿ�д�� 5F7F0
	{
		uart_0_write(*date);
		date++;
	}		
}
/*
UART1�����ַ������� 
������unsigned char *date Ҫ���͵��ַ���ָ��
*/
void USART1_Write_String(unsigned char *date)
{
	while((*(unsigned char*)date!='\0')&&(*(unsigned char*)date<=0X7F))    //�ж��Ƿ�д�� 5F7F0
	{
		uart_1_write(*date);
		date++;
	}		
}
