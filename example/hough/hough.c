/*
 * @Descripttion: 
 * @version: 
 * @Author: Yueyang
 * @email: 1700695611@qq.com
 * @Date: 2020-10-26 19:35:49
 * @LastEditors: Yueyang
 * @LastEditTime: 2020-11-11 16:07:33
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
     Li_Image* out,*bmp,*gray,*smooth,*canny,*roi ;
     char* picname="./picture/panal (";
     char outfile[20];
     char infile[20];
     for(int i=0;i<17;i++){
          sprintf(infile,"%s%d%s",picname,i+1,").jpg");
          sprintf(outfile,"%s%d%s","out",i+1,".bmp");

          LILOG("NEXT PICTURE");
          out=Li_Load_Image(infile,LI_JPEG);
          bmp=Li_Convert_Image(out,LI_JPEG_2_BMP);
          gray=Li_Convert_Image(bmp,LI_BMP_888_2_LI_BMP_8);
          smooth=Li_Smooth(gray,Li_GAUSS);

          canny= Li_Canny(smooth,LI_CANNY_SOBEL,20,128);

          LONG range[]={170,180,100,120};
          Li_Hough_Circle(canny,&c,120,130,range);

          c.r=c.r- c.r%8;
          LONG startx=c.x-c.r ;
          LONG starty=c.y-c.r;
          LONG endx=c.x+c.r ,endy=c.y+c.r;
          roi=Li_Get_Roi(canny,(startx)>0?(startx):0,(starty)>0?(starty):0,(endx)<canny->width?(endx):canny->width,(endy)<canny->height?(endy):canny->height);
          Li_Hough_Line(roi,&l,130,250);

          Li_Image* res=Li_Get_Roi(bmp,(startx)>0?(startx):0,(starty)>0?(starty):0,(endx)<bmp->width?(endx):bmp->width,(endy)<bmp->height?(endy):bmp->height);
          Li_Line_P(res,0xFF0000,l.thera,l.r);
          Li_Circle(res,0x00FF00,(res->width-2)/2,(res->height-2)/2,c.r);
          
          // Li_Save_Image("./smooth.bmp",smooth);
          // Li_Save_Image("./canny_sobel.bmp",canny);
          // Li_Save_Image("./roi.bmp",roi);
          Li_Save_Image(outfile,res);
     }
     LILOG("over");
     return 0; 
}

 