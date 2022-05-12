/*
 * Copyright (c) 2019-2022 Rockchip Eletronics Co., Ltd.
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
 */

#ifndef _RK_AIQ_UAPI_ABAYER2DNR_INT_V23_H_
#define _RK_AIQ_UAPI_ABAYER2DNR_INT_V23_H_

#include "base/xcam_common.h"
#include "rk_aiq_algo_des.h"
#include "abayer2dnrV23/rk_aiq_types_abayer2dnr_algo_int_v23.h"

// need_sync means the implementation should consider
// the thread synchronization
// if called by RkAiqAlscHandleInt, the sync has been done
// in framework. And if called by user app directly,
// sync should be done in inner. now we just need implement
// the case of need_sync == false; need_sync is for future usage.


XCamReturn
rk_aiq_uapi_abayer2dnrV23_SetAttrib(RkAiqAlgoContext *ctx,
                                    const rk_aiq_bayer2dnr_attrib_v23_t *attr,
                                    bool need_sync);

XCamReturn
rk_aiq_uapi_abayer2dnrV23_GetAttrib(const RkAiqAlgoContext *ctx,
                                    rk_aiq_bayer2dnr_attrib_v23_t *attr);

XCamReturn
rk_aiq_uapi_abayer2dnrV23_SetStrength(const RkAiqAlgoContext *ctx,
                                      const rk_aiq_bayer2dnr_strength_v23_t* pStrength);

XCamReturn
rk_aiq_uapi_abayer2dnrV23_GetStrength(const RkAiqAlgoContext *ctx,
                                      rk_aiq_bayer2dnr_strength_v23_t* pStrength);





#endif
