/*
OLED�����ļ�

���ߣ�����ʢԴ��Ƽ����޹�˾
���ڣ�2016/7/8
*/
#include "oled.h"
#include "font.h"
#include "gpio.h"
#include "i2c.h"
#include "delay.h"
#include <stdarg.h>
#include <stdio.h>

static void oled_wrcmd(uint8_t cmd)
{		
	i2c_1_write(I2C_ID_OLED, 0x01, 0x00, &cmd, 0x01);
}

void oled_wrdat(uint8_t dat)	 
{
	i2c_1_write(I2C_ID_OLED, 0x01, 0x40, &dat, 0x01);
}
/*********************LCDȫ��************************************/
static void oled_fill(uint8_t bmp_dat) 
{
	uint8_t y,x;
	for(y=0;y<8;y++)
	{
		oled_wrcmd(0xb0+y);
		oled_wrcmd(0x01);
		oled_wrcmd(0x10);
		
		for(x=0;x<X_WIDTH;x++)
			oled_wrdat(bmp_dat);
	}
}
/*********************LCD ��������************************************/
void oled_set_pos(uint8_t x, uint8_t y) 
{ 
	oled_wrcmd(0xb0+y);
	oled_wrcmd(((x&0xf0)>>4)|0x10);
	oled_wrcmd((x&0x0f)|0x01); 
}

void oled_init(void)
{
	GPIO_Set_Output( U32BIT(oled_rest));	
	GPIO_Pin_Clear(U32BIT(oled_rest));
	delay_ms(10);
	GPIO_Pin_Set(U32BIT(oled_rest));
	delay_ms(10);
	
	i2c_Init(I2C1,U32BIT(I2C_SCLK),U32BIT(I2C_SDA));
	
    oled_wrcmd(0xAE);//--turn off oled panel
	oled_wrcmd(0x00);//---set low column address
	oled_wrcmd(0x10);//---set high column address
	oled_wrcmd(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	oled_wrcmd(0x81);//--set contrast control register
	oled_wrcmd(0xCF); // Set SEG Output Current Brightness
	oled_wrcmd(0xA1);//--Set SEG/Column Mapping     0xa0???? 0xa1??
	oled_wrcmd(0xC8);//Set COM/Row Scan Direction   0xc0???? 0xc8??
	oled_wrcmd(0xA6);//--set normal display
	oled_wrcmd(0xA8);//--set multiplex ratio(1 to 64)
	oled_wrcmd(0x3f);//--1/64 duty
	oled_wrcmd(0xD3);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	oled_wrcmd(0x00);//-not offset
	oled_wrcmd(0xd5);//--set display clock divide ratio/oscillator frequency
	oled_wrcmd(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
	oled_wrcmd(0xD9);//--set pre-charge period
	oled_wrcmd(0xF1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	oled_wrcmd(0xDA);//--set com pins hardware configuration
	oled_wrcmd(0x12);
	oled_wrcmd(0xDB);//--set vcomh
	oled_wrcmd(0x40);//Set VCOM Deselect Level
	oled_wrcmd(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
	oled_wrcmd(0x02);//
	oled_wrcmd(0x8D);//--set Charge Pump enable/disable
	oled_wrcmd(0x14);//--set(0x10) disable
	oled_wrcmd(0xA4);// Disable Entire Display On (0xa4/0xa5)
	oled_wrcmd(0xA6);// Disable Inverse Display On (0xa6/a7) 
	oled_wrcmd(0xAF);//--turn on oled panel

	oled_fill(0x00);  //
	oled_set_pos(0,0); 
}
/*
������������ʾ6*8һ���׼ASCII�ַ���	 
���������uint8_t x  X�������꣬ȡֵ��Χ��32~127(�ܹ���96������)
					uint8_t Y  Y�������꣬ȡֵ��Χ��0~3 ע��Y����������ǰ�ҳ����ģ�1ҳ��8�����أ� ����һ����32�����أ�Ҳ����4ҳ
					uint8_t ch[] Ҫ��ʾ���ַ���
*/
void oled_6x8str(uint8_t x, uint8_t y,uint8_t ch[])
{
	uint8_t c=0,i=0,j=0;
	
	while (ch[j]!='\0')
	{    
		c =ch[j]-32;
		
		if(x>126){x=0;y++;}
			oled_set_pos(x,y);    
			
		for(i=0;i<6;i++)     
			oled_wrdat(F6x8[c][i]);  
		
		x+=6;
		j++;
	}
}
/*
������������ʾ8*16һ���׼ASCII�ַ���	 
���������uint8_t x  X�������꣬ȡֵ��Χ��32~127(�ܹ���96������)
					uint8_t Y  Y�������꣬ȡֵ��Χ��0~3 ע��Y����������ǰ�ҳ����ģ�1ҳ��8�����أ� ����һ����32�����أ�Ҳ����4ҳ
					uint8_t ch[] Ҫ��ʾ���ַ���
*/
void oled_8x16str(uint8_t x, uint8_t y,uint8_t ch[])
{
	uint8_t c=0,i=0,j=0;
	
	while (ch[j]!='\0')
	{    
		c =ch[j]-32;
		
		if(x>120){x=0;y++;}
			oled_set_pos(x,y);    
			
		for(i=0;i<8;i++)     
			oled_wrdat(F8X16[c*16+i]);
		
		oled_set_pos(x,y+1);    
		
		for(i=0;i<8;i++)     
			oled_wrdat(F8X16[c*16+i+8]);  
		
		x+=8;
		j++;
	}
}
/*******************������������ʾ16*16�ĺ����ַ���****************/
void PutGB1616(unsigned short x, unsigned short  y, unsigned char *s)  
{
	unsigned short int k;
	uint8_t i;
	while(*s){
		for (k=0;k<64;k++)    //64��ʾ�Խ����ֿ��еĸ�����ѭ����ѯ����
		{ 
			if ((codeGB_16[k].Index[0]==s[0])&&(codeGB_16[k].Index[1]==s[1]))       //���ֶ�������������
			{ 
				oled_set_pos(x,y);
				i=0;
				for(;i<16;i++) 
				{
					unsigned char m=codeGB_16[k].Msk[i];
					oled_wrdat(m);
				}
				oled_set_pos(x,y+1);
				for(;i<32;i++) 
				{
					unsigned char m=codeGB_16[k].Msk[i];
					oled_wrdat(m);
				}
			}  
		}	
		s+=2;
		x+=16;
	}
}
/***********����������OLED debug*****************/
#define MAX_FORMAT_BUFFER_SIZE	(128)
static uint8_t s_formatBuffer[MAX_FORMAT_BUFFER_SIZE];
void oled_printf(uint8_t x, uint8_t y,char *format,...) 
{
	uint8_t iWriteNum = 0;	
	va_list  ap;
	if(!format)
		return;
	va_start(ap,format);    //��ȡap(va_list��ʽ����������ָ�����������ָ��)   formatΪ����ĸ�ʽ
	iWriteNum = vsprintf((char *)s_formatBuffer,format,ap);  //��ap����format�ĸ�ʽд��s_formatBuffer��  ���صĽ�����ַ����ĳ���
	va_end(ap);   //�ͷŵ�ap
	if(iWriteNum > MAX_FORMAT_BUFFER_SIZE)
		iWriteNum = MAX_FORMAT_BUFFER_SIZE;
	s_formatBuffer[iWriteNum] = '\0';
	oled_8x16str(x,y,s_formatBuffer); 
}
