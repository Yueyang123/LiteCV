/*
 * @Descripttion: 实现图像类的初始化接口
 * @version: 
 * @Author: Yueyang
 * @email: 1700695611@qq.com
 * @Date: 2020-10-27 22:43:25
 * @LastEditors: Yueyang
 * @LastEditTime: 2020-11-01 14:13:00
 */
#ifndef LI_IMAGE_H
#define LI_IMAGE_H

#include "cv.h"

/**
 * @name: Li_Load_Image
 * @msg: 用户接口函数，用来读取一张图片
 *       对于是否支持jpeg 与 png 可以通过cv.h中的宏定义调整
 * @param
 *        BYTE *filepath        图片路径
 *        PICTYPE pt            图片类型
 * @return 0 (right) or -1(something wrong)
 */
LI_API
Li_Image* Li_Load_Image(BYTE* filepath,PICTYPE pt);



/**
 * @name: Li_Save_Image
 * @msg: 用户接口函数，用来保存一张图片
 *       对于是否支持jpeg 与 png 可以通过cv.h中的宏定义调整
 * @param
 *        BYTE *filepath        图片路径
 *        Li_Image* img         Litecv图片类型
 * @return 0 (right) or -1(something wrong)
 */
LI_API
BYTE Li_Save_Image(BYTE* filepath,Li_Image* img);


/**
 * @name: Li_Destroy_Image
 * @msg: 用户接口函数，用来删除一张图片
 * @param
          Li_Image * img
 * @return 0 (right) or -1(something wrong)
 */
LI_API
void Li_Destroy_Image(Li_Image * img);


/**
 * @name: Li_Create_Imgae
 * @msg: 用户接口函数，用来创建一张图片
 * @param
        LONG width  图片宽度
        LONG height 图片高度
        BYTE depth  颜色深度
        PICTYPE pth 图片类型
 * @return Li_Image*  一张图片
 */
LI_API
Li_Image* Li_Create_Imgae(LONG width,LONG height,BYTE depth,PICTYPE pth);


/**
 * @name: Li_Copy_Imgae
 * @msg: 用户接口函数，用来创建一张图片
 * @param
        LONG width  图片宽度
        LONG height 图片高度
        BYTE depth  颜色深度
        PICTYPE pth 图片类型
 * @return Li_Image*  一张图片
 */
LI_API
Li_Image* Li_Copy_Imgae(Li_Image *img);

#endif // !LI_IMAGE_H

