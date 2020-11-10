/*
 * @Descripttion: 
 * @version: 
 * @Author: Yueyang
 * @email: 1700695611@qq.com
 * @Date: 2020-11-10 22:01:04
 * @LastEditors: Yueyang
 * @LastEditTime: 2020-11-10 22:44:07
 */
#ifndef LI_SMOOTH_C
#define LI_SMOOTH_C



#include "cv.h"
#include "li_image_proc.h"
#include <stdio.h>

/**
 * @name: Li_Medeum
 * @msg: 图像中值滤波
 * @param {Li_Image* img}
 * @return {Li_Image*}
 */
Li_Image* Li_Medeum(Li_Image* img)
{
  if(img->imgdepth==LI_DEP_8U){
    BYTE kek=0;
    BYTE* ptr[9]={0};
    BYTE* ptro;
    Li_Image* out=Li_Copy_Image(img);
    for(int i=0;i<img->height;i++)
        for(int j=0;j<img->width;j++)
        {
             BYTE sum=0;
             for(int k=0;k<9;k++)
             ptr[k]=&kek;
             
             if(j-1>=0&&i-1>=0)
             ptr[0]=(BYTE*)img->at(img,j-1,i-1);
             if(j>=0&&i-1>=0)
             ptr[1]=(BYTE*)img->at(img,j+0,i-1);
             if(j+1<=img->width&&i-1>=0)
             ptr[2]=(BYTE*)img->at(img,j+1,i-1);
             if(j-1>=0&&i>=0)
             ptr[3]=(BYTE*)img->at(img,j-1,i+0);
             if(j>=0&&i>=0)
             ptr[4]=(BYTE*)img->at(img,j+0,i+0);
             if(j+1<=img->width&&i>=0)
             ptr[5]=(BYTE*)img->at(img,j+1,i+0);
             if(j-1>=0&&i+1<=img->height)
             ptr[6]=(BYTE*)img->at(img,j-1,i+1);
             if(j>=0&&i+1<=img->height)
             ptr[7]=(BYTE*)img->at(img,j+0,i+1);
             if(j+1<=img->width&&i+1<=img->height)
             ptr[8]=(BYTE*)img->at(img,j+1,i+1);
            
            BYTE temp[9];
            for(int k=0;k<9;k++)
            {
                
                if(ptr[k]!=NULL)
                {
                    temp[k]= (BYTE)(*ptr[k]);
                }
            }
            for(int m=0;m<9-1;m++)
                for(int n=0;n<9-m-1;n++)
                {
                    if(temp[m]>temp[m+1])
                    {
                        BYTE x=temp[m];
                        temp[m]=temp[n+1];
                        temp[n+1]=x;
                    }
                }
           ptro=(BYTE*)out->at(out,j+0,i+0);
           *ptro=temp[4];
        }
        return out;
  }else if (img->imgdepth==LI_DEP_24U||img->imgdepth==LI_DEP_32U)
  {
     Li_Image* imgH[img->imgdepth+1];
     Li_Image* imgL[img->imgdepth+1];
     Li_Split(img,imgH);
     for(int i=0;i<img->imgdepth+1;i++)
     imgL[i]= Li_Medeum(imgH[i]);     
     Li_Image* out2=Li_Combine(imgL,img->imgdepth);
     return out2;
  }
}

/**
 * @name: Li_Smooth
 * @msg: 计算图像滤波
 * @param {Li_Image* img 原图像
 *         BYTE smoothtype( Li_GAUSS,   //高斯滤波
                            Li_AVERAGE, //均值滤波
                            Li_MEDIUM,  //中值滤波)}
 * @return {Li_Image*}
 */
LI_API
Li_Image* Li_Smooth(Li_Image* img,BYTE smoothtype)
{
    if(img==NULL)return NULL;
    Li_Image* out;
    Li_Kernel* kernel;
    double data1[9]={1.0/9,1.0/9,1.0/9,1.0/9,1.0/9,1.0/9,1.0/9,1.0/9,1.0/9};
    double data2[9]={1.0/16,2.0/16,1.0/16,2.0/16,4.0/16,2.0/16,1.0/16,2.0/16,1.0/16};
    switch (smoothtype)
    {
    case Li_AVERAGE:

        kernel=Li_GetKernel(data1,3);
        out= Li_Convolute(img,kernel);
        break;
    case Li_GAUSS:

        kernel=Li_GetKernel(data2,3);
        out= Li_Convolute(img,kernel);
        break;

    case Li_MEDIUM:
        out=Li_Medeum(img);
        break;
    
    default:
        break;
    }
    return out;
    
}


/**
 * @name: Li_Salt_Noise
 * @msg:  图像椒盐噪声
 * @param {Li_Image* img
 *         LONG num 噪点数量}
 * @return {Li_Image*}
 */
LI_API
Li_Image* Li_Salt_Noise(Li_Image* img,LONG num)
{
    Li_Image* out=Li_Copy_Image(img);
    for(int i=0;i<num;i++){
    LONG x=(LONG)(rand()%img->width);
    LONG y=(LONG)(rand()%img->height);
    BYTE * ptr= out->at(out,x,y);
    int r = rand()%2;
        if(r)
        {
        for(int j=0;j<=img->imgdepth;j++)
            *ptr++=0;
        }
        else
        {
        for(int j=0;j<=img->imgdepth;j++)
            *ptr++=0xFF;
        }  
    }
    return out; 
}


#endif // !LI_SMOOTH_C