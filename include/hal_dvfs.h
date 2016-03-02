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
 
#ifndef __HAL_DVFS_H__
#define __HAL_DVFS_H__

/**
 * @addtogroup HAL
 * @{
 * @addtogroup DVFS
 * @{
 * DVFS framework is used to help users easily adjust the CPU frequency at a suitable voltage level.
 * DVFS framework is composed of the following modules:\n
 * CPU frequency, OPP list, voltage controller.\n
 *
 * @section HAL_DVFS_Terms_Chapter Terms and acronyms
 *
 * The following provides descriptions of the terms commonly used in the CLOCK driver and how to use its various functions.
 *
 * |Terms               |Details                                                                 |
 * |--------------------|------------------------------------------------------------------------|
 * |\b CPU \b frequency | How to adjust CPU frequency. |
 * |\b OPP              | Operating Performance Point, a tuple of frequency and voltage. |
 *
 */

#include <stdint.h>
#include <stdbool.h>
#include "hal_platform.h"

#ifdef HAL_DVFS_MODULE_ENABLED

/*****************************************************************************
* Define
*****************************************************************************/
/**@defgroup dvfs_macro
  * @{
  */
/** @brief This macro defines the relationship between the target frequency and the result frequency. */
#define FREQ_RELATION_L 0  /**< lowest frequency at or above target */
#define FREQ_RELATION_H 1  /**< highest frequency below or at target */

/**
  * @}
  */

/*****************************************************************************
* Enum
*****************************************************************************/
/** @defgroup hal_dvfs_enum Enum
  * @{
  */
/** @brief This enum defines return status of DVFS HAL public API. User should check return value after calling those APIs. */
typedef enum {
    HAL_DVFS_STATUS_OK  =  0,                     /**< DVFS function executed successfully */
    HAL_DVFS_STATUS_ERROR  = -1,                  /**< DVFS function detected a common error */
    HAL_DVFS_STATUS_INVAL  = -2,                  /**< User's parameter is invalid */
    HAL_DVFS_STATUS_NOINIT = -3,                  /**< Non-initialized */
    HAL_DVFS_STATUS_EBUSY  = -4,                  /**< Device or resource busy */
    HAL_DVFS_STATUS_EPERM  = -5,                  /**< Operation not permitted */
} hal_dvfs_status_t;

/**
  * @}
  */

/*****************************************************************************
* extern global function
*****************************************************************************/
/**
 * @brief       Initialize the dvfs framework.
 * @return      #HAL_DVFS_STATUS_OK if OK.\n
 *              #HAL_DVFS_STATUS_ERROR if other errors.\n
 */
hal_dvfs_status_t hal_dvfs_init(void);

/**
 * @brief       Adjust the CPU frequency to a suitable target frequency according to the passed-in relation.
 * @param[in]   target_freq: The target frequency, its unit is KHz. For example, 208000 means 208MHz.
 * @param[in]   relation: The relationship between the target frequency and the final frequency.
 *              #HAL_DVFS_FREQ_RELATION_L for lowest frequency at or above target.\n
 *              #HAL_DVFS_FREQ_RELATION_H for highest frequency below or at target.\n
 *              Example 1.\n
 *              hal_dvfs_target_cpu_frequency(103000, HAL_DVFS_FREQ_RELATION_L) means the final cpu frequency is larger than 103 MHz.\n
 *              Example 2.\n
 *              hal_dvfs_target_cpu_frequency(103000, HAL_DVFS_FREQ_RELATION_H) means the final cpu frequency is smaller than 103 MHz.\n
 * @return      #HAL_DVFS_STATUS_OK if OK.\n
 *              #HAL_DVFS_STATUS_INVAL if user's parameter is invalid.\n
 *              #HAL_DVFS_STATUS_ERROR if other errors.\n
 */
hal_dvfs_status_t hal_dvfs_target_cpu_frequency(uint32_t target_freq, uint32_t relation);

/**
 * @brief       Get the current CPU frequency.
 * @return      The current CPU frequency in KHz. For example, 208000 means 208MHz.
 */
uint32_t hal_dvfs_get_cpu_frequency(void);

/**
 * @brief       Get all adjustable CPU frequencies.
 * @param[in]   list: double pointer to the frequency table.
 * @param[in]   list_num: pointer to the number of frequency table.
 * @return      #HAL_DVFS_STATUS_OK if OK.\n
 *              #HAL_DVFS_STATUS_ERROR if other errors.\n
 */
hal_dvfs_status_t hal_dvfs_get_cpu_frequency_list(const uint32_t **list, uint32_t *list_num);

/**
* @}
* @}
*/

#endif /* HAL_DVFS_MODULE_ENABLED */

#endif /* __HAL_DVFS_H__ */

