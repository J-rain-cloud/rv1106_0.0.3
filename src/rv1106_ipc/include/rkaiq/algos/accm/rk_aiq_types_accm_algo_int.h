/*
 * rk_aiq_types_accm_int.h
 *
 *  Copyright (c) 2019 Rockchip Corporation
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

#ifndef _RK_AIQ_TYPES_ACCM_ALGO_INT_H_
#define _RK_AIQ_TYPES_ACCM_ALGO_INT_H_
#include "RkAiqCalibDbTypes.h"
#include "ccm_head.h"
#include "accm/rk_aiq_types_accm_algo.h"

RKAIQ_BEGIN_DECLARE

#define RK_AIQ_ACCM_COLOR_GAIN_NUM 4

typedef struct accm_sw_info_s {
    float sensorGain;
    float awbGain[2];
    float awbIIRDampCoef;
    float varianceLuma;
    bool grayMode;
    bool awbConverged;
    int prepare_type;
    bool ccmConverged;
} accm_sw_info_t;

typedef struct rk_aiq_ccm_mccm_attrib_s {
    // M4_ARRAY_DESC("ccMatrix", "f32", M4_SIZE(3,3), M4_RANGE(-8,7.992), "[1,0,0,0,1,0,0,0,1]", M4_DIGIT(4), M4_DYNAMIC(0))
    float  ccMatrix[9];
    // M4_ARRAY_DESC("ccOffsets", "f32", M4_SIZE(1,3), M4_RANGE(-4095,4095), "0", M4_DIGIT(1), M4_DYNAMIC(0))
    float  ccOffsets[3];
    // M4_ARRAY_DESC("y_alpha_curve", "f32", M4_SIZE(1,17), M4_RANGE(-4095,4095), "1024", M4_DIGIT(0), M4_DYNAMIC(0))
    float  y_alpha_curve[CCM_CURVE_DOT_NUM];
    // M4_NUMBER_DESC("bound pos bit", "f32", M4_RANGE(4, 10), "8", M4_DIGIT(0))
    float low_bound_pos_bit;
} rk_aiq_ccm_mccm_attrib_t;

typedef struct rk_aiq_ccm_mccm_attrib_v2_s {
    // M4_ARRAY_DESC("ccMatrix", "f32", M4_SIZE(3,3), M4_RANGE(-8,7.992), "[1,0,0,0,1,0,0,0,1]", M4_DIGIT(4), M4_DYNAMIC(0))
    float ccMatrix[9];
    // M4_ARRAY_DESC("ccOffsets", "f32", M4_SIZE(1,3), M4_RANGE(-4095,4095), "0", M4_DIGIT(1), M4_DYNAMIC(0))
    float ccOffsets[3];
    // M4_BOOL_DESC("high Y adjust enable", "1")
    bool highy_adj_en;
    // M4_BOOL_DESC("asym enable", "0")
    bool asym_enable;
    // M4_NUMBER_DESC("left bound pos bit", "f32", M4_RANGE(3, 11), "10", M4_DIGIT(0))
    float bound_pos_bit;  // low y alpha adjust
    // M4_NUMBER_DESC("right bound pos bit", "f32", M4_RANGE(3, 11), "10", M4_DIGIT(0))
    float right_pos_bit;  // high y alpha adjust
    // M4_ARRAY_DESC("y alpha curve", "f32", M4_SIZE(1,18), M4_RANGE(-4095,4095), "1024", M4_DIGIT(0), M4_DYNAMIC(0))
    float y_alpha_curve[CCM_CURVE_DOT_NUM_V2];
    // M4_NUMBER_DESC("ccm enhance enable", "u8", M4_RANGE(0, 1), "0", M4_DIGIT(0))
    unsigned short enh_adj_en;
    // M4_ARRAY_DESC("Enhance RGB2Y para", "u8", M4_SIZE(1,3), M4_RANGE(0,128), "[38 75 15]", M4_DIGIT(0),  M4_DYNAMIC(0))
    unsigned char enh_rgb2y_para[3];
    // M4_NUMBER_DESC("Enhance ratio max", "f32", M4_RANGE(0, 8), "0", M4_DIGIT(1))
    float enh_rat_max;
} rk_aiq_ccm_mccm_attrib_v2_t;

typedef struct rk_aiq_ccm_color_inhibition_s {
    float sensorGain[RK_AIQ_ACCM_COLOR_GAIN_NUM];
    float level[RK_AIQ_ACCM_COLOR_GAIN_NUM];//max value 100,default value 0
} rk_aiq_ccm_color_inhibition_t;

typedef struct rk_aiq_ccm_color_saturation_s {
    float sensorGain[RK_AIQ_ACCM_COLOR_GAIN_NUM];
    float level[RK_AIQ_ACCM_COLOR_GAIN_NUM];//max value 100, default value 100
} rk_aiq_ccm_color_saturation_t;

typedef struct rk_aiq_ccm_accm_attrib_s {
    rk_aiq_ccm_color_inhibition_t color_inhibition;
    rk_aiq_ccm_color_saturation_t color_saturation;
} rk_aiq_ccm_accm_attrib_t;

typedef enum rk_aiq_ccm_op_mode_s {
    RK_AIQ_CCM_MODE_INVALID                     = 0,        /**< initialization value */
    RK_AIQ_CCM_MODE_MANUAL                      = 1,        /**< run manual lens shading correction */
    RK_AIQ_CCM_MODE_AUTO                        = 2,        /**< run auto lens shading correction */
    RK_AIQ_CCM_MODE_MAX
} rk_aiq_ccm_op_mode_t;

typedef struct rk_aiq_ccm_attrib_s {
    rk_aiq_uapi_sync_t sync;
    bool byPass;
    // M4_ENUM_DESC("mode", "rk_aiq_ccm_op_mode_t", "RK_AIQ_CCM_MODE_AUTO");
    rk_aiq_ccm_op_mode_t mode;
    // M4_STRUCT_DESC("stManual", "normal_ui_style")
    rk_aiq_ccm_mccm_attrib_t stManual;
    rk_aiq_ccm_accm_attrib_t stAuto;
} rk_aiq_ccm_attrib_t;

typedef struct rk_aiq_ccm_v2_attrib_s {
    rk_aiq_uapi_sync_t sync;
    bool byPass;
    // M4_ENUM_DESC("mode", "rk_aiq_ccm_op_mode_t", "RK_AIQ_CCM_MODE_AUTO");
    rk_aiq_ccm_op_mode_t mode;
    // M4_STRUCT_DESC("stManual", "normal_ui_style")
    rk_aiq_ccm_mccm_attrib_v2_t stManual;
    rk_aiq_ccm_accm_attrib_t stAuto;
} rk_aiq_ccm_v2_attrib_t;

typedef struct rk_aiq_ccm_querry_info_s {
    bool ccm_en;
    // M4_ARRAY_DESC("ccMatrix", "f32", M4_SIZE(3,3), M4_RANGE(-8,7.992), "[1.0000,0.0000,0.0000,0.0000,1.0000,0.0000,0.0000,0.0000,1.0000]", M4_DIGIT(4), M4_DYNAMIC(0))
    float  ccMatrix[9];
    // M4_ARRAY_DESC("ccOffsets", "f32", M4_SIZE(1,3), M4_RANGE(-4095,4095), "0", M4_DIGIT(0), M4_DYNAMIC(0))
    float  ccOffsets[3];
    bool highy_adj_en;
    bool asym_enable;
    float y_alpha_curve[CCM_CURVE_DOT_NUM_V2];
    // M4_NUMBER_DESC("bound pos bit", "f32", M4_RANGE(3, 11), "8", M4_DIGIT(0))
    float low_bound_pos_bit;
    // M4_NUMBER_DESC("high bound pos bit", "f32", M4_RANGE(3, 11), "8", M4_DIGIT(0))
    float right_pos_bit;
    float color_inhibition_level;
    float color_saturation_level;
    // M4_NUMBER_DESC("CCM Saturation", "f32", M4_RANGE(0,200), "0", M4_DIGIT(2))
    float finalSat;
    // M4_STRING_DESC("usedCcm1", M4_SIZE(1,1), M4_RANGE(0, 25), "A_100",M4_DYNAMIC(0))
    char ccmname1[25];
    // M4_STRING_DESC("usedCcm2", M4_SIZE(1,1), M4_RANGE(0, 25), "A_100",M4_DYNAMIC(0))
    char ccmname2[25];
} rk_aiq_ccm_querry_info_t;

RKAIQ_END_DECLARE

#endif

