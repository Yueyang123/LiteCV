/*
 * @Descripttion: 
 * @version: 
 * @Author: Yueyang
 * @email: 1700695611@qq.com
 * @Date: 2020-11-10 21:59:39
 * @LastEditors: Yueyang
 * @LastEditTime: 2020-11-10 22:43:22
 */
#ifndef LI_CONV_C
#define LI_CONV_C



#include "cv.h"
#include "li_image_proc.h"
#include <stdio.h>


/**
 * @name: Li_GetKernel
 * @msg:  得到卷积核矩阵
 * @param {double* data 数据
 *         BYTE KernalKind 卷积核边长}
 * @return {Li_Kernel*}
 */
LI_API 
Li_Kernel* Li_GetKernel(double* data,BYTE KernalKind)
{
    Li_Kernel * kernel;
    kernel=(Li_Kernel*)li_malloc_arr(sizeof(Li_Kernel));
    kernel->arr=(double*)li_malloc_arr(KernalKind*KernalKind*sizeof(double));
    for(int i=0;i<KernalKind*KernalKind;i++)
    kernel->arr[i]=data[i];
    kernel->width=KernalKind;
    kernel->height=KernalKind;
    kernel->arrsize=KernalKind*KernalKind;
    return kernel;
}

/**
 * @name: Li_Convolute
 * @msg: 计算图像卷积
 * @param {Li_Image* img 卷积图像
 *         Li_Kernel* kernal 卷积核 }
 * @return {Li_Image*}
 */
LI_API
Li_Image* Li_Convolute(Li_Image* img,Li_Kernel* kernal)
{
  if(img->imgdepth==LI_DEP_8U){
    if(kernal->width!=3) return NULL;
    BYTE* ptr[9]={0};
    BYTE* ptro;
    Li_Image* out=Li_Copy_Image(img);
    for(int i=0;i<img->height;i++)
        for(int j=0;j<img->width;j++)
        {
             BYTE sum=0;
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
            for(int k=0;k<9;k++)
            {
                double* ptr2=(double*)(kernal->arr+k);
                if(ptr[k]!=NULL)
                {
                    sum+= (BYTE)(*ptr[k] * (*ptr2));
                }
                else 
                {
                    sum+=0;
                }
            }
            ptro=(BYTE*)out->at(out,j+0,i+0);
            *ptro=sum;
        }
        return out;
  }else if (img->imgdepth==LI_DEP_24U||img->imgdepth==LI_DEP_32U)
  {
     Li_Image* imgH[img->imgdepth+1];
     Li_Image* imgL[img->imgdepth+1];
     Li_Split(img,imgH);
     for(int i=0;i<img->imgdepth+1;i++)
     imgL[i]= Li_Convolute(imgH[i],kernal);     
     Li_Image* out2=Li_Combine(imgL,img->imgdepth);
     return out2;
  }
}


/**
 * @name: Li_Sharp
 * @msg:  图像锐化
 * @param {Li_Image* img}
 * @return {Li_Image*}
 */
LI_API
Li_Image* Li_Sharp(Li_Image* img)
{
    double data[9]={1,1,1,1,-7,1,1,1,1}; 
    if(img==NULL)return NULL;
    if(img->imgdepth==LI_DEP_8U){
        Li_Image* out;
        Li_Kernel* kernel;

        kernel=Li_GetKernel(data,3);
        out= Li_Convolute(img,kernel);
        return out;
    }else if (img->imgdepth==LI_DEP_24U||img->imgdepth==LI_DEP_32U)
    {
        Li_Image* imgH[img->imgdepth+1];
        Li_Image* imgL[img->imgdepth+1];
        Li_Split(img,imgH);
        for(int i=0;i<img->imgdepth+1;i++)  
        {
            imgL[i]=Li_Sharp(imgH[i]);
        }
        Li_Image* out2=Li_Combine(imgL,img->imgdepth);
        return out2;
    }
}

/**
 * @name: Li_Emboss
 * @msg:  图像雕版
 * @param {Li_Image* img}
 * @return {Li_Image*}
 */
LI_API
Li_Image* Li_Emboss(Li_Image* img)
{
    double data[9]={0,0,-1,0,-1,0,2,0,0}; 
    if(img==NULL)return NULL;
    if(img->imgdepth==LI_DEP_8U){
        Li_Image* out;
        Li_Kernel* kernel;

        kernel=Li_GetKernel(data,3);
        out= Li_Convolute(img,kernel);
        return out;
    }else if (img->imgdepth==LI_DEP_24U||img->imgdepth==LI_DEP_32U)
    {
        Li_Image* imgH[img->imgdepth+1];
        Li_Image* imgL[img->imgdepth+1];
        Li_Split(img,imgH);
        for(int i=0;i<img->imgdepth+1;i++)  
        {
            imgL[i]=Li_Emboss(imgH[i]);
        }
        Li_Image* out2=Li_Combine(imgL,img->imgdepth);
        return out2;
    }
}

#endif // !LI_CONV_C