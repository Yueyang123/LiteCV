/*
 * @Descripttion: 
 * @version: 
 * @Author: Yueyang
 * @email: 1700695611@qq.com
 * @Date: 2020-11-04 15:41:55
 * @LastEditors: Yueyang
 * @LastEditTime: 2020-11-04 16:12:16
 */
#ifndef LI_IMG_PROC
#define LI_IMG_PROC

#include "cv.h"
#include "li_image.h"
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

#endif // !LI_IMG_PROC