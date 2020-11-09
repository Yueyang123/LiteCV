/*
 * @Descripttion: 对于图像的处理函数
 * @version: V 2.0
 * @Author: Yueyang
 * @email: 1700695611@qq.com
 * @Date: 2020-11-01 14:01:01
 * @LastEditors: Yueyang
 * @LastEditTime: 2020-11-10 01:43:54
 */
#include "li_image_proc.h"
#include "string.h"
#include "stdio.h"
#undef  LOG
#define LOG  "LI_CV_PROC"

/**
 * @name: Li_Split
 * @msg:  图像色道分离
 * @param {Li_Image* img  原图像
 *         Li_Image**     色道分离以后的图像}
 * @return {}
 */
LI_API
void Li_Split(Li_Image* img,Li_Image** out)
{
  for(int i=0;i<img->imgdepth+1;i++){
    out[i]=Li_Create_Image(img->width,img->height,LI_DEP_8U,LI_BMP_8);
  }

  for(int i=0;i<(img->width)*(img->height)*(img->imgdepth+1);i+=(img->imgdepth+1))
  {
      for(int j=0;j<(img->imgdepth+1);j++)
      {
          *((BYTE*)out[j]->data + (i/(img->imgdepth+1)))=*((BYTE*)img->data+i+j);
      }
  }
}

/**
 * @name: Li_Combine
 * @msg:  图像色道分离
 * @param {Li_Image** out 待合并的图像
 *         BYTE depth     要合成的图像深度}
 * @return {}
 */
LI_API
Li_Image*  Li_Combine(Li_Image** out,BYTE depth)
{
    Li_Image* img;
    if(depth==LI_DEP_24U)
    img=Li_Create_Image(out[0]->width,out[0]->height,depth,LI_BMP_888);
    else
    img=Li_Create_Image(out[0]->width,out[0]->height,depth,LI_BMP_32);  
    
    for(int i=0;i<(img->width)*(img->height)*(img->imgdepth+1);i+=(img->imgdepth+1))
    {
        for(int j=0;j<(img->imgdepth+1);j++)
        {
            *((BYTE*)img->data+i+j)=*((BYTE*)out[j]->data + (i/(img->imgdepth+1)));
        }
    }
    return img;
}


/**
 * @name: Li_Threshold
 * @msg:  图像阈值化
 * @param {Li_Image* img 原图像
 *         double threshold 图像阈值0-255
 *         }
 * @return {Li_Image* 二值化后的灰白图像}
 */
LI_API 
Li_Image* Li_Threshold(Li_Image* img,double threshold)
{
    Li_Image* out=Li_Copy_Image(img);
    if(img->pt!=LI_BMP_8)return NULL;
    else
    {
        
        for(int i=0;i<img->height;i++)
            for(int j=0;j<img->width;j++)
            {
                BYTE * ptr1 =img->at(img,j,i);
                BYTE * ptr2 =out->at(out,j,i);
                if(*ptr1>threshold)
                {
                    *ptr2=0xFF;
                }else
                {
                    *ptr2=0x00;
                }
            }
        return out;
    }
    
}


/**
 * @name: Li_GetKernel
 * @msg:  得到卷积核矩阵
 * @param {*}
 * @return {*}
 */
LI_API 
Li_Kernel* Li_GetKernel(double* data,BYTE KernalKind)
{
    Li_Kernel * kernel;
    kernel=(Li_Kernel*)li_malloc_arr(sizeof(Li_Kernel));
    kernel->arr=(double*)li_malloc_arr(KernalKind*KernalKind*sizeof(double));
    for(int i=0;i<KernalKind*KernalKind-1;i++)
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
                else  sum+=0;
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
     Li_Image* out2=Li_Combine(imgL,LI_DEP_32U);
     return out2;
  }
}
