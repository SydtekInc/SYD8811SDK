#ifndef _SYD8801_IOI2C_H_
#define _SYD8801_IOI2C_H_

#include "ARMCM0.h"

#define iic_SCLK   BIT22
#define iic_SDA    BIT23

#define IOI2C_1_BYTE_ADDRESS			0x01
#define IOI2C_2_BYTE_ADDRESS			0x00

//PWMÄ£¿éÃ¶¾Ù
typedef enum {
	iic_write,
	iic_read,
}IIC_DIRECTION;

void ioi2c_ioconfig(void);
void start(void);
void stop(void);
uint8_t i2c_reg_read(uint8_t id, uint8_t addr_len, uint16_t addr, uint8_t * buf, uint16_t sz);
uint8_t i2c_reg_write(uint8_t id, uint8_t addr_len, uint16_t addr, uint8_t * buf, uint16_t sz);


#endif
