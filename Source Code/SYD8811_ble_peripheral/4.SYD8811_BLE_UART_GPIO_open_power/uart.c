#include "uart.h"
#include "gpio.h"
#include "uart_protocol.h"

static UART_CTRL_TYPE * UART_0_CTRL = ((UART_CTRL_TYPE *) UART_0_CTRL_BASE);
static UART_CTRL_TYPE * UART_1_CTRL = ((UART_CTRL_TYPE *) UART_1_CTRL_BASE);

//-------------------------------------------------------------------------------------------------
void uart_0_init(void)
{
	PIN_CONFIG->PIN_15_SEL = PIN_SEL_UART_RXD0;
	PIN_CONFIG->PIN_16_SEL = PIN_SEL_UART_TXD0;
	
	//PM
	PIN_CONFIG->PAD_21_INPUT_PULL_UP = 0;
	PIN_CONFIG->PAD_22_INPUT_PULL_UP = 0;

	UART_0_CTRL->CLK_SEL = 0;		/* 1=32M, 0=16M */
	
	UART_0_CTRL->BAUDSEL = UART_BAUD_115200;
	UART_0_CTRL->FLOW_EN = UART_RTS_CTS_DISABLE;
	
	UART_0_CTRL->RX_INT_MASK = 0;	/* 1=MASK */
	UART_0_CTRL->TX_INT_MASK = 1;	/* 1=MASK */
	
	UART_0_CTRL->PAR_FAIL_INT_MASK = 1; /* 1=MASK */
	UART_0_CTRL->par_rx_even = 1;	/* 1=Even, 0=Odd */
	UART_0_CTRL->par_rx_en = 0;		/* 1=Rx Parity check enable */

	UART_0_CTRL->par_tx_even = 1;	/* 1=Even, 0=Odd */
	UART_0_CTRL->par_tx_en = 0;		/* 1=Tx Parity check enable */

	//clr Int Flag
	UART_0_CTRL->RI = 0;
	UART_0_CTRL->TI = 0;
	UART_0_CTRL->PAR_FAIL = 1;

	UART_0_CTRL->RX_FLUSH = 1;		/* clr rx fifo and set RX_FIFO_EMPTY */

	NVIC_EnableIRQ(UART0_IRQn);

	UART_0_CTRL->UART_EN = 1;
}

/****************************************************************************
UART0串口写函数
参数: uint8_t data 要发送的数据
注意: 
	  使用这个函数不可使能Tx中断
*****************************************************************************/
void uart_0_write(uint8_t data)
{
	UART_0_CTRL->TX_DATA = data;
	while(UART_0_CTRL->TI == 0);
	UART_0_CTRL->TI = 0;
}

/****************************************************************************
UART0串口读Rx FIFO函数
参数:
	pcnt - 返回读到的字节数
	pbuf - 指向数据存放的buf
注意: FIFO长度为4，要求接收buf大小至少为4字节
****************************************************************************/
void uart_0_read(uint8_t *pcnt, uint8_t *pbuf)
{
	uint8_t i = 0;
	volatile uint8_t dly = 0;		//如果用64M时钟，必须要加delay
	
	while(!UART_0_CTRL->RX_FIFO_EMPTY)
	{
		*(pbuf+i) = UART_0_CTRL->RX_DATA;
		i++;
		
		//延时400ns以上
		dly++;
		dly++;
		dly++;		
	}

	*pcnt = i;
}

/****************************************************************************
UART0串口清除Rx FIFO函数
注意: 在关闭了uarten到重新打开UARTen的时候应该清除掉RX的fifo里面的数据
****************************************************************************/
void uart_0_ClrFiFo(void)
{
	UART_0_CTRL->RX_FLUSH = 1;		/* clr rx fifo and set RX_FIFO_EMPTY */
}

void uart_0_close(void)
{
	UART_0_CTRL->UART_EN = 0;
	NVIC_DisableIRQ(UART0_IRQn);
}

/*****************************************************************************
UART0串口中断函数
注意:
	  RX_FLUSH只能置位RX_FIFO_EMPTY,不能清除RI
*****************************************************************************/
void UART0_IRQHandler(void)
{
	if ((UART_0_CTRL->RI) == 1)
	{
		//读数据到buf[]中
		UART_0_CTRL->RI = 0;		//先清标志，再读数据		
		uartRx_callback();
	}

#if 0
	if ((UART_0_CTRL->TI) == 1)
	{
		UART_0_CTRL->TI = 0;
	}
#endif

	if((UART_0_CTRL->PAR_FAIL) == 1)
	{
		UART_0_CTRL->PAR_FAIL = 1;
	}
}

//-------------------------------------------------------------------------------------------------
void uart_1_init(void)
{
	PIN_CONFIG->PIN_2_SEL = PIN_SEL_UART_RXD1;
	PIN_CONFIG->PIN_3_SEL = PIN_SEL_UART_TXD1;	

	//PM
	PIN_CONFIG->PAD_2_INPUT_PULL_UP = 0;
	PIN_CONFIG->PAD_3_INPUT_PULL_UP = 0;

	UART_1_CTRL->CLK_SEL = 0;		/* 1=32M, 0=16M */
	
	UART_1_CTRL->BAUDSEL = UART_BAUD_115200;
	UART_1_CTRL->FLOW_EN = UART_RTS_CTS_DISABLE;
	
	UART_1_CTRL->RX_INT_MASK = 0;	/* 1=MASK */
	UART_1_CTRL->TX_INT_MASK = 1;	/* 1=MASK */
	
	UART_1_CTRL->PAR_FAIL_INT_MASK = 1; /* 1=MASK */
	UART_1_CTRL->par_rx_even = 0;	/* 1=Even, 0=Odd */
	UART_1_CTRL->par_rx_en = 0;		/* 1=Rx Parity check enable */
	
	UART_1_CTRL->par_tx_even = 0;	/* 1=Even, 0=Odd */
	UART_1_CTRL->par_tx_en = 0;		/* 1=Tx Parity check enable */

	//clr Int Flag
	UART_1_CTRL->RI = 0;
	UART_1_CTRL->TI = 0;
	UART_1_CTRL->PAR_FAIL = 1;

	UART_1_CTRL->RX_FLUSH = 1;		/* clr rx fifo and set RX_FIFO_EMPTY */

	NVIC_EnableIRQ(UART1_IRQn);

	UART_1_CTRL->UART_EN = 1;
}

/****************************************************************************
UART1串口写函数
参数: uint8_t data 要发送的数据
注意: 
	  使用这个函数不可使能Tx中断
****************************************************************************/
void uart_1_write(uint8_t data)
{
	UART_1_CTRL->TX_DATA = data;
	while(UART_1_CTRL->TI == 0);
	UART_1_CTRL->TI = 0;
}

/****************************************************************************
UART1串口读Rx FIFO函数
参数:
	pcnt - 返回读到的字节数
	pbuf - 指向数据存放的buf
注意: FIFO长度为4，要求接收buf大小至少为4字节
****************************************************************************/
void uart_1_read(uint8_t *pcnt, uint8_t *pbuf)
{
	uint8_t i = 0;
	volatile uint8_t dly = 0;		//如果用64M时钟，必须要加delay延时400ns以上
	
	while(!UART_1_CTRL->RX_FIFO_EMPTY)
	{
		*(pbuf+i) = UART_1_CTRL->RX_DATA;
		i++;
		
		//
#if 1		
		dly++;
		dly++;
		dly++;
#endif		
	}

	*pcnt = i;
}

void uart_1_close(void)
{
	UART_1_CTRL->UART_EN = 0;
	NVIC_DisableIRQ(UART1_IRQn);
}

/*****************************************************************************
UART1串口中断函数
注意:
	  RX_FLUSH只能置位RX_FIFO_EMPTY,不能清除RI
*****************************************************************************/
void UART1_IRQHandler(void)
{
	if ((UART_1_CTRL->RI) == 1)
	{
		//读数据到buf[]中
		UART_1_CTRL->RI = 0;		//先清标志，再读数据		
		uartRx_callback();
	}

#if 0
	if ((UART_1_CTRL->TI) == 1)
	{
		UART_1_CTRL->TI = 0;
	}
#endif

#if 0
	if((UART_1_CTRL->PAR_FAIL) == 1)
	{
		UART_1_CTRL->PAR_FAIL = 1;
	}
#endif
}

