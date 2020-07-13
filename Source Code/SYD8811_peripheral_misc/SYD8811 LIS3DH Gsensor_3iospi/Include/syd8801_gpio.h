#ifndef _SYD8801_GPIO_H_
#define _SYD8801_GPIO_H_

#include "ARMCM0.h"

extern PIN_CONFIG_TYPE *	PIN_CONFIG;
extern GPO_CTRL_TYPE *	GPO_CTRL;
extern GPI_CTRL_TYPE *	GPI_CTRL;
extern GPIO_IRQ_CTRL_TYPE * GPIO_IRQ_CTRL;

void GPIO_Pin_Set(uint32_t io);
void GPIO_Set_Output(uint32_t io);
void GPIO_Pin_Clear(uint32_t io);
void GPIO_Set_Input(uint32_t io);
uint8_t GPIO_Pin_Read(uint32_t io);
void io_irq_enable(uint32_t io, void *  p_callback);
void io_irq_disable(void);
void GPIO_Pin_Turn(uint32_t io);

#endif
