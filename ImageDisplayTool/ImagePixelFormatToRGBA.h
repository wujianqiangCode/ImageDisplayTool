/*****************************************************************************
*  ImageDisplayTool
*  Copyright (C) 2023 ijianqiangwu@outlook.com
*
*  @file     ImagePixelFormatToRGBA.h
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
# ifndef IMAGEPIXELFORMATTORGBA_H
# define IMAGEPIXELFORMATTORGBA_H

#include "ImageDisplayTool.h"


bool ImagePixelFormatToRGBA(IMAGE image, unsigned char** pDst);

#endif