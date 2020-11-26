#ifndef HC_SR_04_H
#define	HC_SR_04_H
#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"

#define			Trig			PAout(2)
#define			Trig_Pin		GPIO_Pin_2
#define			Trig_Port		GPIOA
#define			Trig_CLKLine	RCC_APB2Periph_GPIOA
#define			Echo			PAin(3)
#define			Echo_Pin		GPIO_Pin_3
#define			Echo_Port		GPIOA
#define			Echo_CLKLine	RCC_APB2Periph_GPIOA

extern uint32_t US_Count;
extern void US_020Configuration(void);
extern void US_SendStartSignal(void);
extern float US_DataConversion(uint32_t count);
void US_AddCount();
uint32_t US_GetCount();
void US_ClearCount();

#endif

