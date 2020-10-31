/*
 * @Descripttion: 实现图像类的初始化接口
 * @version: 
 * @Author: Yueyang
 * @email: 1700695611@qq.com
 * @Date: 2020-10-27 22:43:25
 * @LastEditors: Yueyang
 * @LastEditTime: 2020-10-31 14:22:21
 */
#ifndef LI_IMAGE_H
#define LI_IMAGE_H

#include "cv.h"
/**
 * @name: ptr_li_image_create
 * @msg:  创建Li_image  类型指针
 * @param 
 *      LiArr* data,(已经初始化过的数据指针)
 *      LONG width,LONG height,
 *      BYTE depth,PICTYPE pth（图片类型）
 * @return {Li_Image}一个图片
 */
Li_Image* ptr_li_image_create(
LiArr* data,
LONG width,LONG height,
BYTE depth,PICTYPE pth);

#ifdef USE_JPEG
BYTE* Read_Jpeg(BYTE* filepath,LONG* wdith,LONG* height);
BYTE  Write_Jpeg(BYTE *filepath,BYTE* image_buffer, LONG quality,LONG image_height,LONG image_width);
#endif

#ifdef USE_PNG
BYTE* Read_Png(BYTE* filepath,LONG* width,LONG* height);
BYTE  Write_Png(BYTE* png_file_name, BYTE*  pixels , LONG width, LONG height, LONG bit_depth);
#endif
BITMAPFILEHEADER get_default_file_head(Li_Mat m);
BITMAPINFOHEADER get_default_info_head(Li_Mat m);


LI_API
Li_Image* Li_Load_Image(BYTE* filepath,PICTYPE pt);


LI_API
BYTE Li_Save_Image(BYTE* filepath,Li_Image* img);
#endif // !LI_IMAGE_H

