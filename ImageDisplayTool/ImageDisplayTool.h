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

enum ImagePixelFormat {
	
	BGRA,//BGRA ... BGRA ...BGRA
	RGBA,//RGBA ... RGBA ...RGBA
	ARGB,//ARGB ... ARGB ...ARGB
	ABGR,//ABGR ... ABGR ...ABGR
	
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
	bool _stdcall SetLogDisplayLevelAndTcpServerPort(enum LogLevel level = LOG_DEBUG, int tcpServerPort = 5051);
	bool _stdcall SendLog(char* strbuffer, enum LogLevel level);
	bool _stdcall SendImage(unsigned char* pSrc, unsigned int pixel_width, unsigned int pixel_height, enum ImagePixelFormat type, long long pts = 0);
#ifdef _CPLUSPLUS
}
#endif




