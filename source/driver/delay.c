/*
��ʱ�����ļ�

���ߣ�����ʢԴ��Ƽ����޹�˾
���ڣ�2016/7/8
*/
#include "delay.h"
/*
n������ʱ����
����: uint16_t n Ҫ��ʱ�ĺ����� ��λ��1ms
*/
void delay_ms(uint16_t n){
	uint16_t i,j;
	for(i=0;i<n;i++)
			for(j=0;j<2700;j++);
}
/*
n΢����ʱ����
����: uint16_t n Ҫ��ʱ��΢���� ��λ��1us
*/
void delay_us(uint16_t n){
	uint16_t i,j;
	for(i=0;i<n;i++)
			for(j=0;j<2;j++);
}
