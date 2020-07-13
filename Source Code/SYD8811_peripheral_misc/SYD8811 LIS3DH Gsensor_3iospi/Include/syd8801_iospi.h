
#include "ARMCM0.h" 

#define SPI_SCLK_BIT	BIT22
#define SPI_SDI_BIT		BIT21    //��������MISO  ��ע��
#define SPI_CS_BIT		BIT19    
#define SPI_SDO_BIT		BIT23    //��������MOSI  ��ע��

extern void spi_gpio_init(void);
extern void spi_gpio_write(uint8_t addr, uint8_t data);
extern void spi_gpio_read(uint8_t addr, uint8_t *p_data);
