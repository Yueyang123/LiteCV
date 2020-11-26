#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
#include "delay.h"

								    
void KEY_Init(void)
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);


	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);

}

u8 KEY_Scan()
{	  
	if(KEY0==0)
	{
		if(KEY0==0)return KEY0_PRES;
	}	    
 	return 0;
}
