#ifndef _GSENSOR_H_
#define _GSENSOR_H_

#include "ARMCM0.h"
#include "config.h"

//设备ID，这是7位ID
#define I2C_ID_KX022 0x1E

#define KX022_VAL	0x06


#define  KX022_WHO_AM_I_REG  0x0F

#define  KX022_CNTL1_REG   0x18
#define  KX022_CNTL3_REG   0x1A
#define  KX022_INC2_REG   0x1d
#define  KX022_WUFC_REG   0x23
#define  KX022_ATH_REG    0X30
#define  KX022_INC1_REG   0x1c
#define  KX022_INT_REL    0x17

#define  KX022_ODCNTL_REG  0X1B
#define  KX022_X_OUTL_REG  0X06
#define  KX022_X_OUTH_REG  0X07
#define  KX022_Y_OUTL_REG  0X08
#define  KX022_Y_OUTH_REG  0X09
#define  KX022_Z_OUTL_REG  0X0A
#define  KX022_Z_OUTH_REG  0X0B
#define  KX022_INS1_REG    0X12
#define  KX022_INS2_REG    0X13
#define  KX022_INS3_REG    0X14
#define  KX022_INS4_REG    0X12
#define  KX022_INS5_REG    0X20
#define  KX022_INS6_REG    0X21

#define  KX022_BUF_CNTL1    0x3a
#define  KX022_BUF_CNTL2    0x3b 
#define  KX022_BUF_STATUS_1 0x3c
#define  KX022_BUF_STATUS_2 0x3d
#define  KX022_BUF_CLEAR    0x3e
#define  KX022_BUF_READ     0x3f

uint8_t kx022_init(void);
extern void gensor_read_xyz(int16_t *p_x, int16_t *p_y, int16_t *p_z);
#endif
