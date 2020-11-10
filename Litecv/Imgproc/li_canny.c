#ifndef LI_CANNY_C
#define LI_CANNY_C




#include "cv.h"
#include "li_image_proc.h"
#include <stdio.h>
#include <math.h>


/**
 * @name: Li_Canny
 * @msg:  参考文章 https://blog.csdn.net/HUSTER_Gy/article/details/102942452?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522160498444419724838560446%2522%252C%2522scm%2522%253A%252220140713.130102334.pc%255Fall.%2522%257D&request_id=160498444419724838560446&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~first_rank_v2~rank_v28-11-102942452.first_rank_ecpm_v3_pc_rank_v2&utm_term=canny%E8%BE%B9%E7%BC%98%E6%A3%80%E6%B5%8B%E7%AE%97%E6%B3%95c%E5%AE%9E%E7%8E%B0&spm=1018.2118.3001.4449
 *        图像砍尼检测
 * @param {Li_Image* img 原图像
 *         BYTE CannyType选择算子
 *         BYTE min      最大阈值
 *         BYTE max}     最小阈值
 * @return {*}
 */
LI_API
Li_Image* Li_Canny(Li_Image* img,BYTE CannyType,BYTE min,BYTE max)
{
    if(img==NULL||img->imgdepth!=LI_DEP_8U)return NULL;
    LILOG("CANNY");           
    Li_Image* out =Li_Copy_Image(img); 
    Li_Image* PP =Li_Copy_Image(img); 
    Li_Image* QQ =Li_Copy_Image(img);
    Li_Kernel* SX,*SY;
    double *P =(double*)malloc(sizeof(double)*img->width*img->height);/*x方向偏导*/
    double *Q =(double*)malloc(sizeof(double)*img->width*img->height); /*y方向偏导*/
    /*PI*-1/2* --  PI*1/2*/
    double *Threa =(double*)malloc(sizeof(double)*img->width*img->height);

    #ifdef DEBUG
    Li_Save_Image("before_minus.bmp",out);
    #endif 
    
    /*开始计算梯度与方向角*/
    switch (CannyType)
    {
    case LI_CANNY_MYDEFINE:
        {
            for(int i=0;i<img->height-1;i++)
                for(int j=0;j<img->width-1;j++)
                {
                    BYTE* ptr[4];
                    BYTE* ptr2;
                    /**
                     * 2  3
                     * 0  1
                    */
                    ptr[0]=img->at(img,j,i);
                    ptr[1]=img->at(img,j+1,i);
                    ptr[2]=img->at(img,j,i+1);
                    ptr[3]=img->at(img,j+1,i+1);
                    P[i*img->width+j]=(double)((double)*ptr[3]+*ptr[1]-*ptr[0]-*ptr[2])/2;
                    Q[i*img->width+j]=(double)((double)*ptr[0]+*ptr[1]-*ptr[2]-*ptr[3])/2;  
                    Threa[i*img->width+j]=atan(Q[i*img->width+j]/P[i*img->width+j]);
                    ptr2=out->at(out,j,i);
                    *ptr2=sqrt(P[i*img->width+j]*P[i*img->width+j]+Q[i*img->width+j]*Q[i*img->width+j]);
                }
        }
        break;
    
    case LI_CANNY_SOBEL:
        {
            for(int i=1;i<img->height-1;i++)
                for(int j=1;j<img->width-1;j++)
                {
                    BYTE* ptr[9];
                    BYTE* ptr2;
                    /**6  7  8
                     * 3  4  5
                     * 0  1  2
                     */
                    if(j-1>=0&&i-1>=0)
                    ptr[0]=(BYTE*)img->at(img,j-1,i-1);
                    if(j>=0&&i-1>=0)
                    ptr[1]=(BYTE*)img->at(img,j+0,i-1);
                    if(j+1<=img->width&&i-1>=0)
                    ptr[2]=(BYTE*)img->at(img,j+1,i-1);
                    if(j-1>=0&&i>=0)
                    ptr[3]=(BYTE*)img->at(img,j-1,i+0);
                    if(j>=0&&i>=0)
                    ptr[4]=(BYTE*)img->at(img,j+0,i+0);
                    if(j+1<=img->width&&i>=0)
                    ptr[5]=(BYTE*)img->at(img,j+1,i+0);
                    if(j-1>=0&&i+1<=img->height)
                    ptr[6]=(BYTE*)img->at(img,j-1,i+1);
                    if(j>=0&&i+1<=img->height)
                    ptr[7]=(BYTE*)img->at(img,j+0,i+1);
                    if(j+1<=img->width&&i+1<=img->height)
                    ptr[8]=(BYTE*)img->at(img,j+1,i+1);

                    P[i*img->width+j]=(double)((double)*ptr[2]+*ptr[5]*2+*ptr[8]-*ptr[0]-*ptr[3]*2-*ptr[6]);
                    Q[i*img->width+j]=(double)((double)*ptr[6]+*ptr[7]*2+*ptr[8]-*ptr[0]-*ptr[1]*2-*ptr[2]);    
                    Threa[i*img->width+j]=atan(Q[i*img->width+j]/P[i*img->width+j]);
                    ptr2=out->at(out,j,i);
                    *ptr2=sqrt(P[i*img->width+j]*P[i*img->width+j]+Q[i*img->width+j]*Q[i*img->width+j]);
                }
        }
        break;

        case LI_CANNY_ROBERTS:
         {
            for(int i=0;i<img->height-1;i++)
                for(int j=0;j<img->width-1;j++)
                {
                    BYTE* ptr[4];
                    BYTE* ptr2;
                    /**
                     * 2  3
                     * 0  1
                    */
                    ptr[0]=img->at(img,j,i);
                    ptr[1]=img->at(img,j+1,i);
                    ptr[2]=img->at(img,j,i+1);
                    ptr[3]=img->at(img,j+1,i+1);
                    ptr2=out->at(out,j,i);
                    *ptr2=abs(*ptr[2]-*ptr[1])+abs(*ptr[0]-*ptr[3]);
                    Threa[i*img->width+j]=atan(abs(*ptr[2]-*ptr[1])/abs(*ptr[0]-*ptr[3]));
                }         
         }
        break;

    case LI_CANNY_PREWITT:
          {
            for(int i=1;i<img->height-1;i++)
                for(int j=1;j<img->width-1;j++)
                {
                    BYTE* ptr[9];
                    BYTE* ptr2;
                    /**6  7  8
                     * 3  4  5
                     * 0  1  2
                     */
                    if(j-1>=0&&i-1>=0)
                    ptr[0]=(BYTE*)img->at(img,j-1,i-1);
                    if(j>=0&&i-1>=0)
                    ptr[1]=(BYTE*)img->at(img,j+0,i-1);
                    if(j+1<=img->width&&i-1>=0)
                    ptr[2]=(BYTE*)img->at(img,j+1,i-1);
                    if(j-1>=0&&i>=0)
                    ptr[3]=(BYTE*)img->at(img,j-1,i+0);
                    if(j>=0&&i>=0)
                    ptr[4]=(BYTE*)img->at(img,j+0,i+0);
                    if(j+1<=img->width&&i>=0)
                    ptr[5]=(BYTE*)img->at(img,j+1,i+0);
                    if(j-1>=0&&i+1<=img->height)
                    ptr[6]=(BYTE*)img->at(img,j-1,i+1);
                    if(j>=0&&i+1<=img->height)
                    ptr[7]=(BYTE*)img->at(img,j+0,i+1);
                    if(j+1<=img->width&&i+1<=img->height)
                    ptr[8]=(BYTE*)img->at(img,j+1,i+1);

                    P[i*img->width+j]=(double)((double)*ptr[2]+*ptr[5]+*ptr[8]-*ptr[0]-*ptr[3]-*ptr[6]);
                    Q[i*img->width+j]=(double)((double)*ptr[6]+*ptr[7]+*ptr[8]-*ptr[0]-*ptr[1]-*ptr[2]); 
                    Threa[i*img->width+j]=atan(Q[i*img->width+j]/P[i*img->width+j]);   
                    ptr2=out->at(out,j,i);
                    *ptr2=sqrt(P[i*img->width+j]*P[i*img->width+j]+Q[i*img->width+j]*Q[i*img->width+j]);
                }
        }      

        break;
    
    default:
        break;
    }

    #ifdef DEBUG
    Li_Save_Image("after_minus.bmp",out);
    #endif 

    /*非极大值抑制*/
    for(int j=1;j<out->height-1;j++)
        for(int i=1;i<out->width-1;i++)
        {
            double t=Threa[j*img->width+i];
            BYTE* ptr=out->at(out,i,j);
            double g=(double) *ptr;
            double g0, g1;
            if ((t >= -(3*M_PI/8)) && (t < -(M_PI/8)))
            {
                ptr=out->at(out,i-1,j-1);
                 g0=(double) *ptr;
                ptr=out->at(out,i+1,j+1);
                 g1=(double) *ptr;
            } 
            else if ((t >= -(M_PI/8)) && (t < M_PI/8))
            {
                ptr=out->at(out,i-1,j);
                 g0=(double) *ptr;
                ptr=out->at(out,i+1,j);
                 g1=(double) *ptr;
            }
            else if ((t >= M_PI/8) && (t < 3*M_PI/8))
            {
                ptr=out->at(out,i+1,j-1);
                 g0=(double) *ptr;
                ptr=out->at(out,i-1,j+1);
                 g1=(double) *ptr;
            }
            else
            {
                ptr=out->at(out,i,j-1);
                 g0=(double) *ptr;
                ptr=out->at(out,i,j+1);
                 g1=(double) *ptr;                
            }
        
            if (g <= g0 || g <= g1) {
                ptr=out->at(out,i,j);
                *ptr=0;
            }

        }
 
    /*阈值化操作*/
    #ifdef DEBUG
    Li_Save_Image("before_thre.bmp",out);
    #endif 
    Li_Image*out1=Li_Double_Threshold(out,min,max);
    #ifdef DEBUG
    Li_Save_Image("after_thre.bmp",out1);
    #endif 

    /*边缘链接*/
        for (int j = 1; j < out1->height-2; j++) 
        for (int i = 1; i < out1->width-2; i++) {
            BYTE* ptr=out1->at(out1,i,j);
            if(*ptr==255)
            {
                for (int m = -1; m < 1; m++) {
                    for (int n = -1; n < 1; n++) {
                    BYTE* temp=out1->at(out1,i+n,j+m);
                        if(*ptr!=0&&*ptr!=255)
                        *ptr=255;
                    }
                }             
            }
        }

        for (int j = 0; j < out1->height-1; j++) {
        for (int i = 0; i < out1->width-1; i++) {
            // 如果该点依旧是弱边缘点，及此点是孤立边缘点
             BYTE* ptr=out1->at(out1,i,j);
             if(*ptr!=255&&*ptr!=0)
             *ptr=0;
            }
        }
    Li_Destroy_Image(PP);
    Li_Destroy_Image(QQ);
    return out1;
}

#endif // !LI_CANNY_C
