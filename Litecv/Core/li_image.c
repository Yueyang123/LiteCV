/*
 * @Descripttion: 图像类基本的初始化函数
 * @version: V 2.0
 * @Author: Yueyang
 * @email: 1700695611@qq.com
 * @Date: 2020-10-27 22:41:59
 * @LastEditors: Yueyang
 * @LastEditTime: 2020-11-01 03:49:47
 */
#include "cv.h"
#include "bmp.h"
#include "stdlib.h"
#include "string.h"

#ifdef USE_JPEG
#include "jconfig.h"
#include "jmorecfg.h"
#include <jpeglib.h>
#include <setjmp.h>
#endif

#ifdef USE_PNG
#include "png.h"
#endif

#undef  LOG
#define LOG  "LI_CV_CORE"


/**
 * @name: li_malloc_arr
 * @msg: 为LiArr申请内存
 * @param {size}申请内存的大小
 * @return {LiArr}数组类型
 */
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
    return free((void *)arr);
}

/**
 * @name: ptr_li_mat_free
 * @msg: 为LiMat释放内存
 * @param {void}
 * @return {void}
 */
void ptr_li_mat_free(Li_Mat* mat)
{
  li_free_arr(mat->arr);
  free((void*)mat);
}

/**
 * @name: ptr_li_mat_create
 * @msg: 
 * @param       LONG width,LONG height, 高和宽
                BYTE depth,             图像深度
                void* (*ath)(void* data,LONG x,LONG y),             搜索点的函数指针
                void* (*atath)(void* data,LONG x,LONG y,LONG index) 搜索通道的函数指针
 * @return {Li_Mat}
 */
Li_Mat* ptr_li_mat_create(
LiArr* data,
LONG width,LONG height,
BYTE depth,
void* (*ath)(void* data,LONG x,LONG y),
void* (*atath)(void* data,LONG x,LONG y,LONG index))
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
    Li_Mat* limt= ptr_li_mat_create(dt,width,height,depth, NULL,NULL);
    memcpy(&img->limat,limt,sizeof(Li_Mat));//数据指针一并过来了，所以li_mat->arr不能释放
    img->pt=pth;
    img->data=dt;
    img->width=width;
    img->height=height;
    img->imgdepth=img->limat.datadepth;
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
   bi.biXPelsPerMeter=3780;//默认大小
   bi.biYPelsPerMeter=3780;
   bi.biSizeImage=DataSizePerLine*bi.biHeight;
   bi.biCompression=0;//默认不压缩
   return bi;
}

#ifdef USE_JPEG

/**
 * @name: 
 * @msg: 将RGB数据编码并写JPG图片
 * @param
 *        char *filepath        图片路径
 *        JSAMPLE *image_buffer RGB数据指针
 *        int quality           图片质量
 *        int image_width      图片高度
 *        int image_height       图片宽度
 * @return 0 (right) or -1(something wrong)
 */
BYTE Write_Jpeg(BYTE *filepath,JSAMPLE *image_buffer, LONG quality,LONG image_width,LONG image_height)
{
  struct jpeg_compress_struct cinfo;
  struct jpeg_error_mgr jerr;
  FILE *outfile;          
  JSAMPROW row_pointer[1];
  int row_stride;

  cinfo.err = jpeg_std_error(&jerr);
  /* Now we can initialize the JPEG compression object. */
  jpeg_create_compress(&cinfo);

  if ((outfile = fopen(filepath, "wb")) == NULL) {
    LILOG("can't open");
    return -1;
  }
  jpeg_stdio_dest(&cinfo, outfile);
  cinfo.image_width = image_width;    
  cinfo.image_height = image_height;
  cinfo.input_components = 3;
  cinfo.in_color_space = JCS_RGB;
  jpeg_set_defaults(&cinfo);
  jpeg_set_quality(&cinfo, quality, TRUE);
  jpeg_start_compress(&cinfo, TRUE);
  row_stride = image_width * 3;
  int i=0,j=0;
  while (cinfo.next_scanline < cinfo.image_height) {
    row_pointer[0] = &image_buffer[(cinfo.image_height-cinfo.next_scanline) * row_stride];
    (void)jpeg_write_scanlines(&cinfo, row_pointer, 1);
  }
  jpeg_finish_compress(&cinfo);
  fclose(outfile);
  jpeg_destroy_compress(&cinfo);
}

struct my_error_mgr {
  struct jpeg_error_mgr pub; 

  jmp_buf setjmp_buffer; 
};

typedef struct my_error_mgr *my_error_ptr;

METHODDEF(void)
my_error_exit(j_common_ptr cinfo)
{
  my_error_ptr myerr = (my_error_ptr)cinfo->err;
  (*cinfo->err->output_message) (cinfo);
  longjmp(myerr->setjmp_buffer, 1);
}


/**
 * @name: Read_Jpeg
 * @msg: 读取一个JPG图片
 * @param char* filepath 图片路径
 *        LONG* wdith    返回图片的宽度
 *        LONG* height   返回图片的高度
 * @return 数据指针
 */
BYTE* Read_Jpeg(char* filepath,LONG* width,LONG* height)
{
  BYTE *imgData;
  struct jpeg_decompress_struct cinfo;
  struct my_error_mgr jerr;
  FILE *infile;
  JSAMPARRAY buffer;
  int row_stride; 
  if ((infile = fopen(filepath, "rb")) == NULL) {
    LILOG("can't open");
  }
  cinfo.err = jpeg_std_error(&jerr.pub);
  jerr.pub.error_exit = my_error_exit;
  if (setjmp(jerr.setjmp_buffer)) {
    LILOG("ERROR");
    jpeg_destroy_decompress(&cinfo);
    fclose(infile);
  }
  jpeg_create_decompress(&cinfo);
  jpeg_stdio_src(&cinfo, infile);
  jpeg_read_header(&cinfo, TRUE);
  jpeg_start_decompress(&cinfo);
  row_stride = cinfo.output_width * 3;
  imgData=(BYTE*)malloc(cinfo.output_height*cinfo.output_width*3);
  buffer =malloc(row_stride*1);
  while (cinfo.output_scanline < cinfo.output_height) {
     jpeg_read_scanlines(&cinfo, (JSAMPARRAY)&buffer,1);
      char *p = (char*)buffer;
      for (int x = 0; x <cinfo.output_width; x++)
      {
          *(imgData+(cinfo.output_height-cinfo.output_scanline)*row_stride+3*x+0) = *p++;
          *(imgData+(cinfo.output_height-cinfo.output_scanline)*row_stride+3*x+1) = *p++;
          *(imgData+(cinfo.output_height-cinfo.output_scanline)*row_stride+3*x+2) = *p++; 
      }
      
  }
  *width=cinfo.output_width;
  *height=cinfo.output_height;
  free(buffer);
  (void)jpeg_finish_decompress(&cinfo);
  jpeg_destroy_decompress(&cinfo);
  fclose(infile);
  return imgData;
}

#endif //USE_JPEG

#ifdef USE_PNG

#define PNG_BYTES_TO_CHECK	8
#define HAVE_ALPHA			1
#define NOT_HAVE_ALPHA		0
 
typedef struct _pic_data pic_data;
struct _pic_data {
	int width, height; 	//长宽
	int bit_depth; 	   	//位深度
	int alpha_flag;		//是否有透明通道
	unsigned char *rgba;//实际rgb数据
};
 
BYTE check_is_png(FILE **fp, const char *filename) //检查是否png文件
{
	char checkheader[PNG_BYTES_TO_CHECK]; //查询是否png头
	*fp = fopen(filename, "rb");
	if (*fp == NULL) {
		LILOG("open failed ...1\n");
		return -1;
	}
	if (fread(checkheader, 1, PNG_BYTES_TO_CHECK, *fp) != PNG_BYTES_TO_CHECK) //读取png文件长度错误直接退出
		return 0;
	return png_sig_cmp(checkheader, 0, PNG_BYTES_TO_CHECK); //0正确, 非0错误
}

/**
 * @name: Read_Png
 * @msg: 读取一个png图片
 * @param char* filepath  图片路径
 *        LONG* wdith     返回图片的宽度
 *        LONG* height    返回图片的高度
 *        BYTE* withalpha 是否带有alpha通道
 * @return 数据指针 注：一定返回一个24位的数据指针
 */
BYTE* Read_Png(BYTE *filename,LONG* width,LONG* height) //取出png文件中的rgb数据
{
  pic_data *out =(pic_data*)malloc(sizeof(pic_data));
	png_structp png_ptr; //png文件句柄
	png_infop	info_ptr;//png图像信息句柄
	int ret;
	FILE *fp;
	if (check_is_png(&fp, filename) != 0) {
		LILOG("file is not png ...\n");
		return NULL;
	}
	png_ptr  = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL); 
	info_ptr = png_create_info_struct(png_ptr);
	setjmp(png_jmpbuf(png_ptr));
	rewind(fp);
	png_init_io(png_ptr, fp);
	png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_EXPAND, 0); //读取文件信息
	int channels, color_type; 
	channels 	= png_get_channels(png_ptr, info_ptr); //通道数量
	color_type 	= png_get_color_type(png_ptr, info_ptr);//颜色类型
	out->bit_depth = png_get_bit_depth(png_ptr, info_ptr);//位深度	
	out->width 	 = png_get_image_width(png_ptr, info_ptr);//宽
	out->height  = png_get_image_height(png_ptr, info_ptr);//高
	*width=out->width;
  *height=out->height;
	if(color_type == PNG_COLOR_TYPE_PALETTE)
		png_set_palette_to_rgb(png_ptr);//要求转换索引颜色到RGB
	if(color_type == PNG_COLOR_TYPE_GRAY && out->bit_depth < 8)
		png_set_expand_gray_1_2_4_to_8(png_ptr);//要求位深度强制8bit
	if(out->bit_depth == 16)
		png_set_strip_16(png_ptr);//要求位深度强制8bit
	if(png_get_valid(png_ptr,info_ptr,PNG_INFO_tRNS))
		png_set_tRNS_to_alpha(png_ptr);
	if(color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
		png_set_gray_to_rgb(png_ptr);//灰度必须转换成RG
 
	int i, j, k;
	int size, pos = 0;
	int temp;

	png_bytepp row_pointers; //实际存储rgb数据的buf
	row_pointers = png_get_rows(png_ptr, info_ptr); //也可以分别每一行获取png_get_rowbytes();
	size = out->width * out->height; //申请内存先计算空间
	if (channels == 4 || color_type == PNG_COLOR_TYPE_RGB_ALPHA) { //判断是24位还是32位
		out->alpha_flag = HAVE_ALPHA; //记录是否有透明通道
		size *= (sizeof(unsigned char) * 4); //size = out->width * out->height * channel
		out->rgba = (png_bytep)malloc(size);
		if (NULL == out->rgba) {
			LILOG("malloc rgba faile ...\n");
			png_destroy_read_struct(&png_ptr, &info_ptr, 0);
			fclose(fp);
			return NULL;
		}
		//从row_pointers里读出实际的rgb数据
		for (i = out->height-1; i >0; i --) {
			for (j = 0; j < 4 * out->width; j += 4) {
				out->rgba[pos++] = row_pointers[i][j+2];
				out->rgba[pos++] = row_pointers[i][j+1];
				out->rgba[pos++] = row_pointers[i][j+0];
        out->rgba[pos++] = row_pointers[i][j+3];
			}
		}
	} 
  else if (channels == 3 || color_type == PNG_COLOR_TYPE_RGB) { //判断颜色深度是24位还是32位
    out->alpha_flag = NOT_HAVE_ALPHA;
		size *= (sizeof(unsigned char) * 4);
		out->rgba = (png_bytep)malloc(size);
		if (NULL == out->rgba) {
			LILOG("malloc rgba faile ...\n");
			png_destroy_read_struct(&png_ptr, &info_ptr, 0);
			fclose(fp);
			return NULL;
		}
		//从row_pointers里读出实际的rgb数据
		temp = (3 * out->width);
		for (i = 0; i < out->height; i ++) {
			for (j = 0; j < temp; j += 3) {
				out->rgba[pos++] = row_pointers[i][j+2];
				out->rgba[pos++] = row_pointers[i][j+1];
				out->rgba[pos++] = row_pointers[i][j+0];
        pos++;
			}
		}
	} else return NULL; 
	//6:销毁内存
	png_destroy_read_struct(&png_ptr, &info_ptr, 0);
	fclose(fp);
	//此时， 我们的out->rgba里面已经存储有实际的rgb数据了
	//处理完成以后free(out->rgba)
	return out->rgba;
}
 

/**
 * @name: Write_Png
 * @msg:  写一个png图片
 * @param BYTE*  png_file_name 文件名称
 *        BYTE*  pixels        数据指针
 *        int    width         图像宽度
 *        int    height        图像高度
 *        int    withalpha     是否带有alpha通道
 * @return 0成功 -1失败
 */
BYTE Write_Png(BYTE* png_file_name, BYTE*  pixels , LONG width, LONG height)
{
  pic_data *out=malloc(sizeof(pic_data));
  out->bit_depth=8;
  out->rgba=pixels;
  out->alpha_flag=HAVE_ALPHA;
  out->height=height;
  out->width=width;

	png_structp png_ptr;
	png_infop 	info_ptr;
	png_byte color_type;
	png_bytep * row_pointers;
	FILE *fp = fopen(png_file_name, "wb");
	if (NULL == fp) {
		LILOG("open failed ...2");
		return -1;
	}
	//1: 初始化libpng结构体  
	png_ptr	= png_create_write_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
	if (!png_ptr) {
		LILOG("png_create_write_struct failed ...");
		return -1;
	}
	//2: 初始化png_infop结构体 ， 
	//此结构体包含了图像的各种信息如尺寸，像素位深, 颜色类型等等
	info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr) {
		LILOG("png_create_info_struct failed ...\n");
		return -1;
	}
	//3: 设置错误返回点
	if (setjmp(png_jmpbuf(png_ptr))) {
		LILOG("error during init_io ...\n");
		return -1;
	}
	//4:绑定文件IO到Png结构体
	png_init_io(png_ptr, fp);
	if (setjmp(png_jmpbuf(png_ptr))) {
		LILOG("error during init_io ...\n");
		return -1;
	}
	if (out->alpha_flag == HAVE_ALPHA) color_type = PNG_COLOR_TYPE_RGB_ALPHA;
	else color_type = PNG_COLOR_TYPE_RGB;
	//5：设置以及写入头部信息到Png文件
	png_set_IHDR(png_ptr, info_ptr, out->width, out->height, out->bit_depth,
	color_type, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
	png_write_info(png_ptr, info_ptr);
	if (setjmp(png_jmpbuf(png_ptr))) {
		LILOG("error during init_io ...\n");
		return -1;
	}
	int channels, temp;
	int i, j, pos = 0;
	if (out->alpha_flag == HAVE_ALPHA) {
		channels = 4;
		temp = (4 * out->width);
	} else {
		channels = 3;
		temp = (3 * out->width);
	}
	row_pointers = (png_bytep*)malloc(out->height * sizeof(png_bytep));
	for (i = out->height-1; i >=0; i--) {
		row_pointers[i] = (png_bytep)malloc(temp* sizeof(unsigned char));
		for (j = 0; j < temp; j += channels) {
			if (channels == 4) {
				row_pointers[i][j+2] = out->rgba[pos++];
				row_pointers[i][j+1] = out->rgba[pos++];
				row_pointers[i][j+0] = out->rgba[pos++];
				row_pointers[i][j+3] = out->rgba[pos++];
			} else {
				row_pointers[i][j+2] = out->rgba[pos++];
				row_pointers[i][j+1] = out->rgba[pos++];
				row_pointers[i][j+0] = out->rgba[pos++];
			}
		}
	}
	png_write_image(png_ptr, (png_bytepp)row_pointers);
	if (setjmp(png_jmpbuf(png_ptr))) {
		return -1;
	}
	//7: 写入尾部信息
	png_write_end(png_ptr, NULL);
	//8:释放内存 ,销毁png结构体
	for (i = 0; i < out->height; i ++)
		free(row_pointers[i]);
	free(row_pointers);
	png_destroy_write_struct(&png_ptr, &info_ptr);
	fclose(fp);
	return 0;
}
 
 
#endif //USE_PNG


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

