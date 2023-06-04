/*****************************************************************************
*  ImageDisplayTool
*  Copyright (C) 2023 ijianqiangwu@outlook.com
*
*  @file     ImageDisplayTool.h
*  @brief    对文件的简述
*  Details.
*
*  @author   WuJianQiang
*  @email    ijianqiangwu@outlook.com
*  @version  1.0.0.1(版本号)
*  @date     2023.05.30
*  @license  GNU General Public License (GPL)
*
*----------------------------------------------------------------------------
*  Remark         : Description
*----------------------------------------------------------------------------
*  Change History :
*  <Date>     | <Version> | <Author>       | <Description>
*----------------------------------------------------------------------------
*  2023/05/30 | 1.0.0.1   | WuJianQiang          | Create file
*----------------------------------------------------------------------------
*
*****************************************************************************/

#pragma once
#include <stdbool.h>
#ifndef WIN32
#define _stdcall
#else
#define _stdcall
#endif // WIN32


/*
	YUV格式：粗分有两大类：Planar和Packed。细分有三大类，分别是Planar和Packed，再加上Semi-Planar半平面格式。
		- 对于Planar的YUV格式，先连续存储所有像素点的Y，紧接着存储所有像素点的U，随后是所有像素点的V。
		- 对于Semi-Planar半平面的YUV格式，Y分量单独存储，但是UV分量交叉存储。
		- 对于Packed的YUV格式，每个像素点的Y,U,V是连续交错存储的。
	由于平面格式后缀为p，半平面后缀为sp，包格式不带后缀，并且：
	YUV 4:4:4采样，每一个Y对应一组UV分量。
	YUV 4:2:2采样，每两个Y共用一组UV分量。
	YUV 4:2:0采样，每四个Y共用一组UV分量。
	PS:UV是我们经常说的Cr和Cb变量
*/
enum IMAGE_RGB_FORMAT{

	BGRA,//BGRA ... BGRA ...BGRA
	RGBA,//RGBA ... RGBA ...RGBA
	ARGB,//ARGB ... ARGB ...ARGB
	ABGR,//ABGR ... ABGR ...ABGR
};

enum IMAGE_YUV_FORMAT {
	
	//YUV 420 Planar
	I420,//(yu12，即I420);首先y是连续存储的，然后到u连续存储，再到v连续存储。每4个y对应一组uv分量
	YV12,//首先存储Y，然后连续存储V，最后连续存储U

	//YUV 420 Semi-Planar
	NV12,//首先存储连续的Y，然后UV分别交错存储;4个y对应一组UV分量
	NV21,//首先存储连续的Y，然后VU分别交错存储;4个y对应一组VU分量
	
	//YUV 422 Planar
	I422,//首先y是连续存储的，然后到u连续存储，再到v连续存储。每2个y对应一组uv分量
	YV16,//首先存储Y，然后连续存储V，最后连续存储U

	//YUV 422  Semi-Planar
	NV16,//首先存储连续的Y，然后UV分别交错存储;2个y对应一组UV分量
	NV61,//首先存储连续的Y，然后VU分别交错存储;2个y对应一组VU分量

	//YUV 422  Interleaved
	YUYV,//两个Y对应一组UV变量，并且是交错进行(YUYV ... YUYV ... YUYV)
	YUVY,//两个Y对应一组VU变量，并且是交错进行(YVYU ... YVYU ... YVYU)
	VYUY,//两个Y对应一组VU变量，并且是交错进行(VYUY ... VYUY ... VYUY)
	UYVY,//两个Y对应一组VU变量，并且是交错进行(UYVY ... UYVY ... UYVY)

	//YUV 444 Planar
	I444,//首先y是连续存储的，然后到u连续存储，再到v连续存储。每个y对应一组uv分量
	YV24,//首先存储Y，然后连续存储V，最后连续存储U

	//YUV 444 Semi-Planar
	NV24,//首先存储连续的Y，然后UV分别交错存储;每个y对应一组UV分量
	NV42,//首先存储连续的Y，然后VU分别交错存储;每个y对应一组VU分量

	//YUV 444 Packed
	IYUV,//Y，U，V都是交错进行存储的(YUV ... YUV ... YUV)，一个Y对应一个UV分组

};
enum IMAGE_OpenGL_FORMAT{
	
	OpenGL_BGRA,//BGRA ... BGRA ...BGRA
	OpenGL_RGBA,//RGBA ... RGBA ...RGBA
	
	//YUV 420 Semi-Planar
	OpenGL_NV12,//首先存储连续的Y，然后UV分别交错存储;4个y对应一组UV分量
	OpenGL_NV21,//首先存储连续的Y，然后VU分别交错存储;4个y对应一组VU分量

};
enum IMAGE_IDirect3D_TYPE{

	/*IDirect3DTexture9数据*/
	IF_IDirect3DTexture9,

	/*IDirect3DSurface9数据*/
	IF_IDirect3DSurface9,	

	/*IDirect3DTexture10数据*/
	IF_IDirect3DTexture10,

	/*IDirect3DSurface10数据*/
	IF_IDirect3DSurface10,

	/*IDirect3DTexture10数据*/
	IF_IDirect3DTexture11,

	/*IDirect3DSurface11数据*/
	IF_IDirect3DSurface11,

	/*IDirect3DTexture12数据*/
	IF_IDirect3DTexture12,

	/*IDirect3DSurface12数据*/
	IF_IDirect3DSurface12,
};
struct IMAGE_RGB_INFO{
	IMAGE_RGB_FORMAT format;
	unsigned char* pData;
};
struct IMAGE_YUV_INFO{
	IMAGE_YUV_FORMAT format;
	unsigned char* pData;
};
struct IMAGE_OpenGL_INFO{
	unsigned int texture_id[2];//NV12模式存两个纹理
	unsigned int target; // GL_TEXTURE_2D or GL_RECTANGLE_ARB
	IMAGE_OpenGL_FORMAT format;
 	void *share_window;
};
struct IMAGE_CVPIXEL_INFO{

};
struct IMAGE_Metal_INFO{

};
struct IMAGE_IDirect3D_INFO{

};
/*!
* \struct IMAGE_TYPE
* \brief  视频图像的类型
*/

 enum IMAGE_TYPE{

	/*! RGB类型*/
	IF_RGB,

	/*! YUV类型*/
	IF_YUV,

	/*OpenGLTexture数据*/
	IF_OpenGL,

	/*CVPixel数据*/
	IF_CVPIXEL,

	/*Metal纹理*/
	IF_Metal,

	/*IDirect3D纹理*/
	IF_IDirect3D,
};

struct IMAGE{
	IMAGE_TYPE type;
	union {
		/*! RGB类型*/
		IMAGE_RGB_INFO rgb_info;

		/*! YUV类型*/
		IMAGE_YUV_INFO yuv_info;

		/*OpenGLTexture数据*/
		IMAGE_OpenGL_INFO opengl_info;

		/*CVPixel数据*/
		IMAGE_CVPIXEL_INFO vcpixel_info;

		/*Metal纹理*/
		IMAGE_Metal_INFO metal_info;

		/*IDirect3D纹理*/
		IMAGE_IDirect3D_INFO d3d_info;
	};

	unsigned int pixel_width;
	unsigned int pixel_height;
	long long pts;
};

enum LogLevel {
	LOG_ERROR,
	LOG_WARNING,
	LOG_INFO,
	LOG_DEBUG,
};

#ifdef _CPLUSPLUS
extern "C"
{
#endif

/*
	端口号从1025到49151是注册端口：这些端口多数没有明确的定义服务对象，不同程序可根据实际需要自己定义，咱们可以使用
	socket服务器和客户端的端口只能是49152到65535：因为计算机之间相互通信一般采用这两种通信协议，TCP协议端口和UDP协议端口
*/	
	bool _stdcall SetTcpInfo(char* tcpServerIP, int tcpServerPort = 5051);

	bool _stdcall SetLogDisplayLevel(enum LogLevel level = LOG_DEBUG);
	bool _stdcall SendLog(char* strbuffer, enum LogLevel level);

	bool _stdcall SendImage(IMAGE image);
	
#ifdef _CPLUSPLUS
}
#endif




