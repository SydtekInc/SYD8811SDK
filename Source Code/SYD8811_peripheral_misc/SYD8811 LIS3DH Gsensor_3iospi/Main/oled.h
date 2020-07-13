#ifndef _OLED_H_
#define _OLED_H_

#include "ARMCM0.h"

#define oled_SCLK   BIT11
#define oled_DC     BIT12
#define oled_SDIN   BIT13
#define oled_CS     BIT14 
#define oled_REST   BIT15
#define oled_POEN   BIT16

#define XLevelL		0x00
#define XLevelH		0x10
#define XLevel	    ((XLevelH&0x0F)*16+XLevelL)
#define Max_Column	128
#define Max_Row		  64
#define	Brightness	0xCF 
#define X_WIDTH 128
#define Y_WIDTH 64


void oled_init(void);
void LCD_P6x8Str(unsigned char x, unsigned char y,unsigned char ch[]);
void LCD_P8x16Str(unsigned char x, unsigned y,unsigned char ch[]);
void LCD_P16x16Ch(unsigned char x, unsigned char y,unsigned char  N);
void Draw_BMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
extern void oled_printf(uint8_t x, uint8_t y,char *format,...);
void PutGB1616(unsigned short x, unsigned short  y, unsigned char *s);


#endif
