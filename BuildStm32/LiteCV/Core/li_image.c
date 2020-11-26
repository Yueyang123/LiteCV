/*
 * @Descripttion: 图像类基本的初始化函数
 * @version: V 2.0
 * @Author: Yueyang
 * @email: 1700695611@qq.com
 * @Date: 2020-10-27 22:41:59
 * @LastEditors: Yueyang
 * @LastEditTime: 2020-11-10 22:33:27
 */
#include "cv.h"
#include "stdlib.h"
#include "string.h"
#include "bmp.h"

#undef  LOG
#define LOG  "LI_CV_CORE"

/**
 * @name: li_malloc_arr
 * @msg: 为LiArr申请内存
 * @param {size}申请内存的大小
 * @return {LiArr}数组类型
 */
LI_API
LiArr* li_malloc_arr(LONG size)
{
    return (LiArr*)malloc((size_t)size);
}

/**
 * @name: li_free_arr
 * @msg: 为LiArr释放内存
 * @param {void}
 * @return {void}
 */
void li_free_arr(LiArr* arr)
{
    free((void *)arr);
}

/**
 * @name: Li_Destroy_Mat
 * @msg: 为LiMat释放内存
 * @param {void}
 * @return {void}
 */
void Li_Destroy_Mat(Li_Mat* mat)
{
  li_free_arr(mat->arr);
  free((void*)mat);
}

/**
 * @name: li_bgr_at
 * @msg: 
 * @param {Li_Image* mat
 *         LONG x 指针所在列号
 *         LONG y 所在行号}
 * @return {*}
 */
LiArr* li_bgr_at(Li_Image* mat,LONG x,LONG y)
{
	BYTE* ptr;
  if(x<mat->width&&y<mat->height){
		ptr=((BYTE*)mat->data)+mat->width*(1+mat->imgdepth)*y+(1+mat->imgdepth)*x;
		return ptr;
	}
  else {
  LILOG("BEYOND THE MAT");
  return NULL;
  }
}

LiArr* li_gray_at(Li_Image* mat,LONG x,LONG y)
{
	BYTE* ptr;
  if(x<mat->width&&y<mat->height){
		ptr=(BYTE*)mat->data+mat->width*1*y+1*x;
		return ptr;
	}
  else {
  //LILOG("BEYOND THE MAT");
  return NULL;
  }
}

LiArr* li_rgba_at(Li_Image* mat,LONG x,LONG y)
{
	BYTE* ptr;
  if(x<mat->width&&y<mat->height){
		ptr=(BYTE*) mat->data+mat->width*4*y+4*x;
		return ptr;
	}
  else {
  LILOG("BEYOND THE MAT");
  return NULL;
  }
}

/**
 * @name: Li_Create_Mat
 * @msg: 
 * @param       LONG width,LONG height, 高和宽
                BYTE depth,             图像深度
 * @return {Li_Mat}
 */
Li_Mat* Li_Create_Mat(
LiArr* data,
LONG width,LONG height,
BYTE depth)
{
    Li_Mat* li_mat=(Li_Mat*)malloc(sizeof(Li_Mat));
    li_mat->datadepth= depth;
    li_mat->height   = height;
    li_mat->width    = width;
    li_mat->matsize=width*height;
    
    if(depth!=LI_DEP_1U) {
        li_mat->Bitcount =(depth+1)*8;
        li_mat->arrsize=li_mat->matsize*(depth+1);
    }
    else {
        li_mat->Bitcount=1;
        li_mat->arrsize=li_mat->matsize*1/8;//对于二值化图像一个BYTE代表8个像素点
    }    
    
    li_mat->arr=li_malloc_arr(li_mat->arrsize);
    memcpy(li_mat->arr,data,li_mat->arrsize);

    return li_mat;
}


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
LiArr* dt,
LONG width,LONG height,
BYTE depth,PICTYPE pth)
{
    Li_Image* img =(Li_Image*)malloc(sizeof(Li_Image));
    Li_Mat* limt=NULL;
    img->pt=pth;
    img->data=dt;
    img->width=width;
    img->height=height;
    img->imgdepth=depth;

  switch (pth)
  {
  case LI_BMP_888:
    limt= Li_Create_Mat(dt,width,height,depth);
    memcpy(&img->limat,limt,sizeof(Li_Mat));//数据指针一并过来了，所以li_mat->arr不能释放
    img->at=li_bgr_at;
    break;
  
   case LI_JPEG:
    limt= Li_Create_Mat(dt,width,height,depth);
    memcpy(&img->limat,limt,sizeof(Li_Mat));//数据指针一并过来了，所以li_mat->arr不能释放
    img->at=li_bgr_at;
    break;

   case LI_BMP_8:
    limt= Li_Create_Mat(dt,width,height,depth);
    memcpy(&img->limat,limt,sizeof(Li_Mat));//数据指针一并过来了，所以li_mat->arr不能释放
    img->at=li_gray_at;
    break;  

   case LI_BMP_32:
    limt= Li_Create_Mat(dt,width,height,depth);
    memcpy(&img->limat,limt,sizeof(Li_Mat));//数据指针一并过来了，所以li_mat->arr不能释放
    img->at=li_rgba_at;
    break; 

   case LI_PNG:
    limt= Li_Create_Mat(dt,width,height,depth);
    memcpy(&img->limat,limt,sizeof(Li_Mat));//数据指针一并过来了，所以li_mat->arr不能释放
    img->at=li_rgba_at;
    break; 
  
  default:
    break;
  }  
    return img;
}


/**
 * @name: ptr_li_image_destroy
 * @msg:  销毁Li_image  类型指针
 * @param {Li_Image* }一个图片指针
 *      
 * @return void
 */
void ptr_li_image_destroy(Li_Image* img)
{
  li_free_arr(img->limat.arr);
  free(img);
}

//获取默认的BMP文件头
BITMAPFILEHEADER get_default_file_head(Li_Mat m)
{
   LONG DataSizePerLine = (m.width * m.Bitcount /8+ 3) / 4*4;
   BITMAPFILEHEADER bf;
   if(m.datadepth!=LI_DEP_8U&&m.datadepth!=LI_DEP_1U)
   bf.bfOffBits=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)-2;
   else if(m.datadepth==LI_DEP_8U) 
   bf.bfOffBits=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+1024-2;
   else if(m.datadepth==LI_DEP_1U) 
   bf.bfOffBits=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+8-2;
   
   bf.bfSize   =DataSizePerLine*m.height+bf.bfOffBits;
   bf.bfType   =19778;//"BM"
   bf.bfReserved1=0;
   bf.bfReserved2=0;
   return bf;
}

//获取默认的BMP信息
BITMAPINFOHEADER get_default_info_head(Li_Mat m)
{
   LONG DataSizePerLine = (m.width * m.Bitcount /8+ 3) / 4*4;
   BITMAPINFOHEADER bi;
   bi.biBitCount=m.Bitcount;
   bi.biSize    =40;
   bi.biWidth   =m.width;
   bi.biHeight  =m.height;
   bi.biPlanes  =1;
   bi.biClrImportant=0;
   bi.biClrUsed =0;//默认全都用
   if(m.Bitcount!=32){
   bi.biXPelsPerMeter=3780;//默认大小
   bi.biYPelsPerMeter=3780;
   }else
   {
    bi.biXPelsPerMeter=0;//默认大小
    bi.biYPelsPerMeter=0;    
   }
   bi.biSizeImage=DataSizePerLine*bi.biHeight;
   bi.biCompression=0;//默认不压缩
   return bi;
}



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
BYTE Li_Save_Image(BYTE* filepath,Li_Image* img)
{
  if(img==NULL)
  {
    LILOG("A NULL IMG");
    return -1;
  }
  BYTE sta;
  BITMAPFILEHEADER bf;
  BITMAPINFOHEADER bi;
  switch (img->pt)
  {
   case LI_BMP_888:
     bf= get_default_file_head(img->limat);
     bi= get_default_info_head(img->limat);
     sta=Write_bmp(filepath,img->data,&bf,&bi,img->pt);
    break;
   case LI_BMP_32:
     bf= get_default_file_head(img->limat);
     bi= get_default_info_head(img->limat);
     sta=Write_bmp(filepath,img->data,&bf,&bi,img->pt);
    break;
   case LI_BMP_8:
     bf= get_default_file_head(img->limat);
     bi= get_default_info_head(img->limat);
     sta=Write_bmp(filepath,img->data,&bf,&bi,img->pt);    
    break; 
   
#ifdef USE_JPEG
   case LI_JPEG:
     LILOG("WRITE JPEG");
     sta=Write_Jpeg(filepath,img->data,100,img->limat.width,img->limat.height);
     break;
#endif

#ifdef USE_PNG
   case LI_PNG:
     sta=Write_Png(filepath,img->data,img->limat.width,img->limat.height);
     break;
#endif

  default:
    break;
  }
  return sta;
}


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
Li_Image* Li_Load_Image(BYTE* filepath,PICTYPE pt)
{
    BYTE* data;
    LONG width,height;
    int depth;
    BITMAPFILEHEADER bf;
    BITMAPINFOHEADER bi;
    Li_Image* img=NULL;
    switch (pt)
    {
    case LI_BMP_888:
      LILOG("BMP888");
      data=Read_bmp(filepath,&bf,&bi);
      width=bi.biWidth;
      height=bi.biHeight;
      depth=LI_DEP_24U;
      img=ptr_li_image_create(data,width,height,depth,pt);
      break;

    case LI_BMP_32:
      LILOG("BMP32");
      data=Read_bmp(filepath,&bf,&bi);
      width=bi.biWidth;
      height=bi.biHeight;
      depth=LI_DEP_32U;
      img=ptr_li_image_create(data,width,height,depth,pt);
      break;

    case LI_BMP_8:
      LILOG("BMP8");
      data=Read_bmp(filepath,&bf,&bi);
      width=bi.biWidth;
      height=bi.biHeight;
      depth=LI_DEP_8U;
      img=ptr_li_image_create(data,width,height,depth,pt);
      break;
    
    case LI_BMP_565:
      LILOG("BMP16");
      data=Read_bmp(filepath,&bf,&bi);
      width=bi.biWidth;
      height=bi.biHeight;
      depth=LI_DEP_16U;
      img=ptr_li_image_create(data,width,height,depth,pt);
      break;

#ifdef USE_JPEG
    case LI_JPEG:
      LILOG("JPEG");
      data=Read_Jpeg(filepath,&width,&height);
      depth=LI_DEP_24U;
      img=ptr_li_image_create(data,width,height,depth,pt);
      break;
#endif 

#ifdef USE_PNG
    case LI_PNG:
      
      LILOG("PNG");
      data=Read_Png(filepath,&width,&height);
      depth=LI_DEP_32U;
      img=ptr_li_image_create(data,width,height,depth,pt);
      break;
#endif 
    
    default:
      break;
    }

    return img;
}


/**
 * @name: Li_Destroy_Image
 * @msg: 用户接口函数，用来删除一张图片
 * @param
          Li_Image * img
 * @return 0 (right) or -1(something wrong)
 */
LI_API
void Li_Destroy_Image(Li_Image * img)
{
  ptr_li_image_destroy(img);
}

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
Li_Image* Li_Create_Image(
LONG width,LONG height,
BYTE depth,PICTYPE pth)
{
  LiArr * data=li_malloc_arr(width*height*(depth+1));
  memset(data,0xFF,width*height*(depth+1));
  return ptr_li_image_create(data,width,height,depth,pth);
}


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
Li_Image* Li_Copy_Image(Li_Image *img)
{
  Li_Image * out=NULL;
  out=Li_Create_Image(img->width,img->height,img->imgdepth,img->pt);
  memcpy((void*)out->data,(void*)img->data,img->width*img->height*(img->imgdepth+1));
  return out;
}

