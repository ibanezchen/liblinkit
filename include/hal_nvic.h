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
 
#ifndef __HAL_NVIC_H__
#define __HAL_NVIC_H__
#include "hal_platform.h"

#ifdef HAL_NVIC_MODULE_ENABLED

/** 
 * @addtogroup HAL
 * @{
 * @addtogroup NVIC
 * @{
 * This section introduces the NVIC HAL APIs including terms and acronyms, details on how to use this driver, supported features, enums, structures and functions.
 * NVIC usage follows the CMSIS except it doesn't support direct registration of ISR in the vector table, but it uses
 * #hal_nvic_register_isr_handler function to improve software efficiency and debugging.
 *
 * @section Terms_Chapter Terms and acronyms
 * 
 * |Terms                   |Details                                                                 |
 * |------------------------|------------------------------------------------------------------------|
 * |\b  NVIC                 | Nested Vectored Interrupt Controller. NIVC is the interrupt controller of ARM Cortex-M4. For more details, please refer to <a href="http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.100166_0001_00_en/ric1417175922867.html"> NVIC introduction in ARM Cortex-M4 Processor Technical Reference Manual </a>.|
 * |\b ISR                  | Interrupt service routine.|
 * |\b IRQ                  | Interrupt request.|
 *
 *
 * 
 * @section Driver_Usage_Chapter How to use this driver
 *    
 * - Use NVIC. \n
 *
 *  - Step1: Call hal_nvic_init() function to initialize the NVIC IRQ priority according to the exception number. By default, the lower the exception number the higher is the priority.
 *  - Step2: Call hal_nvic_register_isr_handler() function to register an ISR handler before using NVIC IRQ. 
 *  - Step3: Use CMSIS interface to adjust IRQ priority if needed.
 *  - Step4: Use NVIC_EnableIRQ() to enable the IRQ.
 *  - Sample code:
 *    @code
 *       ret = hal_nvic_init();    //should be done once and only once at init stage 
 *       if (HAL_NVIC_STATUS_OK != ret) {
 *               //error handle;
 *       }
 *       ret = hal_nvic_register_isr_handler(irq_number, isr_handler);   //register IRQ handler.
 *       if (HAL_NVIC_STATUS_OK !=  ret) {
 *               //error handle;
 *       }
 *       NVIC_EnableIRQ(irq_number);
 *
 *      //Change IRQ priority optional 
 *       NVIC_DisableIRQ(irq_number);   //disable IRQ irq_number
 *       NVIC_SetPriority(irq_number);  // change the priority of IRQ irq_number if needed
 *       NVIC_EnableIRQ(irq_number);    //enable IRQ irq_number  
 *    @endcode
 *
 */


#ifdef __cplusplus
    extern "C" {
#endif


/** @defgroup hal_nvic_enum Enums
  * @{
  */

/** @brief  This enum defines the return status of the NVIC API.  */
typedef enum {
    HAL_NVIC_STATUS_ERROR_NO_ISR = -4,              /**< ISR routine is null */
    HAL_NVIC_STATUS_ERROR_IRQ_NUMBER  = -3,         /**< Incorrect IRQ number */
    HAL_NVIC_STATUS_INVALID_PARAMETER = -2,         /**< Invalid parameter */
    HAL_NVIC_STATUS_ERROR             = -1,         /**< NVIC unspecified error */
    HAL_NVIC_STATUS_OK                = 0           /**< NVIC ok */
}hal_nvic_status_t;


/**
  * @}
  */


/** @defgroup hal_nvic_typedef Typedef
  * @{
  */    
/** @brief  This defines the callback function prototype.
 *          User should register an ISR for evrey NVIC IRQ used;
 *          This function is called in the NVIC ISR after the NVIC IRQ is triggered.
 *          More details about the callback, please refer to hal_nvic_register_isr_handler().
 *  @param [in] irq_number is given by driver to notify the current NVIC IRQ.
 */
typedef void (*hal_nvic_isr_t)(hal_nvic_irq_t irq_number);
/**
  * @}
  */
  

/*****************************************************************************
* Functions
*****************************************************************************/

/**
 * @brief This function is used to register an ISR for NVIC IRQ.
 * @param[in] irq_number is the NVIC IRQ number, please refer to #hal_nvic_irq_t.
 * @param[in] isr_handler is the NVIC IRQ's ISR.
 * @return    To indicate whether this function call is successful. 
 *            If the return value is #HAL_NVIC_STATUS_OK, it means success;
 *            If the return value is #HAL_NVIC_STATUS_INVALID_PARAMETER, it means a wrong parameter is given, the parameter must be verified.
 */
hal_nvic_status_t hal_nvic_register_isr_handler(hal_nvic_irq_t irq_number, hal_nvic_isr_t isr_handler);


/**
 * @brief This function is used to initialize the NVIC IRQ with default priority. By default the exception number is lower and priority is higher.
 */
hal_nvic_status_t hal_nvic_init(void);


#ifdef __cplusplus
}
#endif


/** 
* @} 
* @}
*/

#endif /*HAL_NVIC_MODULE_ENABLED*/
#endif /* __HAL_NVIC_H__ */

