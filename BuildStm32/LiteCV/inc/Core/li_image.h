/*
 * @Descripttion: 实现图像类的初始化接口
 * @version: 
 * @Author: Yueyang
 * @email: 1700695611@qq.com
 * @Date: 2020-10-27 22:43:25
 * @LastEditors: Yueyang
 * @LastEditTime: 2020-11-13 18:06:26
 */
#ifndef LI_IMAGE_H
#define LI_IMAGE_H

#include "cv.h"
#include "bmp.h"

/**
 * @name: li_free_arr
 * @msg: 为LiArr释放内存
 * @param {void}
 * @return {void}
 */
LI_API
void li_free_arr(LiArr* arr);

/**
 * @name: li_malloc_arr
 * @msg: 为LiArr申请内存
 * @param {size}申请内存的大小
 * @return {LiArr}数组类型
 */
LI_API
LiArr* li_malloc_arr(LONG size);

/**
 * @name: Li_Create_Mat
 * @msg: 
 * @param       LONG width,LONG height, 高和宽
                BYTE depth,             图像深度
 * @return {Li_Mat}
 */
Li_Mat* Li_Create_Mat(LiArr* data,LONG width,LONG height,BYTE depth);


/**
 * @name: Li_Destroy_Mat
 * @msg: 为LiMat释放内存
 * @param {void}
 * @return {void}
 */
void Li_Destroy_Mat(Li_Mat* mat);

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
Li_Image* Li_Create_Image(LONG width,LONG height,BYTE depth,PICTYPE pth);


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
Li_Image* Li_Copy_Image(Li_Image *img);


/**
 * @name: Li_CvtColor
 * @msg:  提供数组的类型转换不提供类型检查，目标指针在函数内不分配内存
 * @param
          const LiArr* src  原数据
          LiArr *dst        目标数据
          BYTE cvtype       转换方式
 * @return Li_Image*  一张图片
 */
LI_API
void Li_CvtColor( LiArr* src,LiArr *dst,LONG width,LONG height,BYTE cvtype);

/**
 * @name: Li_Convert_Image
 * @msg:  提供图片类型转化，图片类型指针在
 * @param
          const LiArr* src  原数据
          LiArr *dst        目标数据
          BYTE cvtype       转换方式
 * @return Li_Image*  一张图片
 */
LI_API
Li_Image* Li_Convert_Image( Li_Image* src,BYTE convertype);
/**
 * @name: Li_Get_Roi
 * @msg: 获取感兴趣区域
 * @param {Li_Image* img 原图像
 *         LONG x1       左下角所在列号
 *         LONG y1       左下角所在行号
 *         LONG x2       右上角所在列号
 *         LONG y2}      右上角所在行号
 * @return {Li_Image*}
 */
LI_API
Li_Image* Li_Get_Roi(Li_Image* img,LONG x1,LONG y1,LONG x2,LONG y2);

/**
 * @name: Li_ReShape
 * @msg: 调整图像大小
 * @param Li_Image* img  原图像
 *        LONG tag_width 图像宽度
 *        LONG tag_height图像高度
 * @return {*}
 */
LI_API
Li_Image* Li_ReShape(Li_Image* img,LONG tag_width,LONG tag_height);

#endif // !LI_IMAGE_H

