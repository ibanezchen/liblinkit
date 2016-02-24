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
 
#ifndef __HAL_IRRX_H__
#define __HAL_IRRX_H__

#include "hal_platform.h"

#ifdef HAL_IRRX_MODULE_ENABLED

/**
 * @addtogroup HAL
 * @{
 * @addtogroup IRRX
 * @{
 * This section introduces all details about the IRRX APIs including terms and acronyms,
 * supported features, software architecture, how to use this driver, IRRX function groups ,all enum, structures and functions.
 *
 * @section HAL_IRRX_Terms_Chapter Terms and acronyms
 *
 * |Terms                   |Details                                                                 |
 * |------------------------------|------------------------------------------------------------------------|
 * |\b IRRX                       | Infrared Receiver. A receive element use infrared radiation. |
 *
 * @section HAL_IRRX_Features_Chapter Supported features
 *
 * - \b Support \b rc5 \b and \b pwd \b mode. \n
 *   MT7687 support two ways to decode by hardware:
 *  - \b rc5 \b mode: The Philips RC5 IR transmission protocol uses Manchester encoding of the message bits.
 *                    In this mode, you can receive and decode rc5 code directly.
 *  - \b pwd \b mode: PWD is pulse-width-detection in short.In this mode, you can receive any kind of code
 *                    transmits by Infrared Radiation. The hardware will count the length of every wave. You can
 *                    know the cammand sent by calculate the length of wave.
 *
 * @section HAL_IRRX_Driver_Usage_Chapter How to use this driver
 *
 * - Use IRRX in a rc5 mode. \n
 *  - step1: call #hal_pinmux_set_function to set GPIO34 to function 7.
 *  - step2: call #hal_irrx_receive_rc5_start to start the hardware.
 *  - step3: call #hal_irrx_receive_rc5 to receive code.
 *  - step4: if you want to restart rc5 mode, call #hal_irrx_receive_rc5_start once again.
 *  - sample code:
 *    @code
 *       hal_pinmux_set_function(HAL_GPIO_34, 7);//Set GPIO34 to IRRX mode.
 *       hal_irrx_receive_rc5_start(HAL_IRRX_RC5_RECEIVE_FORMAT_BIT_REVERSE, //hardware will decode received data by bit
 *                                  receive_code_rc5, //callback function
 *                                  NULL);
 *       hal_irrx_receive_rc5(&code_rc5); //receive and save code
 *
 *    @endcode
 * - Use IRRX in a pwd mode. \n
 *  - step1: set pwd parameters: inverse and terminate_threshold.
 *  - step2: call #hal_irrx_receive_pwd_start to start the hardware.
 *  - step3: call #hal_irrx_receive_pwd to receive code.
 *  - step4: if you want to restart rc5 mode, call #hal_irrx_receive_pwd_start once again.
 *  - sample code:
 *    @code
 *       uint32_t us = 0;
 *       hal_irrx_pwd_config_t format = {0};    //pwd parameter
 *       format.inverse = 1;
 *       format.terminate_threshold = 10200;
 *       if (HAL_IRRX_STATUS_OK != hal_irrx_receive_pwd_start(&format,
 *                                                            receive_code_pwd,
 *                                                            &us)) {
 *          dbg_error("hal_irrx_receive_pwd_start fail!");
 *       }
 *       if (HAL_IRRX_STATUS_OK != hal_irrx_receive_pwd(&received_length,
 *                                                      data,
 *                                                      sizeof(data))) {
 *          dbg_error("hal_irrx_receive_pwd fail!");
 *       }
 *
 *    @endcode
 * - Use IRRX driver to trigger IRRX rc5/pwd manually. \n
 *
 *
 */



#ifdef __cplusplus
extern "C" {
#endif



/** @defgroup hal_irrx_enum Enum
  * @{
  */


/** @brief RC5 and Pulse Width Detect mode are supported. */
typedef enum{
    HAL_IRRX_STATUS_INVALID_PARAM = -2,
    HAL_IRRX_STATUS_NOT_SUPPORTED = -1,
    HAL_IRRX_STATUS_OK = 0
} hal_irrx_status_t;


/** @brief IRRX transaction error. */
typedef enum{
    HAL_IRRX_EVENT_TRANSACTION_ERROR = -1,
    HAL_IRRX_EVENT_TRANSACTION_SUCCESS = 0 
} hal_irrx_event_t;

/** @brief IRRX  running status */
typedef enum {
    HAL_IRRX_IDLE = 0,
    HAL_IRRX_BUSY = 1
} hal_irrx_running_status_t;


/**
  * @}
  */
  
/** @defgroup hal_irrx_typedef Typedef
   * @{
   */

/** @brief  This defines the callback function prototype.
 *          Register a callback function when in an interrupt mode , this function will be called in IRRX interrupt.
 *          service routine after a transaction is complete
 *  @param [in] event is the transaction event for the current transaction, application can get the transaction result from this parameter.
 *              For more details about the event type, please refer to #hal_irrx_event_t
 *  @param [in] user_data is a parameter provided  by the application .
 */

typedef void (*hal_irrx_callback_t)(hal_irrx_event_t event, void  *user_data);

/**
  * @}
  */

/** @defgroup hal_irrx_struct Struct
  * @{
  */

/**  @RC5 code.bits specifies the valid bits in code[2]. */
typedef struct hal_irrx_rc5_code_s
{
    uint8_t     bits;
    uint32_t    code[2];
} hal_irrx_rc5_code_t;



/** @Pulse-Width-Modulation receive config*/
typedef struct hal_irrx_pwd_config_s
{
    uint8_t     inverse;
    uint32_t    terminate_threshold;
} hal_irrx_pwd_config_t;

/**
  * @}
  */




/** @defgroup hal_irrx_define Define
  * @{
 */

/** @When applied to RC5 receive format, this flag causes the IR pulse inversed  before decoded. */
#define HAL_IRRX_RC5_RECEIVE_FORMAT_SIGNAL_INVERSE      (0x1)


/** @When applied to RC5 receive format, this flag causes order reverse. The decoded IR pulse is bit-reversed.*/
#define HAL_IRRX_RC5_RECEIVE_FORMAT_BIT_REVERSE         (0x10)

/**
  * @}
  */

/**
 * @brief    This function initializes the IRRX hardware clock
 * @return  To indicate whether this function call is successful or not.
 *               #HAL_IRRX_STATUS_OK if the receive started successfully.
                #HAL_IRRX_STATUS_INVALID_PARAM if callback is not specified.
 * @par       Example
 * Sample code please refer to @ref Driver_Usage_Chapter
 * @sa  hal_pwm_deinit()
 */

hal_irrx_status_t hal_irrx_init(void);


/**
 * @brief    This function de-initializes the IRRX hardware clock
 * @return  To indicate whether this function call is successful or not.
 *               #HAL_IRRX_STATUS_OK if the receive started successfully.
                 #HAL_IRRX_STATUS_INVALID_PARAM if callback is not specified.
 * @par       Example
 * Sample code please refer to @ref Driver_Usage_Chapter
 * @sa  hal_pwm_deinit()
 */

hal_irrx_status_t hal_irrx_deinit(void);



/**
 * @brief     IR RC5 code receive start function.
 * @param[in] format  the combination of #HAL_IRRX_RC5_RECEIVE_FORMAT_INVERSE
 *                 and #HAL_IRRX_RC5_RECEIVE_FORMAT_REVERSE.
 * @param[in] callback the callback function to be called when the receive has ended.
 * @param[in] parameter the parameter to be bring back to caller when receive has ended.
 * @return   To indicate whether this function call is successful or not.
 *               #HAL_IRRX_STATUS_OK if the receive started successfully.
                 #HAL_IRRX_STATUS_INVALID_PARAM if callback is not specified.
 * @par       Example
 * Sample code please refer to @ref HAL_IRRX_Driver_Usage_Chapter 
 * @sa  hal_irrx_receive_rc5()
 */



hal_irrx_status_t hal_irrx_receive_rc5_start(uint8_t             format,
                                             hal_irrx_callback_t callback,
                                             void                *parameter);
/**
 * @brief     IR RC5 code receive  function.
 * @param[in] ode the callback function to be called when the receive has ended.
 * @return   To indicate whether this function call is successful or not.
 *               HAL_IRRX_STATUS_OK if the receive started successfully.
                 HAL_IRRX_STATUS_INVALID_PARAM if callback is not specified.
 * @par       Example
 * Sample code please refer to @ref HAL_IRRX_Driver_Usage_Chapter 
 * @sa  hal_irrx_receive_rc5_start()
 */

hal_irrx_status_t hal_irrx_receive_rc5(hal_irrx_rc5_code_t *code);


/**
 * @brief     IR Pulse-Width-Detection code receive start function.
 * @param[in] config which will be  used when the receive is started.
 * @param[in] callback the callback function to be called when the receive has ended.
 * @return   To indicate whether this function call is successful or not.
 *               #HAL_IRRX_STATUS_OK if the receive started successfully.
 *             #HAL_IRRX_STATUS_INVALID_PARAM if callback is not specified.
 * @par       Example
 * Sample code please refer to @ref HAL_IRRX_Driver_Usage_Chapter 
 * @sa  hal_irrx_receive_pwd()
 */

hal_irrx_status_t hal_irrx_receive_pwd_start(
                                const hal_irrx_pwd_config_t     *config,
                                hal_irrx_callback_t             callback,
                                uint32_t                        *precision_us);


/**
 * @brief     IR Pulse-Width-Detection code receive function.
 * @param[in]  received_length the actual received length of code in the buffer.
 * @param[in]   buffer the buffer to be used to stored received code.
 * @param[in]  buffer_length the length of buffer that can be used to store  received code. 
 *                    The maximum is 68 bytes and it is suggested to prepare 68 bytes of space for buffer and specify 68 as buffer_length.
 * @return   To indicate whether this function call is successful or not.
 *               #HAL_IRRX_STATUS_OK if the  receive ended successfully.
                 #HAL_IRRX_STATUS_INVALID_PARAM ifif code is NULL.
 * @par       Example
 * Sample code please refer to @ref HAL_IRRX_Driver_Usage_Chapter 
 * @sa  hal_irrx_receive_pwd()
 */

hal_irrx_status_t hal_irrx_receive_pwd(uint8_t  *received_length,
                                       uint8_t  *buffer,
                                       uint8_t  buffer_length);


/**
 * @brief    This function is used to get the current state of the IRRX
 * @param[out] running_status is the current running status.
 *             #HAL_IRRX_BUSY means the IRRX is in busy status; \n
 *             #HAL_IRRX_IDLE means the IRRX is in idle status, user can use it to transfer data now.
 * @return   To indicate whether this function call is successful or not.
 *               If the return value is #HAL_IRRX_STATUS_OK, it means success.
 * @par       Example
 * Sample code please refer to @ref HAL_IRRX_Driver_Usage_Chapter 
 * @sa   hal_irrx_receive_pwd()
 */

hal_irrx_status_t hal_irrx_get_running_status(hal_irrx_running_status_t *running_status);



#ifdef __cplusplus
    }
#endif

/**
 * @}
 * @}
*/

#endif /*HAL_IRRX_MODULE_ENABLED*/
#endif /* __HAL_IRRX_H__ */


