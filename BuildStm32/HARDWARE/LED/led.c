/*
 * @Descripttion: 
 * @version: 
 * @Author: Yueyang
 * @email: 1700695611@qq.com
 * @Date: 2020-09-10 13:20:53
 * @LastEditors: Yueyang
 * @LastEditTime: 2020-10-01 01:13:29
 */
#include "led.h"


void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;				
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
 GPIO_Init(GPIOC, &GPIO_InitStructure);	
 GPIO_SetBits(GPIOB,GPIO_Pin_13);

}
 
