#include "spi.h"
#include "gpio.h"

static SPI_CTRL_TYPE * SPI_MASTER_CTRL = ((SPI_CTRL_TYPE *) SPI_MASTER_BASE);

void spi_init(enum spi_interface interface)
{
	PIN_CONFIG->PIN_28_SEL = PIN_SEL_SPIM_CLK;	//CLK
	PIN_CONFIG->PIN_29_SEL = PIN_SEL_SPIM_MISO;	// DI
	PIN_CONFIG->PIN_30_SEL = PIN_SEL_SPIM_CSN;	// CS
	PIN_CONFIG->PIN_31_SEL = PIN_SEL_SPIM_MOSI;	// DO

	SPI_MASTER_CTRL->MSB = 1;
	SPI_MASTER_CTRL->SPEED = 0;		//数字越小，速度越快

#if 1
	SPI_MASTER_CTRL->CPOL = 0;
	SPI_MASTER_CTRL->CPHA = 0;
#elif 0
	//untested
	SPI_MASTER_CTRL->CPOL = 0;
	SPI_MASTER_CTRL->CPHA = 1;
#elif 0
	//untested
	SPI_MASTER_CTRL->CPOL = 1;
	SPI_MASTER_CTRL->CPHA = 0;
#else
	SPI_MASTER_CTRL->CPOL = 1;
	SPI_MASTER_CTRL->CPHA = 1;
#endif
}

void spi_cs_enable(enum spi_interface interface)
{
	SPI_MASTER_CTRL->PE = 1;	// CS Low
}

void spi_cs_disable(enum spi_interface interface)
{
	SPI_MASTER_CTRL->PE = 0;	// CS High
}

/***********************************************************
spi写函数
输入参数：uint8_t *p_data 指向要发送的数据
		  uint8_t num     数据的长度
***********************************************************/
void spi_write(uint8_t *p_data,uint16_t num)
{
	// tx data
	for(;num>0;num--)
	{
		SPI_MASTER_CTRL->OUT = *p_data;
		SPI_MASTER_CTRL->START = 1;
		p_data++;
		while(SPI_MASTER_CTRL->START == 1);
		SPI_MASTER_CTRL->DONE = 0;
	}
}

/***********************************************************
spi读函数
输入参数：uint8_t *p_data 指向要接收数据的位置
		  uint8_t num     数据的长度
***********************************************************/
void spi_read(uint8_t *p_data,uint16_t num)
{
	// rx data
	for(;num>0;num--)
	{
		SPI_MASTER_CTRL->OUT = 0xFF;
		SPI_MASTER_CTRL->START = 1;
		while(SPI_MASTER_CTRL->START == 1);
		*p_data = SPI_MASTER_CTRL->IN;
		p_data++;
		SPI_MASTER_CTRL->DONE = 0;
	}
}


