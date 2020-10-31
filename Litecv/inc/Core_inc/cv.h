/*
 * @Descripttion: LITECV顶层头文件，实现基本的数据类型
 * @version: 
 * @Author: Yueyang
 * @email: 1700695611@qq.com
 * @Date: 2020-10-26 19:35:49
 * @LastEditors: Yueyang
 * @LastEditTime: 2020-10-31 13:36:11
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
#define EN_JPEG 1
#define EN_PNG  1

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
 LI_BMP_1   =    0,
 LI_BMP_8   =    1,
 LI_BMP_565 =    2,
 LI_BMP_888 =    3,
 LI_BMP_32  =    4,
 LI_JPEG    =    5,
 LI_PNG     =    6,
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

typedef struct tagLiPoit
{
    LONG x;
    LONG y;
}Li_Point;

typedef void LiArr;

typedef struct tagLi_Mat
{
    LiArr* arr;//图像数据指针
    union
    {
       LONG width;
       LONG cols;
    };
    union 
    {
        LONG height;
        LONG rows;
    };

    BYTE datadepth;  //图像数据的深度
    LONG matsize;    //图像的大小width*height
    LONG arrsize;    //数据的大小matsize*depth
    BYTE Bitcount;   //一个像素点对应的BIT数（(DEP+1)*8）

    void* (*at)(void* data,LONG x,LONG y);//一个可以返回像素点对应的头指针的函数指针
    void* (*atat)(void* data,LONG x,LONG y,LONG index);//更进一步换算某一个通道所在的指针域
}Li_Mat;

typedef struct tag_LI_Image
{
    Li_Mat limat;
    PICTYPE pt;//指明图片类型
    void* data;//指向Li_Mat中的arr，方便操作
    void* (*at)(void* data,LONG x,LONG y);//一个可以返回像素点对应的头指针的函数指针
    void* (*atat)(void* data,LONG x,LONG y,LONG index);//更进一步换算某一个通道所在的指针域
    /**
     *目前支持的图片类型 
     *
        BMP_8,    
        BMP_888 , 
        BMP_32  , 
        JPEG ,
        PNG，
        BW      //黑白图片数据类型
                //除了通过这个库其他的软件无法正常显示
     */

}Li_Image;

#endif // !CV_H