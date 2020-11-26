/*
 * @Descripttion: 对于图像的处理函数
 * @version: V 2.0
 * @Author: Yueyang
 * @email: 1700695611@qq.com
 * @Date: 2020-11-01 14:01:01
 * @LastEditors: Yueyang
 * @LastEditTime: 2020-11-24 22:37:30
 */
#include "li_image_proc.h"
#include "string.h"
#include "stdio.h"
#include <stdlib.h>
#include <math.h>
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
 * @name: Li_Double_Threshold
 * @msg:  图像双阈值化
 * @param {Li_Image* img 原图像
 *         double min    小阈值
 *         double max    大阈值
 *         }
 * @return {Li_Image* 二值化后的灰白图像}
 */
LI_API 
Li_Image* Li_Double_Threshold(Li_Image* img,double min,double max)
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
                if(*ptr1>max)
                {
                    *ptr2=0xFF;
                }else if(*ptr1<min)
                {
                    *ptr2=0x00;
                }
            }
        return out;
    }
}

/**
 * @name: Li_Add
 * @msg: 图像像素相加
 * @param {Li_Image* img1,Li_Image* img2}
 * @return {Li_Image*}
 */
LI_API
Li_Image* Li_Add(Li_Image* img1,Li_Image* img2)
{
    int width=img1->width<img2->width?img1->width:img2->width;
    int height=img1->height<img2->height?img1->height:img2->height;
    Li_Image* out= Li_Copy_Image(img1);
    for(int i=0;i<height;i++)
        for(int j=0;j<width;j++)
        {
            BYTE* ptr1,*ptr2,*ptr;
            ptr=out->at(out,j,i);
            ptr1=img1->at(img1,j,i);
            ptr2=img2->at(img2,j,i);
            for(int i=0;i<img1->imgdepth+1;i++)
            {
                if((ptr1[i]+ptr2[i])<255)
                ptr[i]=ptr1[i]+ptr2[i];
                else
                ptr[i]=255;
            }
        }
        return out;
}

/**
 * @name: Li_Minus
 * @msg: 图像像素相加
 * @param {Li_Image* img1,Li_Image* img2}
 * @return {Li_Image*}
 */
LI_API
Li_Image* Li_Minus(Li_Image* img1,Li_Image* img2)
{
    int width=img1->width<img2->width?img1->width:img2->width;
    int height=img1->height<img2->height?img1->height:img2->height;
    Li_Image* out= Li_Copy_Image(img1);
    for(int i=0;i<height;i++)
        for(int j=0;j<width;j++)
        {
            BYTE* ptr1,*ptr2,*ptr;
            ptr=out->at(out,j,i);
            ptr1=img1->at(img1,j,i);
            ptr2=img2->at(img2,j,i);
            for(int i=0;i<img1->imgdepth+1;i++)
            {
                if((ptr1[i]-ptr2[i])>0)
                ptr[i]=ptr1[i]-ptr2[i];
                else
                ptr[i]=0;
            }
        }
        return out;
}


