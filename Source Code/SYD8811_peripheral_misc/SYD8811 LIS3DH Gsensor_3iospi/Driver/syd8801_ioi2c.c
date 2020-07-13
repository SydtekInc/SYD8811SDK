/*
ioģ��iicʱ������ļ�

���ߣ�����ʢԴ��Ƽ����޹�˾
���ڣ�2016/7/8
*/
#include "syd8801_gpio.h"
#include "syd8801_ioi2c.h"
/*
����iic�ܽź���
gpio15->SDA  gpio16->SCL 
*/
void ioi2c_ioconfig(void){
	GPIO_Set_Output(iic_SCLK | iic_SDA);
	
	GPIO_Pin_Set(iic_SCLK);   //LCD_CS
	GPIO_Pin_Set(iic_SDA);   //LCD_POWER_EN
}
/*
IIC��ʼ���� ʱ��ʼ ����ֹͣλ
*/
void start(void)
{
	GPIO_Pin_Set(iic_SDA);
	GPIO_Pin_Set(iic_SCLK);
	GPIO_Pin_Clear(iic_SDA);
	GPIO_Pin_Clear(iic_SCLK);
}
/*
IICֹͣ���� ����ֹͣλ
*/
void stop(void)
{
	GPIO_Pin_Clear(iic_SCLK);
	GPIO_Pin_Clear(iic_SDA);
	GPIO_Pin_Set(iic_SCLK);
	GPIO_Pin_Set(iic_SDA);
}
/*
IIC�����豸ID(�豸��ַ)�ֽں���
���������uint8_t id �豸�ĵ�ַ ��������λ��ַ ��������ĵ�ַ��������һλ���Ҽ�1����0x50->0xb0
					IIC_DIRECTION direction ���䷽�� �ο�IIC_DIRECTIONö�٣��ñ��������˵�һ��ֱ�ӵ����λ
*/
void iic_sendid(uint8_t id,IIC_DIRECTION direction){
	uint8_t j;
	id<<=1;
	for(j=0;j<7;j++)
	{
		GPIO_Pin_Clear(iic_SCLK);
		if((id&0x80)==0x80)
		{		
			GPIO_Pin_Set(iic_SDA);
		}
		else
		{
			GPIO_Pin_Clear(iic_SDA);
		}
		id=id<<1;
		GPIO_Pin_Set(iic_SCLK);
	}
	GPIO_Pin_Clear(iic_SCLK);
	if(direction==iic_write) GPIO_Pin_Clear(iic_SDA);
	else GPIO_Pin_Set(iic_SDA);
	GPIO_Pin_Set(iic_SCLK);
	//Ӧ��
	GPIO_Pin_Clear(iic_SCLK);   
	GPIO_Pin_Set(iic_SDA);   //���Բ鿴��û��Ӧ��
	GPIO_Pin_Set(iic_SCLK);
	GPIO_Pin_Clear(iic_SCLK); //ע���������Ҫ�ٴ������SCLK  ����Ļ��豸�ͻ���Ϊ��û�е���Ӧ��������ô������˵��ٴο�ʼʱ��һ��ʱ�Ӿͻᱻ��Ϊ��Ӧ�����ʱ��
}
/*
IIC����һ���ֽڵ����ݺ���
���������uint8_t da Ҫ���͵����ݣ�һ���ֽڣ�
*/
void iic_senddata(uint8_t da){
	uint8_t m;
	uint8_t j;
	for(j=0;j<8;j++)
	{
		m=da;
		GPIO_Pin_Clear(iic_SCLK);
		m=m&0x80;
		if(m==0x80)
		{		
			GPIO_Pin_Set(iic_SDA);
		}
		else
		{
			GPIO_Pin_Clear(iic_SDA);
		}
		da=da<<1;
		GPIO_Pin_Set(iic_SCLK);
	}
	//Ӧ��
	GPIO_Pin_Clear(iic_SCLK);  
	GPIO_Pin_Set(iic_SDA);   //���Բ鿴��û��Ӧ��
	GPIO_Pin_Set(iic_SCLK);
	GPIO_Pin_Clear(iic_SCLK);    
}
/*
IIC����һ���ֽڵ����ݺ���
����ֵ��uint8_t���յ������ݣ�һ���ֽڣ�
*/
uint8_t iic_receivedata(void){
	uint8_t j,da;
	GPIO_Set_Input(iic_SDA);  //��Ϊ����
	for(j=0;j<8;j++)
	{
		GPIO_Pin_Clear(iic_SCLK);
		GPIO_Pin_Set(iic_SCLK);
		if(GPIO_Pin_Read(iic_SDA)) da=(da<<1)+1;
		else da=da<<1;
	}
	 //Ӧ��
	GPIO_Pin_Clear(iic_SCLK);  
	GPIO_Set_Output(iic_SDA);   //�ָ����
	GPIO_Pin_Set(iic_SDA);   //���Բ鿴��û��Ӧ��
	GPIO_Pin_Set(iic_SCLK);
	GPIO_Pin_Clear(iic_SCLK); 
	return da;
}
/*
iic0��д����
���������uint8_t id �豸�ĵ�ַ ��������λ��ַ ��������ĵ�ַ��������һλ���Ҽ�1����0x50->0xb0
					uint8_t addr_len �豸�ڲ���ַ���Ĵ�����ַ���ĳ��ȣ��������I2C_2_BYTE_ADDRESS��Ϊ2���ֽڸ���ַ������Ϊ1���ֽ�
					uint8_t * buf Ҫ������������
					uint16_t sz Ҫ���͵����ݳ���
*/
uint8_t i2c_reg_write(uint8_t id, uint8_t addr_len, uint16_t addr, uint8_t * buf, uint16_t sz)
{
	uint8_t i=0;
	start();
	iic_sendid(id,iic_write);
	if(addr_len==IOI2C_2_BYTE_ADDRESS){
		iic_senddata(addr>>8);
	}
	iic_senddata(addr);
	for(i=0;i<sz;i++){
		iic_senddata(* buf);
		buf++;
	}
	stop();
	return 1;  //Ϊ�˼���Ӳ��IIC����
}
/*
iic0��д����
���������uint8_t id �豸�ĵ�ַ ��������λ��ַ ��������ĵ�ַ��������һλ����0x50->0xa0
					uint8_t addr_len �豸�ڲ���ַ���Ĵ�����ַ���ĳ��ȣ��������I2C_2_BYTE_ADDRESS��Ϊ2���ֽڸ���ַ������Ϊ1���ֽ�
					uint8_t * buf ��ȡ���ݵĴ�������
					uint16_t sz Ҫ��ȡ�����ݳ���
*/
uint8_t i2c_reg_read(uint8_t id, uint8_t addr_len, uint16_t addr, uint8_t * buf, uint16_t sz)
{
  uint8_t i=0;
	start();
	iic_sendid(id,iic_write);
	if(addr_len==IOI2C_2_BYTE_ADDRESS){
		iic_senddata(addr>>8);
	}
	iic_senddata(addr);
	start();   //��Ҫ�ٴο�ʼ ע��
	iic_sendid(id,iic_read);   //��ID
	for(i=0;i<sz;i++){
		* buf=iic_receivedata();
		buf++;
	}
	stop();
	return 1;
}
