/*
 * @Descripttion: 
 * @version: 
 * @Author: Yueyang
 * @email: 1700695611@qq.com
 * @Date: 2020-10-26 19:35:49
 * @LastEditors: Yueyang
 * @LastEditTime: 2020-11-11 14:47:39
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
     LiLine l;
     LiCircle c;
     Li_Image* res;
     Li_Image* out =Li_Load_Image("./picture/panal4.jpg",LI_JPEG);
     Li_Image* bmp=Li_Convert_Image(out,LI_JPEG_2_BMP);

     Li_Image* gray=Li_Convert_Image(bmp,LI_BMP_888_2_LI_BMP_8);
     Li_Image* smooth=Li_Smooth(gray,Li_GAUSS);
     Li_Save_Image("./smooth.bmp",smooth);
     Li_Image* img= Li_Canny(smooth,LI_CANNY_SOBEL,20,128);
     Li_Save_Image("./canny_sobel.bmp",img);
     res= Li_Copy_Image(out);
     int range[]={170,180,100,120};
     Li_Hough_Circle(img,&c,120,130,range);
     // printf("%d,%d,%d",c.r,c.x,c.y);
     Li_Circle(res,0xFF0000,c.x,c.y,c.r);
     // res= Li_Copy_Image(out);
     // Li_Hough_Line(img,&l,130,250);
     // Li_Line_P(res,0xFF0000,l.thera,l.r);
      Li_Save_Image("./out.jpg",res);
     // printf("%d,%d",l.r,l.thera);

     LILOG("over");
     return 0; 
}

 