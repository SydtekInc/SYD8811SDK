/*
gpio�����ļ�

���ߣ�����ʢԴ��Ƽ����޹�˾
���ڣ�2016/7/8
*/
#include "syd8801_gpio.h"

//�Ĵ�����ַ����
PIN_CONFIG_TYPE *	PIN_CONFIG	= ((PIN_CONFIG_TYPE *)	PIN_CONFIG_BASE);    //�ܽſ��ƼĴ���
GPO_CTRL_TYPE *	GPO_CTRL	= ((GPO_CTRL_TYPE *)		GPO_CTRL_BASE);          //GPIO�ڹܽ�������ƼĴ�������λ��ܽ�����ߵ�ƽ����֮�͵�ƽ
GPI_CTRL_TYPE *	GPI_CTRL	= ((GPI_CTRL_TYPE *)		GPI_CTRL_BASE);
GPIO_IRQ_CTRL_TYPE * GPIO_IRQ_CTRL = ((GPIO_IRQ_CTRL_TYPE *) GPIO_IRQ_CTRL_BASE);

static void (*gpio_callback)(void);

/*
���ùܽ�Ϊ�������
����: uint32_t io Ҫ���õ�gpio�ܽ����ڵ�λ������0x00����GPIO0 0X02->GPIO1 0X40->GPIO2 0XFF->GPIO[7:0]
������GPIO_Set_Output(0x0f);   ����gpio0~gpio7Ϊ���
			GPIO_Set_Output(BIT0 | BIT1 | BIT2 | BIT3);   ����gpio0~gpio3Ϊ���
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
���ùܽ�Ϊ���뺯��
����: uint32_t io Ҫ���õ�gpio�ܽ����ڵ�λ������0x00����GPIO0 0X02->GPIO1 0X40->GPIO2 0XFF->GPIO[7:0]
������GPIO_Set_Input(0x0f);   ����gpio0~gpio3Ϊ���״
			GPIO_Set_Input(BIT0 | BIT1 | BIT2 | BIT3);   ����gpio0~gpio3Ϊ���
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
	PIN_CONFIG->GPIO_PULL_UP |= io;     //����
	PIN_CONFIG->GPIO_POL  &= (~io) ;   //��ȡ��
}
/*
���ùܽ�����ߵ�ƽ����
����: uint32_t io Ҫ���õ�gpio�ܽ����ڵ�λ������0x00����GPIO0 0X02->GPIO1 0X40->GPIO2 0XFF->GPIO[7:0]
������GPIO_Pin_Set(0xff);   ����gpio0~gpio7����ߵ�ƽ
			GPIO_Set_Input(BIT0 | BIT1 | BIT2 | BIT3 | BIT4 | BIT5 | BIT6 | BIT7);    ����gpio0~gpio3����ߵ�ƽ
*/
void GPIO_Pin_Set(uint32_t io)
{
	GPO_CTRL->GPO |= io;
}
/*
���ùܽ�����͵�ƽ����
����: uint32_t io Ҫ���õ�gpio�ܽ����ڵ�λ������0x00����GPIO0 0X02->GPIO1 0X40->GPIO2 0XFF->GPIO[7:0]
������GPIO_Pin_Set(0xff);   ����gpio0~gpio3����͵�ƽ
			GPIO_Set_Input(BIT0 | BIT1 | BIT2 | BIT3 | BIT4 | BIT5 | BIT6 | BIT7);    ����gpio0~gpio7����͵�ƽ
*/
void GPIO_Pin_Clear(uint32_t io)
{
	GPO_CTRL->GPO &= ~io;
}
/*
���ùܽ������ת����
����: uint32_t io Ҫ���õ�gpio�ܽ����ڵ�λ������0x00����GPIO0 0X02->GPIO1 0X40->GPIO2 0XFF->GPIO[7:0]
������GPIO_Pin_Turn(0xff);   ����gpio0~gpio3����͵�ƽ
			GPIO_Pin_Turn(BIT0 | BIT1 | BIT2 | BIT3 | BIT4 | BIT5 | BIT6 | BIT7);    ����gpio0~gpio7����͵�ƽ
*/
void GPIO_Pin_Turn(uint32_t io)
{
	*(uint32_t *)GPO_CTRL =*(uint32_t *)GPO_CTRL ^ io;
}
/*
���عܽ�״̬����
����: uint32_t io Ҫ���õ�gpio�ܽ����ڵ�λ������0x00����GPIO0 0X02->GPIO1 0X40->GPIO2 0XFF->GPIO[7:0]
����ֵ��Ҫ���صĹܽ�״ֵ̬ 0����ǰ�ܽ�Ϊ�͵�ƽ  1����ǰ�ܽ�Ϊ���ƽ
������GPIO_Pin_Set(0xff);   ����gpio0~gpio3����͵�ƽ
			GPIO_Set_Input(BIT0 | BIT1 | BIT2 | BIT3 | BIT4 | BIT5 | BIT6 | BIT7);    ����gpio0~gpio7����͵�ƽ
*/
uint8_t GPIO_Pin_Read(uint32_t io)
{
	if(GPI_CTRL->GPI & io)  return 1;
	else return 0;
}
/*
GPIO���ж�ʹ�ܺ���
������uint32_t io��Ҫʹ�ܵ�IO�ڣ���0~31������оƬֻ��28��IO�ڣ������������Χ��0~27
			void *  p_callback��GPIO���жϵĻص�����
*/
void io_irq_enable(uint32_t io, void *  p_callback)
{
	// clear interrupt
	GPIO_IRQ_CTRL->GPIO_INT_CLR = GPIO_IRQ_CTRL->GPIO_INT;     //��ȡ�ж�λ��������жϵ��ж�״̬
	// unmask gpio interrupt
	GPIO_IRQ_CTRL->GPIO_INT_MSK &= ~io;   //�üĴ���Ϊ��λ�������θ������жϣ���0����������жϿ��Ա�CPU��Ӧ
	GPIO_IRQ_CTRL->GPIO_TOP_INT_MSK=0;
	gpio_callback = ((void (*)(void))p_callback);  //ע��ص�����
	// enable IRQ
	NVIC_EnableIRQ(GPIO_IRQn);
}
/*
GPIO���ж�ʧ�ܺ���
��ע���ú���ʧ�����е�IO��
*/
void io_irq_disable(void)
{
	NVIC_DisableIRQ(GPIO_IRQn);
	GPIO_IRQ_CTRL->GPIO_TOP_INT_MSK=1;
}
/*
GPIO���жϷ�����
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
		GPIO_IRQ_CTRL->GPIO_INT_CLR= GPIO_IRQ_CTRL->GPIO_INT;
	} 
}
