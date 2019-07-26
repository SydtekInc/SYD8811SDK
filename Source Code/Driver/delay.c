/*
延时函数文件

作者：北京盛源达科技有限公司
日期：2016/7/8
*/
#include "delay.h"
/*
n毫秒延时函数
参数: uint16_t n 要延时的毫秒数 单位：1ms
*/
void delay_ms(uint16_t n){
	uint16_t i,j;
	for(i=0;i<n;i++)
			for(j=0;j<2700;j++);
}
/*
n微秒延时函数
参数: uint16_t n 要延时的微秒数 单位：1us
*/
void delay_us(uint16_t n){
	uint16_t i,j;
	for(i=0;i<n;i++)
			for(j=0;j<2;j++);
}
