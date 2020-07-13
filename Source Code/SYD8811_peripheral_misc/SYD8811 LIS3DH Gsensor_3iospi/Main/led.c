/*
led操作文件

作者：北京盛源达科技有限公司
日期：2016/7/8
*/
#include "led.h"
#include "syd8801_gpio.h"

/*
LED配置函数 
传入参数：	uint32_t led 指定的LED管脚位，比如0x01表示LED在GPIO0， 0x20表示LED在GPIO1,0X80表示第GPIO7
LED是低电平点亮
*/
void led_config(uint32_t led){
	GPIO_Set_Output(led);
	GPIO_Pin_Set(led);   //默认关灯
}

/*
LED点亮函数 
传入参数：	uint32_t led 指定的LED管脚位，比如0x01表示LED在GPIO0， 0x20表示LED在GPIO1,0X80表示第GPIO7
LED是低电平点亮
*/
void led_open(uint32_t led){
	GPIO_Pin_Clear(led);
}
/*
LED熄灭函数 
传入参数：	uint32_t led 指定的LED管脚位，比如0x01表示LED在GPIO0， 0x20表示LED在GPIO1,0X80表示第GPIO7
LED是低电平点亮
*/
void led_close(uint32_t led){
  GPIO_Pin_Set(led);
}
/*
LED翻转函数
传入参数：	uint32_t led 指定的LED管脚位，比如0x01表示LED在GPIO0， 0x20表示LED在GPIO1,0X80表示第GPIO7
LED是低电平点亮
*/
void led_turn(uint32_t led){
		GPIO_Pin_Turn(led);
}
