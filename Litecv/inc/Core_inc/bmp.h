/*
 * @Descripttion: 提供对于BMP文件的底层处理函数
 * @version: V2.0
 * @Author: Yueyang
 * @email: 1700695611@qq.com
 * @Date: 2020-10-26 19:35:49
 * @LastEditors: Yueyang
 * @LastEditTime: 2020-10-31 12:06:11
 */

#ifndef BMP_H_INCLUDED
#define BMP_H_INCLUDED
#include "stdio.h"
#include "cv.h"

/*
 *
 *   黑白：文件头(14字节)+信息头(40字节)+2个调色板(共8字节)+Height(图像高度)*(Width+8-Width%8)/8    

     16色：文件头(14字节)+信息头(40字节)+16个调色板(共64字节)+Height(图像高度)*(Width+4-Width%4)/2    

     256色：文件头(14字节)+信息头(40字节)+256个调色板(共1024字节)+Height(图像高度)*(Width+4-Width%4)

     16位色：文件头(14字节)+信息头(40字节)+Height(图像高度)*(Width+4-Width%4)*2 (由于每个像素由两个字节表示)

     24位色：文件头(14字节)+信息头(40字节)+Height(图像高度)*(Width+4-Width%4)*3 (由于每个像素由三个字节表示)
 * */

/**
 * 字 段 名
描 述

biSize(填40进去)
4
本结构的大小，根据不同的操作系统而不同，在Windows中，此字段的值总为28h字节=40字

biWidth
4
BMP图像的宽度，单位像素
biHeight
4
BMP图像的高度，单位像素

biPlanes(1)
2
总为1

biBitCount（DRP+1）*8
2
BMP图像的色深，即一个像素用多少位表示，常见有1、4、8、16、24和32，分别对应单色、16色、256色、16位高彩色、24位真彩色和32位增强型真彩色

biCompression（0）
4
压缩方式，0表示不压缩，1表示RLE8压缩，2表示RLE4压缩，3表示每个像素值由指定的掩码决定

biSizeImage
4
BMP图像数据大小，必须是4的倍数，图像数据大小不是4的倍数时用0填充补足

//可以决定在物理上图片的大小
biXPelsPerMeter（3780）
4
水平分辨率，单位像素/m
biYPelsPerMeter（3780）
4
垂直分辨率，单位像素/m

biClrUsed（0）
4
BMP图像使用的颜色，0表示使用全部颜色，对于256色位图来说，此值为100h=256

biClrImportant（0）
4
重要的颜色数，此值为0时所有颜色都重要，对于使用调色板的BMP图像来说，
当显卡不能够显示所有颜色时，此值将辅助驱动程序显示颜色
*/

/*
*   与BMP文件有关的变量
*/
typedef struct 
{ // bmih
    DWORD biSize;
    LONG   biWidth;
    LONG   biHeight;
    WORD   biPlanes;
    WORD   biBitCount;
    DWORD biCompression;
    DWORD biSizeImage;
    LONG   biXPelsPerMeter;
    LONG   biYPelsPerMeter;
    DWORD biClrUsed;
    DWORD biClrImportant;
}BITMAPINFOHEADER;


/*
*bfType：位图文件类型，必须是0x424D，即字符串“BM”，也就是说，所有的“*.bmp”文件的头两个字节都是“BM”。
*bfSize：位图文件大小，包括这14个字节。
*bfReserved1, bfReserved2：Windows保留字，暂不用。
*bfOffBits：(bfsize+bisize)从文件头到实际的位图数据的偏移字节数
*/
typedef struct 
{ // bmfh
    WORD    bfType;
    DWORD   bfSize;
    WORD    bfReserved1;
    WORD    bfReserved2;
    DWORD   bfOffBits;
}BITMAPFILEHEADER;

//调色板
typedef struct
{
	unsigned char rgbBlue; //该颜色的蓝色分量  
	unsigned char rgbGreen; //该颜色的绿色分量  
	unsigned char rgbRed; //该颜色的红色分量  
	unsigned char rgbReserved; //保留值  
} RGBQuad;



/**
 * @name: Read_bmp
 * @msg: 读取一个BMP图片
 * @param char *filepath        读取文件的路径
 *        BITMAPFILEHEADER *bmf 与文件有关的信息
 *        BITMAPINFOHEADER *bmi 与图片有关的信息
 * @return 数据指针
 */
BYTE* Read_bmp(BYTE *filepath,BITMAPFILEHEADER *bmf,BITMAPINFOHEADER *bmi);
/**
 * @name: 
 * @msg: 写BMP图片，只负责写数据，没有图片的转换功能
 * @param char *filepath        读取文件的路径
 *        BYTE *imgData         读到的数据
 *        BITMAPFILEHEADER *bmf 与文件有关的信息
 *        BITMAPINFOHEADER *bmi 与图片有关的信息
 *        PICTYPE pt            图片类型
 * @return 0 (right) or -1(something wrong)
 */
BYTE Write_bmp(BYTE *filepath,BYTE *imgData,BITMAPFILEHEADER *bmf,BITMAPINFOHEADER *bmi,PICTYPE pt);

void Print_bmp_FileHeader(BITMAPFILEHEADER *bmfh);
void Print_bmp_InfoHeader(BITMAPINFOHEADER *bmih);

#endif 







