#include "ARMCM0.h"
#include "timer.h"
#include "gpio.h"
#include "debug.h"
#include "lib.h"
#include <string.h>
#include "delay.h"
#include "gpadc.h"
#include "i2c.h"
#include "led_key.h"
#include "spi.h"
#include "flash.h"

#define USER_FLASH_BASE_ADDR 0
#define USER_FLASH_LENGHT 233

uint8_t SPI_RX[1024] = {0}, SPI_TX[1024] = {0};

#define KEY5 GPIO_21

int main()
{	
	uint32_t id=0;
    
	__disable_irq();
	
	BleInit();	
	//根据需要重新设置时钟为4M并校准
	MCUClockSwitch(SYSTEM_CLOCK_64M_RCOSC);
	RCOSCCalibration();
	
	dbg_init();
	UartEn(true);
	dbg_printf("SYD8811 SPIMaster FLASH demo %s:%s\r\n",__DATE__ ,__TIME__);

	PIN_Set_GPIO(U32BIT(LED1) | U32BIT(LED2),PIN_SEL_GPIO);
	GPIO_Set_Output( U32BIT(LED1) | U32BIT(LED2));	
	GPIO_Pin_Set(U32BIT(LED1) | U32BIT(LED2));
	
	PIN_Set_GPIO(U32BIT(KEY1) | U32BIT(KEY2) | U32BIT(KEY3) | U32BIT(KEY4),PIN_SEL_GPIO);
	
	GPIO_Set_Input( U32BIT(KEY5),  U32BIT(KEY5));	
	PIN_Pullup_Enable(T_QFN_48, U32BIT(KEY5));
	GPIO_Input_Enable(U32BIT(KEY5));
	
	spi_init(FLASH_SPI);
	id =SPI_Flash_ReadID();
	if((id != FLASH_ID1) && (id != FLASH_ID2))dbg_printf("flash filed id:%x\r\n",id);
	else dbg_printf("flash succeed id:%x\r\n",id);
	
	__enable_irq();	

	while(1)
	{
		GPIO_Pin_Turn(U32BIT(LED1));
		if(GPIO_Pin_Read( U32BIT(KEY5))){
			uint32_t i=0;
			//erase
			SPI_Flash_Erase_Sector(USER_FLASH_BASE_ADDR);
			dbg_printf("erase addr:%x\r\n",USER_FLASH_BASE_ADDR);
			//write
			for(i=0;i<sizeof(SPI_TX);i++) SPI_TX[i]=i;
			SPI_Flash_Erase_Sector(USER_FLASH_BASE_ADDR);
			SPI_Flash_Write_NoCheck(SPI_TX,USER_FLASH_BASE_ADDR,USER_FLASH_LENGHT);
			dbg_hexdump("write addr:0\r\n",SPI_TX, 64);
			dbg_hexdump("write addr:200\r\n",&SPI_TX[200], 16);
			//read
			memset(SPI_RX,0,sizeof(SPI_RX));
			SPI_Flash_Read(SPI_RX,USER_FLASH_BASE_ADDR,USER_FLASH_LENGHT);
			dbg_hexdump("read addr:0\r\n",SPI_RX, 64);
			dbg_hexdump("read addr:200\r\n",&SPI_RX[200], 16);
			//compare
			for(i=0;i<USER_FLASH_LENGHT;i++)
			{			
				if(SPI_TX[i]!=SPI_RX[i])
				{
					dbg_printf("flash Operation error %x\r\n",i);
					break;
				}
			}
			if(i>=USER_FLASH_LENGHT)
			{
				dbg_printf("flash Operation OK!\r\n");
			}
			GPIO_Pin_Turn(LED2);
			delay_ms(2000);
		}
		delay_ms(1000);
	}	
}

