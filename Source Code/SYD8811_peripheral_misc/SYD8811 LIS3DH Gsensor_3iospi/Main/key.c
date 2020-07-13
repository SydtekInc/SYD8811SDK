#include "key.h"
#include "syd8801_gpio.h"
#include "syd8801_timer.h"

static void timer0_callback(void);
	
/*
key���ú��� 
key�ǵ͵�ƽ����
LED0~3��GPIO8~11
*/
void key_config(void){
	GPIO_Set_Input(KEY0 | KEY2 | KEY3 | KEY1);
}
/*
��ȡ����ֵ����
����ֵ��0��û�а�������
				1��SW1��GPIO8������
				2��SW1��GPIO9������
				3��SW1��GPIO10������
				4��SW1��GPIO11������
*/
uint8_t get_key(void){
		if(!GPIO_Pin_Read(KEY0)){
			return 1;
		}else if(!GPIO_Pin_Read(KEY1)){
			return 2;
		}else if(!GPIO_Pin_Read(KEY2)){
			return 3;
		}else if(!GPIO_Pin_Read(KEY3)){
			return 4;
		}else{
			return 0;
		}
}

/*
key���жϳ��̰����ĺ���
key�ǵ͵�ƽ����
LED0~3��GPIO8~11
*/
void keylong_config(void){
	GPIO_Set_Input(KEY0 | KEY2 | KEY3 | KEY1);
	timer_0_enable(0x20, timer0_callback); // 32 * 31.25 us = 1ms
	__enable_irq();
}
/*
key_sta:����״̬
key_sta[7] 0:�����ж�����δ��� 1�����������Ѿ���� ���Զ�ȡ��������ȡ����֮����������λ�����򰴼����򽫲����ٴ��жϰ�������
key_sta[6] 0���̰��� 1��������
key_sta[5] 0��û���κΰ������� 1���а������ڰ��£����ڽ��а����ȴ��ͷ�
key_sta[4:0] ������� ��1��Ϊ����1 2��Ϊ����2 .....
*/
uint8_t key_sta=0;
static void timer0_callback(void)
{
	static uint16_t time_cnt=0,key_cnt=0,key_pre=0;
	uint8_t key_now=0;
	time_cnt++;
	if(!(key_sta&0x80)){
		key_now=get_key();
		if((key_pre==key_now) && (key_now!=0)){    //0Ϊ��û�а��µ����
			key_cnt ++;
			if(key_cnt<20)key_sta =0;
			else if(key_cnt<1000){
				key_sta |=0x20;
				key_sta &=0xBF;   //�̰���
				key_sta |=key_now&0X1F;
			}else{
				key_sta |=0x40;
				key_sta |=key_now&0X1F;
				key_sta |=0x80;  //�����ж����
				key_cnt=0;
			} 
		}else{
			if(key_sta & 0x20){
				key_sta |=0x80;
			}
			key_cnt=0;
		}
		key_pre=key_now;
	}
}
