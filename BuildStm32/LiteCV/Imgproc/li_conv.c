/*
 * @Descripttion: 
 * @version: 
 * @Author: Yueyang
 * @email: 1700695611@qq.com
 * @Date: 2020-11-10 21:59:39
 * @LastEditors: Yueyang
 * @LastEditTime: 2020-11-24 21:15:30
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


/**
 * @name: Li_Erode
 * @msg: 图像腐蚀(局部最小)
 * @param {Li_Image* img}
 * @return {Li_Image*}
 */
LI_API
Li_Image* Li_Erode(Li_Image* img)
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
           *ptro=temp[0];
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
 * @name: Li_Dilate
 * @msg: 图像膨胀(局部最小)
 * @param {Li_Image* img}
 * @return {Li_Image*}
 */
LI_API
Li_Image* Li_Dilate(Li_Image* img)
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
           *ptro=temp[8];
        }
        return out;
  }else if (img->imgdepth==LI_DEP_24U||img->imgdepth==LI_DEP_32U)
  {
     Li_Image* imgH[img->imgdepth+1];
     Li_Image* imgL[img->imgdepth+1];
     Li_Split(img,imgH);
     for(int i=0;i<img->imgdepth+1;i++)
     imgL[i]= (Li_Image*)Li_Medeum(imgH[i]);     
     Li_Image* out2=Li_Combine(imgL,img->imgdepth);
     return out2;
  }
}

/**
 * @name: Li_Grandient
 * @msg: 形态学梯度
 * @param {Li_Image* img}
 * @return {Li_Image*}
 */
LI_API
Li_Image* Li_Grandient(Li_Image* img)
{
    Li_Image* erode=Li_Erode(img);
    Li_Image* dilate=Li_Dilate(img);
    Li_Image* minus=Li_Minus(dilate,erode);
    Li_Destroy_Image(erode);
    Li_Destroy_Image(dilate);
    return minus;
}

/**
 * @name: Li_Mod_Open
 * @msg: 形态学开运算
 * @param {Li_Image* img}
 * @return {Li_Image* }
 */
LI_API
Li_Image* Li_Mod_Open(Li_Image* img)
{
    Li_Image* dilate=Li_Dilate(img);//先膨胀
    Li_Image* erode=Li_Erode(dilate);//先腐蚀
    Li_Destroy_Image(dilate);
    return erode;
}

/**
 * @name: Li_Mod_Close
 * @msg: 形态学闭运算
 * @param {Li_Image* img}
 * @return {Li_Image* }
 */
LI_API
Li_Image* Li_Mod_Close(Li_Image* img)
{
    Li_Image* erode=Li_Erode(img);//先腐蚀
    Li_Image* dilate=Li_Dilate(erode);//先膨胀
    Li_Destroy_Image(erode);
    return dilate;
}

/**
 * @name: Li_TopHat
 * @msg: 图像顶帽运算
 * @param {Li_Image* img}
 * @return {Li_Image*}
 */
LI_API
Li_Image* Li_TopHat(Li_Image* img)
{
    Li_Image* open=Li_Mod_Open(img);
    Li_Image* top=Li_Minus(img,open);
    Li_Destroy_Image(open);
    return top;
}

/**
 * @name: Li_BlackHat
 * @msg: 图像黑帽运算
 * @param {Li_Image* img}
 * @return {Li_Image*}
 */
LI_API
Li_Image* Li_BlackHat(Li_Image* img)
{
    Li_Image* close=Li_Mod_Close(img);
    Li_Image* black=Li_Minus(img,close);
    Li_Destroy_Image(close);
    return black;
}

#endif // !LI_CONV_C