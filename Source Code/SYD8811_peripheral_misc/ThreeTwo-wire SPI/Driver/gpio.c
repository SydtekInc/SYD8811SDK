/*
gpio操作文件

作者：北京盛源达科技有限公司
日期：2018/2/3
*/
#include "gpio.h"
#include "debug.h"

//寄存器地址声明
PIN_CONFIG_TYPE *	PIN_CONFIG		= ((PIN_CONFIG_TYPE *)	PIN_CONFIG_BASE);    //管脚控制寄存器
#if 0
static GPIO_CTRL_TYPE * GPIO_CTRL	= ((GPIO_CTRL_TYPE *)	GPIO_CTRL_BASE);  	 //GPIO控制寄存器
static GPO_CTRL_TYPE *	GPO_CTRL	= ((GPO_CTRL_TYPE *)	GPO_CTRL_BASE);  	 //GPIO输出控制寄存器
static GPI_CTRL_TYPE *	GPI_CTRL	= ((GPI_CTRL_TYPE *)	GPI_CTRL_BASE);		 //GPIO输入控制寄存器
static GPIO_IRQ_CTRL_TYPE * GPIO_IRQ_CTRL = ((GPIO_IRQ_CTRL_TYPE *) GPIO_IRQ_CTRL_BASE);
#else
GPIO_CTRL_TYPE * GPIO_CTRL	= ((GPIO_CTRL_TYPE *)	GPIO_CTRL_BASE);  	 //GPIO控制寄存器
GPO_CTRL_TYPE *	GPO_CTRL	= ((GPO_CTRL_TYPE *)	GPO_CTRL_BASE);  	 //GPIO输出控制寄存器
GPI_CTRL_TYPE *	GPI_CTRL	= ((GPI_CTRL_TYPE *)	GPI_CTRL_BASE);		 //GPIO输入控制寄存器
GPIO_IRQ_CTRL_TYPE * GPIO_IRQ_CTRL = ((GPIO_IRQ_CTRL_TYPE *) GPIO_IRQ_CTRL_BASE);
#endif

static void (*gpio_callback)(void);

void PIN_Set_GPIO(uint32_t io)
{
	uint32_t i=0;

	for(i=0; i<32; i++)
	{
		if(io & (0x01<<i))
		{
			PIN_CONFIG->PINSEL[i] = PIN_SEL_GPIO;
			io &= ~(0x01<<i);
			if(io == 0)
				break;
		}
	}
}

/*
功能: GPIO设置为输出(首先要把PIN设为GPIO)
参数: 
	  uint32_t io 要设置的gpio管脚所在的位
举例：GPIO_Set_Output(BIT0 | BIT1 | BIT2 | BIT3);   设置gpio0~gpio3为输出
*/
void GPIO_Set_Output(uint32_t io)
{
	GPIO_CTRL->GPIODIR &= ~io;
}

/*
功能: GPIO设置为输入(首先要把PIN设为GPIO)
参数: 
	  uint32_t io 		要设置的GPIO管脚所在的位
	  uint8_t  invert	该GPIO所在位输入是否取反: 0-不取反,1-取反
举例：
	  GPIO_Set_Output(BIT0 | BIT1 | BIT2 | BIT3);   设置gpio0~gpio3为输入
*/
void GPIO_Set_Input(uint32_t io, uint32_t invert_bits)
{
	GPIO_CTRL->GPIODIR |= io;
	GPI_CTRL->GPI_POL = 0;		//全部不翻转

#if 0
	//对输入好像没有影响 - FPGA
	PIN_CONFIG->PAD_INPUT_PULL_UP[0] = 0xff;	  //上拉使能
	PIN_CONFIG->PAD_INPUT_PULL_UP[1] = 0xff;	  //上拉使能
	PIN_CONFIG->PAD_INPUT_PULL_UP[2] = 0xff;	  //上拉使能
	PIN_CONFIG->PAD_INPUT_PULL_UP[3] = 0xff;	  //上拉使能
	PIN_CONFIG->PAD_INPUT_PULL_UP[4] = 0xff;	  //上拉使能
#endif	
}

void GPIO_Input_Enable(uint32_t io)
{
	dbg_printf("0:GPI_CTRL->GPI_InE = 0x%08x\r\n", GPI_CTRL->GPI_InE);
	GPI_CTRL->GPI_InE |= io;
	dbg_printf("1:GPI_CTRL->GPI_InE = 0x%08x\r\n", GPI_CTRL->GPI_InE);
}

void GPIO_Input_Disable(uint32_t io)
{
	GPI_CTRL->GPI_InE &= ~io;
}

/*
功能: 设置管脚输出高电平
参数: uint32_t io 要设置的gpio管脚所在的位
举例：
	  GPIO_Set_Input(BIT0 | BIT1 | BIT2 | BIT3);  设置gpio0~gpio4输出高电平
*/
void GPIO_Pin_Set(uint32_t io)
{
	GPO_CTRL->GPO |= io;
}
/*
功能: 设置管脚输出低电平函数
参数: uint32_t io 要设置的gpio管脚所在的位
举例：
	  GPIO_Set_Input(BIT0 | BIT1 | BIT2 | BIT3);   设置gpio0~gpio4输出低电平
*/
void GPIO_Pin_Clear(uint32_t io)
{
	GPO_CTRL->GPO &= ~io;
}
/*
功能: 设置管脚输出翻转函数
参数: uint32_t io 要设置的gpio管脚所在的位
举例：
	  GPIO_Pin_Turn(BIT0 | BIT1 | BIT2 | BIT3);   设置gpio0~gpio4输出取反
*/
void GPIO_Pin_Turn(uint32_t io)
{
	GPO_CTRL->GPO ^= io;
}
/*
功能: 返回GPIO输入寄存器值
参数: 
返回值：要读回的管脚状态值 0：当前管脚为低电平  1：当前管脚为高电平
*/
uint32_t GPIO_Pin_Read(uint32_t io)
{
	return GPI_CTRL->GPI & io;
}
/*
功能: GPIO口中断使能函数
参数：
	  uint32_t io：要使能的IO口所在的位
	  void *  p_callback：GPIO口中断的回调函数
*/
void io_irq_enable(uint32_t io, void *  p_callback)
{
	// clear interrupt
	GPIO_IRQ_CTRL->GPIO_INT_CLR = GPIO_IRQ_CTRL->GPIO_INT & ~io;     //读取中断位，清除有中断的中断状态
	
	// unmask gpio interrupt
	GPIO_IRQ_CTRL->GPIO_INT_MSK &= ~io;
	GPIO_IRQ_CTRL->GPIO_TOP_INT_MSK = 0;
	gpio_callback = ((void (*)(void))p_callback);
	
	// enable IRQ
	NVIC_EnableIRQ(GPIO_IRQn);
}
/*
功能: GPIO口中断禁止函数
参数：
	  uint32_t io：要禁止中断的IO口所在的位
*/
void io_irq_disable(uint32_t io)
{
	GPIO_IRQ_CTRL->GPIO_INT_MSK |= io;
}

/*
功能: 禁止所有GPIO中断
*/
void io_irq_disable_all(void)
{
	NVIC_DisableIRQ(GPIO_IRQn);
	GPIO_IRQ_CTRL->GPIO_INT_MSK = 0xffffffff;
	GPIO_IRQ_CTRL->GPIO_TOP_INT_MSK = 1;
}

/*
功能: GPIO口中断服务函数
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
		GPIO_IRQ_CTRL->GPIO_INT_CLR = GPIO_IRQ_CTRL->GPIO_INT;
	}
}

