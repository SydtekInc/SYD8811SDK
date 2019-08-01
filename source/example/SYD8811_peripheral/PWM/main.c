/*
�������ļ�
���Բ��裺
1.ȷ���Ѿ������Ͽ����岢��װ��CH340���������򣬲������豸�������¿��Կ������ں�
2.�򿪹���Ŀ¼��Tool�ļ�����ġ�SYD BLE Utility.exe������
3.��UART����Կ������ںţ�ѡ����ȷ�Ĵ���
4.�����open����ť����ʱ��"SYD8811 Evaluation board"����ʾ:"Wait..."
5.��ʱ���¿������ϵĸ�λ������ʾ�ͻ��ɡ�Ready��
6.�ڡ�Firmware����"FW(Upgrade)"�е����Open FW File����ťѡ�񱾹����ڡ�Objects���ļ��еġ�Module_samples.hex���ļ�
7.�ڡ�Firmware����"FW(Upgrade)"�е����Write to Flah����ť,���ɿ������ؽ��ȣ��ȴ��������
8.������ɺ��¸�λ�����ɿ�����ʵ������
9.�ٴ����أ����"SYD8801 Evaluation board"��Detect��ť��Ȼ��ӵ�5���ٴβ�������
��ע�������Ѿ������˴��ڳ���İ��ӣ���ʱ��һ�����open����ť�ͽ�����readey״̬����ʱ��һ�����²�������ģ���ʱ�����һֱ���Ÿ�λ��Ȼ������open����ť��������waite״̬ʱ��ſ���λ���������Ϳ������س�����

���ߣ�����ʢԴ��Ƽ����޹�˾
���ڣ�2016/7/8
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
	
	//���þ��� - Ĭ��ʹ���ڲ�32K����
#if 1
	//Flash mode
	memset((void *)&pwm_parameter, 0x00, sizeof(PWM_PARAMETER));
	pwm_parameter.MODE=flash_mode;
	pwm_parameter.T1=0x10;		//16 * 1/32=0.5s
	pwm_parameter.T2=0x20;		//32 * 1/32=1s
	pwm_parameter.T3=0x20;	//32 * 1/32=1s
	pwm_parameter.N1=0x80;	 	//ָ��flash��ʽ -> �Ƿ���T3 : 0x80(No T3)
	pwm_parameter.N2=0x80;	 	//ָ��flash�ظ�����
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
	//hpwm.prescaler = HPWM_PERSCALER_1;	//����Ƶ��64M/1������ 0.015625us = 15ns
	hpwm.prescaler = HPWM_PERSCALER_64;	//����Ƶ��64M/64������ 1us
	//hpwm.prescaler = HPWM_PERSCALER_32768;	//����Ƶ��64M/32768������ 512us
	//hpwm.prescaler = HPWM_PERSCALER_4;	//����Ƶ��64M/4������ 0.0625us
	hpwm.mode = UP_MODE;      //������������
	hpwm.period = 100;				//100*�������� = 100us. �����UP_DOWN_MODE,���ڻ�ӱ�
#else
	hpwm.prescaler = HPWM_PERSCALER_16;	//����Ƶ��25M/1������ 0.64us
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
	__enable_irq();			////////////////////////////HPWM���жϹ���///////////////////////////////////////
	
	while(1)
	{

	}
}


