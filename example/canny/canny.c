/*
 * @Descripttion: 
 * @version: 
 * @Author: Yueyang
 * @email: 1700695611@qq.com
 * @Date: 2020-10-26 19:35:49
 * @LastEditors: Yueyang
 * @LastEditTime: 2020-11-27 01:07:12
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
     Li_CV_Version();
     BYTE* ptr=NULL;
     Li_Image* out =Li_Load_Image("./picture/panal (1).jpg",LI_JPEG);
     Li_Image* bmp=Li_Convert_Image(out,LI_JPEG_2_BMP);
     Li_Image* gray=Li_Convert_Image(bmp,LI_BMP_888_2_LI_BMP_8);

     Li_Image* smooth=Li_Smooth(gray,Li_GAUSS);
     Li_Image* img= Li_Canny(smooth,LI_CANNY_PREWITT,30,150);
     Li_Save_Image("canny_mydefine.bmp",img);

     Li_Wait_Q();
     LILOG("over");
     return 0; 
}

 