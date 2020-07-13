/*
ADC�����ļ�

���ߣ�����ʢԴ��Ƽ����޹�˾
���ڣ�2016/7/8
*/
#include "syd8801_adc.h"
#include "syd8801_gpio.h"

//�Ĵ�����ַ����
BI_CTRL_TYPE *	BI_CTRL	= ((BI_CTRL_TYPE *)	BI_CTRL_BASE);   
/*
adc��ʼ������
���룺uint8_t cha Ҫ��ʼ����ADCͨ��
			0��CH0/ VBAT
			1��CH1/VBAT1V
			2��CH2/GPIO0
			3��CH3/GPIO1
ע�⣺����������ADC���ڲ��ģ�����ADC���ⲿ�ܽ�
*/
void adc_init(uint8_t cha){
	BI_CTRL->GPADC_EN=0;
	switch(cha){
		case 2:
			PIN_CONFIG->PIN_0_SEL = PIN_SEL_ANALOG_INPUT;
			break;
		case 3:
			PIN_CONFIG->PIN_0_SEL = PIN_SEL_ANALOG_INPUT;
			break;
		default :
			break;
	}
	BI_CTRL->GPADC_CHSEL=cha;
	BI_CTRL->GPADC_DONE=0;
}
/*
adc��ȡADC����
ע�⣺������ﲻ���ϳ�ʱ�˳��Ļ������ｫ�п��ܱ�����
*/
uint16_t get_adcval(void){
	uint16_t i=0;
	do{
		i++;
	}while((! BI_CTRL->GPADC_DONE) && (i<0xfff0));
	BI_CTRL->GPADC_DONE=0;
	if(i>=0xfff0) return 0xffff;
	else 	return BI_CTRL->GPADC_DATA;
}
/*
adc�رպ���
*/
void adc_close(void){
	BI_CTRL->GPADC_EN=0;
	BI_CTRL->GPADC_DONE=0;
}
/*
adc�򿪺��� ��ʼһ��ADCת��
*/
void adc_open(void){
	BI_CTRL->GPADC_DONE=0;
	BI_CTRL->GPADC_EN=1;
}
