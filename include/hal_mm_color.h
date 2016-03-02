/* Copyright Statement:
 *
 * @2015 MediaTek Inc. All rights reserved.
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. and/or its licensors.
 * Without the prior written permission of MediaTek Inc. and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 *
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
 * RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER ON
 * AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH THE MEDIATEK SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN MEDIATEK SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * MEDIATEK FOR SUCH MEDIATEK SOFTWARE.
 */
 
#ifndef __HAL_MM_COLOR_H__
#define __HAL_MM_COLOR_H__

#include "hal_platform.h"
#ifdef HAL_MM_COLOR_MODULE_ENABLED
#include "hal_lcd_if_common.h"
#include "hal_mm_color_internal.h"

//#define LCD_COLOR_base 0xA0470000

#define COLOR_CUSTOM_SHARPNESS_TABLE_NUM  10
#define COLOR_CUSTOM_CONTRAST_TABLE_NUM  10
#define COLOR_CUSTOM_SATURATION_TABLE_NUM  10
#define COLOR_BYPASS_NONE               		0x00000000
#define COLOR_BYPASS_SAT                		0x00000001
#define COLOR_BYPASS_CONTRAST           	0x00000002
#define COLOR_BYPASS_SHARP              	0x00000004
#define COLOR_BYPASS_Y2R                		0x00000008
#define COLOR_BYPASS_R2Y                		0x00000010
#define COLOR_BYPASS_ALL                		0x0000001F
#define COLOR_BYPASS_STALL              		0x00000080
#define COLOR_BYPASS_MASK               		0x0000009F


HAL_LCD_ERROR_ENUM hal_mm_color_initialize(void);
HAL_LCD_ERROR_ENUM hal_mm_color_set_enable(uint8_t enable);
HAL_LCD_ERROR_ENUM hal_mm_color_get_enable(uint8_t* enable);
HAL_LCD_ERROR_ENUM hal_mm_color_power_on(void);
HAL_LCD_ERROR_ENUM hal_mm_color_power_off(void);
HAL_LCD_ERROR_ENUM hal_mm_color_set_sharpness(HAL_MM_COLOR_SHARPNESS_T *sharpness);
HAL_LCD_ERROR_ENUM hal_mm_color_set_contrast(HAL_MM_COLOR_CONTRAST_T *contrast);
HAL_LCD_ERROR_ENUM hal_mm_color_set_saturation(HAL_MM_COLOR_SATURATION_T *saturation);
HAL_LCD_ERROR_ENUM hal_mm_color_set_bypass(uint32_t bypass);
HAL_LCD_ERROR_ENUM hal_mm_color_set_scenario(HAL_MM_COLOR_SCENARIO_ENUM scenario);
HAL_LCD_ERROR_ENUM hal_mm_color_apply_PQ(uint32_t src_width);

#endif // HAL_MM_COLOR_MODULE_ENABLED
#endif //__HAL_MM_COLOR_H__


