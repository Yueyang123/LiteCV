#include "HC_SR.h"
#include "sys.h"
#include "includes.h"
uint32_t US_Count = 0;

//每进入一次定时中断US_Count加一
void US_AddCount()
{
	US_Count++;
}

uint32_t US_GetCount()
{
	return US_Count;
}

void US_ClearCount()
{
	US_Count=0;
}
void HC_SR_Configuration(void)
{
	  GPIO_InitTypeDef    GPIO;
    NVIC_InitTypeDef 	MyNVIC;	
	  EXTI_InitTypeDef	MyEXTI;
    //Enable APB2 Bus
    RCC_APB2PeriphClockCmd(Trig_CLKLine | Echo_CLKLine, ENABLE);
    
    //Register IO 
    GPIO.GPIO_Pin   = Trig_Pin;
    GPIO.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_Init(Trig_Port, &GPIO);
	
	Trig = 0;
	//Register IO 
    GPIO.GPIO_Pin   = Echo_Pin;
    GPIO.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
    GPIO_Init(Echo_Port, &GPIO);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	MyNVIC.NVIC_IRQChannel = EXTI3_IRQn;
	MyNVIC.NVIC_IRQChannelPreemptionPriority = 0;
	MyNVIC.NVIC_IRQChannelSubPriority = 1;	
	MyNVIC.NVIC_IRQChannelCmd = ENABLE;			
	NVIC_Init(&MyNVIC);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource3);
	MyEXTI.EXTI_Line	= EXTI_Line3;
	MyEXTI.EXTI_Trigger = EXTI_Trigger_Rising;
	MyEXTI.EXTI_Mode	= EXTI_Mode_Interrupt;
	MyEXTI.EXTI_LineCmd	= ENABLE;
	EXTI_Init(&MyEXTI);
}

void US_SendStartSignal(void)
{
	Trig = 1;
	delay_us(20);
	Trig = 0;
}
	
float US_DataConversion(uint32_t count)
{
	float result = 0;
	result = (float)((float)(count * 340) / 2000.0);
	return result;
}

void EXTI3_IRQHandler(void)
{
	float Distance;
	if (EXTI_GetITStatus(EXTI_Line3) != RESET) 
	{ 
//		OS_CPU_SR cpu_sr=0;
//		OS_ENTER_CRITICAL();
//		TIM_SetCounter(TIM4,0);
//		while(Echo==1);
//		Distance=(float)((float)TIM_GetCounter(TIM4)*340)/200.0;
//		OS_EXIT_CRITICAL();	
//		if(Distance>0)
//		{
//			printf("Distance:%d %f cm\r\n",TIM_GetCounter(TIM4),Distance);
//		}
				EXTI_ClearITPendingBit(EXTI_Line3);
	}
}
