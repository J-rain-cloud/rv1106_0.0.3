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

#ifndef __ROCKIVA_FACE_API_H__
#define __ROCKIVA_FACE_API_H__

#include "rockiva_common.h"

#ifdef  __cplusplus
extern "C"{
#endif

/* ------------------------------------------------------------------ */

#define ROCKIVA_FACE_MAX_FACE_NUM            (40)                       /* 最大人脸数目 */
#define ROCKIVA_AREA_POINT_NUM_MAX           (6)                        /* 最大区域点数 */
#define ROCKIVA_FACE_FORBIDDEN_AREA          (16)                       /* 最大支持的屏蔽检测区域 */
#define ROCKIVA_FACE_FEATURE_SIZE_MAX        (4096)                     /* 特征值空间大小 */
#define ROCKIVA_FACE_MODEL_VERSION           (64)                       /* 模型版本号字符串长度 */
#define ROCKIVA_FACE_INFO_SIZE_MAX           (32)                       /* 人脸入库信息字符串长度(用户填入) */
#define ROCKIVA_FACE_ID_MAX_NUM              (100)                      /* 特征比对结果的TOP数目（最大）*/

/* ---------------------------类型定义----------------------------------- */

/* 人脸抓拍类型 */
typedef enum {
    ROCKIVA_FACE_CAP_NONE = 0x0000,             /* 不抓拍 */
    ROCKIVA_FACE_CAP_AUTO = 0x0001,             /* 智能抓拍 */
    ROCKIVA_FACE_CAP_FORCE = 0x0010,            /* 触发抓拍 --前端特殊需求 */
    ROCKIVA_FACE_CAP_ALL = 0x0011               /* 1，2同时开启 */
} RockIvaFaceCaptureType;

/* 人脸优选类型 */
typedef enum {
    ROCKIVA_FACE_OPT_BEST,                      /* 效果优先模式 目标从出现到消失的最优人脸 */
    ROCKIVA_FACE_OPT_FAST,                      /* 快速优先模式 目标从出现的一个时间段内的最优人脸 */
    ROCKIVA_FACE_OPT_CYCLE,                     /* 周期优选模式 目标在固定周期时间内的最优人脸 */
} RockIvaFaceOptType;

/* 人脸业务类型 */
typedef enum {
    ROCKIVA_FACE_MODE_NORMAL   = 0,             /* 正常模式(根据RockIvaWorkMode配置) */
    ROCKIVA_FACE_MODE_IMPORT  = 1,              /* 导库模式(底图特征提取) */
    ROCKIVA_FACE_MODE_SEARCH  = 2,              /* 以图搜图模式 */
} RockIvaFaceWorkMode;

/* 目标状态 */
typedef enum {
    ROCKIVA_FACE_OBJ_STATE_FIRST,               /* 目标第一次出现*/
    ROCKIVA_FACE_OBJ_STATE_TRACKING,            /* 目标跟踪过程中 */
    ROCKIVA_FACE_OBJ_STATE_LAST                 /* 目标最后一次出现*/
} RockIvaFaceObjectStatus;

/* 性别 */
typedef enum {
    ROCKIVA_GENDER_TYPE_UNKNOWN   = 0,          /* 未知 */
    ROCKIVA_GENDER_TYPE_MALE      = 1,          /* 男性 */
    ROCKIVA_GENDER_TYPE_FEMALE    = 2           /* 女性 */
} RockIvaFaceGenderType;

/* 年龄 */
typedef enum {
    ROCKIVA_AGE_TYPE_UNKNOWN      = 0,          /* 未知 */
    ROCKIVA_AGE_TYPE_CHILD        = 1,          /* 儿童 */
    ROCKIVA_AGE_TYPE_EARLYYOUTH   = 2,          /* 少年 */
    ROCKIVA_AGE_TYPE_YOUTH        = 3,          /* 青年 */
    ROCKIVA_AGE_TYPE_MIDLIFE      = 4,          /* 中年 */
    ROCKIVA_AGE_TYPE_OLD          = 5           /* 老年 */
} RockIvaFaceAgeType;

/* 情感 */
typedef enum {
    ROCKIVA_EMOTION_TYPE_UNKNOWN      = 0,      /* 未知 */
    ROCKIVA_EMOTION_TYPE_ANGRY        = 1,      /* 生气的 */
    ROCKIVA_EMOTION_TYPE_CALM         = 2,      /* 平静的 */
    ROCKIVA_EMOTION_TYPE_CONFUSED     = 3,      /* 迷茫的 */
    ROCKIVA_EMOTION_TYPE_DISGUST      = 4,      /* 厌恶的 */
    ROCKIVA_EMOTION_TYPE_HAPPY        = 5,      /* 高兴的 */
    ROCKIVA_EMOTION_TYPE_SAD          = 6,      /* 悲伤的 */
    ROCKIVA_EMOTION_TYPE_SCARED       = 7,      /* 害怕的 */
    ROCKIVA_EMOTION_TYPE_SURPRISED    = 8,      /* 吃惊的 */
    ROCKIVA_EMOTION_TYPE_SQUINT       = 9,      /* 眯眼的 */
    ROCKIVA_EMOTION_TYPE_SCREAM       = 10,     /* 尖叫的 */
    ROCKIVA_EMOTION_TYPE_OTHER        = 11      /* 其他 */
} RockIvaFaceEmotionType;

/* 眼镜 */
typedef enum {
    ROCKIVA_GLASSES_TYPE_UNKNOWN         = 0,   /* 未知 */
    ROCKIVA_GLASSES_TYPE_NOGLASSES       = 1,   /* 不戴眼镜 */
    ROCKIVA_GLASSES_TYPE_GLASSES         = 2,   /* 戴眼镜 */
    ROCKIVA_GLASSES_TYPE_SUNGLASSES      = 3    /* 太阳眼镜 （预留）*/
} RockIvaFaceGlassesType;

/* 是否微笑 */
typedef enum {
    ROCKIVA_SMILE_TYPE_UNKNOWN      = 0,        /* 未知 */
    ROCKIVA_SMILE_TYPE_YES          = 1,        /* 微笑 */
    ROCKIVA_SMILE_TYPE_NO           = 2         /* 不微笑 */
} RockIvaFaceSmileType;

/* 是否戴口罩 */
typedef enum {
    ROCKIVA_MASK_TYPE_UNKNOWN      = 0,         /* 未知 */
    ROCKIVA_MASK_TYPE_YES          = 1,         /* 戴口罩 */
    ROCKIVA_MASK_TYPE_NO           = 2          /* 不戴口罩 */
} RockIvaFaceMaskType;

/* 是否有胡子 */
typedef enum {
    ROCKIVA_BEARD_TYPE_UNKNOWN      = 0,        /* 未知 */
    ROCKIVA_BEARD_TYPE_YES          = 1,        /* 有胡子 */
    ROCKIVA_BEARD_TYPE_NO           = 2         /* 没有胡子 */
} RockIvaFaceBeardType;

/* 抓拍类型 */
typedef enum {
    ROCKIVA_FACE_CAP_LAST,                       /* 目标消失抓拍帧 */
    ROCKIVA_FACE_CAP_CYCLE,                      /* 周期抓拍帧 */
} RockIvaFaceCapFrameType;

/* ---------------------------规则配置----------------------------------- */

/* 算法业务类型 */
typedef struct {
    uint8_t faceCaptureEnable;                  /* 人脸抓拍业务 1：有效 */
    uint8_t faceRecognizeEnable;                /* 人脸识别业务 1：有效 */
    uint8_t faceAttributeEnable;                /* 人脸属性分析业务 1:有效 */
    uint8_t relatedPersonEnable;                /* 是否关联人体 1：有效 */
} RockIvaFaceTaskType;

/* 人脸SDK处理能力 */
typedef struct {
    uint32_t maxDetectNum;                      /*最大的检测个数*/
    uint32_t maxCaptureNum;                     /*最大的抓拍个数*/
    uint32_t maxRecogNum;                       /*最大的识别个数*/
} RockIvaFaceCapacity;

/* 人脸抓拍规则设置 */
typedef struct {
    RockIvaFaceCaptureType captureMode;           /* 抓拍模式 */
    uint8_t sensitivity;                          /* 检测灵敏度[1,100] */
    uint8_t passCountFlag;                        /* 过人计数开关[0关 1开] */
    uint8_t fullScreen;                           /* 是否全屏检测[0关 1开] */
    RockIvaArea detectArea;                       /* 检测区域,非全屏时生效 */
    uint8_t forbiddenEn;                          /* 是否屏蔽区域检测[0关 1开] */
    uint32_t forbiddenAreaNum;                    /* 屏蔽区域数目 */
    RockIvaArea forbiddenDetectArea[ROCKIVA_FACE_FORBIDDEN_AREA];  /* 屏蔽检测区域 */
    uint32_t minPupilDis;                         /* 界面设置的最小瞳距值，小于该值过滤 */
    RockIvaFaceOptType optType;                   /* 人脸优选类型 */
    uint32_t optBestNum;                          /* ROCKIVA_FACE_OPT_BEST：人脸优选张数 范围：1-3 */
    uint32_t optCycleValue;                       /* ROCKIVA_FACE_OPT_CYCLE：人脸优选周期优选值 ms */
    uint32_t optFastTime;                         /* ROCKIVA_FACE_OPT_FAST：人脸优选快速模式下的时间设置 */
    uint8_t captureImageFlag;                     /* 在RockIvaFaceCapResult中返回人脸小图，开关[0关 1开] */
    RockIvaRectExpandRatio captureExpand;         /* 抓拍时扩展人脸框上下左右的比例大小配置 */
    uint32_t alignWidth;                          /* 抓拍图像的对齐宽度 */
    RockIvaFaceCapacity faceCapacity;             /* 人脸最大检测、抓拍和识别个数配置，目前只实现设置最大抓拍个数，0[不限制] */
} RockIvaFaceRule;

/* 人脸分析业务初始化参数配置 */
typedef struct {
    RockIvaFaceWorkMode mode;                     /* 人脸任务模式 */
    RockIvaFaceRule faceCaptureRule;              /* 人脸抓拍规则 */
    RockIvaFaceTaskType faceTaskType;             /* 人脸业务类型：人脸抓拍业务/人脸识别业务 */
} RockIvaFaceTaskParams;

/* ------------------------------------------------------------------ */

/* -------------------------- 算法处理结果 --------------------------- */

/* 人脸属性结构体 */
typedef struct {
    RockIvaFaceGenderType gender;         /* 性别 */
    RockIvaFaceAgeType age;               /* 年龄 */
    RockIvaFaceEmotionType emotion;       /* 情感 */
    RockIvaFaceGlassesType eyeGlass;      /* 眼镜 */
    RockIvaFaceSmileType smile;           /* 笑容 */
    RockIvaFaceMaskType mask;             /* 口罩 */
    RockIvaFaceBeardType beard;           /* 胡子 */
    uint32_t attractive;                  /* 颜值 */
} RockIvaFaceAttribute;

/* 人脸角度信息 */
typedef struct {
    int16_t pitch;             /* 俯仰角,表示绕x轴旋转角度 */
    int16_t yaw;               /* 偏航角,表示绕y轴旋转角度 */
    int16_t roll;              /* 翻滚角,表示绕z轴旋转角度 */
} RockIvaAngle;

/* 人脸质量信息 */
typedef struct {
    uint16_t score;             /* 人脸质量分数(值范围0~100) */
    uint16_t clarity;           /* 人脸清晰度(值范围0~100, 100表示最清晰) */
    RockIvaAngle angle;         /* 人脸角度 */
} RockIvaFaceQualityInfo;

/* 单个目标人脸检测基本信息 */
typedef struct {
    uint32_t objId;                                       /* 目标ID[0,2^32) */
    uint32_t frameId;                                     /* 人脸所在帧序号 */
    RockIvaRectangle faceRect;                            /* 人脸区域原始位置 */
    RockIvaFaceQualityInfo faceQuality;                   /* 人脸质量信息 */
    RockIvaFaceObjectStatus faceObjState;                 /* 人脸目标状态 */
    RockIvaObjectInfo person;                             /* 关联的人体检测信息 */
} RockIvaFaceInfo;

/* 单个目标人脸分析信息 */
typedef struct {
    uint32_t featureSize;                                 /* 人脸特征长度,单位字节 */
    char feature[ROCKIVA_FACE_FEATURE_SIZE_MAX];          /* 人脸特征数据 */
    RockIvaFaceAttribute faceAttr;                        /* 人脸属性 */
} RockIvaFaceAnalyseInfo;

/* 人脸检测处理结果 */
typedef struct {
    uint32_t frameId;                                        /* 帧ID */
    uint32_t channelId;                                      /* 通道号 */
    uint32_t objNum;                                         /* 人脸个数 */
    RockIvaFaceInfo faceInfo[ROCKIVA_FACE_MAX_FACE_NUM];     /* 各目标检测信息 */
} RockIvaFaceDetResult;

/* 人脸抓拍处理结果 */
typedef struct {
    uint32_t channelId;                                      /* 通道号 */
    uint32_t frameId;                                        /* 帧ID */
    RockIvaFaceCapFrameType faceCapFrameType;                /* 抓拍帧类型 */
    RockIvaFaceInfo faceInfo;                                /* 人脸基本检测信息 */
    RockIvaFaceAnalyseInfo faceAnalyseInfo;                  /* 人脸分析信息 */
    RockIvaImage captureImage;                               /* 人脸抓拍小图 */
} RockIvaFaceCapResult;

/* 入库特征对应的详细信息，用户输入 */
typedef struct {
    char faceIdInfo[ROCKIVA_FACE_INFO_SIZE_MAX];
} RockIvaFaceIdInfo;

/* 特征更新类型 */
typedef enum {
    ROCKIVA_FACE_FEATURE_INSERT = 0,          /* 添加特征 */
    ROCKIVA_FACE_FEATURE_DELETE = 1,          /* 删除特征 */
    ROCKIVA_FACE_FEATURE_UPDATE = 2,          /* 更新特征 */
    ROCKIVA_FACE_FEATURE_RETRIEVAL = 3,       /* 查找标签 */
    ROCKIVA_FACE_FEATURE_CLEAR = 4,           /* 清除库信息 */
} RockIvaFaceLibraryAction;

/* 特征比对返回结果 */
typedef struct {
    char faceIdInfo[ROCKIVA_FACE_INFO_SIZE_MAX];     /* 人脸详细信息 */
    float score;                                       /* 比对分数 */
} RockIvaFaceSearchResult;

/* 特征比对返回结果列表 */
typedef struct {
    RockIvaFaceSearchResult faceIdScore[ROCKIVA_FACE_ID_MAX_NUM];
    int num;
} RockIvaFaceSearchResults;

/* ---------------------------------------------------------------- */

/**
 * @brief 检测结果回调函数
 * 
 * result 结果
 * status 状态码
 * userData 用户自定义数据
 */
typedef void(*ROCKIVA_FACE_DetResultCallback)(const RockIvaFaceDetResult *result, const RockIvaExecuteStatus status,
                                        void *userData);

/**
 * @brief 抓拍和人脸分析结果回调函数
 * 
 * result 结果
 * status 状态码
 * userData 用户自定义数据
 */
typedef void(*ROCKIVA_FACE_AnalyseResultCallback)(const RockIvaFaceCapResult *result, const RockIvaExecuteStatus status,
                                        void *userData);

typedef struct {
    ROCKIVA_FACE_DetResultCallback detCallback;
    ROCKIVA_FACE_AnalyseResultCallback analyseCallback;
} RockIvaFaceCallback;

/**
 * @brief 初始化
 * 
 * @param handle [INOUT] 初始化完成的handle
 * @param initParams [IN] 初始化参数
 * @param resultCallback [IN] 回调函数
 * @return RockIvaRetCode 
 */
RockIvaRetCode ROCKIVA_FACE_Init(RockIvaHandle handle,
                                const RockIvaFaceTaskParams *initParams,
                                const RockIvaFaceCallback callback);

/**
 * @brief 运行时重新配置(重新配置会导致内部的一些记录清空复位，但是模型不会重新初始化)
 * 
 * @param handle [IN] handle
 * @param initParams [IN] 配置参数
 * @return RockIvaRetCode 
 */
RockIvaRetCode ROCKIVA_FACE_Reset(RockIvaHandle handle, const RockIvaFaceTaskParams* params);

/**
 * @brief 销毁
 * 
 * @param handle [IN] handle
 * @return RockIvaRetCode 
 */
RockIvaRetCode ROCKIVA_FACE_Release(RockIvaHandle handle);

/**
 * @brief 1:1人脸特征比对接口
 * 
 * @param feature1 [IN] 人脸特征1
 * @param feature2 [IN] 人脸特征2
 * @param score [OUT] 人脸1:1比对相似度(范围0-1.0)
 * @return RockIvaRetCode
 */
RockIvaRetCode ROCKIVA_FACE_FeatureCompare(const void* feature1, const void* feature2, float* score);

/**
 * @brief 人脸特征布控接口,用于对某个人脸库进行增、删、改
 * 
 * @param libName [IN] 人脸库名称
 * @param action [IN] 人脸库操作类型
 * @param faceIdInfo [IN] 人脸ID
 * @param faceIdNum [IN] 人脸ID数量
 * @param featureData [IN] 人脸特征数据
 * @return RockIvaRetCode
 */
RockIvaRetCode ROCKIVA_FACE_FeatureLibraryControl(const char* libName, RockIvaFaceLibraryAction action,
                                                  RockIvaFaceIdInfo* faceIdInfo, uint32_t faceIdNum,
                                                  const void* featureData, int featureSize);

/**
 * @brief 人脸特征库检索接口,用于对某个人脸库的特征进行检索
 * 
 * @param libName [IN] 人脸库名称
 * @param featureData [IN] 人脸特征
 * @param num [IN] 比对特征的个数
 * @param topK [IN] 前K个最相似的特征值
 * @param results [OUT] 比对结果
 * @return RockIvaRetCode 
 */
RockIvaRetCode ROCKIVA_FACE_SearchFeature(const char* libName, const void* featureData, int featureSize, uint32_t num, int32_t topK,
                                          RockIvaFaceSearchResults* results);

#ifdef __cplusplus
}
#endif /* end of __cplusplus */


#endif /* end of #ifndef __ROCKIVA_FACE_API_H__ */