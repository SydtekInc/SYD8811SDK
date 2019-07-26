/*
da213���ٶȴ������Ĳ����ļ�

���ߣ�����ʢԴ��Ƽ����޹�˾
���ڣ�2016/7/8
*/
#include "gsensor.h"
#include "i2c.h"
#include "debug.h"
#include "delay.h"
#include "gpio.h"

/*
�Ĵ�����������
��һ��������Ϊ�Ĵ�����ַ �ڶ�������Ϊ�Ĵ�������
*/
const uint8_t kx022_init_data[] = 
{
	KX022_CNTL1_REG, 0x0A, 	//Power Mode/Bandwidth Normal   [4:3]acceleration range of x/y/z axes, 00:+/-2g, 01:+/-4g, 10:+/-8g
	KX022_CNTL3_REG, 0X02, 	//ODR                           Output data rate 25Hz
	KX022_ODCNTL_REG,0x01,  //ODR                           Output data rate 25Hz
};

/*
kx022д�Ĵ�������
������ uint8_t addr  �Ĵ�����ַ
			 uint8_t value �Ĵ�������
ע��ID��ַ����Ϊ������� �Ѿ���ȫ�������������
*/
void kx022_write_reg(uint8_t addr, uint8_t value)
{	
	__align(4) uint8_t val=0;
	val=value;
	i2c_0_write(I2C_ID_KX022, 1, addr, &val, 0x01);
}
/*
kx022���Ĵ�������
������ uint8_t addr  �Ĵ�����ַ
			 uint8_t value ����������
ע��ID��ַ����Ϊ������� �Ѿ���ȫ�������������
*/
void kx022_read_reg(uint8_t addr, uint8_t *p_value)
{
	__align(4) uint8_t val=0;
	i2c_0_read(I2C_ID_KX022, 1, addr, &val, 0x01);
	*p_value=val;
}
/*
kx022д�Ĵ�������
������ uint8_t addr  �Ĵ�����ַ
			 uint8_t buff �Ĵ�������
       uint8_t size  Ҫд����ٸ�����
ע��ID��ַ����Ϊ������� �Ѿ���ȫ�������������
    ��Ϊʹ�õ���DMA�����䣬����������뱣֤����buffΪ���ֽڶ���
*/
void kx022_write_nreg(uint8_t addr, uint8_t * buff, uint8_t size)
{
	i2c_0_write(I2C_ID_KX022, 1, addr, buff, size);
}
/*
kx022���Ĵ�������
������ uint8_t addr  �Ĵ�����ַ
			 uint8_t buff ����������
       uint8_t size  Ҫ��ȡ���ٸ�����
ע��ID��ַ����Ϊ������� �Ѿ���ȫ�������������
*/
void kx022_read_nreg(uint8_t addr, uint8_t *buff, uint8_t size)
{
	i2c_0_read(I2C_ID_KX022, 1, addr, buff, size);
}
/*
kx022��ʼ������
���������˼Ĵ���
*/
uint8_t  kx022_init(void)
{
	uint8_t i,st; 	
	kx022_write_reg(0x00, 0x24);   //��λ
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
kx022��ȡ���ٶȴ���������������ݺ���
���������uint16_t *p_x X�����ݴ洢ָ��
					uint16_t *p_y y�����ݴ洢ָ��
					uint16_t *p_z z�����ݴ洢ָ��
*/
void gensor_read_xyz(int16_t *p_x, int16_t *p_y, int16_t *p_z)
{
		__align(4) uint8_t val[6];
	
		kx022_read_nreg(KX022_X_OUTL_REG, val,6); 
		*p_x = (val[0]) | ((int16_t)val[1] << 8);
		*p_y = (val[2]) | ((int16_t)val[3] << 8);
		*p_z = (val[4]) | ((int16_t)val[5] << 8);
}		

