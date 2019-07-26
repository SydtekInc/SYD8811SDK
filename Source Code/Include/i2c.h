#ifndef _I2C_H_
#define _I2C_H_

#include "ARMCM0.h"

#define I2C0			0x00
#define I2C1			0x01

#define I2C_1_BYTE_ADDRESS			0x01
#define I2C_2_BYTE_ADDRESS			0x00

extern void i2c_Init(uint8_t i2c,uint32_t clk_io,uint32_t sda_io);
extern ErrorStatus i2c_0_write(uint8_t id, uint8_t addr_len, uint16_t addr, uint8_t * buf, uint16_t sz);
extern ErrorStatus i2c_0_read(uint8_t id, uint8_t addr_len, uint16_t addr, uint8_t * buf, uint16_t sz);
extern ErrorStatus i2c_1_write(uint8_t id, uint8_t addr_len, uint16_t addr, uint8_t * buf, uint16_t sz);
extern ErrorStatus i2c_1_read(uint8_t id, uint8_t addr_len, uint16_t addr, uint8_t * buf, uint16_t sz);

#endif

