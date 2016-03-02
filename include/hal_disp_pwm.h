/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. and/or its licensors.
 * Without the prior written permission of MediaTek inc. and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 */
/* MediaTek Inc.   2015. All rights reserved.
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
 * MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 * The following software/firmware and/or related documentation ("MediaTek Software")
 * have been modified by MediaTek Inc. All revisions are subject to any receiver's
 * applicable license agreements with MediaTek Inc.
 */



#ifndef __HAL_DISP_PWM_H__
#define __HAL_DISP_PWM_H__

#include "hal_platform.h"
#ifdef HAL_DISP_PWM_MODULE_ENABLED
/**
 * @addtogroup HAL
 * @{
 * @addtogroup DISP_PWM
 * @{
 * This section introduces  the DISP_PWM APIs including terms and acronym,
 * supported features, software architecture, how to use this driver, ISINK function groups, all enum, structures and functions.
 *
 * @section Terms_Chapter Terms and acronyms
 *
 * |Terms                   |Details                                                                 |
 * |------------------------------|------------------------------------------------------------------------|
 * |\b ISINK                |Current Sink which could give different current depend PMIC setting . |
 * |\b PMIC                 |Power Management Integrated Chip |

 * @section DISP_PWM_Driver_Usage_Chapter How to use this driver
 *
 */


#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    HAL_DISP_PWM_0 = 0,                          /**< disp_pwm channel 0 */
	HAL_DISP_PWM_1, 							 /**< disp_pwm channel 1 */
    HAL_DISP_PWM_MAX_CHANNEL,                    /**< disp_pwm max channel (invalid)*/
} hal_disp_pwm_channel_t;


typedef enum {
    HAL_DISP_PWM_CLOCK_26MHZ = 0,                /**< disp_pwm clock srouce 26Mhz */
    HAL_DISP_PWM_CLOCK_104MHZ = 1,                /**< disp_pwm clock source 104Mhz */
} hal_disp_pwm_source_clock_t ;

typedef enum {
    HAL_DISP_PWM_NORMAL_MODE = 0,                              /**<Normal mode  */
    HAL_DISP_PWM_GRADUAL_MODE = 1,                           /**<Gradual mode  */
} hal_disp_pwm_mode_t ;

typedef enum {
    HAL_DISP_PWM_STATUS_ERROR               = -3,       /**< disp_pwm function error */
    HAL_DISP_PWM_STATUS_ERROR_CHANNEL       = -2,       /**< disp_pwm error port */
    HAL_DISP_PWM_STATUS_INVALID_PARAMETER   = -1,       /**< disp_pwm error invalid parameter */
    HAL_DISP_PWM_STATUS_OK   = 0,                       /**< disp_pwm function ok*/
} hal_disp_pwm_status_t;


typedef enum {
    HAL_DISP_PWM_IDLE = 0,                         /**< This value means disp_pwm idle */
    HAL_DISP_PWM_BUSY = 1                          /**< This value means disp_pwm busy */
} hal_disp_pwm_running_status_t;

hal_disp_pwm_status_t  hal_disp_pwm_init(void);

hal_disp_pwm_status_t  hal_disp_pwm_deinit(void);

hal_disp_pwm_status_t hal_disp_pwm_set_source_clock(hal_disp_pwm_source_clock_t source_clock);

hal_disp_pwm_status_t hal_disp_pwm_set_mode(hal_disp_pwm_mode_t mode);

hal_disp_pwm_status_t hal_disp_pwm_set_duty(uint32_t percent);

hal_disp_pwm_status_t hal_disp_pwm_gradual_mode_enable(hal_disp_pwm_mode_t mode);

hal_disp_pwm_status_t hal_disp_pwm_get_running_status(hal_disp_pwm_running_status_t *running_status);


#ifdef __cplusplus
}
#endif


/**
* @}
* @}
*/

#endif /*HAL_DISP_PWM_MODULE_ENABLED*/
#endif /* __HAL_DISP_PWM_H__ */

