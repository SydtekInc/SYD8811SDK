/*
gpio操作文件

作者：北京盛源达科技有限公司
日期：2016/7/8
*/
#include "syd8801_gpio.h"

//寄存器地址声明
PIN_CONFIG_TYPE *	PIN_CONFIG	= ((PIN_CONFIG_TYPE *)	PIN_CONFIG_BASE);    //管脚控制寄存器
GPO_CTRL_TYPE *	GPO_CTRL	= ((GPO_CTRL_TYPE *)		GPO_CTRL_BASE);          //GPIO口管脚输出控制寄存器，置位则管脚输出高电平，反之低电平
GPI_CTRL_TYPE *	GPI_CTRL	= ((GPI_CTRL_TYPE *)		GPI_CTRL_BASE);
GPIO_IRQ_CTRL_TYPE * GPIO_IRQ_CTRL = ((GPIO_IRQ_CTRL_TYPE *) GPIO_IRQ_CTRL_BASE);

static void (*gpio_callback)(void);

/*
设置管脚为输出函数
参数: uint32_t io 要设置的gpio管脚所在的位，比如0x00设置GPIO0 0X02->GPIO1 0X40->GPIO2 0XFF->GPIO[7:0]
举例：GPIO_Set_Output(0x0f);   设置gpio0~gpio7为输出
			GPIO_Set_Output(BIT0 | BIT1 | BIT2 | BIT3);   设置gpio0~gpio3为输出
*/
void GPIO_Set_Output(uint32_t io)
{
	uint32_t i=0,j=0;
	PIN_CONFIG->GPIODIR &= (~io) ;
	for(i=0x01,j=0;i!=0x10000000;i<<=1,j++){
		if(io&i){
			PIN_CONFIG->GPIOSEL[j/8] &= ~(0xf<<((j%8)*4));
			PIN_CONFIG->GPIOSEL[j/8] |= PIN_SEL_GENERAL_GPIO<<((j%8)*4);
		}
	}
}
/*
设置管脚为输入函数
参数: uint32_t io 要设置的gpio管脚所在的位，比如0x00设置GPIO0 0X02->GPIO1 0X40->GPIO2 0XFF->GPIO[7:0]
举例：GPIO_Set_Input(0x0f);   设置gpio0~gpio3为输出状
			GPIO_Set_Input(BIT0 | BIT1 | BIT2 | BIT3);   设置gpio0~gpio3为输出
*/
void GPIO_Set_Input(uint32_t io)
{
	uint32_t i=0,j=0;
	for(i=0x01,j=0;i!=0x10000000;i<<=1,j++){
		if(io&i){
			PIN_CONFIG->GPIOSEL[j/8] &= ~(0xf<<((j%8)*4));
			PIN_CONFIG->GPIOSEL[j/8] |= PIN_SEL_GENERAL_GPIO<<((j%8)*4);
		}
	}
	PIN_CONFIG->GPIODIR |= io;
	PIN_CONFIG->GPIO_PULL_UP |= io;     //上垃
	PIN_CONFIG->GPIO_POL  &= (~io) ;   //不取反
}
/*
设置管脚输出高电平函数
参数: uint32_t io 要设置的gpio管脚所在的位，比如0x00设置GPIO0 0X02->GPIO1 0X40->GPIO2 0XFF->GPIO[7:0]
举例：GPIO_Pin_Set(0xff);   设置gpio0~gpio7输出高电平
			GPIO_Set_Input(BIT0 | BIT1 | BIT2 | BIT3 | BIT4 | BIT5 | BIT6 | BIT7);    设置gpio0~gpio3输出高电平
*/
void GPIO_Pin_Set(uint32_t io)
{
	GPO_CTRL->GPO |= io;
}
/*
设置管脚输出低电平函数
参数: uint32_t io 要设置的gpio管脚所在的位，比如0x00设置GPIO0 0X02->GPIO1 0X40->GPIO2 0XFF->GPIO[7:0]
举例：GPIO_Pin_Set(0xff);   设置gpio0~gpio3输出低电平
			GPIO_Set_Input(BIT0 | BIT1 | BIT2 | BIT3 | BIT4 | BIT5 | BIT6 | BIT7);    设置gpio0~gpio7输出低电平
*/
void GPIO_Pin_Clear(uint32_t io)
{
	GPO_CTRL->GPO &= ~io;
}
/*
设置管脚输出翻转函数
参数: uint32_t io 要设置的gpio管脚所在的位，比如0x00设置GPIO0 0X02->GPIO1 0X40->GPIO2 0XFF->GPIO[7:0]
举例：GPIO_Pin_Turn(0xff);   设置gpio0~gpio3输出低电平
			GPIO_Pin_Turn(BIT0 | BIT1 | BIT2 | BIT3 | BIT4 | BIT5 | BIT6 | BIT7);    设置gpio0~gpio7输出低电平
*/
void GPIO_Pin_Turn(uint32_t io)
{
	*(uint32_t *)GPO_CTRL =*(uint32_t *)GPO_CTRL ^ io;
}
/*
读回管脚状态函数
参数: uint32_t io 要设置的gpio管脚所在的位，比如0x00设置GPIO0 0X02->GPIO1 0X40->GPIO2 0XFF->GPIO[7:0]
返回值：要读回的管脚状态值 0：当前管脚为低电平  1：当前管脚为搞电平
举例：GPIO_Pin_Set(0xff);   设置gpio0~gpio3输出低电平
			GPIO_Set_Input(BIT0 | BIT1 | BIT2 | BIT3 | BIT4 | BIT5 | BIT6 | BIT7);    设置gpio0~gpio7输出低电平
*/
uint8_t GPIO_Pin_Read(uint32_t io)
{
	if(GPI_CTRL->GPI & io)  return 1;
	else return 0;
}
/*
GPIO口中断使能函数
参数：uint32_t io：要使能的IO口，从0~31，但是芯片只有28个IO口，故这个变量范围：0~27
			void *  p_callback：GPIO口中断的回调函数
*/
void io_irq_enable(uint32_t io, void *  p_callback)
{
	// clear interrupt
	GPIO_IRQ_CTRL->GPIO_INT_CLR = GPIO_IRQ_CTRL->GPIO_INT;     //读取中断位，清除有中断的中断状态
	// unmask gpio interrupt
	GPIO_IRQ_CTRL->GPIO_INT_MSK &= ~io;   //该寄存器为置位代表屏蔽该引脚中断，置0代表该引脚中断可以被CPU响应
	GPIO_IRQ_CTRL->GPIO_TOP_INT_MSK=0;
	gpio_callback = ((void (*)(void))p_callback);  //注册回调函数
	// enable IRQ
	NVIC_EnableIRQ(GPIO_IRQn);
}
/*
GPIO口中断失能函数
备注：该函数失能所有的IO口
*/
void io_irq_disable(void)
{
	NVIC_DisableIRQ(GPIO_IRQn);
	GPIO_IRQ_CTRL->GPIO_TOP_INT_MSK=1;
}
/*
GPIO口中断服务函数
备注：调用回调函数
*/
void GPIO_IRQHandler(void)
{		
	// check interrupt
	if((GPIO_IRQ_CTRL->GPIO_INT & (~GPIO_IRQ_CTRL->GPIO_INT_MSK)))   //只判断非屏蔽引脚
	{
		if(gpio_callback != 0)
			(*gpio_callback)();
		// clear interrupt		
		GPIO_IRQ_CTRL->GPIO_INT_CLR= GPIO_IRQ_CTRL->GPIO_INT;
	} 
}
