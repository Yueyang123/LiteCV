/*
 * @Descripttion: 基于嵌入式LINUX的diplay程序
 * @version: V1.0
 * @Author: Yueyang
 * @email: 1700695611@qq.com
 * @Date: 2020-11-24 18:54:21
 * @LastEditors: Yueyang
 * @LastEditTime: 2020-11-24 19:27:48
 * @Use: ./display /dev/fb0  PATH(.jpg,.bmp,.png)
 */


#include "string.h"
#include "fb.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "cv.h"
#include "li_image.h"
#ifdef __cplusplus
}
#endif
int main(int argc,char** argv)
{
    Li_Image* out;
    if(argc!=3)return 0;
    Painter* p=new Painter(argv[1]);
    
    if(strstr(argv[2],"bmp")!=NULL)
    out=Li_Load_Image((BYTE*)argv[2],BMP_888);
    else if(strstr(argv[2],"png")!=NULL)
    out=Li_Load_Image((BYTE*)argv[2],PNG);
    else if(strstr(argv[2],"jpg")!=NULL)
    out=Li_Load_Image((BYTE*)argv[2],JPEG);
    else
    out=Li_Load_Image((BYTE*)argv[2],BMP_888);

    Li_Image* ffb=Li_ReShape(out,p->width,p->height);

    for(int i=0;i<ffb->height;i++)
        for(int j=0;j<ffb->width;j++)
        {
            BYTE* ptr=(BYTE*) ffb->at(ffb,j,i);
            p->Point(j,p->height- i,LI_RGB(*(ptr+2),*(ptr+1),*(ptr)));
        }

    Li_Save_Image((BYTE*)"2.bmp",ffb);
    return 0;
}