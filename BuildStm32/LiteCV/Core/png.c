/*
 * @Descripttion: 向licvcore 提供png读写接口
 * @version: V 2.0
 * @Author: Yueyang
 * @email: 1700695611@qq.com
 * @Date: 2020-11-10 22:18:19
 * @LastEditors: Yueyang
 * @LastEditTime: 2020-11-10 22:41:48
 */

#ifndef LI_PNG_C
#define LI_PNG_C


#ifdef USE_PNG

#include "png.h"
#include "cv.h"
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


#endif // !LI_PAINTER_C
