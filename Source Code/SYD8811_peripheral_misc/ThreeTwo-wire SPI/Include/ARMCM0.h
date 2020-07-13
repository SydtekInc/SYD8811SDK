/*
Mo内核中断号定义、syd8801寄存器定义文件

作者：北京盛源达科技有限公司
日期：2016/7/8
*/
#ifndef ARMCM0_H
#define ARMCM0_H

#ifdef __cplusplus
extern "C" {
#endif

/* -------------------------  Interrupt Number Definition  ------------------------ */

typedef enum IRQn
{
/* -------------------  Cortex-M0 Processor Exceptions Numbers  ------------------- */
	NonMaskableInt_IRQn	= -14,      /*!<  2 Non Maskable Interrupt          */
	HardFault_IRQn                = -13,      /*!<  3 HardFault Interrupt             */
	SVCall_IRQn                  	=  -5,      /*!< 11 SV Call Interrupt               */
	PendSV_IRQn                   =  -2,      /*!< 14 Pend SV Interrupt               */
	SysTick_IRQn                  =  -1,      /*!< 15 System Tick Interrupt           */
/* ----------------------  ARMCM0 Specific Interrupt Numbers  --------------------- */	
	LLC_IRQn                    =   1,      /*!< LLC Interrupt                      */
	RTC_IRQn                   	=   2,      /*!< RTC Interrupt                      */
	SW_IRQn                   	=   3,      /*!< SW Interrupt                       */	
	I2C0_IRQn                   =   4,      /*!< I2C0 Interrupt                     */
	I2C1_IRQn                   =   5,      /*!< I2C1 Interrupt                     */
	UART0_IRQn                  =   6,      /*!< UART0 Interrupt                    */
	UART1_IRQn                  =   7,      /*!< UART1 Interrupt                    */
	TIMER0_IRQn                 =   8,      /*!< TIMER0 Interrupt                   */
	TIMER1_IRQn                	=   9, 	 /*!< TIMER1 Interrupt                      */
	TIMER2_IRQn                 =   10,      /*!< TIMER2 Interrupt                  */
	TIMER3_IRQn                 =   11,      /*!< TIMER3 Interrupt                  */
	GPIO_IRQn                   =   12,      /*!< GPIO Interrupt                    */
	HID_IRQn                    =   13,      /*!< HID Interrupt                     */
	SPIM_IRQn                  	=   14,      /*!< SPI Master Interrupt              */
	CAP_IRQn                  	=   15,      /*!< CAT detect Interrupt              */
	GPADC_IRQn                 	=   16,      /*!< GPADC Interrupt                   */
	LLC2_IRQn                   =   17,      /*!< LLC2 Interrupt                    */
	SC_IRQn                    	=   18,      /*!< Smart Card Interrupt              */
	IR_Tx_IRQn	                =   19,      /*!< IR Transmit Interrupt             */
	TOUCH_IRQn		              =   20,      /*!< TOUCH Interrupt   	              */
	HPWM_IRQn			              =   21,      /*!< High-speed PWM Interrupt          */
	HTIMER_IRQn				          =   22,      /*!< High-speed Timer Interrupt        */
	IR_Rx_IRQn					        =   23,      /*!< IR Receive Interrupt              */
} IRQn_Type;


/* ================================================================================ */
/* ================      Processor and Core Peripheral Section     ================ */
/* ================================================================================ */
#define __CM0_REV                 0x0000    /*!< Core revision r0p0                              */
#define __MPU_PRESENT             0         /*!< MPU present or not                              */
#define __NVIC_PRIO_BITS          2         /*!< Number of Bits used for Priority Levels         */
#define __Vendor_SysTickConfig    0         /*!< Set to 1 if different SysTick Config is used    */

#include <core_cm0.h>                       /* Processor and core peripherals                    */
#include "system_ARMCM0.h"                  /* System Header                                     */

/* -------------------  Start of section using anonymous unions  ------------------ */
#if defined(__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined(__ICCARM__)
  #pragma language=extended
#elif defined(__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined(__TMS470__)
/* anonymous unions are enabled by default */
#elif defined(__TASKING__)
  #pragma warning 586
#elif defined ( __CSMC__ )		/* Cosmic */
/* anonymous unions are enabled by default */
#else
  #warning Not supported compiler type
#endif

#ifndef bool
	typedef unsigned char			bool;
#endif

#ifndef true
	#define true		1
#endif

#ifndef false
	#define false		0
#endif

#pragma pack(1)
/* -------------------------------------------------------------------------------- */
/* ----------------------       Device Specific Peripheral Section       ---------------------- */
/* -------------------------------------------------------------------------------- */
/* ============================ Parameters define====================== */
/* ============================================================== */
#define U32BIT(s)			((uint32_t)1<<(s))
#define BIT(s)				((uint8_t)1<<(s))

#define BIT0					0x01
#define BIT1					0x02
#define BIT2					0x04
#define BIT3					0x08
#define BIT4					0x10
#define BIT5					0x20
#define BIT6					0x40
#define BIT7					0x80
#define BIT8					0x100
#define BIT9					0x200
#define BIT10					0x400
#define BIT11					0x800
#define BIT12					0x1000
#define BIT13					0x2000
#define BIT14					0x4000
#define BIT15					0x8000
#define BIT16					0x10000
#define BIT17					0x20000
#define BIT18 					0x40000
#define BIT19					0x80000
#define BIT20					0x100000
#define BIT21					0x200000
#define BIT22					0x400000
#define BIT23					0x800000
#define BIT24					0x1000000
#define BIT25					0x2000000
#define BIT26					0x4000000
#define BIT27					0x8000000
#define BIT28					0x10000000
#define BIT29					0x20000000
#define BIT30					0x40000000
#define BIT31					0x80000000
#define BITALL					0xFFFFFFFF

enum GPIO_DEFINE {
	GPIO_0		= 0x00,
	GPIO_1,
	GPIO_2,
	GPIO_3,
	GPIO_4,
	GPIO_5,
	GPIO_6,
	GPIO_7,
	GPIO_8,
	GPIO_9,
	GPIO_10,
	GPIO_11,
	GPIO_12,
	GPIO_13,
	GPIO_14,
	GPIO_15,
	GPIO_16,
	GPIO_17,
	GPIO_18,
	GPIO_19,
	GPIO_20,
	GPIO_21,
	GPIO_22,
	GPIO_23,
	GPIO_24,
	GPIO_25,
	GPIO_26,
	GPIO_27,
	GPIO_28,
	GPIO_29,
	GPIO_30,
	GPIO_31,
};


enum PIN_FUNCTION_DEFINE {
	PIN_SEL_GPIO,
	PIN_SEL_UART_CTS0,
	PIN_SEL_UART_RTS0,
	PIN_SEL_UART_RXD0,
	PIN_SEL_UART_TXD0,
	PIN_SEL_UART_RXD1,
	PIN_SEL_UART_TXD1,
	PIN_SEL_SPIM_CSN,
	PIN_SEL_SPIM_CLK,
	PIN_SEL_SPIM_MOSI,
	PIN_SEL_SPIM_MISO,
	PIN_SEL_I2C_SCL0,
	PIN_SEL_I2C_SDA0,
	PIN_SEL_I2C_SCL1,
	PIN_SEL_I2C_SDA1,
	PIN_SEL_PWM_0,
	PIN_SEL_PWM_1,
	PIN_SEL_PWM_2,
	PIN_SEL_IR_OUT,
	PIN_SEL_SC_IO,
	PIN_SEL_SC_DETECT,
	PIN_SEL_SC_RSTN,
	PIN_SEL_SC_CLK,
	HPWM0,
	HPWM1,
	HPWM2,
	HPWM3,	
	HID_SEN,
	PIN_SEL_ANALOG,
	PIN_SEL_DIGITAL_DEBUG,
	PIN_SEL_RF_DEBUG,

	//
	PIN_PULL_UP				= 0x01,
	PIN_FLOATINF			= 0x00,
	GPIO_SET_INPUT			= 0x01, 
	GPIO_SET_OUTPUT			= 0x00,
	PIN_INPUT_IVERTED		= 0x01,
	PIN_INPUT_NOT_IVERTED	= 0x00,	
	PIN_INPUT_ENABLE		= 0x01,
	PIN_INPUT_DISABLE		= 0x00,		
};
/* ============================ PIN CONFIG ========================= */
typedef union{
	struct {
			/* 0x00  */
			__IO  uint8_t  PIN_0_SEL:6;
			__IO  uint8_t  RSVD_0:2;
			__IO  uint8_t  PIN_1_SEL:6;
			__IO  uint8_t  RSVD_1:2;
			__IO  uint8_t  PIN_2_SEL:6;
			__IO  uint8_t  RSVD_2:2;
			__IO  uint8_t  PIN_3_SEL:6;
			__IO  uint8_t  RSVD_3:2;
			__IO  uint8_t  PIN_4_SEL:6;
			__IO  uint8_t  RSVD_4:2;
			__IO  uint8_t  PIN_5_SEL:6;
			__IO  uint8_t  RSVD_5:2;
			__IO  uint8_t  PIN_6_SEL:6;
			__IO  uint8_t  RSVD_6:2;
			__IO  uint8_t  PIN_7_SEL:6;
			__IO  uint8_t  RSVD_7:2;
			__IO  uint8_t  PIN_8_SEL:6;
			__IO  uint8_t  RSVD_8:2;
			__IO  uint8_t  PIN_9_SEL:6;
			__IO  uint8_t  RSVD_9:2;
			__IO  uint8_t  PIN_10_SEL:6;
			__IO  uint8_t  RSVD_10:2;
			__IO  uint8_t  PIN_11_SEL:6;
			__IO  uint8_t  RSVD_11:2;
			__IO  uint8_t  PIN_12_SEL:6;
			__IO  uint8_t  RSVD_12:2;
			__IO  uint8_t  PIN_13_SEL:6;
			__IO  uint8_t  RSVD_13:2;
			__IO  uint8_t  PIN_14_SEL:6;
			__IO  uint8_t  RSVD_14:2;
			__IO  uint8_t  PIN_15_SEL:6;
			__IO  uint8_t  RSVD_15:2;
			__IO  uint8_t  PIN_16_SEL:6;
			__IO  uint8_t  RSVD_16:2;
			__IO  uint8_t  PIN_17_SEL:6;
			__IO  uint8_t  RSVD_17:2;
			__IO  uint8_t  PIN_18_SEL:6;
			__IO  uint8_t  RSVD_18:2;
			__IO  uint8_t  PIN_19_SEL:6;
			__IO  uint8_t  RSVD_19:2;
			__IO  uint8_t  PIN_20_SEL:6;
			__IO  uint8_t  RSVD_20:2;
			__IO  uint8_t  PIN_21_SEL:6;
			__IO  uint8_t  RSVD_21:2;
			__IO  uint8_t  PIN_22_SEL:6;
			__IO  uint8_t  RSVD_22:2;
			__IO  uint8_t  PIN_23_SEL:6;
			__IO  uint8_t  RSVD_23:2;
			__IO  uint8_t  PIN_24_SEL:6;
			__IO  uint8_t  RSVD_24:2;
			__IO  uint8_t  PIN_25_SEL:6;
			__IO  uint8_t  RSVD_25:2;
			__IO  uint8_t  PIN_26_SEL:6;
			__IO  uint8_t  RSVD_26:2;
			__IO  uint8_t  PIN_27_SEL:6;
			__IO  uint8_t  RSVD_27:2;
			__IO  uint8_t  PIN_28_SEL:6;
			__IO  uint8_t  RSVD_28:2;
			__IO  uint8_t  PIN_29_SEL:6;
			__IO  uint8_t  RSVD_29:2;
			__IO  uint8_t  PIN_30_SEL:6;
			__IO  uint8_t  RSVD_30:2;
			__IO  uint8_t  PIN_31_SEL:6;
			__IO  uint8_t  RSVD_31:2;
#if 1
			/* PAD和PIN没有一一对应 QFN48/QFN32*/
			/* 0x20 */	
			__IO  uint8_t  PAD_0_INPUT_PULL_UP:1;
			__IO  uint8_t  PAD_1_INPUT_PULL_UP:1;
			__IO  uint8_t  PAD_2_INPUT_PULL_UP:1;
			__IO  uint8_t  PAD_3_INPUT_PULL_UP:1;
			__IO  uint8_t  PAD_4_INPUT_PULL_UP:1;
			__IO  uint8_t  PAD_5_INPUT_PULL_UP:1;
			__IO  uint8_t  PAD_6_INPUT_PULL_UP:1;
			__IO  uint8_t  PAD_7_INPUT_PULL_UP:1;
			/* 0x21 */	
			__IO  uint8_t  PAD_8_INPUT_PULL_UP:1;
			__IO  uint8_t  PAD_9_INPUT_PULL_UP:1;
			__IO  uint8_t  PAD_10_INPUT_PULL_UP:1;
			__IO  uint8_t  PAD_11_INPUT_PULL_UP:1;
			__IO  uint8_t  PAD_12_INPUT_PULL_UP:1;
			__IO  uint8_t  PAD_13_INPUT_PULL_UP:1;
			__IO  uint8_t  PAD_14_INPUT_PULL_UP:1;
			__IO  uint8_t  PAD_15_INPUT_PULL_UP:1;
			/* 0x22 */	
			__IO  uint8_t  PAD_16_INPUT_PULL_UP:1;
			__IO  uint8_t  PAD_17_INPUT_PULL_UP:1;
			__IO  uint8_t  PAD_18_INPUT_PULL_UP:1;
			__IO  uint8_t  PAD_19_INPUT_PULL_UP:1;
			__IO  uint8_t  PAD_20_INPUT_PULL_UP:1;
			__IO  uint8_t  PAD_21_INPUT_PULL_UP:1;
			__IO  uint8_t  PAD_22_INPUT_PULL_UP:1;
			__IO  uint8_t  PAD_23_INPUT_PULL_UP:1;
			/* 0x23 */
			__IO  uint8_t  PAD_24_INPUT_PULL_UP:1;
			__IO  uint8_t  PAD_25_INPUT_PULL_UP:1;
			__IO  uint8_t  PAD_26_INPUT_PULL_UP:1;
			__IO  uint8_t  PAD_27_INPUT_PULL_UP:1;
			__IO  uint8_t  PAD_28_INPUT_PULL_UP:1;
			__IO  uint8_t  PAD_29_INPUT_PULL_UP:1;
			__IO  uint8_t  PAD_30_INPUT_PULL_UP:1;
			__IO  uint8_t  PAD_31_INPUT_PULL_UP:1;
			/* 0x24 */	
			__IO  uint8_t  PAD_32_INPUT_PULL_UP:1;
			__IO  uint8_t  PAD_33_INPUT_PULL_UP:1;
			__IO  uint8_t  PAD_34_INPUT_PULL_UP:1;
			__IO  uint8_t  PAD_35_INPUT_PULL_UP:1;
			__IO  uint8_t  PAD_36_INPUT_PULL_UP:1;
			__IO  uint8_t  PAD_37_INPUT_PULL_UP:1;
			__IO  uint8_t  PAD_38_INPUT_PULL_UP:1;
			__IO  uint8_t  PAD_39INPUT_PULL_UP:1;
			/* 0x25 ~ 0x27 */	
			__IO  uint8_t  RSVD03[3];
#endif
#if 1
			/* PAD和PIN_DRV没有一一对应 QFN48*/
			/* 0x28 */	
			__IO  uint8_t  PAD_0_OUTPUT_DRV:1;
			__IO  uint8_t  PAD_1_OUTPUT_DRV:1;
			__IO  uint8_t  PAD_2_OUTPUT_DRV:1;
			__IO  uint8_t  PAD_3_OUTPUT_DRV:1;
			__IO  uint8_t  PAD_4_OUTPUT_DRV:1;
			__IO  uint8_t  PAD_5_OUTPUT_DRV:1;
			__IO  uint8_t  PAD_6_OUTPUT_DRV:1;
			__IO  uint8_t  PAD_7_OUTPUT_DRV:1;
			/* 0x29 */	
			__IO  uint8_t  PAD_8_OUTPUT_DRV:1;
			__IO  uint8_t  PAD_9_OUTPUT_DRV:1;
			__IO  uint8_t  PAD_10_OUTPUT_DRV:1;
			__IO  uint8_t  PAD_11_OUTPUT_DRV:1;
			__IO  uint8_t  PAD_12_OUTPUT_DRV:1;
			__IO  uint8_t  PAD_13_OUTPUT_DRV:1;
			__IO  uint8_t  PAD_14_OUTPUT_DRV:1;
			__IO  uint8_t  PAD_15_OUTPUT_DRV:1;
			/* 0x2a */	
			__IO  uint8_t  PAD_16_OUTPUT_DRV:1;
			__IO  uint8_t  PAD_17_OUTPUT_DRV:1;
			__IO  uint8_t  PAD_18_OUTPUT_DRV:1;
			__IO  uint8_t  PAD_19_OUTPUT_DRV:1;
			__IO  uint8_t  PAD_20_OUTPUT_DRV:1;
			__IO  uint8_t  PAD_21_OUTPUT_DRV:1;
			__IO  uint8_t  PAD_22_OUTPUT_DRV:1;
			__IO  uint8_t  PAD_23_OUTPUT_DRV:1;
			/* 0x2b */
			__IO  uint8_t  PAD_24_OUTPUT_DRV:1;
			__IO  uint8_t  PAD_25_OUTPUT_DRV:1;
			__IO  uint8_t  PAD_26_OUTPUT_DRV:1;
			__IO  uint8_t  PAD_27_OUTPUT_DRV:1;
			__IO  uint8_t  PAD_28_OUTPUT_DRV:1;
			__IO  uint8_t  PAD_29_OUTPUT_DRV:1;
			__IO  uint8_t  PAD_30_OUTPUT_DRV:1;
			__IO  uint8_t  PAD_31_OUTPUT_DRV:1;
			/* 0x2c */	
			__IO  uint8_t  PAD_32_OUTPUT_DRV:1;
			__IO  uint8_t  PAD_33_OUTPUT_DRV:1;
			__IO  uint8_t  PAD_34_OUTPUT_DRV:1;
			__IO  uint8_t  PAD_35_OUTPUT_DRV:1;
			__IO  uint8_t  PAD_36_OUTPUT_DRV:1;
			__IO  uint8_t  PAD_37_OUTPUT_DRV:1;
			__IO  uint8_t  PAD_38_OUTPUT_DRV:1;
			__IO  uint8_t  PAD_39_OUTPUT_DRV:1;
			/* 0x2d ~ 0x2f */	
			__IO  uint8_t  RSVD04[3];
#endif
	};
	struct
	{
			/* 0x00~0x1F */
			__IO  uint8_t  PINSEL[32];
			/* 0x20 ~ 0x24 */	
			__IO  uint8_t  PAD_INPUT_PULL_UP[5];
			/* 0x25 ~ 0x27 */	
			__IO  uint8_t  RSVD05[3];
			/* 0x28~0x2c */
			__IO  uint8_t  PAD_OUTPUT_DRV[5];
			/* 0x2d ~ 0x2f */
			__IO  uint8_t  RSVD06[3];
	};
} PIN_CONFIG_TYPE;
/* ============================ GPIO ========================= */
typedef union{
	struct {	
			/* GPIO Direction select */
			/* 0x00 */	
			__IO  uint8_t  GPIO_0_DIR:1;
			__IO  uint8_t  GPIO_1_DIR:1;
			__IO  uint8_t  GPIO_2_DIR:1;
			__IO  uint8_t  GPIO_3_DIR:1;
			__IO  uint8_t  GPIO_4_DIR:1;
			__IO  uint8_t  GPIO_5_DIR:1;
			__IO  uint8_t  GPIO_6_DIR:1;
			__IO  uint8_t  GPIO_7_DIR:1;
			/* 0x01 */	
			__IO  uint8_t  GPIO_8_DIR:1;
			__IO  uint8_t  GPIO_9_DIR:1;
			__IO  uint8_t  GPIO_10_DIR:1;
			__IO  uint8_t  GPIO_11_DIR:1;
			__IO  uint8_t  GPIO_12_DIR:1;
			__IO  uint8_t  GPIO_13_DIR:1;
			__IO  uint8_t  GPIO_14_DIR:1;
			__IO  uint8_t  GPIO_15_DIR:1;
			/* 0x02 */	
			__IO  uint8_t  GPIO_16_DIR:1;
			__IO  uint8_t  GPIO_17_DIR:1;
			__IO  uint8_t  GPIO_18_DIR:1;
			__IO  uint8_t  GPIO_19_DIR:1;
			__IO  uint8_t  GPIO_20_DIR:1;
			__IO  uint8_t  GPIO_21_DIR:1;
			__IO  uint8_t  GPIO_22_DIR:1;
			__IO  uint8_t  GPIO_23_DIR:1;
			/* 0x03 */	
			__IO  uint8_t  GPIO_24_DIR:1;
			__IO  uint8_t  GPIO_25_DIR:1;
			__IO  uint8_t  GPIO_26_DIR:1;
			__IO  uint8_t  GPIO_27_DIR:1;
			__IO  uint8_t  GPIO_28_DIR:1;
			__IO  uint8_t  GPIO_29_DIR:1;
			__IO  uint8_t  GPIO_30_DIR:1;
			__IO  uint8_t  GPIO_31_DIR:1;
	};
	__IO  uint32_t  GPIODIR;
} GPIO_CTRL_TYPE;

typedef union{
	struct {
			/* Input Enable*/
			/* 0x00 */	
			__IO  uint8_t  GPI_0_InE:1;
			__IO  uint8_t  GPI_1_InE:1;
			__IO  uint8_t  GPI_2_InE:1;
			__IO  uint8_t  GPI_3_InE:1;
			__IO  uint8_t  GPI_4_InE:1;
			__IO  uint8_t  GPI_5_InE:1;
			__IO  uint8_t  GPI_6_InE:1;
			__IO  uint8_t  GPI_7_InE:1;
			/* 0x01 */	
			__IO  uint8_t  GPI_8_InE:1;
			__IO  uint8_t  GPI_9_InE:1;
			__IO  uint8_t  GPI_10_InE:1;
			__IO  uint8_t  GPI_11_InE:1;
			__IO  uint8_t  GPI_12_InE:1;
			__IO  uint8_t  GPI_13_InE:1;
			__IO  uint8_t  GPI_14_InE:1;
			__IO  uint8_t  GPI_15_InE:1;
			/* 0x02 */	
			__IO  uint8_t  GPI_16_InE:1;
			__IO  uint8_t  GPI_17_InE:1;
			__IO  uint8_t  GPI_18_InE:1;
			__IO  uint8_t  GPI_19_InE:1;
			__IO  uint8_t  GPI_20_InE:1;
			__IO  uint8_t  GPI_21_InE:1;
			__IO  uint8_t  GPI_22_InE:1;
			__IO  uint8_t  GPI_23_InE:1;
			/* 0x03 */	
			__IO  uint8_t  GPI_24_InE:1;
			__IO  uint8_t  GPI_25_InE:1;
			__IO  uint8_t  GPI_26_InE:1;
			__IO  uint8_t  GPI_27_InE:1;
			__IO  uint8_t  GPI_28_InE:1;
			__IO  uint8_t  GPI_29_InE:1;
			__IO  uint8_t  GPI_30_InE:1;
			__IO  uint8_t  GPI_31_InE:1;
	
			/* GPIO input value */
			/* 0x04  */	
			__IO  uint8_t  GPI_0:1;
			__IO  uint8_t  GPI_1:1;
			__IO  uint8_t  GPI_2:1;
			__IO  uint8_t  GPI_3:1;
			__IO  uint8_t  GPI_4:1;
			__IO  uint8_t  GPI_5:1;
			__IO  uint8_t  GPI_6:1;
			__IO  uint8_t  GPI_7:1;
			/* 0x05 */
			__IO  uint8_t  GPI_8:1;
			__IO  uint8_t  GPI_9:1;
			__IO  uint8_t  GPI_10:1;
			__IO  uint8_t  GPI_11:1;
			__IO  uint8_t  GPI_12:1;
			__IO  uint8_t  GPI_13:1;
			__IO  uint8_t  GPI_14:1;
			__IO  uint8_t  GPI_15:1;
			/* 0x06 */	
			__IO  uint8_t  GPI_16:1;
			__IO  uint8_t  GPI_17:1;
			__IO  uint8_t  GPI_18:1;
			__IO  uint8_t  GPI_19:1;
			__IO  uint8_t  GPI_20:1;
			__IO  uint8_t  GPI_21:1;
			__IO  uint8_t  GPI_22:1;
			__IO  uint8_t  GPI_23:1;
			/* 0x07 */	
			__IO  uint8_t  GPI_24:1;
			__IO  uint8_t  GPI_25:1;
			__IO  uint8_t  GPI_26:1;
			__IO  uint8_t  GPI_27:1;
			__IO  uint8_t  GPI_28:1;
			__IO  uint8_t  GPI_29:1;
			__IO  uint8_t  GPI_30:1;
			__IO  uint8_t  GPI_31:1;

			/* GPIO input value invert */
			/* 0x08 */	
			__IO  uint8_t  GPI_0_POL:1;
			__IO  uint8_t  GPI_1_POL:1;
			__IO  uint8_t  GPI_2_POL:1;
			__IO  uint8_t  GPI_3_POL:1;
			__IO  uint8_t  GPI_4_POL:1;
			__IO  uint8_t  GPI_5_POL:1;
			__IO  uint8_t  GPI_6_POL:1;
			__IO  uint8_t  GPI_7_POL:1;
			/* 0x09 */	
			__IO  uint8_t  GPI_8_POL:1;
			__IO  uint8_t  GPI_9_POL:1;
			__IO  uint8_t  GPI_10_POL:1;
			__IO  uint8_t  GPI_11_POL:1;
			__IO  uint8_t  GPI_12_POL:1;
			__IO  uint8_t  GPI_13_POL:1;
			__IO  uint8_t  GPI_14_POL:1;
			__IO  uint8_t  GPI_15_POL:1;
			/* 0x0a */	
			__IO  uint8_t  GPI_16_POL:1;
			__IO  uint8_t  GPI_17_POL:1;
			__IO  uint8_t  GPI_18_POL:1;
			__IO  uint8_t  GPI_19_POL:1;
			__IO  uint8_t  GPI_20_POL:1;
			__IO  uint8_t  GPI_21_POL:1;
			__IO  uint8_t  GPI_22_POL:1;
			__IO  uint8_t  GPI_23_POL:1;
			/* 0x0b */	
			__IO  uint8_t  GPI_24_POL:1;
			__IO  uint8_t  GPI_25_POL:1;
			__IO  uint8_t  GPI_26_POL:1;
			__IO  uint8_t  GPI_27_POL:1;
			__IO  uint8_t  GPI_28_POL:1;
			__IO  uint8_t  GPI_29_POL:1;
			__IO  uint8_t  GPI_30_POL:1;
			__IO  uint8_t  GPI_31_POL:1;
	};
	struct {
			__IO  uint32_t  GPI_InE;	//Input Enable
			__I  uint32_t  GPI;			//Input value
			__IO  uint32_t  GPI_POL;	//Input Invert
	};
} GPI_CTRL_TYPE;

typedef union{
	struct {
			/* 0x00  */	
			__IO  uint8_t  GPO_0:1;
			__IO  uint8_t  GPO_1:1;
			__IO  uint8_t  GPO_2:1;
			__IO  uint8_t  GPO_3:1;
			__IO  uint8_t  GPO_4:1;
			__IO  uint8_t  GPO_5:1;
			__IO  uint8_t  GPO_6:1;
			__IO  uint8_t  GPO_7:1;
			/* 0x01 */	
			__IO  uint8_t  GPO_8:1;
			__IO  uint8_t  GPO_9:1;
			__IO  uint8_t  GPO_10:1;
			__IO  uint8_t  GPO_11:1;
			__IO  uint8_t  GPO_12:1;
			__IO  uint8_t  GPO_13:1;
			__IO  uint8_t  GPO_14:1;
			__IO  uint8_t  GPO_15:1;
			/* 0x02 */	
			__IO  uint8_t  GPO_16:1;
			__IO  uint8_t  GPO_17:1;
			__IO  uint8_t  GPO_18:1;
			__IO  uint8_t  GPO_19:1;
			__IO  uint8_t  GPO_20:1;
			__IO  uint8_t  GPO_21:1;
			__IO  uint8_t  GPO_22:1;
			__IO  uint8_t  GPO_23:1;
			/* 0x03 */	
			__IO  uint8_t  GPO_24:1;
			__IO  uint8_t  GPO_25:1;
			__IO  uint8_t  GPO_26:1;
			__IO  uint8_t  GPO_27:1;
			__IO  uint8_t  GPO_28:1;
			__IO  uint8_t  GPO_29:1;
			__IO  uint8_t  GPO_30:1;
			__IO  uint8_t  GPO_31:1;
	};
	__IO  uint32_t  GPO;
} GPO_CTRL_TYPE;

typedef struct {
	/* 0x10 ~0x13 */
	__IO  uint32_t  GPIO_INT_CLR;
	/* 0x14 ~ 0x1F*/
	__IO  uint8_t  RSVD14[12];
	/* 0x20 ~0x23 */
	__IO  uint32_t  GPIO_INT_MSK;
	/* 0x24 ~ 0x27*/
	__IO  uint8_t  RSVD24[4];
	/* 0x28 ~0x2B */
	__IO  uint32_t  GPIO_INT;
	/* 0x2C ~ 0x2F*/
	__IO  uint8_t  RSVD2C[4];
	/* 0x30 */
	__IO  uint8_t  GPIO_TOP_INT_MSK:1;   //全局中断屏蔽寄存器
	__IO  uint8_t  RSVD30:7;
} GPIO_IRQ_CTRL_TYPE;

/* ============================ UART =========================== */
typedef struct {
	__IO  uint8_t  BAUDSEL:4;
	__IO  uint8_t  RI:1;
	__IO  uint8_t  TI:1;
	__IO  uint8_t  RX_INT_MASK:1;
	__IO  uint8_t  FLOW_EN:1;

	__IO  uint8_t  TX_DATA;			/* Tx data*/

	__IO  uint8_t  CLK_SEL:1;		/* 1=32M, 0=16M */
	__IO  uint8_t  PAR_FAIL:1;  	/* Parity fail flag*/
	__IO  uint8_t  PAR_FAIL_INT_MASK:1; /* 1=MASK */
	__IO  uint8_t  UART_EN:1;		
	__IO  uint8_t  par_rx_en:1;		/* Rx Parity check enable */
	__IO  uint8_t  par_rx_even:1;	/* 1=Even, 0=Odd */
	__IO  uint8_t  par_tx_en:1;		/* Tx Parity check enable */
	__IO  uint8_t  par_tx_even:1;	/* 1=Even, 0=Odd */

	__IO  uint8_t  RX_FIFO_EMPTY:1;
	__IO  uint8_t  RX_FIFO_FULL:1;
	__IO  uint8_t  RSVD0:2;
	__IO  uint8_t  TX_INT_MASK:1;	/* 1=Even, 0=Odd */
	__IO  uint8_t  RX_FLUSH:1;		/* clr rx fifo and set RX_FIFO_EMPTY */
	__IO  uint8_t  RSVD1:2;

	__IO  uint8_t  RX_DATA;			/* Rx data*/
} UART_CTRL_TYPE;

/* ============================ I2C =========================== */
typedef struct {
	/* 0x00 - 0x03  */	
	__IO  uint16_t ADDRESS;   	//slave access address low byte and HIGH byte
	__IO  uint8_t  RSVD0:1;
	__IO  uint8_t  ID:7;		//slave device address - 7bit
	__IO  uint8_t  SPEED;		//cann't set to 0
	/* 0x04 - 0x07  */	
	__IO  uint8_t  BUSY:1;
	__IO  uint8_t  RSVD1:1;
	__IO  uint8_t  ERR_FLG:1;
	__IO  uint8_t  DONE_FLG:1;	//current operation complete,clr READ AND WRITE
	__IO  uint8_t  READ:1;		//volatile,automatically clear
	__IO  uint8_t  WRITE:1;		//volatile,automatically clear
	__IO  uint8_t  ADDR_1:1;    //slave access address 1 byte mode. 1:1 byte EEPROM address 0:2 byte EEPROM address
	__IO  uint8_t  RSTB:1;      //software reset,don't clr reg 
	__IO  uint8_t  DATA_CNT:5;  //The number of byte to be read/write."0" means read/write 1 byte; "1" means read/write 2 byte;
	__IO  uint8_t  SLAVE_NACK:1;//[default:1]:slave respond with NACK； 0：slave respond with ACK
	__IO  uint8_t  RSVD2:1;
	__IO  uint8_t  CURR_ADDR:1; //1:read at current addr //0: read at random address 
	__IO  uint16_t RSVD3;
} I2C_CTRL_TYPE;

typedef struct {
	__IO  uint8_t  TX[32];
} I2C_TXD_TYPE;

typedef struct {
	__IO  uint8_t  RX[32];
} I2C_RXD_TYPE;
/* ============================ TIMER =========================== */
typedef struct
{
	/* 0x00~0x2F */
	__IO  uint8_t  RSVD00[48];
	/* 0x30 */
	__IO  uint8_t  TIMER_0_EN:1;
	__IO  uint8_t  TIMER_1_EN:1;
	__IO  uint8_t  TIMER_2_EN:1;
	__IO  uint8_t  TIMER_3_EN:1;
	__IO  uint8_t  TIMER_0_RGLR:1;	//reload enable
	__IO  uint8_t  TIMER_1_RGLR:1;
	__IO  uint8_t  TIMER_2_RGLR:1;
	__IO  uint8_t  TIMER_3_RGLR:1;
	/* 0x31 */
	__IO  uint8_t  TIMER_0_INT_CLR:1;
	__IO  uint8_t  TIMER_1_INT_CLR:1;
	__IO  uint8_t  TIMER_2_INT_CLR:1;
	__IO  uint8_t  TIMER_3_INT_CLR:1;
	__IO  uint8_t  RSVD31:4;
	/* 0x32 */
	__IO  uint8_t  TIMER_0_INT_MASK:1;	//Don't mask TIMER_0_INT_STATUS
	__IO  uint8_t  TIMER_1_INT_MASK:1;	//Don't mask TIMER_1_INT_STATUS
	__IO  uint8_t  TIMER_2_INT_MASK:1;	//Don't mask TIMER_2_INT_STATUS
	__IO  uint8_t  TIMER_3_INT_MASK:1;	//Don't mask TIMER_3_INT_STATUS
	__IO  uint8_t  RSVD32:4;
	/* 0x33 */
	__IO  uint8_t  TIMER_0_INT_STATUS:1;
	__IO  uint8_t  TIMER_1_INT_STATUS:1;
	__IO  uint8_t  TIMER_2_INT_STATUS:1;
	__IO  uint8_t  TIMER_3_INT_STATUS:1;
	__IO  uint8_t  RSVD33:4;		
	/* 0x34~0x37 */
	__IO  uint32_t  TIMER_0_VAL;
	/* 0x38~0x3b */
	__IO  uint32_t  TIMER_1_VAL;
	/* 0x3C~0x3F */
	__IO  uint32_t  TIMER_2_VAL;
	/* 0x40~0x43 */
	__IO  uint32_t  TIMER_3_VAL;
	/* 0x44~0x47 */
	__IO  uint32_t  TIMER_0_CNT;
	/* 0x48~0x4b */
	__IO  uint32_t  TIMER_1_CNT;
	/* 0x4C~0x4F */
	__IO  uint32_t  TIMER_2_CNT;
	/* 0x50~0x53 */
	__IO  uint32_t  TIMER_3_CNT;
} TIMER_CTRL_TYPE;
/* ============================ H_TIMER =========================== */
typedef struct
{
	/* 0x00~0x03 */
	__IO  uint32_t  START:1;	//1:start timer, the timer will stop after the current timing period
	__IO  uint32_t  RSVD00:31;
	/* 0x04~0x07 */
	__IO  uint32_t  STOP:1;		//1:stop timer, the timer will stop after the current timing period
	__IO  uint32_t  RSVD01:31;
	/* 0x08~0x0B */
	__IO  uint8_t  ONE_TIME:1;	//1:single mode, 0:repeat mode until STOP equals to 1
	__IO  uint8_t  DIRECTION:2;	//count direction: 0-up, 1-down, 2-up and down, 3-reserved
	__IO  uint8_t  INTEN:2;		//Int Enable
	__IO  uint8_t  PRESCALER:3;	//Counter clk = hclk/(2^prescaler),default value :0
	__IO  uint8_t  RSVD02[3];
	/* 0x0C~0x0F */
	__IO  uint16_t  COUNTER_TOP;//The max value of counter
	__IO  uint16_t  RSVD03;
	/* 0x10~0x13 */
	__I  uint16_t   COUNTER;
	__I  uint8_t    RSVD04;
	__I  uint8_t    BUSY:1;
	__I  uint8_t    RSVD05:7;
	/* 0x14~0x17 */
	__IO  uint32_t  EVENTS:2;	//bit0 - if the timing period finished ; bit1 - if the task stop finished
	__IO  uint32_t  RSVD06:30;
} H_TIMER_CTRL_TYPE;

/* ============================ PWM =========================== */
typedef struct
{
	/* 0x00*/
	__IO  uint8_t  T1;
	/* 0x01*/
	__IO  uint8_t  T2;
	/* 0x02 ~ 0x03*/
	__IO  uint16_t  T3;
	/* 0x04*/
	__IO  uint8_t  N1;
	/* 0x05*/
	__IO  uint8_t  N2;
	/* 0x06*/
	__IO  uint8_t  T4;
	/* 0x07*/
	__IO  uint8_t  BR_TH_MAX;
	/* 0x08 */
	__IO  uint8_t  BR_TH_MIN;
	/* 0x09 */
	__IO  uint8_t  PWM_M;	
	/* 0x0A */
	__IO  uint8_t  BR_SP:4;
	__IO  uint8_t  MODE:2;
	__IO  uint8_t  PAUS:1;
	__IO  uint8_t  PE:1;
	/* 0x0B */
	__IO  uint8_t  PWM_N;	
} PWM_CTRL_TYPE;
/* ============================ Battery detect  =========================== */
typedef struct
{
	/* 0x00*/
	__IO  uint8_t  GPADC_CHSEL:2;
	__IO  uint8_t  RSVD00:4;
	__IO  uint8_t  GPADC_DONE:1;
	__IO  uint8_t  GPADC_EN:1;
	/* 0x01*/
	__IO  uint8_t  RSVD01;
	/* 0x02 ~ 0x03*/
	__IO  uint16_t  GPADC_DATA;
}BI_CTRL_TYPE;
/* ============================ WDT  =========================== */
typedef struct
{
	/* 0x00*/
	__IO  uint8_t  WDT_EN:1;
	__IO  uint8_t  WDT_CLR:1;
	__IO  uint8_t  RSVD00:6;
	/* 0x01 ~ 0x02*/
	__IO  uint16_t WDT_TIME;
	/* 0x03 */
	__IO  uint8_t  RSVD01;
}WDT_CTRL_TYPE;
/* ============================ eFuse =========================== */
typedef struct {
	/* 0x00 */
	__IO  uint8_t  RSVD00:4;
	__IO  uint8_t  READ:1;
	__IO  uint8_t  WRITE:1;
	__IO  uint8_t  DONE:1;
	__IO  uint8_t  PE:1;
	/* 0x01 */
	__IO  uint8_t  ADDR:4;
	__IO  uint8_t  RSVD01:4;
	/* 0x02 */
	__IO  uint8_t  WDATA;
	/* 0x03 */
	__IO  uint8_t  RDATA;	
} EFUSE_CTRL_TYPE;

/* ============================ RF Control =========================== */
typedef struct
{
	/* 0x18 */
	__IO  uint8_t  RF_ADDR;
	/* 0x19 */
	__IO  uint8_t  RF_WDATA;
	/* 0x1A */
	__IO  uint8_t  RF_RDY:1;
	__IO  uint8_t  RSVD1A:7;
	/* 0x1B */
	__IO  uint8_t  RSVD1B;
	/* 0x1C */
	__IO  uint8_t  RF_RDATA;	
}RF_CTRL_TYPE;
/* ============================ Power Manager =========================== */
typedef struct
{
/* 0x00~0x03 */
__IO uint8_t RSVD00[4];
/* 0x04 */
__IO uint8_t PRAM_SEL:4;
__IO uint8_t DRAM_SEL:4;
/* 0x05 */
__IO uint8_t PWR_WAIT_SLP:6;
__IO uint8_t RSVD05:2;
/* 0x06 ~ 0x0B*/
__IO uint8_t RSVD06[6];
/* 0x0C */
__IO uint8_t MCU_SLEEP:1;
__IO uint8_t RSVD0C:7;
/* 0x0D */
__IO uint8_t UART_EN:1;
__IO uint8_t RSVD0D:7;
/* 0x0E */
__IO uint8_t RSVD0E;
/* 0x0F */
__IO uint8_t DSLP_WAKE_EN:1;
__IO uint8_t RSVD0F0:3;
__IO uint8_t TMR_WAKE_EN:1;
__IO uint8_t PIN_WAKE_EN:1;
__IO uint8_t RSVD0F1:2;
/* 0x10 ~ 0x1F */
__IO uint8_t RSVD10[16];
/* 0x20 */
__IO uint8_t RFMODE_MCU:3;
__IO uint8_t RSVD200:1;
__IO uint8_t RFMODE_MANUAL:1;
__IO uint8_t RSVD201:3;
/* 0x21 ~ 0x23*/
__IO uint8_t RSVD21[3];
/* 0x24 */
__IO uint8_t FSM_SLEEP_EN:1;
__IO uint8_t RSVD24:7;
/* 0x25 */
__IO uint8_t DSLP_SYS:1;
__IO uint8_t RSVD25:7;
/* 0x26 ~ 0x27*/
__IO uint8_t RSVD26[2];
/* 0x28~0x2B */
__IO uint32_t WAKE_PIN_EN;
/* 0x2C~0x2F */
__IO uint32_t WAKE_PIN_UART_EN;
/* 0x30~0x4F */
__IO uint8_t RSVD30[32];
/* 0x50 */
__IO uint8_t FLASH_LDO_ENB:1;
__IO uint8_t RSVD50:7;
/* 0x51~0x56 */
__IO uint8_t RSVD51[6];
/* 0x57 */
__IO uint8_t MBIST_STOP:1;
__IO uint8_t RSVD57:7;
/* 0x58 */
__IO uint8_t RSVD58;
/* 0x59 */
__IO uint8_t ROM_ALWAYS_ON:1;
__IO uint8_t MEM_ISO_SLEEP:1;
__IO uint8_t ALL_XTAL_MODE:1;
__IO uint8_t RSVD59:5;
/* 0x5A~0x5B */
__IO uint8_t RSVD5A[2];
/* 0x5C~0x5F */
__IO uint32_t GPIO_POL;
/* 0x60~0x63 */
__IO uint8_t RSVD60[4];
/* 0x64 */
__IO uint8_t MCU_CLOCK_SEL:2;
__IO uint8_t RSVD64:6;
/* 0x65 */
__IO uint8_t MCU_CLOCK_SW:1;
__IO uint8_t RSVD65:7;
/* 0x66 */
__IO uint8_t RFMODE_RST:1;
__IO uint8_t RSVD66:7;
} POWER_CTRL_TYPE;
/* ============================ SPI Master=========================== */
typedef struct {
	__IO  uint8_t  SPEED:3;
	__IO  uint8_t  MSB:1;	
	__IO  uint8_t  RSVD04:1;	
	__IO  uint8_t  DONE:1;	
	__IO  uint8_t  START:1;	
	__IO  uint8_t  PE:1;	
	__IO  uint8_t  OUT;	
	__IO  uint8_t  IN;	

} SPI_CTRL_TYPE;

/* ==========================  MISC ============================ */
typedef struct {
	/* 0x00 ~ 0x0B */	
	__IO  uint8_t  RSVD00[12];
	/* 0x0C ~0x0F */
	__IO  uint32_t  GPIO;
	/* 0x10 ~0x13 */
	__IO  uint32_t  GPIO_INT_CLR;
	/* 0x14 */
	__IO  uint8_t  RSVD14;
	/* 0x15 */
	__IO  uint8_t  EXT_INT_CLR;
	/* 0x16 ~ 0x17 */	
	__IO  uint8_t  RSVD16[2];
	/* 0x18 */
	__IO  uint8_t  RF_ADDR;
	/* 0x19 */
	__IO  uint8_t  RF_WDATA;
	/* 0x1A */
	__IO  uint8_t  RF_RDY:1;
	__IO  uint8_t  RSVD1A:7;
	/* 0x1B */
	__IO  uint8_t  RSVD1B;
	/* 0x1C */
	__IO  uint8_t  RF_RDATA;
	/* 0x1D ~ 0x1F */	
	__IO  uint8_t  RSVD1D[3];
	/* 0x20 ~0x23 */
	__IO  uint32_t  GPIO_INT_MSK;
	/* 0x24 */
	__IO  uint8_t  RSVD24;
	/* 0x25 */
	__IO  uint8_t  EXT_INT_MSK;
	/* 0x26 ~0x27 */
	__IO  uint16_t  HID_INT7_MSK:10;
	__IO  uint16_t  RSVD26:6;
	/* 0x28 ~0x2B */
	__IO  uint32_t  GPIO_INT;	
	/* 0x2C */
	__IO  uint8_t  RSVD2C;
	/* 0x2D */
	__IO  uint8_t  EXT_INT;
	/* 0x2E ~ 0x2F */	
	__IO  uint8_t  RSVD2E[2];
	/* 0x30 */
	__IO  uint8_t  GPIO_TOP_INT_MSK:1;
	__IO  uint8_t  TIMER_TOP_INT_MSK:1;
	__IO  uint8_t  HID_TOP_INT_MSK:1;
	__IO  uint8_t  RSVD30:5;
	/* 0x31 */
	__IO  uint8_t  GPIO_TOP_INT1:1;
	__IO  uint8_t  GPIO_TOP_INT2:1;
	__IO  uint8_t  RSVD310:1;
	__IO  uint8_t  RSVD311:1;
	__IO  uint8_t  LLC_INT:1;
	__IO  uint8_t  EXT_TOP_INT:1;
	__IO  uint8_t  HID_TOP_INT:1;
	__IO  uint8_t  GPIO_TOP_INT:1;
	/* 0x32 ~ 0x33 */	
	__IO  uint8_t  RSVD32[2];
	/* 0x34 ~0x37 */
	__IO  uint32_t  RSVD34;
	/* 0x38 ~0x3B */
	__IO  uint32_t  RSVD38;
	/* 0x3C ~ 0x3F */	
	__IO  uint8_t  RSVD3C[4];	
	/* 0x40 */
	__IO  uint8_t  BTN_INIT:1;
	__IO  uint8_t  BTN_TRIG:1;
	__IO  uint8_t  R_ZBTN_DIV:2;
	__IO  uint8_t  R_TRANSDELAY:1;
	__IO  uint8_t  R_write_pol:1;
	__IO  uint8_t  RSVD40:2;
	/* 0x41 */
	__IO  uint8_t  R_TW_RPTIME;
	/* 0x42 */
	__IO  uint8_t  BTN_CPI:1;
	__IO  uint8_t  BTN_L:1;
	__IO  uint8_t  BTN_R:1;
	__IO  uint8_t  BTN_M:1;
	__IO  uint8_t  BTN_4:1;
	__IO  uint8_t  BTN_5:1;
	__IO  uint8_t  BTN_TW1:1;
	__IO  uint8_t  BTN_TW2:1;
	/* 0x43 */
	__IO  uint8_t  BTN_Z:1;
	__IO  uint8_t  RSVD43:7;
	/* 0x44 */
	__IO  uint8_t  R_CPOL:1;
	__IO  uint8_t  R_CPHA:1;
	__IO  uint8_t  R_CS_TEST:1;
	__IO  uint8_t  SPI_RESYNC:1;
	__IO  uint8_t  R_SPI_A2D_TH:3;
	__IO  uint8_t  RSVD44:1;
	/* 0x45 */
	__IO  uint8_t  SS_BURST_READ:1;
	__IO  uint8_t  RSVD450:3;
	__IO  uint8_t  SS_BURST_NUM:3;
	__IO  uint8_t  RSVD451:1;
	/* 0x46 ~ 0x4B */
	__IO  uint8_t  SS_ADDR[6];
	/* 0x4C ~ 0x51 */
	__IO  uint8_t  SS_DATA[6];
	/* 0x52 ~ 0x53 */
	__IO  uint8_t  RSVD52[2];
	/* 0x54 ~ 0x57 */
	__IO  uint32_t  GPIODEB;
	/* 0x58 ~ 0x5B */
	__IO  uint32_t  GPIODIR;
	/* 0x5C ~ 0x5F */
	__IO  uint32_t  R_EDGE_TRIG;
	/* 0x60 ~ 0x63 */
	__IO  uint32_t  R_RISE_TRIG;
	/* 0x64 */
	__IO  uint8_t  R_STABLE_THS:4;
	__IO  uint8_t  RSVD64:4;
	/* 0x65 */
	__IO  uint8_t  R_STABLE_THL:6;
	__IO  uint8_t  RSVD65:2;
	/* 0x66 ~ 0x67 */
	__IO  uint16_t  BTNS_RPT:13;
	__IO  uint16_t  RSVD66:3;
	/* 0x68 ~ 0x6B */
	__IO  uint32_t  GPIO_POL;
	/* 0x6C ~ 0x6F */
	__IO  uint32_t  WAKEUP_PIN;
	/* 0x70 ~ 0x73 */
	__IO  uint32_t  PAD_PULLUP;
	/* 0x74 ~ 0x77 */
	__IO  uint32_t  PAD_DRV;
	/* 0x78 */
	__IO  uint8_t  PIN_MODE:4;
	__IO  uint8_t  LLC_TRX_MODE:1;
	__IO  uint8_t  RSVD78:3;
	/* 0x79 */
	__IO  uint8_t  DEBUG_SW;
	/* 0x7A */
	__IO  uint8_t  U2_FLOWCTRL_EN:1;
	__IO  uint8_t  RSVD7A:7;
	/* 0x7B */
	__IO  uint8_t  BAUD_SEL:4;
	__IO  uint8_t  RSVD7B:4;
	/* 0x7C */
	__IO  uint8_t  SS_RDY:1;
	__IO  uint8_t  RSVD7C:7;
	/* 0x7D */
	__IO  uint8_t  PWR_WAIT_SLP:6;
	__IO  uint8_t  RSVD7D:2;
	/* 0x7E */
	__IO  uint8_t  CLK16_MSK:1;
	__IO  uint8_t  RSVD7E:7;
	/* 0x7F */
	__IO  uint8_t  SS_RDY_CLR:1;
	__IO  uint8_t  RSVD7F:7;
	/* 0x80 */
	__IO  uint8_t  SS_BUF[128];
} MISC_CTRL_TYPE;
#pragma pack()

/* --------------------  End of section using anonymous unions  ------------------- */
#if defined(__CC_ARM)
  #pragma pop
#elif defined(__ICCARM__)
  /* leave anonymous unions enabled */
#elif defined(__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined(__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined(__TASKING__)
  #pragma warning restore
#elif defined ( __CSMC__ )		/* Cosmic */
/* anonymous unions are enabled by default */
#else
  #warning Not supported compiler type
#endif

/* ================================================================================ */
/* ==========================              Peripheral memory map             ========================== */
/* ================================================================================ */
#define UART_0_CTRL_BASE		0x500100D0UL
#define UART_1_CTRL_BASE		0x500100E0UL
#define I2C_0_CTRL_BASE			0x50010000UL
#define I2C_0_TXD_BASE			0x50010010UL
#define I2C_0_RXD_BASE			0x50010030UL
#define I2C_1_CTRL_BASE			0x50010080UL
#define I2C_1_TXD_BASE			0x50010090UL
#define I2C_1_RXD_BASE			0x500100B0UL
#define PWM_0_CTRL_BASE			0x40010054UL
#define PWM_1_CTRL_BASE			0x40010060UL
#define PWM_2_CTRL_BASE			0x4001006CUL
#define BI_CTRL_BASE			0x4001007CUL
#define FLASH_CTRL_BASE			0x50001000UL//×
#define TIMER_CTRL_BASE			0x50001000UL//√
#define H_TIMER_CTRL_BASE		0x50010380UL
#define WDT_BASE				0x500010A0UL
#define PIN_CONFIG_BASE			0x50001060UL
#define GPO_CTRL_BASE			0x50001014UL
#define GPI_CTRL_BASE			0x50001018UL
#define GPIO_CTRL_BASE			0x50001024UL
#define GPIO_IRQ_CTRL_BASE		0x40000010UL

#define SPI_MASTER_BASE			0x50010078UL
/* ================================================================================ */
/* ==============================             Memory map             ============================== */
/* ================================================================================ */
#define ROM_BASE				0x00000000
#define RAM_BASE				0x20000000
#define MISC_BASE				0x40000000
#define INTF_BASE				0x40010000
#define LL_BASE	  				0x40020000
#define MDM_BASE				0x40030000
#define PWRON_BASE				0x50001000
#define EFUSE_CTRL_BASE			0x50000800UL
#define RF_BASE					0x40000018UL


#ifdef __cplusplus
}
#endif

#endif  /* ARMCM0_H */

