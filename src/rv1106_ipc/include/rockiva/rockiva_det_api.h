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

#ifndef __ROCKIVA_DET_API_H__
#define __ROCKIVA_DET_API_H__

#include "rockiva_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************/
/*                           结构体                                  */
/********************************************************************/

/* 检测业务初始化参数配置 */
typedef struct {
    uint32_t detObjectType;         /* 配置要检测的目标,例如检测人\机动车\非机动车: ROCKIVA_OBJECT_TYPE_PERSON|ROCKIVA_OBJECT_TYPE_VEHICLE|ROCKIVA_OBJECT_TYPE_NON_VEHICLE */
} RockIvaDetectTaskParams;

/* ---------------------------------------------------------------- */

/**
 * @brief 检测结果回调函数
 *
 * result 结果
 * status 状态码
 * userData 用户自定义数据
 */
typedef void (*ROCKIVA_DetectResultCallback)(const RockIvaDetectResult* result, const RockIvaExecuteStatus status,
                                             void* userdata);

/**
 * @brief 初始化
 *
 * @param handle [INOUT] 要初始化的handle
 * @param initParams [IN] 初始化参数
 * @param resultCallback [IN] 回调函数
 * @return RockIvaRetCode
 */
RockIvaRetCode ROCKIVA_DETECT_Init(RockIvaHandle handle, const RockIvaDetectTaskParams* initParams,
                               const ROCKIVA_DetectResultCallback resultCallback);

/**
 * @brief 运行时重新配置(重新配置会导致内部的一些记录清空复位，但是模型不会重新初始化)
 * 
 * @param handle [IN] handle
 * @param initParams [IN] 配置参数
 * @return RockIvaRetCode 
 */
RockIvaRetCode ROCKIVA_DETECT_Reset(RockIvaHandle handle, const RockIvaDetectTaskParams* params);

/**
 * @brief 释放
 *
 * @param handle [in] handle
 * @return RockIvaRetCode
 */
RockIvaRetCode ROCKIVA_DETECT_Release(RockIvaHandle handle);

#ifdef __cplusplus
}
#endif /* end of __cplusplus */

#endif /* end of #ifndef __ROCKIVA_DET_API_H__ */