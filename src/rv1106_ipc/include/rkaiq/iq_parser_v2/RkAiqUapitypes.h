/*
 *  Copyright (c) 2021 Rockchip Corporation
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

#ifndef ___RK_AIQ_UAPITYPES_H__
#define ___RK_AIQ_UAPITYPES_H__

#include "adehaze_uapi_head.h"
#include "adrc_uapi_head.h"
#include "aec_uapi_head.h"
#include "agamma_uapi_head.h"
#include "amerge_uapi_head.h"
#include "atmo_uapi_head.h"
#include "awb_uapi_head.h"
#include "rk_aiq_user_api_common.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef struct __ae_uapi {
    // M4_STRUCT_DESC("expsw_attr", "normal_ui_style")
    uapi_expsw_attr_t expsw_attr;
    // M4_STRUCT_DESC("QueryExpInfo", "normal_ui_style")
    uapi_expinfo_t expinfo;
} ae_uapi_t;

typedef struct __awb_uapi {
    // M4_STRUCT_DESC("mode", "normal_ui_style")
    uapi_wb_mode_t mode;
    // M4_STRUCT_DESC("wbgain", "normal_ui_style")
    uapi_wb_gain_t wbgain;
} awb_uapi_t;

typedef struct __amerge_uapi {
    // M4_STRUCT_DESC("Info", "normal_ui_style")
    uapiMergeCurrCtlData_t Info;
#if defined(ISP_HW_V21)
    // M4_STRUCT_DESC("stManual", "normal_ui_style")
    mMergeAttrV10_t stManual;
#endif
#if defined(ISP_HW_V30)
    // M4_STRUCT_DESC("stManual", "normal_ui_style")
    mMergeAttrV11_t stManual;
#endif
#if defined(ISP_HW_V32)
    // M4_STRUCT_DESC("stManual", "normal_ui_style")
    mMergeAttrV12_t stManual;
#endif
} amerge_uapi_t;

typedef struct __atmo_uapi {
    // M4_STRUCT_DESC("ctldata", "normal_ui_style")
    uapiTmoCurrCtlData_t ctldata;
} atmo_uapi_t;

typedef struct __adrc_uapi {
#if defined(ISP_HW_V21)
    // M4_STRUCT_DESC("Info", "normal_ui_style")
    DrcInfoV10_t Info;
    // M4_STRUCT_DESC("stManual", "normal_ui_style")
    mdrcAttr_V10_t stManual;
#endif
#if defined(ISP_HW_V30)
    // M4_STRUCT_DESC("Info", "normal_ui_style")
    DrcInfoV11_t Info;
    // M4_STRUCT_DESC("stManual", "normal_ui_style")
    mdrcAttr_V11_t stManual;
#endif
#if defined(ISP_HW_V32)
    // M4_STRUCT_DESC("Info", "normal_ui_style")
    DrcInfoV12_t Info;
    // M4_STRUCT_DESC("stManual", "normal_ui_style")
    mdrcAttr_V12_t stManual;
#endif
} adrc_uapi_t;

typedef struct __agamma_uapi {
#if defined(ISP_HW_V20) || defined(ISP_HW_V21)
    // M4_STRUCT_DESC("stManual", "normal_ui_style")
    AgammaApiManualV10_t stManual;
#else
    // M4_STRUCT_DESC("stManual", "normal_ui_style")
    AgammaApiManualV11_t stManual;
#endif
} agamma_uapi_t;

typedef struct __adehaze_uapi {
    // M4_STRUCT_DESC("Info", "normal_ui_style")
    mDehazeAttrInfoV11_t Info;
#if defined(ISP_HW_V21) || defined(ISP_HW_V30)
    // M4_STRUCT_DESC("stManual", "normal_ui_style")
    mDehazeAttrV11_t stManual;
#endif
#if defined(ISP_HW_V32)
    // M4_STRUCT_DESC("stManual", "normal_ui_style")
    mDehazeAttrV12_t stManual;
#endif
} adehaze_uapi_t;

typedef struct __aiq_scene {
    // M4_STRING_DESC("main_scene", M4_SIZE(1,1), M4_RANGE(0, 32), "normal", M4_DYNAMIC(0))
    char* main_scene;
    // M4_STRING_DESC("sub_scene", M4_SIZE(1,1), M4_RANGE(0, 32), "day", M4_DYNAMIC(0))
    char* sub_scene;
} aiq_scene_t;

typedef struct __work_mode {
    // M4_ENUM_DESC("mode", "rk_aiq_working_mode_t", "RK_AIQ_WORKING_MODE_NORMAL");
    rk_aiq_working_mode_t mode;
} work_mode_t;

typedef struct __aiq_sysctl_desc {
    // M4_STRUCT_DESC("scene", "normal_ui_style")
    aiq_scene_t scene;
    // M4_STRUCT_DESC("work_mode", "normal_ui_style")
    work_mode_t work_mode;
} RkaiqSysCtl_t;

#if ISP_HW_V21
typedef struct __aiq_measure_info {
    // M4_STRUCT_DESC("ae_hwstats", "normal_ui_style")
    uapi_ae_hwstats_t ae_hwstats;
    // M4_STRUCT_DESC("wb_log", "normal_ui_style")
    uapi_wbV21_log_t wb_log;
} aiq_measure_info_t;
#elif ISP_HW_V30
typedef struct __aiq_measure_info {
    // M4_STRUCT_DESC("ae_hwstats", "normal_ui_style")
    uapi_ae_hwstats_t ae_hwstats;
    // M4_STRUCT_DESC("wb_log", "normal_ui_style")
    uapi_wbV30_log_t wb_log;
} aiq_measure_info_t;

#elif ISP_HW_V32
typedef struct __aiq_measure_info {
    // M4_STRUCT_DESC("ae_hwstats", "normal_ui_style")
    uapi_ae_hwstats_t ae_hwstats;
    // M4_STRUCT_DESC("wb_log", "normal_ui_style")
    uapi_wbV32_log_t wb_log;
} aiq_measure_info_t;
#endif

typedef struct __aiq_uapi_t {
    // M4_STRUCT_DESC("ae_uapi", "normal_ui_style")
    ae_uapi_t ae_uapi;
    // M4_STRUCT_DESC("awb_uapi", "normal_ui_style")
    awb_uapi_t awb_uapi;
    // M4_STRUCT_DESC("amerge_uapi", "normal_ui_style")
    amerge_uapi_t amerge_uapi;
#if defined(ISP_HW_V20)
    // M4_STRUCT_DESC("atmo_uapi", "normal_ui_style")
    atmo_uapi_t atmo_uapi;
#else
    // M4_STRUCT_DESC("adrc_uapi", "normal_ui_style")
    adrc_uapi_t adrc_uapi;
#endif
    // M4_STRUCT_DESC("agamma_uapi", "normal_ui_style")
    agamma_uapi_t agamma_uapi;
    // M4_STRUCT_DESC("adehaze_uapi", "normal_ui_style")
    adehaze_uapi_t adehaze_uapi;
    // M4_STRUCT_DESC("SystemCtl", "normal_ui_style")
    RkaiqSysCtl_t system;
    // M4_STRUCT_DESC("measure_info", "normal_ui_style")
    aiq_measure_info_t measure_info;
} RkaiqUapi_t;

#ifdef __cplusplus
}
#endif

#endif  /*___RK_AIQ_UAPITYPES_H__*/
