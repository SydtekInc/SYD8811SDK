#include"IR_Tx.h"
#include"gpio.h"
#include"debug.h"
#include <math.h>
#include "lib.h"

static IR_Tx_CTRL_TYPE * IR_Tx_CTRL	= ((IR_Tx_CTRL_TYPE *)		IR_Tx_CTRL_BASE);

void IR_Tx_Init(void)
{
	uint16_t period, invtime, pwmfomat;
	uint8_t  logicbit;
	uint8_t  clk;
	
	PIN_CONFIG->PIN_4_SEL = PIN_SEL_IR_OUT;
	
	//Disable
	IR_Tx_CTRL->IREN = 0;
	IR_Tx_CTRL->REPEN = 0;	

	//----------------------------CARRIER-------------------------
	//载波周期:
	GetMCUClock(&clk);
	if(clk == SYSTEM_CLOCK_16M_XOSC)	clk = SYSTEM_CLOCK_16M_RCOSC;
	clk = 64/pow(2,clk);	//IR_Tx_CLK too
	dbg_printf("IR_Tx_Init: sys_clk: %dM\r\n", clk);
	period = clk*1000000/IR_CARR_FREQ;	//ir_clk_cycle
	//载波占空比->1/3
	invtime = period/3;
	//载波格式
	pwmfomat = 0;	//0:from high to low, 1:from low to high
	IR_Tx_CTRL->CARRIER = ((uint32_t)invtime<<11)|((uint32_t)pwmfomat<<22)|period;
	
	//----------------------------LOGICBIT-------------------------
	//载波周期26.37362637362637us -> 560us/26.37362637362637us = 21.23
	logicbit = 560/(1000000.0/IR_CARR_FREQ);			//ir_carrier_cycle
	IR_Tx_CTRL->ONE_FH = logicbit;
	IR_Tx_CTRL->ONE_LH = logicbit*3; 
	IR_Tx_CTRL->ZERO_FH = logicbit; 
	IR_Tx_CTRL->ZERO_LH = logicbit;
	
	//----------------------------CTRL----------------------------
	IR_Tx_CTRL->MODE = 0;		//IR mode
	IR_Tx_CTRL->IRINVOUT = 0;	//not invert output level
	IR_Tx_CTRL->ONEFMT = 0;		//mark first,space second
	IR_Tx_CTRL->ZEROFMT = 0;	//mark first,space second
	IR_Tx_CTRL->IRIE = 1;		//interrupt enable when commond CMD FIFO transmit done
	IR_Tx_CTRL->CMDIE = 0;		//interrupt disable when each commond CMD or repeat CMD transmit done
	//repeat interval:108ms
	IR_Tx_CTRL->REPTIME = 108000/(1000000.0/IR_CARR_FREQ);	//repeat interval,in carrier clock cycles
	
	//----------------------------FIFOCLR----------------------------
	IR_Tx_CTRL->ccmdfifoclr = 1;	//clear common comand fifo
	IR_Tx_CTRL->rcmdfifoclr = 1;	//clear repeat comand fifo
	
	//----------------------------INTSTAT----------------------------
	IR_Tx_CTRL->cmd_done_clr = 1;		//clear flag
	IR_Tx_CTRL->trans_done_clr = 1;		//clear flag	

	//Enable
	IR_Tx_CTRL->IREN = 1;
	IR_Tx_CTRL->REPEN = 0;

	NVIC_EnableIRQ(IR_Tx_IRQn);
}

void IR_Tx_SendData(uint16_t usrCode, uint8_t data)
{
	uint32_t val = 0;
	uint16_t bit_sequence = 0;
	uint8_t bit_number = 0;
	uint16_t first_half_time; 
	uint16_t last_half_time;

#if 1	
	//引导码 : type1
	first_half_time = 9000/(1000000.0/IR_CARR_FREQ);		/* 9ms载波 */
	last_half_time	= first_half_time/2;					/* 4.5ms空闲 */
	val = (1<<25)|(0<<24)|(last_half_time<<12)|(first_half_time);
	//dbg_printf("val_1 = 0x%08x\r\n", val);
	IR_Tx_CTRL->COMCMD = val;
#endif

#if 1
	//用户码 - 用户码反码 : type0
	bit_sequence = usrCode;
	bit_number = 0x0f;
	val = (0<<25)|(bit_number<<16)|(bit_sequence);
	//dbg_printf("val_2 = 0x%08x\r\n", val);
	IR_Tx_CTRL->COMCMD = val;
#endif

#if 1
	//数据码 - 数据码反码 : type0
	bit_sequence = (~data<<8)|data;
	bit_number = 0x0f;
	val = (0<<25)|(bit_number<<16)|(bit_sequence);
	//dbg_printf("val_3 = 0x%08x\r\n", val);
	IR_Tx_CTRL->COMCMD = val;
#endif

#if 1
	//停止码 : type1
	first_half_time = 560/(1000000.0/IR_CARR_FREQ); 	/* 0.56ms载波 */
	last_half_time = 0; 		/* NEC格式停止码只有0.56ms载波 */
	val = (1<<25)|(0<<24)|(last_half_time<<12)|(first_half_time);
	//dbg_printf("val_4 = 0x%08x\r\n", val);
	IR_Tx_CTRL->COMCMD = val;
#endif

#if 1
	//重复码	//NEC: 9ms载波-2.25ms空闲-0.56ms载波
	
	IR_Tx_CTRL->rcmdfifoclr = 1;	//clear repeat comand fifo first
	
	//停止码 : type1
	first_half_time = 9000/(1000000.0/IR_CARR_FREQ);		/* 9ms载波 */
	last_half_time = first_half_time/4; 					/* 2.25ms空闲 */
	val = (1<<25)|(0<<24)|(last_half_time<<12)|(first_half_time);
	//dbg_printf("val_5 = 0x%08x\r\n", val);
	IR_Tx_CTRL->REPCMD = val;	
	
	//停止码 : type1
	first_half_time = 560/(1000000.0/IR_CARR_FREQ); 	/* 0.56ms载波 */
	last_half_time = 0; 		/* NEC格式停止码只有0.56ms载波 */
	val = (1<<25)|(0<<24)|(last_half_time<<12)|(first_half_time);
	//dbg_printf("val_6 = 0x%08x\r\n", val);
	IR_Tx_CTRL->REPCMD = val;	
#endif
}

void IR_Tx_IRQHandler(void)
{
	static uint32_t repeat = 0;
	
	if(IR_Tx_CTRL->trans_done)			//Common Cmd FIFO transmit done
	{
		dbg_printf("C");
		IR_Tx_CTRL->trans_done_clr = 1;	
		
		IR_Tx_CTRL->cmd_done_clr = 1;	//need
		IR_Tx_CTRL->CMDIE = 1;
		IR_Tx_CTRL->REPEN = 1;
		repeat = 0;
	}

	if((IR_Tx_CTRL->CMDIE)&&(IR_Tx_CTRL->cmd_done))
	{
		IR_Tx_CTRL->cmd_done_clr = 1;
		dbg_printf("E");		//Each

		//演示通过变量repeat控制重复码发送次数
		repeat++;
		if(repeat == 4)			//只发送2次重复码(4个重复码)
		{
			//stop sending repeat code
			IR_Tx_CTRL->REPEN = 0;
			IR_Tx_CTRL->CMDIE = 0;
			IR_Tx_CTRL->rcmdfifoclr = 1;
			repeat = 0;
		}
	}
}

