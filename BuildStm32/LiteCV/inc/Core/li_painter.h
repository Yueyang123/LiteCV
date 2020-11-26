/*
 * @Descripttion: 图像画笔 在图像上画一些东西
 *  函数保持如下格式 li_paint_xxx(Li_Image* img,LONG Color,LONG width,LONG height,...)
 * @version: 
 * @Author: Yueyang
 * @email: 1700695611@qq.com
 * @Date: 2020-11-01 14:43:37
 * @LastEditors: Yueyang
 * @LastEditTime: 2020-11-24 21:58:59
 */
#ifndef LI_PAINTER_H
#define LI_PAINTER_H

#include "cv.h"

LI_API
void Li_Point(Li_Image* mat,LONG color,LONG x,LONG y);

LI_API
void Li_Line(Li_Image* mat,LONG color,LONG x1, LONG y1, LONG x2, LONG y2);

LI_API
void Li_Circle(Li_Image* mat ,LONG color,LONG x0,LONG y0,LONG r);

LI_API
void Li_Char(Li_Image* mat,LONG color,LONG x,LONG y,BYTE num,BYTE size);

LI_API
void Li_String(Li_Image* mat,LONG color,LONG x,LONG y,LONG width,LONG height,BYTE*p,BYTE size);

LI_API
void Li_Line_P(Li_Image* mat,LONG color,LONG threa, LONG R);

LI_API 
void Li_Line_H(Li_Image* mat,LONG color,LONG x, LONG length);
#endif // DEBUG
