#ifndef _I2C_H_
#define _I2C_H_

#include "ARMCM0.h"

extern I2C_CTRL_TYPE *	I2C_0_CTRL;
extern I2C_TXD_TYPE *		I2C_0_TXD;
extern I2C_RXD_TYPE *		I2C_0_RXD;
extern I2C_CTRL_TYPE *	I2C_1_CTRL;
extern I2C_TXD_TYPE *		I2C_1_TXD;
extern I2C_RXD_TYPE *		I2C_1_RXD;

#define I2C_1_BYTE_ADDRESS			0x01
#define I2C_2_BYTE_ADDRESS			0x00

extern void initI2C_gpio(void);
extern uint8_t i2c_0_write(uint8_t id, uint8_t addr_len, uint16_t addr, uint8_t * buf, uint16_t sz);
extern uint8_t i2c_0_read(uint8_t id, uint8_t addr_len, uint16_t addr, uint8_t * buf, uint16_t sz);
extern uint8_t i2c_1_write(uint8_t id, uint8_t addr_len, uint16_t addr, uint8_t * buf, uint16_t sz);
extern uint8_t i2c_1_read(uint8_t id, uint8_t addr_len, uint16_t addr, uint8_t * buf, uint16_t sz);

#endif

