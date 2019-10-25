#include "ARMCM0.h"
#include "timer.h"
#include "gpio.h"
#include "debug.h"
#include "lib.h"
#include <string.h>
#include "delay.h"
#include "gpadc.h"
#include "led_key.h"
#include "config.h"


LL_CTRL_TYPE * BB_CTRL = ((LL_CTRL_TYPE *) LL_BASE);

enum _DTM_FREQUENCY_TYPE_{
F2402MHZ,
F2404MHZ,
F2406MHZ,
F2408MHZ,
F2410MHZ,
F2412MHZ,
F2414MHZ,
F2416MHZ,
F2418MHZ,
F2420MHZ,
F2422MHZ,
F2424MHZ,
F2426MHZ,
F2428MHZ,
F2430MHZ,
F2432MHZ,
F2434MHZ,
F2436MHZ,
F2438MHZ,
F2440MHZ,
F2442MHZ,
F2444MHZ,
F2446MHZ,
F2448MHZ,
F2450MHZ,
F2452MHZ,
F2454MHZ,
F2456MHZ,
F2458MHZ,
F2460MHZ,
F2462MHZ,
F2464MHZ,
F2466MHZ,
F2468MHZ,
F2470MHZ,
F2472MHZ,
F2474MHZ,
F2476MHZ,
F2478MHZ,
F2480MHZ,
};

enum _DTM_PAYLOAD_TYPE_{
Pseudo_Random_bit_sequence_9,
Alternating_bits_11110000,
Alternating_bits_10101010,
Pseudo_Random_bit_sequence_15,
All_1_bits,
All_0_bits,
Alternating_bits_00001111,
Alternating_bits_0101,
};

uint8_t reg_tmp0=0,reg_tmp1=0;
void DTMTx_Carrier(uint8_t f,uint8_t c2)
{
	BBRFWrite(0x7F,0x01);
	BBRFWrite(0x57,c2);  //rf bankb, addr:0x00, wr:freq idx  
	
	//carrier mode
	BBRFWrite(0x7F,0x01);
	BBRFWrite(0x00,f);  //rf bankb, addr:0x00, wr:freq idx  
	
	reg_tmp0 = *(uint8_t *)0x40030001;
	*(uint8_t *)0x40030001=0x0D;  //modem, addr:0x01, wr:0x0d
	
	reg_tmp1 =*(uint8_t *)0x40030003;
	*(uint8_t *)0x40030003=0x80;  //modem, addr:0x01, wr:0x0d

	*(uint8_t *)0x50001008=0x28;  //power on, addr:0x08, wr:0x28  manual rf tx mode
}

void DTMTx_modulation(uint8_t payload,uint8_t len,uint8_t f,uint8_t c2)
{
	uint8_t tmp[2];
	BBRFWrite(0x7F,0x01);
	BBRFWrite(0x57,c2);  //rf bankb, addr:0x00, wr:freq idx  
	
	BB_CTRL->TXINTMSK = 1;
	BB_CTRL->RXINTMSK = 1;
	
	tmp[0] = payload;
	tmp[1] = len;
	GAPBBTXFIFO0Write(tmp, 0x02);	//HW design

	BB_CTRL->CH_USER = f;
	BB_CTRL->DTM_MODE = 1;
	BB_CTRL->DTM_EN = 1;	
}

static void CmdLETestEnd()
{
	*(uint8_t *)0x50001008=0x24;  
    *(uint8_t *)0x50001008=0x04;

    *(uint8_t *)0x40030003=reg_tmp1;  //modem, addr:0x01, wr:0x0d
	*(uint8_t *)0x40030001=reg_tmp0;  //modem, addr:0x01, wr:0x0d
	
	BB_CTRL->SR_P = 1;
}

int main()
{	
	int8_t f=F2402MHZ;
	int8_t c2=0x28,tx_power=BLE_TX_POWER_0_DBM;
	__disable_irq();

	BleInit();	
	RCOSCCalibration();
	MCUClockSwitch(SYSTEM_CLOCK_64M_RCOSC);
	ClockSwitch(SYSTEM_32K_CLOCK_RCOSC);
	LPOCalibration();						//这是内部RC32k晶振的校准函数	经过该函数后定时器能够得到一个比较准确的值
	
	dbg_init();
	UartEn(true);
	#ifdef _DTMTX_MODULATION_
	dbg_printf("SYD8811 dtm modulation demo %s:%s\r\n", __DATE__ , __TIME__);
	#else
	dbg_printf("SYD8811 dtm Carrier demo %s:%s\r\n", __DATE__ , __TIME__);
	#endif
	
	
	PIN_Set_GPIO(U32BIT(KEY1) | U32BIT(KEY2) | U32BIT(KEY3) | U32BIT(KEY4),PIN_SEL_GPIO);
//	PIN_Set_GPIO(U32BIT(LED1) | U32BIT(LED2) | U32BIT(LED3) | U32BIT(LED4),PIN_SEL_GPIO);
	
	GPIO_Set_Input( U32BIT(KEY1) | U32BIT(KEY2) | U32BIT(KEY3) | U32BIT(KEY4),  U32BIT(KEY1) | U32BIT(KEY2) | U32BIT(KEY3) | U32BIT(KEY4));	
	PIN_Pullup_Enable(T_QFN_48, U32BIT(KEY1) | U32BIT(KEY2) | U32BIT(KEY3) | U32BIT(KEY4));
	GPIO_Input_Enable(U32BIT(KEY1) | U32BIT(KEY2) | U32BIT(KEY3) | U32BIT(KEY4));
	
//	GPIO_Set_Output( U32BIT(LED1) | U32BIT(LED2) | U32BIT(LED3) | U32BIT(LED4));	
//	GPIO_Pin_Set(U32BIT(LED1) | U32BIT(LED2) | U32BIT(LED3) | U32BIT(LED4));

	__enable_irq();	
	#ifdef _DTMTX_MODULATION_
	DTMTx_modulation(Pseudo_Random_bit_sequence_9,1,F2402MHZ,c2);
	#else
	DTMTx_Carrier(F2402MHZ,c2);
	#endif
	ble_SetTxPower(tx_power);

	while(1)
	{
		if(GPIO_Pin_Read( U32BIT(KEY1)))
		{
			CmdLETestEnd();
			delay_ms(5);
			f++;
			if(f>F2480MHZ) f=F2402MHZ;
			#ifdef _DTMTX_MODULATION_
			DTMTx_modulation(Pseudo_Random_bit_sequence_9,1,f,c2);
			#else
			DTMTx_Carrier(f,c2);
			#endif
			dbg_printf("DTMTx_Carrier:%x\r\n", f);
			delay_ms(1000);
		}
		if(GPIO_Pin_Read( U32BIT(KEY2)))
		{
			c2++;
			if(c2>0x7f) c2=0;
			BBRFWrite(0x7F,0x01);
			BBRFWrite(0x57,c2);  //rf bankb, addr:0x00, wr:freq idx  
			dbg_printf("c2:%x\r\n", c2);
			delay_ms(1000);
		}
		if(GPIO_Pin_Read( U32BIT(KEY3)))
		{
			c2--;
			if(c2<0) c2=0x7F;
			BBRFWrite(0x7F,0x01);
			BBRFWrite(0x57,c2);  //rf bankb, addr:0x00, wr:freq idx  
			dbg_printf("c2:%x\r\n", c2);
			delay_ms(1000);
		}
		if(GPIO_Pin_Read( U32BIT(KEY4)))
		{
			
			tx_power--;
			if(tx_power<0) tx_power=BLE_TX_POWER_4_DBM;
			ble_SetTxPower(tx_power);
			dbg_printf("tx_power:%x\r\n", tx_power);
			delay_ms(1000);
		}
	}	
}

