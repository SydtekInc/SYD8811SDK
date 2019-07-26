;/**************************************************************************//**
; * @file     startup_ARMCM0.s
; * @brief    CMSIS Core Device Startup File for
; *           ARMCM0 Device Series
; * @version  V1.08
; * @date     23. November 2012
; *
; * @note
; *
; ******************************************************************************/
;/* Copyright (c) 2011 - 2012 ARM LIMITED
;
;   All rights reserved.
;   Redistribution and use in source and binary forms, with or without
;   modification, are permitted provided that the following conditions are met:
;   - Redistributions of source code must retain the above copyright
;     notice, this list of conditions and the following disclaimer.
;   - Redistributions in binary form must reproduce the above copyright
;     notice, this list of conditions and the following disclaimer in the
;     documentation and/or other materials provided with the distribution.
;   - Neither the name of ARM nor the names of its contributors may be used
;     to endorse or promote products derived from this software without
;     specific prior written permission.
;   *
;   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
;   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
;   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
;   ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
;   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
;   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
;   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
;   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
;   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
;   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
;   POSSIBILITY OF SUCH DAMAGE.
;   ---------------------------------------------------------------------------*/
;/*
;//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
;*/


; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00000400

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000C00

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit


                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       DCD     __initial_sp              ; Top of Stack
                DCD     Reset_Handler             ; Reset Handler
                DCD     NMI_Handler               ; NMI Handler
                DCD     HardFault_Handler         ; Hard Fault Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler               ; SVCall Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV Handler
                DCD     SysTick_Handler           ; SysTick Handler

                ; External Interrupts
                DCD     0 							;  0:  Reserved
                DCD     LLC_IRQHandler				;  1:  LLC
                DCD     RTC_IRQHandler				;  2:  RTC
                DCD     SW_IRQHandler				;  3:  SW
                DCD     I2C0_IRQHandler        	 	;  4:  I2C0
                DCD     I2C1_IRQHandler         	;  5:  I2C1
                DCD     UART0_IRQHandler			;  6:  UART0
                DCD     UART1_IRQHandler			;  7:  UART1
                DCD     TIMER0_IRQHandler     		;  8:  TIMER0
                DCD     TIMER1_IRQHandler     		;  9:  TIMER1
                DCD     TIMER2_IRQHandler 			; 10:  TIMER2
                DCD     TIMER3_IRQHandler 			; 11:  TIMER3
				DCD     GPIO_IRQHandler				; 12:  GPIO
                DCD     HID_IRQHandler				; 13:  HID
                DCD     SPIM_IRQHandler				; 14:  SPIM
                DCD     CAP_IRQHandler				; 15:  CAP
                DCD     GPADC_IRQHandler			; 16:  GPADC
                DCD     LLC2_IRQHandler				; 17:  LLC2
                DCD     ISO_7816_IRQHandler			; 18:  SC
                DCD     IR_Tx_IRQHandler			; 19:  IR_Tx
                DCD     TOUCH_IRQHandler			; 20:  TOUCH
                DCD     HPWM_IRQHandler				; 21:  HPWM
                DCD     HTIMER_IRQHandler			; 22:  HTIMER
                DCD     IR_Rx_IRQHandler			; 23:  IR_Rx
                DCD     0                       	; 24: Reserved
                DCD     0                       	; 25: Reserved
                DCD     0                       	; 26: Reserved
                DCD     0                       	; 27: Reserved
                DCD     0       					; 28: Reserved
                DCD     0                       	; 29: Reserved
                DCD     0         					; 30: Reserved
                DCD     0            				; 31: Reserved
__Vectors_End

__Vectors_Size  EQU     __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY


; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  SystemInit
                IMPORT  __main
                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__main
                BX      R0
                ENDP


; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler               [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler         [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler               [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler            [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler           [WEAK]
                B       .
                ENDP

Default_Handler PROC
                EXPORT  LLC_IRQHandler		[WEAK]
                EXPORT  RTC_IRQHandler		[WEAK]
                EXPORT  SW_IRQHandler		[WEAK]
                EXPORT  I2C0_IRQHandler		[WEAK]
                EXPORT  I2C1_IRQHandler		[WEAK]
                EXPORT  UART0_IRQHandler		[WEAK]
                EXPORT  UART1_IRQHandler		[WEAK]
                EXPORT  TIMER0_IRQHandler		[WEAK]
                EXPORT  TIMER1_IRQHandler		[WEAK]
                EXPORT  TIMER2_IRQHandler		[WEAK] 
                EXPORT  TIMER3_IRQHandler		[WEAK]
                EXPORT  GPIO_IRQHandler		[WEAK]
                EXPORT  HID_IRQHandler		[WEAK]
                EXPORT  SPIM_IRQHandler		[WEAK]
                EXPORT  CAP_IRQHandler		[WEAK]
                EXPORT  GPADC_IRQHandler		[WEAK]
                EXPORT  LLC2_IRQHandler		[WEAK]
                EXPORT  ISO_7816_IRQHandler		[WEAK]
                EXPORT  IR_Tx_IRQHandler		[WEAK]
                EXPORT  TOUCH_IRQHandler		[WEAK]
                EXPORT  HPWM_IRQHandler		[WEAK]	
                EXPORT  HTIMER_IRQHandler		[WEAK]
                EXPORT  IR_Rx_IRQHandler		[WEAK]

LLC_IRQHandler
RTC_IRQHandler
SW_IRQHandler
I2C0_IRQHandler
I2C1_IRQHandler
UART0_IRQHandler
UART1_IRQHandler
TIMER0_IRQHandler
TIMER1_IRQHandler
TIMER2_IRQHandler 
TIMER3_IRQHandler
GPIO_IRQHandler
HID_IRQHandler
SPIM_IRQHandler
CAP_IRQHandler
GPADC_IRQHandler
LLC2_IRQHandler
ISO_7816_IRQHandler
IR_Tx_IRQHandler
TOUCH_IRQHandler
HPWM_IRQHandler	
HTIMER_IRQHandler
IR_Rx_IRQHandler
                B       .

                ENDP


                ALIGN


; User Initial Stack & Heap

                IF      :DEF:__MICROLIB

                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit

                ELSE

                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap

__user_initial_stackheap PROC
                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR
                ENDP

                ALIGN

                ENDIF


                END
