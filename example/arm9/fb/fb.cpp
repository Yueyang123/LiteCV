#include "fb.h"
extern "C"{
#include <sys/ioctl.h>
}

Painter::~Painter()
{
    munmap(pfb, vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8);  /* release the memory */
    close(fbfd);   
}

Painter::Painter(char* str)
{
        int fbfd = 0,screensize=0;
        struct fb_var_screeninfo vinfo;
        struct fb_fix_screeninfo finfo;
        char *fbp = 0;
        int x = 0, y = 0;
        long int location = 0;
        fbfd = open(str, O_RDWR);
        if (!fbfd) {
                printf("Error: cannot open framebuffer device.\n");
                exit(1);
        }
        printf("The framebuffer device was opened successfully.\n");
        /* Get fixed screen information */
        if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo)) {
                printf("Error reading fixed information.\n");
                exit(2);
        }
        /* Get variable screen information */
        if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo)) {
                printf("Error reading variable information.\n");
                exit(3);
        }
        this->vinfo=vinfo;
        this->finfo=finfo;
        this->width=vinfo.xres;
        this->height=vinfo.yres;
        this->fbfd=fbfd;
        screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;
        color_bytes=vinfo.bits_per_pixel / 8;
        fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED,fbfd, 0);
        if ((int)fbp == -1)
        {
            printf("Error: failed to map framebuffer device to memory.\n"); exit(4);
        }
        printf("The framebuffer device was mapped to memory successfully.\n");
        memset(fbp,0,screensize);
        this->pfb=fbp;
}


void Painter::print_info()
{
        printf("vinfo.xres_virtual : %d , vinfo.yres_virtual : %d\n",vinfo.xres_virtual, vinfo.yres_virtual);
        printf("vinfo.xres=%d\n",vinfo.xres);
        printf("vinfo.yres=%d\n",vinfo.yres);
        printf("vinfo.bits_per_bits=%d\n",vinfo.bits_per_pixel);
        printf("vinfo.xoffset=%d\n",vinfo.xoffset);
        printf("vinfo.yoffset=%d\n",vinfo.yoffset);
        printf("finfo.line_length=%d\n",finfo.line_length); 
}

void Painter::set_color(unsigned int color)
{
    this->color=color;
}
char* Painter::at(unsigned int x, unsigned int y)
{
    long int location = 0;
    location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +(y+vinfo.yoffset) * finfo.line_length;
    return pfb + location ;
}

void Painter::Point(unsigned int x, unsigned int y,unsigned int color)
{
    if ((x < width) && (y < height))
	{
		if (color_bytes == 4)
		{
			((unsigned int*)pfb)[y * (width) + x] = color;
		}
		else
		{
			((unsigned short*)pfb)[y * (width) + x] =(((((unsigned int)(color)) & 0xFF) >> 3) | ((((unsigned int)(color)) & 0xFC00) >> 5) | ((((unsigned int)(color)) & 0xF80000) >> 8));
		}
	}
}

//x1,y1:起点坐标
//x2,y2:终点坐标
void Painter::Line(unsigned short x1, unsigned short y1, unsigned short x2, unsigned short y2,unsigned int color)
{
    unsigned short t;
    int xerr=0,yerr=0,delta_x,delta_y,distance;
    int incx,incy,uRow,uCol;
    delta_x=x2-x1; //计算坐标增量
    delta_y=y2-y1;
    uRow=x1;
    uCol=y1;
    if(delta_x>0)incx=1; //设置单步方向
    else if(delta_x==0)incx=0;//垂直线
    else {incx=-1;delta_x=-delta_x;}
    if(delta_y>0)incy=1;
    else if(delta_y==0)incy=0;//水平线
    else{incy=-1;delta_y=-delta_y;}
    if( delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴
    else distance=delta_y;
    for(t=0;t<=distance+1;t++ )//画线输出
    {
        Point(uRow, uCol,color);
        xerr+=delta_x ;
        yerr+=delta_y ;
        if(xerr>distance)
        {
            xerr-=distance;
            uRow+=incx;
        }
        if(yerr>distance)
        {
            yerr-=distance;
            uCol+=incy;
        }
    }
}

void Painter::Char(unsigned short x,unsigned short y,unsigned char num,unsigned char size,unsigned int color)
{
    unsigned char temp,t1,t;
    unsigned short y0=y;
    unsigned char csize=(size/8+((size%8)?1:0))*(size/2);		//得到字体一个字符对应点阵集所占的字节数
    num=num-' ';//得到偏移后的值（ASCII字库是从空格开始取模，所以-' '就是对应字符的字库）
    for(t=0;t<csize;t++)
    {
        if(size==12)temp=asc2_1206[num][t]; 	 	//调用1206字体
        else if(size==16)temp=asc2_1608[num][t];	//调用1608字体
        else if(size==24)temp=asc2_2412[num][t];	//调用2412字体
        else if(size==32)temp=asc2_3216[num][t];	//调用3216字体
        else return;								//没有的字库
        for(t1=0;t1<8;t1++)
        {
            if(temp&0x80)Point(x,y,color);
            temp<<=1;
            y++;
            if(y>=1024)return;		//超区域了
            if((y-y0)==size)
            {
                y=y0;
                x++;
                if(x>=600)return;	//超区域了
                break;
            }
        }
    }
}





void Painter::Circle(unsigned short x0,unsigned short y0,unsigned char r,unsigned int color)
{
    int a,b;
    int di;
    a=0;b=r;
    di=3-(r<<1);             //判断下个点位置的标志
    while(a<=b)
    {
        Point(x0+a, y0-b,color);
        Point(x0+b, y0-a,color);
        Point(x0+b, y0+a,color);
        Point(x0+a, y0+b,color);
        Point(x0-a, y0+b,color);
        Point(x0-b, y0+a,color);
        Point(x0-a, y0-b,color);
        Point(x0-b, y0-a,color);
        a++;
        //使用Bresenham算法画圆
        if(di<0)di +=4*a+6;
        else
        {
            di+=10+4*(a-b);
            b--;
        }
    }
}


void Painter::String(unsigned short x,unsigned short y,unsigned short width,unsigned short height,unsigned char size,char* p,unsigned int color)
{
    unsigned char x0=x;
    width+=x;
    height+=y;
    while((*p<='~')&&(*p>=' '))//判断是不是非法字符!
    {
        if(x>=width){x=x0;y+=size;}
        if(y>=height)break;//退出
        Char(x, y, (unsigned char)*p,size,color);
        x+=size/2;
        p++;
    }
}

