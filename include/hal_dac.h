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
 
#ifndef __HAL_DAC_H__
#define __HAL_DAC_H__
#include "hal_platform.h"

#ifdef HAL_DAC_MODULE_ENABLED

/**
 * @addtogroup HAL
 * @{
 * @addtogroup DAC
 * @{
 * This section describes the programming interfaces of the DAC HAL driver.
 *
 * @section HAL_DAC_Terms_Chapter Terms and acronyms
 *
 * The following provides descriptions to the terms commonly used in the DAC driver and how to use the various functions.
 *
 * |Terms                   |Details                                                                 |
 * |------------------------------|------------------------------------------------------------------------|
 * |\b DAC                        | DAC is a Digital-to-Analog Converter that converts digital data (usually binary) into an analog signal (current, voltage, or electric charge). |
 *
 * @section HAL_DAC_Features_Chapter Supported features
 * The general purpose DAC play a role like waveform generator. Resolution of DAC is 10 bit. Features supported by this module are listed below:
 * - \b Write \b data \b for \b output. \n
 *   Before the DAC data output is enabled, data for output is written into the internal ram dedicated for DAC, which can keep 128 data at most. User can write the DAC data to ram by calling the function hal_dac_write_data().
 * - \b Configure \b data \b output. \n
 *   Data which is written into internal ram can be outputted as waveform. By calling the function hal_dac_configure_output(), user can set the output mode as either repeat mode or no repeat mode, with the first parameter "mode "set HAL_DAC_REPEAT_MODE or HAL_DAC_NO_REPEAT_MODE. The parameter "start_address" and "end_address" together indicate the data range that will be outputted.
 * - \b Start (Stop) \b data \b output. \n
 *   When the hal_dac_start_output() is called, DAC data is output in repeat mode or no repeat mode as user configured. The output will be stopped when the hal_dac_stop_output() is called.
 * @section HAL_DAC_Driver_Usage_Chapter How to use this driver
 * - \b Use \b DAC \b driver \b to \b output \b analog \b waveform.
 *   - Step1: Call hal_dac_init() to initialize the DAC module.
 *   - Step2: Call hal_dac_write_data() to write data that will be outputted to the internal ram.
 *   - Step3: Call hal_dac_configure_output() to configure the data range and output mode(repeat or no repeat).
 *   - Step4: Call hal_dac_start_output() to start the data conversion.
 *   - Step5: Call hal_dac_stop_output() to stop the data conversion if needed.
 *   - Sample code:
 *   @code
 *
 *   #define DATA_LEN  5
 *
 *   uint8_t start_address = 0;
 *   uint16_t data[DATA_LEN] = {0x0010, 0x0011, 0x0012, 0x0013, 0x0014};
 *
 *   hal_dac_init();//Initialize DAC module.
 *   hal_dac_write_data(start_address, data, DATA_LEN);//Write DAC data to internal ram.
 *   hal_dac_configure_output(HAL_DAC_REPEAT_MODE, start_address, start_address+DATA_LEN);//Configure the DAC output mode.
 *   hal_dac_start_output();//Start DAC conversion.
 *   hal_dac_stop_output();//Stop DAC if needed.
 *   hal_dac_deinit();//De-initialize DAC module.
 *
 *   @endcode
 *
 */



#ifdef __cplusplus
extern "C" {
#endif


/*****************************************************************************
 * Enums
 *****************************************************************************/

/** @defgroup hal_dac_enum Enum
 *  @{
 */

/** @brief This enum defines the DAC API return status*/
typedef enum {
    HAL_DAC_STATUS_INVALID_PARAMETER = -2,      /**< Invalid parameter */
    HAL_DAC_STATUS_ERROR = -1,                  /**< DAC error */
    HAL_DAC_STATUS_OK = 0                       /**< DAC ok */
} hal_dac_status_t;

/** @brief This enum defines the DAC output mode*/
typedef enum {
    HAL_DAC_REPEAT_MODE = 0,                    /**< DAC output in repeat mode */
    HAL_DAC_NO_REPEAT_MODE = 1                  /**< DAC output in non repeat mode */
} hal_dac_mode_t;

/**
 * @}
 */


/*****************************************************************************
 * Functions
 *****************************************************************************/

/**
 * @brief 	DAC init function.
 * @return
 * #HAL_DAC_STATUS_OK, DAC initialize success.
 */
hal_dac_status_t hal_dac_init(void);


/**
 * @brief 	DAC deinit function, This function resets the DAC peripheral registers to their default values.
 * @return
 * #HAL_DAC_STATUS_OK, DAC deinit success.
 */
hal_dac_status_t hal_dac_deinit(void);


/**
 * @brief 	Start the DAC data conversion, when this function is called, the data write into the internal ram will be output as analog waveform.
 * @return
 * #HAL_DAC_STATUS_OK, DAC start output success.
 */
hal_dac_status_t hal_dac_start_output(void);

/**
 * @brief 	Stop the DAC data conversion, when this function is called, the data conversion of DAC is stopped.
 * @return
 * #HAL_DAC_STATUS_OK, DAC stop output success.
 */
hal_dac_status_t hal_dac_stop_output(void);

/**
 * @brief 	Write data into the internal ram, prepared to be converted as analog waveform.
 * @param[in] start_address is the address for the data to be saved, should be 0~127.
 * @param[in] data is the base address of the data that will be written into the internal ram.
 * @param[in] length is the length of the data will be written.
 * @return
 * #HAL_DAC_STATUS_INVALID_PARAMETER, which indicates that either start_address or start_address add length is larger than 127. \n
 * #HAL_DAC_STATUS_ERROR, data write to internal ram failed. \n
 * #HAL_DAC_STATUS_OK, data write to internal ram successfully.
 */
hal_dac_status_t hal_dac_write_data(uint8_t start_address, uint16_t *data, uint8_t length);


/**
 * @brief 	This function configures the output mode of the DAC as well as the data range that will be outputted.
 * @param[in] mode is the output mode of DAC, the mode is either repeat mode or no repeat mode, the parameter should be of type #hal_dac_mode_t.
 * @param[in] start_address is the base address of the internal ram that contains the data will be converted.
 * @param[in] end_address is the end address of data in the internal ram.
 * @return
 * #HAL_DAC_STATUS_INVALID_PARAMETER, the start_address or end_address is invalid. \n
 * #HAL_DAC_STATUS_ERROR, the DAC output configure failed. \n
 * #HAL_DAC_STATUS_OK, the DAC output configure successfully.
 * @note
 * User should make sure that both the start_address and end_address are both smaller than 127.
 */
hal_dac_status_t hal_dac_configure_output(hal_dac_mode_t mode, uint8_t start_address, uint8_t end_address);


#ifdef __cplusplus
}
#endif

/**
 * @}
 * @}
*/
#endif /*HAL_DAC_MODULE_ENABLED*/
#endif /* __HAL_DAC_H__ */

