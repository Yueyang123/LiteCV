#include "usart3.h"
#include "sys.h"
#include "delay.h"
#include "usart3.h"
#include "Esp8266.h"
#include "includes.h"


u8* atk_8266_check_cmd(u8 *str)
{
	
	char *strx=0;
	if(USART3_RX_STA&0X8000)
	{ 
		USART3_RX_BUF[USART3_RX_STA&0X7FFF]=0;
		strx=strstr((const char*)USART3_RX_BUF,(const char*)str);
	} 
	return (u8*)strx;
}

void delay(int cnt)
{
	while(cnt>=0)
	{
		cnt--;
	}
}

u8 atk_8266_send_cmd(u8 *cmd,u8 *ack,u16 waittime)
{
	u8 res=0; 
	USART3_RX_STA=0;
	u3_printf("%s\r\n",cmd);
	if(ack&&waittime)
	{
		while(--waittime)
		{
			delay(10000);
			if(USART3_RX_STA&0X8000)
			{
					printf("ack:%s\r\n",(u8*)ack);
					USART3_RX_STA=0;
			} 
		}
		if(waittime==0)res=1; 
	}
	return res;
} 



void ESP8266_Init(void)
{
	OSSchedLock();
	u3_printf("AT\r\n");
	delay(50000);
	u3_printf("AT+CWMODE=2\r\n");
		delay(500000);	
	u3_printf("AT+CWSAP=\"YY\",12345678,1,4\r\n");
		delay(500000);
	u3_printf("AT+CIPMUX=0\r\n");
		delay(50000);	
	u3_printf("AT+CIPSTART=\"TCP\",\"192.168.4.2\",8086\r\n");//wifi??????,????????
		delay(500000);
	u3_printf("AT+CIPMODE=1\r\n");
		delay(500000);
	u3_printf("AT+CIPSEND\r\n");
		delay(500000);	
	OSSchedUnlock();
}