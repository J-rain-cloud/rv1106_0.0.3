/*
 * Copyright 2020 Rockchip Electronics Co. LTD
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
#ifndef _RK_COMM_IVE_H_
#define _RK_COMM_IVE_H_

#include "rk_errno.h"
#include "rk_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

//typedef RK_S32 IVE_HANDLE;

typedef unsigned char IVE_U0Q8;
typedef unsigned short IVE_U0Q11;
typedef unsigned short IVE_U8Q2;
typedef unsigned short IVE_U9Q7;
typedef unsigned short IVE_U10Q0;
typedef short IVE_S9Q7;
typedef int IVE_S25Q7;
typedef IVE_U0Q8 ive_u0q8;
typedef IVE_U0Q11 ive_u0q11;
typedef IVE_U8Q2 ive_u8q2;
typedef IVE_U9Q7 ive_u9q7;
typedef IVE_U10Q0 ive_u10q0;
typedef IVE_S9Q7 ive_s9q7;
typedef IVE_S25Q7 ive_s25q7;

/* Type of the IVE_IMAGE_S data.*/
typedef enum rkIVE_IMAGE_TYPE_E {
    IVE_IMAGE_TYPE_U8C1 = 0x0,
    IVE_IMAGE_TYPE_S8C1 = 0x1,

    IVE_IMAGE_TYPE_YUV420SP = 0x2, /* YUV420 SemiPlanar */
    IVE_IMAGE_TYPE_YUV422SP = 0x3, /* YUV422 SemiPlanar */
    IVE_IMAGE_TYPE_YUV420P = 0x4,  /* YUV420 Planar */
    IVE_IMAGE_TYPE_YUV422P = 0x5,  /* YUV422 planar */

    IVE_IMAGE_TYPE_S8C2_PACKAGE = 0x6,
    IVE_IMAGE_TYPE_S8C2_PLANAR = 0x7,

    IVE_IMAGE_TYPE_S16C1 = 0x8,
    IVE_IMAGE_TYPE_U16C1 = 0x9,

    IVE_IMAGE_TYPE_U8C3_PACKAGE = 0xa,
    IVE_IMAGE_TYPE_U8C3_PLANAR = 0xb,

    IVE_IMAGE_TYPE_S32C1 = 0xc,
    IVE_IMAGE_TYPE_U32C1 = 0xd,

    IVE_IMAGE_TYPE_S64C1 = 0xe,
    IVE_IMAGE_TYPE_U64C1 = 0xf,

    IVE_IMAGE_TYPE_BUTT

} IVE_IMAGE_TYPE_E;

/* Definition of the IVE_IMAGE_S.*/
typedef struct rkIVE_IMAGE_S {
    RK_U64 au64PhyAddr[3];   /* RW;The physical address of the image */
    RK_U64 au64VirAddr[3];   /* RW;The virtual address of the image */
    RK_U32 au32Stride[3];    /* RW;The stride of the image */
    RK_U32 u32Width;         /* RW;The width of the image */
    RK_U32 u32Height;        /* RW;The height of the image */
    IVE_IMAGE_TYPE_E enType; /* RW;The type of the image */
} IVE_IMAGE_S;

typedef IVE_IMAGE_S IVE_SRC_IMAGE_S;
typedef IVE_IMAGE_S IVE_DST_IMAGE_S;

/*
* Definition of the IVE_MEM_INFO_S.This struct special purpose for input or ouput, such as Hist, CCL, ShiTomasi.
*/
typedef struct rkIVE_MEM_INFO_S {
    RK_U64 u64PhyAddr; /* RW;The physical address of the memory */
    RK_U64 u64VirAddr; /* RW;The virtual address of the memory */
    RK_U32 u32Size;    /* RW;The size of memory */
} IVE_MEM_INFO_S;
typedef IVE_MEM_INFO_S IVE_SRC_MEM_INFO_S;
typedef IVE_MEM_INFO_S IVE_DST_MEM_INFO_S;

/* Data struct*/
typedef struct rkIVE_DATA_S {
    RK_U64 u64PhyAddr; /* RW;The physical address of the data */
    RK_U64 u64VirAddr; /* RW;The virtaul address of the data */

    RK_U32 u32Stride; /* RW;The stride of 2D data by byte */
    RK_U32 u32Width;  /* RW;The width of 2D data by byte */
    RK_U32 u32Height; /* RW;The height of 2D data by byte */

    RK_U32 u32Reserved;
} IVE_DATA_S;
typedef IVE_DATA_S IVE_SRC_DATA_S;
typedef IVE_DATA_S IVE_DST_DATA_S;

/* Definition of RK_U16 point */
typedef struct rkIVE_POINT_U16_S {
    RK_U16 u16X; /* RW;The X coordinate of the point */
    RK_U16 u16Y; /* RW;The Y coordinate of the point */
} IVE_POINT_U16_S;

/*
* Definition of RK_S16 point
*/
typedef struct rkIVE_POINT_S16_S {
    RK_S16 s16X; /* RW;The X coordinate of the point */
    RK_S16 s16Y; /* RW;The Y coordinate of the point */
} IVE_POINT_S16_S;

typedef struct rkIVE_POINT_U32_S {
    RK_U32 u32X; /* RW;The X coordinate of the point */
    RK_U32 u32Y; /* RW;The Y coordinate of the point */
} IVE_POINT_U32_S;

typedef struct rkIVE_POINT_S32_S {
    RK_S32 s32X; /* RW;The X coordinate of the point */
    RK_S32 s32Y; /* RW;The Y coordinate of the point */
} IVE_POINT_S32_S;

typedef struct rkIVE_POINT_S25Q7_S {
    IVE_S25Q7 s25q7X; /* RW;The X coordinate of the point */
    IVE_S25Q7 s25q7Y; /* RW;The Y coordinate of the point */
} IVE_POINT_S25Q7_S;

typedef struct rkIVE_POINT_FLOAT {
    float fpX; /*X coordinate*/
    float fpY; /*Y coordinate*/
} IVE_POINT_FLOAT;

typedef struct rkIVE_MV_FLOAT {
    RK_S32 s32Statys; /*Result of tracking: 0-success; -1-failure*/
    RK_S16 fpX;       /*X coordinate*/
    RK_S16 fpY;       /*Y coordinate*/
} IVE_MV_FLOAT;

typedef struct rkIVE_MV_S16_S {
    RK_S32 s32Statys; /*Result of tracking: 0-success; -1-failure*/
    RK_S16 s16X;      /*X coordinate*/
    RK_S16 s16Y;      /*Y coordinate*/
} IVE_MV_S16_S;

typedef struct rkIVE_MV_S9Q7_S {
    RK_S32 s32Statys; /*Result of tracking: 0-success; -1-failure*/
    IVE_S9Q7 s9q7X;   /*X coordinate*/
    IVE_S9Q7 s9q7Y;   /*Y coordinate*/
} IVE_MV_S9Q7_S;

/* Definition of rectangle */
typedef struct rkIVE_RECT_U16_S {
    RK_U16 u16X;      /* RW;The location of X axis of the rectangle */
    RK_U16 u16Y;      /* RW;The location of Y axis of the rectangle */
    RK_U16 u16Width;  /* RW;The width of the rectangle */
    RK_U16 u16Height; /* RW;The height of the rectangle */
} IVE_RECT_U16_S;

typedef struct rkIVE_RECT_U32_S {
    RK_U32 u32X;      /* RW;The location of X axis of the rectangle */
    RK_U32 u32Y;      /* RW;The location of Y axis of the rectangle */
    RK_U32 u32Width;  /* RW;The width of the rectangle */
    RK_U32 u32Height; /* RW;The height of the rectangle */
} IVE_RECT_U32_S;

typedef struct rkIVE_RECT_S32_S {
    RK_S32 s32X;
    RK_S32 s32Y;
    RK_U32 u32Width;
    RK_U32 u32Height;
} IVE_RECT_S24Q8_S;

typedef struct rkIVE_LOOK_UP_TABLE_S {
    IVE_MEM_INFO_S stTable;
    RK_U16 u16ElemNum; /* RW;LUT's elements number */

    RK_U8 u8TabInPreci;
    RK_U8 u8TabOutNorm;

    RK_S32 s32TabInLower; /* RW;LUT's original input lower limit */
    RK_S32 s32TabInUpper; /* RW;LUT's original input upper limit */
} IVE_LOOK_UP_TABLE_S;

typedef enum rkEN_RK_ERR_CODE_E {
    ERR_IVE_SYS_TIMEOUT = 0x40,   /* IVE process timeout */
    ERR_IVE_QUERY_TIMEOUT = 0x41, /* IVE query timeout */
    ERR_IVE_OPEN_FILE = 0x42,     /* IVE open file error */
    ERR_IVE_READ_FILE = 0x43,     /* IVE read file error */
    ERR_IVE_WRITE_FILE = 0x44,    /* IVE write file error */
    ERR_IVE_BUS_ERR = 0x45,

    ERR_IVE_BUTT
} EN_RK_ERR_CODE_E;

typedef enum rkEN_FD_ERR_CODE_E {
    ERR_FD_SYS_TIMEOUT = 0x40,   /* FD process timeout */
    ERR_FD_CFG = 0x41,           /* FD configuration error */
    ERR_FD_FACE_NUM_OVER = 0x42, /* FD candidate face number over */
    ERR_FD_OPEN_FILE = 0x43,     /* FD open file error */
    ERR_FD_READ_FILE = 0x44,     /* FD read file error */
    ERR_FD_WRITE_FILE = 0x45,    /* FD write file error */

    ERR_FD_BUTT
} EN_FD_ERR_CODE_E;

/************************************************IVE error code ***********************************/
/* Invalid device ID */
#define RK_ERR_RVE_INVALID_DEVID RVE_DEF_ERR(RK_ID_IVE, EN_ERR_LEVEL_ERROR, EN_ERR_INVALID_DEVID)
/* Invalid channel ID */
#define RK_ERR_RVE_INVALID_CHNID RVE_DEF_ERR(RK_ID_IVE, EN_ERR_LEVEL_ERROR, EN_ERR_INVALID_CHNID)
/* At least one parameter is illegal. For example, an illegal enumeration value exists. */
#define RK_ERR_RVE_ILLEGAL_PARAM RVE_DEF_ERR(RK_ID_IVE, EN_ERR_LEVEL_ERROR, EN_ERR_ILLEGAL_PARAM)
/* The channel exists. */
#define RK_ERR_RVE_EXIST RVE_DEF_ERR(RK_ID_IVE, EN_ERR_LEVEL_ERROR, EN_ERR_EXIST)
/* The UN exists. */
#define RK_ERR_RVE_UNEXIST RVE_DEF_ERR(RK_ID_IVE, EN_ERR_LEVEL_ERROR, EN_ERR_UNEXIST)
/* A null point is used. */
#define RK_ERR_RVE_NULL_PTR RVE_DEF_ERR(RK_ID_IVE, EN_ERR_LEVEL_ERROR, EN_ERR_NULL_PTR)
/* Try to enable or initialize the system, device, or channel before configuring attributes. */
#define RK_ERR_RVE_NOT_CONFIG RVE_DEF_ERR(RK_ID_IVE, EN_ERR_LEVEL_ERROR, EN_ERR_NOT_CONFIG)
/* The operation is not supported currently. */
#define RK_ERR_RVE_NOT_SURPPORT RVE_DEF_ERR(RK_ID_IVE, EN_ERR_LEVEL_ERROR, EN_ERR_NOT_SUPPORT)
/* The operation, changing static attributes for example, is not permitted. */
#define RK_ERR_RVE_NOT_PERM RVE_DEF_ERR(RK_ID_IVE, EN_ERR_LEVEL_ERROR, EN_ERR_NOT_PERM)
/* A failure caused by the malloc memory occurs. */
#define RK_ERR_RVE_NOMEM RVE_DEF_ERR(RK_ID_IVE, EN_ERR_LEVEL_ERROR, EN_ERR_NOMEM)
/* A failure caused by the malloc buffer occurs. */
#define RK_ERR_RVE_NOBUF RVE_DEF_ERR(RK_ID_IVE, EN_ERR_LEVEL_ERROR, EN_ERR_NOBUF)
/* The buffer is empty. */
#define RK_ERR_RVE_BUF_EMPTY RVE_DEF_ERR(RK_ID_IVE, EN_ERR_LEVEL_ERROR, EN_ERR_BUF_EMPTY)
/* No buffer is provided for storing new data. */
#define RK_ERR_RVE_BUF_FULL RVE_DEF_ERR(RK_ID_IVE, EN_ERR_LEVEL_ERROR, EN_ERR_BUF_FULL)
/* The system is not ready because it may be not initialized or loaded.
 * The error code is returned when a device file fails to be opened. */
#define RK_ERR_RVE_NOTREADY RVE_DEF_ERR(RK_ID_IVE, EN_ERR_LEVEL_ERROR, EN_ERR_SYS_NOTREADY)
/* The source address or target address is incorrect during the operations such as calling 
copy_from_user or copy_to_user. */
#define RK_ERR_RVE_BADADDR RVE_DEF_ERR(RK_ID_IVE, EN_ERR_LEVEL_ERROR, EN_ERR_BADADDR)
/* The resource is busy during the operations such as destroying a VENC channel 
without deregistering it. */
#define RK_ERR_RVE_BUSY RVE_DEF_ERR(RK_ID_IVE, EN_ERR_LEVEL_ERROR, EN_ERR_BUSY)
/* IVE process timeout: 0xA01D8040 */
#define RK_ERR_RVE_SYS_TIMEOUT RVE_DEF_ERR(RK_ID_IVE, EN_ERR_LEVEL_ERROR, ERR_RVE_SYS_TIMEOUT)
/* IVE query timeout: 0xA01D8041 */
#define RK_ERR_RVE_QUERY_TIMEOUT RVE_DEF_ERR(RK_ID_IVE, EN_ERR_LEVEL_ERROR, ERR_RVE_QUERY_TIMEOUT)
/* IVE open file error: 0xA01D8042 */
#define RK_ERR_RVE_OPEN_FILE RVE_DEF_ERR(RK_ID_IVE, EN_ERR_LEVEL_ERROR, ERR_RVE_OPEN_FILE)
/* IVE read file error: 0xA01D8043 */
#define RK_ERR_RVE_READ_FILE RVE_DEF_ERR(RK_ID_IVE, EN_ERR_LEVEL_ERROR, ERR_RVE_READ_FILE)
/* IVE read file error: 0xA01D8044 */
#define RK_ERR_RVE_WRITE_FILE RVE_DEF_ERR(RK_ID_IVE, EN_ERR_LEVEL_ERROR, ERR_RVE_WRITE_FILE)
/* IVE Bus error: 0xA01D8045 */
#define RK_ERR_RVE_BUS_ERR RVE_DEF_ERR(RK_ID_IVE, EN_ERR_LEVEL_ERROR, ERR_RVE_BUS_ERR)

/************************************************FD error code ***********************************/
/* Invalid device ID */
#define RK_ERR_FD_INVALID_DEVID RVE_DEF_ERR(RK_ID_FD, EN_ERR_LEVEL_ERROR, EN_ERR_INVALID_DEVID)
/* Invalid channel ID */
#define RK_ERR_FD_INVALID_CHNID RVE_DEF_ERR(RK_ID_FD, EN_ERR_LEVEL_ERROR, EN_ERR_INVALID_CHNID)
/* At least one parameter is illegal. For example, an illegal enumeration value exists. */
#define RK_ERR_FD_ILLEGAL_PARAM RVE_DEF_ERR(RK_ID_FD, EN_ERR_LEVEL_ERROR, EN_ERR_ILLEGAL_PARAM)
/* The channel exists. */
#define RK_ERR_FD_EXIST RVE_DEF_ERR(RK_ID_FD, EN_ERR_LEVEL_ERROR, EN_ERR_EXIST)
/* The UN exists. */
#define RK_ERR_FD_UNEXIST RVE_DEF_ERR(RK_ID_FD, EN_ERR_LEVEL_ERROR, EN_ERR_UNEXIST)
/* A null point is used. */
#define RK_ERR_FD_NULL_PTR RVE_DEF_ERR(RK_ID_FD, EN_ERR_LEVEL_ERROR, EN_ERR_NULL_PTR)
/* Try to enable or initialize the system, device, or channel before configuring attributes. */
#define RK_ERR_FD_NOT_CONFIG RVE_DEF_ERR(RK_ID_FD, EN_ERR_LEVEL_ERROR, EN_ERR_NOT_CONFIG)
/* The operation is not supported currently. */
#define RK_ERR_FD_NOT_SURPPORT RVE_DEF_ERR(RK_ID_FD, EN_ERR_LEVEL_ERROR, EN_ERR_NOT_SUPPORT)
/* The operation, changing static attributes for example, is not permitted. */
#define RK_ERR_FD_NOT_PERM RVE_DEF_ERR(RK_ID_FD, EN_ERR_LEVEL_ERROR, EN_ERR_NOT_PERM)
/* A failure caused by the malloc memory occurs. */
#define RK_ERR_FD_NOMEM RVE_DEF_ERR(RK_ID_FD, EN_ERR_LEVEL_ERROR, EN_ERR_NOMEM)
/* A failure caused by the malloc buffer occurs. */
#define RK_ERR_FD_NOBUF RVE_DEF_ERR(RK_ID_FD, EN_ERR_LEVEL_ERROR, EN_ERR_NOBUF)
/* The buffer is empty. */
#define RK_ERR_FD_BUF_EMPTY RVE_DEF_ERR(RK_ID_FD, EN_ERR_LEVEL_ERROR, EN_ERR_BUF_EMPTY)
/* No buffer is provided for storing new data. */
#define RK_ERR_FD_BUF_FULL RVE_DEF_ERR(RK_ID_FD, EN_ERR_LEVEL_ERROR, EN_ERR_BUF_FULL)
/* The system is not ready because it may be not initialized or loaded.
 * The error code is returned when a device file fails to be opened. */
#define RK_ERR_FD_NOTREADY RVE_DEF_ERR(RK_ID_FD, EN_ERR_LEVEL_ERROR, EN_ERR_SYS_NOTREADY)
/* The source address or target address is incorrect during the operations such as calling 
copy_from_user or copy_to_user. */
#define RK_ERR_FD_BADADDR RVE_DEF_ERR(RK_ID_FD, EN_ERR_LEVEL_ERROR, EN_ERR_BADADDR)
/* The resource is busy during the operations such as destroying a VENC channel 
without deregistering it. */
#define RK_ERR_FD_BUSY RVE_DEF_ERR(RK_ID_FD, EN_ERR_LEVEL_ERROR, EN_ERR_BUSY)
/* FD process timeout:         0xA02F8040 */
#define RK_ERR_FD_SYS_TIMEOUT RVE_DEF_ERR(RK_ID_FD, EN_ERR_LEVEL_ERROR, ERR_FD_SYS_TIMEOUT)
/* FD configuration error:     0xA02F8041 */
#define RK_ERR_FD_CFG RVE_DEF_ERR(RK_ID_FD, EN_ERR_LEVEL_ERROR, ERR_FD_CFG)
/* FD candidate face number over: 0xA02F8042 */
#define RK_ERR_FD_FACE_NUM_OVER RVE_DEF_ERR(RK_ID_FD, EN_ERR_LEVEL_ERROR, ERR_FD_FACE_NUM_OVER)
/* FD open file error: 0xA02F8043 */
#define RK_ERR_FD_OPEN_FILE RVE_DEF_ERR(RK_ID_FD, EN_ERR_LEVEL_ERROR, ERR_FD_OPEN_FILE)
/* FD read file error: 0xA02F8044 */
#define RK_ERR_FD_READ_FILE RVE_DEF_ERR(RK_ID_FD, EN_ERR_LEVEL_ERROR, ERR_FD_READ_FILE)
/* FD read file error: 0xA02F8045 */
#define RK_ERR_FD_WRITE_FILE RVE_DEF_ERR(RK_ID_FD, EN_ERR_LEVEL_ERROR, ERR_FD_WRITE_FILE)

/************************************************ODT error code ***********************************/
/* ODT Invalid channel ID: 0xA0308002 */
#define RK_ERR_ODT_INVALID_CHNID RVE_DEF_ERR(RK_ID_ODT, EN_ERR_LEVEL_ERROR, EN_ERR_INVALID_CHNID)
/* ODT exist: 0xA0308004 */
#define RK_ERR_ODT_EXIST RVE_DEF_ERR(RK_ID_ODT, EN_ERR_LEVEL_ERROR, EN_ERR_EXIST)
/* ODT unexist: 0xA0308005 */
#define RK_ERR_ODT_UNEXIST RVE_DEF_ERR(RK_ID_ODT, EN_ERR_LEVEL_ERROR, EN_ERR_UNEXIST)
/* ODT The operation, changing static attributes for example, is not permitted: 0xA0308009 */
#define RK_ERR_ODT_NOT_PERM RVE_DEF_ERR(RK_ID_ODT, EN_ERR_LEVEL_ERROR, EN_ERR_NOT_PERM)
/* ODT the system is not ready because it may be not initialized: 0xA0308010 */
#define RK_ERR_ODT_NOTREADY RVE_DEF_ERR(RK_ID_ODT, EN_ERR_LEVEL_ERROR, EN_ERR_SYS_NOTREADY)
/* ODT busy: 0xA0308012 */
#define RK_ERR_ODT_BUSY RVE_DEF_ERR(RK_ID_ODT, EN_ERR_LEVEL_ERROR, EN_ERR_BUSY)
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
#endif /* __RVE_COMM_RVE_H__ */

