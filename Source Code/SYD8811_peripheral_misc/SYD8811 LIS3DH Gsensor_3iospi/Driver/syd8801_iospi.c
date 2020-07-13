/*
gpio口模拟spi的操作文件

作者：北京盛源达科技有限公司
日期：2016/7/8
*/
#include "syd8801_iospi.h"
#include "syd8801_gpio.h"
#include "armcm0.h"
/*
spi写函数 包括了写寄存器的步骤 应该是说写寄存器函数
输入参数：uint8_t addr 要写的寄存器
					uint8_t data 要配置的数据
*/
void spi_gpio_write(uint8_t addr, uint8_t data)
{
	uint8_t idx;
	addr &= ~0x80; // Write bit: set L
	GPIO_Pin_Clear(SPI_CS_BIT);
	__asm volatile (" NOP");
	GPIO_Pin_Clear(SPI_SCLK_BIT);
	__asm volatile (" NOP");
	__asm volatile (" NOP");
	__asm volatile (" NOP");
	__asm volatile (" NOP");
	__asm volatile (" NOP");
	for(idx=0;idx<8;idx++)
	{
		if((addr&BIT(7-idx)))    //判断要发的位是不是0
		{
			GPIO_Pin_Set(SPI_SDO_BIT);
			__asm volatile (" NOP");
			GPIO_Pin_Set(SPI_SCLK_BIT);
			__asm volatile (" NOP");
			GPIO_Pin_Clear(SPI_SCLK_BIT);
			__asm volatile (" NOP");
		}
		else
		{
			GPIO_Pin_Clear(SPI_SDO_BIT);
			__asm volatile (" NOP");
			GPIO_Pin_Set(SPI_SCLK_BIT);
			__asm volatile (" NOP");
			GPIO_Pin_Clear(SPI_SCLK_BIT);
			__asm volatile (" NOP");
		}
	}
	for(idx=0;idx<8;idx++)
	{
		if((data&BIT(7-idx)))
		{
			GPIO_Pin_Set(SPI_SDO_BIT);
			__asm volatile (" NOP");
			GPIO_Pin_Set(SPI_SCLK_BIT);
			__asm volatile (" NOP");
			
			if(idx != 7)
			{
				GPIO_Pin_Clear(SPI_SCLK_BIT);
				__asm volatile (" NOP");
			}
		}
		else
		{
			GPIO_Pin_Clear(SPI_SDO_BIT);
			__asm volatile (" NOP");
			GPIO_Pin_Set(SPI_SCLK_BIT);
			__asm volatile (" NOP");
			
			if(idx != 7)
			{
				GPIO_Pin_Clear(SPI_SCLK_BIT);
				__asm volatile (" NOP");
			}
		}
	}
	GPIO_Pin_Set(SPI_SCLK_BIT);
	__asm volatile (" NOP");
	GPIO_Pin_Set(SPI_CS_BIT);
}
/*
spi读函数 包括了读寄存器的步骤 应该是说读寄存器函数
输入参数：uint8_t addr 要读的寄存器
					uint8_t data 读到数据存放的地址
*/
void spi_gpio_read(uint8_t addr, uint8_t *p_data)
{
	uint8_t idx;
	uint8_t tmp=0;
	addr |= 0x80; // Read bit: set H
	GPIO_Pin_Clear(SPI_CS_BIT);
	__asm volatile (" NOP");	
	GPIO_Pin_Clear(SPI_SCLK_BIT);
	__asm volatile (" NOP");
	__asm volatile (" NOP");
	__asm volatile (" NOP");
	__asm volatile (" NOP");
	__asm volatile (" NOP");
	for(idx=0;idx<8;idx++)
	{
		if((addr&BIT(7-idx)))
		{
			GPIO_Pin_Set(SPI_SDO_BIT);
			__asm volatile (" NOP");
			GPIO_Pin_Set(SPI_SCLK_BIT);
			__asm volatile (" NOP");
			GPIO_Pin_Clear(SPI_SCLK_BIT);
			__asm volatile (" NOP");
		}
		else
		{
			GPIO_Pin_Clear(SPI_SDO_BIT);
			__asm volatile (" NOP");
			GPIO_Pin_Set(SPI_SCLK_BIT);
			__asm volatile (" NOP");
			GPIO_Pin_Clear(SPI_SCLK_BIT);
			__asm volatile (" NOP");
		}
	}
	GPIO_Set_Input(SPI_SDO_BIT);
	for(idx=0;idx<8;idx++)
	{     
		GPIO_Pin_Clear(SPI_SCLK_BIT);
		__asm volatile (" NOP");	
		GPIO_Pin_Set(SPI_SCLK_BIT);
		__asm volatile (" NOP");		
		if(GPIO_Pin_Read(SPI_SDO_BIT))    //SPI_SDI_BIT
		{
			tmp = tmp << 1 ;
			tmp = tmp | 0x01 ;
		}
		else
		{
			tmp = tmp << 1 ;
			tmp = tmp & 0xFE ;
		}			
		if(idx != 7)
			GPIO_Pin_Clear(SPI_SCLK_BIT);
	
		__asm volatile (" NOP");
	}
	GPIO_Set_Output(SPI_SDO_BIT);
	p_data[0] = tmp;
	GPIO_Pin_Set(SPI_SCLK_BIT);
	__asm volatile (" NOP");	
	GPIO_Pin_Set(SPI_CS_BIT);
}
/*
spigpio口配置函数
输入参数：uint8_t addr 要读的寄存器
					uint8_t data 读到数据存放的地址
*/
void spi_gpio_init(void)
{
	GPIO_Set_Output(SPI_CS_BIT | SPI_SCLK_BIT | SPI_SDO_BIT);
	GPIO_Set_Input(SPI_SDI_BIT);
	GPIO_Pin_Set(SPI_CS_BIT | SPI_SCLK_BIT | SPI_SDO_BIT); // SCLK:High,CS:High,SDO:High	
}

