#ifndef _SPI__H__
#define _SPI__H__

#include "ARMCM0.h" 

enum spi_interface{
	FLASH_SPI,
	LCD_SPI,
};

extern void spi_cs_enable(enum spi_interface interface);
extern void spi_cs_disable(enum spi_interface interface);

extern void spi_init(enum spi_interface interface);
extern void spi_write(uint8_t *p_data,uint16_t num);
extern void spi_read(uint8_t *p_data,uint16_t num);

#endif

