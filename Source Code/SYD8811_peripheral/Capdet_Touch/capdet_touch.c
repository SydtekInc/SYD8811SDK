#include "gpio.h"
#include "capdet_touch.h"
#include "DebugLog.h"
#include "timer.h"
#include "softtimer.h"
#include "config.h"
#include <stddef.h>
#include <string.h>

#ifdef _USE_SYD_CAPDET_TOUCH_

#ifdef _SYD_CAPDET_TOUCH_SENSITIVE_
uint8_t capdet_touch_state = 0;
#endif

uint8_t rtc_10s_cnt = 0;
uint32_t press_always_cnt = 0;

uint8_t capdet_calibration_state = 0; /*BIT7:0 空闲状态 1：正在校准; BIT6 :0 空闲状态 1：校准结束; BIT5 :0 空闲状态 1：可以校准*/
uint8_t capdet_calibration_cnt = 0;

CAPDET_ALG_CONTEXT_TYPE g_context;
SYD_CAPDET_TOUCH_KEY_t syd_capdet_key;

static TIMER_CTRL_TYPE * TIMER_CTRL = ((TIMER_CTRL_TYPE *) TIMER_CTRL_BASE);


void capdet_init_all_256(void)
{
	CAPDET_ALG_CONFIG_TYPE g_reg;
	DBGPRINTF(("CAP_DET init\r\n"));

	GPI_CTRL->GPI_6_InE = 0;				//input disable
	GPIO_CTRL->GPIO_6_DIR = 1;				//set input
	PIN_CONFIG->PAD_6_INPUT_PULL_UP = 0;	//pad pullup disable
	PIN_CONFIG->PIN_6_SEL = PIN_SEL_ANALOG; //cap det button 0
	

	#ifdef CAPDET_4_CH
	GPI_CTRL->GPI_7_InE = 0;				//input disable
	GPIO_CTRL->GPIO_7_DIR = 1;				//set input
	PIN_CONFIG->PAD_7_INPUT_PULL_UP = 0;	//pad pullup disable
	PIN_CONFIG->PIN_7_SEL = PIN_SEL_ANALOG; //cap det button 1

	GPI_CTRL->GPI_8_InE = 0;				//input disable
	GPIO_CTRL->GPIO_8_DIR = 1;				//set input
	PIN_CONFIG->PAD_8_INPUT_PULL_UP = 0;	//pad pullup disable
	PIN_CONFIG->PIN_8_SEL = PIN_SEL_ANALOG; //cap det button 2

	GPI_CTRL->GPI_9_InE = 0;				//input disable
	GPIO_CTRL->GPIO_9_DIR = 1;				//set input
	PIN_CONFIG->PAD_9_INPUT_PULL_UP = 0;	//pad pullup disable
	PIN_CONFIG->PIN_9_SEL = PIN_SEL_ANALOG; //cap det button 3
	#endif
	
	memset(&g_context,0,sizeof(g_context));
	memset(&syd_capdet_key,0,sizeof(syd_capdet_key));
	memset(&g_reg,0,sizeof(g_reg));
	
	capdet_init();	

	capdet_reg_read_all(&g_reg);
	g_reg.frm_show = true;
	g_reg.debug_frm_show = 1;
	g_reg.cell_num = 1;
	capdet_reg_write_all(&g_reg);
	
	
#ifdef CAPDET_4_CH
	DBGPRINTF(("4 channel!\r\n"));
	capdet_reg_write(0x00, 0x04);  //set active channel number (1=>ch0 2=>>ch0+ch1 3=>>ch0+ch1+ch2 4=>>ch0+ch1+ch2+ch3) 
#else
	DBGPRINTF(("1 channel!\r\n"));
	capdet_reg_write(0x00, 0x01);
#endif

	//婢х偛濮為悘鍨櫛閹稿甯囬悘鍨櫛鎼? 10 5 , 10 7
	capdet_reg_write(0x40, 200 % 256); // touch force_[7:0] , touch data higher than touch force, would report button press
	capdet_reg_write(0x41, 200/ 256); // touch force_[15:8], touch data higher than touch force, would report button press
	capdet_reg_write(0x42, 100 % 256);  // touch_release_[7:0], touch data lower than touch release, would report button release
	capdet_reg_write(0x43, 100 / 256);  // touch_release_[15:8], touch data lower than touch release, would report button release

	//set frame rate
	capdet_reg_write(0x44, 50); // Active Frame Rate 25Hz
	capdet_reg_write(0x45, 30); // Idle1 Frame Rate 15Hz
	capdet_reg_write(0x46, 30); // Idle2 Frame Rate 15Hz
	capdet_reg_write(0x47, 30); // sleep Frame Rate 15Hz

	//set how long to enter next mode
	capdet_reg_write(0x48, 25);   // fps_idle1_cnt [7:0]
	capdet_reg_write(0x49, 0x00); // fps_idle1_cnt [15:8]
	capdet_reg_write(0x4a, 8);   // fps_idle2_cnt [7:0]
	capdet_reg_write(0x4b, 0x00); // fps_idle2_cnt [15:8]
	capdet_reg_write(0x4c, 8);   // fps_sleep_cnt [7:0]
	capdet_reg_write(0x4d, 0x00); // fps_sleep_cnt [15:8]

	capdet_reg_write(0x58, 0x03); //capdet_ibias //鐠佸墽鐤嗘径褌绔撮悙?03閿涘本鐦?1閺囧菙鐎?(raw閸?)
	#ifdef CAPDET_4_CH
	capdet_reg_write(0x4e, 0xF0);  //set wake_up_mask [7:0] - 鐟?鐎规utton0/1/2/3鐟欏摜娅﹂崰姘跺晪 
	#else
	capdet_reg_write(0x4e, 0xFE); //set wake_up_mask [7:0] - 鐟?鐎规utton0鐟欏摜娅﹂崰姘跺晪
	#endif
	capdet_reg_write(0x59, 0x01); //瀵ら缚?鎷屌嶇�规氨鍋?full cycle閿涘矁艒鐎规艾鈧?1
	capdet_reg_write(0x5A, 0x01); // report latency

	capdet_reg_write(0x3a, 1600%256);  // pos_comp_frm [7:0]
	capdet_reg_write(0x3b, 1600/256); // pos_comp_frm [15:8]
	capdet_reg_write(0x3c, 100);  // pos_comp_val [7:0]
	capdet_reg_write(0x3d, 0x00);	// pos_comp_val [15:8]
	capdet_reg_write(0x3e, 0); // pos_comp_num

	capdet_start();
	*((uint8_t *)(PWRON_BASE + 0x0d)) |= 0x02; //CAPDET_EN = 1
	//capdet_wakeup_cali = 0;

	NVIC_EnableIRQ(CAP_IRQn);
	NVIC_EnableIRQ(TOUCH_IRQn);
	
	#ifdef _USE_SYD_CAPDET_POWERON_AWAYS_TOUCH_CALIBRATION_
	capdet_calibration_state  |=BIT4;   //开机标志位
	#endif
}


void CapDet_touch_force_Calibration(CAPDET_TOUCH_FORCE_CALIBRATION_TYPE type)
{ 
	uint16_t  force=69,release=50;
	switch(type)
	{
		case CALIBRATION_LCD_WACKLUP:
			force+=20;
			release+=20;
			break;
		case CALIBRATION_LCD_SLEEP:

			break;
	}
	capdet_reg_write(0x40, force % 256); // touch force_[7:0] , touch data higher than touch force, would report button press
	capdet_reg_write(0x41, force/ 256); // touch force_[15:8], touch data higher than touch force, would report button press
	capdet_reg_write(0x42, release % 256);  // touch_release_[7:0], touch data lower than touch release, would report button release
	capdet_reg_write(0x43, release / 256);  // touch_release_[15:8], touch data lower than touch release, would report button release
	#if ((defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)))
	DBGPRINTF("touch_force_Calibration: %d  %d\r\n",force,  release);
	#endif
}

#ifdef  _USE_SYD_CAPDET_AUTO_CALIBRATION_

void CapDetForceCalibration(void)
{
	if(g_context.op_mode == 0)
	{
		
	}
	else
	{
		capdet_reg_write(0x0000, 0x01);
		DBGPRINTF(("Force Calibration\r\n"));	
	}
}

void CapDetForceWakeUp(void)
{
	if(g_context.op_mode == 0)
	{
		
	}
	else
	{
		capdet_reg_write(0x005c, 0x00);
		DBGPRINTF(("Force WakeUp\r\n"));	
	}
}

void CapDetForceSleep(void)
{	
	if(g_context.op_mode == 3)
	{
		return;
	}
  capdet_reg_write(0x005c, 0x04);	
	DBGPRINTF(("Force Sleep\r\n"));
}

void CapDetAutoCalibration(void)
{	
		timer_1_disable();
		capdet_calibration_state |=BIT5;
//		capdet_calibration_state |=BIT7;
//		capdet_calibration_cnt=0;
//		CapDetForceWakeUp();
//		DBGPRINTF(("capdet_calibration->init_all\r\n"));
}

static void timer1_callback()
{
	#ifdef _USE_SYD_CAPDET_TOUCH_  //10S调用一次
	rtc_10s_cnt++;
	#ifdef _USE_SYD_CAPDET_POWERON_AWAYS_TOUCH_CALIBRATION_
	if(capdet_calibration_state &BIT4)
	{
		if(rtc_10s_cnt>=3)  //第一次开机校准时间短一些
		{
			CapDetAutoCalibration();
			capdet_calibration_state &=~BIT4;
			DBGPRINTF(("POWERON_AWAYS_TOUCH_CALIBRATION\r\n"));
		}
	}
	else
	{
		if(rtc_10s_cnt>=7)
		{
			CapDetAutoCalibration();
		}
	}
	#else
	if(rtc_10s_cnt>=7)
	{
		CapDetAutoCalibration();
	}
	#endif
	#endif
}
#endif

void CAP_Handler(void)
{
	bool int_get = capdet_process(&g_context);
	#ifdef  _USE_SYD_CAPDET_AUTO_CALIBRATION_
	if(TIMER_CTRL->TIMER_1_EN == 0)
	{
		timer_1_enable(32768, timer1_callback); //32ms运算一次  1032   64ms运算一次  2064
	}
    rtc_10s_cnt=0;
	if(capdet_calibration_state &BIT7)//BIT7 :0 空闲状态   1：正在校准
	{
		capdet_calibration_cnt++;
		if(capdet_calibration_cnt>=30)//30-IDLE1
		{
			capdet_calibration_state &=~BIT7;
			capdet_calibration_state |=BIT6;
			CapDetForceSleep();
			capdet_calibration_cnt=0;
		}
	}
	else if(capdet_calibration_state &BIT6)//BIT6 :0 空闲状态   1：校准结束
	{
		if(g_context.op_mode == 3)
		{
			if(g_context.frm[0]>15)
			{
				CapDetForceCalibration();
				CapDetForceWakeUp();
				capdet_calibration_state |=BIT7;
				DBGPRINTF(("calibration faile\r\n"));
			}
			else
			{
				DBGPRINTF(("calibration ok\r\n"));
			}
			capdet_calibration_state &=~BIT6;
			capdet_calibration_state  &=~BIT4;
		}
	}
	#endif
#if 0
	static uint8_t pre_op_mode = 0;
	if (pre_op_mode != g_context.op_mode) 
	{
		if (g_context.op_mode == 0) 
		{
			DBGPRINTF(("run mode\r\n"));
		}
		else if (g_context.op_mode == 1) 
		{
			DBGPRINTF(("idle1 mode\r\n"));
		}
		else if (g_context.op_mode == 2) 
		{
			DBGPRINTF(("idle2 mode\r\n"));
		}
		else if (g_context.op_mode == 3) 
		{
			DBGPRINTF(("sleep mode\r\n"));
		}
		pre_op_mode = g_context.op_mode;
	}
#endif

	if (int_get) //true if state change
	{
		#if ((0) && (defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)))
		DBGPRINTF("CH0: %4d  %4d  %d %d\r\n", g_context.debug_frm[0], g_context.frm[0], (g_context.btn & 0x01) >> 0,g_context.op_mode);
		#endif

		//ch0
		if ((g_context.btn & 0x01) == 0)
		{
			press_always_cnt=0;
			if (syd_capdet_key.press & 0x01)
			{
				syd_capdet_key.press &= 0xfe;
				#if defined(_DEBUG_)
				DBGPRINTF("ch0 release!\r\n");
				#endif
			}
		}
		else
		{
//			press_always_cnt++;
//			if(press_always_cnt>50*30)
//			{
//				timer_1_disable();
//				capdet_calibration_state |=BIT5;
//				#if defined(_DEBUG_)
//				DBGPRINTF("press always timerout force calibration!\r\n");
//				#endif
//			}
			if ((syd_capdet_key.press & 0x01) == 0)
			{
				
				syd_capdet_key.press |= 0x01;

				Timer_Evt_Start(EVT_20MS);

				#ifdef _SYD_CAPDET_TOUCH_SENSITIVE_
				capdet_touch_state |= CAPDET_TOUCH_STATE_CHECK;
				#endif
				#if defined(_DEBUG_)
				DBGPRINTF("ch0 press!\r\n");
				#endif
			}
		}
	}
}




uint8_t cap_int_flag = 0;
uint8_t touch_int_flag = 0;

void CAP_IRQHandler(void)
{
	
	capdet_int_handle(0);
	cap_int_flag = 1;
	CAP_Handler();
}

void TOUCH_IRQHandler(void)
{
#ifdef _SYD_CAPDET_TOUCH_SENSITIVE_
	capdet_touch_state = CAPDET_TOUCH_STATE_INT;
#if defined(_DEBUG_) || defined(_SYD_RTT_DEBUG_)
	DBGPRINTF("TOUCH_IRQHandler!\r\n");
#endif
#endif
//	touch_int_flag = 1;
	DBGPRINTF("TOUCH_IRQHandler!\r\n");
	capdet_int_handle(0);
}

#endif
