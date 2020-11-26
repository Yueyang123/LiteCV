/*
 * @Descripttion: 
 * @version: 
 * @Author: Yueyang
 * @email: 1700695611@qq.com
 * @Date: 2020-09-10 13:29:32
 * @LastEditors: Yueyang
 * @LastEditTime: 2020-09-30 01:48:07
 * @Describe:向外界提供了OS_TASK_SW()函数，
 * #define  OS_ENTER_CRITICAL()  {cpu_sr = OS_CPU_SR_Save();}//关闭中断进入玲姐区
 * #define  OS_EXIT_CRITICAL()   {OS_CPU_SR_Restore(cpu_sr);}//开中断
 * 定义各种结构类型
 */


#ifndef	__OS_CPU_H__
#define	__OS_CPU_H__

#ifdef  OS_CPU_GLOBALS
#define OS_CPU_EXT
#else
#define OS_CPU_EXT  extern
#endif


typedef unsigned char  BOOLEAN;
typedef unsigned char  INT8U;			/* Unsigned  8 bit quantity       */
typedef signed   char  INT8S;			/* Signed    8 bit quantity       */
typedef unsigned short INT16U;			/* Unsigned 16 bit quantity       */
typedef signed   short INT16S;			/* Signed   16 bit quantity       */
typedef unsigned int   INT32U;			/* Unsigned 32 bit quantity       */
typedef signed   int   INT32S;			/* Signed   32 bit quantity       */
typedef float          FP32;			/* Single precision floating point*/
typedef double         FP64;			/* Double precision floating point*/

//STM32是32位的，所以堆栈与CPU状态寄存器也应该是32位的
typedef unsigned int   OS_STK;			/* Each stack entry is 32-bit wide*/
typedef unsigned int   OS_CPU_SR;		/* Define size of CPU status register*/
/* 
*******************************************************************************
*                             Cortex M3
*                     Critical Section Management
*******************************************************************************
*/


/*
*******************************************************************************
*                          ARM Miscellaneous
*******************************************************************************
*/


//定义栈的增长方向.
//CM3 中,栈是由高地址向低地址增长的,所以 OS_STK_GROWTH 设置为 1
#define  OS_STK_GROWTH        1      /* Stack grows from HIGH to LOW memory on ARM    */
//任务切换宏,由汇编实现.
#define  OS_TASK_SW()         OSCtxSw()

/*
*******************************************************************************
*                               PROTOTYPES
*                           (see OS_CPU_A.ASM)
*******************************************************************************
*/
//OS_CRITICAL_METHOD = 1 :直接使用处理器的开关中断指令来实现宏
//OS_CRITICAL_METHOD = 2 :利用堆栈保存和恢复 CPU 的状态
//OS_CRITICAL_METHOD = 3 :利用编译器扩展功能获得程序状态字，保存在局部变量 cpu_sr
#define  OS_CRITICAL_METHOD   3	 

#if OS_CRITICAL_METHOD == 3
#define  OS_ENTER_CRITICAL()  {cpu_sr = OS_CPU_SR_Save();}
#define  OS_EXIT_CRITICAL()   {OS_CPU_SR_Restore(cpu_sr);}
#endif

void       OSCtxSw(void);
void       OSIntCtxSw(void);
void       OSStartHighRdy(void);

void       OSPendSV(void);

#if OS_CRITICAL_METHOD == 3u                      /* See OS_CPU_A.ASM                                  */
OS_CPU_SR  OS_CPU_SR_Save(void);
void       OS_CPU_SR_Restore(OS_CPU_SR cpu_sr);
#endif
OS_CPU_EXT INT32U OSInterrputSum;

#endif

/************************ (C) COPYLEFT 2010 Leafgrass ************************/
