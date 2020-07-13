/*
PWMģ������ļ�

���ߣ�����ʢԴ��Ƽ����޹�˾
���ڣ�2016/7/8
*/
#include "syd8801_pwm.h"
#include "syd8801_gpio.h"
//�Ĵ�������
PWM_CTRL_TYPE *	PWM_0_CTRL	= ((PWM_CTRL_TYPE *)	PWM_0_CTRL_BASE);
PWM_CTRL_TYPE *	PWM_1_CTRL	= ((PWM_CTRL_TYPE *)	PWM_1_CTRL_BASE);
PWM_CTRL_TYPE *	PWM_2_CTRL	= ((PWM_CTRL_TYPE *)	PWM_2_CTRL_BASE);

/*
pwm0 ��ʼ������
����: PWM_x pwm_x Ҫ��ʼ����pwmģ�� �μ�PWM_MODEö��
			PWM_PARAMETER pwm_parameter pwm���� �μ�PWM_PARAMETER�ṹ��
������	
	PWM_PARAMETER pwm_parameter;
	//Flash mode
	pwm_parameter.MODE=flash_mode;
	pwm_parameter.T1=0x10; 	//16 * 1/32=0.5s ʵ��0.768563250
	pwm_parameter.T2=0x20;      //32 * 1/32=1s	ʵ��1.585201375
	pwm_parameter.T3=0x0000;
	pwm_parameter.N1=0x80;   //�����ظ���û��T3
	pwm_parameter.N2=0x80;   //�����ظ�
  pwm_enable(PWM_0,pwm_parameter);	
*/
void pwm_enable(PWM_x pwm_x,PWM_PARAMETER pwm_parameter)
{
	switch(pwm_x){
		case PWM_0 :
			PIN_CONFIG->PIN_2_SEL = PIN_SEL_PWM_0;
			switch(pwm_parameter.MODE){
				case pwm_mode :
					PWM_0_CTRL->MODE= 0x01;
					PWM_0_CTRL->PWM_M = pwm_parameter.PWM_M;;
					PWM_0_CTRL->PWM_N = pwm_parameter.PWM_N;
					PWM_0_CTRL->PAUS= 0x01;   //��������Ϊ1 �����������ֹͣ
					PWM_0_CTRL->PE= 1;
					break;
				case flash_mode :
					PWM_0_CTRL->MODE= 0x02;
					PWM_0_CTRL->T1 = pwm_parameter.T1;
					PWM_0_CTRL->T2 = pwm_parameter.T2;
					PWM_0_CTRL->T3 = pwm_parameter.T3;
				  PWM_0_CTRL->N1 = pwm_parameter.N1;
					PWM_0_CTRL->N2 = pwm_parameter.N2;
					PWM_0_CTRL->PAUS= 0x01;   
					PWM_0_CTRL->PE= 1;
					break;
				case breath_mode :
					PWM_0_CTRL->MODE= 0x03;
					PWM_0_CTRL->BR_TH_MAX= pwm_parameter.BR_TH_MAX;
					PWM_0_CTRL->BR_TH_MIN = pwm_parameter.BR_TH_MIN;
					PWM_0_CTRL->BR_SP = pwm_parameter.BR_SP;
					PWM_0_CTRL->T4 = pwm_parameter.T4;
					PWM_0_CTRL->PAUS= 0x01;  
					PWM_0_CTRL->PE= 1;
					break;
			}
			break;
		case PWM_1 :
			PIN_CONFIG->PIN_1_SEL = PIN_SEL_PWM_1;
			switch(pwm_parameter.MODE){
				case pwm_mode :
					PWM_1_CTRL->MODE= 0x01;
					PWM_1_CTRL->PWM_M = pwm_parameter.PWM_M;;
					PWM_1_CTRL->PWM_N = pwm_parameter.PWM_N;
					PWM_1_CTRL->PAUS= 0x01;   
					PWM_1_CTRL->PE= 1;
					break;
				case flash_mode :
					PWM_1_CTRL->MODE= 0x02;
					PWM_1_CTRL->T1 = pwm_parameter.T1;
					PWM_1_CTRL->T2 = pwm_parameter.T2;
					PWM_1_CTRL->T3 = pwm_parameter.T3;
				  PWM_1_CTRL->N1 = pwm_parameter.N1;
					PWM_1_CTRL->N2 = pwm_parameter.N2;
					PWM_1_CTRL->PAUS= 0x01;   
					PWM_1_CTRL->PE= 1;
					break;
				case breath_mode :
					PWM_1_CTRL->MODE= 0x03;
					PWM_1_CTRL->BR_TH_MAX= pwm_parameter.BR_TH_MAX;
					PWM_1_CTRL->BR_TH_MIN = pwm_parameter.BR_TH_MIN;
					PWM_1_CTRL->BR_SP = pwm_parameter.BR_SP;
					PWM_1_CTRL->T4 = pwm_parameter.T4;
					PWM_1_CTRL->PAUS= 0x01;
					PWM_1_CTRL->PE= 1;
					break;
			}
			break;
		case PWM_2 :
			PIN_CONFIG->PIN_0_SEL = PIN_SEL_PWM_2;
			switch(pwm_parameter.MODE){
				case pwm_mode :
					PWM_2_CTRL->MODE= 0x01;
					PWM_2_CTRL->PWM_M = pwm_parameter.PWM_M;
					PWM_2_CTRL->PWM_N = pwm_parameter.PWM_N;
					PWM_2_CTRL->PAUS= 0x01; 
					PWM_2_CTRL->PE= 1;
					break;
				case flash_mode :
					PWM_2_CTRL->MODE= 0x02;
					PWM_2_CTRL->T1 = pwm_parameter.T1;
					PWM_2_CTRL->T2 = pwm_parameter.T2;
					PWM_2_CTRL->T3 = pwm_parameter.T3;
				  PWM_2_CTRL->N1 = pwm_parameter.N1;
					PWM_2_CTRL->N2 = pwm_parameter.N2;
					PWM_2_CTRL->PAUS= 0x01;   
					PWM_2_CTRL->PE= 1;
					break;
				case breath_mode :
					PWM_2_CTRL->MODE= 0x03;
					PWM_2_CTRL->BR_TH_MAX= pwm_parameter.BR_TH_MAX;
					PWM_2_CTRL->BR_TH_MIN = pwm_parameter.BR_TH_MIN;
					PWM_2_CTRL->BR_SP = pwm_parameter.BR_SP;
					PWM_2_CTRL->T4 = pwm_parameter.T4;
					PWM_2_CTRL->PAUS= 0x01;
					PWM_2_CTRL->PE= 1;
					break;
			}
			break;
	}
}
void pwm_disable(PWM_x pwm_x)
{
	switch(pwm_x){
		case PWM_0 :
			PWM_0_CTRL->PE= 0;
			break;
		case PWM_1 :
			PWM_1_CTRL->PE= 0;
			break;
		case PWM_2 :
			PWM_2_CTRL->PE= 0;
			break;
	}
}

