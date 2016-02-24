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
 
#ifndef __HAL_PWM_H__
#define __HAL_PWM_H__
#include "hal_platform.h"

#ifdef HAL_PWM_MODULE_ENABLED
/**
 * @addtogroup HAL
 * @{
 * @addtogroup PWM
 * @{
 * This section introduces the PWM APIs including terms and acronyms,
 * supported features, software architecture, details on how to use this driver, PWM function groups, enums, structures and functions.
 * @section Terms_Chapter Terms and acronyms
 *
 * |Terms                         |Details                                                                 |
 * |------------------------------|------------------------------------------------------------------------|
 * |\b PWM                        | Pulse-Width Modulation. PWM is a modulation technique used to encode a message into a pulsing signal. For more information, please refer to <a href="https://en.wikipedia.org/wiki/Pulse-width_modulation"> PWM in Wikipedia </a>.|
 * @section Features_Chapter Supported features
 *
 * - \b Support \b polling \b mode. \n
 *   After a fixed frequency and duty are set, the PWM will generate the fixed waveform at the specified frequency and duty set,the application can query current frequency and
 *   duty of the polling mode ,The PWM does not support interrupt mode.
 *   \n
 * @section Architechture_Chapter Software architecture of PWM
 *
 * Below diagrams show the software architecture of the PWM driver.
 * -# PWM polling mode architecture :  Call hal_pwm_init() function to initialize the PWM source clock,
 *   then, Call hal_pwm_set_frequency() function to set the PWM frequency and get the total counter of the hardware. Total counter is PWM counter internal value in specified frequency. Calculate the duty cycle according to application's duty ratio times total counter.
 *   Duty ratio is the value which duty counter divides total counter.
 *   Call hal_pwm_set_duty_cycle() function to set the PWM duty cycle. Call hal_pwm_start() function to trigger PWM execution.
 *   Call hal_pwm_get_frequency() and  hal_pwm_get_duty_cycle() functions if the current frequency and duty cycle need to be retrieved,
 *   Call hal_pwm_get_running_status() function  to get the PWM on busy or idle.  Call hal_pwm_stop() function to stop the PWM execution.
 *  Polling mode architecture is similar to the polling mode architecture in HAL overview. See @ref HAL_Overview_3_Chapter for polling mode architecture.
 *
 *
 * @section Driver_Usage_Chapte  How to use this driver
 *
 * @}
 * @}
*/
#ifdef HAL_PWM_FEATURE_ADVANCED_CONFIG


/**
 * @addtogroup HAL
 * @{
 * @addtogroup PWM
 * @{
 * - Use PWM with polling mode. \n
 *  - step1: call hal_pwm_init() to initialize  PWM source clock
 *  - step2: call hal_pwm_set_advanced_config() to select clock division, this is set as default and the configuration is optional.
 *  - step3: call hal_pwm_set_frequency() to set frequency and get  total count of the PWM hardware at the specific frequency.
 *  - step4: call hal_pwm_set_duty_cycle() to set duty cycle according to total count and application's duty ratio.
 *  - step5: call hal_pwm_start() to trigger PWM at a specified frequency and duty count values.
 *  - sample code:
 *    @code
 *       ret = hal_pwm_init(pwm_channel,source_clock); //initialize  PWM source clock
 *       if(HAL_PWM_STATUS_OK != ret) {
 *             //error handle
 *       }
 *     ret = hal_pwm_set_advanced_config( pwm_channel, advanced_config);
 *       if(HAL_PWM_STATUS_OK != ret) {
 *             //error handle
 *       }
 *       ret = hal_pwm_set_frequency(pwm_channel, frequency, &total_count); //set frequency and get total count of the PWM hardware at the specific frequency.
 *       if(HAL_PWM_STATUS_OK != ret) {
 *             //error handle
 *       }
 *       duty_cycle= duty_ratio * total_count //duty_cycle is calcauted as a product of application's duty_ratio and hardware's total_count.
 *       ret =hal_pwm_set_duty_cycle(pwm_channel, duty_cycle); //enable PWM to start the timer.
 *       if(HAL_PWM_STATUS_OK != ret) {
 *             //error handle
 *       }
 *       hal_pwm_start(pwm_channel);  //trigger PWM execution.
 *       //...
 *       hal_pwm_get_frequency(pwm_channel, &frequency);
 *       hal_pwm_get_duty_cycle(pwm_channel, &duty_cycle);
 *       //...
 *       hal_pwm_stop(pwm_channel); //stop the PWM.
 *       hal_pwm_deinit();   //deinitialize the PWM.
 *
 *    @endcode
  * @}
 * @}
 */

#endif


/**
 * @addtogroup HAL
 * @{
 * @addtogroup PWM
 * @{
 */


#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup hal_pwm_enum Enum
  * @{
  */

/** @brief	This enum defines the API return type.  */
typedef enum {
    HAL_PWM_STATUS_ERROR                = -3,         /**< An error occurred during the function call. */
    HAL_PWM_STATUS_ERROR_CHANNEL        = -2,         /**< A wrong PWM channel is given. */
    HAL_PWM_STATUS_INVALID_PARAMETER    = -1,         /**< A wrong parameter is given. */
    HAL_PWM_STATUS_OK                   =  0          /**< No error during the function call. */
} hal_pwm_status_t;



/** @brief   This enum defines the PWM running status */
typedef enum {
    HAL_PWM_IDLE = 0,                         /**< PWM status is idle */
    HAL_PWM_BUSY = 1                          /**< PWM status is busy */
} hal_pwm_running_status_t;

/**
  * @}
  */

#ifdef   HAL_PWM_FEATURE_ADVANCED_CONFIG

/** @defgroup hal_pwm_enum Enum
  * @{
  */

/** @brief  This enum defines PWM clock division advanced  configuration */
typedef enum {
    HAL_PWM_CLOCK_DIVISION_2 = 1,            /**< Specify PWM source clock 2 division */
    HAL_PWM_CLOCK_DIVISION_4 = 2,            /**< Specify PWM  source clock 4 division */
    HAL_PWM_CLOCK_DIVISION_8 = 3             /**< Specify PWM  source clock 8 division */
} hal_pwm_advanced_config_t;

/**
  * @}
  */

#endif



#ifdef HAL_PWM_FEATURE_SINGLE_SOURCE_CLOCK

/**
 * @brief    This function initializes the PWM hardware source clock.
 * @param[in]  source_clock is the PWM  source clock. For more details about the parameter, please refer to #hal_pwm_source_clock_t.
 * @return    To indicate whether this function call is successful or not.
 *            If the return value is #HAL_PWM_STATUS_OK, it means success.
 *            If the return value is #HAL_PWM_STATUS_INVALID_PARAMETER, it means a wrong parameter is given. The parameter needs to be verified.
 * @par       Example
 * Sample code please refer to @ref Driver_Usage_Chapter
 * @sa  hal_pwm_deinit()
 */

hal_pwm_status_t hal_pwm_init(hal_pwm_source_clock_t source_clock);

#else
/**
 * @brief    This function initializes the PWM hardware source clock.
 * @param[in]  pwm_channel is PWM channel number. For more details about the parameter, please refer to #hal_pwm_channel_t.
 * @param[in]  source_clock is the PWM  source clock. For more details about the parameter, please refer to #hal_pwm_source_clock_t.
 * @return    To indicate whether this function call is successful or not.
 *            If the return value is #HAL_PWM_STATUS_OK, it means success.
 *            If the return value is #HAL_PWM_STATUS_INVALID_PARAMETER, it means a wrong parameter is given. The parameter needs to be verified.
 * @par       Example
 * Sample code please refer to @ref Driver_Usage_Chapter
 * @sa  hal_pwm_deinit()
 */



hal_pwm_status_t hal_pwm_init(hal_pwm_channel_t pwm_channel, hal_pwm_source_clock_t source_clock);

#endif

/**
 * @brief   This function  deinitializes  PWM hardware .
 * @param[in]  pwm_channel is PWM channel number. For more details about the parameter, please refer to #hal_pwm_channel_t.
 * @return    To indicate whether this function call is successful or not.
 *            If the return value is #HAL_PWM_STATUS_OK, it means success.
 *            If the return value is #HAL_PWM_STATUS_INVALID_PARAMETER, it means a wrong parameter is given. The parameter needs to be verified.
 * @par       Example
 * Sample code please refer to @ref Driver_Usage_Chapter
 * @sa  hal_pwm_init()
 */

hal_pwm_status_t hal_pwm_deinit(hal_pwm_channel_t pwm_channel);


/**
 * @brief This function  sets PWM  frequency and retrieved total count of the PWM hardware at the specified frequency.
 * @param[in]  pwm_channel is PWM channel number. For more details about the parameter, please refer to #hal_pwm_channel_t
 * @param[in]  frequency is  PWM output  frequency.
 * @param[out]   total_count is  PWM hardware total count, the value of this parameter varies based on the given PWM frequency.
 * @return    To indicate whether this function call is successful or not.
 *            If the return value is #HAL_PWM_STATUS_OK, it means success.
 *            If the return value is #HAL_PWM_STATUS_INVALID_PARAMETER, it means a wrong parameter is given. The parameter needs to be verified.
 * @par       Example
 * Sample code please refer to @ref Driver_Usage_Chapter
 * @sa  hal_pwm_get_duty_cycle()
 */
hal_pwm_status_t hal_pwm_set_frequency(hal_pwm_channel_t pwm_channel, uint32_t frequency, uint32_t *total_count);


/**
 * @brief This function sets PWM  duty cycle.
 * @param[in]  pwm_channel is PWM channel number. For more details about the parameter, please refer to #hal_pwm_channel_t.
 * @param[in]  duty_cycle is PWM hardware duty cycle, which is calucated by application's duty ratio times hardware 's total count.
 * @return    To indicate whether this function call is successful or not.
 *            If the return value is #HAL_PWM_STATUS_OK, it means success.
 *            If the return value is #HAL_PWM_STATUS_INVALID_PARAMETER, it means a wrong parameter is given. The parameter needs to be verified.
 * @par       Example
 * Sample code please refer to @ref Driver_Usage_Chapter
 * @sa  hal_pwm_get_duty_cycle()
 */

hal_pwm_status_t hal_pwm_set_duty_cycle(hal_pwm_channel_t pwm_channel, uint32_t duty_cycle);



/**
 * @brief This function is  used to start the PWM execution.
 * @param[in]  pwm_channel is PWM channel number. For more details about the parameter, please refer to #hal_pwm_channel_t.
 * @return    To indicate whether this function call is successful or not.
 *            If the return value is #HAL_PWM_STATUS_OK, it means success.
 *            If the return value is #HAL_PWM_STATUS_INVALID_PARAMETER, it means a wrong parameter is given. The parameter needs to be verified.
 * @par       Example
 * Sample code please refer to @ref Driver_Usage_Chapter
 * @sa  hal_pwm_get_duty_cycle()
 */

hal_pwm_status_t hal_pwm_start(hal_pwm_channel_t pwm_channel);

/**
 * @brief  This function is mainly used to stop the PWM execution.
 * @param[in]  pwm_channel is PWM channel number. For more details about the parameter, please refer to #hal_pwm_channel_t.
 * @return    To indicate whether this function call is successful or not.
 *            If the return value is #HAL_PWM_STATUS_OK, it means success.
 *            If the return value is #HAL_PWM_STATUS_INVALID_PARAMETER, it means a wrong parameter is given. The parameter needs to be verified.
 * @par       Example
 * Sample code please refer to @ref Driver_Usage_Chapter
 * @sa  hal_pwm_stop()
 */

hal_pwm_status_t hal_pwm_stop(hal_pwm_channel_t pwm_channel);


/**
 * @brief This function is  used to get current frequency of the PWM ,the unit of frequency is Hz.
 * @param[in]  pwm_channel is PWM channel number. For more details about the parameter, please refer to #hal_pwm_channel_t.
 * @param[out]  frequency  is PWM output frequency.
 * @return    To indicate whether this function call is successful or not.
 *            If the return value is #HAL_PWM_STATUS_OK, it means success.
 *            If the return value is #HAL_PWM_STATUS_INVALID_PARAMETER, it means a wrong parameter is given. The parameter needs to be verified.
 * @par       Example
 * Sample code please refer to @ref Driver_Usage_Chapter
 * @sa  hal_pwm_set_frequency()
 */

hal_pwm_status_t hal_pwm_get_frequency(hal_pwm_channel_t pwm_channel, uint32_t *frequency);



/**
 * @brief  This function is  used to get the current duty cycle of the PWM.
 * @param[in]  pwm_channel is PWM channel number. For more details about the parameter, please refer to #hal_pwm_channel_t.
 * @param[out]   *duty_cycle is PWM hardware duty cycle, which is calculated based on application's  duty ratio times  hardware 's total count
 * @return    To indicate whether this function call is successful or not.
 *            If the return value is #HAL_PWM_STATUS_OK, it means success.
 *            If the return value is #HAL_PWM_STATUS_INVALID_PARAMETER, it means a wrong parameter is given. The parameter needs to be verified.
 * @par       Example
 * Sample code please refer to @ref Driver_Usage_Chapter
 * @sa  hal_pwm_set_duty_cycle()
 */

hal_pwm_status_t hal_pwm_get_duty_cycle(hal_pwm_channel_t pwm_channel, uint32_t *duty_cycle);


/**
 * @brief  This function is  used to get the current status of PWM.
 * @param[in]  pwm_channel is PWM channel number. For more details about the parameter, please refer to #hal_pwm_channel_t.
 * @param[out]  running_status is PWM busy or idle status ,For details about this parameter, please refer to #hal_pwm_running_status_t .
 * @return    To indicate whether this function call is successful or not.
 *            If the return value is #HAL_PWM_STATUS_OK, it means success.
 *            If the return value is #HAL_PWM_STATUS_INVALID_PARAMETER, it means a wrong parameter is given. The parameter needs to be verified.
 * @par       Example
 * Sample code please refer to @ref Driver_Usage_Chapter
 */

hal_pwm_status_t hal_pwm_get_running_status(hal_pwm_channel_t pwm_channel, hal_pwm_running_status_t *running_status);


#ifdef  HAL_PWM_FEATURE_ADVANCED_CONFIG

/**
 * @brief  This function sets the PWM advanced configuration.
 * @param[in]  pwm_channel is PWM channel number. For more details about the parameter, please refer to #hal_pwm_channel_t.
 * @param[in]   advanced_config is  PWM source clock division value, For more details about this parameter, please refer to #hal_pwm_advanced_config_t.
 * @return    To indicate whether this function call is successful or not.
 *            If the return value is #HAL_PWM_STATUS_OK, it means success.
 *            If the return value is #HAL_PWM_STATUS_INVALID_PARAMETER, it means a wrong parameter is given. The parameter needs to be verified.
 * @par       Example
 * Sample code please refer to @ref Driver_Usage_Chapter
 * @sa  hal_pwm_set_frequency(), hal_pwm_set_duty_cycle()
 */

hal_pwm_status_t hal_pwm_set_advanced_config(hal_pwm_channel_t pwm_channel, hal_pwm_advanced_config_t advanced_config);

#else

#endif


#ifdef __cplusplus
}
#endif


/**
* @}
* @}
*/


#endif /*HAL_PWM_MODULE_ENABLED*/
#endif /* __HAL_PWM_H__ */

