#include "cv.h"
#include "li_image.h"
#include "string.h"

int main()
{

    Li_Image* out=Li_Load_Image((BYTE*)"lena.jpg",JPEG);
    
    Li_Image* img1 =Li_Convert_Image(out,LI_JPEG_2_BMP);
    Li_Save_Image((BYTE*)"3.bmp",img1);
    Li_Destroy_Image(out);

    return 0;
}