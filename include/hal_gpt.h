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
 
#ifndef __HAL_GPT_H__
#define __HAL_GPT_H__
#include "hal_platform.h"

#ifdef HAL_GPT_MODULE_ENABLED

/** 
 * @addtogroup HAL
 * @{
 * @addtogroup GPT
 * @{
 * This section introduces and describes the terms and acronyms, supported features, software architecture, GPT function groups, enums, 
 * structures and functions, and details on how to use the GPT driver.
 *
 * @section HAL_GPT_Terms_Chapter Terms and acronyms
 * 
 * |Terms                         |Details                                                                 |
 * |------------------------------|------------------------------------------------------------------------|
 * |\b GPT                        | General Purpose Timer(GPT) is used as an alram clock to hanlde some events.|
 * |\b NVIC                       | The Nested Vectored Interrupt Controller (NVIC) is the interrupt controller of ARM Cortex-M. For more details, please refer to <a href="http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.100166_0001_00_en/ric1417175922867.html"> NVIC introduction in ARM Cortex-M4 Processor Technical Reference Manual </a>.|
 * 
 * @section HAL_GPT_Features_Chapter Supported features
 * 
 * This controller has a generic design to support various combinations of the timer functionality.
 *
 * - \b Support \b oneshot \b repeat \b and \b free \b run \b modes.\n
 *   A timer can be configured as one of the modes, oneshot mode, repeat mode and free run mode. The timer mode is configured through the mode configuration.
 *  - \b Oneshot \b mode: In this mode, the interrupt is triggered once when the timer expires.
 *  - \b Repeat \b mode: In this mode, the interrupt is triggered when the timer expires. At the same time, 
 *                       the timer is reloaded again with the same value and starts ticking for the next expiration. 
 *                       This pattern repeats until the timer is cancelled.
 *                       This mode is useful for handling functions that are executed periodically.\n
 *  - \b Free \b run \b mode: In this mode, the timer simply becomes a counter. There is no interrupt to be triggered in this mode. 
 *                            The counter keeps running once call #hal_gpt_get_free_run_count() and never stop.
 *                            User can use #hal_gpt_get_free_run_count() to get the stamp of the counter ticks.                    
 *                            This mode is useful as a reference for the scenarios such as delay or counting.\n
 *  .
 * @} 
 * @}
 */
#ifdef HAL_GPT_FEATURE_US_TIMER
/** 
 * @addtogroup HAL
 * @{
 * @addtogroup GPT
 * @{
 * - \b Support \b delay \b function. \n
 *   GPT driver supports millisenconds #hal_gpt_delay_ms() and microseconds #hal_gpt_delay_us() delay. 
 *   It utilizes the free run mode of the timer and the polling mechanism to determine if the timeout for the timer has been reached.\n
 *   Delay function is a hardware delay, it's for some programs to delay for sometime without the need for the context switch.\n
 * - \b Support \b callback \b function \b registration. \n
 *   A callback function must be registered using #hal_gpt_register_callback(), 
 *   then calling #hal_gpt_start_timer_ms() or #hal_gpt_start_timer_us() to set the oneshot mode or the repeat mode, and to start the timer.\n 
 *   The callback function is called after the GPT triggers an interrupt in the GPT ISR routine.\n
 * @} 
 * @}
 */
#else
/** 
 * @addtogroup HAL
 * @{
 * @addtogroup GPT
 * @{
 * - \b Support \b delay \b function. \n
 *   GPT driver supports milliseconds #hal_gpt_delay_ms(). 
 *   It utilizes the free run mode of the timer and the polling mechanism to determine if the timeout for the timer has been reached.\n
 *   The delay function is a hardware delay. It is for some programs to delay for sometime without the need for the context switch. \n
 * - \b Support \b callback \b function \b registration. \n
 *   A callback function must be registered using #hal_gpt_register_callback() function, 
 *   then calling #hal_gpt_start_timer_ms() to set the oneshot mode or the repeat mode, and to start the timer.\n 
 *   The callback function is called after the GPT triggers an interrupt in the GPT ISR routine. \n
 * @} 
 * @}
 */
#endif
/** 
 * @addtogroup HAL
 * @{
 * @addtogroup GPT
 * @{
 * @section HAL_GPT_Driver_Usage_Chapter How to use this driver
 * 
 * - \b Using \b GPT \b oneshot \b or \b repeat \b mode.\n
 *    Call #hal_gpt_get_running_status() function to manually check the GPT status before using the GPT driver in oneshot or repeat mode.
 *    If the status is #HAL_GPT_RUNNING, user should wait till the status is #HAL_GPT_STOPPED. 
 *    Call #hal_gpt_init() then #hal_gpt_start_timer_ms() functions to set the GPT mode and expiration time. 
 *    The timer then starts ticking. Once the pre-set time expires in a oneshot mode, the GPT triggers an interrupt, stops the timer, and calls user's callback function. 
 *    In a repeat mode, when the set time expires, the timer is reloaded with the set time and the user callback function is invoked.
 *    To ensure the precise timing, do not overload the callback function. Let the callback return as quick as possible.
 *  - Step1: Call #hal_gpt_get_running_status() to get the current running status.
 *  - Step2: Call #hal_gpt_init() to configure the base environment.
 *  - Step3: Call #hal_gpt_register_callback() to register a callback function.
 *  - Step3: Call #hal_gpt_start_timer_ms() to set the timer mode and the expiration time, and start the timer.
 *  - Step4: Call #hal_gpt_stop_timer() to stop timer.
 *  - Step5: Call #hal_gpt_deinit() to de-initilize the GPT module if it's no longer in use.
 *  - Sample code:
 *    @code
 *       hal_gpt_running_status_t running_status;
 *       hal_gpt_status_t         ret_status;
 *       hal_gpt_port_t           gpt_port;
 *
 *       gpt_port = HAL_GPT_PORT_0; 
 *       hal_gpt_get_running_status(HAL_GPT_PORT_0,&running_status);        //get running status to check if this port is used or idle.
 *       if ( running_status != HAL_GPT_STOPPED ) {                         //if timer is running, exception handle
 *          //exception handler
 *       }
 *       ret_status = hal_gpt_init(gpt_port);                               //set the GPT base environment.
 *       if(HAL_GPT_STATUS_OK != ret_status) {
 *          //error handler
 *       }
 *       hal_gpt_register_callback(gpt_port, user_gpt_callback,&user_data); //register a user callback.
 *       hal_gpt_start_timer_ms(gpt_port, 10, HAL_GPT_TIMER_TYPE_ONE_SHOT); //set 10ms timeout, set oneshot mode, and start timer.
 *       //if in repeat mode, please call hal_gpt_start_timer_ms(gpt_port, 10, HAL_GPT_TIMER_TYPE_REPEAT);
 *       //....                                                     
 *    @endcode
 *    @code
 *       // Callback function. This function should be registered with #hal_gpt_register_callback().
 *       void user_gpt_callback (void *user_data)
 *       {
 *           // user's handler
 *           hal_gpt_stop_timer(gpt_port);                                    //stop timer.
 *           hal_gpt_deinit(gpt_port);                                        //if it's no longer in use.
 *       }
 *       
 *    @endcode
 * @} 
 * @}
 */
 #ifdef HAL_GPT_FEATURE_US_TIMER
/** 
 * @addtogroup HAL
 * @{
 * @addtogroup GPT
 * @{
 *  - For mode in microseconds, the #hal_gpt_start_timer_us() works the same way as with #hal_gpt_start_timer_ms().
 * @} 
 * @}
 */
 #endif
 
/** 
 * @addtogroup HAL
 * @{
 * @addtogroup GPT
 * @{
 * - \b Using \b GPT \b in \b free \b run \b mode. \n
 *    Call #hal_gpt_get_free_run_count() function to get the first stamp of timer ticks.
 *    Call #hal_gpt_get_free_run_count() function again to get the second stamp of timer ticks.
 *    When you use HAL_GPT_CLOCK_SOURCE_32K parameter, the unit of tick is 1/32768 second.
 *    The different value between the first and the second stamp is the counting ticks.
 *    In a free run mode, the GPT runs continuously and never stop. It do not provide interrupt feature.
 *    The GPT driver also uses this function implementation such as delay function #hal_gpt_delay_ms().
 *  - Step1: Call #hal_gpt_get_free_run_count() to get the first current count.
 *  - Step2: Call #hal_gpt_get_free_run_count() to get the sencond current count.
 *  - Sample code:
 *    @code
 *       hal_gpt_status_t         ret_status;
 *       uint32_t                 count1, count2, duration_count;
 *       uint32_t                 time;
 *       
 *        //get the first value.
 *       ret_status = hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_32K, &count1); 
 *       if(HAL_GPT_STATUS_OK != ret_status) {
 *          //error handler 
 *       }
 *      
 *       hal_gpt_delay_ms(10);                               //delay 10 millisseconds
 *       
 *       //get the second value.
 *       ret_status = hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_32K, &count2);    
 *       if(HAL_GPT_STATUS_OK != ret_status) {
 *          //error handler 
 *       }
 *       
 *      //caculate count1 and count2 duration count value, the duration unit is 1/32768 second.
 *      ret_status = hal_gpt_get_duration_count(count1, count2, &duration_count);
 *       if(HAL_GPT_STATUS_OK != ret_status) {
 *          //error handler 
 *       }
 *      
 *       time = (duration_count*1000)/32768;                //the time means milliseconds.
 *    @endcode
 * @} 
 * @}
 */

 #ifdef HAL_GPT_FEATURE_US_TIMER
/** 
 * @addtogroup HAL
 * @{
 * @addtogroup GPT
 * @{
 *  - 
 *    If use the enum paramter HAL_GPT_CLOCK_SOURCE_1M in #hal_gpt_get_free_run_count(), 
 *    notice that using HAL_GPT_CLOCK_SOURCE_13K and HAL_GPT_CLOCK_SOURCE_1M means use different free run timer.
 *    when you use HAL_GPT_CLOCK_SOURCE_1M, the count of tick unit is 1 micosecond.
 *    For more details about HAL_GPT_CLOCK_SOURCE_1M and HAL_GPT_CLOCK_SOURCE_13K, please refer to @ref hal_gpt_enum about hal_gpt_clock_source_t.
 *  - Sample code:
 *    @code
 *       hal_gpt_status_t         ret_status;
 *       uint32_t                 count1, count2, duration_count;
 *
 *       //get the first value.
 *       ret_status = hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, &count1);            
 *       if(HAL_GPT_STATUS_OK != ret_status) {
 *          //error handler 
 *       }
 *      
 *       hal_gpt_delay_us(10);                       //delay 10 microseconds.
 *      
 *       //get the second value.
 *       ret_status = hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, &count2);           
 *       if(HAL_GPT_STATUS_OK != ret_status) {
 *          //error handler 
 *       }
 *       
 *      //caculate count1 and count2 duration count value, the duration unit is 1 microsecond.
 *      ret_status = hal_gpt_get_duration_count(count1, count2, &duration_count);
 *       if(HAL_GPT_STATUS_OK != ret_status) {
 *          //error handler 
 *       }
 *    @endcode  
 * @} 
 * @}
 */
 #endif

 /** 
 * @addtogroup HAL
 * @{
 * @addtogroup GPT
 * @{
 * - \b Using \b GPT \b delay \b function. \n
 *   Call #hal_gpt_delay_ms() function to set the delay time.
 *   When in a delay, the GPT driver uses free run mode and polls register value until it reaches the setting time.
 *  - Sample code:
 *    @code
 *       hal_gpt_delay_ms(10);  //delay 10 millisseconds
 *    @endcode
 * @} 
 * @}
 */

 #ifdef HAL_GPT_FEATURE_US_TIMER
/** 
 * @addtogroup HAL
 * @{
 * @addtogroup GPT
 * @{
 *  - Sample code:
 *    @code
 *       hal_gpt_delay_us(10);  //delay 10 microseconds
 *    @endcode  
 * @} 
 * @}
 */
 #endif

/** 
 * @addtogroup HAL
 * @{
 * @addtogroup GPT
 * @{
 */

#ifdef __cplusplus
    extern "C" {
#endif

/** @defgroup hal_gpt_typedef Typedef
  * @{
  */
  
/** @brief  Register a callback function when using GPT oneshot or repeat modes. 
  *         This function will be called after the timer times out in the GPT ISR routine.
  *         For more details about the callback function, please refer to #hal_gpt_register_callback().
  * @param[in] user_data is this variable pointer defined by the user to record the data.
  */
typedef void(* hal_gpt_callback_t )(void *user_data); 

/**
  * @}
  */

/** @defgroup hal_gpt_enum Enum
  * @{
  */  
  
/** @brief This enum define GPT timer type */
typedef enum {
    HAL_GPT_TIMER_TYPE_ONE_SHOT = 0,                /**< Set the GPT oneshot mode  */ 
    HAL_GPT_TIMER_TYPE_REPEAT   = 1                 /**< Set the GPT repeat  mode  */  
}hal_gpt_timer_type_t;


/** @brief This enum define GPT status */
typedef enum {
    HAL_GPT_STATUS_ERROR             = -3,         /**< A GPT function ERROR */
    HAL_GPT_STATUS_ERROR_PORT        = -2,         /**< A wrong GPT port  */
    HAL_GPT_STATUS_INVALID_PARAMETER = -1,         /**< An invalid parameter */
    HAL_GPT_STATUS_OK   = 0                        /**< No error occurred during the function call*/
}hal_gpt_status_t; 


/** @brief This enum GPT running status */
typedef enum {
    HAL_GPT_STOPPED = 0,                            /**< The GPT is stopped */
    HAL_GPT_RUNNING = 1                             /**< The GPT is running */
} hal_gpt_running_status_t;


/**
  * @}
  */
  
/**
 * @brief     This function is used to initialize the GPT base enironment. Call this function if a timer is required.
 * @param[in] gpt_port is the port number.
 * @return    #HAL_GPT_STATUS_OK, if operation is successful.\n
 *            #HAL_GPT_STATUS_ERROR_PORT, if the gpt_port value is wrong.
 * @sa        #hal_gpt_deinit()   
 */
hal_gpt_status_t hal_gpt_init(hal_gpt_port_t gpt_port);


/**
 * @brief     De-initilize the GPT timer.
 *            After calling this function, the callback is cleared, the clock power is turned off, interrupts and GPT module are disabled.
 * @param[in] gpt_port is the port number.
 * @return    #HAL_GPT_STATUS_OK, if operation is successful.\n
 *            #HAL_GPT_STATUS_ERROR_PORT, if the gpt_port value is wrong.
 * @sa        #hal_gpt_init() 
 */
hal_gpt_status_t hal_gpt_deinit(hal_gpt_port_t gpt_port);


/**
 * @brief     Get the running status of the port as specified.
 * @param[in] gpt_port is the port number.
 * @param[out] running_status is the pointer to the running status after the function returns. Please refer to #hal_gpt_running_status_t for details about this parameter.
 * @return    #HAL_GPT_STATUS_OK, if operation is successful.\n
 *            #HAL_GPT_STATUS_ERROR_PORT,the gpt_port value is wrong.   
 */
hal_gpt_status_t hal_gpt_get_running_status(hal_gpt_port_t gpt_port, hal_gpt_running_status_t *running_status);


/**
 * @brief     Register a callback function with the timer specified by the port.
 *            The callback can only be registered when the timer, as specified by the port, is in #HAL_GPT_STOPPED state.
 *            If timer is in #HAL_GPT_RUNNING state, the callback cannot be registered and this function returns #HAL_GPT_STATUS_ERROR.
 * @param[in] gpt_port is the port number.
 * @param[in] callback is the function pointer of the callback.
 *            This callback will be called when the timer expires.
 * @param[in] user_data is the pointer to the parameter for the callback.
 * @return    #HAL_GPT_STATUS_OK, if operation is successful.\n
 *            #HAL_GPT_STATUS_ERROR_PORT,the gpt_port value is wrong.\n
 *            #HAL_GPT_STATUS_ERROR, callback registration failed. 
 */
hal_gpt_status_t hal_gpt_register_callback(hal_gpt_port_t gpt_port, hal_gpt_callback_t callback, void *user_data);

/**
 * @brief      Get the current count of the free run timer
 * @param[in]  clock_source is the clock source of free timer. 
 *             For more details, please refer to @ref hal_gpt_enum about hal_gpt_clock_source_t.
 * @param[out] count is the user's parameter pointer to get count value.
 * @return     #HAL_GPT_STATUS_OK, if operation is successful.\n   
 */
hal_gpt_status_t hal_gpt_get_free_run_count(hal_gpt_clock_source_t clock_source, uint32_t *count);


/**
 * @brief     Set the expiration time in milliseconds and the timer mode, then start the timer. 
 *            The function only works successfully while the timer is stopped.
 * @param[in] gpt_port is the port number.
 * @param[in] timeout_time_ms is the expiration time in milliseconds.
 * @param[in] timer_type is the timer mode, i.e. oneshot or repeat timer mode defined in #hal_gpt_timer_type_t.
 * @return    #HAL_GPT_STATUS_OK, if OK.
 *            #HAL_GPT_STATUS_ERROR_PORT, if the gpt_port value is wrong.   
 */
hal_gpt_status_t hal_gpt_start_timer_ms(hal_gpt_port_t gpt_port, uint32_t timeout_time_ms, hal_gpt_timer_type_t timer_type);


/**
 * @brief     Set the delay time in milliseconds.
 * @param[in] ms is the delay time in milliseconds.
 * @return    #HAL_GPT_STATUS_OK, if operation is successful.\n
 *            #HAL_GPT_STATUS_ERROR_PORT, if the gpt_port value is wrong.     
 */
hal_gpt_status_t hal_gpt_delay_ms(uint32_t ms);

#ifdef HAL_GPT_FEATURE_US_TIMER

/**
 * @brief     Set the expiration time in microseconds and the timer mode, then start the timer. The function only works successfully while the timer is stopped.
 * @param[in] gpt_port is the port number.   
 * @param[in] timeout_time_us is the expiration time in microseconds.
 * @param[in] timer_type is the timer mode, i.e. oneshot or repeat timer mode defined in #hal_gpt_timer_type_t.
 * @return    #HAL_GPT_STATUS_OK, if the operation is successful.\n
 *            #HAL_GPT_STATUS_ERROR_PORT, if gpt_port value is wrong.    
 */
hal_gpt_status_t hal_gpt_start_timer_us(hal_gpt_port_t gpt_port, uint32_t timeout_time_us, hal_gpt_timer_type_t timer_type);

/**
 * @brief     Set delay time in microseconds.
 * @param[in] us is the delay time in microseconds.
 * @return    #HAL_GPT_STATUS_OK, if operation is successful.\n
 *            #HAL_GPT_STATUS_ERROR_PORT, if the gpt_port value is wrong.    
 */
hal_gpt_status_t hal_gpt_delay_us(uint32_t us);

#endif

/**
 * @brief     Stop the timer, only for oneshot mode and repeat mode.
 * @param[in] gpt_port is the port number. 
 * @return    #HAL_GPT_STATUS_OK, if the timer is stopped successfully.\n
 *            #HAL_GPT_STATUS_ERROR_PORT, if the gpt_port value is wrong.      
 */
hal_gpt_status_t hal_gpt_stop_timer(hal_gpt_port_t gpt_port);

/**
 * @brief      Caculate the duration count value.
 * @param[in]  start_count is the start count value. 
 * @param[in]  end_count is the start count value. 
 * @param[out] duration_count is the user's parameter pointer to get duration count.
 * @return     #HAL_GPT_STATUS_OK, if operation is successful.\n
 *             #HAL_GPT_STATUS_INVALID_PARAMETER, duration_count is null.
 */
hal_gpt_status_t hal_gpt_get_duration_count(uint32_t start_count, uint32_t end_count, uint32_t *duration_count);


#ifdef __cplusplus
}
#endif

/** 
* @} 
* @}
*/
#endif /*HAL_GPT_MODULE_ENABLED*/
#endif /* __HAL_GPT_H__ */ 

