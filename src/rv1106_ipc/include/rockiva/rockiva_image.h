/****************************************************************************
*
*    Copyright (c) 2021 by Rockchip Corp.  All rights reserved.
*
*    The material in this file is confidential and contains trade secrets
*    of Rockchip Corporation. This is proprietary information owned by
*    Rockchip Corporation. No part of this work may be disclosed,
*    reproduced, copied, transmitted, or used in any way for any purpose,
*    without the express written permission of Rockchip Corporation.
*
*****************************************************************************/

#ifndef __ROCKIVA_IMAGE_H__
#define __ROCKIVA_IMAGE_H__

#include "rockiva_common.h"

#ifdef  __cplusplus
extern "C"{
#endif

/**
 * @brief 图像裁剪
 * 
 * @param srcImg [IN] 原图像
 * @param rect [IN] 裁剪区域
 * @param alignSize [IN] 裁剪图像对齐
 * @param cropImg [OUT] 裁剪图像
 * @return RockIvaRetCode 执行结果
 */
RockIvaRetCode ROCKIVA_IMAGE_Crop(const RockIvaImage *srcImg, const RockIvaRectangle *rect, int alignSize, RockIvaImage *cropImg, RockIvaRectExpandRatio *expand);

/**
 * @brief 图像拷贝(目前只能拷贝虚拟地址内存的图像数据,目标图像用完后需要释放)
 * 
 * @param srcImg [IN] 原图像
 * @param dstImg [OUT] 拷贝图像
 * @return RockIvaRetCode 执行结果
 */
RockIvaRetCode ROCKIVA_IMAGE_Clone(const RockIvaImage *srcImg, RockIvaImage *dstImg);

/**
 * @brief 释放图像(只能释放虚拟地址内存的图像数据,DMA buffer的不能释放)
 * 
 * @param srcImg [IN] 原图像
 * @return RockIvaRetCode 执行结果
 */
RockIvaRetCode ROCKIVA_IMAGE_Release(const RockIvaImage *img);

/**
 * @brief 获取图像大小
 * 
 * @param srcImg [IN] 原图像
 * @return int 执行结果
 */
int ROCKIVA_IMAGE_Get_Size(const RockIvaImage *srcImg);

/**
 * @brief 按设定比例缩放矩形框,缩放后的目标框宽高=原宽高*ratio
 * 
 * @param srcRect [IN] 原矩形框(坐标值范围0~9999)
 * @param ratio [IN] 缩放比例(>0)
 * @return RockIvaRectangle 缩放后的矩形框(坐标值范围0~9999)
 */
RockIvaRectangle ROCKIVA_RECT_Scaling(const RockIvaRectangle *srcRect, float ratio);

#ifdef  __cplusplus
}
#endif /* end of __cplusplus */

#endif /* end of #ifndef __ROCKIVA_IMAGE_H__ */
