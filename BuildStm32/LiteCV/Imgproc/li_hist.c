/*
 * @Descripttion: 
 * @version: 
 * @Author: Yueyang
 * @email: 1700695611@qq.com
 * @Date: 2020-11-24 21:45:16
 * @LastEditors: Yueyang
 * @LastEditTime: 2020-11-24 23:15:20
 */
#ifndef LI_HIST_C
#define LI_HIST_C

#include "li_image_proc.h"
#include "li_painter.h"
#include <string.h>

Li_Hist* Li_Create_Hist(float* data)
{
    Li_Hist* hist=(Li_Hist*)malloc(sizeof(Li_Hist));
    memcpy(hist->data,data,256*sizeof(float));
    return hist;
}


void Li_Destroy_Hist(Li_Hist* hist)
{
    free(hist);
}

/**
 * @name: Li_Print_Hist
 * @msg: 打印直方图
 * @param {Li_Hist* hist}
 * @return {*}
 */
LI_API
void Li_Print_Hist(Li_Hist* hist)
{
    printf("[ ");
    for(int i=0;i<256;i++)
    {
        printf("%f ",hist->data[i]);
    }
    printf(" ]");
}

/**
 * @name: Li_Visual_Hist
 * @msg: 直方图转化为图像
 * @param {Li_Hist* hist}
 * @return {Li_Image*}
 */
LI_API
Li_Image* Li_Visual_Hist(Li_Hist* hist)
{
    Li_Image* img=Li_Create_Image(256,256,LI_DEP_24U,LI_BMP_888);
    float max=0,div=0;
    for(int i=0;i<256;i++)
    {
        if(hist->data[i]>max)
            max=hist->data[i];
    }
    div=256/max;
    for(int i=0;i<256;i++)
    {
        Li_Line_H(img,0x0000FF,i,hist->data[i]*div);
    }
    return img;
}

/**
 * @name: Li_Get_Hist
 * @msg: 绘制直方图
 * @param {Li_Image* img 图像}
 * @return {Li_Hist* 直方图数据}
 */
LI_API 
Li_Hist* Li_Get_Hist(Li_Image* img)
{
   if(img->imgdepth!=LI_DEP_8U)return NULL;

   float* buffer;//存储0-255的数值出现的次数
   float* result;
   int length=img->width*img->height;
   //将申请的地址全部初始化为0
   buffer=(float*)malloc(256*sizeof(float));
   result=(float*)malloc(256*sizeof(float));
   memset(buffer,0,256*4);
   memset(result,0,256*4);

   for(int i=0;i<length;i++)
   {
      BYTE off=*((BYTE*)img->data+i);
      buffer[off]++;
   }

   for(int i=0;i<256;i++)
   {
      result[i]=buffer[i]/length;
   }
   Li_Hist* hist=Li_Create_Hist(result);
   return hist;
}

/**
 * @name: Li_Normalize_Hist
 * @msg: 直方图均衡化
 * @param {Li_Image* img}
 * @return {*}
 */
LI_API
Li_Image* Li_Normalize_Hist(Li_Image* img)
{
    Li_Image* dst=Li_Copy_Image(img);
    Li_Hist* Hist= Li_Get_Hist(img);
    float Max,Min;
    float sum[256];
    BYTE out[256];//对于源灰度值产生进行新的映射表
    BYTE* buf=(BYTE*)malloc(img->width*img->height*sizeof(BYTE));
    //找到原图灰度值中的最大值和最小值 
    //一般而言应该是0-255
    for(int i=1;i<img->width*img->height;i++)
    {
        if(*((BYTE*)img->data+i)>Max)
        {
            Max=*((BYTE*)img->data+i);
        }
         if(*((BYTE*)img->data+i)<Min)
        {
            Min=*((BYTE*)img->data+i);
        }
    }
    BYTE* inaddr;
    float* data=Hist->data;
    //计算累计概率和
    sum[0]=*data;
    for(int i=1;i<=255;i++)
    {
       sum[i]=sum[i-1]+*(data+i);
       out[i]=(BYTE)(sum[i]*(Max-Min));//获得一张新的灰度值表
    }

   for(int x=0;x<dst->width;x++)
   for(int y=0;y<dst->height;y++)
   {
        inaddr=dst->at(dst,x,y);
        BYTE temp=*inaddr;
       *(inaddr)=out[temp];
   }
   return dst;
}

#endif // !LI_HIST_C
