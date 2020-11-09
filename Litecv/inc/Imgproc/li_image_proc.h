/*
 * @Descripttion: 
 * @version: 
 * @Author: Yueyang
 * @email: 1700695611@qq.com
 * @Date: 2020-11-04 15:41:55
 * @LastEditors: Yueyang
 * @LastEditTime: 2020-11-10 01:39:14
 */
#ifndef LI_IMG_PROC
#define LI_IMG_PROC

#include "cv.h"
#include "li_image.h"

typedef struct tagLi_Kernel
{
    double* arr;//图像数据指针
    LONG width;
    LONG height;
    LONG arrsize;    //数据的大小matsize*depth
}Li_Kernel;
/**
 * @name: Li_Split
 * @msg:  图像色道分离
 * @param {Li_Image* img}
 * @return {Li_Image** 图像指针的指针}
 */
LI_API
void Li_Split(Li_Image* img,Li_Image** out);

/**
 * @name: Li_Split
 * @msg:  图像色道分离
 * @param {Li_Image* img  原图像
 *         Li_Image**     色道分离以后的图像}
 * @return {}
 */
LI_API
Li_Image*  Li_Combine(Li_Image** out,BYTE depth);


/**
 * @name: Li_Threshold
 * @msg:  图像阈值化
 * @param {Li_Image* img 原图像
 *         double threshold 图像阈值0-255
 *         }
 * @return {Li_Image* 二值化后的灰白图像}
 */
LI_API 
Li_Image* Li_Threshold(Li_Image* img,double threshold);


/**
 * @name: Li_Convolute
 * @msg: 计算图像卷积
 * @param {Li_Image* img 卷积图像
 *         Li_Kernel* kernal 卷积核 }
 * @return {Li_Image*}
 */
LI_API
Li_Image* Li_Convolute(Li_Image* img,Li_Kernel* kernal);


/**
 * @name: Li_GetKernel
 * @msg:  得到卷积核矩阵
 * @param {*}
 * @return {*}
 */
LI_API 
Li_Kernel* Li_GetKernel(double* data,BYTE KernalKind);

#endif // !LI_IMG_PROC