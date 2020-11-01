/*
 * @Descripttion: 
 * @version: 
 * @Author: Yueyang
 * @email: 1700695611@qq.com
 * @Date: 2020-10-26 19:35:49
 * @LastEditors: Yueyang
 * @LastEditTime: 2020-11-01 12:49:28
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


     BYTE* ptr=NULL;
     Li_Image* out =Li_Create_Imgae(300,300,LI_DEP_24U,LI_BMP_888);
     ptr=out->at(out,10,10);
     if(ptr!=NULL){
          memset(ptr,0xFF,1);
          memset(ptr+1,0,1);  
          memset(ptr+2,0,1);            
     }
     else LILOG("somthing was wrong");

     

     
     

     Li_Save_Image("./picture/1.bmp",out);
     Li_Destroy_Image(out);

     LILOG("over");
     return 0; 
}

 