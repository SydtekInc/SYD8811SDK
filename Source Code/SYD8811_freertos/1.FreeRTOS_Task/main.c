/* BLE */
#include "ARMCM0.h"
#include "config.h"
#include "lib.h"
#include "SYD_ble_service_Profile.h"
#include "ble.h"

/* freeRTOS */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"

/*drive*/
#include "debug.h"
//#include "uart_0_debug.h"
#include "gpio.h"
#include "led_key.h"


void board_init(void)
{
	#ifdef CONFIG_UART_ENABLE
	dbg_init();
	UartEn(true);
	DBGPRINTF("\r\nSYD8811 Uart debug mode test.\r\n");
	#endif
	
	GPIO_Set_Output(U32BIT(LED1));
	PIN_Pullup_Disable(T_QFN_48, U32BIT(LED1));
	GPIO_Pin_Set(U32BIT(LED1));	
}


//Task1
void Task1( void *pvParameters )
{
	for( ;; )
	{		
		vTaskDelay(500);//500ms
		GPIO_Pin_Turn(U32BIT(LED1));
		DBGPRINTF(("\r\nTask1 vTaskDelay\r\n"));
	}	
}

//Task2
void Task2( void *pvParameters )
{
	portTickType xLastWakeTime;
	 xLastWakeTime = xTaskGetTickCount();
	for( ;; )
	{		
		vTaskDelayUntil( &xLastWakeTime, 3000 );
		DBGPRINTF(("\r\nTask2 vTaskDelayUntil\r\n"));
	}	
}



void vStartThreadTasks( void )
{
	BaseType_t xReturn = pdPASS;/* Create Result*/
	
	DBGPRINTF(("Init task\r\n"));

	xReturn = xTaskCreate( Task1, "Task1", configMINIMAL_STACK_SIZE, NULL, 4, ( xTaskHandle * ) NULL );
	if(pdPASS == xReturn) DBGPRINTF(("Create Task1 Success!\r\n"));
	
	xReturn = xTaskCreate( Task2, "Task2", configMINIMAL_STACK_SIZE, NULL, 3, ( xTaskHandle * ) NULL );
	if(pdPASS == xReturn) DBGPRINTF(("Create Task2 Success!\r\n"));

	DBGPRINTF(("\r\nSYD8811 freeRTOS Start\r\n"));
	DBGPRINTF(("\r\n"));
}


/*-----------------------------------------------------------*/
int main( void )
{
	__disable_irq();
	
	//ble stack init
	ble_init();
	
	MCUClockSwitch(SYSTEM_CLOCK_64M_RCOSC);
	RCOSCCalibration();
	
	#ifdef USER_32K_CLOCK_RCOSC
	ClockSwitch(SYSTEM_32K_CLOCK_RCOSC);
	LPOCalibration();
	#else
	ClockSwitch(SYSTEM_32K_CLOCK_XOSC);
	#endif
	
	board_init();
	DBGPRINTF(("board hardware init\r\n"));

	__enable_irq();	

	vStartThreadTasks();
	
	/* Start the scheduler. */
	vTaskStartScheduler();
	/* Will only get here if there was not enough heap space to create the
	idle task. */
	return 0;
}

