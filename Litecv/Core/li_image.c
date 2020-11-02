/*
 * @Descripttion: 图像类基本的初始化函数
 * @version: V 2.0
 * @Author: Yueyang
 * @email: 1700695611@qq.com
 * @Date: 2020-10-27 22:41:59
 * @LastEditors: Yueyang
 * @LastEditTime: 2020-11-02 17:39:12
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

LiArr* li_bgr_at(Li_Image* mat,LONG x,LONG y)
{
  if(x<mat->width&&y<mat->height&&x>=0&&y>=0)
  return mat->data+mat->width*(1+mat->imgdepth)*y+(1+mat->imgdepth)*x;
  else {
  LILOG("BEYOND THE MAT");
  return NULL;
  }
}

LiArr* li_gray_at(Li_Image* mat,LONG x,LONG y)
{
  if(x<mat->width&&y<mat->height&&x>=0&&y>=0)
  return mat->data+mat->width*1*y+1*x;
  else {
  LILOG("BEYOND THE MAT");
  return NULL;
  }
}

LiArr* li_rgba_at(Li_Image* mat,LONG x,LONG y)
{
  if(x<mat->width&&y<mat->height&&x>=0&&y>=0)
  return mat->data+mat->width*4*y+4*x;
  else {
  LILOG("BEYOND THE MAT");
  return NULL;
  }
}

/**
 * @name: ptr_li_mat_create
 * @msg: 
 * @param       LONG width,LONG height, 高和宽
                BYTE depth,             图像深度
 * @return {Li_Mat}
 */
Li_Mat* ptr_li_mat_create(
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
    limt= ptr_li_mat_create(dt,width,height,depth);
    memcpy(&img->limat,limt,sizeof(Li_Mat));//数据指针一并过来了，所以li_mat->arr不能释放
    img->at=li_bgr_at;
    break;
  
   case LI_JPEG:
    limt= ptr_li_mat_create(dt,width,height,depth);
    memcpy(&img->limat,limt,sizeof(Li_Mat));//数据指针一并过来了，所以li_mat->arr不能释放
    img->at=li_bgr_at;
    break;

   case LI_BMP_8:
    limt= ptr_li_mat_create(dt,width,height,depth);
    memcpy(&img->limat,limt,sizeof(Li_Mat));//数据指针一并过来了，所以li_mat->arr不能释放
    img->at=li_bgr_at;
    break;  

   case LI_BMP_32:
    limt= ptr_li_mat_create(dt,width,height,depth);
    memcpy(&img->limat,limt,sizeof(Li_Mat));//数据指针一并过来了，所以li_mat->arr不能释放
    img->at=li_rgba_at;
    break; 

   case LI_PNG:
    limt= ptr_li_mat_create(dt,width,height,depth);
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
  row_stride = (image_width * 3 + 3) & ~3;
  int i=0,j=0;
  for(i=0;i<image_height;i++)
    for(j=0;j<image_width;j++)
    {
      BYTE temp=image_buffer[3*image_width*i+3*j];
      image_buffer[3*image_width*i+3*j]=image_buffer[3*image_width*i+3*j+2];
      image_buffer[3*image_width*i+3*j+2]=temp;
    }
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
  row_stride = (cinfo.output_width * 3 + 3) & ~3;
  imgData=(BYTE*)malloc(cinfo.output_height*cinfo.output_width*3);
  buffer =malloc(row_stride*1);
  while (cinfo.output_scanline < cinfo.output_height) {
     jpeg_read_scanlines(&cinfo, (JSAMPARRAY)&buffer,1);
      char *p = (char*)buffer;
      for (int x = 0; x <cinfo.output_width; x++)
      {
          *(imgData+(cinfo.output_height-cinfo.output_scanline)*row_stride+3*x+2) = *p++;
          *(imgData+(cinfo.output_height-cinfo.output_scanline)*row_stride+3*x+1) = *p++;
          *(imgData+(cinfo.output_height-cinfo.output_scanline)*row_stride+3*x+0) = *p++; 
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
Li_Image* Li_Create_Imgae(
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
Li_Image* Li_Copy_Imgae(Li_Image *img)
{
  Li_Image * out=NULL;
  out=Li_Create_Imgae(img->width,img->height,img->imgdepth,img->pt);
  memcpy((void*)out->data,(void*)img->data,img->width*img->height*(img->imgdepth+1));
  return out;
}


/**
 *  Y = 0.299 * R + 0.587 * G + 0.114 * B;
    Y=D+E+F;
    D=0.299*R;
    E=0.587*G;
    F=0.114*B;
*/
static short int YMap[3][256]={
{0,0,0,0,1,1,1,2,2,2,2,3,3,3,4,4,4,5,5,5,5,6,6,6,7,7,7,8,8,8,8,9,9,9,10,10,10,11,11,11,11,12,12,12,13,13,13,14,14,14,14,15,15,15,16,16,16,17,17,17,17,18,18,18,19,19,19,20,20,20,20,21,21,21,22,22,22,23,23,23,23,24,24,24,25,25,25,25,26,26,26,27,27,27,28,28,28,28,29,29,29,30,30,30,31,31,31,31,32,32,32,33,33,33,34,34,34,34,35,35,35,36,36,36,37,37,37,37,38,38,38,39,39,39,40,40,40,40,41,41,41,42,42,42,43,43,43,43,44,44,44,45,45,45,46,46,46,46,47,47,47,48,48,48,49,49,49,49,50,50,50,51,51,51,51,52,52,52,53,53,53,54,54,54,54,55,55,55,56,56,56,57,57,57,57,58,58,58,59,59,59,60,60,60,60,61,61,61,62,62,62,63,63,63,63,64,64,64,65,65,65,66,66,66,66,67,67,67,68,68,68,69,69,69,69,70,70,70,71,71,71,72,72,72,72,73,73,73,74,74,74,75,75,75,75,76},
{0,0,1,1,2,2,3,4,4,5,5,6,7,7,8,8,9,9,10,11,11,12,12,13,14,14,15,15,16,17,17,18,18,19,19,20,21,21,22,22,23,24,24,25,25,26,26,27,28,28,29,29,30,31,31,32,32,33,34,34,35,35,36,36,37,38,38,39,39,40,41,41,42,42,43,44,44,45,45,46,46,47,48,48,49,49,50,51,51,52,52,53,53,54,55,55,56,56,57,58,58,59,59,60,61,61,62,62,63,63,64,65,65,66,66,67,68,68,69,69,70,71,71,72,72,73,73,74,75,75,76,76,77,78,78,79,79,80,80,81,82,82,83,83,84,85,85,86,86,87,88,88,89,89,90,90,91,92,92,93,93,94,95,95,96,96,97,98,98,99,99,100,100,101,102,102,103,103,104,105,105,106,106,107,107,108,109,109,110,110,111,112,112,113,113,114,115,115,116,116,117,117,118,119,119,120,120,121,122,122,123,123,124,125,125,126,126,127,127,128,129,129,130,130,131,132,132,133,133,134,134,135,136,136,137,137,138,139,139,140,140,141,142,142,143,143,144,144,145,146,146,147,147,148,149,149},
{0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,5,5,5,5,5,5,5,5,5,6,6,6,6,6,6,6,6,6,7,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,8,9,9,9,9,9,9,9,9,9,10,10,10,10,10,10,10,10,10,11,11,11,11,11,11,11,11,11,12,12,12,12,12,12,12,12,12,13,13,13,13,13,13,13,13,14,14,14,14,14,14,14,14,14,15,15,15,15,15,15,15,15,15,16,16,16,16,16,16,16,16,16,17,17,17,17,17,17,17,17,18,18,18,18,18,18,18,18,18,19,19,19,19,19,19,19,19,19,20,20,20,20,20,20,20,20,20,21,21,21,21,21,21,21,21,22,22,22,22,22,22,22,22,22,23,23,23,23,23,23,23,23,23,24,24,24,24,24,24,24,24,24,25,25,25,25,25,25,25,25,25,26,26,26,26,26,26,26,26,27,27,27,27,27,27,27,27,27,28,28,28,28,28,28,28,28,28,29}
};

/**
 *  U = - 0.1687 R - 0.3313 G + 0.5 B + 128
    Y=D+E+F;
    D=- 0.1687 R;
    E=- 0.3313 G;
    F=  0.5 B;
*/
static short int UMap[3][256]={
{0,-1,-1,-1,-1,-1,-2,-2,-2,-2,-2,-2,-3,-3,-3,-3,-3,-3,-4,-4,-4,-4,-4,-4,-5,-5,-5,-5,-5,-5,-6,-6,-6,-6,-6,-6,-7,-7,-7,-7,-7,-7,-8,-8,-8,-8,-8,-8,-9,-9,-9,-9,-9,-9,-10,-10,-10,-10,-10,-10,-11,-11,-11,-11,-11,-11,-12,-12,-12,-12,-12,-12,-13,-13,-13,-13,-13,-13,-14,-14,-14,-14,-14,-15,-15,-15,-15,-15,-15,-16,-16,-16,-16,-16,-16,-17,-17,-17,-17,-17,-17,-18,-18,-18,-18,-18,-18,-19,-19,-19,-19,-19,-19,-20,-20,-20,-20,-20,-20,-21,-21,-21,-21,-21,-21,-22,-22,-22,-22,-22,-22,-23,-23,-23,-23,-23,-23,-24,-24,-24,-24,-24,-24,-25,-25,-25,-25,-25,-25,-26,-26,-26,-26,-26,-26,-27,-27,-27,-27,-27,-27,-28,-28,-28,-28,-28,-29,-29,-29,-29,-29,-29,-30,-30,-30,-30,-30,-30,-31,-31,-31,-31,-31,-31,-32,-32,-32,-32,-32,-32,-33,-33,-33,-33,-33,-33,-34,-34,-34,-34,-34,-34,-35,-35,-35,-35,-35,-35,-36,-36,-36,-36,-36,-36,-37,-37,-37,-37,-37,-37,-38,-38,-38,-38,-38,-38,-39,-39,-39,-39,-39,-39,-40,-40,-40,-40,-40,-40,-41,-41,-41,-41,-41,-41,-42,-42,-42,-42,-42,-43,-43,-43,-43,-43,-43,-44},
{0,-1,-1,-1,-2,-2,-2,-3,-3,-3,-4,-4,-4,-5,-5,-5,-6,-6,-6,-7,-7,-7,-8,-8,-8,-9,-9,-9,-10,-10,-10,-11,-11,-11,-12,-12,-12,-13,-13,-13,-14,-14,-14,-15,-15,-15,-16,-16,-16,-17,-17,-17,-18,-18,-18,-19,-19,-19,-20,-20,-20,-21,-21,-21,-22,-22,-22,-23,-23,-23,-24,-24,-24,-25,-25,-25,-26,-26,-26,-27,-27,-27,-28,-28,-28,-29,-29,-29,-30,-30,-30,-31,-31,-31,-32,-32,-32,-33,-33,-33,-34,-34,-34,-35,-35,-35,-36,-36,-36,-37,-37,-37,-38,-38,-38,-39,-39,-39,-40,-40,-40,-41,-41,-41,-42,-42,-42,-43,-43,-43,-44,-44,-44,-45,-45,-45,-46,-46,-46,-47,-47,-47,-48,-48,-48,-49,-49,-49,-50,-50,-50,-51,-51,-51,-52,-52,-52,-53,-53,-53,-54,-54,-54,-55,-55,-55,-55,-56,-56,-56,-57,-57,-57,-58,-58,-58,-59,-59,-59,-60,-60,-60,-61,-61,-61,-62,-62,-62,-63,-63,-63,-64,-64,-64,-65,-65,-65,-66,-66,-66,-67,-67,-67,-68,-68,-68,-69,-69,-69,-70,-70,-70,-71,-71,-71,-72,-72,-72,-73,-73,-73,-74,-74,-74,-75,-75,-75,-76,-76,-76,-77,-77,-77,-78,-78,-78,-79,-79,-79,-80,-80,-80,-81,-81,-81,-82,-82,-82,-83,-83,-83,-84,-84,-84,-85,-85},
{0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12,13,13,14,14,15,15,16,16,17,17,18,18,19,19,20,20,21,21,22,22,23,23,24,24,25,25,26,26,27,27,28,28,29,29,30,30,31,31,32,32,33,33,34,34,35,35,36,36,37,37,38,38,39,39,40,40,41,41,42,42,43,43,44,44,45,45,46,46,47,47,48,48,49,49,50,50,51,51,52,52,53,53,54,54,55,55,56,56,57,57,58,58,59,59,60,60,61,61,62,62,63,63,64,64,65,65,66,66,67,67,68,68,69,69,70,70,71,71,72,72,73,73,74,74,75,75,76,76,77,77,78,78,79,79,80,80,81,81,82,82,83,83,84,84,85,85,86,86,87,87,88,88,89,89,90,90,91,91,92,92,93,93,94,94,95,95,96,96,97,97,98,98,99,99,100,100,101,101,102,102,103,103,104,104,105,105,106,106,107,107,108,108,109,109,110,110,111,111,112,112,113,113,114,114,115,115,116,116,117,117,118,118,119,119,120,120,121,121,122,122,123,123,124,124,125,125,126,126,127,127}
};
/**
 *  V = 0.5 R - 0.4187 G - 0.0813 B + 128
    Y=D+E+F;
    D=  0.5 R;
    E=- 0.4187 G ;
    F=- 0.0813 B;
*/
static short int VMap[3][256]={
{0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12,13,13,14,14,15,15,16,16,17,17,18,18,19,19,20,20,21,21,22,22,23,23,24,24,25,25,26,26,27,27,28,28,29,29,30,30,31,31,32,32,33,33,34,34,35,35,36,36,37,37,38,38,39,39,40,40,41,41,42,42,43,43,44,44,45,45,46,46,47,47,48,48,49,49,50,50,51,51,52,52,53,53,54,54,55,55,56,56,57,57,58,58,59,59,60,60,61,61,62,62,63,63,64,64,65,65,66,66,67,67,68,68,69,69,70,70,71,71,72,72,73,73,74,74,75,75,76,76,77,77,78,78,79,79,80,80,81,81,82,82,83,83,84,84,85,85,86,86,87,87,88,88,89,89,90,90,91,91,92,92,93,93,94,94,95,95,96,96,97,97,98,98,99,99,100,100,101,101,102,102,103,103,104,104,105,105,106,106,107,107,108,108,109,109,110,110,111,111,112,112,113,113,114,114,115,115,116,116,117,117,118,118,119,119,120,120,121,121,122,122,123,123,124,124,125,125,126,126,127,127},
{0,-1,-1,-2,-2,-3,-3,-3,-4,-4,-5,-5,-6,-6,-6,-7,-7,-8,-8,-8,-9,-9,-10,-10,-11,-11,-11,-12,-12,-13,-13,-13,-14,-14,-15,-15,-16,-16,-16,-17,-17,-18,-18,-19,-19,-19,-20,-20,-21,-21,-21,-22,-22,-23,-23,-24,-24,-24,-25,-25,-26,-26,-26,-27,-27,-28,-28,-29,-29,-29,-30,-30,-31,-31,-31,-32,-32,-33,-33,-34,-34,-34,-35,-35,-36,-36,-37,-37,-37,-38,-38,-39,-39,-39,-40,-40,-41,-41,-42,-42,-42,-43,-43,-44,-44,-44,-45,-45,-46,-46,-47,-47,-47,-48,-48,-49,-49,-49,-50,-50,-51,-51,-52,-52,-52,-53,-53,-54,-54,-55,-55,-55,-56,-56,-57,-57,-57,-58,-58,-59,-59,-60,-60,-60,-61,-61,-62,-62,-62,-63,-63,-64,-64,-65,-65,-65,-66,-66,-67,-67,-67,-68,-68,-69,-69,-70,-70,-70,-71,-71,-72,-72,-73,-73,-73,-74,-74,-75,-75,-75,-76,-76,-77,-77,-78,-78,-78,-79,-79,-80,-80,-80,-81,-81,-82,-82,-83,-83,-83,-84,-84,-85,-85,-85,-86,-86,-87,-87,-88,-88,-88,-89,-89,-90,-90,-91,-91,-91,-92,-92,-93,-93,-93,-94,-94,-95,-95,-96,-96,-96,-97,-97,-98,-98,-98,-99,-99,-100,-100,-101,-101,-101,-102,-102,-103,-103,-104,-104,-104,-105,-105,-106,-106,-106,-107,-107},
{0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-6,-6,-6,-6,-6,-6,-6,-6,-6,-6,-6,-6,-7,-7,-7,-7,-7,-7,-7,-7,-7,-7,-7,-7,-7,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-12,-12,-12,-12,-12,-12,-12,-12,-12,-12,-12,-12,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-16,-16,-16,-16,-16,-16,-16,-16,-16,-16,-16,-16,-17,-17,-17,-17,-17,-17,-17,-17,-17,-17,-17,-17,-17,-18,-18,-18,-18,-18,-18,-18,-18,-18,-18,-18,-18,-19,-19,-19,-19,-19,-19,-19,-19,-19,-19,-19,-19,-20,-20,-20,-20,-20,-20,-20,-20,-20,-20,-20,-20,-20,-21,-21,-21,-21,-21,-21,-21,-21,-21}
};
//     b = 1.164*y+2.018*u-277;
//     g = 1.164*y-0.380*u-0.813*v+134;
//     r = 1.164*y+1.159*v-148;
static short int BUMap[3][256]={
{0,1,2,3,4,5,6,8,9,10,11,12,13,15,16,17,18,19,20,22,23,24,25,26,27,29,30,31,32,33,34,36,37,38,39,40,41,43,44,45,46,47,48,50,51,52,53,54,55,57,58,59,60,61,62,64,65,66,67,68,69,71,72,73,74,75,76,77,79,80,81,82,83,84,86,87,88,89,90,91,93,94,95,96,97,98,100,101,102,103,104,105,107,108,109,110,111,112,114,115,116,117,118,119,121,122,123,124,125,126,128,129,130,131,132,133,135,136,137,138,139,140,142,143,144,145,146,147,149,150,151,152,153,154,155,157,158,159,160,161,162,164,165,166,167,168,169,171,172,173,174,175,176,178,179,180,181,182,183,185,186,187,188,189,190,192,193,194,195,196,197,199,200,201,202,203,204,206,207,208,209,210,211,213,214,215,216,217,218,220,221,222,223,224,225,226,228,229,230,231,232,233,235,236,237,238,239,240,242,243,244,245,246,247,249,250,251,252,253,254,256,257,258,259,260,261,263,264,265,266,267,268,270,271,272,273,274,275,277,278,279,280,281,282,284,285,286,287,288,289,291,292,293,294,295,296},
{0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,80,82,84,86,88,90,92,94,96,98,100,102,104,106,108,110,113,115,117,119,121,123,125,127,129,131,133,135,137,139,141,143,145,147,149,151,153,155,157,159,161,163,165,167,169,171,173,175,177,179,181,183,185,187,189,191,193,195,197,199,201,203,205,207,209,211,213,215,217,219,221,224,226,228,230,232,234,236,238,240,242,244,246,248,250,252,254,256,258,260,262,264,266,268,270,272,274,276,278,280,282,284,286,288,290,292,294,296,298,300,302,304,306,308,310,312,314,316,318,320,322,324,326,328,330,332,334,337,339,341,343,345,347,349,351,353,355,357,359,361,363,365,367,369,371,373,375,377,379,381,383,385,387,389,391,393,395,397,399,401,403,405,407,409,411,413,415,417,419,421,423,425,427,429,431,433,435,437,439,441,443,445,448,450,452,454,456,458,460,462,464,466,468,470,472,474,476,478,480,482,484,486,488,490,492,494,496,498,500,502,504,506,508,510,512,514}
};
static short int GUMap[3][256]={
{0,1,2,3,4,5,6,8,9,10,11,12,13,15,16,17,18,19,20,22,23,24,25,26,27,29,30,31,32,33,34,36,37,38,39,40,41,43,44,45,46,47,48,50,51,52,53,54,55,57,58,59,60,61,62,64,65,66,67,68,69,71,72,73,74,75,76,77,79,80,81,82,83,84,86,87,88,89,90,91,93,94,95,96,97,98,100,101,102,103,104,105,107,108,109,110,111,112,114,115,116,117,118,119,121,122,123,124,125,126,128,129,130,131,132,133,135,136,137,138,139,140,142,143,144,145,146,147,149,150,151,152,153,154,155,157,158,159,160,161,162,164,165,166,167,168,169,171,172,173,174,175,176,178,179,180,181,182,183,185,186,187,188,189,190,192,193,194,195,196,197,199,200,201,202,203,204,206,207,208,209,210,211,213,214,215,216,217,218,220,221,222,223,224,225,226,228,229,230,231,232,233,235,236,237,238,239,240,242,243,244,245,246,247,249,250,251,252,253,254,256,257,258,259,260,261,263,264,265,266,267,268,270,271,272,273,274,275,277,278,279,280,281,282,284,285,286,287,288,289,291,292,293,294,295,296},
{0,0,0,1,1,1,2,2,3,3,3,4,4,4,5,5,6,6,6,7,7,7,8,8,9,9,9,10,10,11,11,11,12,12,12,13,13,14,14,14,15,15,15,16,16,17,17,17,18,18,18,19,19,20,20,20,21,21,22,22,22,23,23,23,24,24,25,25,25,26,26,26,27,27,28,28,28,29,29,30,30,30,31,31,31,32,32,33,33,33,34,34,34,35,35,36,36,36,37,37,37,38,38,39,39,39,40,40,41,41,41,42,42,42,43,43,44,44,44,45,45,45,46,46,47,47,47,48,48,49,49,49,50,50,50,51,51,52,52,52,53,53,53,54,54,55,55,55,56,56,56,57,57,58,58,58,59,59,60,60,60,61,61,61,62,62,63,63,63,64,64,64,65,65,66,66,66,67,67,67,68,68,69,69,69,70,70,71,71,71,72,72,72,73,73,74,74,74,75,75,75,76,76,77,77,77,78,78,79,79,79,80,80,80,81,81,82,82,82,83,83,83,84,84,85,85,85,86,86,86,87,87,88,88,88,89,89,90,90,90,91,91,91,92,92,93,93,93,94,94,94,95,95,96,96,96},
{0,0,1,2,3,4,4,5,6,7,8,8,9,10,11,12,13,13,14,15,16,17,17,18,19,20,21,21,22,23,24,25,26,26,27,28,29,30,30,31,32,33,34,34,35,36,37,38,39,39,40,41,42,43,43,44,45,46,47,47,48,49,50,51,52,52,53,54,55,56,56,57,58,59,60,60,61,62,63,64,65,65,66,67,68,69,69,70,71,72,73,73,74,75,76,77,78,78,79,80,81,82,82,83,84,85,86,86,87,88,89,90,91,91,92,93,94,95,95,96,97,98,99,99,100,101,102,103,104,104,105,106,107,108,108,109,110,111,112,113,113,114,115,116,117,117,118,119,120,121,121,122,123,124,125,126,126,127,128,129,130,130,131,132,133,134,134,135,136,137,138,139,139,140,141,142,143,143,144,145,146,147,147,148,149,150,151,152,152,153,154,155,156,156,157,158,159,160,160,161,162,163,164,165,165,166,167,168,169,169,170,171,172,173,173,174,175,176,177,178,178,179,180,181,182,182,183,184,185,186,186,187,188,189,190,191,191,192,193,194,195,195,196,197,198,199,199,200,201,202,203,204,204,205,206,207}
};
static short int RUMap[3][256]={
{0,1,2,3,4,5,6,8,9,10,11,12,13,15,16,17,18,19,20,22,23,24,25,26,27,29,30,31,32,33,34,36,37,38,39,40,41,43,44,45,46,47,48,50,51,52,53,54,55,57,58,59,60,61,62,64,65,66,67,68,69,71,72,73,74,75,76,77,79,80,81,82,83,84,86,87,88,89,90,91,93,94,95,96,97,98,100,101,102,103,104,105,107,108,109,110,111,112,114,115,116,117,118,119,121,122,123,124,125,126,128,129,130,131,132,133,135,136,137,138,139,140,142,143,144,145,146,147,149,150,151,152,153,154,155,157,158,159,160,161,162,164,165,166,167,168,169,171,172,173,174,175,176,178,179,180,181,182,183,185,186,187,188,189,190,192,193,194,195,196,197,199,200,201,202,203,204,206,207,208,209,210,211,213,214,215,216,217,218,220,221,222,223,224,225,226,228,229,230,231,232,233,235,236,237,238,239,240,242,243,244,245,246,247,249,250,251,252,253,254,256,257,258,259,260,261,263,264,265,266,267,268,270,271,272,273,274,275,277,278,279,280,281,282,284,285,286,287,288,289,291,292,293,294,295,296},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,1,2,3,4,5,6,8,9,10,11,12,13,15,16,17,18,19,20,22,23,24,25,26,27,28,30,31,32,33,34,35,37,38,39,40,41,42,44,45,46,47,48,49,50,52,53,54,55,56,57,59,60,61,62,63,64,66,67,68,69,70,71,73,74,75,76,77,78,79,81,82,83,84,85,86,88,89,90,91,92,93,95,96,97,98,99,100,101,103,104,105,106,107,108,110,111,112,113,114,115,117,118,119,120,121,122,124,125,126,127,128,129,130,132,133,134,135,136,137,139,140,141,142,143,144,146,147,148,149,150,151,152,154,155,156,157,158,159,161,162,163,164,165,166,168,169,170,171,172,173,174,176,177,178,179,180,181,183,184,185,186,187,188,190,191,192,193,194,195,197,198,199,200,201,202,203,205,206,207,208,209,210,212,213,214,215,216,217,219,220,221,222,223,224,225,227,228,229,230,231,232,234,235,236,237,238,239,241,242,243,244,245,246,248,249,250,251,252,253,254,256,257,258,259,260,261,263,264,265,266,267,268,270,271,272,273,274,275,276,278,279,280,281,282,283,285,286,287,288,289,290,292,293,294,295}
};

void bgr_yuyv(BYTE b, BYTE g, BYTE r, BYTE *y, BYTE *u, BYTE *v)
{
  BYTE temp;
  temp=r;
  r=b;
  b=temp;
	*y = YMap[0][r]+YMap[1][g]+YMap[2][b];
	*u = UMap[0][r]+UMap[1][g]+UMap[2][b]+128;
	*v = VMap[0][r]+VMap[1][g]+VMap[2][b]+128;

  // *y = 0.299 * r + 0.587 * g + 0.114 * b;
	// *u = -0.1687 * r -  0.3313 * g + 0.5 * b + 128;
	// *v = 0.5 * r - 0.4187 * g -0.0813 * b + 128;
}
 
void Li_Arr_bgr_yuyv(LiArr *pRgb, LiArr *pYuv, int width, int height)
{
	//考虑到每两个rgb像素对应一个yuyv组合，因此，width应为2的倍数
	int width1 = width = width / 2 * 2;
 
	for(int h = 0; h < height; h ++)
	{
		BYTE *ptr1 = pRgb + h * width * 3;
		BYTE *ptr2 = pYuv + h * width * 2;
 
		for(int w = 0; w < width1; w += 2)
		{
			BYTE y1, u1, v1, y2, u2, v2;
			bgr_yuyv(*ptr1 ++, *ptr1 ++, *ptr1 ++, &y1, &u1, &v1);
			bgr_yuyv(*ptr1 ++, *ptr1 ++, *ptr1 ++, &y2, &u2, &v2);
			//u、v分量取平均值
			BYTE u = (u1 + u2) / 2;
			BYTE v = (v1 + v2) / 2;
			*ptr2 ++ = y1;
			*ptr2 ++ = u;
			*ptr2 ++ = y2;
			*ptr2 ++ = v;
		}
	}
}
/**
    B= 1.164*(Y-16) + 2.018*(U-128);
    G= 1.164*(Y-16) - 0.380*(U-128) - 0.813*(V-128);
    R= 1.164*(Y-16) + 1.159*(V-128);
*/
int yuv_rgb(int y, int u, int v)
{
    unsigned int pixel32 = 0;
    unsigned char *pixel = (unsigned char *)&pixel32;
    int r, g, b;
    // b = 1.164*y+2.018*u-277;
    // g = 1.164*y-0.380*u-0.813*v+134;
    // r = 1.164*y+1.159*v-148;
    b = BUMap[0][y]+BUMap[1][u]-277;
    g = GUMap[0][y]-GUMap[1][u]-GUMap[2][v]+134;
    r = RUMap[0][y]+RUMap[2][v]-148;
    if(r > 255) r = 255;
    if(g > 255) g = 255;
    if(b > 255) b = 255;
    if(r < 0) r = 0;
    if(g < 0) g = 0;
    if(b < 0) b = 0;
    pixel[2] = r ;
    pixel[1] = g ;
    pixel[0] = b ;
    return pixel32;
}
 

int Li_Arr_yuyv_bgr(LiArr *yuv, LiArr* rgb, LONG width, LONG height)
{
  unsigned int in, out = 0;
  unsigned int pixel_16;
  unsigned char pixel_24[3];
  unsigned int pixel32;
  int y0, u, y1, v;
  for(in = 0; in < width * height * 2; in += 4) {
    pixel_16 =
    ((BYTE*)yuv)[in + 3] << 24 |
    ((BYTE*)yuv)[in + 2] << 16 |
    ((BYTE*)yuv)[in + 1] <<  8 |
    ((BYTE*)yuv)[in + 0];
    y0 = (pixel_16 & 0x000000ff);
    u  = (pixel_16 & 0x0000ff00) >>  8;
    y1 = (pixel_16 & 0x00ff0000) >> 16;
    v  = (pixel_16 & 0xff000000) >> 24;
    pixel32 = yuv_rgb(y0, u, v);
    pixel_24[0] = (pixel32 & 0x000000ff);
    pixel_24[1] = (pixel32 & 0x0000ff00) >> 8;
    pixel_24[2] = (pixel32 & 0x00ff0000) >> 16;
    ((BYTE*)rgb)[out++] = pixel_24[0];
    ((BYTE*)rgb)[out++] = pixel_24[1];
    ((BYTE*)rgb)[out++] = pixel_24[2];
    pixel32 = yuv_rgb(y1, u, v);
    pixel_24[0] = (pixel32 & 0x000000ff);
    pixel_24[1] = (pixel32 & 0x0000ff00) >> 8;
    pixel_24[2] = (pixel32 & 0x00ff0000) >> 16;
    ((BYTE*)rgb)[out++] = pixel_24[0];
    ((BYTE*)rgb)[out++] = pixel_24[1];
    ((BYTE*)rgb)[out++] = pixel_24[2];
 }
 return 0;
}



/** RGB转灰度转换关系表
 *  Grey = (R*1 + G*2 + B*1) >> 2
    Grey= (R*2 + G*5 + B*1) >> 3
    Grey= (R*4 + G*10 + B*2) >> 4
    Grey = (R*9 + G*19 + B*4) >> 5
    Grey = (R*19 + G*37 + B*8) >> 6
    Grey= (R*38 + G*75 + B*15) >> 7
    Grey= (R*76 + G*150 + B*30) >> 8
    Grey = (R*153 + G*300 + B*59) >> 9
    Grey = (R*306 + G*601 + B*117) >> 10
    Grey = (R*612 + G*1202 + B*234) >> 11
    Grey = (R*1224 + G*2405 + B*467) >> 12
    Grey= (R*2449 + G*4809 + B*934) >> 13
    Grey= (R*4898 + G*9618 + B*1868) >> 14
    Grey = (R*9797 + G*19235 + B*3736) >> 15
    Grey = (R*19595 + G*38469 + B*7472) >> 16
    Grey = (R*39190 + G*76939 + B*14943) >> 17
    Grey = (R*78381 + G*153878 + B*29885) >> 18
    Grey =(R*156762 + G*307757 + B*59769) >> 19
    Grey= (R*313524 + G*615514 + B*119538) >> 20
 *
 */
//默认采用四位精度表示
//Grey= (R*4 + G*10 + B*2) >> 4
//Grey = (R*1224 + G*2405 + B*467) >> 12
//site 精确度
void Li_Arr_bgr_gray( LiArr* src,LiArr *dst,LONG width,LONG height,BYTE site)
{
  int x,y;
  switch (site)
  {

  case 0: //查表法实现灰度转换 12位
    for(x=0;x<height;x++)
      for(y=0;y<width;y++)
      {
        *((BYTE*)dst+width*x+y)=(YMap[2][*((BYTE*)src+3*width*x+3*y)]) //B
                                    +YMap[1][(*((BYTE*)src+3*width*x+3*y+1))] //G
                                      +YMap[0][(*((BYTE*)src+3*width*x+3*y+2))]; //R
      }
  break;

  case 4:
    for(x=0;x<height;x++)
      for(y=0;y<width;y++)
      {
        *((BYTE*)dst+width*x+y)=(*((BYTE*)src+3*width*x+3*y)*2) //B
                                    +(*((BYTE*)src+3*width*x+3*y+1)*10) //G
                                      +(*((BYTE*)src+3*width*x+3*y+2)*4)>>4; //R
      }
    break;

    case 8:
    for(x=0;x<height;x++)
      for(y=0;y<width;y++)
      {
        *((BYTE*)dst+width*x+y)=(*((BYTE*)src+3*width*x+3*y)*30) //B
                                    +(*((BYTE*)src+3*width*x+3*y+150)*10) //G
                                      +(*((BYTE*)src+3*width*x+3*y+2)*76)>>8; //R
      }
    break;

   case 16:
    for(x=0;x<height;x++)
      for(y=0;y<width;y++)
      {
        *((BYTE*)dst+width*x+y)=(*((BYTE*)src+3*width*x+3*y)*7472) //B
                                    +(*((BYTE*)src+3*width*x+3*y+150)*38469) //G
                                      +(*((BYTE*)src+3*width*x+3*y+2)*19595)>>16; //R
      }
    break;
  
  default:
    break;
  }

}

void Li_Arr_gray_bgr( LiArr* src,LiArr *dst,LONG width,LONG height)
{
    int x=0,y=0;
     for(x=0;x<height;x++)
      for(y=0;y<width;y++)
      {
        *((BYTE*)dst+3*width*x+3*y)=*((BYTE*)src+width*x+y);
        *((BYTE*)dst+3*width*x+3*y+1)=*((BYTE*)src+width*x+y);
        *((BYTE*)dst+3*width*x+3*y+2)=*((BYTE*)src+width*x+y);
      }
}

void Li_Arr_bgr_rgb(LiArr* src,LiArr *dst, LONG width, LONG height)
{
   int i=0,j=0;
   for(i=0;i<height;i++)
    for(j=0;j<width;j++)
    {
      BYTE temp=*((BYTE*)src+3*width*i+3*j);
      *((BYTE*)dst+3*width*i+3*j)=*((BYTE*)src+3*width*i+3*j+2);
      *((BYTE*)dst+3*width*i+3*j+2)=temp;
    }
}

void Li_Arr_bgr_bgra(LiArr* src,LiArr *dst, LONG width, LONG height)
{
    	int row_bytes;
    	int i,j;
    	uint8_t* ptr;
    	int src_pad;
    	uint32_t off;
     
    	row_bytes = (width * 3 + 3) & ~3; 
    	off = 0*row_bytes;
    	for(i = 0; i < height;i++)
    	{   
        ptr = src + off;
    		for(j = 0; j < width; j++)
    		{
    			*(BYTE*)dst++ = *ptr++;
    			*(BYTE*)dst++ = *ptr++;
    			*(BYTE*)dst++ = *ptr++;
    			*(BYTE*)dst++ = 0;
    		}
            off += row_bytes;
    	}
}

void Li_Arr_bgra_bgr(LiArr* src,LiArr *dst, int width, int height)
{
    	uint32_t src_row_bytes;
    	uint32_t dst_row_bytes;
    	uint32_t off;
    	int i,j;
    	uint32_t* ptr;
    	uint8_t* img;
    	uint32_t color;
    	int pad;
    	
    	src_row_bytes = width << 2;
    	dst_row_bytes = (width * 3 + 3) & ~3;
    	pad = dst_row_bytes - width * 3;
     
    	off = 0 * dst_row_bytes;
    	ptr = (uint32_t*)src;
    	
    	for(i = 0; i < height; i++)
    	{  
    		img = dst + off;
    		for (j = 0; j < width; j++)
    		{   
    			color = *ptr++;
    			*img++ =  color & 0x000000FF;
    			*img++ =  (color >> 8) & 0x000000FF;
    			*img++ =  (color >> 16) & 0x000000FF;
    		}
    		off += dst_row_bytes;
    	}
}


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
void Li_CvtColor( LiArr* src,LiArr *dst,LONG width,LONG height,BYTE cvtype)
{
  switch (cvtype)
  {
  case LI_BGR2GRAY:
    Li_Arr_bgr_gray(src,dst,width,height,0);
    break;
  
  case LI_GRAY2BGR:
    Li_Arr_gray_bgr(src,dst,width,height);
    break;

  case LI_BGR2BGRA:
    Li_Arr_bgr_bgra(src,dst,width,height);
    break;

  case LI_BGRA2BGR:
    Li_Arr_bgra_bgr(src,dst,width,height);
    break;
  
  case LI_BGR2RGB:
    Li_Arr_bgr_rgb(src,dst,width,height);
    break;
  
  case LI_RGB2BGR:
    Li_Arr_bgr_rgb(src,dst,width,height);
    break;
  
  case LI_RGB2RGBA:
    Li_Arr_bgr_rgb(src,src,width,height);
    Li_Arr_bgr_bgra(src,dst,width,height);
    break;

  case LI_BGR2YUYV:
    Li_Arr_bgr_yuyv(src,dst,width,height);
    break;
  
  case LI_YUYV2BGR:
    Li_Arr_yuyv_bgr(src,dst,width,height);
    break;


  default:
    break;
  }

}



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
Li_Image* Li_Convert_Image( Li_Image* src,BYTE convertype)
{
  Li_Image* dst;
  switch (convertype)
  {
  
  case LI_JPEG_2_BMP:

  if(src->pt==LI_JPEG){
   dst=Li_Copy_Imgae(src);
   dst->pt=LI_BMP_888;
  }else{
      LILOG("TYPE ERROR");
      break;
  }
  break;

  case LI_BMP_2_JPEG:

  if(src->pt==LI_BMP_888){
   dst=Li_Copy_Imgae(src);
   dst->pt=LI_JPEG;
  }else{
      LILOG("TYPE ERROR");
      break;
  }
  break;

  case LI_PNG_2_BMP:
  if(src->pt==LI_PNG){
   dst=Li_Copy_Imgae(src);
   dst->pt=LI_BMP_32;
  }else{
      LILOG("TYPE ERROR");
      break;
  }
  break;

  case LI_BMP_2_PNG:
  if(src->pt==LI_BMP_32){
   dst=Li_Copy_Imgae(src);
   dst->pt=LI_PNG;
  }else{
      LILOG("TYPE ERROR");
      break;
  }
  break;


  case LI_BMP_888_2_LI_BMP32:
    if(src->pt==LI_BMP_888){
    dst=Li_Create_Imgae(src->width,src->height,LI_DEP_32U,LI_BMP_32);
    Li_CvtColor(src->data,dst->data,src->width,src->height,LI_BGR2BGRA);
    }else {
      LILOG("TYPE ERROR");
      break;
    }  
   break;

  case LI_BMP_32_2_LI_BMP888:
    if(src->pt==LI_BMP_32){
    dst=Li_Create_Imgae(src->width,src->height,LI_DEP_24U,LI_BMP_888);
    Li_CvtColor(src->data,dst->data,src->width,src->height,LI_BGRA2BGR);
    }else {
      LILOG("TYPE ERROR");
      break;
    }
    break;

  case LI_BMP_888_2_LI_BMP_8:
    if(src->pt==LI_BMP_888){
    dst=Li_Create_Imgae(src->width,src->height,LI_DEP_8U,LI_BMP_8);
    Li_CvtColor(src->data,dst->data,src->width,src->height,LI_BGR2GRAY);
    }else {
      LILOG("TYPE ERROR");
      break;
    }
    break;

  case LI_BMP_8_2_LI_BMP_888:
    if(src->pt==LI_BMP_8){
    dst=Li_Create_Imgae(src->width,src->height,LI_DEP_24U,LI_BMP_888);
    Li_CvtColor(src->data,dst->data,src->width,src->height,LI_GRAY2BGR);
    }else {
      LILOG("TYPE ERROR");
      break;
    }
    break;


  
  default:
    break;
  }
  return dst;
}

