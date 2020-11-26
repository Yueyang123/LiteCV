;/*********************** (C) COPYRIGHT 2010 Libraworks *************************
;* File Name	: os_cpu_a.asm 
;* Author		: Librae 
;* Version		: V1.0
;* Date			: 06/10/2010
;* Description	: 关于STM32的底层代码提供
;*******************************************************************************/

		IMPORT  OSRunning               ; 引入外界的变量
        IMPORT  OSPrioCur
        IMPORT  OSPrioHighRdy
        IMPORT  OSTCBCur
        IMPORT  OSTCBHighRdy
        IMPORT  OSIntNesting
        IMPORT  OSIntExit
        IMPORT  OSTaskSwHook
           
        EXPORT  OSStartHighRdy               
        EXPORT  OSCtxSw
        EXPORT  OSIntCtxSw
		EXPORT  OS_CPU_SR_Save         ; 向外部提供的函数
    	EXPORT  OS_CPU_SR_Restore       
        EXPORT  PendSV_Handler
        	
     
NVIC_INT_CTRL   	EQU     0xE000ED04  ; 中断控制寄存器的地址
NVIC_SYSPRI2    	EQU     0xE000ED20  ; 系统优先级寄存器
NVIC_PENDSV_PRI 	EQU     0xFFFF0000  ; PendSV的优先级（最低）
                                        ;
NVIC_PENDSVSET  	EQU     0x10000000  ; 触发PendSV中断的数值


		PRESERVE8 
		
		AREA    |.text|, CODE, READONLY
        THUMB 
    
           

;********************************************************************************************************
;                                   CRITICAL SECTION METHOD 3 FUNCTIONS
;
; Description: Disable/Enable interrupts by preserving the state of interrupts.  Generally speaking you
;              would store the state of the interrupt disable flag in the local variable 'cpu_sr' and then
;              disable interrupts.  'cpu_sr' is allocated in all of uC/OS-II's functions that need to
;              disable interrupts.  You would restore the interrupt disable state by copying back 'cpu_sr'
;              into the CPU's status register.
;
; Prototypes :     OS_CPU_SR  OS_CPU_SR_Save(void);
;                  void       OS_CPU_SR_Restore(OS_CPU_SR cpu_sr);
;
;
; Note(s)    : 1) These functions are used in general like this:
;
;                 void Task (void *p_arg)
;                 {
;                 #if OS_CRITICAL_METHOD == 3          /* Allocate storage for CPU status register */
;                     OS_CPU_SR  cpu_sr;
;                 #endif
;
;                          :
;                          :
;                     OS_ENTER_CRITICAL();             /* cpu_sr = OS_CPU_SaveSR();                */
;                          :
;                          :
;                     OS_EXIT_CRITICAL();              /* OS_CPU_RestoreSR(cpu_sr);                */
;                          :
;                          :
;                 }
;********************************************************************************************************

OS_CPU_SR_Save
    MRS     R0, PRIMASK  	;加载PRIMASK寄存器地址
    CPSID   I				;PRIMASK=1,关闭所有中断（除了nmi and hardfault）
    BX      LR			    ;返回

OS_CPU_SR_Restore
    MSR     PRIMASK, R0	   	;
    BX      LR				;



;********************************************************************************************************
;                                          START MULTITASKING  开始任务
;                                       void OSStartHighRdy(void) 
;
; Note(s) : 1) This function triggers a PendSV exception (essentially, causes a context switch) to cause
;              the first task to start.函数触发PendSV异常（从本质上讲,是导致上下文切换）导致第一个任务开始
;
;           2) OSStartHighRdy() MUST: 关键流程
;              a) Setup PendSV exception priority to lowest;
;									设置PendSV异常优先级到最低
;              b) Set initial PSP to 0, to tell context switcher this is first run;
;									设置初始进程堆栈到0位置，目的是告诉上下文/任务切换器这个函数第一个执行
;              c) Set OSRunning to TRUE;
;									设置OSRunning标志为TRUE
;              d) Trigger PendSV exception;
;									切换PendSV异常
;              e) Enable interrupts (tasks will run with interrupts enabled).
;									使能中断（任务将通过启用中断运行）
;               其通过OSSTart()完成调用
;********************************************************************************************************
 

OSStartHighRdy
        LDR     R4, =NVIC_SYSPRI2      ; set the PendSV exception priority
        LDR     R5, =NVIC_PENDSV_PRI
        STR     R5, [R4]

        MOV     R4, #0                 ; set the PSP to 0 for initial context switch call
        MSR     PSP, R4                ; 将PSP指针拨到空闲任务的开始位置
                                       ; PENDSV回去执行PendSV_Handler_Nosave
        LDR     R4, =OSRunning         ; OSRunning = TRUE
        MOV     R5, #1                 ; 告诉系统开始运行
        STRB    R5, [R4]

                                       ;
        LDR     R4, =NVIC_INT_CTRL     ;trigger the PendSV exception (causes context switch)
        LDR     R5, =NVIC_PENDSVSET    ;触发PENDSV中断
        STR     R5, [R4]

        CPSIE   I                      ;enable interrupts at processor level
OSStartHang
        B       OSStartHang            ;should never get here


;********************************************************************************************************
;                               PERFORM A CONTEXT SWITCH (From task level) 从任务级执行一个上下文切换
;                                           void OSCtxSw(void)
;
; Note(s) : 1) OSCtxSw() is called when OS wants to perform a task context switch.  This function
;              triggers the PendSV exception which is where the real work is done.
;OSCtxSw 和 OSIntCtxSw 这两个是用来做任务切换的，这两个看起来都是一样的，其实它
;们都只是触发一个 PendSV 中断，具体的切换过程在 PendSV 中断服务函数里面进行。这两个
;函数看起来是一样的，但是他们的意义是不同的，OSCtxSw 是任务级切换，比如从任务 A 切换
;********************************************************************************************************

OSCtxSw
		PUSH    {R4, R5}
        LDR     R4, =NVIC_INT_CTRL  	;中断控制寄存器所在的地址 (causes context switch)
        LDR     R5, =NVIC_PENDSVSET
        STR     R5, [R4]
		POP     {R4, R5}
        BX      LR

;中断切换到任务
OSIntCtxSw
		PUSH    {R4, R5}
        LDR     R4, =NVIC_INT_CTRL
        LDR     R5, =NVIC_PENDSVSET
        STR     R5, [R4]
		POP     {R4, R5}
        BX      LR
        NOP             ;提示MCU我已经完成了入栈不需要再进行一次


PendSV_Handler
    CPSID   I                                                   ; 关闭中断 Prevent interruption during context switch
    MRS     R0, PSP                                             ; PSP is process stack pointer
    CBZ     R0, PendSV_Handler_Nosave		                    ; PSP是否等于0，判断是不是第一次调用
                                                                ; 如果是的话下面一段就不需要执行了Skip register save the first time

    SUBS    R0, R0, #0x20                                       ; 0x20代表需要向堆栈压入32个字节Save remaining regs r4-11 on process stack
    STM     R0, {R4-R11}

    LDR     R1, =OSTCBCur                                       ; OSTCBCur->OSTCBStkPtr = SP;
    LDR     R1, [R1]
    STR     R0, [R1]                                            ; R0 is SP of process being switched out

                                                                ; At this point, entire context of process has been saved
PendSV_Handler_Nosave
    PUSH    {R14}                                               ; 调用狗子函数Save LR exc_return value
    LDR     R0, =OSTaskSwHook                                   ; OSTaskSwHook();
    BLX     R0
    POP     {R14}

    LDR     R0, =OSPrioCur                                      ; OSPrioCur = OSPrioHighRdy;
    LDR     R1, =OSPrioHighRdy
    LDRB    R2, [R1]
    STRB    R2, [R0]

    LDR     R0, =OSTCBCur                                       ; *R0=R2 既OSTCBCur  = OSTCBHighRdy;
    LDR     R1, =OSTCBHighRdy                                   ; 是任务控制块结构体指针可以指向最该优先级的指针
    LDR     R2, [R1]
    STR     R2, [R0]

    LDR     R0, [R2]                                            ; R0=OSTCBHighRdy R0 is new process SP; SP = OSTCBHighRdy->OSTCBStkPtr;
    LDM     R0, {R4-R11}                                        ; 恢复堆栈Restore r4-11 from new process stack
    ADDS    R0, R0, #0x20
    MSR     PSP, R0                                             ; R0+=0X20 R0就是星任务的栈顶指针Load PSP with new process SP
    ORR     LR, LR, #0x04                                       ; 将PSP的值变为R0 Ensure exception return uses process stack
    CPSIE   I                                                   ; 将LR 位2置1 ，表示返回后回到进程
    BX      LR                                                  ; Exception return will restore remaining context

 end  