/*
 * @Descripttion: 
 * @version: 
 * @Author: Yueyang
 * @email: 1700695611@qq.com
 * @Date: 2020-10-26 19:35:49
 * @LastEditors: Yueyang
 * @LastEditTime: 2020-11-03 12:04:40
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "bmp.h"
#include "cv.h"
#include "li_image.h"
#include "li_painter.h"

int main()
{
     BYTE* ptr=NULL;
     Li_Image* out7 =Li_Create_Imgae(300,300,LI_DEP_24U,LI_BMP_888);
     ptr=out7->at(out7,40,20);
     *ptr++=0;
     *ptr++=0xFF;
     *ptr++=0;
     Li_Save_Image("1.bmp",out7);
     LILOG("over");
     return 0; 
}

 