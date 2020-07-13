/*
gpio�����ļ�

���ߣ�����ʢԴ��Ƽ����޹�˾
���ڣ�2018/2/3
*/
#include "gpio.h"
#include "debug.h"

//�Ĵ�����ַ����
PIN_CONFIG_TYPE *	PIN_CONFIG		= ((PIN_CONFIG_TYPE *)	PIN_CONFIG_BASE);    //�ܽſ��ƼĴ���
#if 0
static GPIO_CTRL_TYPE * GPIO_CTRL	= ((GPIO_CTRL_TYPE *)	GPIO_CTRL_BASE);  	 //GPIO���ƼĴ���
static GPO_CTRL_TYPE *	GPO_CTRL	= ((GPO_CTRL_TYPE *)	GPO_CTRL_BASE);  	 //GPIO������ƼĴ���
static GPI_CTRL_TYPE *	GPI_CTRL	= ((GPI_CTRL_TYPE *)	GPI_CTRL_BASE);		 //GPIO������ƼĴ���
static GPIO_IRQ_CTRL_TYPE * GPIO_IRQ_CTRL = ((GPIO_IRQ_CTRL_TYPE *) GPIO_IRQ_CTRL_BASE);
#else
GPIO_CTRL_TYPE * GPIO_CTRL	= ((GPIO_CTRL_TYPE *)	GPIO_CTRL_BASE);  	 //GPIO���ƼĴ���
GPO_CTRL_TYPE *	GPO_CTRL	= ((GPO_CTRL_TYPE *)	GPO_CTRL_BASE);  	 //GPIO������ƼĴ���
GPI_CTRL_TYPE *	GPI_CTRL	= ((GPI_CTRL_TYPE *)	GPI_CTRL_BASE);		 //GPIO������ƼĴ���
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
����: GPIO����Ϊ���(����Ҫ��PIN��ΪGPIO)
����: 
	  uint32_t io Ҫ���õ�gpio�ܽ����ڵ�λ
������GPIO_Set_Output(BIT0 | BIT1 | BIT2 | BIT3);   ����gpio0~gpio3Ϊ���
*/
void GPIO_Set_Output(uint32_t io)
{
	GPIO_CTRL->GPIODIR &= ~io;
}

/*
����: GPIO����Ϊ����(����Ҫ��PIN��ΪGPIO)
����: 
	  uint32_t io 		Ҫ���õ�GPIO�ܽ����ڵ�λ
	  uint8_t  invert	��GPIO����λ�����Ƿ�ȡ��: 0-��ȡ��,1-ȡ��
������
	  GPIO_Set_Output(BIT0 | BIT1 | BIT2 | BIT3);   ����gpio0~gpio3Ϊ����
*/
void GPIO_Set_Input(uint32_t io, uint32_t invert_bits)
{
	GPIO_CTRL->GPIODIR |= io;
	GPI_CTRL->GPI_POL = 0;		//ȫ������ת

#if 0
	//���������û��Ӱ�� - FPGA
	PIN_CONFIG->PAD_INPUT_PULL_UP[0] = 0xff;	  //����ʹ��
	PIN_CONFIG->PAD_INPUT_PULL_UP[1] = 0xff;	  //����ʹ��
	PIN_CONFIG->PAD_INPUT_PULL_UP[2] = 0xff;	  //����ʹ��
	PIN_CONFIG->PAD_INPUT_PULL_UP[3] = 0xff;	  //����ʹ��
	PIN_CONFIG->PAD_INPUT_PULL_UP[4] = 0xff;	  //����ʹ��
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
����: ���ùܽ�����ߵ�ƽ
����: uint32_t io Ҫ���õ�gpio�ܽ����ڵ�λ
������
	  GPIO_Set_Input(BIT0 | BIT1 | BIT2 | BIT3);  ����gpio0~gpio4����ߵ�ƽ
*/
void GPIO_Pin_Set(uint32_t io)
{
	GPO_CTRL->GPO |= io;
}
/*
����: ���ùܽ�����͵�ƽ����
����: uint32_t io Ҫ���õ�gpio�ܽ����ڵ�λ
������
	  GPIO_Set_Input(BIT0 | BIT1 | BIT2 | BIT3);   ����gpio0~gpio4����͵�ƽ
*/
void GPIO_Pin_Clear(uint32_t io)
{
	GPO_CTRL->GPO &= ~io;
}
/*
����: ���ùܽ������ת����
����: uint32_t io Ҫ���õ�gpio�ܽ����ڵ�λ
������
	  GPIO_Pin_Turn(BIT0 | BIT1 | BIT2 | BIT3);   ����gpio0~gpio4���ȡ��
*/
void GPIO_Pin_Turn(uint32_t io)
{
	GPO_CTRL->GPO ^= io;
}
/*
����: ����GPIO����Ĵ���ֵ
����: 
����ֵ��Ҫ���صĹܽ�״ֵ̬ 0����ǰ�ܽ�Ϊ�͵�ƽ  1����ǰ�ܽ�Ϊ�ߵ�ƽ
*/
uint32_t GPIO_Pin_Read(uint32_t io)
{
	return GPI_CTRL->GPI & io;
}
/*
����: GPIO���ж�ʹ�ܺ���
������
	  uint32_t io��Ҫʹ�ܵ�IO�����ڵ�λ
	  void *  p_callback��GPIO���жϵĻص�����
*/
void io_irq_enable(uint32_t io, void *  p_callback)
{
	// clear interrupt
	GPIO_IRQ_CTRL->GPIO_INT_CLR = GPIO_IRQ_CTRL->GPIO_INT & ~io;     //��ȡ�ж�λ��������жϵ��ж�״̬
	
	// unmask gpio interrupt
	GPIO_IRQ_CTRL->GPIO_INT_MSK &= ~io;
	GPIO_IRQ_CTRL->GPIO_TOP_INT_MSK = 0;
	gpio_callback = ((void (*)(void))p_callback);
	
	// enable IRQ
	NVIC_EnableIRQ(GPIO_IRQn);
}
/*
����: GPIO���жϽ�ֹ����
������
	  uint32_t io��Ҫ��ֹ�жϵ�IO�����ڵ�λ
*/
void io_irq_disable(uint32_t io)
{
	GPIO_IRQ_CTRL->GPIO_INT_MSK |= io;
}

/*
����: ��ֹ����GPIO�ж�
*/
void io_irq_disable_all(void)
{
	NVIC_DisableIRQ(GPIO_IRQn);
	GPIO_IRQ_CTRL->GPIO_INT_MSK = 0xffffffff;
	GPIO_IRQ_CTRL->GPIO_TOP_INT_MSK = 1;
}

/*
����: GPIO���жϷ�����
��ע�����ûص�����
*/
void GPIO_IRQHandler(void)
{	
	// check interrupt
	if((GPIO_IRQ_CTRL->GPIO_INT & (~GPIO_IRQ_CTRL->GPIO_INT_MSK)))   //ֻ�жϷ���������
	{
		if(gpio_callback != 0)
			(*gpio_callback)();

		// clear interrupt		
		GPIO_IRQ_CTRL->GPIO_INT_CLR = GPIO_IRQ_CTRL->GPIO_INT;
	}
}

