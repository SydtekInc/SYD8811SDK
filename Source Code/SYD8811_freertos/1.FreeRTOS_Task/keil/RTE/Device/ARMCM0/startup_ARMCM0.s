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

Stack_Size      EQU     0x00002000

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00002000

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
                DCD     SVC_Handler        ; SVCall Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     PendSV_Handler    	; PendSV Handler
                DCD     SysTick_Handler     ; SysTick Handler

                ; External Interrupts
                DCD     GPIO_IRQHandler		; 0:
                DCD     LLC_IRQHandler 		; 1:
                DCD     SPIM_IRQHandler		; 2: 
                DCD     SPIS_IRQHandler		; 3: 
                DCD     I2CM0_IRQHandler		; 4: 
                DCD     I2CM1_IRQHandler		; 5: 					
                DCD     UART0_IRQHandler		; 6: 
                DCD     UART2_IRQHandler		; 7: 
                DCD     I2CS_IRQHandler		; 8: 
                DCD     TIMER0_IRQHandler	; 9: 
                DCD     TIMER1_IRQHandler	; 10:
                DCD     TIMER2_IRQHandler	; 11:
                DCD     TIMER3_IRQHandler	; 12:                
                DCD		TIMER4_IRQHandler	; 13:	
                DCD     WDT_IRQHandler		; 14:
                DCD     SW_IRQHandler		; 15: 
                DCD     PWM1_IRQHandler		; 16: 
                DCD     PWM2_IRQHandler		; 17: 
                DCD     PWM3_IRQHandler 		; 18: 
                DCD     M2M_IRQHandler		; 19: 
                DCD     RTC_IRQHandler 		; 20: 
                DCD     ISO_7816_IRQHandler 	; 21: 
                DCD     IR_IRQHandler 		; 22: 
                DCD     TRNG_IRQHandler		; 23: 
                DCD     GPADC_IRQHandler	; 24: 
                DCD     UART1_IRQHandler		; 25: 
                DCD     CAPDET_IRQHandler	; 26: 
                DCD     PDM_IRQHandler		; 27: 
                DCD     LLC2_IRQHandler		; 28: 
                DCD     LLC3_IRQHandler		; 29: 
                DCD     I2S_IRQHandler		; 30: 
                DCD     INTCOMB_IRQHandler	; 31: 
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
             EXPORT		GPIO_IRQHandler			[WEAK]
             EXPORT		LLC_IRQHandler			[WEAK]
             EXPORT		SPIM_IRQHandler			[WEAK]
             EXPORT		SPIS_IRQHandler			[WEAK]
             EXPORT		I2CM0_IRQHandler	    [WEAK]
             EXPORT		I2CM1_IRQHandler		[WEAK]				
             EXPORT		UART0_IRQHandler		[WEAK]
             EXPORT		UART2_IRQHandler		[WEAK]
             EXPORT		I2CS_IRQHandler			[WEAK]
             EXPORT		TIMER0_IRQHandler		[WEAK]
             EXPORT		TIMER1_IRQHandler		[WEAK]
             EXPORT		TIMER2_IRQHandler		[WEAK]
             EXPORT		TIMER3_IRQHandler		[WEAK]         
             EXPORT		TIMER4_IRQHandler		[WEAK]
             EXPORT		WDT_IRQHandler			[WEAK]
             EXPORT		SW_IRQHandler			[WEAK]
             EXPORT		PWM1_IRQHandler			[WEAK]
             EXPORT		PWM2_IRQHandler			[WEAK]
             EXPORT		PWM3_IRQHandler			[WEAK]
             EXPORT		M2M_IRQHandler			[WEAK]
             EXPORT		RTC_IRQHandler			[WEAK]
             EXPORT		ISO_7816_IRQHandler		[WEAK]
             EXPORT		IR_IRQHandler			[WEAK]
             EXPORT		TRNG_IRQHandler			[WEAK]
             EXPORT		GPADC_IRQHandler		[WEAK]
             EXPORT		UART1_IRQHandler		[WEAK]
             EXPORT		CAPDET_IRQHandler		[WEAK]
             EXPORT		PDM_IRQHandler			[WEAK]
             EXPORT		LLC2_IRQHandler			[WEAK]
             EXPORT		LLC3_IRQHandler			[WEAK]
             EXPORT		I2S_IRQHandler			[WEAK]
             EXPORT		INTCOMB_IRQHandler		[WEAK]

GPIO_IRQHandler		
LLC_IRQHandler		
SPIM_IRQHandler		
SPIS_IRQHandler		
I2CM0_IRQHandler	
I2CM1_IRQHandler					
UART0_IRQHandler	
UART2_IRQHandler	
I2CS_IRQHandler		
TIMER0_IRQHandler	
TIMER1_IRQHandler	
TIMER2_IRQHandler	
TIMER3_IRQHandler	         
TIMER4_IRQHandler	
WDT_IRQHandler		
SW_IRQHandler		
PWM1_IRQHandler		
PWM2_IRQHandler		
PWM3_IRQHandler		
M2M_IRQHandler		
RTC_IRQHandler		
ISO_7816_IRQHandler
IR_IRQHandler		
TRNG_IRQHandler		
GPADC_IRQHandler	
UART1_IRQHandler	
CAPDET_IRQHandler	
PDM_IRQHandler		
LLC2_IRQHandler		
LLC3_IRQHandler		
I2S_IRQHandler		
INTCOMB_IRQHandler	
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
