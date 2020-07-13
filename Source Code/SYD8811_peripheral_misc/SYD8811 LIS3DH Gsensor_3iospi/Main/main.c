/*
主函数文件
测试步骤：
1.确保已经连接上开发板并安装上PL2303的驱动程序，并且自设备管理器下可以看到串口号
2.打开工程目录下Tool文件夹里的“SYD BLE Utility.exe”程序
3.在UART里可以看到串口号，选择正确的串口
4.点击“open”按钮，此时在"SYD8801 Evaluation board"里提示:"Wait..."
5.此时按下开发板上的复位键，提示就会变成“Ready”
6.在“Firmware”的"FW(Upgrade)"中点击“Open FW File”按钮选择本工程在“Objects”文件夹的“Module_samples.hex”文件
7.在“Firmware”的"FW(Upgrade)"中点击“Write to Flah”按钮,即可看到下载进度，等待下载完成
8.下载完成后按下复位键即可看到本实验现象
9.再次下载：点击"SYD8801 Evaluation board"的Detect按钮，然后从第5步再次操作即可
备注：对于已经下载了串口程序的板子，有时候一点击“open”按钮就进入了readey状态，这时候一般是下不进程序的，这时候可以一直按着复位键然后点击“open”按钮，当进入waite状态时候放开复位键，这样就可以下载程序了

作者：北京盛源达科技有限公司
日期：2016/7/8
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
		计算公式：加速度 = 读到的原始值 * 16000mG / 65536  
		其中的16000mG是这样的：本例程的测量量程是 +-8G  也就是正负8G的范围，这里是在CTRL_REG4寄存器里设置的
		那么所能读到的最大数据是65536，也就是说每个数据的刻度是 16000/65536 mg
		把开发板平放在桌面上，所测得的数据是 X:FFC0  Y:0000 Z:1100  其中FFC0表示他的数值是 -(FFFF-FFC0)是个负值，这个就很小可以忽略，那么就可以认为重力加速度全在Z轴上
		Z轴的数据是1100，这是一个16进制数据，十进制就是4352，那么Z轴的加速度也就是重力加速度是：4352*16000/65536 mg=1062.5 mg  也就是说重力加速度是1.0652个G，这个数值还是可以信赖的
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
