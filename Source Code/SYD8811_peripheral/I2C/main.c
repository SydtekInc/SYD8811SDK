#include "ARMCM0.h"
#include "timer.h"
#include "gpio.h"
#include "debug.h"
#include "lib.h"
#include <string.h>
#include "delay.h"
#include "config.h"
#include "i2c.h"
#include "gsensor.h"

#define I2C_SCLK  GPIO_11
#define I2C_SDA   GPIO_13

int main()
{	
	int16_t x,y,z;
	uint16_t i=0;
	float vat=0.0;
	__disable_irq();
	BleInit();
	
	MCUClockSwitch(SYSTEM_CLOCK_64M_RCOSC);
	RCOSCCalibration();
	//ClockSwitch(SYSTEM_32K_CLOCK_XOSC);
	
	dbg_init();
	UartEn(true);
	dbg_printf("SYD8811 I2C test demo %s:%s\r\n",__DATE__ ,__TIME__);
	
	i2c_Init(I2C0,U32BIT(I2C_SCLK),U32BIT(I2C_SDA));
	
	if(kx022_init()) 
		dbg_printf("kx022 init succeed\r\n");
	else 
		dbg_printf("kx022 init faild\r\n");
	
	__enable_irq();	

	while(1)
	{
		/*
		���㹫ʽ�����ٶ� = ������ԭʼֵ * 8000mG / 65536 / 1000  
		���е�8000mG�������ģ������̵Ĳ��������� +-4G  Ҳ��������4G�ķ�Χ����������Resolution/Range�Ĵ��������õ�
		��ô���ܶ��������������65536��Ҳ����˵ÿ�����ݵĿ̶��� 8000/65536 mg
		*/
		gensor_read_xyz(&x, &y, &z);
		vat=(float)x*8000/65536/1000;
		dbg_printf("x : %02x vat: %4.3f i:%d\r\n",x,vat,i);
		vat=(float)y*8000/65536/1000;
		dbg_printf("y : %02x vat: %4.3f i:%d\r\n",y,vat,i);
		vat=(float)z*8000/65536/1000;
		dbg_printf("z : %02x vat: %4.3f i:%d\r\n",z,vat,i);
		delay_ms(500);
		i++;
	}	
}

