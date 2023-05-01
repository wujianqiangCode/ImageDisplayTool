#include "../ImageDisplayTool/ImageDisplayTool.h"
#ifdef _WIN32
#pragma comment(lib, "ImageDisplayTool.lib")
#include <windows.h>
#else
#include <string.h>
#endif
#include <GL/gl.h>
#include <assert.h>
#include <iostream>
using namespace std;
int main() {

#if 0
	// 运行时加载DLL库
	HMODULE module = LoadLibrary(L"ImageDisplayTool.dll");
	if (module == NULL)
	{
		printf("加载ImageDisplayTool.dll动态库失败\n");
		return -1;
	}

	typedef bool(*SetLogDisplayLevelAndTcpServerPortFunc)(LogLevel, int); // 定义函数指针类型
	SetLogDisplayLevelAndTcpServerPortFunc SetLogDisplayLevelAndTcpServerPort;
	// 导出函数地址
	SetLogDisplayLevelAndTcpServerPort = (SetLogDisplayLevelAndTcpServerPortFunc)GetProcAddress(module, "SetLogDisplayLevelAndTcpServerPort");

	typedef bool(*SendLogFunc)(char*, LogLevel); // 定义函数指针类型
	SendLogFunc SendLog;
	// 导出函数地址
	SendLog = (SendLogFunc)GetProcAddress(module, "SendLogFunc");

	typedef bool(*SendImageFunc)(unsigned char* , unsigned int , unsigned int , enum ImagePixelFormat ); // 定义函数指针类型
	SendImageFunc SendImage;
	// 导出函数地址
	SendImage = (SendImageFunc)GetProcAddress(module, "SendImage");

#endif

	bool flage = SetTcpServerPort(5051);
	assert(flage);

//#define TestLog 1
#define TestImage 1
#ifdef TestLog
	char ss[24];
	memset(ss, 0, sizeof(ss));
#ifdef __linux__
	snprintf(ss, sizeof("TestSendLog"), "TestSendLog");
#else
	sprintf_s(ss, "TestSendLog");
#endif
	SetLogDisplayLevel(LOG_INFO);
	flage = SendLog(ss, LOG_INFO);
	
#elif TestImage

#define TestOpenGL 1

#ifdef TestRGBImage

	IMAGE image;
	image.type = IF_RGB;
	image.pixel_width = 200;
	image.pixel_height = 100;
	image.rgb_info.format = RGBA;
	image.rgb_info.pData = new unsigned char[image.pixel_width* image.pixel_height* 4]();
	memset(image.rgb_info.pData, 255, sizeof(image.rgb_info.pData));
	image.pts = 100;
	flage = SendImage(image);
#elif TestYUVImage
	
	IMAGE image;
	image.type = IF_YUV;
	image.pixel_width = 200;
	image.pixel_height = 100;
	image.yuv_info.format = NV12;
	image.yuv_info.pData = new unsigned char[image.pixel_width* image.pixel_height* 3 /2]();
	memset(image.yuv_info.pData, 128, sizeof(image.yuv_info.pData));
	image.pts = 100;
	flage = SendImage(image);
#elif TestOpenGL

	IMAGE image;
	GLenum err;
	image.type = IF_OpenGL;
	image.pixel_width = 200;
	image.pixel_height = 100;
	image.opengl_info.target = GL_TEXTURE_2D;

	if(0){

		image.opengl_info.format = OpenGL_RGBA;
		unsigned char *data = new unsigned char[image.pixel_width* image.pixel_height* 4]();  // CPU memory
		memset(image.rgb_info.pData, 255, sizeof(image.rgb_info.pData));
		glGenTextures(1, image.opengl_info.texture_id);
		glBindTexture(image.opengl_info.target, image.opengl_info.texture_id[0]);
		err = glGetError();
		// data的数据内容为【R(1 byte), G(1 byte), B(1 byte), A(1 byte)】, 【R(1 byte), G(1 byte), B(1 byte), A(1 byte)】...
		glTexImage2D(image.opengl_info.target, 0, GL_RGBA, image.pixel_width, image.pixel_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		err = glGetError();
		glBindTexture(image.opengl_info.target, 0);
	}
	else{

		image.opengl_info.format = OpenGL_NV12;
		unsigned char *data = new unsigned char[image.pixel_width* image.pixel_height* 3 /2]();  // CPU memory
		memset(image.rgb_info.pData, 255, sizeof(image.rgb_info.pData));

		//y
		glGenTextures(1, image.opengl_info.texture_id);
		glBindTexture(image.opengl_info.target, image.opengl_info.texture_id[0]);
		err = glGetError();
		glTexImage2D(image.opengl_info.target, 0, GL_LUMINANCE, image.pixel_width, image.pixel_height, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, data);
		err = glGetError();
		glTexParameteri(image.opengl_info.target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(image.opengl_info.target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(image.opengl_info.target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(image.opengl_info.target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//uv
		glGenTextures(1, &(image.opengl_info.texture_id[1]));
		glBindTexture(image.opengl_info.target, image.opengl_info.texture_id[1]);
		err = glGetError();
		glTexImage2D(image.opengl_info.target, 0, GL_LUMINANCE_ALPHA, image.pixel_width/2, image.pixel_height/2, 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, &data[image.pixel_width* image.pixel_height]);
		err = glGetError();
		glTexParameteri(image.opengl_info.target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(image.opengl_info.target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(image.opengl_info.target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(image.opengl_info.target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
		glBindTexture(image.opengl_info.target, 0);
	}
	

	image.pts = 100;
	flage = SendImage(image);

#elif TestD3D 
	
#elif TestMetal
#endif
#endif
	assert(flage);
	return 0;
}
