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
#include "uart.h"

extern uint8_t tx_len,rx_len, rx_buf[RX_BUF_MAX];

int main()
{	
	uint8_t i=0;	
	__disable_irq();

	BleInit();	
	MCUClockSwitch(SYSTEM_CLOCK_64M_RCOSC);
	RCOSCCalibration();
	
	PIN_Set_GPIO(U32BIT(KEY1) | U32BIT(KEY2) | U32BIT(KEY3) | U32BIT(KEY4),PIN_SEL_GPIO);
	PIN_Set_GPIO(U32BIT(LED1) | U32BIT(LED2) | U32BIT(LED3) | U32BIT(LED4),PIN_SEL_GPIO);
	
	GPIO_Set_Input( U32BIT(KEY1) | U32BIT(KEY2) | U32BIT(KEY3) | U32BIT(KEY4),  U32BIT(KEY1) | U32BIT(KEY2) | U32BIT(KEY3) | U32BIT(KEY4));	
	PIN_Pullup_Enable(T_QFN_48, U32BIT(KEY1) | U32BIT(KEY2) | U32BIT(KEY3) | U32BIT(KEY4));
	GPIO_Input_Enable(U32BIT(KEY1) | U32BIT(KEY2) | U32BIT(KEY3) | U32BIT(KEY4));
	
	GPIO_Set_Output( U32BIT(LED1) | U32BIT(LED2) | U32BIT(LED3) | U32BIT(LED4));	
	GPIO_Pin_Set(U32BIT(LED1) | U32BIT(LED2) | U32BIT(LED3) | U32BIT(LED4));
	
	dbg_init();
	UartEn(true);
	dbg_printf("SYD8811 UART1 test demo %s:%s\r\n", __DATE__ , __TIME__);

	__enable_irq();	

	while(1)
	{
		if(tx_len!=rx_len)
		{
			uint8_t len=0,rx_len_temp=rx_len;	
			if(tx_len>rx_len)
			{
				len=RX_BUF_MAX-tx_len;
				for(i=0;i<len;i++){
					uart_1_write(rx_buf[tx_len+i]);
				}
				for(i=0;i<rx_len_temp;i++){
					uart_1_write(rx_buf[i]);
				}
				tx_len=rx_len_temp;
			}
			else
			{
				len=rx_len_temp-tx_len;
				for(i=0;i<len;i++){
					uart_1_write(rx_buf[tx_len+i]);
				}
				tx_len=rx_len_temp;
			}
			
		}
	}	
}

