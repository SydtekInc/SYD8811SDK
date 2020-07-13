/*
lis3dh加速度传感器的操作文件

作者：北京盛源达科技有限公司
日期：2016/7/8
*/
#include "lis3dh.h"
#include "syd8801_iospi.h"
#include "syd8801_debug.h"

/*
寄存器配置数组
第一个数数据为寄存器地址 第二个数据为寄存器数据
*/
const uint8_t lis3dh_init_data[] = 
{
	0x20, 0x4F, // CTRL_REG1  Normal / low power mode (50 Hz)  low power mode Z、X、Y axis enable
	0x21, 0x00, // CTRL_REG2  失能所有高通滤波
	0x22, 0x80, // CTRL_REG3  只是使能了CLICK interrupt on INT1
	0x23, 0x21, // CTRL_REG4  [5:4] 00: +/- 2G; 01: +/- 4G; 10: +/- 8G; 11: +/- 16G 选择了8G   
	0x24, 0x00, // CTRL_REG5   失能FIFO等功能
	0x25, 0x80, // CTRL_REG6   使能I2_CLICKen  
	0x38, 0x10, // CLICK_CFG, only enable single click interrupt  Z 
	0x3A, 0x1A, // CLICK_THS
	0x3B, 0x04, // TIME_LIMIT
	0x3C, 0x03, // TIME_LATENCY
	0x3D, 0x20, // TIME_WINDOW
};
/*
lis3dh写寄存器函数
参数： uint8_t addr  寄存器地址
			 uint8_t value 寄存器数据
注意ID地址不作为传入参数 已经在全部变量定义好了
*/
void lis3dh_write_reg(uint8_t addr, uint8_t value)
{	
	//i2c_1_write(I2C_ID_LOS3DH, I2C_1_BYTE_ADDRESS, addr, &value, 0x01);
	//i2c_reg_write(I2C_ID_LOS3DH, IOI2C_1_BYTE_ADDRESS, addr, &value, 0x01);
	spi_gpio_write(addr, value);
}
/*
lis3dh读寄存器函数
参数： uint8_t addr  寄存器地址
			 uint8_t value 读到的内容
注意ID地址不作为传入参数 已经在全部变量定义好了
*/
void lis3dh_read_reg(uint8_t addr, uint8_t *p_value)
{
	//i2c_1_read(I2C_ID_LOS3DH, I2C_1_BYTE_ADDRESS, addr, p_value, 0x01);
	//i2c_reg_read(I2C_ID_LOS3DH, IOI2C_1_BYTE_ADDRESS, addr, p_value, 0x01);
	spi_gpio_read(addr, p_value);
}
/*
lis3dh初始化函数
这里配置了寄存器
*/
void lis3dh_init(void)
{
	uint8_t i,st;
	//initI2C_gpio();
	//ioi2c_ioconfig();
	spi_gpio_init();
	// lis3dh register initialization
	for(i=0; i<(sizeof(lis3dh_init_data)); i+=2)
		lis3dh_write_reg(lis3dh_init_data[i], lis3dh_init_data[i+1]);
	lis3dh_read_reg(LIS3DH_WHO_AM_I_REG, &st);
	if(st == 0x33) dbg_printf("lis3dh initialize succeed\r\n");
	else dbg_printf("lis3dh initialize failed \r\n");
}
/*
lis3dh获取加速度传感器三个轴的数据函数
传入参数：uint16_t *p_x X轴数据存储指针
					uint16_t *p_y y轴数据存储指针
					uint16_t *p_z z轴数据存储指针
*/
void lis3dh_get_accelerometer_data(int16_t *p_x, int16_t *p_y, int16_t *p_z)
{
	uint8_t st;
	uint8_t val[2];
	lis3dh_read_reg(LIS3DH_STATUS_REG, &st);   //07
	if((st & 0x04) != 0x00)
	{
		lis3dh_read_reg(LIS3DH_X_DATA_REG, &val[0]);   //28
		lis3dh_read_reg(LIS3DH_X_DATA_REG+1, &val[1]);
		*p_x = val[0] | (val[1] << 8);
		lis3dh_read_reg(LIS3DH_Y_DATA_REG, &val[0]);   //2A
		lis3dh_read_reg(LIS3DH_Y_DATA_REG+1, &val[1]);
		*p_y = val[0] | (val[1] << 8);
		lis3dh_read_reg(LIS3DH_Z_DATA_REG, &val[0]);    //2c
		lis3dh_read_reg(LIS3DH_Z_DATA_REG+1, &val[1]);
		*p_z = val[0] | (val[1] << 8);
	}
}
/*
使传感器开始工作函数
如果没有调用该函数，传感器返回的结果不正常
*/
void lis3dh_strat_accelerometer()
{
	lis3dh_write_reg(0x20, ( LIS3DH_REG0x20_VAL| 0x07 ));
}
/*
使传感器结束工作函数
调用了该函数后，传感器返回的结果将不正常
*/
void lis3dh_stop_accelerometer()
{
	lis3dh_write_reg(0x20, LIS3DH_REG0x20_VAL);
}


