/*
 * @Descripttion: 
 * @version: 
 * @Author: Yueyang
 * @email: 1700695611@qq.com
 * @Date: 2020-11-28 01:14:29
 * @LastEditors: Yueyang
 * @LastEditTime: 2020-11-28 12:00:53
 */
#include <seeta/FaceDetector.h>
#include <seeta/FaceLandmarker.h>
#include <seeta/FaceRecognizer.h>
#include <seeta/Struct.h>
#include <array>
#include <map>
#include <iostream>

#ifdef __cplusplus
extern "C" {
#endif
#include "cv.h"
#include "li_image.h"
#include "li_painter.h"
#ifdef __cplusplus
}
#endif

int test_image(seeta::FaceDetector &FD, seeta::FaceLandmarker &FL)
{
    for(int i=1;i<=4;i++){
	std::string image_path = std::to_string(i)+".bmp";
	std::cout << "Loading image: " << image_path << std::endl;
	Li_Image* img=Li_Load_Image((BYTE*)image_path.c_str(),BMP_888);
    Li_Image* square=Li_ReShape(img,500,500);
    Li_Image* img2=Li_Rotate_180(square);
    Li_Image* img1=Li_Convert_Image(img2,LI_BMP_888_2_LI_BMP_8);

    SeetaImageData simage;
    simage.width=img1->width;
    simage.height=img1->height;
    simage.data=(unsigned char*)img1->data;
    simage.channels=1;

	auto faces = FD.detect(simage);

    std::cout<<faces.size<<std::endl;
	for (int i = 0; i < faces.size; ++i)
	{
		auto &face = faces.data[i];
		auto points = FL.mark(simage, face.pos);

        Li_Line(img2,0xFF0000,face.pos.x,face.pos.y,face.pos.x,face.pos.y+face.pos.height);
        Li_Line(img2,0xFF0000,face.pos.x,face.pos.y,face.pos.x+face.pos.width,face.pos.y);
        Li_Line(img2,0xFF0000,face.pos.x+face.pos.width,face.pos.y,face.pos.x+face.pos.width,face.pos.y+face.pos.height);
        Li_Line(img2,0xFF0000,face.pos.x,face.pos.y+face.pos.height,face.pos.x+face.pos.width,face.pos.y+face.pos.height);
		for (auto &point : points)
		{
            Li_Circle(img2,0xFF0000,point.x,point.y,1);
		}
	}
    Li_Image*res= Li_Rotate_180(img2);
	auto output_path = image_path + ".pts81.bmp";
	Li_Save_Image((BYTE*)output_path.c_str(),res);
	std::cerr << "Saving result into: " << output_path << std::endl;
    }
	return EXIT_SUCCESS;
}

int main()
{
    seeta::ModelSetting::Device device = seeta::ModelSetting::CPU;
    int id = 0;
    seeta::ModelSetting FD_model( "./model/fd_2_00.dat", device, id );
    seeta::ModelSetting FL_model( "./model/pd_2_00_pts81.dat", device, id );

	seeta::FaceDetector FD(FD_model);
	seeta::FaceLandmarker FL(FL_model);

    
	FD.set(seeta::FaceDetector::PROPERTY_VIDEO_STABLE, 1);

    return test_image(FD, FL);

}
