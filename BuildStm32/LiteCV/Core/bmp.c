/*
 * @Descripttion: BMP的底层函数
 * @version: V 2.0
 * @Author: Yueyang
 * @email: 1700695611@qq.com
 * @Date: 2020-11-04 01:22:01
 * @LastEditors: Yueyang
 * @LastEditTime: 2020-11-10 22:40:10
 */
#ifndef BMP_H
#define BMP_H



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string.h"
#include "bmp.h"

int Read_bmp_FileHeader(char *filepath,BITMAPFILEHEADER *bmfh)
{
   FILE *fp;
   fp=fopen(filepath,"rb");
   if(!fp)
   {
      return -1;
   }
   if(fread(&bmfh->bfType,sizeof(WORD),1,fp)!=1)
   {
      fclose(fp);
      return -1;
   }
   if(fread(&bmfh->bfSize,sizeof(DWORD),1,fp)!=1)
   {
      fclose(fp);
      return -1;
   }
   if(fread(&bmfh->bfReserved1,sizeof(WORD),1,fp)!=1)
   {
      fclose(fp);
      return -1;
   }
   if(fread(&bmfh->bfReserved2,sizeof(WORD),1,fp)!=1)
   {
      fclose(fp);
      return -1;
   }
   if(fread(&bmfh->bfOffBits,sizeof(DWORD),1,fp)!=1)
   {
      fclose(fp);
      return -1;
   }
   fclose(fp);
   return 0;
}


int Read_bmp_InfoHeader(char *filepath,BITMAPINFOHEADER *bmih)
{
   FILE *fp;
   fp=fopen(filepath,"rb");
   if(!fp)
   {
      return -1;
   }
   fseek(fp,14,SEEK_SET);
   if(fread(&bmih->biSize,sizeof(DWORD),1,fp)!=1)
   {
      fclose(fp);
      return -1;
   }
   if(fread(&bmih->biWidth,sizeof(LONG),1,fp)!=1)
   {
      fclose(fp);
      return -1;
   }
   if(fread(&bmih->biHeight,sizeof(LONG),1,fp)!=1)
   {
      fclose(fp);
      return -1;
   }
   if(fread(&bmih->biPlanes,sizeof(WORD),1,fp)!=1)
   {
      fclose(fp);
      return -1;
   }
   if(fread(&bmih->biBitCount,sizeof(WORD),1,fp)!=1)
   {
      fclose(fp);
      return -1;
   }
   if(fread(&bmih->biCompression,sizeof(DWORD),1,fp)!=1)
   {
      fclose(fp);
      return -1;
   }
   if(fread(&bmih->biSizeImage,sizeof(DWORD),1,fp)!=1)
   {
      fclose(fp);
      return -1;
   }
   if(fread(&bmih->biXPelsPerMeter,sizeof(LONG),1,fp)!=1)
   {
      fclose(fp);
      return -1;
   }
   if(fread(&bmih->biYPelsPerMeter,sizeof(LONG),1,fp)!=1)
   {
      fclose(fp);
      return -1;
   }
   if(fread(&bmih->biClrUsed,sizeof(DWORD),1,fp)!=1)
   {
      fclose(fp);
      return -1;
   }
   if(fread(&bmih->biClrImportant,sizeof(DWORD),1,fp)!=1)
   {
      fclose(fp);
      return -1;
   }
   fclose(fp);
   return 0;
}


void Print_bmp_FileHeader(BITMAPFILEHEADER *bmfh)
{
   printf("The contents in the file header of the BMP file:\n");
   printf("bfOffBits: %ld\n",(long int)bmfh->bfOffBits);
   printf("bfReserved1: %ld\n",(long int)bmfh->bfReserved1);
   printf("bfReserved2: %ld\n",(long int)bmfh->bfReserved2);
   printf("bfSize: %ld\n",(long int)bmfh->bfSize);
   printf("bfType: %ld\n",(long int)bmfh->bfType);
}

void Print_bmp_InfoHeader(BITMAPINFOHEADER *bmih)
{
   printf("The content in the info header of the BMP file:\n");
   printf("biBitCount: %ld\n",(long int)bmih->biBitCount);
   printf("biClrImportant: %ld\n",(long int)bmih->biClrImportant);
   printf("biClrUsed: %ld\n",(long int)bmih->biClrUsed);
   printf("biCompression: %ld\n",(long int)bmih->biCompression);
   printf("biHeight: %ld\n",(long int)bmih->biHeight);
   printf("biPlanes: %ld\n",(long int)bmih->biPlanes);
   printf("biSize: %ld\n",(long int)bmih->biSize);
   printf("biSizeImage: %ld\n",(long int)bmih->biSizeImage);
   printf("biWidth: %ld\n",(long int)bmih->biWidth);
   printf("biXPelsPerMeter: %ld\n",(long int)bmih->biXPelsPerMeter);
   printf("biYPelsPerMeter: %ld\n",(long int)bmih->biYPelsPerMeter);
}


/**
 * @name: Read_bmp
 * @msg: 读取一个BMP图片
 * @param char *filepath        读取文件的路径
 *        BITMAPFILEHEADER *bmf 与文件有关的信息
 *        BITMAPINFOHEADER *bmi 与图片有关的信息
 * @return 数据指针
 */
BYTE* Read_bmp(BYTE *filepath,BITMAPFILEHEADER *bmf,BITMAPINFOHEADER *bmi)
{
   BYTE *imgData;
   BITMAPINFOHEADER bmih;
   BITMAPFILEHEADER bmfh;
   FILE *fp;
   u8 R, G, B;
   u16 pixel;
   int n,i;
   int width;
   int height;
   int bitCount;
   DWORD dwLineBytes;
   n=Read_bmp_FileHeader(filepath,&bmfh);
   if(n==-1)
   {
      printf("Can not read the file header of the BMP file.\n");
      return NULL;
   }
   n=Read_bmp_InfoHeader(filepath,&bmih);
   if(n==-1)
   {
      printf("Can not read the info header of the BMP file.\n");
      return NULL;
   }

   memcpy(bmi,&bmih,sizeof(BITMAPINFOHEADER));
   memcpy(bmf,&bmfh,sizeof(BITMAPFILEHEADER));
   #ifdef DEBUG
   Print_bmp_FileHeader(bmf);
   Print_bmp_InfoHeader(bmi);
   #endif // DEBUG

   width=bmih.biWidth;
   height=bmih.biHeight;
   bitCount=bmih.biBitCount;
   imgData=(BYTE*)malloc((bitCount/(8*sizeof(BYTE)))*width*height*sizeof(BYTE));
   fp=fopen(filepath,"rb");
   if(!fp)
   {
      printf("Can not open the file: %s\n",filepath);
      return NULL;
   }
   fseek(fp,bmfh.bfOffBits,SEEK_SET);//移动到数据开始的地方

   if(fread(imgData,(bitCount/(8*sizeof(BYTE)))*width*height*sizeof(BYTE),1,fp)!=1)
   {
         
      free(imgData);
      fclose(fp);
      return NULL;
   }

   fclose(fp);
   return imgData;
}


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
LONG Write_bmp(BYTE *filepath,BYTE *imgData,BITMAPFILEHEADER *bmf,BITMAPINFOHEADER *bmi,PICTYPE pt)
{
   FILE *fp;
   int i;
   RGBQuad *IpRGBQuad;
   LONG height=bmi->biHeight;
   DWORD dwLineBytes=(bmi->biBitCount/(8*sizeof(BYTE)))*bmi->biWidth;
   fp=fopen(filepath,"wb");
   if(!fp)
   {
      printf("Error: Can not open the file:%s\n",filepath);
   }
   switch (pt)
   {

   case LI_BMP_1://BW
       dwLineBytes=(bmi->biWidth +8-bmi->biWidth%8)/8;

       if(fwrite(&(bmf->bfType),sizeof(WORD),1,fp)!=1)
      {
         fclose(fp);
         return -1;
      }
      if(fwrite(&(bmf->bfSize),sizeof(DWORD),1,fp)!=1)
      {
         fclose(fp);
         return -1;
      }
      if(fwrite(&(bmf->bfReserved1),sizeof(WORD),1,fp)!=1)
      {
         fclose(fp);
         return -1;
      }
      if(fwrite(&(bmf->bfReserved2),sizeof(WORD),1,fp)!=1)
      {
         fclose(fp);
         return -1;
      }
      if(fwrite(&(bmf->bfOffBits),sizeof(DWORD),1,fp)!=1)
      {
         fclose(fp);
         return -1;
      }
      if(fwrite(bmi,40,1,fp)!=1)
      {
         fclose(fp);
         return -1;
      }
      /*图像的读取顺序是从下到上,从左到右*/
	   IpRGBQuad = (RGBQuad *)malloc(2*sizeof(RGBQuad));
		   IpRGBQuad[0].rgbRed = 0;
			IpRGBQuad[0].rgbGreen = 0;
			IpRGBQuad[0].rgbBlue = 0;
			IpRGBQuad[0].rgbReserved = 0;

   		IpRGBQuad[1].rgbRed = 255;
			IpRGBQuad[1].rgbGreen = 255;
			IpRGBQuad[1].rgbBlue = 255;
			IpRGBQuad[0].rgbReserved = 0;	 
      fwrite(IpRGBQuad,8,1,fp);
      if(fwrite(imgData,dwLineBytes*height,1,fp)!=1)
      {
         fclose(fp);
         return -1;
      }
   break;

   case LI_BMP_8://GRAY
      LILOG("WRITE GRAY");
      if(fwrite(&(bmf->bfType),sizeof(WORD),1,fp)!=1)
      {
         fclose(fp);
         return -1;
      }
      if(fwrite(&(bmf->bfSize),sizeof(DWORD),1,fp)!=1)
      {
         fclose(fp);
         return -1;
      }
      if(fwrite(&(bmf->bfReserved1),sizeof(WORD),1,fp)!=1)
      {
         fclose(fp);
         return -1;
      }
      if(fwrite(&(bmf->bfReserved2),sizeof(WORD),1,fp)!=1)
      {
         fclose(fp);
         return -1;
      }
      if(fwrite(&(bmf->bfOffBits),sizeof(DWORD),1,fp)!=1)
      {
         fclose(fp);
         return -1;
      }
      if(fwrite(bmi,40,1,fp)!=1)
      {
         fclose(fp);
         return -1;
      }
      /*图像的读取顺序是从下到上,从左到右*/

	   IpRGBQuad = (RGBQuad *)malloc(256*sizeof(RGBQuad));//灰度图为8位的调色板数据为256个结构,1024个字节
		for(int i = 0;i < 256;i++){
			IpRGBQuad[i].rgbRed = i;
			IpRGBQuad[i].rgbGreen = i;
			IpRGBQuad[i].rgbBlue = i;
			IpRGBQuad[i].rgbReserved = 0;
		}
      fwrite(IpRGBQuad,1024,1,fp);
      if(fwrite(imgData,height*dwLineBytes,1,fp)!=1)
      {
         fclose(fp);
         return -1;
      }
   break;

   case LI_BMP_565://BMP565
      printf("暂不支持，实在不行自己写\n");
      /* code */
   break;

   case LI_BMP_888://BMP888
      //因为存在字节对齐问题不能一次写入
      if(fwrite(&(bmf->bfType),sizeof(WORD),1,fp)!=1)
      {
         fclose(fp);
         return -1;
      }
      if(fwrite(&(bmf->bfSize),sizeof(DWORD),1,fp)!=1)
      {
         fclose(fp);
         return -1;
      }
      if(fwrite(&(bmf->bfReserved1),sizeof(WORD),1,fp)!=1)
      {
         fclose(fp);
         return -1;
      }
      if(fwrite(&(bmf->bfReserved2),sizeof(WORD),1,fp)!=1)
      {
         fclose(fp);
         return -1;
      }
      if(fwrite(&(bmf->bfOffBits),sizeof(DWORD),1,fp)!=1)
      {
         fclose(fp);
         return -1;
      }
      if(fwrite(bmi,40,1,fp)!=1)
      {
         fclose(fp);
         return -1;
      }
      if(fwrite(imgData,height*dwLineBytes,1,fp)!=1)
      {
         fclose(fp);
         return -1;
      }
   break;  

   case LI_BMP_32://BMP32
      if(fwrite(&(bmf->bfType),sizeof(WORD),1,fp)!=1)
      {
         fclose(fp);
         return -1;
      }
      if(fwrite(&(bmf->bfSize),sizeof(DWORD),1,fp)!=1)
      {
         fclose(fp);
         return -1;
      }
      if(fwrite(&(bmf->bfReserved1),sizeof(WORD),1,fp)!=1)
      {
         fclose(fp);
         return -1;
      }
      if(fwrite(&(bmf->bfReserved2),sizeof(WORD),1,fp)!=1)
      {
         fclose(fp);
         return -1;
      }
      if(fwrite(&(bmf->bfOffBits),sizeof(DWORD),1,fp)!=1)
      {
         fclose(fp);
         return -1;
      }
      if(fwrite(bmi,40,1,fp)!=1)
      {
         fclose(fp);
         return -1;
      }
      if(fwrite(imgData,height*dwLineBytes,1,fp)!=1)
      {
         fclose(fp);
         return -1;
      }
   break;  


   default:
      break;
   }
	return 0;
}

#endif // !BMP_H