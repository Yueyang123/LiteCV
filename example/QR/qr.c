/*
 * @Descripttion: 
 * @version: 
 * @Author: Yueyang
 * @email: 1700695611@qq.com
 * @Date: 2020-11-26 12:23:49
 * @LastEditors: Yueyang
 * @LastEditTime: 2020-11-26 15:04:58
 */
#include "cv.h"
#include "li_image.h"
#include "li_qrcode.h"

int main()
{
    Li_Image* Qr=Li_QREncode("123.57.93.3");
    Li_Save_Image("QR.bmp",Qr);
    
    LILOG("OVER");
}