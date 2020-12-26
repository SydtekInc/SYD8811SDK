#include "gpio.h"

//寄存器地址声明
PIN_CONFIG_TYPE *	PIN_CONFIG	= ((PIN_CONFIG_TYPE *)	PIN_CONFIG_BASE);    //管脚控制寄存器
GPIO_CTRL_TYPE *	GPIO_CTRL	= ((GPIO_CTRL_TYPE *)	GPIO_CTRL_BASE);  	 //GPIO控制寄存器
GPO_CTRL_TYPE *		GPO_CTRL	= ((GPO_CTRL_TYPE *)	GPO_CTRL_BASE);  	 //GPIO输出控制寄存器
GPI_CTRL_TYPE *		GPI_CTRL	= ((GPI_CTRL_TYPE *)	GPI_CTRL_BASE);		 //GPIO输入控制寄存器
GPIO_IRQ_CTRL_TYPE * 	GPIO_IRQ_CTRL = ((GPIO_IRQ_CTRL_TYPE *) GPIO_IRQ_CTRL_BASE);

static void (*gpio_callback)(void);

static uint8_t pinmuxtab48[24] = {
	0,1,2,3,4,5,6,7,8,9,10,17,18,19,20,21,22,23,24,25,26,27,30,31,
};
static uint8_t pinmuxtab32[24] = {
	0,1,2,3,4,5,6,9,10,7,8,17,21,18,22,23,24,19,25,20,26,27,30,31,
};

void gpio_init_lowpower(void)
{
	*((uint8_t *)(PWRON_BASE + 0x80)) = 0xff; //pull up 
	*((uint8_t *)(PWRON_BASE + 0x81)) = 0xff; //pull up 
	*((uint8_t *)(PWRON_BASE + 0x82)) = 0xff; //pull up
	*((uint8_t *)(PWRON_BASE + 0x83)) = 0xcf; //pull up   pin29/pin28 SWD
	*((uint8_t *)(PWRON_BASE + 0x84)) = 0xff; //pull up 
}

void PIN_Set_GPIO(uint32_t io,uint8_t fun)
{
	uint32_t i;

	for(i=0; i<32; i++)
	{
		if(io & (0x01<<i))
		{
			PIN_CONFIG->PINSEL[i] = fun;
			io &= ~(0x01<<i);
			if(io == 0)
				break;
		}
	}
}

void PIN_Pullup_Enable(enum _QFN_TYPE_ type, uint32_t io)
{
	uint32_t i;
	uint32_t *addr32 = (uint32_t *)0x50001080;
	uint8_t  *addr8  = (uint8_t *)0x50001084;
	uint8_t  *p = 0;
	
	if(type == T_QFN_48)
	{
		p = pinmuxtab48;
	}
	else if(type == T_QFN_32)
	{
		p = pinmuxtab32;
	}
	
	if(p!=0)
	{
		uint32_t tmp;
		for(i=0; i<24; i++)
		{
			tmp = 0x01<<i;
			if(io & tmp)
			{
				*addr32 |= (0x01 << p[i]);
				io &= ~tmp;
				if(io == 0)
					break;
			}
		}
		
		for(i=24; i<32; i++)
		{
			tmp = 0x01<<i;
			if(io & tmp)
			{
				*addr8 |= (0x01<<(i-24));
				io &= ~tmp;
				if(io == 0)
					break;
			}
		}
	}
}

void PIN_Pullup_Disable(enum _QFN_TYPE_ type, uint32_t io)
{
	uint32_t i;
	uint32_t *addr32 = (uint32_t *)0x50001080;
	uint8_t  *addr8  = (uint8_t *)0x50001084;
	uint8_t  *p = 0;
	
	if(type == T_QFN_48)
	{
		p = pinmuxtab48;
	}
	else if(type == T_QFN_32)
	{
		p = pinmuxtab32;
	}

	if(p!=0)
	{
		uint32_t tmp;
		for(i=0; i<24; i++)
		{
			tmp = 0x01<<i;
			if(io & tmp)
			{
				*addr32 &= ~(0x01 << p[i]);
				io &= ~tmp;
				if(io == 0)
					break;
			}
		}
		
		for(i=24; i<32; i++)
		{
			tmp = 0x01<<i;
			if(io & tmp)
			{
				*addr8 &= ~(0x01<<(i-24));
				io &= ~tmp;
				if(io == 0)
					break;
			}
		}
	}
}


/*********************************************************************************
功能: GPIO设置为输出(首先要把PIN设为GPIO)
参数: 
	  uint32_t io 要设置的gpio管脚所在的位
举例：GPIO_Set_Output(BIT0|BIT1|BIT2|BIT3);   设置gpio0~gpio3为输出
*********************************************************************************/
void GPIO_Set_Output(uint32_t io)
{
	GPIO_CTRL->GPIODIR &= ~io;
}

/***************************************************************************************
功能: GPIO设置为输入(首先要把PIN设为GPIO)
参数: 
	  uint32_t io: 		要设置的GPIO管脚所在的位
	  uint32_t  invert_bits:	该bit所对应的输入是否取反: 0-不取反,1-取反
举例：
	  GPIO_Set_Input(BIT0|BIT1|BIT2|BIT3, BIT0|BIT1);   //gpio0~3输入,gpio0和gpio1取反
***************************************************************************************/
void GPIO_Set_Input(uint32_t io, uint32_t invert_bits)
{
	GPIO_CTRL->GPIODIR |= io;
	GPI_CTRL->GPI_InE |= io;
	
	GPI_CTRL->GPI_POL  &= (~io);
	GPI_CTRL->GPI_POL  |= invert_bits;
}

void GPIO_Input_Enable(uint32_t io)
{
	GPI_CTRL->GPI_InE |= io;
}

void GPIO_Input_Disable(uint32_t io)
{
	GPI_CTRL->GPI_InE &= ~io;
}

/*********************************************************************************
功能: 管脚输出设置为高电平
参数: uint32_t io 要设置的gpio管脚所在的位
举例：
	  GPIO_Set_Input(BIT0 | BIT1 | BIT2 | BIT3);  设置gpio0~gpio4输出高电平
*********************************************************************************/
void GPIO_Pin_Set(uint32_t io)
{
	GPO_CTRL->GPO |= io;
}
/*********************************************************************************
功能: 管脚输出设置为低电平
参数: uint32_t io 要设置的gpio管脚所在的位
举例：
	  GPIO_Set_Input(BIT0 | BIT1 | BIT2 | BIT3);   设置gpio0~gpio4输出低电平
*********************************************************************************/
void GPIO_Pin_Clear(uint32_t io)
{
	GPO_CTRL->GPO &= ~io;
}

/*********************************************************************************
功能: 设置管脚输出翻转
参数: uint32_t io 要设置的gpio管脚所在的位
举例：
	  GPIO_Pin_Turn(BIT0 | BIT1 | BIT2 | BIT3);   设置gpio0~gpio4输出取反
*/
void GPIO_Pin_Turn(uint32_t io)
{
	GPO_CTRL->GPO ^= io;
}

/*********************************************************************************
功能: 返回GPIO输入寄存器值
参数: 要获取的GPIO所在位
返回值：要读回的管脚状态
*********************************************************************************/
uint32_t GPIO_Pin_Read(uint32_t io)
{
	return GPI_CTRL->GPI & io;
}

/*********************************************************************************
功能: GPIO口中断使能函数
参数：
	  uint32_t io：要使能的IO口所在的位
	  void *  p_callback：GPIO口中断的回调函数
*********************************************************************************/
void io_irq_enable(uint32_t io, void *  p_callback)
{	
	// clear interrupt
	GPIO_IRQ_CTRL->GPIO_INT_CLR = GPIO_IRQ_CTRL->GPIO_INT & io;

	// unmask gpio interrupt
	GPIO_IRQ_CTRL->GPIO_INT_MSK &= ~io;
	GPIO_IRQ_CTRL->GPIO_TOP_INT_MSK = 0;
	gpio_callback = ((void (*)(void))p_callback);

	// enable IRQ
	NVIC_EnableIRQ(GPIO_IRQn);
}

/*********************************************************************************
功能: GPIO口中断禁止函数
参数：
	  uint32_t io：要禁止中断的IO口所在的位
*********************************************************************************/
void io_irq_disable(uint32_t io)
{
	GPIO_IRQ_CTRL->GPIO_INT_MSK |= io;
}

/*********************************************************************************
功能: 禁止所有GPIO中断
*********************************************************************************/
void io_irq_disable_all(void)
{
	NVIC_DisableIRQ(GPIO_IRQn);
	GPIO_IRQ_CTRL->GPIO_INT_MSK = 0xffffffff;
	GPIO_IRQ_CTRL->GPIO_TOP_INT_MSK = 1;
}

/********************************************************************************
功能: GPIO口中断服务函数
备注：调用回调函数
*********************************************************************************/
void GPIO_IRQHandler(void)
{
	// check interrupt
	if((GPIO_IRQ_CTRL->GPIO_INT & (~GPIO_IRQ_CTRL->GPIO_INT_MSK)))
	{
		if(gpio_callback != 0)
			(*gpio_callback)();

		// clear interrupt		
		GPIO_IRQ_CTRL->GPIO_INT_CLR = GPIO_IRQ_CTRL->GPIO_INT;
	}
}

