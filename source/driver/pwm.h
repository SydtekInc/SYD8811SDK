#ifndef _PWM_H_
#define _PWM_H_

#include "ARMCM0.h"

#define 	HPWM_CLK			64000000UL			//设计值

//PWM模块枚举
typedef enum {
	PWM_0,
	PWM_1,
	PWM_2,
}PWM_x;

typedef enum {
	HPWM_CH0 = 0x01,
	HPWM_CH1 = 0x02,
	HPWM_CH2 = 0x04,
	HPWM_CH3 = 0x08,
	HPWM_CHALL = 0x0f,
}HPWM_CHx;

//PWM模块工作模式枚举
typedef enum {
	always_on_mode,
	pwm_mode,
	flash_mode,
	breath_mode,
}PWM_mode;

typedef enum {
	UP_MODE,
	UP_DOWN_MODE,
}HPWM_mode;

typedef enum {
	HPWM_INT_NONE = 0,
    HPWM_INT_PERIOD = 1,
    HPWM_INT_TASK_STOP = 2,
    HPWM_INT_ALL  = 3,
} HPWM_INT_TYPE;

typedef enum {
    HPWM_PERSCALER_1 = 0,
    HPWM_PERSCALER_2 = 1,
	HPWM_PERSCALER_4 = 2,
	HPWM_PERSCALER_8 = 3,
	HPWM_PERSCALER_16 = 4,
	HPWM_PERSCALER_32 = 5,
	HPWM_PERSCALER_64 = 6,
	HPWM_PERSCALER_128 = 7,
	HPWM_PERSCALER_256 = 8,
	HPWM_PERSCALER_512 = 9,
	HPWM_PERSCALER_1024 = 10,
	HPWM_PERSCALER_2048 = 11,
	HPWM_PERSCALER_4096 = 12,
	HPWM_PERSCALER_8192 = 13,
	HPWM_PERSCALER_16384 = 14,
	HPWM_PERSCALER_32768 = 15
} HPWM_PERSCALER_TYPE;

typedef enum {
	LOW_FIRST = 0,
	HIGH_FIRST
} HPWM_POLARITY_TYPE;

//PWM参数
typedef struct{
	uint8_t  module;   //模块 使用那个pwm模块
	
	//----------------------------flash mode------------------------------
	uint8_t  T1;  //T1 value(high level time) for flash mode. Unit:1/32 S
	uint8_t  T2;  //T2 value(T1 + low level time) for flash mode. Unit:1/32 S
	uint16_t T3;  //T3 value(low level time) for flash mode. Unit:1/32 S
	uint8_t  N1;  //repeat "T1-T2" N1 times. If N1 set 0x80 then always repeat "T1-T2" and No T3
	uint8_t  N2;  //repeat "flash" N2 times. If N2 set 0x80 then always repeat "flash".
	//----------------------------breath mode------------------------------
	uint8_t  T4;  //breath mode , flash period. Unit:1/2ms 
	uint8_t  BR_TH_MAX;   //breath mode maxinum briteness threshlod of the LED.Unit:1/2ms
	uint8_t  BR_TH_MIN;   //breath mode minnum briteness threshlod of the LED.Unit:1/2ms
	uint8_t  BR_SP;  //BR_SP : breath mode speed.indicate the breath speed. Unit:1/32 ms
	//----------------------------PWM mode------------------------------
	uint8_t  PWM_N;	   //N value for PWM mode. Unit:1/32 ms
	uint8_t  PWM_M;	   //M value for PWM mode. Unit:1/32 ms

	uint8_t  MODE;   // 1 : PWM mode   2 : flash mode.   3 : breath mode.
}PWM_PARAMETER;

//HPWM参数
typedef struct{
	HPWM_CHx  channel;
	HPWM_mode mode;
	HPWM_PERSCALER_TYPE  prescaler;
	HPWM_POLARITY_TYPE   polarity;
	uint16_t  period;
	uint16_t  duty;
}HPWM_PARAMETER;

extern void pwm_enable(PWM_x pwm_x,PWM_PARAMETER pwm_parameter);
extern void pwm_disable(PWM_x pwm_x);
extern void Hpwm_Init(HPWM_PARAMETER *pwm_parameter);
extern void Hpwm_Set_duty(HPWM_CHx  channels, uint16_t compare);
extern void Hpwm_Set_period(uint16_t period);
extern void Hpwm_Set_mode(HPWM_mode mode);
extern void Hpwm_Start(void);
extern void Hpwm_Stop(void);

#endif

