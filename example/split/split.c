/*
 * @Descripttion: 图像色道分离与合并
 * @version: 
 * @Author: Yueyang
 * @email: 1700695611@qq.com
 * @Date: 2020-10-26 19:35:49
 * @LastEditors: Yueyang
 * @LastEditTime: 2020-11-10 19:28:47
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "bmp.h"
#include "cv.h"
#include "li_image.h"
#include "li_painter.h"
#include "li_image_proc.h"

int main()
{
     BYTE* ptr=NULL;
     Li_Image* out =Li_Load_Image("./picture/whu_rgb888.bmp",LI_BMP_888);
     Li_Image* img[3];
     Li_Split(out,img);
     Li_Save_Image("1.bmp",img[0]);
     Li_Save_Image("2.bmp",img[1]);
     Li_Save_Image("3.bmp",img[2]);

     Li_Image* img2= Li_Combine(img,LI_DEP_24U);
     Li_Save_Image("4.bmp",img2);
     LILOG("over");
     return 0; 
     LILOG("over");
     return 0; 
}

 