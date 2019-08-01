#include"rcc.h"
#include"debug.h"
#include"math.h"
#include"lib.h"
//#define _DEBUG_LPO

void LpoCali(void)
{
	uint8_t calRet = 0; 		
	uint8_t calBand0_7 = 0, calBand8_9 = 0; 
	
	calRet = LPOCalibration();
	RFWrite(0x7f, 0x01);
	RFRead(0x25, &calBand0_7);
	RFRead(0x26, &calBand8_9);
	#ifdef _DEBUG_LPO
		DBGPRINTF(("LPOCal: %02x, %02x, %02x, %02x\r\n", calRet, calBand0_7, calBand8_9&0x03, calBand8_9>>0x02));
	#endif
	calRet=calRet;
}


uint8_t getPre(void)
{
	uint8_t clk;
	GetMCUClock(&clk);
	if(clk == SYSTEM_CLOCK_16M_XOSC)clk = SYSTEM_CLOCK_16M_RCOSC;
	uint8_t pre= 64/pow(2,clk);
	return pre;
}
