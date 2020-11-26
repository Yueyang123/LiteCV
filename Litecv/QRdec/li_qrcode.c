/*
 * @Descripttion: 二维码编码
 * @version: V 1.0
 * @Author: Yueyang
 * @email: 1700695611@qq.com
 * @Date: 2020-11-26 11:43:15
 * @LastEditors: Yueyang
 * @LastEditTime: 2020-11-26 18:01:26
 */
#include <string.h>
#include "qrencode.h"  
#include "cv.h"
#include "li_image.h"
#include "li_qrcode.h"

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

