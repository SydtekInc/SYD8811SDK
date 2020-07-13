/*
�������ļ�
���Բ��裺
1.ȷ���Ѿ������Ͽ����岢��װ��PL2303���������򣬲������豸�������¿��Կ������ں�
2.�򿪹���Ŀ¼��Tool�ļ�����ġ�SYD BLE Utility.exe������
3.��UART����Կ������ںţ�ѡ����ȷ�Ĵ���
4.�����open����ť����ʱ��"SYD8801 Evaluation board"����ʾ:"Wait..."
5.��ʱ���¿������ϵĸ�λ������ʾ�ͻ��ɡ�Ready��
6.�ڡ�Firmware����"FW(Upgrade)"�е����Open FW File����ťѡ�񱾹����ڡ�Objects���ļ��еġ�Module_samples.hex���ļ�
7.�ڡ�Firmware����"FW(Upgrade)"�е����Write to Flah����ť,���ɿ������ؽ��ȣ��ȴ��������
8.������ɺ��¸�λ�����ɿ�����ʵ������
9.�ٴ����أ����"SYD8801 Evaluation board"��Detect��ť��Ȼ��ӵ�5���ٴβ�������
��ע�������Ѿ������˴��ڳ���İ��ӣ���ʱ��һ�����open����ť�ͽ�����readey״̬����ʱ��һ�����²�������ģ���ʱ�����һֱ���Ÿ�λ��Ȼ������open����ť��������waite״̬ʱ��ſ���λ���������Ϳ������س�����

���ߣ�����ʢԴ��Ƽ����޹�˾
���ڣ�2016/7/8
*/
#include "ARMCM0.h"
#include "syd8801_gpio.h"
#include "syd8801_delay.h"
#include "syd8801_timer.h"
#include "syd8801_uart.h"
#include "syd8801_wdt.h"
#include "syd8801_pwm.h"
#include "syd8801_debug.h"
#include "syd8801_adc.h"
#include "lis3dh.h"
#include "led.h"
#include "key.h"
#include "oled.h"

int main()
{
	int16_t x,y,z;
	uint16_t i=0;
	float vat=0.0;
	dbg_init();
	lis3dh_init();
  lis3dh_strat_accelerometer();
	
	while(1)
	{
		/*
		���㹫ʽ�����ٶ� = ������ԭʼֵ * 16000mG / 65536  
		���е�16000mG�������ģ������̵Ĳ��������� +-8G  Ҳ��������8G�ķ�Χ����������CTRL_REG4�Ĵ��������õ�
		��ô���ܶ��������������65536��Ҳ����˵ÿ�����ݵĿ̶��� 16000/65536 mg
		�ѿ�����ƽ���������ϣ�����õ������� X:FFC0  Y:0000 Z:1100  ����FFC0��ʾ������ֵ�� -(FFFF-FFC0)�Ǹ���ֵ������ͺ�С���Ժ��ԣ���ô�Ϳ�����Ϊ�������ٶ�ȫ��Z����
		Z���������1100������һ��16�������ݣ�ʮ���ƾ���4352����ôZ��ļ��ٶ�Ҳ�����������ٶ��ǣ�4352*16000/65536 mg=1062.5 mg  Ҳ����˵�������ٶ���1.0652��G�������ֵ���ǿ���������
		*/
		lis3dh_get_accelerometer_data(&x, &y, &z);
		vat=(float)x*16000/65536/1000;
		dbg_printf("x : %04x vat: %4.3f i:%d\r\n",x,vat,i);
		vat=(float)y*16000/65536/1000;
		dbg_printf("y : %04x vat: %4.3f i:%d\r\n",y,vat,i);
		vat=(float)z*16000/65536/1000;
		dbg_printf("z : %04x vat: %4.3f i:%d\r\n",z,vat,i);
		
		delay_ms(500);
		i++;
	}
}
