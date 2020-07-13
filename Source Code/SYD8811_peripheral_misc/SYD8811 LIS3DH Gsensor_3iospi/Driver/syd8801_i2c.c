/*
硬件iic操作文件

作者：北京盛源达科技有限公司
日期：2016/7/8
*/
#include "syd8801_i2c.h"
#include "syd8801_gpio.h"
#include <string.h>

//寄存器地址定义
I2C_CTRL_TYPE *	I2C_0_CTRL	= ((I2C_CTRL_TYPE *)	I2C_0_CTRL_BASE);
I2C_TXD_TYPE *		I2C_0_TXD	= ((I2C_TXD_TYPE *)	I2C_0_TXD_BASE);
I2C_RXD_TYPE *		I2C_0_RXD	= ((I2C_RXD_TYPE *)	I2C_0_RXD_BASE);
I2C_CTRL_TYPE *	I2C_1_CTRL	= ((I2C_CTRL_TYPE *)	I2C_1_CTRL_BASE);
I2C_TXD_TYPE *		I2C_1_TXD	= ((I2C_TXD_TYPE *)	I2C_1_TXD_BASE);
I2C_RXD_TYPE *		I2C_1_RXD	= ((I2C_RXD_TYPE *)	I2C_1_RXD_BASE);

/*
iic的IO口复用操作
iic_sclk->gpio22
iic_sda->gpio223
*/
void initI2C_gpio(void){
	// pin22~23  configured to I2C_1 mode.
	PIN_CONFIG->PIN_22_SEL = PIN_SEL_I2C_1_CLOCK;
	PIN_CONFIG->PIN_23_SEL = PIN_SEL_I2C_1_DATA;

}
/*
iic0的写函数
传入参数：uint8_t id 设备的地址 这里是七位地址 最终输出的地址将会左移一位并且加1，如0x50->0xb0
					uint8_t addr_len 设备内部地址（寄存器地址）的长度，如果传入I2C_2_BYTE_ADDRESS则为2个字节个地址，否则为1个字节
					uint8_t * buf 要发的数据内容
					uint16_t sz 要发送的数据长度
返回值：uint8_t 发送数据过程中发生了错误
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
iic0的写函数
传入参数：uint8_t id 设备的地址 这里是七位地址 最终输出的地址将会左移一位，如0x50->0xa0
					uint8_t addr_len 设备内部地址（寄存器地址）的长度，如果传入I2C_2_BYTE_ADDRESS则为2个字节个地址，否则为1个字节
					uint8_t * buf 读取数据的储存区域
					uint16_t sz 要读取的数据长度
返回值：uint8_t 接收数据过程中发生了错误
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
iic1的写函数
传入参数：uint8_t id 设备的地址 这里是七位地址 最终输出的地址将会左移一位并且加1，如0x50->0xb0
					uint8_t addr_len 设备内部地址（寄存器地址）的长度，如果传入I2C_2_BYTE_ADDRESS则为2个字节个地址，否则为1个字节
					uint8_t * buf 要发的数据内容
					uint16_t sz 要发送的数据长度
返回值：uint8_t 发送数据过程中发生了错误
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
iic1的写函数
传入参数：uint8_t id 设备的地址 这里是七位地址 最终输出的地址将会左移一位，如0x50->0xa0
					uint8_t addr_len 设备内部地址（寄存器地址）的长度，如果传入I2C_2_BYTE_ADDRESS则为2个字节个地址，否则为1个字节
					uint8_t * buf 读取数据的储存区域
					uint16_t sz 要读取的数据长度
返回值：uint8_t 接收数据过程中发生了错误
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

