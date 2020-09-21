
;Define address for ram base and Depth 32K Bytes
RAM_BASE   EQU 0x00400000
RAM_LIMIT  EQU 0x00405FFF

;ICU address definitions
ICU_BASE		EQU	0x00800000
ICU_CLKSEL_LOC	EQU	0x00
ICU_CPUCLK_LOC	EQU	0x04


    IMPORT  __main                          ;C entry point 
    IMPORT  InitStack                       ;init stack
    
    EXPORT  Reset
    EXPORT __rt_div0
    EXPORT __user_initial_stackheap
    
;
    CODE32
    AREA    Init,CODE,READONLY
	ENTRY
    

Reset
;Disable all interrupts
         LDR    r0, =ICU_BASE		
         MOV	r1, #1
         STR	r1, [r0, #ICU_CLKSEL_LOC]
         MOV    r1, #0
         STR	r1, [r0, #ICU_CPUCLK_LOC]
        
;Zeros all Data's RAM
;        LDR     r0, =RAM_BASE
;        LDR     r1, =RAM_LIMIT
;        MOV     r2, #0
;ZERORAM
;        CMP     r0, r1
;        STRCC   r2, [r0], #4
;        BCC     ZERORAM

        BL      InitStack       ;

;Enable IRQ and FIQ Interrupt
	    MRS		r0,CPSR		
	    bic		r0,r0,#0xC0		
	    MSR     CPSR_c,r0

; --- Branch to C Library entry point                                        
        B       __main          ; use B not BL, because an application will never return this way

; 库函数初始化堆和栈，不能删除
__user_initial_stackheap    
        LDR     r0,=bottom_of_heap
        BX      lr ;MOV   pc,lr

; 整数除法除数为0错误处理函数，替代原始的__rt_div0减少目标代码大小
__rt_div0
        B       __rt_div0


        AREA    Myheap, DATA, NOINIT, ALIGN=2
bottom_of_heap     SPACE   256  ;

    END
;/*********************************************************************************************************
;**                            End Of File
;********************************************************************************************************/
