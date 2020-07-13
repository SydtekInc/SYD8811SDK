#include "key.h"
#include "syd8801_gpio.h"
#include "syd8801_timer.h"

static void timer0_callback(void);
	
/*
key配置函数 
key是低电平点亮
LED0~3在GPIO8~11
*/
void key_config(void){
	GPIO_Set_Input(KEY0 | KEY2 | KEY3 | KEY1);
}
/*
获取按键值函数
返回值：0：没有按键按下
				1：SW1（GPIO8）按下
				2：SW1（GPIO9）按下
				3：SW1（GPIO10）按下
				4：SW1（GPIO11）按下
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
key有判断长短按键的函数
key是低电平点亮
LED0~3在GPIO8~11
*/
void keylong_config(void){
	GPIO_Set_Input(KEY0 | KEY2 | KEY3 | KEY1);
	timer_0_enable(0x20, timer0_callback); // 32 * 31.25 us = 1ms
	__enable_irq();
}
/*
key_sta:按键状态
key_sta[7] 0:按键判断流程未完成 1：按键流程已经完成 可以读取按键，读取按键之后必须清除该位，否则按键程序将不会再次判断按键输入
key_sta[6] 0：短按键 1：长按键
key_sta[5] 0：没有任何按键按下 1：有按键正在按下，正在进行按键等待释放
key_sta[4:0] 按键编号 如1则为按键1 2则为按键2 .....
*/
uint8_t key_sta=0;
static void timer0_callback(void)
{
	static uint16_t time_cnt=0,key_cnt=0,key_pre=0;
	uint8_t key_now=0;
	time_cnt++;
	if(!(key_sta&0x80)){
		key_now=get_key();
		if((key_pre==key_now) && (key_now!=0)){    //0为都没有按下的情况
			key_cnt ++;
			if(key_cnt<20)key_sta =0;
			else if(key_cnt<1000){
				key_sta |=0x20;
				key_sta &=0xBF;   //短按键
				key_sta |=key_now&0X1F;
			}else{
				key_sta |=0x40;
				key_sta |=key_now&0X1F;
				key_sta |=0x80;  //按键判断完成
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
