#ifndef _PWM_H_
#define _PWM_H_

#include "ARMCM0.h"

extern PWM_CTRL_TYPE *	PWM_0_CTRL;
extern PWM_CTRL_TYPE *	PWM_1_CTRL;
extern PWM_CTRL_TYPE *	PWM_2_CTRL;

//PWM模块枚举
typedef enum PWM_X{
	PWM_0,
	PWM_1,
	PWM_2,
}PWM_x;

//PWM模块模型枚举
typedef enum PWM_MODE{
	pwm_mode,
	flash_mode,
	breath_mode,
}PWM_mode;

//PWM参数数组
typedef struct{
	uint8_t  module;   //模块 使用那个pwm模块
	uint8_t  T1;  //T1 value for flash mode. Unit:1/32 S
	uint8_t  T2;  //T2 value for flash mode. Unit:1/32 S
	uint16_t  T3; //T3value for flash mode. Unit:1/32 S
	uint8_t  N1;  //repeat "T1-T2" N1 times. If N1 set 0x80 then always repeat "T1-T2" and No T3
	uint8_t  N2;  //repeat "flash1" N2 times. If N2 set 0x80 then always repeat "flash1".
	uint8_t  T4;  //breath mode , flash period. Unit:1/2ms 
	uint8_t  BR_TH_MAX;   //breath mode maxinum briteness threshlod of the LED.Unit:1/2ms
	uint8_t  BR_TH_MIN;   //breath mode minnum briteness threshlod of the LED.Unit:1/2ms
	uint8_t  PWM_M;	   //M value for PWM mode. Unit:1/32 ms
	uint8_t  BR_SP;  //BR_SP : breath mode speed.indicate the breath speed. Unit:1/32 ms
	uint8_t  MODE;   //1 : PWM mode   2 : flash mode.   3 : breath mode.
	uint8_t  PWM_N;	   //N value for PWM mode. Unit:1/32 ms
}PWM_PARAMETER;

void pwm_enable(PWM_x pwm_x,PWM_PARAMETER pwm_parameter);
void pwm_disable(PWM_x pwm_x);

#endif

