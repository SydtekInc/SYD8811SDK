/*
led�����ļ�

���ߣ�����ʢԴ��Ƽ����޹�˾
���ڣ�2016/7/8
*/
#include "led.h"
#include "syd8801_gpio.h"

/*
LED���ú��� 
���������	uint32_t led ָ����LED�ܽ�λ������0x01��ʾLED��GPIO0�� 0x20��ʾLED��GPIO1,0X80��ʾ��GPIO7
LED�ǵ͵�ƽ����
*/
void led_config(uint32_t led){
	GPIO_Set_Output(led);
	GPIO_Pin_Set(led);   //Ĭ�Ϲص�
}

/*
LED�������� 
���������	uint32_t led ָ����LED�ܽ�λ������0x01��ʾLED��GPIO0�� 0x20��ʾLED��GPIO1,0X80��ʾ��GPIO7
LED�ǵ͵�ƽ����
*/
void led_open(uint32_t led){
	GPIO_Pin_Clear(led);
}
/*
LEDϨ���� 
���������	uint32_t led ָ����LED�ܽ�λ������0x01��ʾLED��GPIO0�� 0x20��ʾLED��GPIO1,0X80��ʾ��GPIO7
LED�ǵ͵�ƽ����
*/
void led_close(uint32_t led){
  GPIO_Pin_Set(led);
}
/*
LED��ת����
���������	uint32_t led ָ����LED�ܽ�λ������0x01��ʾLED��GPIO0�� 0x20��ʾLED��GPIO1,0X80��ʾ��GPIO7
LED�ǵ͵�ƽ����
*/
void led_turn(uint32_t led){
		GPIO_Pin_Turn(led);
}
