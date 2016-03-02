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
 

#ifndef __HAL_LOG_H__
#define __HAL_LOG_H__

/**
 * @filel_log.h.
 *
 * The debug printing macros that were used by HAL module is defined in this
 * header file.
 *
 * Feature option: MTK_HAL_PLAIN_LOG_ENABLE
 *
 * This feature option turns the LOG system integration off in HAL module.
 * It was added to allow bootloader, which has no operating system in it, to
 * be able to use HAL layer code.
 */
#include "hal_feature_config.h"

#if !defined(MTK_HAL_PLAIN_LOG_ENABLE)
#include "syslog.h"
#else
#include "stdio.h"
#endif /* !defined(MTK_HAL_PLAIN_LOG_ENABLE) */

#ifdef __cplusplus
extern "C" {
#endif


#if !defined(MTK_HAL_PLAIN_LOG_ENABLE)


#define log_hal_create(_level)                      log_create_module(hal, (_level))
#define log_hal_fatal(_message,...)                 LOG_E(hal, (_message), ##__VA_ARGS__)
#define log_hal_error(_message,...)                 LOG_E(hal, (_message), ##__VA_ARGS__)
#define log_hal_warning(_message,...)               LOG_W(hal, (_message), ##__VA_ARGS__)
#define log_hal_info(_message,...)                  LOG_I(hal, (_message), ##__VA_ARGS__)
#define log_hal_dump(_message, _data, _len, ...)    LOG_HEXDUMP_I(hal, (_message), (_data), (_len), ##__VA_ARGS__)
#define log_hal_config_print_switch(_switch)        log_config_print_switch(hal, (_switch))
#define log_hal_config_print_level(_level)          log_config_print_level(hal, (_level))
#define log_hal_config_print_func(_print_func)      log_config_print_func(hal, (_print_func))
#define log_hal_config_dump_func(_dump_func)        log_config_dump_func(hal, (_dump_func))


#else /* !defined(MTK_HAL_PLAIN_LOG_ENABLE) */



#define log_hal_create(_level)
#define log_hal_fatal(_message...)                  do { printf(_message); } while (0)
#define log_hal_error(_message...)                  do { printf(_message); } while (0)
#define log_hal_warning(_message...)                do { printf(_message); } while (0)
#define log_hal_info(_message...)                   do { printf(_message); } while (0)
#define log_hal_dump(_message, _data, _len, ...)    do {} while (0)
#define log_hal_config_print_switch(_switch)        do {} while (0)
#define log_hal_config_print_level(_level)          do {} while (0)
#define log_hal_config_print_func(_print_func)      do {} while (0)
#define log_hal_config_dump_func(_dump_func)        do {} while (0)


#endif /* defined(MTK_HAL_PLAIN_LOG_ENABLE) */


#ifdef __cplusplus
}
#endif

#endif /* __HAL_LOG_H__ */

