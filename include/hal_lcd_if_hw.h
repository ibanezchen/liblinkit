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
 
#ifndef __HAL_LCD_IF_HW_H__
#define __HAL_LCD_IF_HW_H__

#include "hal_platform.h"
#include "hal_lcd_if_common.h"
#include "bsp_lcd.h"

#ifdef HAL_LCD_MODULE_ENABLED


 /**
  * @addtogroup HAL
  * @{
  * @addtogroup LCD
  * @{
  * This section introduces the LCD APIs including terms and acronym,
  * supported features, software architecture, how to use this driver, ISINK function groups, all enum, structures and functions.
  *
  * @section Terms_Chapter Terms and acronyms
  *
  * |Terms					 |Details																  |
  * |------------------------------|------------------------------------------------------------------------|
  * |\b ROI 					   | Region of Interest, the region will be transfered, inculding width and height.
  * |\b DMA 					   | Direct Memory Access, the data can be accessed by LCD engine without CPU. For more information, please check <a href="https://en.wikipedia.org/wiki/Direct_memory_access"> Direct memory access in wiki </a>.|
  * |\b TE  					   | The VSync signal send from LCM to LCD engine to prevent tearing effect.
  *
  * @section Features_Chapter Supported features
  * 
  * - \b Support \b DMA \b and \b CPU \b mode. \n
  *   LCD engine can transfer pixel data in two different mode:
  *  - \b DMA \b mode: In this mode, LCD engine will fetch the data from DRAM  by using DMA
  * 	 and transfer to LCM module. After transmission, the LCD engine will raised a transfer complete interrupt. \n
  *  - \b CPU \b mode: In this mode, LCD engine will send the buffer manually, you have to assign each pixel data in this mode. \n
  *
  * - \b Support \b callback \b function \b registration.
  *   When the LCD uses DMA mode to transfer data, you can register a callback function \n
  *   via #hal_lcd_register_callback(). After LCD engine finish transfering data by DMA mode, a transfer complete interruput will be send by
  *   LCD engine, and you callback function will be executed.
  * 
  * @section LCD_Driver_Usage_Chapter How to use this driver
  * 
  * - Use LCD with DMA mode. \n
  *  - step1: add START_LCD_TRANSFER to start the LCD DMA mode in the end of blockwrite function of LCM driver.
  *  - step2: call #hal_lcd_initialize() to initial the LCD engine.
  *  - step3: call #hal_lcd_config_roi() to set ROI information.
  *  - step4: call #hal_lcd_config_layer() to set layer data.
  *  - step5: call BlockWrite funtion in LCM driver function table to start transfer.
  *  - sample code:
  *    @code
  * 	  HAL_LCD_ROI_PARA_STRUCT_T roi_para;
  * 	  HAL_LCD_LAYER_PARA_STRUCT_T layer_para;
  *
  * 	  ret = hal_lcd_initialize();
  * 	  if(HAL_LCD_NO_ERROR != ret){
  * 			// error handle
  * 	  }
  *
  * 	  // set the parameter of roi_para
  * 	  ret = hal_lcd_config_roi(&roi_para);
  * 	  if(HAL_LCD_NO_ERROR != ret){
  * 			// error handle
  * 	  }
  *
  * 	  // set the parameter of layer_para
  * 	  ret = hal_lcd_config_layer(&layer_data);		 
  * 	  if(HAL_LCD_NO_ERROR != ret){
  * 			// error handle
  * 	  }
  * 	  
  * 	  // start to blt
  * 	  MainLCD->BlockWrite(startx, starty, endx, endy);
  *
  * 	  LCM driver:
  * 	  LCD_Blockwrite()
  * 	  {
  * 			// set the ROI data to LCM
  * 			
  * 			// Add this to start DMA mode
  * 			ENABLE_LCD_TRANSFER_COMPLETE_INT;
  * 			DISABLE_LCD_ROI_CTRL_CMD_FIRST;
  * 			START_LCD_TRANSFER;
  * 	  }
  *    @endcode
  *
  * - Use LCD with CPU mode. \n
  *  - step1: write a for loop to transfer pixel data with LCD CPU mode in the blockwrite function of LCM driver.
  *  - step2: call #hal_lcd_initialize() to initial the LCD engine.
  *  - step3: call #hal_lcd_config_roi() to set ROI information.
  *  - step4: call #hal_lcd_config_layer() to set layer data.
  *  - step5: call BlockWrite funtion in LCM driver function table to start transfer.
  *  - sample code:
  *    @code
  * 	  HAL_LCD_ROI_PARA_STRUCT_T roi_para;
  * 	  HAL_LCD_LAYER_PARA_STRUCT_T layer_para;
  *
  * 	  ret = hal_lcd_initialize();
  * 	  if(HAL_LCD_NO_ERROR != ret){
  * 			// error handle
  * 	  }
  *
  * 	  // set the parameter of roi_para
  * 	  ret = hal_lcd_config_roi(&roi_para);
  * 	  if(HAL_LCD_NO_ERROR != ret){
  * 			// error handle
  * 	  }
  *
  * 	  // set the parameter of layer_para
  * 	  ret = hal_lcd_config_layer(&layer_data);		 
  * 	  if(HAL_LCD_NO_ERROR != ret){
  * 			// error handle
  * 	  }
  * 	  
  * 	  // start to blt
  * 	  MainLCD->BlockWrite(startx, starty, endx, endy);
  *
  * 	  LCM driver:
  * 	  LCD_Blockwrite()
  * 	  {
  * 			// set the ROI data to LCM
  * 			
  * 			// Write a for loop to transfer data
  * 			for(i = 0; i < height; i++)
  * 			{
  * 				  for(j = 0; j < width; j++)
  * 				  {
  * 						//send pixel data
  * 				  }
  * 			}
  * 	  }
  *
  *    @endcode
  *
  * @section Function_Group_Chapter LCD function groups description
  * 
  * For easily using,we group the APIs by its functionality.
  * You can refer to the details of each function by clicking the function name.
  * - LCD initialize function. \n The #hal_lcd_initialize() function mainly configue the default value of LCD engine.
  *   Before using LCD engine, you should call this firstly. The function is:
  *  - #hal_lcd_initialize()
  * - LCD power on/off funtions. \n The #hal_lcd_power_on() will eable the power of LCD engine. The #hal_lcd_power_off() will disalbe the power of LCD engine. Before accessing LCD registers,
  *   you should call #hal_lcd_power_on() to enable power and after setting register values or blting, you should call #hal_lcd_power_off() to turn off the power of LCD engine to decrease the power consumption.
  *   The funtions are:
  *  - #hal_lcd_power_on()
  *  - #hal_lcd_power_off()
  * - LCD callback register functions.	\n Use this function to register a callback function if the DMA mode is enabled.
  *  - #hal_lcd_register_callback()
  * - LCD configuration functions.	\n #hal_lcd_config_roi() function will fill the ROI information to related registers. #hal_lcd_config_layer() will fill the layer information to related registers.
  *   The #hal_lcd_set_index_color_table() funtion set the index color table information. Before using index color mode(4bit/2bit/1bit),
  *   you should call this function to set the index color table. 
  *   The functions are:
  *  - #hal_lcd_config_roi()
  *  - #hal_lcd_config_layer()
  *  - #hal_lcd_set_index_color_table()
  *
  */
   
#ifdef __cplusplus
extern "C" {
#endif


/** @defgroup hal_lcd_typedef Typedef
  * @{
  * @brief  Register a callback function when using DMA modes. 
  *		   This function will be called after the TE/frame done/Command queue done interrupt.
  *		   For more details about the callback function, please refer to #hal_gpt_register_callback().
  * @param[in] user_data is this variable pointer defined by the user to record the data.
  */  
   
 typedef void (*hal_lcd_callback_t)(void *param);
 
/**
  * @}
*/

/**
 * @brief This function is mainly used to start LCD engine hardware to transfer data to LCM. This function will restore the LCM interface timing setting and re-apply mm_colo.
 *
  * @param[in] main_cmd_addr	The register address to be written when sending command to LCM
  * @param[in] main_data_addr   The register address to be written when sending data to LCM
  * @param[in] main_lcd_output_format	 The output format LCD engine will send to LCM
 * @return    To indicate whether this function call success or not. 
 *            If the return value is #HAL_LCD_NO_ERROR,it means success;
 *            If the return value is #HAL_LCD_INITIALIZE_ERROR,it means the register of LCD engine  can't be set so the initialize of LCD engine is failed. Please assure you call #hal_lcd_power_on() before set LCD engine registers. 
 *            If the return value is #HAL_LCD_MM_COLOR_INITIALIZE_ERROR,it means the register of color engine  can't be set so the initialize of color engine is failed. Please assure you call #hal_lcd_power_on() before set color engine registers. 
 */
HAL_LCD_ERROR_ENUM hal_lcd_initialize(uint32_t main_cmd_addr, uint32_t main_data_addr, uint32_t main_lcd_output_format);

/**
 * @brief This function is mainly used to set the timing parameter to LCD engine hardware . This function will restore the LCM interface timing setting and re-apply mm_color.
 *
 * @param[in] port	Which serial port will be used
 * @param[in] css 	Chip Select Setup Time
 * @param[in] csh	Chip Select Hold Time
 * @param[in] rd_1st	Read pulse high duation
 * @param[in] rd_2nd	Read pulse low duation
 * @param[in] wr_1st 	Write pulse high duation
 * @param[in] wr_2nd	Write pulse low duation
 * @param[in] clock		The clock speed
 *
 * @return    To indicate whether this function call success or not. 
 *            If the return value is #HAL_LCD_NO_ERROR,it means success;
 *	      If the return value is #HAL_LCD_PARAMETER_ERROR,it means the parameter out of bound, please check the parameter;
 */
HAL_LCD_ERROR_ENUM hal_lcd_set_serial_if_timing(HAL_LCD_IF_TIME_PARA_T para);
 
 /**
  * @brief This function is mainly used to set the timing parameter to LCD engine hardware . This function will restore the LCM interface timing setting and re-apply mm_colo.
  *
  * @param[in] port  Which serial port will be used
  * @param[in] css	 Chip Select Setup Time
  * @param[in] csh	 Chip Select Hold Time
  * @param[in] rd_1st	 Read pulse high duation
  * @param[in] rd_2nd	 Read pulse low duation
  * @param[in] wr_1st	 Write pulse high duation
  * @param[in] wr_2nd	 Write pulse low duation
  * @param[in] clock	 The clock speed
  *
  * @return    To indicate whether this function call success or not. 
  * 		   If the return value is #HAL_LCD_NO_ERROR,it means success;
  * 	   If the return value is #HAL_LCD_PARAMETER_ERROR,it means the parameter out of bound, please check the parameter;
  */
HAL_LCD_ERROR_ENUM hal_lcd_set_serial_if_mode(HAL_LCD_IF_MODE_PARA_T para);

/**
 * @brief This function is mainly used to set the timing parameter to LCD engine hardware . This function will restore the LCM interface timing setting and re-apply mm_colo.
 *
 * @param[in] port	Which serial port will be used
 * @param[in] css	Chip Select Setup Time
 * @param[in] csh	Chip Select Hold Time
 * @param[in] rd_1st	Read pulse high duation
 * @param[in] rd_2nd	Read pulse low duation
 * @param[in] wr_1st	Write pulse high duation
 * @param[in] wr_2nd	Write pulse low duation
 * @param[in] clock 	The clock speed
 *
 * @return	  To indicate whether this function call success or not. 
 *			  If the return value is #HAL_LCD_NO_ERROR,it means success;
 *		  If the return value is #HAL_LCD_PARAMETER_ERROR,it means the parameter out of bound, please check the parameter;
 */
HAL_LCD_ERROR_ENUM hal_lcd_set_serial_if_2data_lane_mode(HAL_LCD_IF_ENUM port, bool enable, HAL_LCD_SCNF_IF_2PIN_WIDTH_ENUM if_2data_width);

 /**
  * @brief This function is mainly used to set the timing parameter to LCD engine hardware . This function will restore the LCM interface timing setting and re-apply mm_colo.
  *
  * @param[in] port  Which serial port will be used
  * @param[in] css	 Chip Select Setup Time
  * @param[in] csh	 Chip Select Hold Time
  * @param[in] rd_1st	 Read pulse high duation
  * @param[in] rd_2nd	 Read pulse low duation
  * @param[in] wr_1st	 Write pulse high duation
  * @param[in] wr_2nd	 Write pulse low duation
  * @param[in] clock	 The clock speed
  *
  * @return    To indicate whether this function call success or not. 
  * 		   If the return value is #HAL_LCD_NO_ERROR,it means success;
  * 	   If the return value is #HAL_LCD_PARAMETER_ERROR,it means the parameter out of bound, please check the parameter;
  */
HAL_LCD_ERROR_ENUM hal_lcd_power_on(void);

 /**
  * @brief This function is mainly used to set the timing parameter to LCD engine hardware . This function will restore the LCM interface timing setting and re-apply mm_colo.
  *
  * @param[in] port  Which serial port will be used
  * @param[in] css	 Chip Select Setup Time
  * @param[in] csh	 Chip Select Hold Time
  * @param[in] rd_1st	 Read pulse high duation
  * @param[in] rd_2nd	 Read pulse low duation
  * @param[in] wr_1st	 Write pulse high duation
  * @param[in] wr_2nd	 Write pulse low duation
  * @param[in] clock	 The clock speed
  *
  * @return    To indicate whether this function call success or not. 
  * 		   If the return value is #HAL_LCD_NO_ERROR,it means success;
  * 	   If the return value is #HAL_LCD_PARAMETER_ERROR,it means the parameter out of bound, please check the parameter;
  */
HAL_LCD_ERROR_ENUM hal_lcd_power_off(void);

 /**
  * @brief This function is mainly used to set the timing parameter to LCD engine hardware . This function will restore the LCM interface timing setting and re-apply mm_colo.
  *
  * @param[in] port  Which serial port will be used
  * @param[in] css	 Chip Select Setup Time
  * @param[in] csh	 Chip Select Hold Time
  * @param[in] rd_1st	 Read pulse high duation
  * @param[in] rd_2nd	 Read pulse low duation
  * @param[in] wr_1st	 Write pulse high duation
  * @param[in] wr_2nd	 Write pulse low duation
  * @param[in] clock	 The clock speed
  *
  * @return    To indicate whether this function call success or not. 
  * 		   If the return value is #HAL_LCD_NO_ERROR,it means success;
  * 	   If the return value is #HAL_LCD_PARAMETER_ERROR,it means the parameter out of bound, please check the parameter;
  */
HAL_LCD_ERROR_ENUM hal_lcd_config_layer(HAL_LCD_LAYER_PARA_STRUCT_T *layer_data);

 /**
  * @brief This function is mainly used to set the timing parameter to LCD engine hardware . This function will restore the LCM interface timing setting and re-apply mm_colo.
  *
  * @param[in] port  Which serial port will be used
  * @param[in] css	 Chip Select Setup Time
  * @param[in] csh	 Chip Select Hold Time
  * @param[in] rd_1st	 Read pulse high duation
  * @param[in] rd_2nd	 Read pulse low duation
  * @param[in] wr_1st	 Write pulse high duation
  * @param[in] wr_2nd	 Write pulse low duation
  * @param[in] clock	 The clock speed
  *
  * @return    To indicate whether this function call success or not. 
  * 		   If the return value is #HAL_LCD_NO_ERROR,it means success;
  * 	   If the return value is #HAL_LCD_PARAMETER_ERROR,it means the parameter out of bound, please check the parameter;
  */
HAL_LCD_ERROR_ENUM hal_lcd_config_roi(HAL_LCD_ROI_PARA_STRUCT_T *roi_para);

 /**
  * @brief This function is mainly used to set the timing parameter to LCD engine hardware . This function will restore the LCM interface timing setting and re-apply mm_colo.
  *
  * @param[in] port  Which serial port will be used
  * @param[in] css	 Chip Select Setup Time
  * @param[in] csh	 Chip Select Hold Time
  * @param[in] rd_1st	 Read pulse high duation
  * @param[in] rd_2nd	 Read pulse low duation
  * @param[in] wr_1st	 Write pulse high duation
  * @param[in] wr_2nd	 Write pulse low duation
  * @param[in] clock	 The clock speed
  *
  * @return    To indicate whether this function call success or not. 
  * 		   If the return value is #HAL_LCD_NO_ERROR,it means success;
  * 	   If the return value is #HAL_LCD_PARAMETER_ERROR,it means the parameter out of bound, please check the parameter;
  */
 HAL_LCD_ERROR_ENUM hal_lcd_set_index_color_table(uint32_t* index_table);

 /**
  * @brief This function is mainly used to set the timing parameter to LCD engine hardware . This function will restore the LCM interface timing setting and re-apply mm_colo.
  *
  * @param[in] port  Which serial port will be used
  * @param[in] css	 Chip Select Setup Time
  * @param[in] csh	 Chip Select Hold Time
  * @param[in] rd_1st	 Read pulse high duation
  * @param[in] rd_2nd	 Read pulse low duation
  * @param[in] wr_1st	 Write pulse high duation
  * @param[in] wr_2nd	 Write pulse low duation
  * @param[in] clock	 The clock speed
  *
  * @return    To indicate whether this function call success or not. 
  * 		   If the return value is #HAL_LCD_NO_ERROR,it means success;
  * 	   If the return value is #HAL_LCD_PARAMETER_ERROR,it means the parameter out of bound, please check the parameter;
  */
 hal_lcd_callback_t hal_lcd_register_callback(hal_lcd_callback_t lcd_callback);

 /**
  * @brief This function is mainly used to set the timing parameter to LCD engine hardware . This function will restore the LCM interface timing setting and re-apply mm_colo.
  *
  * @param[in] port  Which serial port will be used
  * @param[in] css	 Chip Select Setup Time
  * @param[in] csh	 Chip Select Hold Time
  * @param[in] rd_1st	 Read pulse high duation
  * @param[in] rd_2nd	 Read pulse low duation
  * @param[in] wr_1st	 Write pulse high duation
  * @param[in] wr_2nd	 Write pulse low duation
  * @param[in] clock	 The clock speed
  *
  * @return    To indicate whether this function call success or not. 
  * 		   If the return value is #HAL_LCD_NO_ERROR,it means success;
  * 	   If the return value is #HAL_LCD_PARAMETER_ERROR,it means the parameter out of bound, please check the parameter;
  */
 HAL_LCD_ERROR_ENUM hal_lcd_init_TE(uint32_t frame_rate, uint32_t back_porch, uint32_t front_porch, uint32_t width, uint32_t height, uint32_t main_lcd_output);

 /**
  * @brief This function is mainly used to set the timing parameter to LCD engine hardware . This function will restore the LCM interface timing setting and re-apply mm_colo.
  *
  * @param[in] low_time  	Reset pin keep low time (ms)
  * @param[in] high_time	Reset pin keep high delay (ms)
  *
  * @return    To indicate whether this function call success or not. 
  * 		   If the return value is #HAL_LCD_NO_ERROR,it means success;
  * 	   If the return value is #HAL_LCD_PARAMETER_ERROR,it means the parameter out of bound, please check the parameter;
  */
HAL_LCD_ERROR_ENUM hal_lcd_toggle_reset(uint32_t low_time, uint32_t high_time);

 /**
  * @brief This function is mainly used to set the timing parameter to LCD engine hardware . This function will restore the LCM interface timing setting and re-apply mm_colo.
  *
  * @return    To indicate whether this function call success or not. 
  * 		   If the return value is #HAL_LCD_NO_ERROR,it means success;
  * 	   If the return value is #HAL_LCD_PARAMETER_ERROR,it means the parameter out of bound, please check the parameter;
  */
HAL_LCD_ERROR_ENUM hal_lcd_toggle_DMA(void);


 /**
  * @brief This function is mainly used to set the timing parameter to LCD engine hardware . This function will restore the LCM interface timing setting and re-apply mm_colo.
  *
  * @return    To indicate whether this function call success or not. 
  * 		   If the return value is #HAL_LCD_NO_ERROR,it means success;
  * 	   If the return value is #HAL_LCD_PARAMETER_ERROR,it means the parameter out of bound, please check the parameter;
  */
uint32_t hal_lcd_get_layer_address(HAL_LCD_LAYER_ENUM layer);


#ifdef __cplusplus
 }
#endif
 
 
 /**
 * @}
 * @}
 */
 
#endif /*HAL_LCD_MODULE_ENABLED*/
#endif /* __HAL_LCD_IF_HW_H__ */
 
