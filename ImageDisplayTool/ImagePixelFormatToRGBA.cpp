#include "ImagePixelFormatToRGBA.h"
#include <stdio.h>

void BGRAToRGBA(const unsigned char* bgra, unsigned char* rgba,
	unsigned int pixel_width, unsigned int pixel_height) {

	int offset = 0;
	rgba = new unsigned char[pixel_width * pixel_height * 4]();
	for (unsigned int y = 0; y < pixel_height; y++) {
		for (unsigned int x = 0; x < pixel_width; x++) {

			auto temp = rgba[offset];
			rgba[offset] = bgra[offset + 2];//R
			rgba[offset + 1] = bgra[offset + 1];//G
			rgba[offset + 2] = temp;//B
			rgba[offset + 3] = bgra[offset + 3];//A

			offset += 4;
		}
	}
}
void ABGRToRGBA(const unsigned char* abgr, unsigned char* rgba,
	unsigned int pixel_width, unsigned int pixel_height) {

	int offset = 0;
	rgba = new unsigned char[pixel_width * pixel_height * 4]();
	for (unsigned int y = 0; y < pixel_height; y++) {
		for (unsigned int x = 0; x < pixel_width; x++) {

			auto temp = rgba[offset];
			rgba[offset] = abgr[offset + 3];//R
			rgba[offset + 1] = abgr[offset + 2];//G
			rgba[offset + 2] = abgr[offset + 1];//B
			rgba[offset + 3] = temp;//A

			offset += 4;
		}
	}
}
void ARGBToRGBA(const unsigned char* argb, unsigned char* rgba,
	unsigned int pixel_width, unsigned int pixel_height) {
	
	int offset = 0;
	rgba = new unsigned char[pixel_width * pixel_height * 4]();
	for (unsigned int y = 0; y < pixel_height; y++) {
		for (unsigned int x = 0; x < pixel_width; x++) {

			auto temp = rgba[offset];
			rgba[offset] = argb[offset + 1];//R
			rgba[offset + 1] = argb[offset + 2];//G
			rgba[offset + 2] = argb[offset + 3];//B
			rgba[offset + 3] = temp;//A

			offset += 4;
		}
	}
}
void I420ToRGBA(const unsigned char* yuv, unsigned char* rgba,
	unsigned int pixel_width, unsigned int pixel_height) {

	register int U, V, R, G, B, V2, U5, UV;
	register int Y0, Y1, Y2, Y3;
	rgba = new unsigned char[pixel_width * pixel_height * 4]();
	unsigned int size = pixel_width * pixel_height;
	const unsigned char* iU = yuv + size;
	const unsigned char* iV = yuv + 5 * size / 4;
	for (unsigned int i = 0; i < pixel_height / 2; i++)
	{
		for (unsigned int j = 0; j < pixel_width / 2; j++)
		{
			U = (int)((*iU++ - 128) * 0.354);
			U5 = 5 * U;
			V = (int)((*iV++ - 128) * 0.707);
			V2 = 2 * V;
			UV = -U - V;
			Y0 = *yuv++;
			Y1 = *yuv;
			yuv = yuv + pixel_width - 1;
			Y2 = *yuv++;
			Y3 = *yuv;
			yuv = yuv - pixel_width + 1;

			// Original equations
			// R = Y           + 1.402 V
			// G = Y - 0.344 U - 0.714 V
			// B = Y + 1.772 U
			R = Y0 + V2;
			if ((R >> 8) > 0) R = 255; else if (R < 0) R = 0;

			G = Y0 + UV;
			if ((G >> 8) > 0) G = 255; else if (G < 0) G = 0;

			B = Y0 + U5;
			if ((B >> 8) > 0) B = 255; else if (B < 0) B = 0;

			*rgba++ = (unsigned char)R;
			*rgba++ = (unsigned char)G;
			*rgba++ = (unsigned char)B;
			*rgba++ = 0;

			//---
			R = Y1 + V2;
			if ((R >> 8) > 0) R = 255; else if (R < 0) R = 0;

			G = Y1 + UV;
			if ((G >> 8) > 0) G = 255; else if (G < 0) G = 0;

			B = Y1 + U5;
			if ((B >> 8) > 0) B = 255; else if (B < 0) B = 0;

			*rgba++ = (unsigned char)R;
			*rgba++ = (unsigned char)G;
			*rgba++ = (unsigned char)B;
			*rgba = 0;
			rgba = rgba + 4 * pixel_width - 7;

			//---
			R = Y2 + V2;
			if ((R >> 8) > 0) R = 255; else if (R < 0) R = 0;

			G = Y2 + UV;
			if ((G >> 8) > 0) G = 255; else if (G < 0) G = 0;

			B = Y2 + U5;
			if ((B >> 8) > 0) B = 255; else if (B < 0) B = 0;

			*rgba++ = (unsigned char)R;
			*rgba++ = (unsigned char)G;
			*rgba++ = (unsigned char)B;
			*rgba++ = 0;

			//---
			R = Y3 + V2;
			if ((R >> 8) > 0) R = 255; else if (R < 0) R = 0;

			G = Y3 + UV;
			if ((G >> 8) > 0) G = 255; else if (G < 0) G = 0;

			B = Y3 + U5;
			if ((B >> 8) > 0) B = 255; else if (B < 0) B = 0;

			*rgba++ = (unsigned char)R;
			*rgba++ = (unsigned char)G;
			*rgba++ = (unsigned char)B;
			*rgba = 0;
			rgba = rgba - 4 * pixel_width + 1;
		}
		yuv += pixel_width;
		rgba += 4 * pixel_width;
	}
}

void YV12ToRGBA(const unsigned char* yuv, unsigned char* rgba,
	unsigned int pixel_width, unsigned int pixel_height) {
	
	register int U, V, R, G, B, V2, U5, UV;
	register int Y0, Y1, Y2, Y3;
	rgba = new unsigned char[pixel_width * pixel_height * 4]();
	unsigned int size = pixel_width * pixel_height;
	const unsigned char* iV = yuv + size;
	const unsigned char* iU = yuv + 5 * size / 4;
	for (unsigned int i = 0; i < pixel_height / 2; i++)
	{
		for (unsigned int j = 0; j < pixel_width / 2; j++)
		{
			U = (int)((*iU++ - 128) * 0.354);
			U5 = 5 * U;
			V = (int)((*iV++ - 128) * 0.707);
			V2 = 2 * V;
			UV = -U - V;
			Y0 = *yuv++;
			Y1 = *yuv;
			yuv = yuv + pixel_width - 1;
			Y2 = *yuv++;
			Y3 = *yuv;
			yuv = yuv - pixel_width + 1;

			R = Y0 + V2;
			if ((R >> 8) > 0) R = 255; else if (R < 0) R = 0;

			G = Y0 + UV;
			if ((G >> 8) > 0) G = 255; else if (G < 0) G = 0;

			B = Y0 + U5;
			if ((B >> 8) > 0) B = 255; else if (B < 0) B = 0;

			*rgba++ = (unsigned char)R;
			*rgba++ = (unsigned char)G;
			*rgba++ = (unsigned char)B;
			*rgba++ = 0;

			//---
			R = Y1 + V2;
			if ((R >> 8) > 0) R = 255; else if (R < 0) R = 0;

			G = Y1 + UV;
			if ((G >> 8) > 0) G = 255; else if (G < 0) G = 0;

			B = Y1 + U5;
			if ((B >> 8) > 0) B = 255; else if (B < 0) B = 0;

			*rgba++ = (unsigned char)R;
			*rgba++ = (unsigned char)G;
			*rgba++ = (unsigned char)B;
			*rgba = 0;
			rgba = rgba + 4 * pixel_width - 7;

			//---
			R = Y2 + V2;
			if ((R >> 8) > 0) R = 255; else if (R < 0) R = 0;

			G = Y2 + UV;
			if ((G >> 8) > 0) G = 255; else if (G < 0) G = 0;

			B = Y2 + U5;
			if ((B >> 8) > 0) B = 255; else if (B < 0) B = 0;

			*rgba++ = (unsigned char)R;
			*rgba++ = (unsigned char)G;
			*rgba++ = (unsigned char)B;
			*rgba++ = 0;

			R = Y3 + V2;
			if ((R >> 8) > 0) R = 255; else if (R < 0) R = 0;

			G = Y3 + UV;
			if ((G >> 8) > 0) G = 255; else if (G < 0) G = 0;

			B = Y3 + U5;
			if ((B >> 8) > 0) B = 255; else if (B < 0) B = 0;

			*rgba++ = (unsigned char)R;
			*rgba++ = (unsigned char)G;
			*rgba++ = (unsigned char)B;
			*rgba = 0;
			rgba = rgba - 4 * pixel_width + 1;
		}
		yuv += pixel_width;
		rgba += 4 * pixel_width;
	}
}

void NV12ToRGBA(const unsigned char* yuv, unsigned char* rgba,
	unsigned int pixel_width, unsigned int pixel_height) {
	
	//nv12
	int total = pixel_width * pixel_height;
	rgba = new unsigned char[pixel_width * pixel_height * 4]();
	char Y, U, V;
	float R, G, B;
	int index = 0;

	for (unsigned int h = 0; h < pixel_height; h++) {
		for (unsigned int w = 0; w < pixel_width / 2; w++) {

			Y = yuv[h * pixel_width + w * 2];
			V = yuv[total + (h >> 1) * pixel_width + w * 2];
			U = yuv[total + (h >> 1) * pixel_width + w * 2 + 1];
			R = Y + 1.4075 * (U - 128);
			G = Y - 0.3455 * (V - 128) - 0.7169 * (U - 128);
			B = Y + 1.779 * (V - 128);

			if (R < 0) R = 0;
			if (R > 255) R = 255;
			if (G < 0) G = 0;
			if (G > 255) G = 255;
			if (B < 0) B = 0;
			if (B > 255) B = 255;

			rgba[index++] = B;
			rgba[index++] = G;
			rgba[index++] = R;
			rgba[index++] = 255;

			Y = yuv[h * pixel_width + w * 2 + 1];
			R = Y + 1.4075 * (V - 128);
			G = Y - 0.3455 * (U - 128) - 0.7169 * (V - 128);
			B = Y + 1.779 * (U - 128);

			if (R < 0) R = 0;
			if (R > 255) R = 255;
			if (G < 0) G = 0;
			if (G > 255) G = 255;
			if (B < 0) B = 0;
			if (B > 255) B = 255;

			rgba[index++] = B;
			rgba[index++] = G;
			rgba[index++] = R;
			rgba[index++] = 255;
		}
	}
}


void NV21ToRGBA(const unsigned char* yuv, unsigned char* rgba,
	int pixel_width, int pixel_height) {

	//nv21
	int total = pixel_width * pixel_height;
	rgba = new unsigned char[pixel_width * pixel_height * 4]();
	char Y, U, V;
	float R, G, B;
	int index = 0;

	for (int h = 0; h < pixel_height; h++) {
		for (int w = 0; w < pixel_width / 2; w++) {

			Y = yuv[h * pixel_width + w * 2];
			V = yuv[total + (h >> 1) * pixel_width + w * 2];
			U = yuv[total + (h >> 1) * pixel_width + w * 2 + 1];
			R = Y + 1.4075 * (V - 128);
			G = Y - 0.3455 * (U - 128) - 0.7169 * (V - 128);
			B = Y + 1.779 * (U - 128);

			if (R < 0) R = 0;
			if (R > 255) R = 255;
			if (G < 0) G = 0;
			if (G > 255) G = 255;
			if (B < 0) B = 0;
			if (B > 255) B = 255;

			rgba[index++] = B;
			rgba[index++] = G;
			rgba[index++] = R;
			rgba[index++] = 255;

			Y = yuv[h * pixel_width + w * 2 + 1];
			R = Y + 1.4075 * (V - 128);
			G = Y - 0.3455 * (U - 128) - 0.7169 * (V - 128);
			B = Y + 1.779 * (U - 128);

			if (R < 0) R = 0;
			if (R > 255) R = 255;
			if (G < 0) G = 0;
			if (G > 255) G = 255;
			if (B < 0) B = 0;
			if (B > 255) B = 255;

			rgba[index++] = B;
			rgba[index++] = G;
			rgba[index++] = R;
			rgba[index++] = 255;
		}
	}
}



bool ImagePixelFormatToRGBA(unsigned char* pSrc, unsigned char* pDst, unsigned int pixel_width, unsigned int pixel_height, enum ImagePixelFormat type) {
	if (type == RGBA) {
		pDst = pSrc;
		return true;
	}
	else if (type == BGRA) {
		BGRAToRGBA(pSrc, pDst, pixel_width, pixel_height);
		return true;
	}
	else if (type == ABGR) {
		ABGRToRGBA(pSrc, pDst, pixel_width, pixel_height);
		return true;
	}
	else if (type == ARGB) {
		ARGBToRGBA(pSrc, pDst, pixel_width, pixel_height);
		return true;
	}
	else if (type == I420) {
		I420ToRGBA(pSrc, pDst, pixel_width, pixel_height);
		return true;
	}
	else if (type == YV12) {
		YV12ToRGBA(pSrc, pDst, pixel_width, pixel_height);
		return true;
	}
	else if (type == NV12) {
		NV12ToRGBA(pSrc, pDst, pixel_width, pixel_height);
		return true;
	}
	else if (type == NV21) {
		NV21ToRGBA(pSrc, pDst, pixel_width, pixel_height);
		return true;
	}
	else {
		printf("ImagePixelFormat error ,exit...\n");
		return false;
	}

}
