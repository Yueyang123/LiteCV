<!--
 * @Descripttion: 
 * @version: 
 * @Author: Yueyang
 * @email: 1700695611@qq.com
 * @Date: 2020-10-27 16:24:49
 * @LastEditors: Yueyang
 * @LastEditTime: 2020-11-01 11:29:01
-->
# LiteCV 使用说明
## （一）写在前面
在大概在一年多以前我就已经在尝试着，



## （二）三方库的编译方式总结

说明:下面的库都有提供但是可能编译器版本不同，需要自己编译
我使用的编译器分别是 gcc-9.3
                    mingw-8.1

### (1)Windows 中使用mingw 编译libjpeg libpng libz

#### MinGW
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


### (2) Linux 中使用默认gcc直接编译libjpeg libpng libz

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

