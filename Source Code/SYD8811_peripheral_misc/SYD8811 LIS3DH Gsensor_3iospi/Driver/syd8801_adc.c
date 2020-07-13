/*
ADC操作文件

作者：北京盛源达科技有限公司
日期：2016/7/8
*/
#include "syd8801_adc.h"
#include "syd8801_gpio.h"

//寄存器地址声明
BI_CTRL_TYPE *	BI_CTRL	= ((BI_CTRL_TYPE *)	BI_CTRL_BASE);   
/*
adc初始化函数
输入：uint8_t cha 要初始化的ADC通道
			0：CH0/ VBAT
			1：CH1/VBAT1V
			2：CH2/GPIO0
			3：CH3/GPIO1
注意：这里有两个ADC是内部的，两个ADC是外部管脚
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
adc获取ADC函数
注意：如果这里不加上超时退出的话，这里将有可能被卡死
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
adc关闭函数
*/
void adc_close(void){
	BI_CTRL->GPADC_EN=0;
	BI_CTRL->GPADC_DONE=0;
}
/*
adc打开函数 开始一次ADC转换
*/
void adc_open(void){
	BI_CTRL->GPADC_DONE=0;
	BI_CTRL->GPADC_EN=1;
}
