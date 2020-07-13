/*
UART操作文件

作者：北京盛源达科技有限公司
日期：2016/7/8
*/
#include "uart.h"
#include "gpio.h"
#include "delay.h"

//寄存器定义
UART_CTRL_TYPE * UART_0_CTRL = ((UART_CTRL_TYPE *) UART_0_CTRL_BASE);
UART_CTRL_TYPE * UART_1_CTRL = ((UART_CTRL_TYPE *) UART_1_CTRL_BASE);

//-------------------------------------------------------------------------------------------------

/*
UART0配置函数
*/
void uart_0_init(void)
{
//	PIN_CONFIG->PIN_4_SEL = PIN_SEL_UART_RXD0;
//	PIN_CONFIG->PIN_5_SEL = PIN_SEL_UART_TXD0; 
	*((uint8_t *)(PWRON_BASE + 0x74)) = 0x03;	//pin 20 config uart0 rx
	*((uint8_t *)(PWRON_BASE + 0x75)) = 0x04;	//pin 21 config uart0 tx

	UART_0_CTRL->CLK_SEL = 0;		/* 1=32M, 0=16M */
	
	UART_0_CTRL->BAUDSEL = UART_BAUD_115200;
	UART_0_CTRL->FLOW_EN = UART_RTS_CTS_DISABLE;
	UART_0_CTRL->RX_INT_MASK = 1;	/* 1=MASK */
	UART_0_CTRL->TX_INT_MASK = 1;	/* 1=MASK */
	
	UART_0_CTRL->PAR_FAIL_INT_MASK = 1; /* 1=MASK */
	UART_0_CTRL->par_rx_en = 0;		/* Rx Parity check enable */
	UART_0_CTRL->par_rx_even = 1;	/* 1=Even, 0=Odd */
	
	UART_0_CTRL->par_tx_en = 0;		/* Tx Parity check enable */
	UART_0_CTRL->par_tx_even = 1;	/* 1=Even, 0=Odd */
	
	UART_0_CTRL->RI = 0;
	UART_0_CTRL->TI = 0;
	UART_0_CTRL->PAR_FAIL = 1;

	UART_0_CTRL->RX_FLUSH = 1;		/* clr rx fifo and set RX_FIFO_EMPTY */

	NVIC_EnableIRQ(UART0_IRQn);

	UART_0_CTRL->UART_EN = 1;
}

/*
UART0串口写函数
参数: uint8_t data 要发送的数据
注意: 使用这个函数不能使能Tx中断
*/
void uart_0_write(uint8_t data)
{
	UART_0_CTRL->TI = 0;
	UART_0_CTRL->TX_DATA = data;
	while(UART_0_CTRL->TI == 0);
	UART_0_CTRL->TI = 0;
}

/*
UART0串口读FIFO函数
参数:
	pcnt - 返回读到的字节数
	pbuf - 指向数据存放的buf
注意: FIFO长度为4，要求buf长度至少为4字节
*/
void uart_0_read(uint8_t *pcnt, uint8_t *pbuf)
{
	uint8_t i = 0;
	
	while(!UART_0_CTRL->RX_FIFO_EMPTY)
	{
		*(pbuf+i) = UART_0_CTRL->RX_DATA;
		i++;
	}

	*pcnt = i;
}

void uart_0_close(void)
{
	UART_0_CTRL->UART_EN = 0;
	NVIC_DisableIRQ(UART0_IRQn);
}

/*
UART0串口中断函数
*/
void UART0_IRQHandler(void)
{
	/*RX_FLUSH只能置位RX_FIFO_EMPTY,不能清除RI*/
	if ((UART_0_CTRL->RI) == 1)
	{
#if 0
		//关闭Tx中断  //这样会有丢失
		uart_0_write('R');
		UART_0_CTRL->RI = 0;
#elif 0
		//关闭Tx中断  //这样会有丢失
		uint8_t len, buf[4];
		uint8_t i;
		
		uart_0_read(&len, buf);
		UART_0_CTRL->RI = 0;

		for(i=0; i<len; i++)
		{
			uart_0_write(buf[i]);
		}
#endif
	}

	if ((UART_0_CTRL->TI) == 1)
	{
		//这里要注意:因为TI,RI的完成标志和中断标志共用，所以这里这样判断是有问题的,
		//也就是说，这里的TI并不代表是中断，只代表发送完成!	
		UART_0_CTRL->TI = 0;
		UART_0_CTRL->TX_DATA = 'T';
#if 1
		//仅供测试
		delay_ms(50);
		while(1);
#endif
	}

	if((UART_0_CTRL->PAR_FAIL) == 1)
	{
		UART_0_CTRL->PAR_FAIL = 1;
		
		#if 1
			//仅供测试
			delay_ms(50);
			UART_0_CTRL->TX_DATA = 'P';
			while(1);
		#endif
	}
}

//-------------------------------------------------------------------------------------------------

/*
UART1配置函数
*/
void uart_1_init(void)
{
#if 1
		PIN_CONFIG->PIN_0_SEL = PIN_SEL_UART_RXD1;
		PIN_CONFIG->PIN_1_SEL = PIN_SEL_UART_TXD1;	
#else
		PIN_CONFIG->PIN_22_SEL = PIN_SEL_UART_RXD1;
		PIN_CONFIG->PIN_23_SEL = PIN_SEL_UART_TXD1;	
#endif

	UART_1_CTRL->CLK_SEL = 0;		/* 1=32M, 0=16M */
	
	UART_1_CTRL->BAUDSEL = UART_BAUD_115200;
	UART_1_CTRL->FLOW_EN = UART_RTS_CTS_DISABLE;
	UART_1_CTRL->RX_INT_MASK = 1;	/* 1=MASK */
	UART_1_CTRL->TX_INT_MASK = 1;	/* 1=MASK */
	
	UART_1_CTRL->PAR_FAIL_INT_MASK = 1; /* 1=MASK */
	UART_1_CTRL->par_rx_en = 0;		/* Rx Parity check enable */
	UART_1_CTRL->par_rx_even = 1;	/* 1=Even, 0=Odd */
	
	UART_1_CTRL->par_tx_en = 0;		/* Tx Parity check enable */
	UART_1_CTRL->par_tx_even = 0;	/* 1=Even, 0=Odd */
	
	UART_1_CTRL->RI = 0;
	UART_1_CTRL->TI = 0;
	UART_1_CTRL->PAR_FAIL = 1;

	UART_1_CTRL->RX_FLUSH = 1;		/* clr rx fifo and set RX_FIFO_EMPTY */

	NVIC_EnableIRQ(UART1_IRQn);

	UART_1_CTRL->UART_EN = 1;
}

/*
UART1串口写函数
参数: uint8_t data 要发送的数据
注意: 使用这个函数不能使能Tx中断
*/
void uart_1_write(uint8_t data)
{
	UART_1_CTRL->TX_DATA = data;
	while(UART_1_CTRL->TI == 0);
	UART_1_CTRL->TI = 0;
}

/*
UART1串口读FIFO函数
参数:
	pcnt - 返回读到的字节数
	pbuf - 指向数据存放的buf
注意: FIFO长度为4，要求buf长度至少为4字节
*/
void uart_1_read(uint8_t *pcnt, uint8_t *pbuf)
{
	uint8_t i = 0;
	
	while(!UART_1_CTRL->RX_FIFO_EMPTY)
	{
		*(pbuf+i) = UART_1_CTRL->RX_DATA;
		i++;
	}

	*pcnt = i;
}

void uart_1_close(void)
{
	UART_1_CTRL->UART_EN = 0;
	NVIC_DisableIRQ(UART1_IRQn);
}

/*
UART1串口中断函数
*/
void UART1_IRQHandler(void)
{
	/*RX_FLUSH只能置位RX_FIFO_EMPTY,不能清除RI*/
	if ((UART_1_CTRL->RI) == 1)
	{
#if 0
		//这样会有数据丢失
		uart_1_write('R');
		UART_1_CTRL->RI = 0;
#elif 0
		//关闭Tx中断
		uint8_t len, buf[4];
		uint8_t i;
		
		uart_1_read(&len, buf);
		UART_1_CTRL->RI = 0;

		for(i=0; i<len; i++)
		{
			uart_1_write(buf[i]);
		}
#endif
	}

	if ((UART_1_CTRL->TI) == 1)
	{
		UART_1_CTRL->TI = 0;
#if 0
		//仅供测试
		delay_ms(50);
		UART_1_CTRL->TX_DATA = 'T';
		while(1);
#endif
	}

	if((UART_1_CTRL->PAR_FAIL) == 1)
	{
		UART_1_CTRL->PAR_FAIL = 1;
#if 1
		//仅供测试
		delay_ms(50);
		UART_1_CTRL->TX_DATA = 'P';
		while(1);
#endif
	}
}

