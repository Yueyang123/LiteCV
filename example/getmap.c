/*
 * @Descripttion: 查表法实现颜色空间转换需要的表
 * @version: 
 * @Author: Yueyang
 * @email: 1700695611@qq.com
 * @Date: 2020-10-26 19:35:49
 * @LastEditors: Yueyang
 * @LastEditTime: 2020-11-02 17:25:38
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>


int main()
{
     int D[256],F[256],E[256];
     int i;
     for(i=0;i<256;i++)
     {
     D[i]=i*1224;
     D[i]=D[i]>>12;
     E[i]=i*2405;
     E[i]=E[i]>>12;
     F[i]=i*467;
     F[i]=F[i]>>12;
     }

     for(i=0;i<256;i++)
     printf("%d,",D[i]);

     printf("\r\n");


     for(i=0;i<256;i++)
     printf("%d,",E[i]);

     printf("\r\n");

     for(i=0;i<256;i++)
     printf("%d,",F[i]);

     printf("\r\n");
     printf("\r\n");
     printf("\r\n");


     int D[256],F[256],E[256];
     int i;
     for(i=0;i<256;i++)
     {
     D[i]=i*1224;
     D[i]=D[i]>>12;
     E[i]=i*2404;
     E[i]=E[i]>>12;
     F[i]=i*467;
     F[i]=F[i]>>12;
     }

     for(i=0;i<256;i++)
     printf("%d,",D[i]);

     printf("\r\n");


     for(i=0;i<256;i++)
     printf("%d,",E[i]);

     printf("\r\n");

     for(i=0;i<256;i++)
     printf("%d,",F[i]);

     printf("\r\n");
     printf("\r\n");
     printf("\r\n");


     for(i=0;i<256;i++)
     {
     D[i]=i*(-691);
     D[i]=D[i]>>12;
     E[i]=i*(-1357);
     E[i]=E[i]>>12;
     F[i]=i*2048;
     F[i]=F[i]>>12;
     }

     for(i=0;i<256;i++)
     printf("%d,",D[i]);

     printf("\r\n");


     for(i=0;i<256;i++)
     printf("%d,",E[i]);

     printf("\r\n");

     for(i=0;i<256;i++)
     printf("%d,",F[i]);

     printf("\r\n");
     printf("\r\n");
     printf("\r\n");

     for(i=0;i<256;i++)
     {
     D[i]=i*(2048);
     D[i]=D[i]>>12;
     E[i]=i*(-1715);
     E[i]=E[i]>>12;
     F[i]=i*(-333);
     F[i]=F[i]>>12;
     }

     for(i=0;i<256;i++)
     printf("%d,",D[i]);

     printf("\r\n");


     for(i=0;i<256;i++)
     printf("%d,",E[i]);

     printf("\r\n");

     for(i=0;i<256;i++)
     printf("%d,",F[i]);

     printf("\r\n");


    for(i=0;i<256;i++)
     {
     D[i]=i*4768;
     D[i]=D[i]>>12;
     E[i]=i*8266;
     E[i]=E[i]>>12;
     F[i]=i*0;
     F[i]=F[i]>>12;
     }

     for(i=0;i<256;i++)
     printf("%d,",D[i]);

     printf("\r\n");


     for(i=0;i<256;i++)
     printf("%d,",E[i]);

     printf("\r\n");

     for(i=0;i<256;i++)
     printf("%d,",F[i]);

     printf("\r\n");
     printf("\r\n");
     printf("\r\n");

     for(i=0;i<256;i++)
     {
     D[i]=i*4768;
     D[i]=D[i]>>12;
     E[i]=i*1556;
     E[i]=E[i]>>12;
     F[i]=i*3330;
     F[i]=F[i]>>12;
     }

     for(i=0;i<256;i++)
     printf("%d,",D[i]);

     printf("\r\n");


     for(i=0;i<256;i++)
     printf("%d,",E[i]);

     printf("\r\n");

     for(i=0;i<256;i++)
     printf("%d,",F[i]);

     printf("\r\n");
     printf("\r\n");
     printf("\r\n");

     for(i=0;i<256;i++)
     {
     D[i]=i*4768;
     D[i]=D[i]>>12;
     E[i]=i*0;
     E[i]=E[i]>>12;
     F[i]=i*4747;
     F[i]=F[i]>>12;
     }

     for(i=0;i<256;i++)
     printf("%d,",D[i]);

     printf("\r\n");


     for(i=0;i<256;i++)
     printf("%d,",E[i]);

     printf("\r\n");

     for(i=0;i<256;i++)
     printf("%d,",F[i]);

     printf("\r\n");
     printf("\r\n");
     printf("\r\n");

     //LILOG("over");
     return 0; 
}

 