#include "ARMCM0.h"
#include "timer.h"
#include "gpio.h"
#include "debug.h"
#include "lib.h"
#include <string.h>
#include "delay.h"
#include "gpadc.h"
#include "led_key.h"
#include "config.h"

extern  uint8_t channel;

#define WRITE_READ_LEN 32

#define FLASH_INTERNAL_DATA_ADDR   0x00

static void user_gpio_callback()
{
	uint32_t SW;

	SW=GPIO_IRQ_CTRL->GPIO_INT; 

	if(SW&U32BIT(KEY3))
	{
		GPIO_Pin_Turn(U32BIT(LED3));
		dbg_printf("KEY3 Irq down\r\n");
		delay_ms(1000);
	}
	if(SW&U32BIT(KEY4))
	{
		GPIO_Pin_Turn(U32BIT(LED4));
		dbg_printf("KEY4 Irq down\r\n");
		delay_ms(1000);
	}
}

int main()
{	
	uint16_t i=0;
	uint16_t addr=0;
	uint8_t tx_buff[32],rx_buff[32],base_data=0;
	__disable_irq();

	BleInit();	
	MCUClockSwitch(SYSTEM_CLOCK_64M_RCOSC);
	RCOSCCalibration();
	
	dbg_init();
	UartEn(true);
	dbg_printf("SYD8811 GPIO test demo %s:%s\r\n", __DATE__ , __TIME__);
	
	PIN_Set_GPIO(U32BIT(KEY1) | U32BIT(KEY2) | U32BIT(KEY3) | U32BIT(KEY4),PIN_SEL_GPIO);
	PIN_Set_GPIO(U32BIT(LED1) | U32BIT(LED2) | U32BIT(LED3) | U32BIT(LED4),PIN_SEL_GPIO);
	
	GPIO_Set_Input( U32BIT(KEY1) | U32BIT(KEY2) | U32BIT(KEY3) | U32BIT(KEY4),  U32BIT(KEY1) | U32BIT(KEY2) | U32BIT(KEY3) | U32BIT(KEY4));	
	PIN_Pullup_Enable(T_QFN_48, U32BIT(KEY1) | U32BIT(KEY2) | U32BIT(KEY3) | U32BIT(KEY4));
	GPIO_Input_Enable(U32BIT(KEY1) | U32BIT(KEY2) | U32BIT(KEY3) | U32BIT(KEY4));
	
	io_irq_enable(U32BIT(KEY4), &user_gpio_callback);
	
	GPIO_Set_Output( U32BIT(LED1) | U32BIT(LED2) | U32BIT(LED3) | U32BIT(LED4));	
	GPIO_Pin_Set(U32BIT(LED1) | U32BIT(LED2) | U32BIT(LED3) | U32BIT(LED4));

	__enable_irq();	

	while(1)
	{
		if(GPIO_Pin_Read( U32BIT(KEY1)))
		{
			for(i=0;i<WRITE_READ_LEN;i++)
			{
				tx_buff[i]=base_data+i;
			}
			//注意ble_flash_erase函数会进行擦除操作，所以必须要保证地址是正确的
//			EraseFlashData(FLASH_INTERNAL_DATA_ADDR+addr,1);   //注意这里是标准的flash操作，在写数据之前必须要擦除，除非要写的地址区域已经被擦除过
//			WriteFlashData(FLASH_INTERNAL_DATA_ADDR+addr,WRITE_READ_LEN, tx_buff); 
			//注意：CODEB的函数为代码大小减去16K，比如代码区为160KB，那么CODB的大小九尾160-16=144KB
			EraseCodeB(FLASH_INTERNAL_DATA_ADDR+addr,1);   //注意这里是标准的flash操作，在写数据之前必须要擦除，除非要写的地址区域已经被擦除过
			WriteCodeB(FLASH_INTERNAL_DATA_ADDR+addr,WRITE_READ_LEN, tx_buff); 
			dbg_printf("write addr:%04x len:%04x\r\n",FLASH_INTERNAL_DATA_ADDR+addr,WRITE_READ_LEN);
			DBGHEXDUMP("",tx_buff,WRITE_READ_LEN);
			base_data++;
		  GPIO_Pin_Turn(LED1);
			delay_ms(600);
		}
		if(GPIO_Pin_Read( U32BIT(KEY2)))
		{
			GPIO_Pin_Turn(LED2);
			memset(rx_buff,0,WRITE_READ_LEN);
//			ReadFlashData(FLASH_INTERNAL_DATA_ADDR+addr,WRITE_READ_LEN, rx_buff);
			//注意：CODEB的函数为代码大小减去16K，比如代码区为160KB，那么CODB的大小九尾160-16=144KB
		    ReadCodeB(FLASH_INTERNAL_DATA_ADDR+addr,WRITE_READ_LEN, rx_buff);
			dbg_printf("read addr:%04x len:%04x\r\n",FLASH_INTERNAL_DATA_ADDR+addr,WRITE_READ_LEN);
			DBGHEXDUMP("",rx_buff,WRITE_READ_LEN);
			if(memcmp(rx_buff,tx_buff,WRITE_READ_LEN)==0)
			{
				dbg_printf("memcmp ok!\r\n");
			}
			else
			{
				dbg_printf("memcmp faile!\r\n");
			}
			delay_ms(600);
		}
		
		if(GPIO_Pin_Read( U32BIT(KEY3)))
		{
			GPIO_Pin_Turn(LED3);
			addr+=256;
			dbg_printf("write read addr:%04x\r\n",FLASH_INTERNAL_DATA_ADDR+addr);
			delay_ms(600);
		}
	}	
}

