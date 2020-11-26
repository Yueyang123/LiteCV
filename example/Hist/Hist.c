/*
 * @Descripttion: 图像直方图常见操作
 * @version: 
 * @Author: Yueyang
 * @email: 1700695611@qq.com
 * @Date: 2020-10-26 19:35:49
 * @LastEditors: Yueyang
 * @LastEditTime: 2020-11-27 01:08:09
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
     Li_Image* out =Li_Load_Image("./picture/whu_rgb888.bmp",LI_BMP_888);     
     Li_Image* gray=Li_Convert_Image(out,LI_BMP_888_2_LI_BMP_8);
     Li_Save_Image("./gray.bmp",gray);
     Li_Hist*hist=Li_Get_Hist(gray);
     Li_Image* cdf=Li_Visual_Hist(hist);
     Li_Save_Image("cdf.bmp",cdf);
     Li_Image* nomal=Li_Normalize_Hist(gray);
     Li_Save_Image("./nomal.bmp",nomal);
     Li_Hist*hist1=Li_Get_Hist(nomal);
     Li_Image* cdf1=Li_Visual_Hist(hist1);
     Li_Save_Image("cdf1.bmp",cdf1);
     Li_Wait_Q();
     LILOG("over");
     return 0; 
}

 