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
 
#ifndef __NVDM_H__
#define __NVDM_H__

/**
 * @addtogroup NVDM
 * @{
 * This section introduces the NVDM APIs including terms and acronyms,
 * supported features, software architecture, details on how to use the NVDM, enums, structures, typedefs and functions.
 *
 * @section NVDM_Terms_Chapter Terms and acronyms
 *
 * |        Terms         |           Details                |
 * |----------------------|----------------------------------|
 * |\b NVDM             | Non-volatile Data Management is a middleware used to store user's data. |
 *
 * @section NVDM_Features_Chapter Supported features
 *
 * - \b Support \b retaining \b data \b after \b power \b is \b off. \n
 *   NVDM stores user data in a flash memory, so the data is preserved even after power is off. \n
 * - \b Support \b grouping \b data \b items. \n
 *   NVDM defines group attribution for data item.
 *   The user can define different data items with different group names.
 *   This enables to classify many data items and keep them in order.
 *
 * @section NVDM_APIs_Usage_Chapter How to use NVDM APIs
 *
 * - To use the NVDM services follow the steps, as shown below. \n
 *  - Step1: Call nvdm_init() to initialize the NVDM module.
 *  - Step2: Call nvdm_write_data_item() to write or update user's data item to flash.
 *  - Step3: Call nvdm_read_data_item() to read user's data item from flash.
 *  - sample code:
 *    @code
 *       #define STA_IPADDR_DEFAULT_VALUE "192.168.0.1"
 *
 *       void nvdm_application(void)
 *       {
 *           nvdm_status_t status;
 *           uint32_t size;
 *           uint8_t buffer[16];
 *
 *           status = nvdm_init();
 *           status = nvdm_write_data_item("STA", "IpAddr", DATA_ITEM_TYPE_STRING, (uint8_t *)STA_IPADDR_DEFAULT_VALUE, sizeof(STA_IPADDR_DEFAULT_VALUE));
 *           status = nvdm_read_data_item("STA", "IpAddr", buffer, &size);
 *       }
 *    @endcode
 */

#include <stdint.h>
#include "nvdm_config.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup NVDM_enum Enum
  * @{
  */

/** @brief This enum defines the display type of a data item. */
typedef enum {
    NVDM_DATA_ITEM_TYPE_RAW_DATA = 0x01,   /**< Defines the display type with raw data. */
    NVDM_DATA_ITEM_TYPE_STRING = 0x02,     /**< Defines the display type with string. */
} nvdm_data_item_type_t;

/** @brief This enum defines return type of NVDM public APIs. */
typedef enum {
    NVDM_STATUS_INVALID_PARAMETER = -5,  /**< The user parameter is invalid. */
    NVDM_STATUS_ITEM_NOT_FOUND = -4,     /**< The data item wasn't found by the NVDM. */
    NVDM_STATUS_INSUFFICIENT_SPACE = -3, /**< No space is available in the flash. */
    NVDM_STATUS_INCORRECT_CHECKSUM = -2, /**< The NVDM found a checksum error when reading the data item. */
    NVDM_STATUS_ERROR = -1,              /**< An unclassified error occurred. */
    NVDM_STATUS_OK = 0,                  /**< Operation was successful. */
} nvdm_status_t;

/**
  * @}
  */

/**
 * @brief     This function initializes the NVDM module to enable using NVDM services.
 *            User must not call nvdm_read_data_item() or nvdm_write_data_item() before nvdm_init().
 *            Call nvdm_init() only once.
 *            Normally it is called to initialize a flow or a task.
 * @return
 *                #NVDM_STATUS_OK if OK. \n
 *                #NVDM_STATUS_ERROR if an unclassified error occurred. \n
 */
nvdm_status_t nvdm_init(void);

/**
 * @brief     This function is used to write or update a data item to flash.
 *            If there are existing data items on the flash, the NVDM invalidates old values and replaces with new ones.
 *            No other operation is performed while the data is being written to the flash.
 *            This function returns after the data is completely written to the flash.
 *            User must check the return status to verify the data is written to flash successfully.
 * @param[in] type   is type of data item, it decides how to display value.
 * @param[in] group_name   is group name of data item, for example user can define it to "Bluetooth".
 * @param[in] data_item_name   is the name of a data item, for example user can define it as "address" that belongs to "Bluetooth".
 * @param[in] buffer   is a pointer to the data item's content.
 * @param[in] size   is the size of the data item's content.
 * @return
 *                #NVDM_STATUS_OK if OK. \n
 *                #NVDM_STATUS_ERROR if an unclassified error occurred. \n
 *                #NVDM_STATUS_INVALID_PARAMETER if a parameter is invalid. \n
 *                #NVDM_STATUS_INSUFFICIENT_SPACE if a storage space is not enough. \n
 * @note      Call this API in tasks or function callbacks, but not in the interrupt handlers.
 */
nvdm_status_t nvdm_write_data_item(const char *group_name,
                                   const char *data_item_name,
                                   nvdm_data_item_type_t type,
                                   const uint8_t *buffer,
                                   uint32_t size);

/**
 * @brief     This function is used to read a data item from flash.
 *            If there is no such data item, NVDM returns an error.
 *            User must check the return status to verify the data read from flash is correct.
 * @param[in] group_name   is a group name of the data item, For example user can define it as "Bluetooth".
 * @param[in] data_item_name   is a name of the data item, For example user can define it as an "address" that belongs to "Bluetooth".
 * @param[out] buffer   is a pointer to user buffer, the NVDM copies the data item content into this buffer.
 * @param[inout] size   is the user buffer size when used as an input and is the size of actual data item's content read out when used as an output.
 * @return
 *                #NVDM_STATUS_OK if OK. \n
 *                #NVDM_STATUS_ERROR if an unclassified error occurred. \n
 *                #NVDM_STATUS_INVALID_PARAMETER if a parameter is invalid. \n
 *                #NVDM_STATUS_ITEM_NOT_FOUND if a data item is not found. \n
 *                #NVDM_STATUS_INCORRECT_CHECKSUM if the checksum of data item is invalid. \n
 * @note      Call this API in tasks or function callbacks, but not in the interrupt handlers.
 */
nvdm_status_t nvdm_read_data_item(const char *group_name,
                                  const char *data_item_name,
                                  uint8_t *buffer,
                                  uint32_t *size);

#ifdef __cplusplus
}
#endif

/**
* @}
*/

#endif /* __NVDM_H__ */

