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
	PendSV_IRQn                   	=  -2,      /*!< 14 Pend SV Interrupt               */
	SysTick_IRQn                  	=  -1,      /*!< 15 System Tick Interrupt           */
/* ----------------------  ARMCM0 Specific Interrupt Numbers  --------------------- */	
	LLC_IRQn                    	=   1,      /*!< LLC Interrupt                    */
	I2C0_IRQn                    	=   4,      /*!< I2C0 Interrupt                    */
	I2C1_IRQn                    	=   5,      /*!< I2C1 Interrupt                    */
	UART0_IRQn                    	=   6,      /*!< UART0 Interrupt                    */
	UART1_IRQn                    	=   7,      /*!< UART1 Interrupt                    */
	TIMER0_IRQn                    	=   8,      /*!< TIMER0 Interrupt                    */
	TIMER1_IRQn                    	=   9, 	 /*!< TIMER1 Interrupt                    */
	TIMER2_IRQn                    	=   10,      /*!< TIMER2 Interrupt                    */
	TIMER3_IRQn                    	=   11,      /*!< TIMER3 Interrupt                    */
	GPIO_IRQn                    	=   12,      /*!< GPIO Interrupt                    */
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
#define BIT18 				0x40000
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
	PIN_SEL_GENERAL_GPIO		= 0x00,
	PIN_SEL_ANALOG_INPUT		= 0x01,
	PIN_SEL_SPI_0_CLOCK		= 0x01,
	PIN_SEL_SPI_0_DATA_IN		= 0x01,
	PIN_SEL_SPI_0_CSN			= 0x01,
	PIN_SEL_SPI_0_DATA_OUT	= 0x01,
	PIN_SEL_SPI_1_CLOCK		= 0x01,
	PIN_SEL_SPI_1_DATA_IN		= 0x01,
	PIN_SEL_SPI_1_CSN			= 0x01,
	PIN_SEL_SPI_1_DATA_OUT	= 0x01,
	PIN_SEL_MOUSE_MOTION_IN	= 0x01,
	PIN_SEL_MOUSE_KEY_L		= 0x01,
	PIN_SEL_MOUSE_KEY_R		= 0x01,
	PIN_SEL_MOUSE_KEY_M		= 0x01,
	PIN_SEL_MOUSE_KEY_CPI	= 0x01,
	PIN_SEL_MOUSE_KEY_B4		= 0x01,
	PIN_SEL_MOUSE_KEY_B5		= 0x01,
	PIN_SEL_MOUSE_KEY_Z1		= 0x01,
	PIN_SEL_MOUSE_KEY_Z2		= 0x01,
	PIN_SEL_MOUSE_KEY_T1		= 0x01,
	PIN_SEL_MOUSE_KEY_T2		= 0x01,
	PIN_SEL_I2C_0_CLOCK		= 0x03,
	PIN_SEL_I2C_0_DATA		= 0x03,
	PIN_SEL_I2C_1_CLOCK		= 0x03,
	PIN_SEL_I2C_1_DATA		= 0x03,	
	PIN_SEL_UART_0_RXD		= 0x04,	
	PIN_SEL_UART_0_TXD		= 0x04,	
	PIN_SEL_UART_0_CTS		= 0x04,	
	PIN_SEL_UART_0_RTS		= 0x04,	
	PIN_SEL_UART_1_RXD		= 0x04,	
	PIN_SEL_UART_1_TXD		= 0x04,	
	PIN_SEL_PWM_0				= 0x05,	
	PIN_SEL_PWM_1				= 0x05,	
	PIN_SEL_PWM_2				= 0x05,	
	PIN_PULL_UP				= 0x01,
	PIN_FLOATINF				= 0x00,
	PIN_SET_INPUT				= 0x01, 
	PIN_SET_OUTPUT			= 0x00,
	PIN_INPUT_IVERTED			= 0x01,
	PIN_INPUT_NOT_IVERTED	= 0x00,
};
/* ============================ PIN CONFIG ========================= */
typedef union{
	struct {
			/* 0x00  */
			__IO  uint8_t  PIN_0_SEL:4;
			__IO  uint8_t  PIN_1_SEL:4;
			/* 0x01  */
			__IO  uint8_t  PIN_2_SEL:4;
			__IO  uint8_t  PIN_3_SEL:4;
			/* 0x02  */
			__IO  uint8_t  PIN_4_SEL:4;
			__IO  uint8_t  PIN_5_SEL:4;
			/* 0x03  */
			__IO  uint8_t  PIN_6_SEL:4;
			__IO  uint8_t  PIN_7_SEL:4;
			/* 0x04  */
			__IO  uint8_t  PIN_8_SEL:4;
			__IO  uint8_t  PIN_9_SEL:4;
			/* 0x05  */
			__IO  uint8_t  PIN_10_SEL:4;
			__IO  uint8_t  PIN_11_SEL:4;
			/* 0x06  */
			__IO  uint8_t  PIN_12_SEL:4;
			__IO  uint8_t  PIN_13_SEL:4;
			/* 0x07  */
			__IO  uint8_t  PIN_14_SEL:4;
			__IO  uint8_t  PIN_15_SEL:4;
			/* 0x08  */
			__IO  uint8_t  PIN_16_SEL:4;
			__IO  uint8_t  PIN_17_SEL:4;
			/* 0x09  */
			__IO  uint8_t  PIN_18_SEL:4;
			__IO  uint8_t  PIN_19_SEL:4;
			/* 0x0A  */
			__IO  uint8_t  PIN_20_SEL:4;
			__IO  uint8_t  PIN_21_SEL:4;
			/* 0x0B  */
			__IO  uint8_t  PIN_22_SEL:4;
			__IO  uint8_t  PIN_23_SEL:4;
			/* 0x0C  */
			__IO  uint8_t  PIN_24_SEL:4;
			__IO  uint8_t  PIN_25_SEL:4;
			/* 0x0D */
			__IO  uint8_t  PIN_26_SEL:4;
			__IO  uint8_t  PIN_27_SEL:4;	
			/* 0x0E */
			__IO  uint8_t  PIN_28_SEL:4;
			__IO  uint8_t  PIN_29_SEL:4;	
			/* 0x0F */
			__IO  uint8_t  PIN_30_SEL:4;
			__IO  uint8_t  PIN_31_SEL:4;	
			/* 0x10 ~ 0x33 */	
			__IO  uint8_t  RSVD00[36];
			/* 0x34 */	
			__IO  uint8_t  PIN_0_PULL_UP:1;
			__IO  uint8_t  PIN_1_PULL_UP:1;
			__IO  uint8_t  PIN_2_PULL_UP:1;
			__IO  uint8_t  PIN_3_PULL_UP:1;
			__IO  uint8_t  PIN_4_PULL_UP:1;
			__IO  uint8_t  PIN_5_PULL_UP:1;
			__IO  uint8_t  PIN_6_PULL_UP:1;
			__IO  uint8_t  PIN_7_PULL_UP:1;
			/* 0x35 */	
			__IO  uint8_t  PIN_8_PULL_UP:1;
			__IO  uint8_t  PIN_9_PULL_UP:1;
			__IO  uint8_t  PIN_10_PULL_UP:1;
			__IO  uint8_t  PIN_11_PULL_UP:1;
			__IO  uint8_t  PIN_12_PULL_UP:1;
			__IO  uint8_t  PIN_13_PULL_UP:1;
			__IO  uint8_t  PIN_14_PULL_UP:1;
			__IO  uint8_t  PIN_15_PULL_UP:1;
			/* 0x36 */	
			__IO  uint8_t  PIN_16_PULL_UP:1;
			__IO  uint8_t  PIN_17_PULL_UP:1;
			__IO  uint8_t  PIN_18_PULL_UP:1;
			__IO  uint8_t  PIN_19_PULL_UP:1;
			__IO  uint8_t  PIN_20_PULL_UP:1;
			__IO  uint8_t  PIN_21_PULL_UP:1;
			__IO  uint8_t  PIN_22_PULL_UP:1;
			__IO  uint8_t  PIN_23_PULL_UP:1;
			/* 0x37 */	
			__IO  uint8_t  PIN_24_PULL_UP:1;
			__IO  uint8_t  PIN_25_PULL_UP:1;
			__IO  uint8_t  PIN_26_PULL_UP:1;
			__IO  uint8_t  PIN_27_PULL_UP:1;
			__IO  uint8_t  PIN_28_PULL_UP:1;
			__IO  uint8_t  PIN_29_PULL_UP:1;
			__IO  uint8_t  PIN_30_PULL_UP:1;
			__IO  uint8_t  PIN_31_PULL_UP:1;
			/* 0x38 ~ 0x4b */	
			__IO  uint8_t  RSVD01[20];
			/* 0x4c */	
			__IO  uint8_t  PIN_0_POL:1;
			__IO  uint8_t  PIN_1_POL:1;
			__IO  uint8_t  PIN_2_POL:1;
			__IO  uint8_t  PIN_3_POL:1;
			__IO  uint8_t  PIN_4_POL:1;
			__IO  uint8_t  PIN_5_POL:1;
			__IO  uint8_t  PIN_6_POL:1;
			__IO  uint8_t  PIN_7_POL:1;
			/* 0x4d */	
			__IO  uint8_t  PIN_8_POL:1;
			__IO  uint8_t  PIN_9_POL:1;
			__IO  uint8_t  PIN_10_POL:1;
			__IO  uint8_t  PIN_11_POL:1;
			__IO  uint8_t  PIN_12_POL:1;
			__IO  uint8_t  PIN_13_POL:1;
			__IO  uint8_t  PIN_14_POL:1;
			__IO  uint8_t  PIN_15_POL:1;
			/* 0x4e */	
			__IO  uint8_t  PIN_16_POL:1;
			__IO  uint8_t  PIN_17_POL:1;
			__IO  uint8_t  PIN_18_POL:1;
			__IO  uint8_t  PIN_19_POL:1;
			__IO  uint8_t  PIN_20_POL:1;
			__IO  uint8_t  PIN_21_POL:1;
			__IO  uint8_t  PIN_22_POL:1;
			__IO  uint8_t  PIN_23_POL:1;
			/* 0x4f */	
			__IO  uint8_t  PIN_24_POL:1;
			__IO  uint8_t  PIN_25_POL:1;
			__IO  uint8_t  PIN_26_POL:1;
			__IO  uint8_t  PIN_27_POL:1;
			__IO  uint8_t  PIN_28_POL:1;
			__IO  uint8_t  PIN_29_POL:1;
			__IO  uint8_t  PIN_30_POL:1;
			__IO  uint8_t  PIN_31_POL:1;
			/* 0x50 */	
			__IO  uint8_t  PIN_0_DIR:1;
			__IO  uint8_t  PIN_1_DIR:1;
			__IO  uint8_t  PIN_2_DIR:1;
			__IO  uint8_t  PIN_3_DIR:1;
			__IO  uint8_t  PIN_4_DIR:1;
			__IO  uint8_t  PIN_5_DIR:1;
			__IO  uint8_t  PIN_6_DIR:1;
			__IO  uint8_t  PIN_7_DIR:1;
			/* 0x51 */	
			__IO  uint8_t  PIN_8_DIR:1;
			__IO  uint8_t  PIN_9_DIR:1;
			__IO  uint8_t  PIN_10_DIR:1;
			__IO  uint8_t  PIN_11_DIR:1;
			__IO  uint8_t  PIN_12_DIR:1;
			__IO  uint8_t  PIN_13_DIR:1;
			__IO  uint8_t  PIN_14_DIR:1;
			__IO  uint8_t  PIN_15_DIR:1;
			/* 0x52 */	
			__IO  uint8_t  PIN_16_DIR:1;
			__IO  uint8_t  PIN_17_DIR:1;
			__IO  uint8_t  PIN_18_DIR:1;
			__IO  uint8_t  PIN_19_DIR:1;
			__IO  uint8_t  PIN_20_DIR:1;
			__IO  uint8_t  PIN_21_DIR:1;
			__IO  uint8_t  PIN_22_DIR:1;
			__IO  uint8_t  PIN_23_DIR:1;
			/* 0x53 */	
			__IO  uint8_t  PIN_24_DIR:1;
			__IO  uint8_t  PIN_25_DIR:1;
			__IO  uint8_t  PIN_26_DIR:1;
			__IO  uint8_t  PIN_27_DIR:1;
			__IO  uint8_t  PIN_28_DIR:1;
			__IO  uint8_t  PIN_29_DIR:1;
			__IO  uint8_t  PIN_30_DIR:1;
			__IO  uint8_t  PIN_31_DIR:1;
	};
	struct
	{
		/* 0x2C~0x2F */
		__IO  uint32_t  GPIOSEL[4];
		/* 0x10 ~ 0x33 */	
		__IO  uint8_t  RSVD02[36];
		/* 0x5C~0x5F */
		__IO  uint32_t  GPIO_PULL_UP;
				/* 0x38 ~ 0x4b */	
		__IO  uint8_t  RSVD03[20];
		__IO  uint32_t  GPIO_POL;
		/* 0x60~0x63 */
		__IO  uint32_t  GPIODIR;
	};
} PIN_CONFIG_TYPE;
/* ============================ GPIO ========================= */
typedef union{
	struct {
		/* 0x00  */	
		__IO  uint8_t  GPI_0:1;
		__IO  uint8_t  GPI_1:1;
		__IO  uint8_t  GPI_2:1;
		__IO  uint8_t  GPI_3:1;
		__IO  uint8_t  GPI_4:1;
		__IO  uint8_t  GPI_5:1;
		__IO  uint8_t  GPI_6:1;
		__IO  uint8_t  GPI_7:1;
		/* 0x35 */	
		__IO  uint8_t  GPI_8:1;
		__IO  uint8_t  GPI_9:1;
		__IO  uint8_t  GPI_10:1;
		__IO  uint8_t  GPI_11:1;
		__IO  uint8_t  GPI_12:1;
		__IO  uint8_t  GPI_13:1;
		__IO  uint8_t  GPI_14:1;
		__IO  uint8_t  GPI_15:1;
		/* 0x36 */	
		__IO  uint8_t  GPI_16:1;
		__IO  uint8_t  GPI_17:1;
		__IO  uint8_t  GPI_18:1;
		__IO  uint8_t  GPI_19:1;
		__IO  uint8_t  GPI_20:1;
		__IO  uint8_t  GPI_21:1;
		__IO  uint8_t  GPI_22:1;
		__IO  uint8_t  GPI_23:1;
		/* 0x37 */	
		__IO  uint8_t  GPI_24:1;
		__IO  uint8_t  GPI_25:1;
		__IO  uint8_t  GPI_26:1;
		__IO  uint8_t  GPI_27:1;
		__IO  uint8_t  GPI_28:1;
		__IO  uint8_t  GPI_29:1;
		__IO  uint8_t  GPI_30:1;
		__IO  uint8_t  GPI_31:1;
	};
	__IO  uint32_t  GPI;
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
		/* 0x35 */	
		__IO  uint8_t  GPO_8:1;
		__IO  uint8_t  GPO_9:1;
		__IO  uint8_t  GPO_10:1;
		__IO  uint8_t  GPO_11:1;
		__IO  uint8_t  GPO_12:1;
		__IO  uint8_t  GPO_13:1;
		__IO  uint8_t  GPO_14:1;
		__IO  uint8_t  GPO_15:1;
		/* 0x36 */	
		__IO  uint8_t  GPO_16:1;
		__IO  uint8_t  GPO_17:1;
		__IO  uint8_t  GPO_18:1;
		__IO  uint8_t  GPO_19:1;
		__IO  uint8_t  GPO_20:1;
		__IO  uint8_t  GPO_21:1;
		__IO  uint8_t  GPO_22:1;
		__IO  uint8_t  GPO_23:1;
		/* 0x37 */	
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
/* ============================ UART =========================== */
typedef struct {
	__IO  uint8_t  BAUDSEL:4;
	__IO  uint8_t  R1:1;
	__IO  uint8_t  T1:1;
	__IO  uint8_t  INT_MASK:1;
	__IO  uint8_t  FLOW:1;
	__IO  uint8_t  SUB;
} UART_CTRL_TYPE;
/* ============================ I2C =========================== */
typedef struct {
	__IO  uint16_t  ADDRESS;   //address low byte AND HIGH byte  对于eeprom这里是内存地址
	__IO  uint8_t  RSVD0:1;
	__IO  uint8_t  ID:7;		//the control byte for SLAVE. The 1st byte write to slave except the LSB, the LSB is the read/write signal.
	__IO  uint8_t  SPEED;
	__IO  uint8_t  BUSY:1;
	__IO  uint8_t  ERR:1;
	__IO  uint8_t  ERR_FLG:1;
	__IO  uint8_t  DONE_FLG:1;
	__IO  uint8_t  READ:1;
	__IO  uint8_t  WRITE:1;
	__IO  uint8_t  ADDR_1:1;   //ADDR1 : address 1 byte mode. 1:1 byte EEPROM address 0:2 byte EEPROM address
	__IO  uint8_t  RSTB:1;     //I2C_DATA_CNT : I2C data number. It means how many bytes to read/write."0" means read/write 1 byte; "1" means read/write 2 byte;
	__IO  uint8_t  DATA_CNT:5;
	__IO  uint8_t  RSVD1:1;
	__IO  uint8_t  RSVD2:1;
	__IO  uint8_t  RSVD3:1;
} I2C_CTRL_TYPE;

typedef struct {
	__IO  uint8_t  TX[32];
} I2C_TXD_TYPE;

typedef struct {
	__IO  uint8_t  RX[32];
} I2C_RXD_TYPE;
/* ============================ GPIO =========================== */
typedef struct {
	/* 0x10 ~0x13 */
	__IO  uint32_t  GPIO_INT_CLR;   //中断清除寄存器
	/* 0x14 ~ 0x1F*/
	__IO  uint8_t  RSVD14[12];
	/* 0x20 ~0x23 */
	__IO  uint32_t  GPIO_INT_MSK;   //中断屏蔽寄存器
	/* 0x24 ~ 0x27*/
	__IO  uint8_t  RSVD24[4];
	/* 0x28 ~0x2B */
	__IO  uint32_t  GPIO_INT;     //中断状态寄存器
	/* 0x2C ~ 0x2F*/
	__IO  uint8_t  RSVD2C[4];
	/* 0x30 */
	__IO  uint8_t  GPIO_TOP_INT_MSK:1;   //全局中断屏蔽寄存器
	__IO  uint8_t  RSVD30:7;	
	/* 0x31 ~ 0x53*/
	//__IO  uint8_t  RSVD31[35];
	/* 0x54 ~0x57 */
	//__IO  uint32_t  GPIO_DEB;
	/* 0x58 ~0x5B */
	//__IO  uint32_t  GPIO_DIR;	
	/* 0x5C ~0x5F */
	//__IO  uint32_t  GPIO_EDGE_TRIG;	
	/* 0x60 ~0x63 */
	//__IO  uint32_t  GPIO_RISE_TRIG;	
	/* 0x64 ~ 0x67*/
	//__IO  uint8_t  RSVD64[4];
	/* 0x68 ~0x6B */
	//__IO  uint32_t  GPIO_POL;
} GPIO_IRQ_CTRL_TYPE;
/* ============================ TIMER =========================== */
typedef struct
{
	/* 0x00~0x2F */
	//__IO  uint8_t  RSVD00[48];
	/* 0x30 */
	__IO  uint8_t  TIMER_0_EN:1;
	__IO  uint8_t  TIMER_1_EN:1;
	__IO  uint8_t  TIMER_2_EN:1;
	__IO  uint8_t  TIMER_3_EN:1;
	__IO  uint8_t  TIMER_0_RGLR:1;
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
	__IO  uint8_t  TIMER_0_INT_MASK:1;
	__IO  uint8_t  TIMER_1_INT_MASK:1;
	__IO  uint8_t  TIMER_2_INT_MASK:1;
	__IO  uint8_t  TIMER_3_INT_MASK:1;
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
} TIMER_CTRL_TYPE;
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
	/* 0x01 ~ 0x03*/
	__IO  uint8_t  RSVD01[3];
	/* 0x04 ~ 0x05*/
	__IO  uint16_t  WDT_TIME;
}WDT_CTRL_TYPE;

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
#define UART_0_CTRL_BASE		0x40010050UL
#define UART_1_CTRL_BASE		0x400100D0UL
#define I2C_0_CTRL_BASE			0x40010000UL
#define I2C_0_TXD_BASE			0x40010010UL
#define I2C_0_RXD_BASE			0x40010030UL
#define I2C_1_CTRL_BASE			0x40010080UL
#define I2C_1_TXD_BASE			0x40010090UL
#define I2C_1_RXD_BASE			0x400100B0UL
#define PWM_0_CTRL_BASE		0x40010054UL
#define PWM_1_CTRL_BASE		0x40010060UL
#define PWM_2_CTRL_BASE		0x4001006CUL
#define BI_CTRL_BASE			0x4001007CUL
#define GPIO_IRQ_CTRL_BASE		0x40000010UL
#define FLASH_CTRL_BASE		0x50001000UL
#define TIMER_CTRL_BASE		0x50001030UL
#define WDT_BASE				0x50001074UL
#define PIN_CONFIG_BASE		0x50001010UL
#define GPI_CTRL_BASE			0x4000000CUL
#define GPO_CTRL_BASE			0x5000102CUL
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


#ifdef __cplusplus
}
#endif

#endif  /* ARMCM0_H */

