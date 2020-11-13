<!--
 * @Descripttion: 
 * @version: 
 * @Author: Yueyang
 * @email: 1700695611@qq.com
 * @Date: 2020-10-27 16:24:49
 * @LastEditors: Yueyang
 * @LastEditTime: 2020-11-13 17:58:01
-->
# LiteCV 使用说明
## （一）写在前面
或许你会存在这样的需求，对于一张图片你根本无需对其作出太过复杂的处理，但是你有没有，
办法可以很方便的读取一张图片，无论采用什么外部库你都需要经过一些很麻烦，甚至可以说
是并不友好的一些事情。而因为采用了 外部的库，而当那些库并不简单的时候，对于底层的
一些东西就不再变得那么可控了。那么有没有办法可以实现图片的简单读取，同时也可以实现
对底层的完全控制呢。

在大概在一年多以前我就已经在尝试着做一些与图像处理有关的工作了，当时完成了底层的IO
读写，与一些简单的例如灰度增强与仿射变换等工作，但是非常遗憾的是由于当时对于底层数
据架构的处理并不是非常完善，导致后面的工作变得越来越难以进行，所以在最近，我又尝试
重新进行底层架构。目前的整个体系架构可以参考doc\Litecv体系架构.km文件。在这个基础
上我又写了一篇可以通过这个架构进行表盘指针读数的文章，参考doc\应用Litecv的表盘读数
论文.docx。对于现在的体系架构我总体上还是比较满意的。目前已经可以支持常见的文件类型
（BMP，JPEG，PNG）的读写。遗憾的是，并没有做任何与UI有关的工作，导致无法实时显示任
何图片，但这并不重要，对于外部库更少的依赖就意味着你可以更方便的进行移植与编译。


## （二）简单的测试一下吧
### （1）Windows下的测试
如果你用的是windows电脑，那么就很简单了，你可以双击win_build下的任何一个可执行文件，
这些程序实现了一些常用的功能例如 图片读取与显示，对于图片进行画笔操作。图像滤波卷积，
边缘检测等等，在这个时候，当前文件夹下多出的文件就是这个程序生成的文件。

### （2）Linux下的测试
和上面一样，进入linux_build文件夹./XXX 运行相应的程序

### （3）arm 
请转到下面的编译


## （三）如何快捷的编译代码

###  （1）首先我们来看一下我们需要编译哪些文件
Core文件夹中，我们只需要编译li_image.c  ,为啥嘞，
Core文件夹下的其他文件都已经被我include到li_image.c
文件中了，所以编译会很简单。

对于头文件请在编译选项中引入以下头文件目录：
Litecv\inc\Core

Imgproc中的文件可以选择不编译，如果你只想要实现一些最
简单的IO读取功能的话。如果需要编译的话那么只要编译
li_image_proc.c文件即可。

对于头文件请在编译选项中引入以下头文件目录：
Litecv\inc\Imgproc

### （2）怎么编译呢
对于使用GNU套件的人来说，那就很简单了，因为我们使用了
Cmake的管理工具，但是如果你用的是其他的编译器的话也不
要紧，反正只有两个文件，编译应该问题不大。就是将前面两
个文件一起编译即可。

#### （I）windows下的编译

##### （一）按照我写的脚本编译
###### 1）你需要先下载以下两个软件

[MinGW下载地址](https://sourceforge.net/projects/mingw-w64/files/mingw-w64/mingw-w64-release/)

[Cmake下载地址](https://cmake.org/files/)

（2）修改编译文件
就是CMakeLists.txt文件如下
```shell
cmake_minimum_required(VERSION 3.2)
project(LICV)
include_directories (Litecv/inc/Core)
include_directories (Litecv/inc/Imgproc)
aux_source_directory(./ DIR_MAIN)
set(LICV_MAIN ${DIR_MAIN})

add_compile_options(-std=c99)

aux_source_directory(./example/basicio DIR_EXP01)
set(LICV_EXP01 ${DIR_EXP01})
aux_source_directory(./example/painter DIR_EXP02)
set(LICV_EXP02 ${DIR_EXP02})
aux_source_directory(./example/conv   DIR_EXP04)
set(LICV_EXP04 ${DIR_EXP04})
aux_source_directory(./example/canny   DIR_EXP05)
set(LICV_EXP05 ${DIR_EXP05})

set(ARM OFF)

if(ARM)
aux_source_directory(./example/arm9 DIR_EXP03)
set(LICV_EXP03 ${DIR_EXP03})

else()
if (CMAKE_HOST_WIN32)
    set(WINDOWS ON)
elseif (CMAKE_HOST_APPLE)
    set(MACOS   ON)
elseif (CMAKE_HOST_UNIX)
    set(LINUX   ON)
endif ()
endif()


set(USE_JPEG   ON)
set(USE_PNG    ON)
add_subdirectory(Litecv)


add_executable(${PROJECT_NAME} ${LICV_MAIN})
target_link_libraries(${PROJECT_NAME} licvcore)
target_link_libraries(${PROJECT_NAME} licvimgproc)

add_executable(IO ${LICV_EXP01})
target_link_libraries(IO licvcore)

add_executable(Painter ${LICV_EXP02})
target_link_libraries(Painter licvcore)

add_executable(smooth ${LICV_EXP04})
target_link_libraries(smooth licvcore)
target_link_libraries(smooth licvimgproc)

add_executable(canny ${LICV_EXP05})
target_link_libraries(canny licvcore)
target_link_libraries(canny licvimgproc)


if(ARM)
add_executable(display ${LICV_EXP03})
target_link_libraries(display licvcore)
endif(ARM)
```

就是将
```
set(USE_JPEG   ON)
set(USE_PNG    ON)
```
改成
```
set(USE_JPEG   OFF)
set(USE_PNG    OFF)
```
再将inc/Core/cv.h文件中的
```
//是否支持JPEG与PNG
#define EN_JPEG 1
#define EN_PNG  1
```
改为
```
//是否支持JPEG与PNG
#define EN_JPEG 0
#define EN_PNG  0
```
这样就可以编译了

进入win_build，当然也可以自己新建一个文件
运行
 ```
 cmake.exe ../ -G "MinGW Makefiles"
 mingw32-make.exe
 ```


#### (二)gcc直接编译的方法
Makefile我就不写了
```
gcc -c .\li_image.c -I../inc/Core -o li_image.o

ar -r .\li_image.a .\li_image.o

gcc -c .\li_image_proc.c -I..\inc\Core\  -I..\inc\Imgproc\ -o li_image_proc.o

ar -r .\li_image_proc.a .\li_image_proc.o

gcc .\main.c  .\Litecv\Core\li_image.a .\Litecv\Imgproc\li_image_proc.a  -I.\Litecv\inc\Core\  -I.\Litecv\inc\Imgproc\ -o Licv
```

### （3）不想用jpeg，png图片的可以不看了


这里使用的是从网上下载的MinGw版本，将路径C:MinGW\bin加到"环境变量"→"系统变量"→"Path"
命令行输入：
gcc -v
可看到gcc版本为：gcc version 8.1.0 (rev2, Built by MinGW-builds project)

#### MSYS
下载地址：http://www.mingw.org/wiki/MSYS
当前版本：1.0.11
一路安装下去即可

#### zlib
下载地址：http://www.zlib.net/
当前版本：1.2.11
命令行输入：
	
    cp win32\makefile.gcc makefile.gcc
    mingw32-make -f makefile.gcc

生成libz.a文件

#### libpng

下载地址：http://www.libpng.org/pub/png/libpng.html
当前版本：1.6.37
打开scripts/makefile.gcc设置zlib路径：
	
    ZLIBINC = ../zlib-1.2.11
    ZLIBLIB = ../zlib-1.2.11

拷贝scripts/pnglibconf.h.prebuilt到源码目录，改名为pnglibconf.h
命令行输入：
		
    cp scripts\makefile.gcc makefile.gcc
    mingw32-make -f makefile.gcc

生成libpng.a文件

#### libjpeg

下载地址：http://www.ijg.org/
当前版本：9
打开MSYS (rxvt)，输入：
	
	
    cd jpeg-9
    ./configure
    make

若是出现以下错误：

	
	
jcapimin.c:127:1: error: conflicting types for 'jpeg_suppress_tables'
 jpeg_suppress_tables (j_compress_ptr cinfo, boolean suppress)

打开jconfig.h，增加以下定义：

	
#define HAVE_PROTOTYPES 1

重新输入：
	
make 

上面的库编完以后修改：
``` shell
Litecv\CMakeLists.txt文件
cmake_minimum_required(VERSION 3.2)
include_directories(
    inc/Core
    inc/Imgproc
)
FILE(GLOB DIR_SRCS  "Core/li_image.c")
FILE(GLOB PROC_SRCS "Imgproc/li_image_proc.c")

SET(LICV_CORE ${DIR_SRCS})
SET(LICV_PROC ${PROC_SRCS})

#根据实际情况修改静态库的绝对路径
#linux中不需要指定库的头文件目录
if(LINUX)
    if(USE_JPEG)
    include_directories(/home/swann/LiteCV/Litecv/3rd/linux_3rd_lib/jpeg_linux_install/include)
    #include_directories(/home/swann/IMX_283A/Qt/App/LiteCV/Litecv/3rd/linux_3rd_lib/jpeg_linux_install/include)
    #使用编译器自带的jpeg库
    link_libraries(/home/swann/LiteCV/Litecv/3rd/linux_3rd_lib/jpeg_linux_install/lib/libjpeg.a)
    #link_libraries(/home/swann/IMX_283A/Qt/App/LiteCV/Litecv/3rd/linux_3rd_lib/jpeg_linux_install/lib/libjpeg.a)
    #link_libraries(libjpeg.a )
    endif(USE_JPEG)

    if(USE_PNG)

    include_directories(/home/swann/LiteCV/Litecv/3rd/linux_3rd_lib/png_linux_install/include)
    link_libraries(/home/swann/LiteCV/Litecv/3rd/linux_3rd_lib/png_linux_install/lib/libpng16.a)
    link_libraries(/home/swann/LiteCV/Litecv/3rd/linux_3rd_lib/zlib_linux_install/lib/libz.a)

    #include_directories(/home/swann/IMX_283A/Qt/App/LiteCV/Litecv/3rd/arm_3rd_build/png_arm_install/include)
    #link_libraries(/home/swann/IMX_283A/Qt/App/LiteCV/Litecv/3rd/linux_3rd_lib/png_linux_install/lib/libpng.a)
    #link_libraries(/home/swann/IMX_283A/Qt/App/LiteCV/Litecv/3rd/linux_3rd_lib/zlib_linux_install/lib/libz.a )
    link_libraries(  m)
    endif(USE_PNG)

elseif(WINDOWS)
    if(USE_JPEG)
    include_directories(E:/LiteCV/Litecv/3rd/win_3rd_lib/jpeg_win_install/include)
    link_libraries(E:/LiteCV/Litecv/3rd/win_3rd_lib/jpeg_win_install/lib/libjpeg.a )
    endif(USE_JPEG)
    if(USE_PNG)
    include_directories( E:/LiteCV/Litecv/3rd/win_3rd_lib/png_win_install/include)
    link_libraries(  E:/LiteCV/Litecv/3rd/win_3rd_lib/png_win_install/lib/libpng.a)
    link_libraries(  E:/LiteCV/Litecv/3rd/win_3rd_lib/zlib_win_install/lib/libz.a )
    link_libraries(  m)
    endif(USE_PNG)

elseif(ARM)
    Message(ARM)
    if(USE_JPEG)
    include_directories(/home/swann/IMX_283A/Qt/App/LiteCV/Litecv/3rd/arm_3rd_build/jpeg_arm_install/include)
    #使用编译器自带的jpeg库
    link_libraries(/home/swann/IMX_283A/Qt/App/LiteCV/Litecv/3rd/arm_3rd_build/jpeg_arm_install/lib/libjpeg.a)
    endif(USE_JPEG)

    if(USE_PNG)
    include_directories(/home/swann/IMX_283A/Qt/App/LiteCV/Litecv/3rd/arm_3rd_build/png_arm_install/include)
    link_libraries(/home/swann/IMX_283A/Qt/App/LiteCV/Litecv/3rd/arm_3rd_build/png_arm_install/lib/libpng.a)
    link_libraries(/home/swann/IMX_283A/Qt/App/LiteCV/Litecv/3rd/arm_3rd_build/zlib_arm_install/lib/libz.a)
    link_libraries(  m)
    endif(USE_PNG)
endif()
add_library(licvcore   STATIC  ${LICV_CORE})
add_library(licvimgproc STATIC  ${LICV_PROC})
```

把目录改一下。

#### （II）Linux下的编译与arm交叉编译
和windows基本一样，新建一个文件

cmake ..

make 即可

如果是交叉编译可以在cmake-gui中修改编译器



 #### libjpeg编译：

<ul>
<li>下载libjpeg源码：http://www.ijg.org/
下载jpegsrc.v9a.tar.gz<br>
<li>解压源码,命令：tar -zxvf jpegsrc.v9a,
源码文件夹为jpeg-9a<br>
<li>运行命令：./configure --prefix=jpeg-9a/release --enable-shared=no<br>
 <li>在jpeg-9a下查找Makefile文件并打开，查找CFLAGS，在CFLAGS = -g -02 后面添加 -fPIC<br>
 <li>运行命令：make<br>
 <li>运行命令：make install<br>
 <li>最终静态库文件安装在jpeg-9a/release/lib下
</ul>

#### libPng编译：

编译libPng首先需要编译zlib，过程如下：
<ul>
<li>下载zlib源码zlib-1.2.11.tar.gz<br>
    <li>解压zlib源码到zlib-1.2.11<br>
    <li>运行命令：./configure --static   静态编译<br>
    <li>在zlib-1.2.11下查找Makefile文件并打开，查找CFLAGS 并在该行最后加上 -fPIC<br>
    <li>运行命令：make<br>
    <li>运行命令：make install<br>
</ul>
下面编译libpng
<ul>
    <li>下载源码libpng-1.6.37.tar.gz<br>
    <li>解压到libpng-1.6.37<br>
    <li>运行命令：./configure --prefix=libpng-1.6.37/release --enable-shared=no<br>
    <li>在libpng-1.6.13下查找Makefile文件并打开，查找CFLAGS并在该行最后加上 -fPIC<br>
    <li>运行命令：make<br>
    <li>运行命令：make install<br>
</ul>
最后将所有的库文件归拢一下就OK了

### (3) 交叉编译

./configure --prefix=/home/swann/IMX_283A/Qt/App/LiteCV/Litecv/3rd/src/libpng-1.6.37/png_arm_install --host=arm-linux CC=arm-none-linux-gnueabi-gcc CFLAGS=-I/home/swann/IMX_283A/Qt/App/LiteCV/Litecv/3rd/src/zlib-1.2.11/zlib_arm_install/include LDFLAGS=-L/home/swann/IMX_283A/Qt/App/LiteCV/Litecv/3rd/src/zlib-1.2.11/zlib_arm_install/lib --prefix=/home/swann/IMX_283A/Qt/App/LiteCV/Litecv/3rd/src/libpng-1.6.37/png_arm_install

//change  makefile
DEFAULT_INCLUDES = -I.
DEFAULT_INCLUDES +=-I/home/swann/IMX_283A/Qt/App/LiteCV/Litecv/3rd/src/zlib-1.2.11/zlib_arm_install/include



