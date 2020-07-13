/*
Ӳ��iic�����ļ�

���ߣ�����ʢԴ��Ƽ����޹�˾
���ڣ�2016/7/8
*/
#include "syd8801_i2c.h"
#include "syd8801_gpio.h"
#include <string.h>

//�Ĵ�����ַ����
I2C_CTRL_TYPE *	I2C_0_CTRL	= ((I2C_CTRL_TYPE *)	I2C_0_CTRL_BASE);
I2C_TXD_TYPE *		I2C_0_TXD	= ((I2C_TXD_TYPE *)	I2C_0_TXD_BASE);
I2C_RXD_TYPE *		I2C_0_RXD	= ((I2C_RXD_TYPE *)	I2C_0_RXD_BASE);
I2C_CTRL_TYPE *	I2C_1_CTRL	= ((I2C_CTRL_TYPE *)	I2C_1_CTRL_BASE);
I2C_TXD_TYPE *		I2C_1_TXD	= ((I2C_TXD_TYPE *)	I2C_1_TXD_BASE);
I2C_RXD_TYPE *		I2C_1_RXD	= ((I2C_RXD_TYPE *)	I2C_1_RXD_BASE);

/*
iic��IO�ڸ��ò���
iic_sclk->gpio22
iic_sda->gpio223
*/
void initI2C_gpio(void){
	// pin22~23  configured to I2C_1 mode.
	PIN_CONFIG->PIN_22_SEL = PIN_SEL_I2C_1_CLOCK;
	PIN_CONFIG->PIN_23_SEL = PIN_SEL_I2C_1_DATA;

}
/*
iic0��д����
���������uint8_t id �豸�ĵ�ַ ��������λ��ַ ��������ĵ�ַ��������һλ���Ҽ�1����0x50->0xb0
					uint8_t addr_len �豸�ڲ���ַ���Ĵ�����ַ���ĳ��ȣ��������I2C_2_BYTE_ADDRESS��Ϊ2���ֽڸ���ַ������Ϊ1���ֽ�
					uint8_t * buf Ҫ������������
					uint16_t sz Ҫ���͵����ݳ���
����ֵ��uint8_t �������ݹ����з����˴���
*/
uint8_t i2c_0_write(uint8_t id, uint8_t addr_len, uint16_t addr, uint8_t * buf, uint16_t sz)
{
	uint8_t bret=0;
	I2C_0_CTRL->ID = id;
	I2C_0_CTRL->ADDR_1 = addr_len;	
	I2C_0_CTRL->ADDRESS = addr;
	I2C_0_CTRL->DATA_CNT = (sz - 1);
	I2C_0_CTRL->RSTB=1;
	memcpy((uint8_t *)I2C_0_TXD->TX, buf ,sz);
	I2C_0_CTRL->WRITE=1;
	while(1)
	{
		if(I2C_0_CTRL->DONE_FLG == 1)
			break;
	}
	if(I2C_0_CTRL->ERR_FLG==1)
		bret = 0;
	else
		bret =  1;
	I2C_0_CTRL->DONE_FLG = 0;
	I2C_0_CTRL->ERR_FLG = 0;
	I2C_0_CTRL->WRITE=0;
	I2C_0_CTRL->RSTB=0;	
	return bret;
}
/*
iic0��д����
���������uint8_t id �豸�ĵ�ַ ��������λ��ַ ��������ĵ�ַ��������һλ����0x50->0xa0
					uint8_t addr_len �豸�ڲ���ַ���Ĵ�����ַ���ĳ��ȣ��������I2C_2_BYTE_ADDRESS��Ϊ2���ֽڸ���ַ������Ϊ1���ֽ�
					uint8_t * buf ��ȡ���ݵĴ�������
					uint16_t sz Ҫ��ȡ�����ݳ���
����ֵ��uint8_t �������ݹ����з����˴���
*/
uint8_t i2c_0_read(uint8_t id, uint8_t addr_len, uint16_t addr, uint8_t * buf, uint16_t sz)
{
	uint8_t bret=0;
	I2C_0_CTRL->ID = id;
	I2C_0_CTRL->ADDR_1 = addr_len;	
	I2C_0_CTRL->ADDRESS = addr;
	I2C_0_CTRL->DATA_CNT = (sz - 1);
	I2C_0_CTRL->RSTB=1;
	I2C_0_CTRL->READ=1;
	while(1)
	{
		if(I2C_0_CTRL->DONE_FLG == 1)
			break;
	}
	if(I2C_0_CTRL->ERR_FLG==1)
	{		
		bret =  0;
	}
	else
	{
		memcpy(buf, (uint8_t *)I2C_0_RXD->RX, sz);
		bret = 1;
	}		
	I2C_0_CTRL->DONE_FLG = 0;
 	I2C_0_CTRL->ERR_FLG = 0;
	I2C_0_CTRL->READ=0;
	I2C_0_CTRL->RSTB=0;
	return bret;
}
/*
iic1��д����
���������uint8_t id �豸�ĵ�ַ ��������λ��ַ ��������ĵ�ַ��������һλ���Ҽ�1����0x50->0xb0
					uint8_t addr_len �豸�ڲ���ַ���Ĵ�����ַ���ĳ��ȣ��������I2C_2_BYTE_ADDRESS��Ϊ2���ֽڸ���ַ������Ϊ1���ֽ�
					uint8_t * buf Ҫ������������
					uint16_t sz Ҫ���͵����ݳ���
����ֵ��uint8_t �������ݹ����з����˴���
*/
uint8_t i2c_1_write(uint8_t id, uint8_t addr_len, uint16_t addr, uint8_t * buf, uint16_t sz)
{
	uint8_t bret=0;
	I2C_1_CTRL->ID = id;
	I2C_1_CTRL->ADDR_1 = addr_len;	
	I2C_1_CTRL->ADDRESS = addr;
	I2C_1_CTRL->DATA_CNT = (sz - 1);
	I2C_1_CTRL->RSTB=1;
	memcpy((uint8_t *)I2C_1_TXD->TX, buf ,sz);
	I2C_1_CTRL->WRITE=1;
	while(1)
	{
		if(I2C_1_CTRL->DONE_FLG == 1)
			break;
	}
	if(I2C_1_CTRL->ERR_FLG==1)
		bret = 0;
	else
		bret =  1;
	I2C_1_CTRL->DONE_FLG = 0;
	I2C_1_CTRL->ERR_FLG = 0;
	I2C_1_CTRL->WRITE=0;
	I2C_1_CTRL->RSTB=0;	
	return bret;
}
/*
iic1��д����
���������uint8_t id �豸�ĵ�ַ ��������λ��ַ ��������ĵ�ַ��������һλ����0x50->0xa0
					uint8_t addr_len �豸�ڲ���ַ���Ĵ�����ַ���ĳ��ȣ��������I2C_2_BYTE_ADDRESS��Ϊ2���ֽڸ���ַ������Ϊ1���ֽ�
					uint8_t * buf ��ȡ���ݵĴ�������
					uint16_t sz Ҫ��ȡ�����ݳ���
����ֵ��uint8_t �������ݹ����з����˴���
*/
uint8_t i2c_1_read(uint8_t id, uint8_t addr_len, uint16_t addr, uint8_t * buf, uint16_t sz)
{
	uint8_t bret=0;
	I2C_1_CTRL->ID = id;
	I2C_1_CTRL->ADDR_1 = addr_len;	
	I2C_1_CTRL->ADDRESS = addr;
	I2C_1_CTRL->DATA_CNT = (sz - 1);
	I2C_1_CTRL->RSTB=1;
	I2C_1_CTRL->READ=1;
	while(1)
	{
		if(I2C_1_CTRL->DONE_FLG == 1)
			break;
	}
	if(I2C_1_CTRL->ERR_FLG==1)
	{		
		bret =  0;
	}
	else
	{
		memcpy(buf, (uint8_t *)I2C_1_RXD->RX, sz);

		bret = 1;
	}		
	I2C_1_CTRL->DONE_FLG = 0;
 	I2C_1_CTRL->ERR_FLG = 0;
	I2C_1_CTRL->READ=0;
	I2C_1_CTRL->RSTB=0;
	return bret;
}

