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
 
#ifndef __HAL_ACCDET_H__
#define __HAL_ACCDET_H__
#include "hal_platform.h"

#ifdef	 HAL_ACCDET_MODULE_ENABLED

/**
 * @addtogroup HAL
 * @{
 * @addtogroup ACCDET
 * @{
 * This section describes the programming interfaces of ACCDET HAL driver.
 * The hardware accessory detector (ACCDET) detects states of earphone (plug-in/plug-out/hook-key), based on the suggested circuit. The de-bounce scheme is also supported to resist uncertain input noises. When the state is stable, the PWM unit of ACCDET will enable the comparator, MBIAS and threshold voltage of the comparator periodically for the plugging detection. With suitable PWM settings, very low-power consumption can be achieved when the detection feature is enabled. In order to compensate the delay between the detection login and comparator, the delay enabling scheme is adopted. Given the suitable delay number compared to the rising edge of PWM high pulse, the stable plugging state can be prorogated to digital detection logic. Then the correct plugging state can be detected and reported.
 *
 * @section HAL_ACCDET_Terms_Chapter Terms and acronyms
 *
 * The following provides descriptions to the terms commonly used in the ACCDET driver and how to use the various functions.
 *
 * |Terms                   |Details                                                                 |
 * |------------------------------|------------------------------------------------------------------------|
 * |\b ACCDET                     | Accessory detector which is designed to detect plug-in/out of multiple types of external components.|
 * |\b PWM                        | Pulse Width Modulation (PWM) is a modulation technique used to encode a message into a pulsing signal and whose main use is to allow the control of the power supplied to electrical devices, especially to inertial loads such as motors. For more information, please refer to <a href="https://en.wikipedia.org/wiki/Pulse-width_modulation"> PWM in Wikipedia</a>.|
 * For PWM, the term duty cycle describes the proportion of 'on' time to the regular interval or 'period' of time; a low duty cycle corresponds to low power, because the power is off for most of the time. Duty cycle is expressed in percent, 100% being fully on.
 *
 * @section HAL_ACCDET_Features_Chapter Supported features
 * As described above, to perform an accurate detection, the debounce time and proper PWM setting are supported. The supported features of ACCDET driver are listed below: \n
 * - \b Set \b debounce \b time \b separately \b for \b plug-in/plug-out/hook-key. \n
 *   The API dedicated for debounce time setting is hal_accdet_set_debounce_time(), and the parameter is type #hal_accdet_debounce_time_t, the fields of which contains accdet_plug_in_debounce, accdet_plug_out_debounce as well as accdet_hook_key_debounce. User can adjust the three fields according to the sensitivity of the specific hardware circuit. Also, the debounce time can be set by calling the API hal_accdet_init(), other than the debounce, the setting of PWM which will showed below is supported as well.
 *
 * - \b Set \b parameters \b for \b internal \b PWM. \n
 *   User can set PWM parameters such as with, threshold, and delay, by calling the API hal_accdet_init(). As PWM counter frequency is 32K HZ, thus the PWM output frequency is (32K/PWM width) HZ and the output duty cycle is (PWM threshold)*(1/32) ms.
 * - \b Callback \b function \b registration. \n
 *   When the state of the plugged external component changed, a interrupt will be triggered. Users could register their own call back function, by calling hal_accdet_register_callback(). The registered callback function will be invoked in the ACCDET ISR routine when the interrupt is triggered.
 *
 * @section ACCDET_Driver_Usage_Chapter How to use this driver
 *
 *  - \b Configure \b ACCDET \b module \b for \b external \b components \b detection. \n
 *  Before the ACCDET module is enabled for earphone detection, user should configure the internal PWM, the debounce time for all three states, and the callback function should be registered as well. The function hal_accdet_set_debounce_time() could be called anytime , to adjust the debounce time to a proper value. The Steps below should be followed:
 *   - Step1: Call hal_accdet_init() to initialize the ACCDET module, parameters for PWM and debounce time are both included.
 *   - Step2: Call hal_accdet_register_callback() to register a callback function.
 *   - Step3: Call hal_accdet_enable() to enable the ACCDET module.
 *   - sample code:
 *   @code
 *
 *   hal_accdet_config_t accdet_config;
 *   uint32_t user_data;
 *   void accdet_user_callback(hal_accdet_callback_event_t event, void *user_data);
 *
 *   accdet_config.accdet_pwm_width = 0x1900;//Set PWM width
 *   accdet_config.accdet_pwm_threshold = 0x0400;//Set PWM threshold, should be smaller than PWM width.
 *   accdet_config.accdet_pwm_delay = 0x8180;//Set PWM delay
 *   accdet_config.accdet_debounce.accdet_hook_key_debounce = 0x2652;//Set debounce time for hook key
 *   accdet_config.accdet_debounce.accdet_plug_in_debounce = 0x3FDE;//Set debounce time for plug in
 *   accdet_config.accdet_debounce.accdet_plug_out_debounce = 0x1FEF;//Set debounce time for plug out
 *
 *   hal_accdet_init(&accdet_config);//Configure PWM and debounce time
 *   hal_accdet_register_callback(accdet_user_callback, (void *)&user_data);//Register callback function
 *   hal_accdet_enable();//Enable ACCDET
 *
 *   hal_accdet_disable();//Disable ACCDET module
 *   hal_accdet_deinit();//Deinit ACCDET module
 *
 *   @endcode
 *
 *  - \b Modify \b debounce \b time \b for \b external \b components \b detection. \n
 *  By calling hal_accdet_set_debounce_time(), the debounce time of ACCDET module can be modified. After the debounce time is set, the ACCDET will work with debounce time newly set. Sample code is showed below:
 *  @code
 *
 *  hal_accdet_debounce_time_t debounce_time;
 *
 *  debounce_time.accdet_hook_key_debounce = 0x2652;//Set debounce time for hook key
 *  debounce_time.accdet_plug_in_debounce = 0x1000;//Set debounce time for plug in
 *  debounce_time.accdet_plug_out_debounce = 0x1FEF;//Set debounce time for plug out
 *  hal_accdet_set_debounce_time(&debounce_time);
 *
 *  @endcode
 */



#ifdef __cplusplus
extern "C" {
#endif


/*****************************************************************************
 * Enums
 *****************************************************************************/

/** @defgroup hal_accdet_enum Enum
 *  @{
 */

/** @brief This enum defines the ACCDET EVENT type.  */
typedef enum {
    HAL_ACCDET_EVENT_HOOK_KEY = 0,             /**< ACCDET event hook key */
    HAL_ACCDET_EVENT_PLUG_IN = 1,              /**< ACCDET event plug in */
    HAL_ACCDET_EVENT_ERROR = 2,                /**< ACCDET event error */
    HAL_ACCDET_EVENT_PLUG_OUT = 3              /**< ACCDET event plug out */
} hal_accdet_callback_event_t;


/** @brief This enum defines the ACCDET status type.  */
typedef enum {
    HAL_ACCDET_STATUS_ERROR = -1,              /**< ACCDET status error */
    HAL_ACCDET_STATUS_OK = 0                   /**< ACCDET status ok */
} hal_accdet_status_t;

/**
 * @}
 */

/*****************************************************************************
 * Structures
 *****************************************************************************/

/** @defgroup hal_accdet_struct Struct
 *  @{
 */

/** @brief ACCDET debounce time*/
typedef struct {
    uint16_t accdet_hook_key_debounce;          /**< ACCDET hook key debounce time */
    uint16_t accdet_plug_in_debounce;           /**< ACCDET plug in debounce time */
    uint16_t accdet_plug_out_debounce;          /**< ACCDET plug out debounce time */
} hal_accdet_debounce_time_t;


/** @brief ACCDET config, the configuration of internal PWM and the debounce time are both included in the structure.*/
typedef struct {
    uint16_t accdet_pwm_width;                  /**< ACCDET PWM width */
    uint16_t accdet_pwm_threshold;              /**< ACCDET PWM threshold */
    uint16_t accdet_pwm_delay;                  /**< ACCDET PWM delay */
    hal_accdet_debounce_time_t accdet_debounce; /**< ACCDET debounce time */
} hal_accdet_config_t;

/**
 * @}
 */

/** @defgroup hal_accdet_typedef Typedef
 *  @{
 */

/** @brief ACCDET callback typedef, when the plug state changed, the interrupt will be triggered and this registered callback will be invoked.*/
typedef void (*hal_accdet_callback_t)(hal_accdet_callback_event_t event, void *user_data);

/**
 * @}
 */

/*****************************************************************************
 * Functions
 *****************************************************************************/

/**
 * @brief 	ACCDET initialize function, the internal PWM and debounce time are both configured.
 * @param[in] accdet_config is the config information of ACCDET, see the structure #hal_accdet_config_t.
 * @return
 * #HAL_ACCDET_STATUS_ERROR, ACCDET module init failed. \n
 * #HAL_ACCDET_STATUS_OK, ACCDET module init success.
 */
hal_accdet_status_t hal_accdet_init(hal_accdet_config_t *accdet_config);


/**
 * @brief  ACCDET deinit function.
 * @return
 * #HAL_ACCDET_STATUS_OK, ACCDET deinit success.
 */
hal_accdet_status_t hal_accdet_deinit(void);


/**
 * @brief 	ACCDET enable function. Enable the ACCDET module.
 * @return
 * #HAL_ACCDET_STATUS_OK, ACCDET enable success.
 */
hal_accdet_status_t hal_accdet_enable(void);


/**
 * @brief 	ACCDET disable function. Disable the ACCDET module.
 * @return
 * #HAL_ACCDET_STATUS_OK, ACCDET disable success.
 */
hal_accdet_status_t hal_accdet_disable(void);


/**
 * @brief 	register callback function for ACCDET interrupt.
 * @param[in] accdet_callback is the pointer of ACCDET callback function.
 * @param[in] user_data is the user data of callback function.
 * @return
 * #HAL_ACCDET_STATUS_OK, the callback function of ACCDET is registered successfully.
 */
hal_accdet_status_t hal_accdet_register_callback(hal_accdet_callback_t accdet_callback, void *user_data);


/**
 * @brief 	set debounce time for ACCDET.
 * @param[in] debounce_time is the debounce value of ACCDET.
 * @return
 * #HAL_ACCDET_STATUS_OK, the debounce time of ACCDET is set successfully.
 */
hal_accdet_status_t hal_accdet_set_debounce_time(hal_accdet_debounce_time_t *debounce_time);


#ifdef __cplusplus
}
#endif

/**
 * @}
 * @}
*/

#endif /*HAL_ACCDET_MODULE_ENABLED*/

#endif /* __HAL_ACCDET_H__ */

