/*
主函数文件
测试步骤：
1.确保已经连接上开发板并安装上CH340的驱动程序，并且自设备管理器下可以看到串口号
2.打开工程目录下Tool文件夹里的“SYD BLE Utility.exe”程序
3.在UART里可以看到串口号，选择正确的串口
4.点击“open”按钮，此时在"SYD8811 Evaluation board"里提示:"Wait..."
5.此时按下开发板上的复位键，提示就会变成“Ready”
6.在“Firmware”的"FW(Upgrade)"中点击“Open FW File”按钮选择本工程在“Objects”文件夹的“Module_samples.hex”文件
7.在“Firmware”的"FW(Upgrade)"中点击“Write to Flah”按钮,即可看到下载进度，等待下载完成
8.下载完成后按下复位键即可看到本实验现象
9.再次下载：点击"SYD8801 Evaluation board"的Detect按钮，然后从第5步再次操作即可
备注：对于已经下载了串口程序的板子，有时候一点击“open”按钮就进入了readey状态，这时候一般是下不进程序的，这时候可以一直按着复位键然后点击“open”按钮，当进入waite状态时候放开复位键，这样就可以下载程序了

作者：北京盛源达科技有限公司
日期：2016/7/8
*/
#include <string.h>
#include "ARMCM0.h"
#include "uart.h"
#include "delay.h"
#include "debug.h"
#include "gpio.h"
#include "pwm.h"
#include "lib.h"
#include "config.h"

void LPWM_Init(void)
{
	PWM_PARAMETER pwm_parameter;
	
	//配置晶振 - 默认使用内部32K晶振
#if 1
	//Flash mode
	memset((void *)&pwm_parameter, 0x00, sizeof(PWM_PARAMETER));
	pwm_parameter.MODE=flash_mode;
	pwm_parameter.T1=0x10;		//16 * 1/32=0.5s
	pwm_parameter.T2=0x20;		//32 * 1/32=1s
	pwm_parameter.T3=0x20;	//32 * 1/32=1s
	pwm_parameter.N1=0x80;	 	//指定flash格式 -> 是否有T3 : 0x80(No T3)
	pwm_parameter.N2=0x80;	 	//指定flash重复次数
	pwm_enable(PWM_0, pwm_parameter);
#endif

#if 1
	//Breath mode timing
	pwm_parameter.MODE=breath_mode;
	pwm_parameter.BR_TH_MAX=20;		//20/2=10ms
	pwm_parameter.BR_TH_MIN=4;   	//4/2=2ms
	pwm_parameter.T4=20;	 				//20/2=10ms
	pwm_parameter.BR_SP=4;  	    //4/32ms = 1/8ms = 125us
	pwm_enable(PWM_1, pwm_parameter);
#endif

#if 1
	//PWM mode timing 
	pwm_parameter.MODE=pwm_mode;
	pwm_parameter.PWM_N=125;	//n/32ms
	pwm_parameter.PWM_M=250;	//m/32ms
	pwm_enable(PWM_2,pwm_parameter);
#endif
}

void HPWM_Handler(void)
{
	HPWM_PARAMETER hpwm;
	//common parameters
#if 1	
	//hpwm.prescaler = HPWM_PERSCALER_1;	//计数频率64M/1，周期 0.015625us = 15ns
	hpwm.prescaler = HPWM_PERSCALER_64;	//计数频率64M/64，周期 1us
	//hpwm.prescaler = HPWM_PERSCALER_32768;	//计数频率64M/32768，周期 512us
	//hpwm.prescaler = HPWM_PERSCALER_4;	//计数频率64M/4，周期 0.0625us
	hpwm.mode = UP_MODE;      //计数方向向上
	hpwm.period = 100;				//100*计数周期 = 100us. 如果是UP_DOWN_MODE,周期会加倍
#else
	hpwm.prescaler = HPWM_PERSCALER_16;	//计数频率25M/1，周期 0.64us
	hpwm.mode = UP_DOWN_MODE;
	hpwm.period = 100;				//100*0.64us = 64us
#endif

#if 1	
	//ch0 parameters
	hpwm.channel = HPWM_CH0;
	hpwm.polarity = HIGH_FIRST;
	hpwm.duty = 1;
	Hpwm_Init(&hpwm);
#endif
#if 1
	//ch1 parameters
	hpwm.channel = HPWM_CH1;
	hpwm.polarity = HIGH_FIRST;
	hpwm.duty = 1;
	Hpwm_Init(&hpwm);
#endif
#if 1
	//ch2 parameters
	hpwm.channel = HPWM_CH2;
	hpwm.polarity = HIGH_FIRST;
	hpwm.duty = 1;
	Hpwm_Init(&hpwm);
#endif
#if 1
	//ch3 parameters
	hpwm.channel = HPWM_CH3;
	hpwm.polarity = HIGH_FIRST;
	hpwm.duty = 1;
	Hpwm_Init(&hpwm);
#endif
	//
	Hpwm_Start();
}

int main(void)
{
	
	__disable_irq();
	
	BleInit();
	MCUClockSwitch(SYSTEM_CLOCK_64M_RCOSC);
	RCOSCCalibration();

// ClockSwitch(SYSTEM_32K_CLOCK_32MXO_DIV);
// LPOCalibration();

	ClockSwitch(SYSTEM_32K_CLOCK_RCOSC);
	LPOCalibration();
	
	dbg_init();
	UartEn(true);
	dbg_printf("SYD8811 PWM test demo %s:%s\r\n",__DATE__ ,__TIME__);

	//slow pwm
	PIN_Set_GPIO(U32BIT(LPWM0_GPIO), PIN_SEL_PWM_0);
	PIN_Set_GPIO(U32BIT(LPWM1_GPIO), PIN_SEL_PWM_1);
	PIN_Set_GPIO(U32BIT(LPWM2_GPIO), PIN_SEL_PWM_2);

	LPWM_Init();
	
	PIN_Set_GPIO(U32BIT(HPWM0_GPIO), PIN_SEL_HPWM_CH0);
	PIN_Set_GPIO(U32BIT(HPWM1_GPIO), PIN_SEL_HPWM_CH1);
	PIN_Set_GPIO(U32BIT(HPWM2_GPIO), PIN_SEL_HPWM_CH2);
	PIN_Set_GPIO(U32BIT(HPWM3_GPIO), PIN_SEL_HPWM_CH3);

	 
	HPWM_Handler();
	dbg_printf("SYD8811 PWM test demo %s:%s\r\n",__DATE__ ,__TIME__);
	__enable_irq();			////////////////////////////HPWM有中断功能///////////////////////////////////////
	
	while(1)
	{

	}
}


