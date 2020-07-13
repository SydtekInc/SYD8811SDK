/*
看门狗操作文件

作者：北京盛源达科技有限公司
日期：2016/7/8
*/
#include "wdt.h"

WDT_CTRL_TYPE * WDT_CTRL = ((WDT_CTRL_TYPE *) WDT_BASE);
/*
看门狗初始化函数
参数: uint16_t count 看门狗计数器初始值 计数器是递减计数器 单位：256/32.768 = 7.8ms
*/
void wdt_enable(uint16_t count)
{
	//dbg_printf("WDT_CTRL = 0x%08x\r\n", *(uint32_t *)WDT_CTRL);

	WDT_CTRL->WDT_CLR = 1;			/*必须的*/
	WDT_CTRL->WDT_TIME = count;		/*time越短，越容易测试到死机*/
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
禁用看门狗
*/
void wdt_disable()
{
	WDT_CTRL->WDT_EN = 0;
}

