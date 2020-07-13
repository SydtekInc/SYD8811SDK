/*
�������ļ�
���Բ��裺
1.ȷ���Ѿ������Ͽ����岢��װ��PL2303���������򣬲������豸�������¿��Կ������ں�
2.�򿪹���Ŀ¼��Tool�ļ�����ġ�SYD BLE Utility.exe������
3.��UART����Կ������ںţ�ѡ����ȷ�Ĵ���
4.�����open����ť����ʱ��"SYD8801 Evaluation board"����ʾ:"Wait..."
5.��ʱ���¿������ϵĸ�λ������ʾ�ͻ��ɡ�Ready��
6.�ڡ�Firmware����"FW(Upgrade)"�е����Open FW File����ťѡ�񱾹����ڡ�Objects���ļ��еġ�Module_samples.hex���ļ�
7.�ڡ�Firmware����"FW(Upgrade)"�е����Write to Flah����ť,���ɿ������ؽ��ȣ��ȴ��������
8.������ɺ��¸�λ�����ɿ�����ʵ������
9.�ٴ����أ����"SYD8801 Evaluation board"��Detect��ť��Ȼ��ӵ�5���ٴβ�������
��ע�������Ѿ������˴��ڳ���İ��ӣ���ʱ��һ�����open����ť�ͽ�����readey״̬����ʱ��һ�����²�������ģ���ʱ�����һֱ���Ÿ�λ��Ȼ������open����ť��������waite״̬ʱ��ſ���λ���������Ϳ������س�����

���ߣ�����ʢԴ��Ƽ����޹�˾
���ڣ�2016/7/8
*/
#include "ARMCM0.h"
#include "uart.h"
#include "delay.h"
#include "debug.h"
#include "wdt.h"
#include "gpio.h"
#include "spi.h"
static POWER_CTRL_TYPE * PW_CTRL = ((POWER_CTRL_TYPE *) PWRON_BASE);
static MISC_CTRL_TYPE * MISC_CTRL = ((MISC_CTRL_TYPE *) MISC_BASE);
void BBRFRead(uint8_t addr, uint8_t* data)
{
	MISC_CTRL->RF_RDY=1;
	
	MISC_CTRL->RF_ADDR = addr;

	*data = MISC_CTRL->RF_RDATA;

	while(MISC_CTRL->RF_RDY==0);

	*data = MISC_CTRL->RF_RDATA;
}

void BBRFWrite(uint8_t addr, uint8_t data)
{
	MISC_CTRL->RF_RDY=1;
	
	MISC_CTRL->RF_ADDR = addr;

	MISC_CTRL->RF_WDATA = data;

	while(MISC_CTRL->RF_RDY==0);
}
void PCUartCtrl(bool en)
{
	if(en == true)
	{
		*((uint8_t *)(PWRON_BASE + 0x74)) = 0x03;	//pin 20 config uart0 rx
		*((uint8_t *)(PWRON_BASE + 0x75)) = 0x04;	//pin 21 config uart0 tx
		//*((uint8_t *)(PWRON_BASE + 0x62)) = 0x03;	//pin 2 config uart0 rx
		//*((uint8_t *)(PWRON_BASE + 0x63)) = 0x04;	//pin 3 config uart0 tx	
		
		*((uint8_t *)(PWRON_BASE + 0x60)) = 0x05;	//pin 0 config uart1 rx
		*((uint8_t *)(PWRON_BASE + 0x61)) = 0x06;	//pin 1 config uart1 tx
		
	}
	else
	{
		*((uint8_t *)(PWRON_BASE + 0x74)) = 0x00;	
		*((uint8_t *)(PWRON_BASE + 0x75)) = 0x00;	
		//*((uint8_t *)(PWRON_BASE + 0x62)) = 0x00;	
		//*((uint8_t *)(PWRON_BASE + 0x63)) = 0x00;	
		
		*((uint8_t *)(PWRON_BASE + 0x60)) = 0x00;	
		*((uint8_t *)(PWRON_BASE + 0x61)) = 0x00;	
	}
}
void PCUartEn(bool en)
{
	if(en)
	{
		uint8_t temp;
		
		BBRFWrite(0x7f, 0x01);
		BBRFRead(0x28, &temp);
		temp |= 0x1f;
		BBRFWrite(0x28, temp);

		BBRFWrite(0x7f, 0x00);
		BBRFWrite(0x35, 0x3f);
		BBRFWrite(0x3a, 0xb0);
	}
	
	if(en)
		PW_CTRL->UART_EN = 1;
	else
		PW_CTRL->UART_EN = 0;
}
int main(void)
{
	uint8_t i=0,val=0;
	
	PCUartCtrl(true);		
	dbg_init();
	//PCUartEn(1);
	
	PIN_Set_GPIO(BIT7);
	GPIO_Set_Output(BIT7 );
	for(i=0;i<10;i++) GPIO_Pin_Turn(BIT7);
	
	PIN_CONFIG->PIN_24_SEL = HID_SEN;
	PIN_CONFIG->PIN_25_SEL = HID_SEN;
	PIN_CONFIG->PIN_26_SEL = HID_SEN;
	
	DBGPRINTF(("flash cache dsleep test123\r\n"));
	delay_ms(1);
	SPISingleWrite(0x20,0x4f);
	SPISingleWrite(0x21,0x00);
	SPISingleWrite(0x22,0x80);
	delay_ms(1);
	SPISingleWrite(0x23,0x21);
	delay_ms(1);
	SPISingleWrite(0x24,0x00);
	SPISingleWrite(0x25,0x80);
	SPISingleWrite(0x38,0x10);
	SPISingleWrite(0x3a,0x1a);
	SPISingleWrite(0x3b,0x0c);
	SPISingleWrite(0x3c,0x03);
	SPISingleWrite(0x3d,0x20);
	while(1)
	{
		GPIO_Pin_Turn(BIT7);
		
		SPISingleRead(0x0f,&val);
		DBGPRINTF(("rval:%x %x\r\n",0x0f,val));
		SPISingleRead(0x23,&val);
		DBGPRINTF(("rval:%x %x\r\n",0x23,val));
		delay_ms(1000);
	}
}


