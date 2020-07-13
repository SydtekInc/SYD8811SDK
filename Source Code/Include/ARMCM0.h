/*
M0内核中断号定义、SYD8811寄存器定义文件

作者：北京盛源达科技有限公司
日期：2017/12/25
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
	ISO7816_IRQn                =   18,      /*!< Smart Card Interrupt              */
	IR_Tx_IRQn	                =   19,      /*!< IR Transmit Interrupt             */
	TOUCH_IRQn		            =   20,      /*!< TOUCH Interrupt   	              */
	HPWM_IRQn			        =   21,      /*!< High-speed PWM Interrupt          */
	HTIMER_IRQn				    =   22,      /*!< High-speed Timer Interrupt        */
	IR_Rx_IRQn					=   23,      /*!< IR Receive Interrupt              */
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
typedef enum {false = 0, true = !false} bool;
#endif


typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;
typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;
typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrorStatus;

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
	PIN_SEL_HPWM_CH0,
	PIN_SEL_HPWM_CH1,
	PIN_SEL_HPWM_CH2,
	PIN_SEL_HPWM_CH3,	
	PIN_SEL_HID_SEN,
	PIN_SEL_ANALOG,
	PIN_SEL_SC_VCC,
	PIN_SEL_IR_IN,			//PIN_SEL_RF_DEBUG,

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
			__IO  uint8_t  PAD_39_INPUT_PULL_UP:1;
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
	__IO  uint8_t  SPEED;		//clk = 2*(SPEED+1)
	/* 0x04 - 0x07  */	
	__IO  uint8_t  BUSY:1;
	__IO  uint8_t  RSVD1:1;
	__IO  uint8_t  ERR_FLG:1;
	__IO  uint8_t  DONE_FLG:1;	//current operation complete,clr READ AND WRITE
	__IO  uint8_t  READ:1;		//volatile,automatically clear
	__IO  uint8_t  WRITE:1;		//volatile,automatically clear
	__IO  uint8_t  ADDR_1:1;    //slave access address 1 byte mode. 1:1 byte EEPROM address 0:2 byte EEPROM address
	__IO  uint8_t  RSTB:1;      //software reset,don't clr reg. 0 - reset 
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

/* ============================ IR_Tx =========================== */
typedef struct {
	/* 0x00 - 0x03	*/	
	__IO  uint32_t CARRIER; //period:bit 0~10(unit: ir_clk_cycle), invert time:bit 11~21(unit: ir_clk_cycle), pwm fomat:bit 22(0: from high to low)
	/* 0x04 - 0x07  */	
	__IO  uint8_t  ONE_FH;	//the first half duration of logic one in carrier clock cycles. Must be >0 
	__IO  uint8_t  ONE_LH;	//the last half duration of logic one in carrier clock cycles. Must be >0
	__IO  uint8_t  ZERO_FH; //the first half duration of logic zero in carrier clock cycles. Must be >0 
	__IO  uint8_t  ZERO_LH; //Defines the last half duration of logic zero in carrier clock cycles. Must be >0
	/* 0x08 - 0x0B	*/	
	__IO  uint8_t  IREN:1;	//enable IR transmition
	__IO  uint8_t  REPEN:1; //enable repeat transmition
	__IO  uint8_t  MODE:1;	//0-IR, 1-PWM
	__IO  uint8_t  IRINVOUT:1;	//0-Not invert output level, 1-Invert output level
	__IO  uint8_t  ONEFMT:1;	//0-Mark first, 1-space first
	__IO  uint8_t  ZEROFMT:1;	//0-Mark first, 1-space first
	__IO  uint8_t  IRIE:1;		//interrupt enable when commond CMD FIFO transmit done: 0-disable, 1-enable
	__IO  uint8_t  CMDIE:1;		//interrupt enable when each commond CMD and repeat CMD transmit done:0-disable , 1-enable
	__IO  uint16_t REPTIME;		//repeat interval(lower 13 bit available),in carrier clock cycles
	__IO  uint8_t  RSVD0;
	/* 0x0C - 0x0F	*/
	__IO  uint8_t  ccmdfifoclr:1;   //clear common comand fifo
	__IO  uint8_t  rcmdfifoclr:1;   //clear repeat comand fifo
	__IO  uint8_t  RSVD1:6;
	__IO  uint8_t  RSVD2[3];
	/* 0x10 - 0x13	*/
	__I   uint8_t  ccmdfifocnt:4;   //count in common command fifo(8 byte)
	__I   uint8_t  rcmdfifocnt:4;   //count in repeat command fifo(8 byte)
	__I   uint8_t  irbusy:1;
	__I   uint8_t  RSVD3:7;	
	__I   uint8_t  RSVD4[2];
	/* 0x14 - 0x17	*/
	__I  uint8_t  trans_done:1;   //interrupt when commond CMD FIFO transmit done
	__I  uint8_t  cmd_done:1;     //interrupt when each cmd transmit done
	__IO  uint8_t  RSVD5:6;
	__O  uint8_t  trans_done_clr:1;
	__O  uint8_t  cmd_done_clr:1;
	__IO  uint8_t  RSVD6:6;
	__IO  uint8_t  RSVD7[2];
	/* 0x18 - 0x1B	*/
	__O  uint32_t COMCMD; 		   //data to transmit,write into common command fifo
	/*
	cmd type 0:
				[15:0]: bit sequence, LSB
				[19:16]: bit number = the number of valid bits in bit sequence - 1
				[25]: cmd type
	cmd type 1:
				[11:0] first half time 
				[23:12] last half time
				[24]: mark first or not ,0 mark first,1 space first
				[25]: cmd type
	*/
	
	/* 0x1C - 0x1F	*/
	__O  uint32_t REPCMD;	//data to transmit,write into repeat command fifo
	/*
	cmd type 0:
				[15:0]: bit sequence
				[19:16]: bit number 
				[25]: cmd type 
	cmd type 1:
				[11:0] first half time 
				[23:12] last half time
				[24]: mask first or not ,0 mark first,1 space first
				[25]: cmd type
	*/
} IR_Tx_CTRL_TYPE;

/* ============================ IR_Rx =========================== */
typedef struct {
	/* 0x00 - 0x03	*/	
	__IO  uint32_t Rx_EN:1;		//Non-volatile
	__I   uint32_t RSVD0:31;

	/* 0x04 - 0x07  */	
	__IO  uint32_t LAST_LEVEL:1;
	__I   uint32_t RSVD1:31;
	
	/* 0x08 - 0x0B	*/
	__I   uint32_t COUNTER;	//24bit available
	
	/* 0x0C - 0x0F	*/
	__IO  uint32_t EVENT:1; //Write 1 to clear
	__I   uint32_t RSVD2:31;

	/* 0x10 - 0x13	*/
	__IO  uint32_t INT_EN:1; //Enable Interrupt
	__I   uint32_t RSVD3:31;
} IR_Rx_CTRL_TYPE;

/* ============================ SPI Master=========================== */
typedef struct {
	__IO  uint8_t  SPEED:3;
	__IO  uint8_t  MSB:1;	
	__IO  uint8_t  RSVD00:1;	
	__IO  uint8_t  DONE:1;	
	__IO  uint8_t  START:1;	
	__IO  uint8_t  PE:1;	
	__IO  uint8_t  OUT;	
	__IO  uint8_t  IN;	
	__IO  uint8_t  CPOL:1;
	__IO  uint8_t  CPHA:1;
	__IO  uint8_t  RSVD01:6;	
} SPI_CTRL_TYPE;

/* ============================ FLASH Control =========================== */
typedef struct {
	/* 0x20 ~0x23 */
	__IO  uint32_t FLASH_ADDR_OFFSET;
	/* 0x24 ~0x27 */
	__IO  uint8_t  TASK_START:1;		//1: start APB read write process	
	__I   uint8_t  TASK_FINISH:1;		//1: flash controler finish the APB read write process	
	__IO  uint8_t  HCLK_FAST_OUT:1;		//1: HCLK_FAST output mode
	__IO  uint8_t  ENHANCE_MODE:1;		//1: enhance mode, 0: normal mode
	__IO  uint8_t  APB_CTRL:1;			//1: flash read write through APB, 0: flash read through AHB
	__IO  uint8_t  WAKEUP:1;			//1: wake up FLASH from sleep mode.
	__IO  uint8_t  RSVD00:2;			//Reserved 
	__IO  uint8_t  RSVD01[3];			//Reserved 

	/* 0x28 ~0x2B */
	__IO  uint8_t  CONTINUES_WORDS:7;	//the words read write one time
	__IO  uint8_t  RSVD02:1;			//Reserved 
	__IO  uint8_t  RSVD03[3];			//Reserved 

	/* 0x2C ~0x2F */
	__IO  uint8_t  TRANS_RECEIVE_LENGTH;//7:4 : receive bytes, 3:0 : transmit bytes
	__IO  uint8_t  RSVD04[3];			//Reserved 

	/* 0x30 ~0x33 */
	__IO  uint32_t TRANS_CMD_ADDR;		//[31:24] - cmd, [23:16] - addr[23:16], [15:8] - addr[15:8], [7:0] : addr[7:0]
	
	/* 0x34 ~0x37 */
	__IO  uint32_t TRANS_DUMMY;			//for bytes of data to write
	/* 0x38 ~0x3B */
	__IO  uint16_t QSPIMODETx;
	__IO  uint8_t  QSPIMODERx:2;		//if receive bytes use xIO(10: 4IO mode,01: 2IO mode ,00: 1IO mode)
	__IO  uint8_t  RSVD05:6;			//Reserved 
	__IO  uint8_t  RSVD06;				//Reserved 
	/* 0x3C ~0x3F */
	__IO  uint8_t  READ_DELAY_HALF_CYC:1;	//1: read data delay half cycle, 0: no delay
	__IO  uint8_t  READ_DELAY_ONE_CYC:1;	//1: read data delay one cycle, 0: no delay
	__IO  uint8_t  RSVD0E:6;				//Reserved 
	__IO  uint8_t  RSVD07[3];				//Reserved 
	/* 0x40 ~0x43 */
	__IO  uint32_t READ_STATUS;				//31:0 data or status received from the flash
	/* 0x44 ~0x47 */
	__IO  uint8_t  TDP_TDPDD_L;				//
	__IO  uint8_t  TDP_TDPDD_H:4;			//
	__IO  uint8_t  RSVD08:4;				//Reserved 
	__IO  uint8_t  RSVD09[2];				//Reserved 
	/* 0x48 ~0x4B */
	__IO  uint8_t  TCRDP_L;					//
	__IO  uint8_t  TCRDP_H:4;				//
	__IO  uint8_t  RSVD0A:4;				//Reserved 
	__IO  uint8_t  RSVD0B[2];				//Reserved 
	/* 0x4C ~0x4F */
	__IO  uint8_t  TRDP_L;					//
	__IO  uint8_t  TRDP_H:4;				//
	__IO  uint8_t  RSVD0C:4;				//Reserved 
	__IO  uint8_t  RSVD0D[2];				//Reserved 
	/* 0x50 ~0x53 */
	__IO  uint8_t  HOLD_MANUAL_EN:1;		//HOLD manual mode enable
	__IO  uint8_t  RSVD1E:3;				//Reserved 
	__IO  uint8_t  HOLD_MANUAL_VAL:1;		//HOLD manual setting
	__IO  uint8_t  RSVD1F:3;
	
	__IO  uint8_t  WP_MANUAL_EN:1;			//WP manual mode enable
	__IO  uint8_t  RSVD20:3;
	__IO  uint8_t  WP_MANUAL_VAL:1;			//WP manual setting
	__IO  uint8_t  RSVD21:3;
	
	__IO  uint8_t  CS_MANUAL_EN:1;			//CS manual mode enable
	__IO  uint8_t  RSVD22:3;
	__IO  uint8_t  CS_MANUAL_VAL:1;			//CS manual setting
	__IO  uint8_t  RSVD23:3;

	__IO  uint8_t  RSVD24;					//Reserved
	/* 0x54 ~0x57 */
	__IO  uint8_t  FLASH_TR_STATE:2;		//0:IDLE, 1:TRANS, 2:REVERSE, 3:RECEIVE
	__IO  uint8_t  RSVD25:2;				//Reserved
	__IO  uint8_t  FLASH_SLEEP_STATE:2;		//0: STAND_BY, 1: wait_tDP_tDPDD, 2: deep_power_down, 3: wake_up 
	__IO  uint8_t  RSVD26:2;				//Reserved 
	__IO  uint8_t  RSVD27[3];				//Reserved 
	/* 0x58 ~0x5B */
	__IO  uint8_t  FLASH_DEBUG_SEL;			//for debug use
	__IO  uint8_t  RSVD28[3];				//Reserved 
	/* 0x5C ~0x5F */
	__IO  uint32_t  FLASH_DEBUG_BUS;		//for debug use
} FLASH_CTRL_TYPE;

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
	__IO  uint32_t  START:1;	//1:start timer, the timer will stop after the current timing period, volatile bit
	__IO  uint32_t  RSVD00:31;
	/* 0x04~0x07 */
	__IO  uint32_t  STOP:1;		//1:stop timer, the timer will stop after the current timing period, volatile bit
	__IO  uint32_t  RSVD01:31;
	/* 0x08~0x0B */
	__IO  uint8_t  ONE_TIME:1;	//1:single mode, 0:repeat mode until wirte 1 to STOP
	__IO  uint8_t  INTEN:1;		//Int Enable
	__IO  uint8_t  RSVDxx:3;
	__IO  uint8_t  PRESCALER:3;	//Counter clk = hclk/(2^prescaler),default value :0
	__IO  uint8_t  RSVD02[3];
	/* 0x0C~0x0F */
	__IO  uint16_t  COUNTER_TOP;//The max value of counter(count direction fixed to count UP)
	__IO  uint16_t  RSVD03;
	/* 0x10~0x13 */
	__I  uint16_t   COUNTER;
	__I  uint8_t    RSVD04;
	__I  uint8_t    BUSY:1;		//busy indication, 1-busy, default 0
	__I  uint8_t    RSVD05:7;
	/* 0x14~0x17 */
	__IO  uint32_t  EVENT:1;	//the flag of the timing period finished,write 1 to clear
	__IO  uint32_t  RSVD06:31;
} H_TIMER_CTRL_TYPE;

/* ============================ PWM =========================== */
typedef struct
{
	/* 0x00*/
	__IO  uint8_t  T1;		//T1 value for flash mode. Unit:1/32 S
	/* 0x01*/
	__IO  uint8_t  T2;		//T2 value for flash mode. Unit:1/32 S
	/* 0x02 ~ 0x03*/
	__IO  uint16_t  T3;		//T3 value for flash mode. Unit:1/32 S
	/* 0x04*/
	__IO  uint8_t  N1;		//repeat "T1-T2" N1 times. If N1 set 0x80 then always repeat "T1-T2" and No T3
	/* 0x05*/
	__IO  uint8_t  N2;		//repeat "flash((T1-T2)*N1-T3)" N2 times. If N2 set 0x80 then always repeat "flash".
	/* 0x06*/
	__IO  uint8_t  T4;		//breath mode , flash period. Unit:1/2ms	
	/* 0x07*/
	__IO  uint8_t  BR_TH_MAX;//breath mode maxinum briteness threshlod of the LED.Unit:1/2ms
	/* 0x08 */
	__IO  uint8_t  BR_TH_MIN;//breath mode minnum briteness threshlod of the LED.Unit:1/2ms
	/* 0x09 */
	__IO  uint8_t  PWM_M;	 //M value(denominator) for PWM mode. Unit:1/32 ms
	/* 0x0A */
	__IO  uint8_t  BR_SP:4;	 //breath mode speed.indicate the breath speed. Unit:1/32 ms
	__IO  uint8_t  MODE:2;	 //0-always on mode; 1-PWM mode; 2-flash mode; 3-breath mode
	__IO  uint8_t  PAUS:1;	 //when "0" pause the flash or breath mode.
	__IO  uint8_t  LED_PE:1; //enable the LED mode.
	/* 0x0B */
	__IO  uint8_t  PWM_N;	 //N value(numerator) for PWM mode. Unit:1/32 ms
} PWM_CTRL_TYPE;

/* ============================ HPWM =========================== */
typedef struct
{
	/* 0x00~0x03 */
	__IO  uint32_t  STOP:1;		//1:stop timer, the timer will stop after the current timing period
	__IO  uint32_t  RSVD00:31;
	/* 0x04~0x07 */
	__IO  uint32_t  START:1;	//1:start timer, the timer will stop after the current timing period
	__IO  uint32_t  RSVD01:31;
	/* 0x08~0x0B */
	__IO  uint32_t  RSVD02;
	/* 0x0C~0x0F */
	__IO  uint32_t  RSVD03;
	/* 0x10~0x13 */
	__IO  uint32_t  EVENTS:2;	//bit0 - if the PWM period finished ; bit1 - if the task stop finished
	__IO  uint32_t  RSVD04:30;
	/* 0x14~0x17 */
	__IO  uint32_t  INTEN:2; 	//Int Enable
	__IO  uint32_t	RSVD05:30;
	/* 0x18~0x1B */
	__IO  uint32_t  RSVD06;
	/* 0x1C~0x1F */
	__IO  uint32_t  MODE:1; 	//count direction: 0-up, 1-up and down
	__IO  uint32_t	RSVD07:30;
	/* 0x20~0x23 */
	__IO  uint16_t  COUNTER_TOP;//The max value of counter - the period of PWM
	__IO  uint16_t  RSVD08;
	/* 0x24~0x27 */
	__IO  uint32_t  PRESCALER:4;//Counter clk = hclk/(2^prescaler),default value :0
	__IO  uint32_t	RSVD09:28;
	/* 0x28~0x2B */
	__IO  uint32_t  RSVD10;	
	/* 0x2C~0x2F */
	__IO  uint32_t  POLARITY:4;	//POLARITY[x] - polarity for channel x, cann't be set when HPWM start
	__IO  uint32_t	RSVD11:28;
	/* 0x30~0x33 */
	__IO  uint16_t  CMP_CH0;
	__IO  uint16_t  CMP_CH1;
	/* 0x34~0x37 */
	__IO  uint16_t  CMP_CH2;
	__IO  uint16_t  CMP_CH3;
} HPWM_CTRL_TYPE;

/* ============================ GPADC =========================== */
typedef struct
{
	/* 0x00 ~ 0x03*/
	__IO  uint32_t  TASK_STOP:1;	//write 1 to  disable gpadc,volatile bit
	__IO  uint32_t  RSVD00:31;
	/* 0x04 ~ 0x07*/
	__IO  uint32_t  TASK_START:1;	//write 1 to  start gpadc,volatile bit
	__IO  uint32_t  RSVD01:31;
	/* 0x08 ~ 0x0b*/
	__IO  uint32_t  CHANNEL_SEL:4;	//channel sel from 0 to 15 - maybe used @ bist mode
	__IO  uint32_t  RSVD02:28;
	/* 0x0c ~ 0x0f*/
	__IO  uint32_t  RSVD03;
	/* 0x10 ~ 0x13*/
	__IO  uint32_t  EVENTS:1;		//write 0 to clear - convert completely
	__IO  uint32_t  RSVD04:31;
	/* 0x14 ~ 0x17*/
	__IO  uint32_t  Continue_Scan:1;//write 1 to  enter gpadc continue SCAN mode until TASK_STOP
	__IO  uint32_t  RSVD05:31;	
	/* 0x18 ~ 0x1b*/
	__IO  uint32_t  RSVD06;
	/* 0x1c ~ 0x1f*/
	__IO  uint32_t  INTENSET:1;		//write 1 to  enable gpadc interrupt
	__IO  uint32_t  RSVD07:31;	
	/* 0x20 ~ 0x23*/
	__IO  uint32_t  INTENCLR:1;		//write 1 to  disable gpadc interrupt
	__IO  uint32_t  RSVD08:31;	
	/* 0x24 ~ 0x27*/
	__IO  uint16_t  SCAN_COUNT;
	__IO  uint16_t  RSVD09;
	/* 0x28 ~ 0x2b*/
	__IO  uint16_t  DATA_LENGTH; 	//+1, ave模式下，一次SCAN采集的数据个数,参考AVERAGE寄存器
	__IO  uint16_t  RSVD10;
	/* 0x2c ~ 0x3b*/
	__IO  uint32_t  RSVD11[4];
	/* 0x3c ~ 0x3f*/
	__IO  uint8_t   START_SETTLE:6;	//time delay from GPADC enable to GPADC DATA available
	__IO  uint8_t   RSVD12:2;
	__IO  uint8_t   RSVD13[3];
	/* 0x40 ~ 0x43*/
	__IO  uint8_t   CHANNEL_SETTLE:6;//time delay from channel switch to GPADC DATA available
	__IO  uint8_t   RSVD14:2;
	__IO  uint8_t   RSVD15[3];
	/* 0x44 ~ 0x47*/
	__IO  uint32_t  AVERAGE:3;		 //Average=3/5/7：2/4/8次求和后取平均,对应的DATA_LENGTH=1/3/7, //default value:1(no average)
	__IO  uint32_t  RSVD16:29;
	/* 0x48 ~ 0x4b*/
	__IO  uint32_t  CHANNEL_SET_NUM:4;//enable the channel selected by CHANNEL_SET0 & CHANNEL_SET1 in all mode, never be zero,and max value 11
	__IO  uint32_t  RSVD17:28;
	/* 0x4c ~ 0x4f*/
	__IO  uint32_t  DA_GPADC_EN:1;
	__IO  uint32_t  RSVD18:31;
	/* 0x50 ~ 0x53*/
	__IO  uint8_t   DA_GPADC_TRIM:5;
	__IO  uint8_t   RSVD19:3;
	__IO  uint8_t   RSVD20[3];
	/* 0x54 ~ 0x57*/
	__IO  uint32_t  DA_GPADC_BIST_EN:1;
	__IO  uint32_t  RSVD21:31; 
	/* 0x58 ~ 0x5b*/
	__IO  uint32_t  DA_GPADC_BIST_SHORT_EN:1;
	__IO  uint32_t  RSVD22:31; 
	/* 0x5c~ 0x5f */
	__IO  uint8_t   CLKRATE:6; //GPADC clock frequency = hclk/((CLKRATE+1)*2)
	__IO  uint8_t   RSVD23:2;
	__IO  uint8_t   RSVD24[3];
	/* 0x60 ~ 0x63*/
	__IO  uint32_t  CHANNEL_SET0;	//Scan channel list
	/* 0x64 ~ 0x67*/
	__IO  uint32_t  CHANNEL_SET1;	//Scan channel list
	/* 0x68 ~ 0x6b*/
	__I  uint32_t   DEBUG_BUS;
	/* 0x6c ~ 0x6f*/
	__I  uint32_t   adc_data_hclk:10;	//adc raw data
	__I  uint32_t	RSVD25:22;
	/* 0x70 ~ 0x73*/
	__I  uint32_t   gpadc_fsm_cs:3;	//gpadc current state
	__I  uint32_t   RSVD26:29;
	/* 0x74 ~ 0x77*/
	__IO  uint32_t  BIST_SHORT_HIGH_SETTLE:10;
	__IO  uint32_t	RSVD27:22;
	/* 0x78 ~ 0x7b*/
	__IO  uint32_t  BIST_SHORT_LOW_SETTLE:10;
	__IO  uint32_t	RSVD28:22;
	/* 0x7c ~ 0x7f*/
	__IO  uint8_t   Debug_O_SEL;
	__IO  uint8_t	RSVD29[3];
	/* 0x80 ~ 0x83*/
	__I  uint32_t   adc_data_ave_hclk:10;	//average data out
	__I  uint32_t	RSVD30:22;
	/* 0x84 ~ 0x87*/
	__IO  uint32_t  RG_GP_ADC_BIST_UB:10;
	__IO  uint32_t	RSVD31:22;
	/* 0x88 ~ 0x8b*/
	__IO  uint32_t  RG_GP_ADC_BIST_LB:10;
	__IO  uint32_t	RSVD32:22;
	/* 0x8c ~ 0x8f*/
	__IO  uint32_t  RG_GP_ADC_BIST_NFRAME:5;
	__IO  uint32_t	RSVD33:27;
	/* 0x90 ~ 0x93*/
	__IO  uint32_t  RG_GP_ADC_BIST_RAMPSET:5;
	__IO  uint32_t	RSVD34:27;
	/* 0x94 ~ 0x97*/
	__IO  uint32_t  RG_GP_ADC_BIST_LSBSHIFT:3;
	__IO  uint32_t	RSVD35:29;
	/* 0x98 ~ 0x9b*/
	__IO  uint32_t  RG_GP_ADC_BIST_ELYDONE:1;
	__IO  uint32_t  RSVD36:31;
	/* 0x9c ~ 0x9f*/
	__IO  uint32_t	RG_GP_ADC_BIST_UPDOWN:1;
	__IO  uint32_t	RSVD37:31;
	/* 0xa0 ~ 0xa3*/
	__IO  uint32_t  RG_AMIC_ADC_BIST_WINDOW:4;
	__IO  uint32_t  RSVD38:28;
	/* 0xa4 ~ 0xa7*/
	__I  uint32_t	GP_ADC_BIST_RESULT:1;
	__I  uint32_t	RSVD39:31;
	/* 0xa8 ~ 0xab*/
	__I  uint32_t   GP_ADC_BISTPTR:12;
	__I  uint32_t	RSVD40:20;
	/* 0xac ~ 0xaf*/
	__I  uint32_t   GP_ADC_BISTWINSTAT;
	/* 0xb0 ~ 0xb3*/
	__IO  uint32_t  RG_GP_ADC_BIST_PREPTIME:4;
	__IO  uint32_t  RSVD41:28;
}GPADC_CTRL_TYPE;

/* ============================ CAPDET =========================== */
typedef struct
{
	/* 0x00 ~ 0x03*/
	__IO  uint8_t  RG_CAPDET_IBIAS:2;
	__I   uint8_t  RSVD00:6;
	__IO  uint8_t  B_CAPDET_N1:6;
	__I   uint8_t  RSVD01:2;
	__IO  uint8_t  B_CAPDET_DEGLITCH;
	__IO  uint8_t  R_FULL_CYCLE_CNT_EN:1;
	__I   uint8_t  RSVD02:7;	
	/* 0x04 ~ 0x07*/
	__I   uint32_t CAPDET_CNT_OVERFLOW:1;
	__I   uint32_t RSVD03:31;
	/* 0x08 ~ 0x0b*/
	__I   uint32_t CAPDET_INT:1;
	__I   uint32_t TOUCH_INT:1;
	__I   uint32_t RSVD04:30;
	/* 0x0c ~ 0x0f*/
	__IO  uint8_t  R_Total_pad:4;
	__I   uint8_t  RSVD05:4;
	__IO  uint16_t R_TOUCH_MASK;
	__IO  uint8_t  R_TOUCH_INT_MASK:1;
	__I   uint8_t  RSVD06:3;
	__IO  uint8_t  R_CAPDET_INT_MASK:1;
	__I   uint8_t  RSVD07:3;
	/* 0x10 ~ 0x13*/
	__IO  uint16_t R_Threshold;
	__IO  uint16_t R_SETTLE_CYCLE;
	/* 0x14 ~ 0x17*/
	__IO  uint8_t  R_CHANNEL_MAP0:4;
	__I   uint8_t  RSVD08:4;
	__IO  uint8_t  R_CHANNEL_MAP1:4;
	__I   uint8_t  RSVD09:4;
	__IO  uint8_t  R_CHANNEL_MAP2:4;
	__I   uint8_t  RSVD10:4;
	__IO  uint8_t  R_CHANNEL_MAP3:4;
	__I   uint8_t  RSVD11:4;
	/* 0x18 ~ 0x1b*/
	__IO  uint8_t  R_CHANNEL_MAP4:4;
	__I   uint8_t  RSVD12:4;
	__IO  uint8_t  R_CHANNEL_MAP5:4;
	__I   uint8_t  RSVD13:4;
	__IO  uint8_t  R_CHANNEL_MAP6:4;
	__I   uint8_t  RSVD14:4;
	__IO  uint8_t  R_CHANNEL_MAP7:4;
	__I   uint8_t  RSVD15:4;
	/* 0x1c ~ 0x1f*/
	__IO  uint8_t  R_CHANNEL_MAP8:4;
	__I   uint8_t  RSVD16:4;
	__IO  uint8_t  R_CHANNEL_MAP9:4;
	__I   uint8_t  RSVD17:4;
	__IO  uint8_t  R_CHANNEL_MAPA:4;
	__I   uint8_t  RSVD18:4;
	__IO  uint8_t  R_CHANNEL_MAPB:4;
	__I   uint8_t  RSVD19:4;
	/* 0x20 ~ 0x23*/
	__IO  uint8_t  R_CHANNEL_MAPC:4;
	__I   uint8_t  RSVD20:4;
	__IO  uint8_t  R_CHANNEL_MAPD:4;
	__I   uint8_t  RSVD21:4;
	__IO  uint8_t  R_CHANNEL_MAPE:4;
	__I   uint8_t  RSVD22:4;
	__IO  uint8_t  R_CHANNEL_MAPF:4;
	__I   uint8_t  RSVD23:4;
	/* 0x24 ~ 0x27*/
	__IO  uint16_t  R_Timer_En:1;
	__I   uint16_t  RSVD24:15;
	__IO  uint16_t  R_Timer;
	/* 0x28 ~ 0x2b*/
	__IO  uint32_t  R_Each_Time:18;
	__I   uint16_t  RSVD25:14;	
	/* 0x2c ~ 0x3f*/
	__I   uint32_t	RSVD26[5];
	/* 0x40 ~ 0x43*/
	__I   uint16_t	COUNT_OUT0:16;	
	__I   uint16_t	TimeOut_0:1;	
	__I   uint16_t	RSVD27:15;	
	/* 0x44 ~ 0x47*/
	__I   uint16_t	COUNT_OUT1:16;	
	__I   uint16_t	TimeOut_1:1;	
	__I   uint16_t	RSVD28:15;	
	/* 0x48 ~ 0x4b*/
	__I   uint16_t	COUNT_OUT2:16;	
	__I   uint16_t	TimeOut_2:1;	
	__I   uint16_t	RSVD29:15;	
	/* 0x4c ~ 0x4f*/
	__I   uint16_t	COUNT_OUT3:16;	
	__I   uint16_t	TimeOut_3:1;	
	__I   uint16_t	RSVD30:15;	
	/* 0x50 ~ 0x53*/
	__I   uint16_t	COUNT_OUT4:16;	
	__I   uint16_t	TimeOut_4:1;	
	__I   uint16_t	RSVD31:15;	
	/* 0x54 ~ 0x57*/
	__I   uint16_t	COUNT_OUT5:16;	
	__I   uint16_t	TimeOut_5:1;	
	__I   uint16_t	RSVD32:15;	
	/* 0x58 ~ 0x5b*/
	__I   uint16_t	COUNT_OUT6:16;	
	__I   uint16_t	TimeOut_6:1;	
	__I   uint16_t	RSVD33:15;	
	/* 0x5c ~ 0x5f*/
	__I   uint16_t	COUNT_OUT7:16;	
	__I   uint16_t	TimeOut_7:1;	
	__I   uint16_t	RSVD34:15;	
	/* 0x60 ~ 0x63*/
	__I   uint16_t	COUNT_OUT8:16;	
	__I   uint16_t	TimeOut_8:1;	
	__I   uint16_t	RSVD35:15;	
	/* 0x64 ~ 0x67*/
	__I   uint16_t	COUNT_OUT9:16;	
	__I   uint16_t	TimeOut_9:1;	
	__I   uint16_t	RSVD36:15;	
	/* 0x68 ~ 0x6b*/
	__I   uint16_t	COUNT_OUTA:16;	
	__I   uint16_t	TimeOut_A:1;	
	__I   uint16_t	RSVD37:15;	
	/* 0x6c ~ 0x6f*/
	__I   uint16_t	COUNT_OUTB:16;	
	__I   uint16_t	TimeOut_B:1;	
	__I   uint16_t	RSVD38:15;		
	/* 0x70 ~ 0x73*/
	__I   uint16_t	COUNT_OUTC:16;	
	__I   uint16_t	TimeOut_C:1;	
	__I   uint16_t	RSVD39:15;	
	/* 0x74 ~ 0x77*/
	__I   uint16_t	COUNT_OUTD:16;	
	__I   uint16_t	TimeOut_D:1;	
	__I   uint16_t	RSVD40:15;	
	/* 0x78 ~ 0x7b*/
	__I   uint16_t	COUNT_OUTE:16;	
	__I   uint16_t	TimeOut_E:1;	
	__I   uint16_t	RSVD41:15;		
	/* 0x7c ~ 0x7f*/
	__I   uint16_t	COUNT_OUTF:16;	
	__I   uint16_t	TimeOut_F:1;	
	__I   uint16_t	RSVD42:15;		
}CAPDET_CTRL_TYPE;

/* ============================ RTC =========================== */
typedef struct {
	/* 0xA8 */
	__IO  uint8_t  RSVD00;
	/* 0xA9 */
	__IO  uint8_t  EVENTS:4;
	__I   uint8_t  RSVD01:4;
	/* 0xAA */
	__IO  uint8_t  EVENTS_EN:4;
	__IO  uint8_t  EVENTS_CLR:4;
	/* 0xAB */
	__IO  uint8_t  START:1;	//rtc start
	__IO  uint8_t  STOP:1;	//rtc stop
	__IO  uint8_t  CLEAR:1;	//rtc clear: clr week,hour,min,sec
	__IO  uint8_t  LOAD:1;	//rtc road: reload COMPARE0 & COMPARE1
	__IO  uint8_t  RSVD04:4;
	/* 0xAC ~ 0xAF */
	__IO  uint32_t COUNTER:24;		//the inner counter initial value with range 0~PRESCALER, and its unit is clk
	__I   uint32_t  RSVD05:8;
	/* 0xB0 ~ 0xB1 */
	__IO  uint16_t  PRESCALER:15;	//(32K)/(PRESCALER+1) = clk/(prescaler+1)
	__IO  uint16_t  RSVD06:1;
	/* 0xB2 */
	__IO  uint8_t  SECONDS_BIT:4;	//exponent value -> clk/(prescaler+1)/(2^second_bit)  //prescale again based on tick period Int
	__IO  uint8_t  RSVD07:4;
	/* 0xB3 */
	__IO  uint8_t  DEBUG_SEL:4;		//digital debug
	__IO  uint8_t  RSVD08:4;
	/* 0xB4 ~ 0xC3 */
	__IO  uint32_t	COMPARE0;		//alarm_0: lower 24bit valiable(HH/MM/SS)
	__IO  uint32_t	COMPARE1;		//alarm_1: lower 24bit valiable(HH/MM/SS)
	__IO  uint32_t	CALENDAR_INI;	//calendar initial value : week/hour/minute/second
	__I  uint32_t   CALENDAR;		//calendar current value : week/hour/minute/second
}RTC_CTRL_TYPE;

/* ============================ SmartCard Ctrl =========================== */
typedef struct
{
	/* 0x00*/
	__IO  uint8_t  MODE:1;		//0-7816; 1-UART
	__IO  uint8_t  PARITY:1;	//0-no parity bit; 1-one parity bit(7816 mode default)
	__IO  uint8_t  ODD:1;		//Parity Check mode Under UART,0-even; 1-odd
	__IO  uint8_t  T0T1:1;		//0-T0 Protocol; 1-T1 Protocol
	__IO  uint8_t  STOP_LEN:1;	//Stop Bit Length(valid when mode = 1),0-1ETU,1-2ETU
	__IO  uint8_t  RX_RETRY_CNT:3;	//the maximum number of receiver retries that are allowed when parity error has occurred.
	/* 0x01*/
	__IO  uint8_t  TX_RETRY_CNT:3;	//the maximum number of transmitter retries that are allowed when parity error has occurred.
	__IO  uint8_t  CLK_STOP_VAL:1;	//clock level to keep when clock disabled.
	__IO  uint8_t  CLK_STOP_EN:1;	//1-stop clk
	__IO  uint8_t  DET_LEVEL:1; 	//detect card insert at falling edge(0) or rising edge(1)
	__IO  uint8_t  AUTO_ACTIVATION_EN:1;  //1:active after card insert detect
	__IO  uint8_t  ACTIVE_VCC_LEVEL:1; 	  //SC output voltage level
	/* 0x02 ~ 0x03*/
	__IO  uint8_t  EXTRA_GUARD_TIME;	  //extra guard time integer
	__IO  uint8_t  GUARD_TIME;			  //Block Guard Time, ETU based
	//__IO  uint8_t  BLOCK_GUARD_TIME;	  //Block Guard Time, ETU based
	/* 0x04 ~ 0x07*/
	__IO  uint8_t  RX_FIFO_THRESHOLD:4;
	__IO  uint8_t  TX_FIFO_THRESHOLD:4;
	__IO  uint16_t RX_TIMEOUT_DELAY;		//rx fifo empty overtime setting
	__IO  uint8_t  RX_TIMEOUT_DETECT_EN:1; 	//rx fifo empty overtime detect enable when receive
	__IO  uint8_t  FILTER:2;
	__IO  uint8_t  RSVD00:5;
	/* 0x08 ~ 0x0B*/
	__IO  uint16_t SC_CLK_DIV;		//Smart card clock divisor,clk_after_divisor = clk/(SC_CLK_DIV+1)
	__IO  uint16_t BAUD_CLK_DIV;	//Baud clock divisor, ETU = clk_after_divisor/(BIT_DIV+1)
	/* 0x0C ~ 0x0F*/
	__IO  uint8_t RX_ENABLE:1;
	__IO  uint8_t TX_ENABLE:1;
	__IO  uint8_t RX_RETRY_ENABLE:1;	//enable retry when receive error has occurred.
	__IO  uint8_t TX_RETRY_ENABLE:1;	//enable retry when transmit error has occurred.
	__IO  uint8_t inject_tpe :1;		//inject transmit parity error
	__IO  uint8_t inject_rpe :1;		//inject receive parity error
	__IO  uint8_t  RSVD01:2;
	__IO  uint8_t  RSVD02[3];
	/* 0x10 ~ 0x13*/
	__IO  uint8_t TRIGGER_ACTIVATE:1;	//start activation sequence
	__IO  uint8_t TRIGGER_DEACTIVATE:1;	//start deactivation sequence
	__IO  uint8_t TRIGGER_WARM_RESET:1;	//start warm reset	
	__IO  uint8_t RSVD03:5;
	__IO  uint8_t RSVD04[3];
	/* 0x14 ~ 0x17*/
	__IO  uint16_t ACT_TIME; //the duration of each part of the activation and deactivation sequence
	__IO  uint16_t RSVD05;
	/* 0x18 ~ 0x1B*/
	__IO  uint16_t RST_TIME; //the duration of the smartcard reset sequence
	__IO  uint16_t RSVD06;	
	/* 0x1C ~ 0x1F*/
	__IO  uint16_t ATR_WAIT_TIME; //The ATR response on SCIO should begin between 400 and 40000 clock cycles (Td) after the rising edge of the SCRSTN signal
	__IO  uint16_t INS_WAIT_TIME;	
	/* 0x20 ~ 0x23*/
	__IO  uint16_t C2CDLY; 		  //the maximum time between the leading edges of two, consecutive characters
	__IO  uint16_t RSVD08;
	/* 0x24 ~ 0x27*/
union{
	struct{
		__IO  uint8_t  TXDONE_IE:1; 	//transmission Done Interrupt enable
		__IO  uint8_t  TXFE_IE:1;		//TX FIFO empty Interrupt enable
		__IO  uint8_t  TXTHR_IE:1;		//TX FIFO Threshold Interrupt enable
		__IO  uint8_t  TXPERR_IE:1; 	//Transmission Parity Error Interrupt Enable
		__IO  uint8_t  TXRETRY_IE:1;	//retry interrupt enable when parity error when transmitting
		__IO  uint8_t  TXOVRETRY_IE:1;	//over retry interrupt enable when parity error when transmitting
		__IO  uint8_t  RXFNE_IE:1;		//RX FIFO not empty Interrupt Enable
		__IO  uint8_t  RXTHR_IE:1;		//RX FIFO Threshold Interrupt Enable
		
		__IO  uint8_t  RXOVT_IE:1;		//rx fifo empty overtime interrupt enable
		__IO  uint8_t  RXPERR_IE:1; 	//Receive Parity Error Interrupt Enable
		__IO  uint8_t  RXRETRY_IE:1;	//retry interrupt enable when parity error when receiving
		__IO  uint8_t  RXOVRETRY_IE:1;	//over retry interrupt enable when parity error when receiving
		__IO  uint8_t  C2CTIMEOUT_IE:1; //character to character overtime interupt enable
		__IO  uint8_t  ATRDONE_IE:1;	//ATR Done Interrupt Enable
		__IO  uint8_t  ATRFAIL_IE:1;	//ATR Fail Interrupt Enablee
		__IO  uint8_t  CARD_INS_IE:1;	//Card detect Interrupt Enable
		
		__IO  uint8_t  CARD_RM_IE:1;	//Card remove Interrupt Enable	
		__IO  uint8_t  DACT_DONE_IE:1;	//card deactive done interrupt enable
		__IO  uint8_t  RSVD09:6;
		
		__IO  uint8_t  RSVD10;
	};

	__IO  uint32_t  INTS_EN;
};

	/* 0x28 ~ 0x2B*/
union{
	struct{
		__IO  uint8_t  TXDONE:1;		//transmission Done Interrupt flag
		__I   uint8_t  TXFE:1;			//TX FIFO empty Interrupt flag
		__I   uint8_t  TXTHR:1;			//TX FIFO Threshold Interrupt flag
		__IO  uint8_t  TXPERR:1;		//Transmission Parity Error Interrupt 
		__IO  uint8_t  TXRETRY:1;		//retry interrupt enable when parity error when transmitting
		__IO  uint8_t  TXOVRETYR:1; 	//over retry interrupt when parity error when transmitting
		__I   uint8_t  RXFNE:1;			//RX FIFO not empty Interrupt flag
		__I   uint8_t  RXTHR:1;			//RX FIFO Threshold Interrupt flag
		
		__IO  uint8_t  RXOVT:1; 		//rx fifo empty overtime interrupt
		__IO  uint8_t  RXPERR:1;		//Receive Parity Error Interrupt 
		__IO  uint8_t  RXRETRY:1;		//retry interrupt when parity error when receiving
		__IO  uint8_t  RXOVRETRY:1; 	//over retry interrupt when parity error when receiving		
		__IO  uint8_t  C2CTIMEOUT:1;	//character to character overtime  interupt
		__IO  uint8_t  ATRDONE:1;		//ATR done interupt 
		__IO  uint8_t  ATRFAIL:1;		//ATR fail interupt 
		__IO  uint8_t  CARD_INS:1;		//Card detect Interrupt
		
		__IO  uint8_t  CARD_RM:1;		//Card remove Interrupt
		__IO  uint8_t  DACT_DONE:1; 	//card deactive done interrupt
		__IO  uint8_t  RSVD11:6;
	
		__IO  uint8_t  RSVD12;
	};
	
	__IO  uint32_t INTS_STATE;	
};

	/* 0x2C ~ 0x2F*/
	__I  uint8_t  INVERSE:1;		//0:direct convention(lsbf,high->1), 1:inverse convention(msbf,low->1)
	__I  uint8_t  RXATV:1;			//receive in active 
	__I  uint8_t  TXATV:1;			//transmission in active
	__I  uint8_t  RSVD13:5;

	__I  uint8_t  RSVD14[3];
	/* 0x30 ~ 0x33*/
	__IO  uint8_t  TXFIFO_OVF:1;	//tx fifo overflow
	__IO  uint8_t  RXFIFO_OVF:1;	//rx fifo overflow 
	__IO  uint8_t  RSVD15:6;

	__IO  uint8_t  RSVD16[3];	
	/* 0x34 ~ 0x37*/
	__IO  uint8_t  DATA;				//Write this register to push data into tx FIFO,read this register to get data from rx FIFO
	__I   uint8_t  RSVD17[3];
	/* 0x38 ~ 0x3B*/
	__I  uint32_t  SC_STATE:3;		//Card state
	__I  uint32_t  ACT_STATE:3;		//ACT state
	__I  uint32_t  ATR_STATE:3;		//ATR state
	__I  uint32_t  ATRSEQ_STATE:3;	//ATR Seq Parse State
}SC_READER_CTRL_TYPE;

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

/* ============================ Power Manager  =========================== */
typedef struct
{
	/* 0x00 */
	__IO  uint8_t  MCU_CLOCK_SEL:3;	//MCU clock selection: (0: 64MHz, 1: 32MHz, 2: 16MHz...)
	__IO  uint8_t  RSVD00:5;
	/* 0x01 */
	__IO  uint8_t  RSVD01;	
	/* 0x02 */
	__IO  uint8_t  RSVD02;
	/* 0x03 */
	__IO  uint8_t  SWD_WAKE_FLAG:1;
	__IO  uint8_t  RSVD03:7;
	/* 0x04 */
	__IO  uint8_t  RSVD040:4;
	__IO  uint8_t  DRAM_SEL:3;	//DRAM_sel[0] : enable first DataRAM(8K byte), [1]: sec 8k, [2]: third 16k
	__IO  uint8_t  RSVD041:1;
	/* 0x05 */
	__IO  uint8_t  RSVD05;	
	/* 0x06 ~ 0x07 */
	__IO  uint16_t  PWR_WAIT_SLP:12;	//Power wake-up settling time in LPO unit
	__IO  uint16_t  RSVD06:4;
	/* 0x08 */
	__IO  uint8_t  RFMODE_MCU:5;	//RFMODE_mcu : (1: power-down, 2: sleep, 4: standby, 8: TX, 0x10: RX)
	__IO  uint8_t  RFMODE_MANUAL:1;	//RFMODE_manual : enable RFMODE manual setting mode
	__IO  uint8_t  RSVD080:1;
	__IO  uint8_t  RFMODE_RST:1;	//Reset RFMODE to standby mode
	/* 0x09 */
	__IO  uint8_t  RSVD09;
	/* 0x0a */
	__IO  uint8_t  FSM_SLEEP_EN:1;	//Enable auto sleep mode
	__IO  uint8_t  MRR_MANU_ON:1;
	__IO  uint8_t  MRR_MANU_OFF:1;
	__IO  uint8_t  RSVD0A:5;
	/* 0x0b */
	__IO  uint8_t  DSLP_SYS:1;		//Enable deep sleep mode(power-down)
	__IO  uint8_t  RSVD0B1:3;
	__IO  uint8_t  DSLP_LPO_EN:1;
	__IO  uint8_t  RSVD0B2:3;
	/* 0x0C */
	__IO  uint8_t  MCU_SLEEP:1;		//MCU sleep mode
	__IO  uint8_t  RSVD0C1:7;
	/* 0x0D */
	__IO  uint8_t  UART_EN:1;		//
	__IO  uint8_t  CAPDET_EN:1;
	__IO  uint8_t  RSVD0D:5;
	__IO  uint8_t  SW_RESET:1;		//software reset, 0:reset, def:1
	/* 0x0E */
	__IO  uint8_t  LPS09_MANU_ON:1;
	__IO  uint8_t  LPS09_MANU_EN:1;
	__IO  uint8_t  LPS06_MANU_ON:1;
	__IO  uint8_t  LPS06_MANU_EN:1;
	__IO  uint8_t  RSVD0E:2;
	__IO  uint8_t  DIG_DEBUG_EN:1;
	__IO  uint8_t  ANA_DEBUG_EN:1;
	/* 0x0F */
	__IO  uint8_t  RSVD0F0:2;
	__IO  uint8_t  CAPDET_WAKE_EN:1;
	__IO  uint8_t  ANA_WAKE_EN:1;
	__IO  uint8_t  TMR_WAKE_EN:1;	//enable timer wake-up of both sleep and deep sleep mode
	__IO  uint8_t  PIN_WAKE_EN:1;	//enable pin wake-up of both sleep and deep sleep mode
	__IO  uint8_t  RTC_WAKE_EN:1;
	__IO  uint8_t  WDT_WAKE_EN:1;	
	/* 0x10 ~ 0x13 */
	__IO  uint32_t  WAKE_PIN_EN;	//Select wake-up pin combination
	/* 0x14~0x1F */
	__IO  uint8_t  RSVD18[12];
	/* 0x20~0x23 */
	__IO  uint32_t  GPIO_POL;	//GPIO input polarity : (1: un-changed, 0: inverted)
} POWER_CTRL_TYPE;

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

/* ============================ LLC ============================= */
typedef struct {
	/* 0x00 */
	__IO  uint8_t  SR_A:1;		// reset all link-layer state machine and registers
	__IO  uint8_t  SR_P:1;		// reset all link-layer state machine except registers
	__IO  uint8_t  RSVD00:6;
	/* 0x01 */
	/*__IO  uint8_t  TXINT:1;	// TX interrupt status when transmitting a packet and ack-ed
	__IO  uint8_t  RXINT:1;		// RX interrupt status when received a valid packet
	__IO  uint8_t  ADVSCANEND:1;	// Advertising or Scan interval end interrupt status
	__IO  uint8_t  CONNSETUP:1;	// Connection set-up interrupt status
	__IO  uint8_t  CONNLOST:1;		// Connection lost interrupt status
	__IO  uint8_t  CONNEVTEND:1;	// Connection event end interrupt status
	__IO  uint8_t  SLEEP:1;			// Sleep event interrupt status when transaction ends in a connection interval
	__IO  uint8_t  WAKEUP:1;*/		// Wake-up event interrupt status when a connection interval starts from sleeping
	__IO  uint8_t  INTST;
	/* 0x02 */
	__IO  uint8_t  TXINTMSK:1;
	__IO  uint8_t  RXINTMSK:1;
	__IO  uint8_t  ADVSCANENDMSK:1;
	__IO  uint8_t  CONNSETUPMSK:1;
	__IO  uint8_t  CONNLOSTMSK:1;
	__IO  uint8_t  CONNEVTENDMSK:1;
	__IO  uint8_t  SLEEPMSK:1;
	__IO  uint8_t  WAKEUPMSK:1;	
	/* 0x03 */
	__IO  uint8_t  TX_FULL:1;		// TXFIFO full
	__IO  uint8_t  TX_EMPTY:1;	// TXFIFO empty
	__IO  uint8_t  RX_FULL:1;		// RXFIFO full
	__IO  uint8_t  RX_EMPTY:1;	// RXFIFO empty
	__IO  uint8_t  RSVD03:4;	
	/* 0x04 ~ 0x05 */
	__IO  uint8_t  RSVD04[2];
	/* 0x06 */
	__IO  uint8_t  LTCY_DIS;
	/* 0x07 */
	__IO  uint8_t  RSVD07;
	/* 0x08 */
	__IO  uint8_t  ARD:4;	// RX state time-out duration -> T_timeout = 250 + ARD*150 (us)
	__IO  uint8_t  DIS_CRC:1;	// disable send crc ?
	__IO  uint8_t  WW_HALVED_EN:1;	// wind wide halved disconn check enable
	__IO  uint8_t  WW_RESERVE:1;
	__IO  uint8_t  RSVD08:1;
	/* 0x09 */
	__IO  uint8_t  WHITE_EN:1;	// enable whitening function, (rx & tx)
	__IO  uint8_t  CRC_ALLOW:1;	// disable CRC check
	__IO  uint8_t  RSVD090:2;
	__IO  uint8_t  CRC_PASS:1;	// status of CRC_PASS of received packet
	__IO  uint8_t  SENDING_ACK:1;	// status of received a packet and not yet acked
	__IO  uint8_t  RSVD091:2;
	/* 0x0A */
	__IO  uint8_t  CH_SEL;	// obsolete
	/* 0x0B */
	__IO  uint8_t  T_TXSTR;	// TX start-up time (config rf tx to tx data delay time, unit: 2us)
	/* 0x0C */
	__IO  uint8_t  T_R2TSTR;	// RX-to-TX time (rx end to config rf tx delay time, unit: 2us)
	/* 0x0D */
	__IO  uint8_t  FIXED_CH;	// when set, TX channel is set to CH_USER(0x62) in physical channel order
	/* 0x0E */
	__IO  uint8_t  T_STBYLEN;	// Standby time between RX and TX
	/* 0x0F */
	__IO  uint8_t  FSM_STATE;	// Internal state machine ?
	/* 0x10 */
	__IO  uint8_t  ADV_EN:1;		//start adv
	__IO  uint8_t  ADV_DLY_EN:1;	//enable delay of adv event(note: delay is a pseu-rand with range of 0~10ms).
	__IO  uint8_t  FILTERPOLICY:2;		//filter policy, adv & connect filter
	__IO  uint8_t  FIL_ADR_TYPE:1;	//filter addr type
	__IO  uint8_t  FIL_ADVA_EN:1;		//enable AdvA check of white-list check in advertising mode
	__IO  uint8_t  RSVD10:2;
	/* 0x11 */
	__IO  uint8_t  ADV_RND:7;	//round number of adv event
	__IO  uint8_t  RSVD11:1;
	/* 0x12 ~ 0x13 */
	__IO  uint16_t  ADV_ITV;	//adv interval, unit: 625us
	/* 0x14 */
	__IO  uint8_t  ADV_PITV;	//adv chn(37/38/39) interval, unit: 336us
	/* 0x15 */
	__IO  uint8_t  ADV_CHIDX;	//bit0~2: adv chnmap
	/* 0x16 */
	union{
		struct{
			__IO  uint8_t  ADV_IND_FIL:1;
			__IO  uint8_t  ADV_DIR_FIL:1;
			__IO  uint8_t  ADV_NC_FIL:1;
			__IO  uint8_t  SCAN_REQ_FIL:1;
			__IO  uint8_t  SCAN_RSP_FIL:1;
			__IO  uint8_t  CONN_REQ_FIL:1;
			__IO  uint8_t  ADV_SCAN_FIL:1;
			__IO  uint8_t  ALL_FIL:1;
		};
		__IO  uint8_t  FILTER_POLICY;
	};
	/* 0x17 */
	__IO  uint8_t  RSVD17;
	/* 0x18 */
	//__IO  uint8_t  A_SLP_INT_R:1;		///
	//__IO  uint8_t  S_SLP_INT_R:1;		///
	//__IO  uint8_t  A_WAKE_INT_R:1;	///
	//__IO  uint8_t  S_WAKE_INT_R:1;	///
	//__IO  uint8_t  RSVD18:4;
	__IO  uint8_t  LLC2_INTST;			
	/* 0x19 */
	__IO  uint8_t  A_SLP_INT_MSK:1;	///
	__IO  uint8_t  S_SLP_INT_MSK:1;	///
	__IO  uint8_t  A_WAKE_INT_MSK:1;	///
	__IO  uint8_t  S_WAKE_INT_MSK:1;	///
	__IO  uint8_t  RSVD19:4;
	/* 0x1A */
	__IO  uint8_t  CONN_AUTOSLP_EN:1;	///
	__IO  uint8_t  ADV_AUTOSLP_EN:1;		///
	__IO	  uint8_t  AUTOSLP_CLKGATE_EN:1;	///
	__IO  uint8_t  LTCY_WW_EN:1;			///
	__IO  uint8_t  RSVD2A:4;
	/* 0x1B ~ 0x1F */
	__IO  uint8_t  RSVD1B[5];	
	/* 0x20 ~ 0x21 */
	__IO  uint16_t  CONN_EVTCNT;	//connection event counter
	/* 0x22 */
	__IO  uint8_t  CONN_UPDATE:1;	//enable connection update
	__IO  uint8_t  CHMAP_UPDATE:1;	//enable channel-map update
	__IO  uint8_t  RSVD22:6;
	/* 0x23 */
	__IO  uint8_t  CONN_CRCERRTH:3;	//?
	__IO  uint8_t  RSVD230:1;
	__IO  uint8_t  STOP_REPLY:1;	//stop reply ack
	__IO  uint8_t  RSVD231:3;
	/* 0x24 */
	__IO  uint8_t  RSVD24;
	/* 0x25 */
	__IO  uint8_t  HOP_INC;	//Hopping increment parameter
	/* 0x26 ~ 0x27 */
	__IO  uint16_t  CONN_GO;	//Connection window offset parameter in 1.25ms unit
	/* 0x28 */
	__IO  uint8_t  CONN_WS;	//Connection window size in 1.25ms unit
	/* 0x29 */
	__IO  uint8_t  RSVD29;	
	/* 0x2A ~ 0x2B */
	__IO  uint16_t  CONN_ITV;	//Connection interval in 1.25ms unit
	/* 0x2C ~ 0x2D */
	__IO  uint16_t  CONN_LTCY;	//Slave latency
	/* 0x2E ~ 0x2F */
	__IO  uint16_t  CONN_STO;		//Supervision time-out in 10ms unit
	/* 0x30 ~ 0x31 */
	__IO  uint16_t  CONN_INS;		//Connection update instant
	/* 0x32 ~ 0x33 */
	__IO  uint16_t  CONN_WO;		//Connection window offset[obsolete]
	/* 0x34 */
	__IO  uint8_t  CONN_WW_OFFSET:4;	
	__IO  uint8_t  RSVD34:4;	
	/* 0x35 */
	__IO  uint8_t  LOST_SUPER:1;	//Connection lost reason: supervision timeout
	__IO  uint8_t  LOST_WWEXT:1;	//window-widening exceed limit
	__IO  uint8_t  LOST_6NC:1;	//starting 6 packets not received
	__IO  uint8_t  LOST_INS:1;		//connection update instant invalid
	__IO  uint8_t  RSVD35:4;	
	/* 0x36 ~ 37 */
	__IO  uint16_t  CONN_WW_SETUP;	//Window-widening during guard time, in LPO clock unit		
	/* 0x38 ~ 0x39 */
	__IO  uint16_t  CONN_INS_CH;	//channel map update instant
	/* 0x3A ~ 0x3B */
	__IO  uint16_t  CONN_WW;	//Window-widening during connection, in LPO clock unit
	/* 0x3C ~ 0x3F */
	__IO  uint8_t  RSVD3C[4];
	/* 0x40 */
	__IO  uint8_t  DTM_EN:1;	//enable DTM mode
	__IO  uint8_t  DTM_MODE:1;	//DTM_TX(1), DTM_RX(0)
	__IO  uint8_t  BER_TEST:1;		//enable BER test
	__IO  uint8_t  RSVD40:5;	
	/* 0x41 */
	__IO  uint8_t  BER_LEN;		//BER test packet length
	/* 0x42 ~ 0x43 */
	__IO  uint8_t  RSVD42[2];
	/* 0x44 ~ 0x45 */
	__IO  uint16_t  DTM_RCNT;		//DTM_RX received packet counter
	/* 0x46 ~ 0x47 */
	__IO  uint16_t  DTM_TCNT;		//DTM_TX transmitted packet counter
	/* 0x48 ~ 0x4F */
	__IO  uint8_t  RSVD48[8];
	/* 0x50 */
	__IO  uint8_t  SEC_TX:1;	//Security mode enable:enable TX security
	__IO  uint8_t  SEC_RX:1;	//enable RX security
	__IO  uint8_t  RSVD50:6;	
	/* 0x51 */
	__IO  uint8_t  SEC_MIC_OK:1;	//MIC ok of current incoming packet
	__IO  uint8_t  SEC_BUSY:1;	//Security engine is busy
	__IO  uint8_t  RSVD51:6;
	/* 0x52 ~ 0x53 */
	__IO  uint8_t  RSVD52[2];
	/* 0x54 */
	__IO  uint8_t  SEC_AES_REQ:1;		//enable manual AES mode ?
	__IO  uint8_t  RSVD54:7;
	/* 0x55 */
	__IO  uint8_t  RAND_NUM;			//random number generator
	/* 0x56 ~ 0x5F */
	__IO  uint8_t  RSVD56[10];
	/* 0x60 */
	__IO  uint8_t  SCAN_EN:1;		//enable scan mode
	__IO  uint8_t  SCAN_TYPE:1;	//active(1), passive(0)
	__IO  uint8_t  INIT_EN:1;		//conn init ?
	__IO  uint8_t  RSVD60:5;	
	/* 0x61 */
	__IO  uint8_t  SCAN_ROUND;	//Round number of scan event
	/* 0x62 */
	__IO  uint8_t  CH_USER;	//User-defined channel during DTM and scan mode
	/* 0x63 */
	__IO  uint8_t  RSVD63;	
	/* 0x64 ~ 0x65 */
	__IO  uint16_t  SCAN_WINDOW;	//Scanning window in 580us unit
	/* 0x66 ~ 0x67 */
	__IO  uint16_t  SCAN_ITV;			//Scanning interval in 580us unit
	/* 0x68 ~ 0x6F */
	__IO  uint8_t  RSVD68[8];
	/* 0x70 */
	__IO  uint8_t  TH_LAST;	//Threshold of last replying packet in LPO period unit
	/* 0x71 */
	__IO  uint8_t  TH_SLEEP;	//Threshold of sleep time indicator in LPO period unit
	/* 0x72 */
	__IO  uint8_t  OVER_SLPTH;	//Timing exceeds sleep time indicator
	/* 0x73 */
	__IO  uint8_t  T_CLKWAKE;		//XO clock settling time in LPO period unit
	/* 0x74 */
	__IO  uint8_t  ADV_CH0;	//Advertising channel 0, default is channel 37
	/* 0x75 */
	__IO  uint8_t  ADV_CH1;	//Advertising channel 1, default is channel 38
	/* 0x76 */
	__IO  uint8_t  ADV_CH2;	//Advertising channel 2, default is channel 39
	/* 0x77 */
	__IO  uint8_t  DIS_LOST_LINK:1;
	__IO  uint8_t  EN_MORE_DATA:1;
	__IO  uint8_t  RSVD770:2;	
	__IO  uint8_t  EN_FW_LTCY_CHG:1;		// enable fw latency change
	__IO  uint8_t  RSVD771:3;	
	/* 0x78 */
	__IO  uint8_t  WW_MINUS1_CNT:5;	//Window-widening tuning[obsolete]
	__IO  uint8_t  RSVD78:3;	
	/* 0x79 */
	__IO  uint8_t  OVER_0P5:1;	//Window-widening tuning[obsolete]
	__IO  uint8_t  RSVD79:7;		
	/* 0x7A ~ 0x7F */
	__IO  uint8_t  RSVD7A[6];
	/* 0x80 ~ 0x85*/
	__IO  uint8_t  MAC_ADDR[6];	//Own MAC address
	/* 0x86 ~ 0x87*/
	__IO  uint8_t  RSVD86[2];
	/* 0x88 ~ 0x8B*/
	__IO  uint8_t  ACC_CODE[4];	//Own access code
	/* 0x8C ~ 0x91*/
	__IO  uint8_t  WHITE_LIST[6];	//filter addr
	/* 0x92 ~ 0x93*/
	__IO  uint8_t  RSVD92[2];
	/* 0x94 ~ 0x96*/
	__IO  uint8_t  INIT_CRC[3];	//CRC initial value
	/* 0x97*/
	__IO  uint8_t  RSVD97;
	/* 0x98 ~ 0x9C*/
	__IO  uint8_t  CHMAP[5];	//Channel map
	/* 0x9D ~ 0x9F*/
	__IO  uint8_t  RSVD9D[3];	
	/* 0xA0 ~ 0xAF*/
	__IO  uint8_t  SEC_LTK[16];	//Security long term key
	/* 0xB0 ~ 0xBF*/
	__IO  uint8_t  SEC_IV[16];		//Security initial vector	
	/* 0xC0*/
	__IO  uint8_t  TXD0;	//TXFIFO0 entry port
	/* 0xC1*/
	__IO  uint8_t  TXD1;	//TXFIFO1 entry port
	/* 0xC2 ~ 0xC3*/
	__IO  uint8_t  RSVDC2[2];
	/* 0xC4*/
	__IO  uint8_t  RXD;	//RXFIFO port
	/* 0xC5 ~ 0xC7*/
	__IO  uint8_t  RSVDC5[3];
	/* 0xC8*/
	__IO  uint8_t  TXFF_DONE;	//After writing each byte to TXFIFO, set txff_done to finish the process
	/* 0xC9*/
	__IO  uint8_t  RXFF_DONE;	//After reading bytes from RXFIFO, set rxff_done to finish the process
	/* 0xCA ~ 0xCE*/
	__IO  uint8_t  CHUPDATE[5];	//Channel map used by channel-map update
	/* 0xCF*/
	__IO  uint8_t  RSVDCF;
	/* 0xD0 ~ 0xD3 */
	__IO  uint8_t  LLC_DBG[4];	//LLC debug
} LL_CTRL_TYPE;
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
#define PWM_0_CTRL_BASE			0x50010054UL
#define PWM_1_CTRL_BASE			0x50010060UL
#define PWM_2_CTRL_BASE			0x5001006CUL
#define HPWM_CTRL_BASE			0x50010280UL
#define IR_Tx_CTRL_BASE			0x50010180UL
#define IR_Rx_CTRL_BASE			0x500101C0UL
#define BI_CTRL_BASE			0x4001007CUL
#define FLASH_CTRL_BASE		    0x40010020UL
#define TIMER_CTRL_BASE			0x50001000UL
#define H_TIMER_CTRL_BASE		0x500103C0UL
#define WDT_BASE				0x500010A0UL
#define PIN_CONFIG_BASE			0x50001060UL
#define GPO_CTRL_BASE			0x50001014UL
#define GPI_CTRL_BASE			0x50001018UL
#define GPIO_CTRL_BASE			0x50001024UL
#define GPIO_IRQ_CTRL_BASE		0x40000010UL
#define RTC_CTRL_BASE			0x500010a8UL
#define SC_7816_CTRL_BASE		0x50010200UL
#define SPI_MASTER_BASE			0x50010078UL
#define GPADC_CTRL_BASE			0x50010300UL
#define CAPDET_CTRL_BASE		0x50010100UL
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

