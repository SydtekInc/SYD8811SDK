#ifndef _LIS3DH_H_
#define _LIS3DH_H_

#include "ARMCM0.h"

//设备ID，这是7位ID，如果写操作正在发出的ID是 0x19<<1+1=0x33  读操作就是 0x19<<1=0x32
#define I2C_ID_LOS3DH 0x19

#define LIS3DH_REG0x20_VAL	0x30

#define LIS3DH_STATUS_REG	0x07
#define LIS3DH_WHO_AM_I_REG	0x0F
#define LIS3DH_X_DATA_REG	0x28
#define LIS3DH_Y_DATA_REG	0x2A
#define LIS3DH_Z_DATA_REG	0x2C

void lis3dh_write_reg(uint8_t addr, uint8_t reg);
void lis3dh_read_reg(uint8_t addr, uint8_t * p_reg);
void lis3dh_init(void);
void lis3dh_strat_accelerometer(void);
void lis3dh_stop_accelerometer(void);
void lis3dh_get_accelerometer_data(int16_t *p_x, int16_t *p_y, int16_t *p_z);
	
#endif

