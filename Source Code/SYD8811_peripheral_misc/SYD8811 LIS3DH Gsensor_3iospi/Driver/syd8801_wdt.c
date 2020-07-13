/*
看门狗操作文件

作者：北京盛源达科技有限公司
日期：2016/7/8
*/
#include "syd8801_wdt.h"

WDT_CTRL_TYPE * WDT_CTRL = ((WDT_CTRL_TYPE *) WDT_BASE);
/*
看门狗初始化函数
参数: uint16_t count 看门狗计数器初始值 计数器是递减计数器 单位：1/32.768ms
*/
void wdt_enable(uint16_t count)
{
	WDT_CTRL->WDT_TIME = count;
	WDT_CTRL->WDT_EN = 1;
}
/*
清除看门狗函数 
这里将会把计数器的值设置回初始值
*/
void wdt_clear()
{
	WDT_CTRL->WDT_CLR=1;
}
/*
失能看门狗  看门狗将不能够复位系统
*/
void wdt_disable()
{
	WDT_CTRL->WDT_EN = 0;
}

