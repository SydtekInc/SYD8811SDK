#include "gpio.h"

//�Ĵ�����ַ����
PIN_CONFIG_TYPE *	PIN_CONFIG	= ((PIN_CONFIG_TYPE *)	PIN_CONFIG_BASE);    //�ܽſ��ƼĴ���
GPIO_CTRL_TYPE *	GPIO_CTRL	= ((GPIO_CTRL_TYPE *)	GPIO_CTRL_BASE);  	 //GPIO���ƼĴ���
GPO_CTRL_TYPE *		GPO_CTRL	= ((GPO_CTRL_TYPE *)	GPO_CTRL_BASE);  	 //GPIO������ƼĴ���
GPI_CTRL_TYPE *		GPI_CTRL	= ((GPI_CTRL_TYPE *)	GPI_CTRL_BASE);		 //GPIO������ƼĴ���
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
����: GPIO����Ϊ���(����Ҫ��PIN��ΪGPIO)
����: 
	  uint32_t io Ҫ���õ�gpio�ܽ����ڵ�λ
������GPIO_Set_Output(BIT0|BIT1|BIT2|BIT3);   ����gpio0~gpio3Ϊ���
*********************************************************************************/
void GPIO_Set_Output(uint32_t io)
{
	GPIO_CTRL->GPIODIR &= ~io;
}

/***************************************************************************************
����: GPIO����Ϊ����(����Ҫ��PIN��ΪGPIO)
����: 
	  uint32_t io: 		Ҫ���õ�GPIO�ܽ����ڵ�λ
	  uint32_t  invert_bits:	��bit����Ӧ�������Ƿ�ȡ��: 0-��ȡ��,1-ȡ��
������
	  GPIO_Set_Input(BIT0|BIT1|BIT2|BIT3, BIT0|BIT1);   //gpio0~3����,gpio0��gpio1ȡ��
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
����: �ܽ��������Ϊ�ߵ�ƽ
����: uint32_t io Ҫ���õ�gpio�ܽ����ڵ�λ
������
	  GPIO_Set_Input(BIT0 | BIT1 | BIT2 | BIT3);  ����gpio0~gpio4����ߵ�ƽ
*********************************************************************************/
void GPIO_Pin_Set(uint32_t io)
{
	GPO_CTRL->GPO |= io;
}
/*********************************************************************************
����: �ܽ��������Ϊ�͵�ƽ
����: uint32_t io Ҫ���õ�gpio�ܽ����ڵ�λ
������
	  GPIO_Set_Input(BIT0 | BIT1 | BIT2 | BIT3);   ����gpio0~gpio4����͵�ƽ
*********************************************************************************/
void GPIO_Pin_Clear(uint32_t io)
{
	GPO_CTRL->GPO &= ~io;
}

/*********************************************************************************
����: ���ùܽ������ת
����: uint32_t io Ҫ���õ�gpio�ܽ����ڵ�λ
������
	  GPIO_Pin_Turn(BIT0 | BIT1 | BIT2 | BIT3);   ����gpio0~gpio4���ȡ��
*/
void GPIO_Pin_Turn(uint32_t io)
{
	GPO_CTRL->GPO ^= io;
}

/*********************************************************************************
����: ����GPIO����Ĵ���ֵ
����: Ҫ��ȡ��GPIO����λ
����ֵ��Ҫ���صĹܽ�״̬
*********************************************************************************/
uint32_t GPIO_Pin_Read(uint32_t io)
{
	return GPI_CTRL->GPI & io;
}

/*********************************************************************************
����: GPIO���ж�ʹ�ܺ���
������
	  uint32_t io��Ҫʹ�ܵ�IO�����ڵ�λ
	  void *  p_callback��GPIO���жϵĻص�����
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
����: GPIO���жϽ�ֹ����
������
	  uint32_t io��Ҫ��ֹ�жϵ�IO�����ڵ�λ
*********************************************************************************/
void io_irq_disable(uint32_t io)
{
	GPIO_IRQ_CTRL->GPIO_INT_MSK |= io;
}

/*********************************************************************************
����: ��ֹ����GPIO�ж�
*********************************************************************************/
void io_irq_disable_all(void)
{
	NVIC_DisableIRQ(GPIO_IRQn);
	GPIO_IRQ_CTRL->GPIO_INT_MSK = 0xffffffff;
	GPIO_IRQ_CTRL->GPIO_TOP_INT_MSK = 1;
}

/********************************************************************************
����: GPIO���жϷ�����
��ע�����ûص�����
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

