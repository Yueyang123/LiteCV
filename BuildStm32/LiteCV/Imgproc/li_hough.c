/*
 * @Descripttion: 
 * @version: 
 * @Author: Yueyang
 * @email: 1700695611@qq.com
 * @Date: 2020-11-11 08:22:08
 * @LastEditors: Yueyang
 * @LastEditTime: 2020-11-11 23:27:31
 */
#ifndef HOUGH_C
#define HOUGH_C
#include "cv.h"
#include "li_image_proc.h"
#include "li_image.h"
#include "string.h"
#include "math.h"
#include "li_painter.h"

/**
 * @name: Li_Hough_Line
 * @msg: 霍夫直线变换
 * @param {Li_Image* img 原图像
 * 		   LiLine* lines 返回的直线类型指针
 * 		   LONG maxthrea 允许的最大角度
 * 		   LONG maxr     语序的最大半径}
 * @return {*}
 */
LI_API 
void Li_Hough_Line(Li_Image* img,LiLine* lines, LONG maxthrea,LONG maxr)
{
	//x*cos(theta)+y*sin(theta)=r;
	if(img==NULL||img->imgdepth!=LI_DEP_8U) return;
    int k,maxValue;
	int *pAccumulateArr=NULL;		//累加数组
	int thetaMax=maxthrea;
	int theta;
	int rValue;
	float fRate = (float)(PI/180);
    LONG RMax=(LONG)maxr;
	int AccuArrLength=(thetaMax+1)*(RMax+1);
    int pointNum=0;
 	pAccumulateArr=(int*)malloc(AccuArrLength*sizeof(int));
	memset(pAccumulateArr,0,AccuArrLength*sizeof(int));
    LiPoint *point=(LiPoint*)malloc(img->width*img->height*sizeof(LiPoint));
	//去除边缘点，防止干扰
    for(int i=2;i<img->height-2;i++)
        for(int j=2;j<img->width-2;j++)
        {
            BYTE* ptr=img->at(img,j,i);
            if(*ptr!=0)
            {
                point[pointNum].x=j;
                point[pointNum].y=i;
                pointNum++;
            }
        }
    /*对每个点算一遍每一个角度所对应的R值*/
    for (k=0;k<pointNum;k++)
	{
        int x=point[k].x;
        int y=point[k].y;
		for (theta=0;theta<=thetaMax;theta++)
		{

			rValue=(float)(x) * cos(theta * fRate) + (float)y * sin(theta * fRate)+0.5;
            
			if (rValue>0&&rValue<=RMax&&theta<=thetaMax)
			{
				int indexTemp=rValue*(thetaMax+1)+theta;
				if (indexTemp>=0)
				{
					pAccumulateArr[indexTemp]++;
				}
			}
		}
	}

	//得到最佳参数
	maxValue=0;
	int lineR=0;
	int lineTheta=0;
	for (int r=0;r<=RMax;r++)
	{
		for (theta=0;theta<=thetaMax;theta++)
		{
			int iCount = pAccumulateArr[r * (thetaMax+1) + theta];
			if (maxValue<iCount)
			{	
				maxValue=iCount;
				lineR=r;
				lineTheta=theta;
			}
		}
	}
   lines->thera=lineTheta;
   lines->r=lineR;
}

/**
 * @name: Li_Hough_Circle_R
 * @msg:  固定半径的Hough变换
 * @param {Li_Image* img  		原图像
 * 		   LiCircle* circles    返回的圆指针（不会再内部分配内存）
 * 		   LONG R				变换半径
 * 		   LONG* range}			圆心得范围
 * @return {*}
 */
LI_API 
LONG Li_Hough_Circle_R(Li_Image* img,LiCircle* circles, LONG R,LONG* range)
{
	if(img==NULL||img->imgdepth!=LI_DEP_8U) return 0;
    int k,max_value=0;
	int *pAccumulateArr=NULL;		//累加数组
	float fRate = (float)(PI/180);
	int AccuArrLength=img->width * img->height;;
 	pAccumulateArr=(int*)malloc(AccuArrLength*sizeof(int));
	memset(pAccumulateArr,0,AccuArrLength*sizeof(int));

	for(int i = 0; i < img->height; i++)
	{
		for(int j = 0; j < img->width; j++)
		{
			BYTE *ptr=img->at(img,j,i);
			if(*ptr == 255)
				for(int a = 0; a < 360; a++)
				{
					double theta = a * PI / 180;//转成弧度制
					int x = i - R * cos(theta);//得到理想圆心x坐标
					int y = j - R * sin(theta);//得到理想圆心y坐标
					if(x>0&&x<img->width&&y>0&&y<img->height&&x<range[1]&&x>range[0]&&y<range[3]&&y>range[2])
					{
						pAccumulateArr[y * img->width + x]++;
					}
				}
		}
	}
	for(int i = 0; i < img->height; i++)
		for(int j = 0; j < img->width; j++)
		{
			int value_ = pAccumulateArr[i * img->width + j];
			if(value_>max_value)
			{
				//printf("(%d,%d,%d,%d)",max_value,value_,i,j);
				max_value=value_;
				circles->x=j;
				circles->y=i;
				circles->r=R;
			}
		}		
	return max_value;
}


/**
 * @name: Li_Hough_Circle
 * @msg:  给定范围的Hough变换
 * @param {Li_Image* img  		原图像
 * 		   LiCircle* circles    返回的圆指针（不会再内部分配内存）
 * 		   LONG Rmin,LONG Rmax  最小最大半径
 * 		   LONG* range}			圆心得范围
 * @return {*}
 */
LI_API 
void Li_Hough_Circle(Li_Image* img,LiCircle* circles, LONG Rmin,LONG Rmax,LONG* range)
{
	int maxvalue=0,value=0;
	LiCircle c;
	for(int i=Rmin;i<Rmax;i++)
	{
	  value= Li_Hough_Circle_R( img, &c, i,range);
	  if(value>maxvalue)
	  {
		  circles->r=c.r;
		  circles->x=c.x;
		  circles->y=c.y;
	  }
	}
}


#endif // !HOUGH_Cs