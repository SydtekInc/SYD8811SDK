/*
io模拟iic时序操作文件

作者：北京盛源达科技有限公司
日期：2016/7/8
*/
#include "syd8801_gpio.h"
#include "syd8801_ioi2c.h"
/*
设置iic管脚函数
gpio15->SDA  gpio16->SCL 
*/
void ioi2c_ioconfig(void){
	GPIO_Set_Output(iic_SCLK | iic_SDA);
	
	GPIO_Pin_Set(iic_SCLK);   //LCD_CS
	GPIO_Pin_Set(iic_SDA);   //LCD_POWER_EN
}
/*
IIC开始函数 时序开始 产生停止位
*/
void start(void)
{
	GPIO_Pin_Set(iic_SDA);
	GPIO_Pin_Set(iic_SCLK);
	GPIO_Pin_Clear(iic_SDA);
	GPIO_Pin_Clear(iic_SCLK);
}
/*
IIC停止函数 产生停止位
*/
void stop(void)
{
	GPIO_Pin_Clear(iic_SCLK);
	GPIO_Pin_Clear(iic_SDA);
	GPIO_Pin_Set(iic_SCLK);
	GPIO_Pin_Set(iic_SDA);
}
/*
IIC发送设备ID(设备地址)字节函数
输入参数：uint8_t id 设备的地址 这里是七位地址 最终输出的地址将会左移一位并且加1，如0x50->0xb0
					IIC_DIRECTION direction 传输方向 参考IIC_DIRECTION枚举，该变量决定了第一个直接的最低位
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
	//应答
	GPIO_Pin_Clear(iic_SCLK);   
	GPIO_Pin_Set(iic_SDA);   //可以查看有没有应答
	GPIO_Pin_Set(iic_SCLK);
	GPIO_Pin_Clear(iic_SCLK); //注意这里必须要再次清除掉SCLK  否则的话设备就会认为还没有到响应结束，那么就造成了当再次开始时第一个时钟就会被认为是应答结束时钟
}
/*
IIC发送一个字节的数据函数
输入参数：uint8_t da 要发送的数据（一个字节）
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
	//应答
	GPIO_Pin_Clear(iic_SCLK);  
	GPIO_Pin_Set(iic_SDA);   //可以查看有没有应答
	GPIO_Pin_Set(iic_SCLK);
	GPIO_Pin_Clear(iic_SCLK);    
}
/*
IIC接收一个字节的数据函数
返回值：uint8_t接收到的数据（一个字节）
*/
uint8_t iic_receivedata(void){
	uint8_t j,da;
	GPIO_Set_Input(iic_SDA);  //设为输入
	for(j=0;j<8;j++)
	{
		GPIO_Pin_Clear(iic_SCLK);
		GPIO_Pin_Set(iic_SCLK);
		if(GPIO_Pin_Read(iic_SDA)) da=(da<<1)+1;
		else da=da<<1;
	}
	 //应答
	GPIO_Pin_Clear(iic_SCLK);  
	GPIO_Set_Output(iic_SDA);   //恢复输出
	GPIO_Pin_Set(iic_SDA);   //可以查看有没有应答
	GPIO_Pin_Set(iic_SCLK);
	GPIO_Pin_Clear(iic_SCLK); 
	return da;
}
/*
iic0的写函数
传入参数：uint8_t id 设备的地址 这里是七位地址 最终输出的地址将会左移一位并且加1，如0x50->0xb0
					uint8_t addr_len 设备内部地址（寄存器地址）的长度，如果传入I2C_2_BYTE_ADDRESS则为2个字节个地址，否则为1个字节
					uint8_t * buf 要发的数据内容
					uint16_t sz 要发送的数据长度
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
	return 1;  //为了兼容硬件IIC函数
}
/*
iic0的写函数
传入参数：uint8_t id 设备的地址 这里是七位地址 最终输出的地址将会左移一位，如0x50->0xa0
					uint8_t addr_len 设备内部地址（寄存器地址）的长度，如果传入I2C_2_BYTE_ADDRESS则为2个字节个地址，否则为1个字节
					uint8_t * buf 读取数据的储存区域
					uint16_t sz 要读取的数据长度
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
	start();   //需要再次开始 注意
	iic_sendid(id,iic_read);   //读ID
	for(i=0;i<sz;i++){
		* buf=iic_receivedata();
		buf++;
	}
	stop();
	return 1;
}
