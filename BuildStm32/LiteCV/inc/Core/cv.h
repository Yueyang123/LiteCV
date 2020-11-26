/*
 * @Descripttion: LITECV顶层头文件，实现基本的数据类型
 * @version: 
 * @Author: Yueyang
 * @email: 1700695611@qq.com
 * @Date: 2020-10-26 19:35:49
 * @LastEditors: Yueyang
 * @LastEditTime: 2020-11-13 17:53:09
 */


#ifndef _CV_H
#define _CV_H


//调试使用的控制台打印
#define DEBUG
#ifdef  DEBUG
#define LILOG(msg)  printf("%s: %s (%s,%d,%s)\n",LOG,msg, __FILE__, __LINE__ ,__FUNCTION__)
#define LOG   "LI_CV_H"
#else  
#define LILOG(msg) 
#endif // DEBUG


//定义可以给用户使用的函数
#define LI_API

//是否支持JPEG与PNG
#define EN_JPEG 0
#define EN_PNG  0

#if EN_JPEG
#define USE_JPEG
#endif

#if EN_PNG
#define USE_PNG
#endif




#define false                0
#define true                 1  
#define LI_FALSE             false
#define LI_TRUE              true  
#define PI                   3.1415926 

#define GUI_RED       0x0000FF
#define GUI_BLUE      0xFF0000
#define GUI_GREEN     0x00FF00
#define RGB565_R      0xF800             //the separate RGB value
#define RGB565_G      0x07E0
#define RGB565_B      0x001F

#define LI_ARGB(a, r, g, b) ((((unsigned int)(a)) << 24) | (((unsigned int)(r)) << 16) | (((unsigned int)(g)) << 8) | ((unsigned int)(b)))
#define LI_ARGB_A(rgb) ((((unsigned int)(rgb)) >> 24) & 0xFF)
#define LI_RGB(r, g, b) ((0xFF << 24) | (((unsigned int)(r)) << 16) | (((unsigned int)(g)) << 8) | ((unsigned int)(b)))
#define LI_RGB_R(rgb) ((((unsigned int)(rgb)) >> 16) & 0xFF)
#define LI_RGB_G(rgb) ((((unsigned int)(rgb)) >> 8) & 0xFF)
#define LI_RGB_B(rgb) (((unsigned int)(rgb)) & 0xFF)
#define LI_RGB_32_to_16(rgb) (((((unsigned int)(rgb)) & 0xFF) >> 3) | ((((unsigned int)(rgb)) & 0xFC00) >> 5) | ((((unsigned int)(rgb)) & 0xF80000) >> 8))
#define LI_RGB_16_to_32(rgb) ((0xFF << 24) | ((((unsigned int)(rgb)) & 0x1F) << 3) | ((((unsigned int)(rgb)) & 0x7E0) << 5) | ((((unsigned int)(rgb)) & 0xF800) << 8))


/*
*             linux64             windows64        linux32         windows32

char          8                   8                8                 8
short         16                  16               16                16
int           32                  32               32                32
long          64                  32               32                32
long long     64                  64               64                64
size_t        64                  64               32                32
*/
//在不同的平台上一些数据的字长不一样
#if (defined _WIN32) || (defined WIN32) || (defined _WIN64) || (defined WIN64)

typedef unsigned short       WORD;
typedef unsigned long        DWORD;
typedef long                 LONG;
typedef unsigned char        BYTE;
typedef unsigned             char uint8_t;
typedef unsigned short       int uint16_t;
typedef unsigned             int uint32_t;
typedef uint32_t             u32;
typedef uint16_t             u16;
typedef uint8_t              u8;
#endif



#if (defined __linux__) || (defined __APPLE__)

typedef unsigned             char uint8_t;
typedef unsigned short       int uint16_t;
typedef unsigned             int uint32_t;
typedef uint32_t             u32;
typedef uint16_t             u16;
typedef uint8_t              u8;
typedef u16                  WORD; //必须是16个字节
typedef u32                  DWORD;//必须是32字节
typedef u32                  LONG; //必须把long固定为32位，直接用long的话是64位
typedef unsigned char        BYTE;

#else
typedef unsigned             char uint8_t;
typedef unsigned short       int uint16_t;
typedef unsigned             int uint32_t;
typedef uint32_t             u32;
typedef uint16_t             u16;
typedef uint8_t              u8;
typedef u16                  WORD; //必须是16个字节
typedef u32                  DWORD;//必须是32字节
typedef u32                  LONG; //必须把long固定为32位，直接用long的话是64位
typedef unsigned char        BYTE;
#endif

typedef enum tagPICTYPE
{ 
 BMP_1, 
 BMP_8,    
 BMP_565,  
 BMP_888 , 
 BMP_32  , 
 JPEG ,
 PNG
}PICTYPE;

enum{
 LI_BMP_1   ,
 LI_BMP_8   ,
 LI_BMP_565 ,
 LI_BMP_888 ,
 LI_BMP_32  ,
 LI_JPEG    ,
 LI_PNG     ,
};

/*
*图像的深度
*/
enum{
 LI_DEP_1U=    -1,//二值图用来适应小内存的情况，也就是说，一个一节存储8个像素

 LI_DEP_8U=    0, //无符号整形变量,每个像素8个

 LI_DEP_16U=   1,//对应BMP RGB565类型的数据

 LI_DEP_24U=   2,//对应BMP RGB888类型的数据

 LI_DEP_32U=   3,//4通道图像

 LI_DEP_64U=   4,//用不到

};


//颜色转换类型
enum
{
    LI_RGB2RGBA,
    LI_RGBA2RGB,
    LI_BGR2BGRA,
    LI_BGRA2BGR,
    LI_BGR2RGB,
    LI_RGB2BGR,
    LI_BGR2GRAY,
    LI_GRAY2BGR,
    LI_BGRA2GRAY,
    LI_RGB2GRAY,
    LI_BGR2YUYV,
    LI_YUYV2BGR,
    LI_BGRA2YUYV
};

//图片类型转换
enum
{
    LI_JPEG_2_BMP,        //图像编解码
    LI_PNG_2_BMP,
    LI_BMP_2_JPEG,
    LI_BMP_2_PNG,
    LI_BMP_888_2_LI_BMP_8,//灰度化
    LI_BMP_8_2_LI_BMP_888,
    LI_BMP_888_2_LI_BMP32,//增加alpha
    LI_BMP_32_2_LI_BMP888

};


enum
{
  LI_FONT_12=12,
  LI_FONT_16=16,
  LI_FONT_24=24,
  LI_FONT_32=32  
};

typedef void LiArr;

typedef struct tagLi_Mat
{
    LiArr* arr;//图像数据指针
    LONG width;
    LONG height;
    BYTE datadepth;  //图像数据的深度
    LONG matsize;    //图像的大小width*height
    LONG arrsize;    //数据的大小matsize*depth
    BYTE Bitcount;   //一个像素点对应的BIT数（(DEP+1)*8）
}Li_Mat;





/**
 *目前支持的图片类型 
 *
 *      从下至上，从左至右
        BMP_8,    
        BMP_888,//BGR 
        BMP_32, //BGRA
        JPEG ,  //存储形式为BGR
        PNG，   //在数组中的存储形式为BGRA

*/

typedef struct tag_LI_Image
{
    Li_Mat limat;
    PICTYPE pt;//指明图片类型
    LONG width;
    LONG height;
    BYTE imgdepth;
    void* data;//指向Li_Mat中的arr，方便操作
    void* (*at)( struct tag_LI_Image* mat,LONG x,LONG y);//一个可以返回像素点对应的头指针的函数指针

}Li_Image;

#endif // !CV_H
