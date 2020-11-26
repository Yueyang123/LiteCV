/*
 * @Descripttion: 
 * @version: 
 * @Author: Yueyang
 * @email: 1700695611@qq.com
 * @Date: 2020-09-10 13:20:54
 * @LastEditors: Yueyang
 * @LastEditTime: 2020-09-30 02:10:26
 */
#include "sys.h" 	
#include "delay.h"	
#include "led.h"
#include "key.h"
#include "usart.h"
#include "includes.h"
#include "usb_lib.h"
#include "hw_config.h"
#include "usb_pwr.h"
#include "24cxx.h"
#include "exti.h"
#include "timer.h"
#include "string.h"
#include "usart3.h"
#include "Esp8266.h"
#include "pwm.h"
#include "HC_SR.h"
/////////////////////////UCOSII任务设置///////////////////////////////////
//START 任务
//设置任务优先级
#define START_TASK_PRIO      		10 //开始任务的优先级设置为最低
//设置任务堆栈大小
#define START_STK_SIZE  				64
//任务堆栈	
OS_STK START_TASK_STK[START_STK_SIZE];
//任务函数
void start_task(void *pdata);	
 			   
#define ESP_TASK_PRIO            6
#define ESP_STK_SIZE						 64
OS_STK  ESP_TASK_STK[ESP_STK_SIZE];
void esp_task();


#define KEY_TASK_PRIO            7
#define KEY_STK_SIZE						 64
OS_STK  KEY_TASK_STK[KEY_STK_SIZE];
void key_task();

//USB任务
//设置任务优先级
#define USB_TASK_PRIO       			5 
//设置任务堆栈大小
#define USB_STK_SIZE  					 128
//任务堆栈
OS_STK USB_TASK_STK[USB_STK_SIZE];
//任务函数
void usb_task(void *pdata);


u8 SYSTEM_STATUS[10];//从网络部分获取的信息，用作单片机的控制


 int main(void)
 {	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	delay_init();	    //延时函数初始化	  
	uart_init(115200);
	OSInit();   
 	OSTaskCreate(start_task,(void *)0,(OS_STK *)&START_TASK_STK[START_STK_SIZE-1],START_TASK_PRIO );//创建起始任务
	OSStart();	  	 
}
	  
//开始任务
void start_task(void *pdata)
{
  OS_CPU_SR cpu_sr=0;
	INT8U   err;
	pdata = pdata; 
  OS_ENTER_CRITICAL();			//进入临界区(无法被中断打断)    
 	OSTaskCreate(usb_task,(void *)0,(OS_STK*)&USB_TASK_STK[USB_STK_SIZE-1],USB_TASK_PRIO);	
 	OSTaskCreate(esp_task,(void *)0,(OS_STK*)&ESP_TASK_STK[ESP_STK_SIZE-1],ESP_TASK_PRIO);
	OSTaskCreate(key_task,(void *)0,(OS_STK*)&KEY_TASK_STK[KEY_STK_SIZE-1],KEY_TASK_PRIO);

	delay_ms(1800);
	USB_Port_Set(0); //USB 先断开
	delay_ms(700);
	USB_Port_Set(1); //USB 再次连接
	Set_USBClock();
	USB_Interrupts_Config();
	USB_Init();
	AT24CXX_Init();
	KEY_Init();
	usart3_init(115200);
	//EXTIX_Init();
	LED_Init();

	ESP8266_Init();
	TIM3_PWM_Init(1999,719);//50HZ
	TIM4_Int_Init(9999,7199);//10000HZ  1000ms
	//HC_SR_Configuration();
	
	OSTaskDel(START_TASK_PRIO);	//挂起起始任务.
	OS_EXIT_CRITICAL();				//退出临界区(可以被中断打断)
}



void usb_task(void *pdatac)
{
	 u8 usbstatus=0;
	 u16 times=0;  
	 u16 len,t;
	 u8* key;
	 u8 tbuf[20];
	 u8 usb_str[]="usb_task";
	 INT8U   err;
	  usbstatus=bDeviceState;

	while(1){
		if(USB_USART_RX_STA&0x8000)
		{					   
			len=USB_USART_RX_STA&0x3FFF;//得到此次接收到的数据长度
			for(t=0;t<len;t++)
			{
				USB_USART_SendData(USB_USART_RX_BUF[t]);//以字节方式,发送给USB 
			}
			usb_printf("\r\n\r\n");//插入换行
			USB_USART_RX_STA=0;
		}else
		{
			times++;

			delay_ms(1000);
		}
	}
}

void esp_task()
{
	u16 t;  
	u16 len;	
	static int tmp=0;
	while(1)
	{
		if(USART3_RX_STA!=0)
		{					  
			
			len=USART3_RX_STA&0x3fff;
			memcpy(SYSTEM_STATUS,USART3_RX_BUF,len);
			usb_printf("%c",USART3_RX_BUF[0]);
			usb_printf("\r\n\r\n");
			
			if(USART3_RX_BUF[0]=='0')
			{
				LED0=0;
			}else if(USART3_RX_BUF[0]=='1')
			LED0=1;
			USART3_RX_STA=0;
		}

			
		delay_ms(1000);

	}
}

////		delay_ms(1000);	 										 
////		TIM_SetCompare2(TIM3,1750);// £¨2000-1750£©/2000 * 20mS=2.5mS  
//// 		delay_ms(1000);	 										 
////		TIM_SetCompare2(TIM3,1800);// £¨2000-1800£©/2000 * 20mS=2mS  
////		delay_ms(1000);	 										 
////		TIM_SetCompare2(TIM3,1850);// £¨2000-1850£©/2000 * 20mS=1.5mS  
////		delay_ms(1000);	 										 
////		TIM_SetCompare2(TIM3,1900);// £¨2000-1900£©/2000 * 20mS=1mS  
////		delay_ms(1000);	

void key_task()
{
	u8 key;
	int count;
	int pwm_start=1750,i;
	OS_CPU_SR cpu_sr=0;
	int distance=0;
	while(1)
	{
		key=KEY_Scan();
		pwm_start=1750;

//		for( i=0;i<10;i++){
//			TIM_SetCompare2(TIM3,1750+i*25);
//			delay_ms(1000);			
//			}
		}
}