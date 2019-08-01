#ifndef _SENSOR_SPI_H_
#define _SENSOR_SPI_H_

#include "ARMCM0.h"

#define R_WRIT_POL   0		/// 0 - 最高读写位是0

extern void SPIBurstReadSetAddr(uint8_t len, uint8_t* paddr);
extern void SPIBurstRead(uint8_t *pbuf, uint8_t len);
extern void SPISingleWrite(uint8_t addr, uint8_t data);
extern void SPISingleRead(uint8_t addr, uint8_t *p_data);

#endif
