/*
lis3dh���ٶȴ������Ĳ����ļ�

���ߣ�����ʢԴ��Ƽ����޹�˾
���ڣ�2016/7/8
*/
#include "lis3dh.h"
#include "syd8801_iospi.h"
#include "syd8801_debug.h"

/*
�Ĵ�����������
��һ��������Ϊ�Ĵ�����ַ �ڶ�������Ϊ�Ĵ�������
*/
const uint8_t lis3dh_init_data[] = 
{
	0x20, 0x4F, // CTRL_REG1  Normal / low power mode (50 Hz)  low power mode Z��X��Y axis enable
	0x21, 0x00, // CTRL_REG2  ʧ�����и�ͨ�˲�
	0x22, 0x80, // CTRL_REG3  ֻ��ʹ����CLICK interrupt on INT1
	0x23, 0x21, // CTRL_REG4  [5:4] 00: +/- 2G; 01: +/- 4G; 10: +/- 8G; 11: +/- 16G ѡ����8G   
	0x24, 0x00, // CTRL_REG5   ʧ��FIFO�ȹ���
	0x25, 0x80, // CTRL_REG6   ʹ��I2_CLICKen  
	0x38, 0x10, // CLICK_CFG, only enable single click interrupt  Z 
	0x3A, 0x1A, // CLICK_THS
	0x3B, 0x04, // TIME_LIMIT
	0x3C, 0x03, // TIME_LATENCY
	0x3D, 0x20, // TIME_WINDOW
};
/*
lis3dhд�Ĵ�������
������ uint8_t addr  �Ĵ�����ַ
			 uint8_t value �Ĵ�������
ע��ID��ַ����Ϊ������� �Ѿ���ȫ�������������
*/
void lis3dh_write_reg(uint8_t addr, uint8_t value)
{	
	//i2c_1_write(I2C_ID_LOS3DH, I2C_1_BYTE_ADDRESS, addr, &value, 0x01);
	//i2c_reg_write(I2C_ID_LOS3DH, IOI2C_1_BYTE_ADDRESS, addr, &value, 0x01);
	spi_gpio_write(addr, value);
}
/*
lis3dh���Ĵ�������
������ uint8_t addr  �Ĵ�����ַ
			 uint8_t value ����������
ע��ID��ַ����Ϊ������� �Ѿ���ȫ�������������
*/
void lis3dh_read_reg(uint8_t addr, uint8_t *p_value)
{
	//i2c_1_read(I2C_ID_LOS3DH, I2C_1_BYTE_ADDRESS, addr, p_value, 0x01);
	//i2c_reg_read(I2C_ID_LOS3DH, IOI2C_1_BYTE_ADDRESS, addr, p_value, 0x01);
	spi_gpio_read(addr, p_value);
}
/*
lis3dh��ʼ������
���������˼Ĵ���
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
lis3dh��ȡ���ٶȴ���������������ݺ���
���������uint16_t *p_x X�����ݴ洢ָ��
					uint16_t *p_y y�����ݴ洢ָ��
					uint16_t *p_z z�����ݴ洢ָ��
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
ʹ��������ʼ��������
���û�е��øú��������������صĽ��������
*/
void lis3dh_strat_accelerometer()
{
	lis3dh_write_reg(0x20, ( LIS3DH_REG0x20_VAL| 0x07 ));
}
/*
ʹ������������������
�����˸ú����󣬴��������صĽ����������
*/
void lis3dh_stop_accelerometer()
{
	lis3dh_write_reg(0x20, LIS3DH_REG0x20_VAL);
}


