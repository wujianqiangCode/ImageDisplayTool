#pragma once
# ifndef IMAGEPIXELFORMATTORGBA_H
# define IMAGEPIXELFORMATTORGBA_H

#include "ImageDisplayTool.h"


bool ImagePixelFormatToRGBA(unsigned char* pSrc, unsigned char* pDst, unsigned int pixel_width, unsigned int pixel_height, enum ImagePixelFormat type);

#endif