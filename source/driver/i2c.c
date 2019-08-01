#include "i2c.h"
#include "gpio.h"
#include <string.h>

//寄存器地址定义
static I2C_CTRL_TYPE *		I2C_0_CTRL	= ((I2C_CTRL_TYPE *)	I2C_0_CTRL_BASE);
static I2C_TXD_TYPE *		I2C_0_TXD	= ((I2C_TXD_TYPE *)	I2C_0_TXD_BASE);
static I2C_RXD_TYPE *		I2C_0_RXD	= ((I2C_RXD_TYPE *)	I2C_0_RXD_BASE);
static I2C_CTRL_TYPE *		I2C_1_CTRL	= ((I2C_CTRL_TYPE *)	I2C_1_CTRL_BASE);
static I2C_TXD_TYPE *		I2C_1_TXD	= ((I2C_TXD_TYPE *)	I2C_1_TXD_BASE);
static I2C_RXD_TYPE *		I2C_1_RXD	= ((I2C_RXD_TYPE *)	I2C_1_RXD_BASE);

/*****************************************************************************
para: 
	i2c   : I2C0 or I2C1
return : void
*****************************************************************************/
void i2c_Init(uint8_t i2c,uint32_t clk_io,uint32_t sda_io)
{
	if(i2c == I2C0)
	{
		PIN_Set_GPIO(sda_io,PIN_SEL_GPIO);
		
		PIN_Pullup_Enable(T_QFN_48, sda_io);
		
		PIN_Set_GPIO(clk_io,PIN_SEL_I2C_SCL0);
		PIN_Set_GPIO(sda_io,PIN_SEL_I2C_SDA0);
		
		I2C_0_CTRL->SLAVE_NACK = 0; 	// 1:NACK,  0:ACK
		I2C_0_CTRL->SPEED = 79;			  //IIC clk = MCU CLK/(2*(speed+1))   SPEED默认值是64
	}
	else if(i2c == I2C1)
	{
		PIN_Set_GPIO(clk_io,PIN_SEL_I2C_SCL1);
		PIN_Set_GPIO(sda_io,PIN_SEL_I2C_SDA1);
		I2C_1_CTRL->SLAVE_NACK = 0; 	// 1:NACK,  0:ACK
		I2C_1_CTRL->SPEED = 79;			  //IIC clk = MCU CLK/(2*(speed+1)) SPEED默认值是64
	}
}

/***************************************************************************************************
para:
	uint8_t id:			7位设备地址
	uint8_t addr_len:   设备内部存储地址的长度，I2C_2_BYTE_ADDRESS(2字节)，I2C_1_BYTE_ADDRESS(1字节)
	uint8_t * buf:		要发的数据内容
	uint16_t sz:		要发送的数据长度

return : SUCCESS or ERROR
***************************************************************************************************/
ErrorStatus i2c_0_write(uint8_t id, uint8_t addr_len, uint16_t addr, uint8_t * buf, uint16_t sz)
{
	ErrorStatus bret = SUCCESS;

	I2C_0_CTRL->RSTB = 1;
	I2C_0_CTRL->ID = id;
	I2C_0_CTRL->ADDR_1 = addr_len;	
	I2C_0_CTRL->ADDRESS = addr;
	I2C_0_CTRL->DATA_CNT = (sz - 1);

	memcpy((uint8_t *)I2C_0_TXD->TX, buf ,sz);

	I2C_0_CTRL->WRITE = 1;
	
	while(I2C_0_CTRL->DONE_FLG == 0);
	I2C_0_CTRL->DONE_FLG = 0;

	if(I2C_0_CTRL->ERR_FLG==1)
	{
		I2C_0_CTRL->ERR_FLG = 0;
		bret = ERROR;
	}

	I2C_0_CTRL->RSTB = 0;			//reset
	
	return bret;
}

/***************************************************************************************************
para:
	uint8_t id:			7位设备地址
	uint8_t addr_len:   设备内部存储地址的长度，I2C_2_BYTE_ADDRESS(2字节)，I2C_1_BYTE_ADDRESS(1字节)
	uint8_t * buf:		读取数据的储存区域
	uint16_t sz:		要读取的数据长度

return : SUCCESS or ERROR
***************************************************************************************************/
ErrorStatus i2c_0_read(uint8_t id, uint8_t addr_len, uint16_t addr, uint8_t * buf, uint16_t sz)
{
	ErrorStatus bret = SUCCESS;

	I2C_0_CTRL->RSTB=1;
	I2C_0_CTRL->ID = id;
	I2C_0_CTRL->ADDR_1 = addr_len;	
	I2C_0_CTRL->ADDRESS = addr;
	I2C_0_CTRL->DATA_CNT = (sz - 1);
	
	I2C_0_CTRL->READ=1;

	while(I2C_0_CTRL->DONE_FLG == 0);
	I2C_0_CTRL->DONE_FLG = 0;

	if(I2C_0_CTRL->ERR_FLG == 1)
	{
		I2C_0_CTRL->ERR_FLG = 0;
		bret =  ERROR;
	}
	else
	{
		memcpy(buf, (uint8_t *)I2C_0_RXD->RX, sz);
	}

	I2C_0_CTRL->RSTB = 0;		//reset
	
	return bret;
}

/***************************************************************************************************
para:
	uint8_t id:			7位设备地址
	uint8_t addr_len:   设备内部存储地址的长度，I2C_2_BYTE_ADDRESS(2字节)，I2C_1_BYTE_ADDRESS(1字节)
	uint8_t * buf:		要发的数据内容
	uint16_t sz:		要发送的数据长度

return : SUCCESS or ERROR
***************************************************************************************************/
ErrorStatus i2c_1_write(uint8_t id, uint8_t addr_len, uint16_t addr, uint8_t * buf, uint16_t sz)
{
	ErrorStatus bret = SUCCESS;

	I2C_1_CTRL->RSTB = 1;
	I2C_1_CTRL->ID = id;
	I2C_1_CTRL->ADDR_1 = addr_len;	
	I2C_1_CTRL->ADDRESS = addr;
	I2C_1_CTRL->DATA_CNT = (sz - 1);
	
	memcpy((uint8_t *)I2C_1_TXD->TX, buf ,sz);
	
	I2C_1_CTRL->WRITE=1;
	
	while(I2C_1_CTRL->DONE_FLG == 0);
	I2C_1_CTRL->DONE_FLG = 0;

	if(I2C_1_CTRL->ERR_FLG==1)
	{
		I2C_1_CTRL->ERR_FLG = 0;
		bret = ERROR;
	}
	
	I2C_1_CTRL->RSTB=0;				//reset
	
	return bret;
}

/***************************************************************************************************
para:
	uint8_t id:			7位设备地址
	uint8_t addr_len:   设备内部存储地址的长度，I2C_2_BYTE_ADDRESS(2字节)，I2C_1_BYTE_ADDRESS(1字节)
	uint8_t * buf:		读取数据的储存区域
	uint16_t sz:		要读取的数据长度

return : SUCCESS or ERROR
***************************************************************************************************/
ErrorStatus i2c_1_read(uint8_t id, uint8_t addr_len, uint16_t addr, uint8_t * buf, uint16_t sz)
{
	ErrorStatus bret = SUCCESS;

	I2C_1_CTRL->RSTB=1;
	I2C_1_CTRL->ID = id;
	I2C_1_CTRL->ADDR_1 = addr_len;	
	I2C_1_CTRL->ADDRESS = addr;
	I2C_1_CTRL->DATA_CNT = (sz - 1);
	
	I2C_1_CTRL->READ=1;
	
	while(I2C_1_CTRL->DONE_FLG == 0);
	I2C_1_CTRL->DONE_FLG = 0;

	if(I2C_1_CTRL->ERR_FLG == 1)
	{		
		I2C_1_CTRL->ERR_FLG = 0;
		bret =  ERROR;
	}
	else
	{
		memcpy(buf, (uint8_t *)I2C_1_RXD->RX, sz);
	}

	I2C_1_CTRL->RSTB = 0;		//reset
	
	return bret;
}

