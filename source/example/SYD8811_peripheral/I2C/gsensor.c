/*
da213加速度传感器的操作文件

作者：北京盛源达科技有限公司
日期：2016/7/8
*/
#include "gsensor.h"
#include "i2c.h"
#include "debug.h"
#include "delay.h"
#include "gpio.h"

/*
寄存器配置数组
第一个数数据为寄存器地址 第二个数据为寄存器数据
*/
const uint8_t kx022_init_data[] = 
{
	KX022_CNTL1_REG, 0x0A, 	//Power Mode/Bandwidth Normal   [4:3]acceleration range of x/y/z axes, 00:+/-2g, 01:+/-4g, 10:+/-8g
	KX022_CNTL3_REG, 0X02, 	//ODR                           Output data rate 25Hz
	KX022_ODCNTL_REG,0x01,  //ODR                           Output data rate 25Hz
};

/*
kx022写寄存器函数
参数： uint8_t addr  寄存器地址
			 uint8_t value 寄存器数据
注意ID地址不作为传入参数 已经在全部变量定义好了
*/
void kx022_write_reg(uint8_t addr, uint8_t value)
{	
	__align(4) uint8_t val=0;
	val=value;
	i2c_0_write(I2C_ID_KX022, 1, addr, &val, 0x01);
}
/*
kx022读寄存器函数
参数： uint8_t addr  寄存器地址
			 uint8_t value 读到的内容
注意ID地址不作为传入参数 已经在全部变量定义好了
*/
void kx022_read_reg(uint8_t addr, uint8_t *p_value)
{
	__align(4) uint8_t val=0;
	i2c_0_read(I2C_ID_KX022, 1, addr, &val, 0x01);
	*p_value=val;
}
/*
kx022写寄存器函数
参数： uint8_t addr  寄存器地址
			 uint8_t buff 寄存器数据
       uint8_t size  要写入多少个数据
注意ID地址不作为传入参数 已经在全部变量定义好了
    因为使用的是DMA来传输，所以这里必须保证传入buff为四字节对其
*/
void kx022_write_nreg(uint8_t addr, uint8_t * buff, uint8_t size)
{
	i2c_0_write(I2C_ID_KX022, 1, addr, buff, size);
}
/*
kx022读寄存器函数
参数： uint8_t addr  寄存器地址
			 uint8_t buff 读到的内容
       uint8_t size  要读取多少个数据
注意ID地址不作为传入参数 已经在全部变量定义好了
*/
void kx022_read_nreg(uint8_t addr, uint8_t *buff, uint8_t size)
{
	i2c_0_read(I2C_ID_KX022, 1, addr, buff, size);
}
/*
kx022初始化函数
这里配置了寄存器
*/
uint8_t  kx022_init(void)
{
	uint8_t i,st; 	
	kx022_write_reg(0x00, 0x24);   //复位
	for(i=0; i<(sizeof(kx022_init_data)); i+=2)
	{
		kx022_write_reg(kx022_init_data[i], kx022_init_data[i+1]);
	}
	kx022_read_reg(KX022_INT_REL, &st);
	kx022_read_reg(KX022_WHO_AM_I_REG, &st);
	
	if(st == 0x14) return 1;
	#ifdef CONFIG_UART_ENABLE
	dbg_printf("WHO I ME: %4X \r\n",st);
	#endif
	return 0;
}
/*
kx022获取加速度传感器三个轴的数据函数
传入参数：uint16_t *p_x X轴数据存储指针
					uint16_t *p_y y轴数据存储指针
					uint16_t *p_z z轴数据存储指针
*/
void gensor_read_xyz(int16_t *p_x, int16_t *p_y, int16_t *p_z)
{
		__align(4) uint8_t val[6];
	
		kx022_read_nreg(KX022_X_OUTL_REG, val,6); 
		*p_x = (val[0]) | ((int16_t)val[1] << 8);
		*p_y = (val[2]) | ((int16_t)val[3] << 8);
		*p_z = (val[4]) | ((int16_t)val[5] << 8);
}		

