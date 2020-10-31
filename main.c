/*
 * @Descripttion: 
 * @version: 
 * @Author: Yueyang
 * @email: 1700695611@qq.com
 * @Date: 2020-10-26 19:35:49
 * @LastEditors: Yueyang
 * @LastEditTime: 2020-10-31 21:22:51
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
     //这里的指针只可以作为左值发生改变
     //也就是说如果内存申请发生在函数里面的话
     //指针实际上上不会发生改变的
     //也就是说这里的指针等于说没有进行内存申请
     //也就是说不要指望通过函数传参的方式为指针赋值

     Li_Image* out=Li_Load_Image("./picture/whu_rgb888.bmp",LI_BMP_888);
     Li_Save_Image("./picture/1.bmp",out);

     Li_Image* out3=Li_Load_Image("./picture/whu_gray.bmp",LI_BMP_8);  
     Li_Save_Image("./picture/2.bmp",out3);   

     Li_Image* out4=Li_Load_Image("./picture/whu_rgba.bmp",LI_BMP_32);  
     Li_Save_Image("./picture/3.bmp",out4);  

     Li_Image* out1=Li_Load_Image("./picture/whu_png.png",LI_PNG);
     Li_Save_Image("./picture/1.png",out1);
     
     Li_Image* out2=Li_Load_Image("./picture/whu_jpg.jpg",LI_JPEG);
     Li_Save_Image("./picture/1.jpg",out2);

       
     
     //通过函数返回的指针如果在函数分配了内存是可以直接使用的
     // LONG height,width;
     // BITMAPFILEHEADER bf;
     // BITMAPINFOHEADER bi;

     // Li_Image* img0=Li_Load_Image("./picture/whu_rgba.bmp",LI_BMP_32);
     // bf= get_default_file_head(img0->limat);
     // bi= get_default_info_head(img0->limat);
     // Write_bmp("3.bmp",img0->data,&bf,&bi,LI_BMP_32);

     // Li_Image* img=Li_Load_Image("./picture/whu_png.png",LI_PNG);
     // bf= get_default_file_head(img->limat);
     // bi= get_default_info_head(img->limat);
     // Write_bmp("1.bmp",img->data,&bf,&bi,LI_BMP_32);
     // Write_Png("1.png",img->data,img->limat.width,img->limat.height,8);

     // Li_Image* img1=Li_Load_Image("./picture/whu_jpg.jpg",LI_JPEG);
     // bf= get_default_file_head(img1->limat);
     // bi= get_default_info_head(img1->limat);
     // Write_bmp("2.bmp",img1->data,&bf,&bi,LI_BMP_32);
     // Write_Jpeg("1.jpg",img->data,100,img1->limat.width,img1->limat.height); 

     // Li_Image* img2=Li_Load_Image("./picture/whu_gray.bmp",LI_BMP_8);
     // bf= get_default_file_head(img2->limat);
     // bi= get_default_info_head(img2->limat);
     // Write_bmp("4.bmp",img2->data,&bf,&bi,LI_BMP_8);

     LILOG("over");
     return 0; 
}

 