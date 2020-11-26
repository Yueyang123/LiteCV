/*
 * @Descripttion: 向licvcore 提供jpegJ读写接口
 * @version: V 2.0
 * @Author: Yueyang
 * @email: 1700695611@qq.com
 * @Date: 2020-11-10 22:18:19
 * @LastEditors: Yueyang
 * @LastEditTime: 2020-11-10 22:40:47
 */
#ifndef JPEG_C
#define JPEG_C


#ifdef USE_JPEG

#include "jconfig.h"
#include "jmorecfg.h"
#include <jpeglib.h>
#include <setjmp.h>
#include "cv.h"

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
  row_stride = (cinfo.output_width * 3 );
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


#endif // !JPE_CG