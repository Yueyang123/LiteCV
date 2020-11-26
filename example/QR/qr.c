/*
 * @Descripttion: 
 * @version: 
 * @Author: Yueyang
 * @email: 1700695611@qq.com
 * @Date: 2020-11-26 12:23:49
 * @LastEditors: Yueyang
 * @LastEditTime: 2020-11-27 01:09:57
 */
#include "cv.h"
#include "li_image.h"
#include "li_qrcode.h"

int main()
{
    Li_CV_Version();
    Li_Image* Qr=Li_QREncode("123.57.93.3");
    LILOG("QR: 123.57.93.3");
    Li_Save_Image("QR.bmp",Qr);
    Li_Wait_Q();
    LILOG("OVER");
}