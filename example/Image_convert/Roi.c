/*
 * @Descripttion: 
 * @version: 
 * @Author: Yueyang
 * @email: 1700695611@qq.com
 * @Date: 2020-10-26 19:35:49
 * @LastEditors: Yueyang
 * @LastEditTime: 2020-11-10 21:24:05
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
     Li_Image* out =Li_Load_Image("./picture/whu_rgba.bmp",LI_BMP_32);
     Li_Image* Roi =Li_Get_Roi(out,20,20,300,300);
     Li_Save_Image("Roi.bmp",Roi);

     Li_Image* img= Li_ReShape(Roi,512,512);
     Li_Save_Image("shape.bmp",img);
     LILOG("over");
     return 0; 
}

 