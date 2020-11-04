/*
 * @Descripttion: 对于图像的处理函数
 * @version: V 2.0
 * @Author: Yueyang
 * @email: 1700695611@qq.com
 * @Date: 2020-11-01 14:01:01
 * @LastEditors: Yueyang
 * @LastEditTime: 2020-11-04 16:31:03
 */
#include "li_image_proc.h"
#include "string.h"

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
  for(int i=0;i<3;i++){
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
 * @name: Li_GetKernel
 * @msg:  得到卷积核矩阵
 * @param {*}
 * @return {*}
 */
LI_API 
Li_Mat* Li_GetKernel(BYTE** data,BYTE KernalKind)
{
    Li_Mat * mat;
    return mat;
}
