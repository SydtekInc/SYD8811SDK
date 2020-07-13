/*
OLED�����ļ�

���ߣ�����ʢԴ��Ƽ����޹�˾
���ڣ�2016/7/8
*/
#include "oled.h"
#include "font.h"
#include "syd8801_gpio.h"
#include "syd8801_delay.h"
#include <stdarg.h>
#include <stdio.h>

/*********************LCDд����************************************/ 
void LCD_WrDat(unsigned char dat)	 
{
	unsigned char i;
	GPIO_Pin_Set(oled_DC); 
	for(i=0;i<8;i++) //����һ����λ���� 
	{
		if((dat << i) & 0x80) GPIO_Pin_Set(oled_SDIN);
		else GPIO_Pin_Clear(oled_SDIN);
		GPIO_Pin_Clear(oled_SCLK);
		GPIO_Pin_Set(oled_SCLK);
	}
}
/*********************LCDд����************************************/										
void LCD_WrCmd(unsigned char cmd)
{
	unsigned char i;
	GPIO_Pin_Clear(oled_DC);
	for(i=0;i<8;i++) //����һ����λ���� 
	{
		if((cmd << i) & 0x80) GPIO_Pin_Set(oled_SDIN);
		else GPIO_Pin_Clear(oled_SDIN);
		GPIO_Pin_Clear(oled_SCLK);
		GPIO_Pin_Set(oled_SCLK);
	}
}
/*********************LCD ��������************************************/
void LCD_Set_Pos(unsigned char x, unsigned char y) 
{ 
	LCD_WrCmd(0xb0+y);
	LCD_WrCmd(((x&0xf0)>>4)|0x10);
	LCD_WrCmd((x&0x0f)|0x01); 
} 
/*********************LCDȫ��************************************/
void LCD_Fill(unsigned char bmp_dat) 
{
	unsigned char y,x;
	for(y=0;y<8;y++)
	{
		LCD_WrCmd(0xb0+y);
		LCD_WrCmd(0x01);
		LCD_WrCmd(0x10);
		for(x=0;x<X_WIDTH;x++)
		LCD_WrDat(bmp_dat);
	}
}
/*********************LCD��λ************************************/
void LCD_CLS(void)
{
	unsigned char y,x;	
	for(y=0;y<8;y++)
	{
		LCD_WrCmd(0xb0+y);
		LCD_WrCmd(0x01);
		LCD_WrCmd(0x10); 
		for(x=0;x<X_WIDTH;x++)
		LCD_WrDat(0);
	}								
}
/*
SPI IOg�ܽ����� 
*/
void iospi_ioconfig(void){
	GPIO_Set_Output(oled_SCLK | oled_DC | oled_SDIN | oled_CS | oled_REST | oled_POEN);
	
	GPIO_Pin_Clear(oled_CS);   //LCD_CS
	GPIO_Pin_Set(oled_POEN);   //LCD_POWER_EN
}
void oled_init(void)
{
	iospi_ioconfig();
	GPIO_Pin_Set(oled_SCLK);   //LCD_SCL
	GPIO_Pin_Clear(oled_REST);   //LCD_RST
	delay_ms(50);
	GPIO_Pin_Set(oled_REST);   //LCD_RST
  //���ϵ絽���濪ʼ��ʼ��Ҫ���㹻��ʱ�䣬���ȴ�RC��λ���   
	LCD_WrCmd(0xae);//--turn off oled panel
	LCD_WrCmd(0x00);//---set low column address
	LCD_WrCmd(0x10);//---set high column address
	LCD_WrCmd(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	LCD_WrCmd(0x81);//--set contrast control register
	LCD_WrCmd(0xcf); // Set SEG Output Current Brightness
	//LCD_WrCmd(0xcf); // Set SEG Output Current Brightness
	LCD_WrCmd(0xa1);//--Set SEG/Column Mapping     0xa0���ҷ��� 0xa1����
	LCD_WrCmd(0xc8);//Set COM/Row Scan Direction   0xc0���·��� 0xc8����
	LCD_WrCmd(0xa6);//--set normal display
	LCD_WrCmd(0xa8);//--set multiplex ratio(1 to 64)
	LCD_WrCmd(0x3f);//--1/64 duty
	LCD_WrCmd(0xd3);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	LCD_WrCmd(0x00);//-not offset
	LCD_WrCmd(0xd5);//--set display clock divide ratio/oscillator frequency
	LCD_WrCmd(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
	LCD_WrCmd(0xd9);//--set pre-charge period
	LCD_WrCmd(0xf1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	LCD_WrCmd(0xda);//--set com pins hardware configuration
	LCD_WrCmd(0x12);
	LCD_WrCmd(0xdb);//--set vcomh
	LCD_WrCmd(0x40);//Set VCOM Deselect Level
	LCD_WrCmd(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
	LCD_WrCmd(0x02);//
	LCD_WrCmd(0x8d);//--set Charge Pump enable/disable
	LCD_WrCmd(0x14);//--set(0x10) disable
	LCD_WrCmd(0xa4);// Disable Entire Display On (0xa4/0xa5)
	LCD_WrCmd(0xa6);// Disable Inverse Display On (0xa6/a7) 
	LCD_WrCmd(0xaf);//--turn on oled panel
	LCD_Fill(0x00);  //��ʼ����
	LCD_Set_Pos(0,0); 	
}
/***************������������ʾ6*8һ���׼ASCII�ַ���	��ʾ�����꣨x,y����yΪҳ��Χ0��7****************/
void LCD_P6x8Str(unsigned char x, unsigned char y,unsigned char ch[])
{
	unsigned char c=0,i=0,j=0;      
	while (ch[j]!='\0')
	{    
		c =ch[j]-32;
		if(x>126){x=0;y++;}
		LCD_Set_Pos(x,y);    
		for(i=0;i<6;i++)     
		LCD_WrDat(F6x8[c][i]);  
		x+=6;
		j++;
	}
}
/*******************������������ʾ8*16һ���׼ASCII�ַ���	 ��ʾ�����꣨x,y����yΪҳ��Χ0��7****************/
void LCD_P8x16Str(unsigned char x, unsigned y,unsigned char ch[])
{
	unsigned char c=0,i=0,j=0;
	while (ch[j]!='\0')
	{    
		c =ch[j]-32;
		if(x>120){x=0;y++;}
		LCD_Set_Pos(x,y);    
		for(i=0;i<8;i++)     
		LCD_WrDat(F8X16[c*16+i]);
		LCD_Set_Pos(x,y+1);    
		for(i=0;i<8;i++)     
		LCD_WrDat(F8X16[c*16+i+8]);  
		x+=8;
		j++;
	}
}
/*******************������������ʾ16*16�ĺ����ַ���	 ��ʾ�����꣨x,y����yΪҳ��Χ0��7****************/
void PutGB1616(unsigned short x, unsigned short  y, unsigned char *s)  
{
	unsigned short int k;
	uint8_t i;
	while(*s){
		for (k=0;k<64;k++)    //64��ʾ�Խ����ֿ��еĸ�����ѭ����ѯ����
		{ 
			if ((codeGB_16[k].Index[0]==s[0])&&(codeGB_16[k].Index[1]==s[1]))       //���ֶ�������������
			{ 
				LCD_Set_Pos(x,y);
				i=0;
				for(;i<16;i++) 
				{
					unsigned char m=codeGB_16[k].Msk[i];
					LCD_WrDat(m);
				}
				LCD_Set_Pos(x,y+1);
				for(;i<32;i++) 
				{
					unsigned char m=codeGB_16[k].Msk[i];
					LCD_WrDat(m);
				}
			}  
		}	
		s+=2;
		x+=16;
	}
}

/***********������������ʾ��ʾBMPͼƬ128��64��ʼ������(x,y),x�ķ�Χ0��127��yΪҳ�ķ�Χ0��7*****************/
void Draw_BMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[])
{ 	
 unsigned int j=0;
 unsigned char x,y;
  
  if(y1%8==0) y=y1/8;      
  else y=y1/8+1;
	for(y=y0;y<y1;y++)
	{
		LCD_Set_Pos(x0,y);				
    for(x=x0;x<x1;x++)
	    {      
	    	LCD_WrDat(BMP[j++]);	    	
	    }
	}
} 
#define MAX_FORMAT_BUFFER_SIZE	(128)
static uint8_t s_formatBuffer[MAX_FORMAT_BUFFER_SIZE];
/***********����������OLED debug*****************/
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
	LCD_P8x16Str(x,y,s_formatBuffer); 
}
