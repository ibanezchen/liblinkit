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
 
#ifndef __HAL_TRNG_H__
#define __HAL_TRNG_H__

#include "hal_platform.h"
#ifdef HAL_TRNG_MODULE_ENABLED

/**
 * @addtogroup HAL
 * @{
 * @addtogroup TRNG
 * @{
 * This section introduces  the TRNG APIs including terms and acronym,
 * supported features, software architecture, how to use this driver, TRNG function groups, all enum, structures and functions.
 *
 * @section Terms_Chapter Terms and acronyms
 *
 * |Terms                   |Details                                                                 |
 * |------------------------------|------------------------------------------------------------------------|
 * |\b TRNG                |True Randam Number Generater. TRNG is a HW generater which will generate random data for applications . |

 * @section TRNG_Driver_Usage_Chapter How to use this driver
 *
 * - Trigger TRNG generate random number. \n
 *  - step1: Call hal_trng_init() to initialize  TRNG clock.
 *  - step2: Call hal_trng_get_generated_random_number() to generate random number.
 *  - step3: Call hal_trng_deinit() to  de-initialize  TRNG

 *  - sample code:
 *    @code
 *       ret = hal_trng_init(); //initialize the TRNG source clock
 *       if(HAL_TRNG_STATUS_OK != ret) {
 *             //error handle
 *       }
 *       ret = hal_trng_get_generated_random_number(&random_number); //get random number .
 *       if(HAL_TRNG_STATUS_OK != ret) {
 *             //error handle
 *       }
 *       
 *    hal_trng_deinit();   // de-initialize the TRNG.
 *
 *    @endcode
 */



#ifdef __cplusplus
extern "C" {
#endif


/** @defgroup hal_trng_enum Enum
  * @{
  */


/** @brief This enum defines the API return type.  */
typedef enum {
    HAL_TRNG_STATUS_ERROR                = -2,         /**< This value means error happened during the function call. */
    HAL_TRNG_STATUS_INVALID_PARAMETER    = -1,         /**<  This value means a wrong parameter is given. */
    HAL_TRNG_STATUS_OK                   =  0          /**<  This value means no error happen during the function call. */
} hal_trng_status_t;


/**
  * @}
  */



/**
 * @brief     This function initializes the TRNG hardware clock .
 * @return   To indicate whether this function call is successful or not.
 *               If the return value is #HAL_TRNG_STATUS_OK, it means success.
 * @par       Example
 * Sample code please refer to @ref TRNG_Driver_Usage_Chapter
 * @sa  hal_trng_deinit()
 */

hal_trng_status_t hal_trng_init(void);



/**
 * @brief     This function de-initializes the TRNG hardware clock .
 * @return   To indicate whether this function call is successful or not.
 *               If the return value is #HAL_TRNG_STATUS_OK, it means success.
 * @par       Example
 * Sample code please refer to @ref TRNG_Driver_Usage_Chapter
 * @sa  hal_trng_init()
 */

hal_trng_status_t hal_trng_deinit(void);



/**
 * @brief     This function is used to get  random number which TRNG generated .
 * @param[out] random_number is the TRNG hardware generated.
 * @return   To indicate whether this function call is successful or not.
 *               If the return value is #HAL_TRNG_STATUS_OK, it means success.
 * @par       Example
 * Sample code please refer to @ref TRNG_Driver_Usage_Chapter.
 * @sa  hal_trng_init(),hal_trng_deinit().
 */


hal_trng_status_t hal_trng_get_generated_random_number(uint32_t *random_number);


#ifdef __cplusplus
}
#endif


/**
* @}
* @}
*/

#endif /*HAL_TRNG_MODULE_ENABLED*/
#endif /* __HAL_TRNG_H__ */

