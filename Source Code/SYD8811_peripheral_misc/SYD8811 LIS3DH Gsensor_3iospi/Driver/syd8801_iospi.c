/*
gpio��ģ��spi�Ĳ����ļ�

���ߣ�����ʢԴ��Ƽ����޹�˾
���ڣ�2016/7/8
*/
#include "syd8801_iospi.h"
#include "syd8801_gpio.h"
#include "armcm0.h"
/*
spiд���� ������д�Ĵ����Ĳ��� Ӧ����˵д�Ĵ�������
���������uint8_t addr Ҫд�ļĴ���
					uint8_t data Ҫ���õ�����
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
		if((addr&BIT(7-idx)))    //�ж�Ҫ����λ�ǲ���0
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
spi������ �����˶��Ĵ����Ĳ��� Ӧ����˵���Ĵ�������
���������uint8_t addr Ҫ���ļĴ���
					uint8_t data �������ݴ�ŵĵ�ַ
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
spigpio�����ú���
���������uint8_t addr Ҫ���ļĴ���
					uint8_t data �������ݴ�ŵĵ�ַ
*/
void spi_gpio_init(void)
{
	GPIO_Set_Output(SPI_CS_BIT | SPI_SCLK_BIT | SPI_SDO_BIT);
	GPIO_Set_Input(SPI_SDI_BIT);
	GPIO_Pin_Set(SPI_CS_BIT | SPI_SCLK_BIT | SPI_SDO_BIT); // SCLK:High,CS:High,SDO:High	
}

