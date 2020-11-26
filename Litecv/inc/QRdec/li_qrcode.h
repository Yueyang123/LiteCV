/*
 * @Descripttion: 
 * @version: 
 * @Author: Yueyang
 * @email: 1700695611@qq.com
 * @Date: 2020-11-26 11:45:31
 * @LastEditors: Yueyang
 * @LastEditTime: 2020-11-26 13:36:06
 */
#ifndef LI_QR_H
#define LI_QR_H


/**
 * @name: Li_QREncode
 * @msg: 二维码生成
 * @param {char* src字符串}
 * @return {Li_Image*}
 */
Li_Image* Li_QREncode(BYTE* src);


/**
 * @name: Li_QRCode
 * @msg: 图像解码
 * @param {Li_Image* img}
 * @return {BYTE*}
 */
BYTE* Li_QRCode(Li_Image* img);
#endif 