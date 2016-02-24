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
 
#ifndef __HAL_IRTX_H__
#define __HAL_IRTX_H__

#include "hal_platform.h"

#ifdef HAL_IRTX_MODULE_ENABLED

/**
 * @addtogroup HAL
 * @{
 * @addtogroup IRTX
 * @{
 * This section describes the programming interfaces of the IRTX HAL driver.
 *
 * @section HAL_IRTX_Terms_Chapter Terms and acronyms
 *
 * The following provides descriptions to the terms commonly used in the ADC driver and how to use the various functions.
 *
 * |Terms                   |Details                                                                 |
 * |------------------------------|------------------------------------------------------------------------|
 * |\b IRTX                       | IRTX is Infrared Transmiter in short. The transmitter element of infrared radiation. |
 *
 * @section HAL_IRTX_Features_Chapter Supported features
 * - \b Support \b nec, \b rc5, \b rc6 and \b pwd \b mode. \n
 *   MT7687 has four ways to encode:
 * - \b nec \b mode: nec encode format is one of widest used infrared protocols in the world. In this mode,
 *                   your can send nec mode code by hardware directly.
 * - \b rc5 \b mode: The Philips RC5 IR transmission protocol uses Manchester encoding of the message bits.
 *                   In this mode, you can send rc5 mode code directly.
 * - \b rc6 \b mode: Like RC-5 the new RC-6 protocol was also defined by Philips. In this mode, you can send
 *                   rc6 mode code by hardware directly.
 * - \b pwd \b mode: PWD is pulse-width-detection in short.In this mode, you can send any kind of code
 *                   by Infrared Radiation. The hardware will count the length of every wave. You can
 *                   know the cammand sent by calculate the length of wave.
 *
 * @section HAL_IRTX_Driver_Usage_Chapter How to use this driver
 * - Use IRTX in a nec mode. \n
 *  - step1: call #hal_pinmux_set_function to set GPIO33 to function 7.
 *  - step2: call #hal_irtx_send_nec_data to start the hardware.
 *  - sample code:
 *    @code
 *       hal_pinmux_set_function(HAL_GPIO_33, 7);//Set GPIO33 to IRTX mode.
 *       uint8_t data[HAL_IRTX_MAX_DATA_LENGTH] = {
 *           0xA5, 0xF0, 0xAF, 0x00,
 *           0xff, 0x00, 0xAA, 0x55
 *       };
 *       if (HAL_IRTX_OK != hal_irtx_send_nec_data(HAL_IRTX_REPEAT_DISABLE, //if you want to send data repeat,use #HAL_IRTX_REPEAT_ENABLE
 *                                                 data, 64)) {
 *           printf("hal_irtx_send_nec_data fail.\r\n");
 *       }
 *    @endcode
 * - Use IRTX in a rc5 mode. \n
 *  - step1: call #hal_pinmux_set_function to set GPIO33 to function 7.
 *  - step2: call #hal_irtx_send_rc5_data to start the hardware.
 *  - sample code:
 *    @code
 *       hal_pinmux_set_function(HAL_GPIO_33, 7);//Set GPIO33 to IRTX mode.
 *       uint8_t data[HAL_IRTX_MAX_DATA_LENGTH] = {
 *           0xA5, 0xF0, 0xAF, 0x00,
 *           0xff, 0x00, 0xAA, 0x55
 *       };
 *       if (HAL_IRTX_OK != hal_irtx_send_rc5_data(HAL_IRTX_REPEAT_DISABLE, //if you want to send data repeat,use #HAL_IRTX_REPEAT_ENABLE
 *                                                 data, 64)) {
 *           printf("hal_irtx_send_rc5_data fail.\r\n");
 *       }
 *    @endcode
 * - Use IRTX in a rc6 mode. \n
 *  - step1: call #hal_pinmux_set_function to set GPIO33 to function 7.
 *  - step2: call #hal_irtx_send_rc6_data to start the hardware.
 *  - sample code:
 *    @code
 *       hal_pinmux_set_function(HAL_GPIO_33, 7);//Set GPIO33 to IRTX mode.
 *       uint8_t data[HAL_IRTX_MAX_DATA_LENGTH] = {
 *           0xA5, 0xF0, 0xAF, 0x00,
 *           0xff, 0x00, 0xAA, 0x55
 *       };
 *       if (HAL_IRTX_OK != hal_irtx_send_rc6_data(HAL_IRTX_REPEAT_DISABLE, //if you want to send data repeat,use #HAL_IRTX_REPEAT_ENABLE
 *                                                 data, 64)) {
 *           printf("hal_irtx_send_rc6_data fail.\r\n");
 *       }
 *    @endcode
 * - Use IRTX in a pwd mode. \n
 *  - step1: create a callback function as isr_ir_tx just you like.
 *  - step2: call #hal_irtx_register_pulse_data_callback to regiseter callback function.
 *  - step3: call #hal_irtx_configure_pulse_data_carrier to set frequency and duty_cycle.
 *  - step4: call #hal_irtx_send_pulse_data to send data.
 *  - sample code:
 *    @code
 *       static void isr_ir_tx(void *arg)
 *       {
 *           ir_tx_done = 1;
 *       }
 *
 *       uint8_t data_number = 41;
 *       uint8_t data[68] = {
 *           225, 112, 17, 15, 34, 15, 35, 15, 17, 15, 34, 15, 17, 15, 17, 15,
 *           17, 15, 34, 15, 17, 15, 34, 15, 34, 15, 17, 15, 34, 15, 17, 15,
 *           17, 15, 17, 15, 34, 15, 34, 15, 34
 *       };
 *
 *       printf("output Software Pluse Width IR \r\n");
 *       if (HAL_IRTX_OK != hal_irtx_register_pulse_data_callback(isr_ir_tx, NULL)) {
 *           printf("hal_irtx_send_pulse_data failed.\r\n");
 *           return;
 *       }
 *
 *       uint16_t frequency = 40;//40KHz
 *       uint8_t duty_cycle = 25;// 25% duty cycle
 *       if (HAL_IRTX_OK != hal_irtx_configure_pulse_data_carrier(frequency, duty_cycle)) {
 *           printf("hal_irtx_send_pulse_data failed.\r\n");
 *           return;
 *       }
 *
 *       uint8_t base_period = 80; // unit:0.5us, SWM_BP=80, PW_value saturate for NEC 9ms leading
 *       if (HAL_IRTX_OK != hal_irtx_send_pulse_data(base_period, data, data_number)) {
 *           printf("hal_irtx_send_pulse_data failed.\r\n");
 *           return;    }
 *
 *       while (!ir_tx_done) {
 *       }//wait for the interrupt
 *
 *    @endcode
 *
 */



#ifdef __cplusplus
extern "C" {
#endif


/** @defgroup hal_irtx_define Define
  * @{
 */

/** @brief irtx max data length */
#define HAL_IRTX_MAX_DATA_LENGTH (12)

/**
  * @}
 */



/** @defgroup hal_irtx_enum Enum
  * @{
 */

/** @brief irtx repeat mode */
typedef enum {
    HAL_IRTX_REPEAT_ENABLE = 0,
    HAL_IRTX_REPEAT_DISABLE
} hal_irtx_repeat_code_t;


/** @brief irtx status */
typedef enum {
    HAL_IRTX_STATUS_ERROR = -1,
    HAL_IRTX_STATUS_OK = 0
} hal_irtx_status_t;


/** @brief IRTX transaction error */
typedef enum {
    HAL_IRTX_EVENT_TRANSACTION_ERROR = -1,       /**< IRTX transaction error */
    HAL_IRTX_EVENT_TRANSACTION_SUCCESS = 0,      /**< IRTX transaction success */
} hal_irtx_event_t;


/** @brief IRTX  running status */
typedef enum {
    HAL_IRTX_IDLE = 0,                         /**< IRTX idle */
    HAL_IRTX_BUSY = 1,                         /**<IRTX busy */
} hal_irtx_running_status_t;


/**
  * @}
 */

/** @defgroup hal_irtx_typedef Typedef
   * @{
   */

/** @brief  This defines the callback function prototype.
 *          Register a callback function when in an interrupt mode , this function will be called in IRTX interrupt.
 *          service routine after a transaction is complete
 *  @param [in] event is the transaction event for the current transaction, application can get the transaction result from this parameter.
 *              For more details about the event type, please refer to #hal_irtx_event_t
 *  @param [in] user_data is a parameter provided  by the application .
 */



/** @brief irtx callback */
typedef void (*hal_irtx_pulse_data_callback_t)(hal_irtx_event_t event, void  *user_data);

/**
  * @}
 */

/**
 * @brief    This function initializes the IRTX hardware clock
 * @return  To indicate whether this function call is successful or not.
 *               HAL_IRRX_STATUS_OK if the receive started successfully.
                 HAL_IRRX_STATUS_INVALID_PARAM if callback is not specified.
 * @par       Example
 * Sample code please refer to @ref Driver_Usage_Chapter
 * @sa  hal_pwm_deinit()
 */

hal_irtx_status_t hal_irtx_init(void);


/**
 * @brief    This function de-initializes the IRTX hardware clock
 * @return  To indicate whether this function call is successful or not.
 *               #HAL_IRRX_STATUS_OK if the receive started successfully.
                 #HAL_IRRX_STATUS_INVALID_PARAM if callback is not specified.
 * @par       Example
 * Sample code please refer to @ref Driver_Usage_Chapter
 * @sa  hal_pwm_deinit()
 */

hal_irtx_status_t hal_irtx_deinit(void);



/**
 * @brief    send NEC ir data function.
 * @param[in] repeat_code  repeat code for NEC irtx.
 * @param[in] data data to be sent.
 * @param[in] bit_length  data length in bit
 * @return   To indicate whether this function call is successful or not.
 *               #HAL_IRTX_STATUS_OK if sends  successfully.
                 #HAL_IRTX_STATUS_INVALID_PARAM if invalid parameter.
 * @par       Example
 * Sample code please refer to @ref HAL_IRTX_Driver_Usage_Chapter 
 */

hal_irtx_status_t hal_irtx_send_nec_data(hal_irtx_repeat_code_t repeat_code,
                                         const uint8_t data[HAL_IRTX_MAX_DATA_LENGTH],
                                         uint32_t bit_length);



/**
 * @brief    send RC5 ir data function.
 * @param[in] repeat_code  repeat code for RC5 irtx.
 * @param[in] data the data content to be sent.
 * @param[in] bit_length  data length in bit
 * @return   To indicate whether this function call is successful or not.
 *               HAL_IRTX_STATUS_OK if sends  successfully.
                 HAL_IRTX_STATUS_INVALID_PARAM if invalid parameter.
 * @par       Example
 * Sample code please refer to @ref HAL_IRTX_Driver_Usage_Chapter 
 */

hal_irtx_status_t hal_irtx_send_rc5_data(hal_irtx_repeat_code_t repeat_code,
                                         const uint8_t data[HAL_IRTX_MAX_DATA_LENGTH],
                                         uint32_t bit_length);


/**
 * @brief    send RC6 ir data function.
 * @param[in] repeat_code  repeat code for RC6 irtx.
 * @param[in] data the data content to be sent.
 * @param[in] bit_length  data length in bit
 * @return   To indicate whether this function call is successful or not.
 *               #HAL_IRTX_STATUS_OK if sends  successfully.
                 #HAL_IRTX_STATUS_INVALID_PARAM if invalid parameter.
 * @par       Example
 * Sample code please refer to @ref HAL_IRTX_Driver_Usage_Chapter 
 */

hal_irtx_status_t hal_irtx_send_rc6_data(hal_irtx_repeat_code_t repeat_code,
                                         const uint8_t data[HAL_IRTX_MAX_DATA_LENGTH],
                                         uint32_t bit_length);



/**
 * @brief    configure the pulse data carrier function.
 * @param[in] frequency  pulse data carrier frequency.
 * @param[in] duty_cycle pulse data carrier duty cycle
 * @return   To indicate whether this function call is successful or not.
 *               #HAL_IRTX_STATUS_OK if sends  successfully.
                 #HAL_IRTX_STATUS_INVALID_PARAM if invalid parameter.
 * @par       Example
 * Sample code please refer to @ref HAL_IRTX_Driver_Usage_Chapter 
 */

hal_irtx_status_t hal_irtx_configure_pulse_data_carrier(uint32_t frequency,
                                                        uint32_t duty_cycle);


/**
 * @brief    register pulse data callback, which will be called after transmission completes.
 * @param[in] callback user defined callback function.
 * @param[in] user_data  user defined extension data
 * @return   To indicate whether this function call is successful or not.
 *               #HAL_IRTX_STATUS_OK if sends  successfully.
                 #HAL_IRTX_STATUS_INVALID_PARAM if invalid parameter.
 * @par       Example
 * Sample code please refer to @ref HAL_IRTX_Driver_Usage_Chapter 
 */

hal_irtx_status_t hal_irtx_register_pulse_data_callback(hal_irtx_pulse_data_callback_t callback,
                                                        void *user_data);

/**
 * @brief    send pulse data.
 * @param[in] base_period  base period for sending data.
 * @param[in] data  the data content to be sent
 * @param[in] length data length in byte
 * @return   To indicate whether this function call is successful or not.
 *               #HAL_IRTX_STATUS_OK if sends  successfully.
                 #HAL_IRTX_STATUS_INVALID_PARAM if invalid parameter.
 * @par       Example
 * Sample code please refer to @ref HAL_IRTX_Driver_Usage_Chapter 
 */

hal_irtx_status_t hal_irtx_send_pulse_data(uint32_t base_period, uint8_t *data, uint32_t length);


/**
 * @brief    This function is used to get the current state of the IRTX
 * @param[out] running_status is the current running status.
 *             #HAL_IRTX_BUSY means the IRTX is in busy status; \n
 *             #HAL_IRTX_IDLE means the IRTX is in idle status, user can use it to transfer data now.
 * @return   To indicate whether this function call is successful or not.
 *               If the return value is #HAL_IRTX_STATUS_OK, it means success.
 * @par       Example
 * Sample code please refer to @ref HAL_IRTX_Driver_Usage_Chapter 
 */

hal_irtx_status_t hal_irtx_get_running_status(hal_irtx_running_status_t *running_status);



#ifdef __cplusplus
    }
#endif

/**
 * @}
 * @}
*/

#endif /*HAL_IRTX_MODULE_ENABLED*/
#endif /* __HAL_IRTX_H__ */


