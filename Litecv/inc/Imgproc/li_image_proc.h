/*
 * @Descripttion: 
 * @version: 
 * @Author: Yueyang
 * @email: 1700695611@qq.com
 * @Date: 2020-11-04 15:41:55
 * @LastEditors: Yueyang
 * @LastEditTime: 2020-11-11 14:42:56
 */
#ifndef LI_IMG_PROC
#define LI_IMG_PROC

#include "cv.h"
#include "li_image.h"

#define M_PI           3.14159265358979323846  /* pi */

typedef struct tagLi_Kernel
{
    double* arr;//图像数据指针
    LONG width;
    LONG height;
    LONG arrsize;    //数据的大小matsize*depth
}Li_Kernel;

typedef struct tagLi_Line
{
    LONG start_x;
    LONG start_y;
    LONG end_x;
    LONG end_y;
    LONG thera;
    LONG r;
}LiLine;


typedef struct tag_LiPoint
{
    LONG x;
    LONG y;
    struct tag_LiPoint* nextpoint;    
}LiPoint;

typedef struct tag_LiCircle
{
    LONG x;
    LONG y;
    LONG r;
}LiCircle;


enum Li_Smooth_Type
{
    Li_GAUSS,   //高斯滤波
    Li_AVERAGE, //均值滤波
    Li_MEDIUM,  //中值滤波
    
};

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

/**
 * @name: Li_Smooth
 * @msg: 计算图像滤波
 * @param {Li_Image* img 原图像
 *         BYTE smoothtype( Li_GAUSS,   //高斯滤波
                            Li_AVERAGE, //均值滤波
                            Li_MEDIUM,  //中值滤波)}
 * @return {Li_Image*}
 */
LI_API
Li_Image* Li_Smooth(Li_Image* img,BYTE smoothtype);
/**
 * @name: Li_Sharp
 * @msg:  图像锐化
 * @param {Li_Image* img}
 * @return {Li_Image*}
 */
LI_API
Li_Image* Li_Sharp(Li_Image* img);

/**
 * @name: Li_Emboss
 * @msg:  图像雕版
 * @param {Li_Image* img}
 * @return {Li_Image*}
 */
LI_API
Li_Image* Li_Emboss(Li_Image* img);

/**
 * @name: Li_Salt_Noise
 * @msg:  图像椒盐噪声
 * @param {Li_Image* img
 *         LONG num 噪点数量}
 * @return {Li_Image*}
 */
LI_API
Li_Image* Li_Salt_Noise(Li_Image* img,LONG num);

enum CannyType
{
    LI_CANNY_ROBERTS,
    LI_CANNY_SOBEL,
    LI_CANNY_PREWITT,
    LI_CANNY_MYDEFINE
};


/**
 * @name: Li_Double_Threshold
 * @msg:  图像双阈值化
 * @param {Li_Image* img 原图像
 *         double min    小阈值
 *         double max    大阈值
 *         }
 * @return {Li_Image* 二值化后的灰白图像}
 */
LI_API 
Li_Image* Li_Double_Threshold(Li_Image* img,double min,double max);

/**
 * @name: Li_Canny
 * @msg:  参考文章 https://blog.csdn.net/HUSTER_Gy/article/details/102942452?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522160498444419724838560446%2522%252C%2522scm%2522%253A%252220140713.130102334.pc%255Fall.%2522%257D&request_id=160498444419724838560446&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~first_rank_v2~rank_v28-11-102942452.first_rank_ecpm_v3_pc_rank_v2&utm_term=canny%E8%BE%B9%E7%BC%98%E6%A3%80%E6%B5%8B%E7%AE%97%E6%B3%95c%E5%AE%9E%E7%8E%B0&spm=1018.2118.3001.4449
 *        图像砍尼检测
 * @param {Li_Image* img 原图像
 *         BYTE CannyType选择算子
 *         BYTE min      最大阈值
 *         BYTE max}     最小阈值
 * @return {*}
 */
LI_API
Li_Image* Li_Canny(Li_Image* img,BYTE CannyType,BYTE min,BYTE max);



LI_API 
void Li_Hough_Line(Li_Image* img,LiLine* lines, LONG maxthrea,LONG maxr);


LI_API 
LONG Li_Hough_Circle_R(Li_Image* img,LiCircle* circles, LONG R,LONG* range);


LI_API 
void Li_Hough_Circle(Li_Image* img,LiCircle* circles, LONG Rmin,LONG Rmax,LONG* range);

#endif // !LI_IMG_PROC