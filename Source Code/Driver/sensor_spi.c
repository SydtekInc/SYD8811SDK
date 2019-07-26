#include "sensor_spi.h"
#include <string.h>

static  MISC_CTRL_TYPE * MISC_CTRL = ((MISC_CTRL_TYPE *) MISC_BASE);

void SPIBurstReadSetAddr(uint8_t len, uint8_t* paddr)
{
	uint8_t i;

	MISC_CTRL->SS_BURST_NUM = len;

	for(i = 0; i < len; i++)
		MISC_CTRL->SS_ADDR[i] = paddr[i];
}

void SPIBurstRead(uint8_t *pbuf, uint8_t len)
{
	uint8_t i;

	MISC_CTRL->SS_BURST_READ = 1;

	while(MISC_CTRL->SS_BURST_READ==1);

	for(i = 0; i < len; i++)
		pbuf[i] = MISC_CTRL->SS_DATA[i];
}

void SPISingleWrite(uint8_t addr, uint8_t data)
{
	uint8_t i;
	
	MISC_CTRL->R_write_pol=R_WRIT_POL;
	
	MISC_CTRL->SS_RDY_CLR = 1;
	
  MISC_CTRL->SS_BUF[addr] = data;
	
	while(1)
	{
		for(i=0; i< 10; i++)
			__asm volatile (" NOP");

		if(MISC_CTRL->SS_RDY == 1)
			break;
	}
}

void SPISingleRead(uint8_t addr, uint8_t *p_data)
{	
	uint8_t num_tmp = MISC_CTRL->SS_BURST_NUM;
	uint8_t addr_tmp = MISC_CTRL->SS_ADDR[0];
	
	MISC_CTRL->R_write_pol=R_WRIT_POL;
	
	MISC_CTRL->SS_BURST_NUM = 0x01;

	MISC_CTRL->SS_ADDR[0] = addr;

	MISC_CTRL->SS_BURST_READ = 1;

	while(MISC_CTRL->SS_BURST_READ==1);
	
	*p_data = MISC_CTRL->SS_DATA[0];

	MISC_CTRL->SS_BURST_NUM = num_tmp;

	MISC_CTRL->SS_ADDR[0] = addr_tmp;
}
