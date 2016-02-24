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
 
#ifndef __HAL_I2C_MASTER_H__
#define __HAL_I2C_MASTER_H__
#include "hal_platform.h"

#ifdef HAL_I2C_MASTER_MODULE_ENABLED
/** 
 * @addtogroup HAL
 * @{
 * @addtogroup I2C_MASTER
 * @{
 *
 * @section HAL_I2C_Terms_Chapter Terms and acronyms
 * 
 * |Terms                         |Details                                                                 |
 * |------------------------------|------------------------------------------------------------------------|
 * |\b I2C                        | Inter-Integrated Circuit. I2C is typically used to attach low-speed peripheral ICs to processors and microcontrollers. For an introduction to I2C, please refer to <a href="https://en.wikipedia.org/wiki/I%C2%B2C"> I2C in Wikipedia</a>.|
 * |\b DMA                        | Direct Memory Access. For an introduction to DMA, please refer to <a href="https://en.wikipedia.org/wiki/Direct_memory_access"> DMA in Wikipedia</a>.|
 * |\b GPIO                       | General Purpose Inputs-Outputs. For more details, please refer to the @ref GPIO module in HAL. |
 * |\b NVIC                       | Nested Vectored Interrupt Controller. NVIC is the interrupt controller of ARM Cortex-M4. For more details, please refer to <a href="http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.100166_0001_00_en/ric1417175922867.html"> NVIC introduction in ARM Cortex-M4 Processor Technical Reference Manual</a>.|
 *
 * @section HAL_I2C_Features_Chapter Supported features
 *
 * - \b Polling \b mode \b transaction: 
 *    In polling mode, the functions with a postfix "_polling" won't return any value until the transaction is complete. 
 *    After the function returns, the return value should be checked to obtain the transaction result and invoke code to handle any error status values.
 *
 * - \b DMA \b mode \b transaction: 
 *    In DMA mode, the function will return a value once the I2C and DMA hardware registers are assigned. The related functions will not wait
 *    for the transaction to finish. After the transaction finishes, an interrupt will be triggered and the user callback in the I2C ISR
 *    routine called. After the function returns, the return value should be checked to obtain the transaction result and invoke code to
 *    handle any error status values.
 *     
 * @section HAL_I2C_Architecture_Chapter Software architecture of I2C
 * - \b Polling \b mode \b architecture. \n
 *   Polling mode architecture is similar to the polling mode architecture in HAL overview. See @ref HAL_Overview_3_Chapter for polling mode architecture.
 * - \b DMA \b mode \b architecture. \n
 *   DMA mode architecture is similar to the interrupt mode architecture in HAL overview. See @ref HAL_Overview_3_Chapter for interrupt mode architecture.
 *
 *
 * @section HAL_I2C_Driver_Usage_Chapter How to use this driver
 * - \b Using \b I2C \b polling \b mode.  \n
 *  To use I2C driver in a polling mode, configure GPIO pins to pinmux to SCL and SDA, then call
 *  #hal_pinmux_set_function to select the pinmux function. After setting the pinmux, call #hal_i2c_master_get_running_status() to check the I2C
 *  status. If the status is #HAL_I2C_STATUS_BUS_BUSY, wait till the status becomes #HAL_I2C_STATUS_IDLE. Once the data is successfully
 *  transmitted, call #hal_i2c_master_deinit() to release the I2C resource for other users. Steps are shown below:
 *  - Step1: Call #hal_pinmux_set_function() to set GPIO pinmux. 
 *  - Step2: Call #hal_i2c_master_init() to initialize one I2C master.
 *  - Step3: Call #hal_i2c_master_send_polling() to send data in a polling mode.
 *  - Step4: Call #hal_i2c_master_receive_polling() to receive data in a polling mode.
 *  - Step5: Call #hal_i2c_master_deinit() to de-allocate the I2C master if I2C is no longer in use.
 *  - Sample code:
 *    @code
 *       hal_pinmux_set_function(gpio_pin, function_index);//set pinmux
 *       if(HAL_I2C_STATUS_OK == hal_i2c_master_init(i2c_port, &i2c_config)) {
 *           ret = hal_i2c_master_send_polling(i2c_port, slave_address, data, size); //send data
 *           if (HAL_I2C_STATUS_OK != ret) {
 *               //error handle;
 *           }
 *           ret = hal_i2c_master_receive_polling(i2c_port, slave_address, data, size);//receive data
 *           if (HAL_I2C_STATUS_OK != ret) {
 *               //error handle;
 *           } 
 *           hal_i2c_master_deinit(i2c_port); // Must call de-initialize when not using I2C
 *           
 *       } else {
 *           //busy handle
 *       }
 *       
 *    @endcode
 *
 * - \b Using \b I2C \b DMA \b mode. \n
 *  To use I2C driver in DMA mode, configure GPIO pins to pinmux to SCL and SDA, then call
 *  #hal_pinmux_set_function to select the pinmux function. After setting the pinmux, call #hal_i2c_master_get_running_status() to check the I2C
 *  status. If the status is #HAL_I2C_STATUS_BUS_BUSY, user should wait till the status is #HAL_I2C_STATUS_IDLE, then
 *  call #hal_i2c_master_register_callback() to register a callback function. Once the data transaction is finished,
 *  call #hal_i2c_master_deinit() in your callback function which is registered by #hal_i2c_master_register_callback() to release the I2C resource to other users. Steps are shown below:
 *  - Step1: Call #hal_pinmux_set_function() to set GPIO pinmux. 
 *  - Step2: Call #hal_i2c_master_init() to initialize one I2C master.
 *  - Step3: Call #hal_i2c_master_register_callback() to register a user callback.
 *  - Step4: Call #hal_i2c_master_send_dma() to send data within a polling mode.
 *  - Step5: Call #hal_i2c_master_receive_dma() to receive data in a polling mode.
 *  - Step6: Call #hal_i2c_master_deinit() to de-initialize the I2C master if I2C is no longer in use.
 *  - Sample code:
 *    @code
 *       hal_pinmux_set_function(gpio_pin, function_index);//set pinmux
 *       if(HAL_I2C_STATUS_OK == hal_i2c_master_init(i2c_port, &i2c_config)) {
 *           hal_i2c_master_register_callback(i2c_port, i2c_callback, (void *) &user_data)// register a user callback.
 *           ret = hal_i2c_master_send_dma(i2c_port, slave_address, data, size); //send data
 *           if (HAL_I2C_STATUS_OK != ret) {
 *               //error handle;
 *           }
 *       } else {
 *           //busy handle

 *       }
 *       
 *    @endcode
 *    @code
 *       // Callback function sample code. This function should be passed to driver while call hal_i2c_master_register_callback.
 *       void user_i2c_callback (uint8_t slave_address,hal_i2c_callback_event_t event,void *user_data)
 *       {
 *           if(HAL_I2C_EVENT_ACK_ERROR == event) {
 *               //ack error handle;
 *           } else if(HAL_I2C_EVENT_NACK_ERROR == event) {
 *               //nack error handle;
 *           } else if(HAL_I2C_EVENT_TIMEOUT_ERROR == event) {
 *               // timeout handle;
 *           } else if(HAL_I2C_EVENT_SUCCESS == event) {
 *               // success handle;
 *               // slave_address can tell user which device is using I2C. 
 *               // if current transaction is data receiving, if I2C is no longer in use.
 *           }
 *           hal_i2c_master_deinit(i2c_port);// Must call de-initialize when it's no longer in use.
 *       }
 *       
 *    @endcode
 */

 


#ifdef __cplusplus
    extern "C" {
#endif


/***************************************************************************** 
* Enums
*****************************************************************************/

/** @defgroup hal_i2c_master_enum Enum
  * @{
  */  

/** @brief This enum defines the transaction result event. These results will be passed to user using a callback function. 
  *  Please refer #hal_i2c_master_register_callback() for more details. 
  */
typedef enum {
    HAL_I2C_EVENT_ACK_ERROR = -3,           /**<  An ACK error occurred during transaction. */ 
    HAL_I2C_EVENT_NACK_ERROR = -2,          /**<  A NACK error occurred during transaction.*/ 
    HAL_I2C_EVENT_TIMEOUT_ERROR = -1,       /**<  A timeout error occurred during transaction.*/ 
    HAL_I2C_EVENT_SUCCESS = 0               /**<  The transaction completed wihtout any error. */ 
}hal_i2c_callback_event_t;


/** @brief This enum define the HAL interface return value. */
typedef enum {
    HAL_I2C_STATUS_ERROR = -4,                        /**<  An error occurred and the transaction failed. */
    HAL_I2C_STATUS_ERROR_BUSY = -3,	                  /**<  I2C bus busy error is given. */
    HAL_I2C_STATUS_INVALID_PORT_NUMBER = -2,          /**<  A wrong port number is given. */ 
    HAL_I2C_STATUS_INVALID_PARAMETER = -1,             /**<  A wrong parameter is given. */ 
    HAL_I2C_STATUS_OK = 0                            /**<  No error occurred during the function call. */ 
}hal_i2c_status_t;

/** @brief This enum define the I2C bus status type. */
typedef enum { 
    HAL_I2C_STATUS_IDLE = 0,                         /**<  The I2C bus is idle. */ 
    HAL_I2C_STATUS_BUS_BUSY = 1                    /**<  The I2C bus is busy. */ 
}hal_i2c_running_type_t;

/** @brief This enum define the I2C transaction speed.  */
typedef enum {
    HAL_I2C_FREQUENCY_50K  = 0,          /**<  Transmit data with 50kbps. */ 
    HAL_I2C_FREQUENCY_100K = 1,          /**<  Transmit data with 100kbps. */ 
    HAL_I2C_FREQUENCY_200K = 2,          /**<  Transmit data with 200kbps. */ 
    HAL_I2C_FREQUENCY_400K = 3,          /**<  Transmit data with 400kbps. */ 
    HAL_I2C_FREQUENCY_MAX                /**<  Max transaction speed, don't use this value. */ 
}hal_i2c_frequency_t;

/**
  * @}
  */
  
/*****************************************************************************
* Structures                                                                  
*****************************************************************************/

/** @defgroup hal_i2c_master_struct Struct
  * @{
  */


/** @brief This structure define the config parameter to initialize an I2C master.  */
typedef struct{
    hal_i2c_frequency_t frequency;             /**<  The transfer speed. please refer to #hal_i2c_frequency_t for speed definition. */  
}hal_i2c_config_t;

/** @brief This structure define the I2C bus status type. */
typedef struct { 
    hal_i2c_running_type_t running_status;   /**<  The running status is defined in #hal_i2c_running_type_t */  
}hal_i2c_running_status_t;

#ifdef HAL_I2C_MASTER_FEATURE_SEND_TO_RECEIVE
/** @brief This structure defines the config parameter for send_to_receive transaction format. about send-to-receive format,please refer to @ref HAL_I2C_Features_Chapter for more details. */
typedef struct{
    uint8_t slave_address;                     /**<  slave device address. */ 
    const uint8_t *send_data;                  /**<  the data buffer to be sent. */ 
    uint32_t send_length;                      /**<   the length of data to send. */ 
    uint8_t *receive_buffer;                   /**<  the data buffer to receive. */ 
    uint32_t receive_length;                     /**<  the length of data to receive. */ 
}hal_i2c_send_to_receive_config_t;
#endif

/**
  * @}
  */
  
/** @defgroup hal_i2c_master_typedef Typedef
  * @{
  */

/** @brief  This defines the callback function prototype.
 *          User should register a callback function while using DMA mode.
 *          This function is called after the transaction finishes in the I2C ISR routine.
 *          For more details about the callback, please refer to #hal_i2c_master_register_callback().
 *          More details about callback architecture, please refer to @ref HAL_I2C_Architecture_Chapter.
 *  @param [in] slave_address is a user defined slave address to send or receive data.
 *  @param [in] event is the transaction event of current transaction. This parameter can tell user the transaction result. 
 *              For more details about the event type,please refer to #hal_i2c_callback_event_t.
 *  @param [in] user_data is the user defined parameter obtained from #hal_i2c_master_register_callback() function.
 *  @sa  #hal_i2c_master_register_callback()
 */
typedef void (*hal_i2c_callback_t)(uint8_t slave_address,hal_i2c_callback_event_t event,void *user_data);

/**
  * @}
  */

/*****************************************************************************
* Functions                                                                   
*****************************************************************************/


/**
 * @brief Initialize the I2C master before starting a transaction.
 * @param[in] i2c_port is the I2C master port number. The value is defined in #hal_i2c_port_t.
 * @param[in] i2c_config Is the configuration parameter to initialize I2C. Details are described at #hal_i2c_config_t.
 * @return #HAL_I2C_STATUS_INVALID_PORT_NUMBER means an invalid port number is given; \n
 *         #HAL_I2C_STATUS_INVALID_PARAMETER means an invalid transfer_frequency is given; \n
 *         #HAL_I2C_STATUS_OK means this function completed successfully.
 *         #HAL_I2C_STATUS_ERROR_BUSY means the I2C bus is in use.
 * @note   #hal_i2c_master_deinit() must be called when I2C is no longer in use, or the I2C resource will not be released and other users cannot
 *         use this I2C master.
 * @par       Example
 *    Sample code please refer to @ref HAL_I2C_Driver_Usage_Chapter
 * @sa #hal_i2c_master_deinit()
 */
hal_i2c_status_t hal_i2c_master_init(hal_i2c_port_t i2c_port, hal_i2c_config_t *i2c_config);


/**
 * @brief Release the I2C master after the transaction is over. User must call this function if I2C is no longer in use.
 * @param[in] i2c_port is the I2C master port number. The value is defined in #hal_i2c_port_t.
 * @return  #HAL_I2C_STATUS_INVALID_PORT_NUMBER means an invalid port number is given； \n
 *          #HAL_I2C_STATUS_OK means this function completed successfully.
 * @note   This function must be called when I2C is no longer in use, or the I2C resource will not be released and other users can
 *         not use this I2C master.
 * @par       Example
 *    Sample code please refer to @ref HAL_I2C_Driver_Usage_Chapter
 * @sa #hal_i2c_master_init()
 */
hal_i2c_status_t hal_i2c_master_deinit(hal_i2c_port_t i2c_port);


/**
 * @brief Set the transaction speed separately. User can use this function to change the transaction speed without using #hal_i2c_master_init().
 * @param[in] i2c_port is the I2C master port number. The value is defined in #hal_i2c_port_t.
 * @param[in] speed is an enum value defined in #hal_i2c_frequency_t. Only value of type #hal_i2c_frequency_t is accepted.
 * @return   #HAL_I2C_STATUS_INVALID_PORT_NUMBER means an invalid port number is given; \n
 *           #HAL_I2C_STATUS_INVALID_PARAMETER means an invalid speed is given; \n
 *           #HAL_I2C_STATUS_OK means this function completed successfully.
 *           #HAL_I2C_STATUS_ERROR_BUSY means the I2C bus is in use.
 * @par       Example
 * @code
 *       ret = hal_i2c_master_config_speed(HAL_I2C_MASTER_1,HAL_I2C_SPEED_400K);
 * @endcode
 * @sa #hal_i2c_master_init()
 */
hal_i2c_status_t hal_i2c_master_set_frequency(hal_i2c_port_t i2c_port, hal_i2c_frequency_t frequency);




/**
 * @brief Register the callback function while using DMA mode.
 *        The callback function will be called at I2C ISR routine after the I2C triggers an interrupt.
 *        Always call this function to register a callback function while using DMA mode.
 *        Refer to @ref HAL_I2C_Architecture_Chapter for DMA architecture.
 * @param[in] i2c_port is the I2C master port number. The value is defined in #hal_i2c_port_t.
 * @param[in] i2c_callback is the callback function given by user, which will be called at I2C ISR routine.
 * @param[in] user_data is a parameter given by user and will pass to user while the callback function is called. See the last parameter of #hal_i2c_callback_t.
 * @return   #HAL_I2C_STATUS_INVALID_PORT_NUMBER means an invalid port number is given; \n
 *           #HAL_I2C_STATUS_INVALID_PARAMETER means a NULL function pointer is given by user; \n
 *           #HAL_I2C_STATUS_OK means this function completed successfully.
 * @par       Example
 *    Sample code please refer to @ref HAL_I2C_Driver_Usage_Chapter
 */
hal_i2c_status_t hal_i2c_master_register_callback(hal_i2c_port_t i2c_port, hal_i2c_callback_t i2c_callback,void *user_data);


/**
 * @brief Send data to slave with polling mode.
 *  This function will not return until the transaction finishes. For more details about polling mode, please refer to polling mode of @ref
 *  HAL_I2C_Features_Chapter.
 * @param[in] i2c_port is the I2C master port number. The value is defined in #hal_i2c_port_t.
 * @param[in] slave_address is the I2C slave address.
 * @param[in] data is the data buffer to send.
 * @param[in] size is the data size to send. The maximum value is #HAL_I2C_MAXIMUM_POLLING_TRANSACTION_SIZE.
 * @return   #HAL_I2C_STATUS_INVALID_PORT_NUMBER means an invalid port number is given; \n
 *           #HAL_I2C_STATUS_INVALID_PARAMETER means a NULL buffer pointer is given by user; \n
 *           #HAL_I2C_STATUS_OK means this function completed successfully; \n
 *           #HAL_I2C_STATUS_ERROR means a hardware error occurred during the transaction.\n
 *           #HAL_I2C_STATUS_ERROR_BUSY means the I2C bus is in use.
 * @par       Example
 *    Sample code please refer to @ref HAL_I2C_Driver_Usage_Chapter
 * @sa #hal_i2c_master_send_dma()
 */
hal_i2c_status_t hal_i2c_master_send_polling(hal_i2c_port_t i2c_port, uint8_t slave_address,const uint8_t *data, uint32_t size);


/**
 * @brief Send data to slave with DMA mode.
 *  This function returns a value immediately after finishing setting the hardware register. For more details about DMA mode, please refer to @ref
 *  DMA mode of HAL_I2C_Features_Chapter.
 *  Note, not all masters support DMA mode. For more details about DMA mode please refer to #hal_i2c_port_t.
 * @param[in] i2c_port is the I2C master port number. The value is defined in #hal_i2c_port_t.
 * @param[in] slave_address is the I2C slave address.
 * @param[in] data is the data buffer to send.
 * @param[in] size is the data size to send. The maximum value is #HAL_I2C_MAXIMUM_DMA_TRANSACTION_SIZE.
 * @return   #HAL_I2C_STATUS_INVALID_PORT_NUMBER means an invalid port number is given; \n
 *           #HAL_I2C_STATUS_INVALID_PARAMETER means an NULL buffer pointer is given by user; \n
 *           #HAL_I2C_STATUS_OK means this function completed successfully; \n
 *           #HAL_I2C_STATUS_ERROR_BUSY means the I2C bus is in use.
 * @par       Example
 *    Sample code please refer to @ref HAL_I2C_Driver_Usage_Chapter
 * @sa #hal_i2c_master_send_polling()
 */
hal_i2c_status_t hal_i2c_master_send_dma(hal_i2c_port_t i2c_port, uint8_t slave_address, const uint8_t *data, uint32_t size);


/**
 * @brief Receive data from slave in a polling mode.
 *  This function will not return a value until the transaction is finished. For more details about polling mode, please refer to @ref
 *  polling mode of HAL_I2C_Features_Chapter.
 * @param[in] i2c_port is the I2C master port number. The value is defined in #hal_i2c_port_t.
 * @param[in] slave_address is the I2C slave address.
 * @param[out] buffer is the data buffer to receive.
 * @param[in] size is the data size to receive. The maximum value is #HAL_I2C_MAXIMUM_POLLING_TRANSACTION_SIZE.
 * @return   #HAL_I2C_STATUS_INVALID_PORT_NUMBER means an invalid port number is given; \n
 *           #HAL_I2C_STATUS_INVALID_PARAMETER means a NULL buffer pointer is given by user; \n
 *           #HAL_I2C_STATUS_OK means this function completed successfully; \n
 *           #HAL_I2C_STATUS_ERROR means a hardware error occurred during the transaction. \n
 *           #HAL_I2C_STATUS_ERROR_BUSY means the I2C bus is in use.
 * @par       Example
 *    Sample code please refer to @ref HAL_I2C_Driver_Usage_Chapter
 * @sa #hal_i2c_master_receive_dma()
 */
hal_i2c_status_t hal_i2c_master_receive_polling(hal_i2c_port_t i2c_port, uint8_t slave_address, uint8_t *buffer, uint32_t size);



/**
 * @brief Receive data from slave in a DMA mode.
 *  This function will return a value immediately after finishing setting the hardware register. For more details of DMA mode, please refer to @ref
 *  DMA mode of HAL_I2C_Features_Chapter.
 *  Note, not all masters support DMA mode. For more details about DMA mode, please refer to #hal_i2c_port_t.
 * @param[in] i2c_port is the I2C master port number. The value is defined in #hal_i2c_port_t.
 * @param[in] slave_address is the I2C slave address.
 * @param[out] buffer is the data buffer to receive. 
 * @param[in] size is the data size to receive. The maximum value is #HAL_I2C_MAXIMUM_DMA_TRANSACTION_SIZE.
 * @return   #HAL_I2C_STATUS_INVALID_PORT_NUMBER means an invalid port number is given; \n
 *           #HAL_I2C_STATUS_INVALID_PARAMETER means a NULL buffer pointer is given by user; \n
 *           #HAL_I2C_STATUS_OK means this function completed successfully; \n
 *           #HAL_I2C_STATUS_ERROR_BUSY means the I2C bus is in use.
 * @par       Example
 *    Sample code please refer to @ref HAL_I2C_Driver_Usage_Chapter
 * @sa #hal_i2c_master_receive_polling()
 */
hal_i2c_status_t hal_i2c_master_receive_dma(hal_i2c_port_t i2c_port, uint8_t slave_address, uint8_t  *buffer, uint32_t size);


#ifdef HAL_I2C_MASTER_FEATURE_SEND_TO_RECEIVE
/**
 * @brief This function will trigger a send to receive format in a polling mode after beginning the transaction.
 *  For more details about send to receive transaction format, please refer to send to receive transaction of @ref HAL_I2C_Features_Chapter.
 * @param[in] i2c_port is the I2C master port number. The value is defined in #hal_i2c_port_t.
 * @param[in] i2c_send_to_receive_config->slave_address is the I2C slave address.
 * @param[in] i2c_send_to_receive_config->send_data is the data buffer to be sent.
 * @param[in] i2c_send_to_receive_config->send_length is the length of data to send. The maximum value is #HAL_I2C_MAXIMUM_POLLING_TRANSACTION_SIZE.
 * @param[out] i2c_send_to_receive_config->receive_buffer is the data buffer to receive.
 * @param[in] i2c_send_to_receive_config->receive_length is the length of data to receive. The maximum value is #HAL_I2C_MAXIMUM_POLLING_TRANSACTION_SIZE.
 * @return   #HAL_I2C_STATUS_INVALID_PORT_NUMBER means an invalid port number is given; \n
 *           #HAL_I2C_STATUS_INVALID_PARAMETER means a NULL buffer pointer is given by user; \n
 *           #HAL_I2C_STATUS_OK means this function completed successfully; \n
 *           #HAL_I2C_STATUS_ERROR means a hardware error occurred during the transaction. \n
 *           #HAL_I2C_STATUS_ERROR_BUSY means the I2C bus is in use.
 * @par       Example
 *    Sample code please refer to @ref HAL_I2C_Driver_Usage_Chapter
 * @sa #hal_i2c_master_send_to_receive_dma()
 */
hal_i2c_status_t hal_i2c_master_send_to_receive_polling(hal_i2c_port_t i2c_port, hal_i2c_send_to_receive_config_t *i2c_send_to_receive_config);



/**
 * @brief This function will trigger a send to receive format in a DMA mode after the transaction has begun.
 *  For more details about send to receive transaction format, please refer to send to receive transaction of @ref HAL_I2C_Features_Chapter.
 *  Note, not all masters support DMA mode. For more details about DMA mode, please refer to DMA mode of #hal_i2c_port_t.
 * @param[in] i2c_port is the I2C master port number. The value is defined in #hal_i2c_port_t.
 * @param[in] i2c_send_to_receive_config->slave_address is the I2C slave address.
 * @param[in] i2c_send_to_receive_config->send_data is the data buffer to be sent.
 * @param[in] i2c_send_to_receive_config->send_length is the length of data to send. The maximum value is #HAL_I2C_MAXIMUM_POLLING_TRANSACTION_SIZE.
 * @param[out] i2c_send_to_receive_config->receive_buffer is the data buffer to receive.
 * @param[in] i2c_send_to_receive_config->receive_length is the length of data to receive. The maximum value is #HAL_I2C_MAXIMUM_DMA_TRANSACTION_SIZE.
 * @return   #HAL_I2C_STATUS_INVALID_PORT_NUMBER means an invalid port number is given; \n
 *           #HAL_I2C_STATUS_INVALID_PARAMETER means a NULL buffer pointer is given by user; \n
 *           #HAL_I2C_STATUS_OK means this function completed successfully; \n
 *           #HAL_I2C_STATUS_ERROR_BUSY means the I2C bus is in use.
 * @par       Example
 *    Sample code please refer to @ref HAL_I2C_Driver_Usage_Chapter
 * @sa #hal_i2c_master_send_to_receive_polling()
 */
hal_i2c_status_t hal_i2c_master_send_to_receive_dma(hal_i2c_port_t i2c_port, hal_i2c_send_to_receive_config_t *i2c_send_to_receive_config);

#endif /* #ifdef HAL_I2C_MASTER_FEATURE_SEND_TO_RECEIVE */



/**
 * @brief Get running status of the I2C master.
 *  Call this function to check if the I2C is idle or not before transferring data. If it's not idle, then the resource is currently in use, 
 *  delay the operation until the I2C is idle.
 * @param[in] i2c_port is the I2C master port number. The value is defined in #hal_i2c_port_t.
 * @param[out] running_status 
 *             #HAL_I2C_STATUS_BUS_BUSY means the I2C master is in busy status; \n
 *             #HAL_I2C_STATUS_IDLE means the I2C master is in idle status; User can use it to transmit data immediately.
 * @return   #HAL_I2C_STATUS_INVALID_PORT_NUMBER means an invalid port number is given; \n
 *           #HAL_I2C_STATUS_OK means this function completed successfully.
 * @par       Example
 *    Sample code please refer to @ref HAL_I2C_Driver_Usage_Chapter
 */
hal_i2c_status_t hal_i2c_master_get_running_status(hal_i2c_port_t i2c_port,hal_i2c_running_status_t *running_status);


#ifdef __cplusplus
}
#endif

/** 
* @} 
* @}
*/
#endif /*HAL_I2C_MASTER_MODULE_ENABLED*/
#endif /* __HAL_I2C_MASTER_H__ */ 

