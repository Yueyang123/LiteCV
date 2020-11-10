/*
 * @Descripttion: 
 * @version: 
 * @Author: Yueyang
 * @email: 1700695611@qq.com
 * @Date: 2020-10-26 19:35:49
 * @LastEditors: Yueyang
 * @LastEditTime: 2020-11-10 22:09:08
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
     Li_Image* out =Li_Load_Image("./picture/lena.bmp",LI_BMP_888);
     Li_Image* gray=Li_Convert_Image(out,LI_BMP_888_2_LI_BMP_8);

     Li_Image* smooth=Li_Smooth(gray,Li_GAUSS);
     Li_Image* img= Li_Canny(smooth,LI_CANNY_SOBEL,30,120);
     Li_Save_Image("canny_sobel.bmp",img);

     LILOG("over");
     return 0; 
}

 