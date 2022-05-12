/*
 * Copyright 2022 Rockchip Electronics Co. LTD
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef INCLUDE_RT_MPI_RK_COMM_IVS_H_

#define INCLUDE_RT_MPI_RK_COMM_IVS_H_
#include "rk_type.h"
#include "rk_common.h"
#include "rk_errno.h"
#include "rk_comm_video.h"
#include "rk_comm_mb.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

#define IVS_MAX_AREA_NUM 16
#define IVS_MAX_AREA_POINT_NUM 6

typedef enum rkIVS_MODE_E {
    IVS_MODE_MD = 1 << 0,
    IVS_MODE_OD = 1 << 1,
    IVS_MODE_MD_OD = IVS_MODE_MD | IVS_MODE_OD,
    IVS_MODE_BUTT
} IVS_MODE_E;

typedef struct rkIVS_AREA_S {
    RK_U32 u32PointNum;                               /* 点个数 */
    POINT_S points[IVS_MAX_AREA_POINT_NUM]; /* 围成区域的所有点坐标 */
} IVS_AREA_S;

typedef struct rkIVS_AREAS_S {
    RK_U32 u32AreaNum;
    IVS_AREA_S areas[IVS_MAX_AREA_NUM];
} IVS_AREAS_S;

typedef struct rkIVS_DET_ATTR_S {
    IVS_AREAS_S stDetArea;
} IVS_DET_ATTR_S;

typedef struct rkIVS_CHN_ATTR_S {
    IVS_MODE_E enMode;
    RK_U32 u32PicWidth;
    RK_U32 u32PicHeight;
    PIXEL_FORMAT_E enPixelFormat;
    ROTATION_E enRotation;
    MIRROR_E enMirror;
    RK_BOOL bTraceClose;
    RK_S32  s32Gop;
    RK_BOOL bSmearEnable;
    RK_BOOL bWeightpEnable;
    RK_BOOL bMDEnable;
    RK_S32  s32MDInterval;
    RK_BOOL bMDNightMode;
    RK_BOOL bODEnable;
    RK_S32  s32ODInterval;
    RK_S32  s32ODPercent; // [5, 8]

    union {
        IVS_DET_ATTR_S stDetAttr;
    };
} IVS_CHN_ATTR_S;

typedef struct rkIVS_MD_INFO_S {
    RK_U32 frameId;          /* 所在帧序号 */
    RECT_S stRect;           /* 目标区域框 (万分比) */
    RK_CHAR *pData;
    RK_U32 u32Size;
    RK_S32 s32Fd;
} IVS_MD_INFO_S;

typedef struct rkIVS_OD_INFO_S {
    RK_U32 frameId;          /* 所在帧序号 */
    RK_U32 u32Flag;
    RK_U32 u32PixSum;
} IVS_OD_INFO_S;

typedef struct rkIVS_RESULT_S {
    IVS_MD_INFO_S stMdInfo;
    IVS_OD_INFO_S stOdInfo;
} IVS_RESULT_S;

typedef struct rkIVS_RESULT_INFO_S {
    RK_S32 s32ResultNum;
    IVS_RESULT_S *pstResults;
} IVS_RESULT_INFO_S;

/*********************************************************************************************/
/* invlalid channel ID */
#define RK_ERR_IVS_INVALID_CHNID RK_DEF_ERR(RK_ID_IVS, RK_ERR_LEVEL_ERROR, RK_ERR_INVALID_CHNID)
/* at lease one parameter is illagal ,eg, an illegal enumeration value  */
#define RK_ERR_IVS_ILLEGAL_PARAM RK_DEF_ERR(RK_ID_IVS, RK_ERR_LEVEL_ERROR, RK_ERR_ILLEGAL_PARAM)
/* channel exists */
#define RK_ERR_IVS_EXIST         RK_DEF_ERR(RK_ID_IVS, RK_ERR_LEVEL_ERROR, RK_ERR_EXIST)
/* using a NULL point */
#define RK_ERR_IVS_NULL_PTR      RK_DEF_ERR(RK_ID_IVS, RK_ERR_LEVEL_ERROR, RK_ERR_NULL_PTR)
/* try to enable or initialize system,device or channel, before configing attribute */
#define RK_ERR_IVS_NOT_CONFIG    RK_DEF_ERR(RK_ID_IVS, RK_ERR_LEVEL_ERROR, RK_ERR_NOT_CONFIG)
/* operation is not supported by NOW */
#define RK_ERR_IVS_NOT_SUPPORT   RK_DEF_ERR(RK_ID_IVS, RK_ERR_LEVEL_ERROR, RK_ERR_NOT_SUPPORT)
/* operation is not permitted ,eg, try to change stati attribute */
#define RK_ERR_IVS_NOT_PERM      RK_DEF_ERR(RK_ID_IVS, RK_ERR_LEVEL_ERROR, RK_ERR_NOT_PERM)
/* the channle is not existed  */
#define RK_ERR_IVS_UNEXIST       RK_DEF_ERR(RK_ID_IVS, RK_ERR_LEVEL_ERROR, RK_ERR_UNEXIST)
/* failure caused by malloc memory */
#define RK_ERR_IVS_NOMEM         RK_DEF_ERR(RK_ID_IVS, RK_ERR_LEVEL_ERROR, RK_ERR_NOMEM)
/* failure caused by malloc buffer */
#define RK_ERR_IVS_NOBUF         RK_DEF_ERR(RK_ID_IVS, RK_ERR_LEVEL_ERROR, RK_ERR_NOBUF)
/* no data in buffer */
#define RK_ERR_IVS_BUF_EMPTY     RK_DEF_ERR(RK_ID_IVS, RK_ERR_LEVEL_ERROR, RK_ERR_BUF_EMPTY)
/* no buffer for new data */
#define RK_ERR_IVS_BUF_FULL      RK_DEF_ERR(RK_ID_IVS, RK_ERR_LEVEL_ERROR, RK_ERR_BUF_FULL)
/* system is not ready,had not initialed or loaded */
#define RK_ERR_IVS_SYS_NOTREADY  RK_DEF_ERR(RK_ID_IVS, RK_ERR_LEVEL_ERROR, RK_ERR_NOTREADY)
/* system busy */
#define RK_ERR_IVS_BUSY          RK_DEF_ERR(RK_ID_IVS, RK_ERR_LEVEL_ERROR, RK_ERR_BUSY)
/* bad address,  eg. used for copy_from_user & copy_to_user   */
#define RK_ERR_IVS_BADADDR       RK_DEF_ERR(RK_ID_IVS, RK_ERR_LEVEL_ERROR, RK_ERR_BADADDR)

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif /* End of #ifndef  INCLUDE_RT_MPI_RK_COMM_IVS_H_ */


