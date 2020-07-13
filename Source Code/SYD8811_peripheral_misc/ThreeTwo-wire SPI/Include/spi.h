#ifndef _SPI_H_
#define _SPI_H_

#include "ARMCM0.h"

#define R_WRIT_POL   1

#ifdef _SPI_C
#else
	extern void SPIBurstReadSetAddr(uint8_t len, uint8_t* paddr);
	extern void SPIBurstRead(uint8_t *pbuf, uint8_t len);
	extern void SPISingleWrite(uint8_t addr, uint8_t data);
	extern void SPISingleRead(uint8_t addr, uint8_t *p_data);
#endif

#endif
