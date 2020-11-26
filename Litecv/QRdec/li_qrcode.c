/*
 * @Descripttion: 二维码编码
 * @version: V 1.0
 * @Author: Yueyang
 * @email: 1700695611@qq.com
 * @Date: 2020-11-26 11:43:15
 * @LastEditors: Yueyang
 * @LastEditTime: 2020-11-26 15:02:47
 */
#include <string.h>
#include "qrencode.h"  
#include "cv.h"
#include "li_image.h"
#include "li_qrcode.h"
#include "quirc.h"
#include "quirc_internal.h"
/**
 * @name: Li_QREncode
 * @msg: 二维码生成
 * @param {BYTE* src字符串}
 * @return {Li_Image*}
 */
Li_Image* Li_QREncode(BYTE* src)
{
    QRcode*  pQRC;
    int unWidth, unWidthAdjusted, unDataBytes;
    Li_Image* out;
    BYTE* pSourceData,*pDestData,*pRGBData ;
    if (pQRC = QRcode_encodeString(src, 0, QR_ECLEVEL_H, QR_MODE_8, 1))
    {
        unWidth=pQRC->width;
                unWidthAdjusted = unWidth * 8 * 3;
        if (unWidthAdjusted % 4)
            unWidthAdjusted = (unWidthAdjusted / 4 + 1) * 4;
        unDataBytes = unWidthAdjusted * unWidth * 8;
        out=Li_Create_Image(8*unWidth,8*unWidth,LI_DEP_24U,LI_BMP_888);
        pSourceData = pQRC->data;
        pRGBData=out->data;
        pSourceData = pQRC->data;
        for (int y = 0; y < unWidth; y++)
        {
            pDestData = pRGBData + unWidthAdjusted * y * 8;
            for (int x = 0; x < unWidth; x++)
            {
                if (*pSourceData & 1)
                {
                    for (int l = 0; l < 8; l++)
                    {
                        for (int n = 0; n < 8; n++)
 
                        {
                             //以下三行是设置三基色，三基色都设置为0x00，则生成的二维码图片就是黑色的了，要什么颜色自己调整
                            *(pDestData + n * 3 + unWidthAdjusted * l) = 0x00;            
                            *(pDestData + 1 + n * 3 + unWidthAdjusted * l) = 0x00;
                            *(pDestData + 2 + n * 3 + unWidthAdjusted * l) = 0x00;
                        }
                    }
                }
                pDestData += 3 * 8;
                pSourceData++;
            }
        }
    }
    return out;
}

/**
 * @name: Li_QRCode
 * @msg: 图像解码
 * @param {Li_Image* img}
 * @return {BYTE*}
 * @TODO 现在还用不了
 */
BYTE* Li_QRCode(Li_Image* img)
{
    struct quirc *qr;
    Li_Image* out,*out1;
	uint8_t *image;
    if(img->imgdepth==LI_DEP_8U)
    out=Li_Copy_Image(img);
    if(img->imgdepth==LI_DEP_24U)
    out=Li_Convert_Image(img,LI_BGR2GRAY);
    else if(img->imgdepth==LI_DEP_32U){
        out1=Li_Convert_Image(img,LI_BGRA2BGR);
        out=Li_Convert_Image(out1,LI_BGR2GRAY);
        Li_Destroy_Image(out1);
    }else return NULL;

	qr = quirc_new();
	if (!qr) {
		LILOG("Failed to allocate memory");
		return NULL;
	}   	
	if (quirc_resize(qr, out->width, out->height) < 0) {
		LILOG("Failed to allocate video memory");
		return NULL;
	}
    int w=out->width;
    int h=out->height;
    image = quirc_begin(qr, NULL, NULL);
    for(int y=0;y<h;y++)
        for(int x=0;x<w;x++)
        {
            BYTE* ptr=out->at(out,x,y);
            *(image+y*w+x)=*ptr;
        }
    quirc_end(qr);
	int num_codes;
	int i;
	num_codes = quirc_count(qr);
	for (i = 0; i < num_codes; i++) {
		struct quirc_code code;
		struct quirc_data data;
		quirc_decode_error_t err;
		quirc_extract(qr, i, &code);
		/* Decoding stage */
        err = quirc_decode(&code, &data);
        if (err) {
            LILOG("DECODE FAILED ");
        }
        printf("Data: %s\n", data.payload);
	}
    return NULL;
}