/*
 * @Descripttion: 底层图片IO测试
 * @version: V 2.0
 * @Author: Yueyang
 * @email: 1700695611@qq.com
 * @Date: 2020-10-26 19:35:49
 * @LastEditors: Yueyang
 * @LastEditTime: 2020-11-27 01:17:12
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
     Li_CV_Version();
     //加载保存销毁图片
     Li_Image* out=Li_Load_Image("./picture/whu_rgb888.bmp",LI_BMP_888);
     Li_Save_Image("rgb888.bmp",out);
     Li_Destroy_Image(out);

     Li_Image* out3=Li_Load_Image("./picture/whu_gray.bmp",LI_BMP_8);  
     Li_Save_Image("gray.bmp",out3);   
     Li_Destroy_Image(out3);

     Li_Image* out4=Li_Load_Image("./picture/whu_rgba.bmp",LI_BMP_32);  
     Li_Save_Image("rgba.bmp",out4);  
     Li_Destroy_Image(out4);

     Li_Image* out1=Li_Load_Image("./picture/whu_png.png",LI_PNG);
     Li_Save_Image("png.png",out1);
     Li_Destroy_Image(out1);

     Li_Image* out2=Li_Load_Image("./picture/whu_jpg.jpg",LI_JPEG);
     Li_Save_Image("jpg.jpg",out2);

     Li_Wait_Q();
     LILOG("over");
     return 0; 
}

 