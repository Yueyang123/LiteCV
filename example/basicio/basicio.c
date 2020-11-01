/*
 * @Descripttion: 底层图片IO测试
 * @version: V 2.0
 * @Author: Yueyang
 * @email: 1700695611@qq.com
 * @Date: 2020-10-26 19:35:49
 * @LastEditors: Yueyang
 * @LastEditTime: 2020-11-01 14:26:17
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "bmp.h"
#include "cv.h"
#include "li_image.h"
int main()
{
     //加载保存销毁图片
     Li_Image* out=Li_Load_Image("./picture/whu_rgb888.bmp",LI_BMP_888);
     Li_Save_Image("./picture/1.bmp",out);
     Li_Destroy_Image(out);

     Li_Image* out3=Li_Load_Image("./picture/whu_gray.bmp",LI_BMP_8);  
     Li_Save_Image("./picture/2.bmp",out3);   
     Li_Destroy_Image(out3);

     Li_Image* out4=Li_Load_Image("./picture/whu_rgba.bmp",LI_BMP_32);  
     Li_Save_Image("./picture/3.bmp",out4);  
     Li_Destroy_Image(out4);

     Li_Image* out1=Li_Load_Image("./picture/whu_png.png",LI_PNG);
     Li_Save_Image("./picture/1.png",out1);
     Li_Destroy_Image(out1);

     Li_Image* out2=Li_Load_Image("./picture/whu_jpg.jpg",LI_JPEG);
     Li_Save_Image("./picture/1.jpg",out2);
     Li_Destroy_Image(out2);


     //创建图片并操作像素
     BYTE* ptr=NULL;
     Li_Image* out7 =Li_Create_Imgae(300,300,LI_DEP_24U,LI_BMP_888);
     ptr=out7->at(out7,10,10);
     if(ptr!=NULL){
          memset(ptr,0xFF,1);
          memset(ptr+1,0,1);  
          memset(ptr+2,0,1);            
     }
     Li_Save_Image("./picture/1.bmp",out3);
     Li_Destroy_Image(out7);

     Li_Image* out8 =Li_Load_Image("./picture/whu_jpg.jpg",LI_JPEG);
     ptr=out8->at(out8,10,10);
     if(ptr!=NULL){
          memset(ptr,0xFF,1);
          memset(ptr+1,0,1);  
          memset(ptr+2,0,1);
     }
     Li_Save_Image("./picture/2.jpg",out8);
     Li_Destroy_Image(out8);

     Li_Image* out5 =Li_Load_Image("./picture/whu_png.png",LI_PNG);
     ptr=out5->at(out5,10,10);
     if(ptr!=NULL){
          memset(ptr,0xFF,1);
          memset(ptr+1,0,1);  
          memset(ptr+2,0,1);
     }
     Li_Save_Image("./picture/2.png",out5);

     Li_Image* out6=Li_Copy_Imgae(out6);
     Li_Save_Image("./picture/3.png",out6);


     LILOG("over");
     return 0; 
}

 