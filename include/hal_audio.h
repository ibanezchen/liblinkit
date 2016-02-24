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
 
#ifndef __HAL_AUDIO_H__
#define __HAL_AUDIO_H__
#include "hal_platform.h"

#ifdef HAL_AUDIO_MODULE_ENABLED

/** 
 * @addtogroup HAL
 * @{
 * @addtogroup AUDIO
 * @{
 * This document mainly introduce all details about the audio APIs,
 * supported features,software achitechture,how to use this driver,audio function groups,all enum,structure and functions.
 *
 * @section Driver_Usage_Chapter How to use this driver
 * 
 * - Turn on audio play function and play out via earphone. \n
 *  - step1: call #hal_audio_set_stream_out_sample_rate to configue audio sample rate.
 *  - step2: call #hal_audio_set_stream_out_channel_number to configue audio channel number.
 *  - step3: call #hal_audio_set_stream_out_device to config audio output device.
 *  - step4: call #hal_audio_stream_out_start to start audio playback flow.
 *  - sample code:
 *    @code
 *      static void user_audio_stream_out_callback(hal_audio_event_t event, void *user_data)
 *      {
 *          switch(event) {
 *              case HAL_AUDIO_EVENT_UNDERFLOW:
 *                //user need to filled data when recieve the event
 *                //audio output might be discontinuous since data underflow
 *                break;
 *              case HAL_AUDIO_EVENT_DATA_REQUEST:
 *              	 //filled data if output data is avaliable
 *              	 break; 
 *              case HAL_AUDIO_EVENT_ERROR:
 *                //error handle
 *                break;                 	
 *           }
 *      }
 *      
 *      static void audio_play(void)
 *      {
 *          hal_audio_set_stream_out_sample_rate(HAL_AUDIO_SAMPLE_RATE_48KHZ);
 *          hal_audio_set_stream_out_channel_number(HAL_AUDIO_STEREO);
 *          hal_audio_set_stream_out_device(HAL_AUDIO_DEVICE_HEADSET);
 *          hal_audio_register_stream_out_callback(user_audio_stream_out_callback, NULL);
  *          // get the amount of internal-use memory
 *          hal_audio_get_memory_size(&memory_size);
 *          memory = malloc(memory_size * sizeof(uint16_t *));
 *          if(NULL == memory){
 *             //error handle: fail to allocate memory
 *          }
 *          result = hal_audio_set_memory(memory);
 *          if(HAL_AUDIO_STATUS_OK != result){
 *             //error handle
 *          }
 *          hal_audio_stream_out_start(HAL_AUDIO_AUDIO_PLAYBACK);
 *      }
 * 
 *      static void audio_stop(void)
 *      {                 
 *          hal_audio_stream_out_stop();  
 *          //free memory which is allocated for internal use
 *          hal_audio_restore_memory(&memory);
 *          free(memory);
 *      }
 *    @endcode
 *
 * For easily using,we group the APIs by its functionality.
 * User can refer to the details of each function by clicking the function name.
 * - \b Initialization \b and \b configuration. \n 
 *   The #hal_audio_init function mainly initialize the audio hardware. User should call this function when system boot up. \n
 *   The #hal_audio_set_stream_out_sample_rate and #hal_audio_set_stream_in_sample_rate are used to set path sample rate. \n When audio application is related to voice, stream in/out
 *   sample rate should be set as 8k for narrowband and 16k for wideband. \n #hal_audio_set_stream_out_channel_number and #hal_audio_set_stream_in_channel_number are used to set channel number.\n
 *   The sample rate and channel number config functions should be called before power on an audio application, and could not be changed durning the application life time. \n
 *   Which means user need to re-conifg these settings when start a new audio track or a application. \n
 *   #hal_audio_set_stream_out_device and # hal_audio_set_stream_in_device also need to specify before audio start. Devices settings could be changed when an audio is still activated.
 *   The functions are:
 *   - #hal_audio_init
 *   - #hal_audio_deinit
 *   - #hal_audio_set_stream_out_sample_rate
 *   - #hal_audio_set_stream_out_channel_number
 *   - #hal_audio_set_stream_out_device 
 *   - #hal_audio_set_stream_in_sample_rate
 *   - #hal_audio_set_stream_in_channel_number
 *   - #hal_audio_set_stream_in_device 
 *
 * - \b Callback \b register \b functions \n 
 *   Use these functions to register callback function for stream output and in data operation respectively. The functions are:  
 *  - #hal_audio_register_stream_out_callback
 *  - #hal_audio_register_stream_in_callback
 *
 * - \b Enable \b and \b disable \b functions. \n 
 *   #hal_audio_stream_out_start function will enable the stream output hardware and the data would start play.
 *   #hal_audio_stream_out_stop function will stop the stream out playback immediately. \n
 *   #hal_audio_stream_in_start function will enable the stream input hardware and user may start get data from hardware input path.
 *   #hal_audio_stream_in_stop function will stop the stream in immediately. The functions are: 
 *   - #hal_audio_stream_out_start
 *   - #hal_audio_stream_out_stop
 *   - #hal_audio_stream_in_start
 *   - #hal_audio_stream_in_stop
 *
 * - \b Volume \b control \b functions \n
 *   The volume of stream out and in are set using #hal_audio_set_stream_out_volume and #hal_audio_set_stream_in_volume respectively. \n The volume can be changed durning the application life time.
 *   Volume is composed of digital gain analog gain. Gain range are chip dependent, user need to refers to chip spec. \n Mute functions are also provided. User can use #hal_audio_mute_stream_out
 *   and #hal_audio_mute_stream_in to mute audio path. One should be noticed is that unmute should be called after mute is set when audio need to be played out or recorded in. 
 *   The functions are:
 *   - #hal_audio_mute_stream_out
 *   - #hal_audio_set_stream_out_volume
 *   - #hal_audio_mute_stream_in
 *   - #hal_audio_set_stream_in_volume
 *
 * - \b Data \b transfer \b functions \n
 *   - Stream out transfer
 *    The #hal_audio_get_stream_out_sample_count should be called before #hal_audio_stream_out_write to know how many free space of output buffer can be written. The functions are:  
 *    - #hal_audio_stream_out_write
 *    - #hal_audio_get_stream_out_sample_count
 *    - sample code:
 *    @code
 *     uint16_t user_buffer[512] = { //with data };
 *     static void audio_write_data(void)
 *     {
 *         uint32_t sample_count = 0;
 *         uint16_t *data_buffer = (uint16_t *)user_buffer;
 *         // get available free space of output buffer 
 *         hal_audio_get_stream_out_sample_count(&sample_count);
 *         //write numbers of sample_count samples for audio out
 *         hal_audio_stream_out_write(user_buffer, sample_count);    
 *     }
 *    @endcode
 *   - Stream in transfer
 *    The #hal_audio_get_stream_in_sample_count should be called before #hal_audio_stream_in_read to know how many avaliable samples of input buffer can be read. The functions are: 
 *    - #hal_audio_stream_in_read
 *    - #hal_audio_get_stream_in_sample_count
 *    - sample code:
 *    @code
 *     uint16_t user_buffer[512];
 *     static void audio_read_data(void)
 *     {
 *         uint32_t sample_count = 0;
 *         uint16_t *data_buffer = (uint16_t *)user_buffer;
 *         //get available data count of input buffer 
 *         hal_audio_get_stream_in_sample_count(&sample_count);
 *         //copy numbers of sample_count samples into user_buffer
 *         hal_audio_stream_in_read(user_buffer, sample_count);    
 *     } 
 *    @endcode
 */


#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif


/** @defgroup hal_audio_enum Enum
  * @{
  */ 

/** @brief audio status */
typedef enum {
    HAL_AUDIO_STATUS_INVALID_PARAMETER = -2,  /**<  This value means a wrong parameter is given. */
    HAL_AUDIO_STATUS_ERROR             = -1,  /**<  This value means some error happen during the function call. */ 
    HAL_AUDIO_STATUS_OK                =  0   /**<  This value means no error happen during the function call. */
} hal_audio_status_t;

/** @brief audio event */
typedef enum {
    HAL_AUDIO_EVENT_ERROR               = -1, /**<  This value means some error happen during the function call. */
    HAL_AUDIO_EVENT_NONE                =  0, /**<  This value means no error happen during the function call. */
    HAL_AUDIO_EVENT_UNDERFLOW           =  1, /**<  This value means tx data underflow. */
    HAL_AUDIO_EVENT_DATA_REQUEST        =  2, /**<  This value means request user to fill data. */
    HAL_AUDIO_EVENT_DATA_NOTIFICATION   =  3  /**<  This value means notify user rx data is ready. */
} hal_audio_event_t;

/** @brief audio device */
typedef enum {
    HAL_AUDIO_DEVICE_NONE            = 0x0000,  /**<  No audio device is on */
    HAL_AUDIO_DEVICE_MAIN_MIC        = 0x0001,  /**<  Stream in: main mic */
    HAL_AUDIO_DEVICE_HEADSET_MIC     = 0x0002,  /**<  Stream in: earphone mic */
    HAL_AUDIO_DEVICE_HANDSET         = 0x0004,  /**<  Stream out:reciever */
    HAL_AUDIO_DEVICE_HANDFREE_MONO   = 0x0008,  /**<  Stream out:loudspeaker, mono */
    HAL_AUDIO_DEVICE_HANDFREE_STEREO = 0x0010,  /**<  Stream out:loudspeaker, stereo to mono L=R=(R+L)/2 */
    HAL_AUDIO_DEVICE_HEADSET         = 0x0020,  /**<  Stream out:earphone, stereo */
    HAL_AUDIO_DEVICE_HEADSET_MONO    = 0x0040,  /**<  Stream out:earphone, mono to stereo. L=R */
    HAL_AUDIO_DEVICE_LINEIN          = 0x0080   /**<  Stream in/out: line in */
} hal_audio_device_t;  

/** @brief audio mute device define */
typedef enum {
    HAL_AUDIO_MUTE_MAIN_MIC    = 0x0001, /**<  Mute main mic */
    HAL_AUDIO_MUTE_EAR_MIC     = 0x0002, /**<  Mute earphone mic */
    HAL_AUDIO_MUTE_HANDSET     = 0x0004, /**<  Mute reciever */
    HAL_AUDIO_MUTE_HANDFREE    = 0x0008, /**<  Mute loudspeaker */
    HAL_AUDIO_MUTE_HEADSET     = 0x0010, /**<  Mute earphone */
    HAL_AUDIO_MUTE_LINEIN      = 0x0020  /**<  Mute line in path */
} hal_audio_mute_t; 

/** @brief audio mute function define */
typedef enum {
    HAL_AUDIO_MUTE_NONE  = 0,   /**<  No function is mute */
    HAL_AUDIO_MUTE_PCM   = 1    /**<  PCM playback path is mute */
} hal_audio_mute_function_t;

/** @brief audio sample rate define */
typedef enum {
    HAL_AUDIO_SAMPLE_RATE_8KHZ      = 0, /**< 8000Hz  */
    HAL_AUDIO_SAMPLE_RATE_11_025KHZ = 1, /**< 11025Hz */
    HAL_AUDIO_SAMPLE_RATE_12KHZ	    = 2, /**< 12000Hz */
    HAL_AUDIO_SAMPLE_RATE_16KHZ     = 3, /**< 16000Hz */
    HAL_AUDIO_SAMPLE_RATE_22_05KHZ  = 4, /**< 22050Hz */
    HAL_AUDIO_SAMPLE_RATE_24KHZ     = 5, /**< 24000Hz */
    HAL_AUDIO_SAMPLE_RATE_32KHZ     = 6, /**< 32000Hz */
    HAL_AUDIO_SAMPLE_RATE_44_1KHZ   = 7, /**< 44100Hz */
    HAL_AUDIO_SAMPLE_RATE_48KHZ     = 8, /**< 48000Hz */
    HAL_AUDIO_SAMPLE_RATE_96KHZ     = 9  /**< 96000Hz */
} hal_audio_sample_rate_t;

/** @brief audio bps define */
typedef enum {
    HAL_AUDIO_BITS_PER_SAMPLE_16    = 0, /**< 16 bps */
    HAL_AUDIO_BITS_PER_SAMPLE_24    = 1  /**< 24 bps */
} hal_audio_bits_per_sample_t;

/** @brief audio channel number define */
typedef enum {
    HAL_AUDIO_MONO    = 0, /**< This value means 1 channel  */
    HAL_AUDIO_STEREO  = 1  /**< This value means 2 channels */
} hal_audio_channel_number_t;

/** @brief audio function define */
typedef enum {
    HAL_AUDIO_AUDIO_PLAYBACK     = 0, /**< audio playback: music */
    HAL_AUDIO_VOICE_PLAYBACK     = 1, /**< voice playback: voice */  
    HAL_AUDIO_VOICE_RECORD       = 2, /**< voice record */
    HAL_AUDIO_BT_SPEECH          = 3 	/**< BT call spplication */
} hal_audio_active_type_t;


/**
  * @}
  */

/** @defgroup hal_audio_struct Struct
  * @{
  */

/** @brief audio stream node structure */
typedef struct {
	  hal_audio_sample_rate_t     stream_sample_rate;    /**< Specify the sample rate of audio.*/
	  hal_audio_bits_per_sample_t stream_bit_rate;       /**< Specify the bps of audio.*/
	  hal_audio_channel_number_t  stream_channel;
	  hal_audio_device_t          audio_device;          /**< Specify the device.*/
	  uint32_t                    digital_gain_index;    /**< Digital gain index of stream.*/
	  uint32_t                    analog_gain_index;     /**< Analog gain index of stream.*/
} hal_audio_stream_node_t;

/** @brief audio structure */
typedef struct {
	  audio_stream_node_t         stream_in;               /**< audio input configuration*/
	  audio_stream_node_t         stream_out;              /**< audio output configuration*/
	  hal_audio_active_type_t     audio_path_type;         /**< audio function type*/	
	  hal_audio_mute_t            mute_device;             /**< audio mute devices*/
	  bool                        loopback;                /**< audio loopback configuration*/
} hal_audio_struct_t;


/**
  * @}
  */

/** @defgroup hal_audio_typedef Typedef
  * @{
  */
  
/** @brief  This define audio stream out callback function prototype.
 *          User should register a callback function while turn on audio stream out path.
 *          More details about the callback, please refer to #hal_audio_register_stream_out_callback.
 *  @param[in] event is the value defined in #hal_audio_event_t. This paramter is given by the driver to tell the user of data flow processing behavior.
 *  @param[in] user_data is a paramter given by user via #hal_audio_register_stream_out_callback.       
 */
typedef void (*hal_audio_stream_out_callback_t)(hal_audio_event_t event, void *user_data);

/** @brief  This define audio stream in callback function prototype.
 *          User should register a callback function while turn on audio stream in path.
 *          More details about the callback, please refer to #hal_audio_register_stream_in_callback.
 *  @param[in] event is the value defined in #hal_audio_event_t. This paramter is given by the driver to tell the user of data flow processing behavior.
 *  @param[in] user_data is a paramter given by user via #hal_audio_register_stream_in_callback.       
 */
typedef void (*hal_audio_stream_in_callback_t)(hal_audio_event_t event, void *user_data);  

/**
  * @}
  */

/**
 * @brief     Initializes basic settings of audio hardware
 * @return    #HAL_AUDIO_STATUS_OK, if OK
 * @note      This function should at least be called once after system boot up and before using audio functionality.
 * @sa        #hal_audio_deinit  
 * @par       Example
 * Sample code please refer to @ref Driver_Usage_Chapter 
 */
hal_audio_status_t hal_audio_init(void);

/**
 * @brief     Deinitialize audio settings
 * @return    #HAL_AUDIO_STATUS_OK, if OK
 * @sa        #hal_audio_init 
 * @par       Example
 * Sample code please refer to @ref Driver_Usage_Chapter 
 */
hal_audio_status_t hal_audio_deinit(void);

/**
 * @brief     Set audio output stream sample rate
 * @param[in] sample_rate is to set output sample rate. Please refers to #hal_audio_sample_rate_t.
 * @return    #HAL_AUDIO_STATUS_OK, if sample rate is valid
 * @note      When audio function is speech usage, such as HAL_AUDIO_SPEECH_PLAYBACK / HAL_AUDIO_BT_SPEECH, 
 *            only 8k or 16kHz is available.
 * @par       Example
 * Sample code please refer to @ref Driver_Usage_Chapter
 */
hal_audio_status_t hal_audio_set_stream_out_sample_rate(hal_audio_sample_rate_t sample_rate);

/**
 * @brief     Set audio output channel number
 * @param[in] channel_number is to set output channel number. Please refers to #hal_audio_channel_number_t.
 * @return    #HAL_AUDIO_STATUS_OK, if channel number is valid 
 * @par       Example
 * Sample code please refer to @ref Driver_Usage_Chapter
 */
hal_audio_status_t hal_audio_set_stream_out_channel_number(hal_audio_channel_number_t channel_number);

/**
 * @brief     Power on audio out 
 * @param[in] active_type is to set output function type. Please refers to #hal_audio_active_type_t.
 * @return    #HAL_AUDIO_STATUS_OK, if output path type is valid
 * @sa        #hal_audio_stream_out_stop  
 * @par       Example
 * Sample code please refer to @ref Driver_Usage_Chapter
 */
 
hal_audio_status_t hal_audio_stream_out_start(hal_audio_active_type_t active_type);

/**
 * @brief     Power off all stream out path
 * @sa        #hal_audio_stream_out_start    
 * @par       Example
 * Sample code please refer to @ref Driver_Usage_Chapter
 */
void hal_audio_stream_out_stop(void);

/**
 * @brief     Set audio output volume
 * @param[in] digital_volume_index is to set digital gain. Gain range: gain map depends
 * @param[in] analog_volume_index is to set digital gain. Gain range: hardware capability and gain map depends
 * @return    #HAL_AUDIO_STATUS_OK, if output volume range is valid  
 * @par       Example
 * Sample code please refer to @ref Driver_Usage_Chapter
 */
hal_audio_status_t hal_audio_set_stream_out_volume(uint32_t digital_volume_index, uint32_t analog_volume_index);

/**
 * @brief     Mute audio output stream 
 * @param[in] mute is a flag to set audio out silence or not
 * @par       example
 * @code      hal_audio_mute_stream_out(true);
 * @endcode
 */
void hal_audio_mute_stream_out(bool mute);

/**
 * @brief     Set audio output device
 * @param[in] device is the ouput component. Refers to #hal_audio_device_t. 
 * @return    #HAL_AUDIO_STATUS_OK, if output device is valid  
 * @par       Example
 * Sample code please refer to @ref Driver_Usage_Chapter
 */
hal_audio_status_t hal_audio_set_stream_out_device(hal_audio_device_t device);

/**
 * @brief     Write data to audio output
 * @param[in] buffer is the pointer to output data.
 * @param[in] size is the available free space of the output buffer.
 * @return    #HAL_AUDIO_STATUS_OK, if OK
 * @sa        #hal_audio_get_stream_out_sample_count      
 * @par       Example
 * Sample code please refer to @ref Driver_Usage_Chapter
 */
hal_audio_status_t hal_audio_stream_out_write(const void *buffer, uint32_t size);

/**
 * @brief      Query available output free space.
 * @param[out] sample_count is available output sample count.   
 * @return     #HAL_AUDIO_STATUS_OK, if OK
 * @note       The function should be called before #hal_audio_stream_out_write is called to make sure free space of the output buffer       
 * @sa         #hal_audio_stream_out_write 
 * @par        Example
 * Sample code please refer to @ref Driver_Usage_Chapter
 */
hal_audio_status_t hal_audio_get_stream_out_sample_count(uint32_t *sample_count);

/**
 * @brief     Register the callback function for output data
 * @param[in] callback is the function pointer of callback for output data control 
 * @param[in] user_data is extended parameter for user.
 * @return    #HAL_AUDIO_STATUS_OK, if OK   
 * @par       Example
 * Sample code please refer to @ref Driver_Usage_Chapter
 */ 
hal_audio_status_t hal_audio_register_stream_out_callback(hal_audio_stream_out_callback_t callback, void *user_data);

/**
 * @brief     Set audio input stream sample rate
 * @param[in] sample_rate is to set input sample rate. Please refers to #hal_audio_sample_rate_t.
 * @return    #HAL_AUDIO_STATUS_OK, if sample rate is valid
 * @note      Only 8k and 16k is support. 
 * @par       Example
 * @code      hal_audio_set_stream_in_sample_rate(HAL_AUDIO_SAMPLE_RATE_8KHZ);
 * @endcode
 */ 
hal_audio_status_t hal_audio_set_stream_in_sample_rate(hal_audio_sample_rate_t sample_rate);

/**
 * @brief     Set audio input channel number
 * @param[in] channel_number is to set input channel number. Please refers to #hal_audio_channel_number_t.
 * @return    #HAL_AUDIO_STATUS_OK, if channel number is valid 
 * @par       Example
 * @code      hal_audio_set_stream_in_channel_number(HAL_AUDIO_MONO);
 * @endcode
 */
hal_audio_status_t hal_audio_set_stream_in_channel_number(hal_audio_channel_number_t channel_number);

/**
 * @brief     Power on audio in 
 * @param[in] active_type is to set input function type. Please refers to #hal_audio_active_type_t.
 * @return    #HAL_AUDIO_STATUS_OK, if input path type is valid
 * @sa        #hal_audio_stream_in_stop 
 * @par       Example
 * @code      hal_audio_stream_in_start(HAL_AUDIO_SPEECH_RECORD);
 * @endcode
 */
hal_audio_status_t hal_audio_stream_in_start(hal_audio_active_type_t active_type);

/**
 * @brief     Power off all stream in path
 * @sa        #hal_audio_stream_out_start    
 * @par       Example
 * @code      hal_audio_stream_in_start();
 * @endcode
 */ 
void hal_audio_stream_in_stop(void);

/**
 * @brief     Set audio input volume
 * @param[in] digital_volume_index is to set digital gain. Gain range: gain map depends
 * @param[in] analog_volume_index is to set digital gain. Gain range: hardware capability and gain map depends
 * @return    #HAL_AUDIO_STATUS_OK, if input volume range is valid  
 * @par       Example
 * Sample code please refer to @ref Driver_Usage_Chapter
 */ 
hal_audio_status_t hal_audio_set_stream_in_volume(uint32_t digital_volume_index, uint32_t analog_volume_index);

/**
 * @brief     Mute audio input stream 
 * @param[in] mute is a flag to set audio out silence or not
 * @par       Example
 * @code      hal_audio_mute_stream_in(true);
 * @endcode
 */
void hal_audio_mute_stream_in(bool mute);

/**
 * @brief     Set audio input device
 * @param[in] device is the input component. Refers to #hal_audio_device_t. 
 * @return    #HAL_AUDIO_STATUS_OK, if input device is valid  
 * @par       Example
 * @code      hal_audio_set_stream_in_device(HAL_AUDIO_DEVICE_MAIN_MIC);
 * @endcode
 */
hal_audio_status_t hal_audio_set_stream_in_device(hal_audio_device_t device);

/**
 * @brief     Recieve data from audio input
 * @param[in] buffer is the pointer of user's buffer.
 * @param[in] sample_count is data amount from reciever.
 * @return    #HAL_AUDIO_STATUS_OK, if OK 
 * @sa        #hal_audio_get_stream_in_sample_count  
 * @par       Example
 * Sample code please refer to @ref Driver_Usage_Chapter
 */
hal_audio_status_t hal_audio_stream_in_read(void *buffer, uint32_t sample_count);

/**
 * @brief      Query available input data sample count.
 * @param[out] sample_count is the available recieve data amount.
 * @return     #HAL_AUDIO_STATUS_OK, if OK 
 * @note       The function should be called before #hal_audio_stream_in_read is called to make sure data amount of the input buffer 
 * @sa         #hal_audio_stream_in_read  
 * @par        Example
 * Sample code please refer to @ref Driver_Usage_Chapter
 */
hal_audio_status_t hal_audio_get_stream_in_sample_count(uint32_t *sample_count);

/**
 * @brief     Register the callback function for input data
 * @param[in] callback is the function pointer of callback for input data control 
 * @param[in] user_data is extended parameter for user.
 * @return    #HAL_AUDIO_STATUS_OK, if OK   
 * @par       Example
 * @code      hal_audio_register_stream_in_callback(stream_in_callback, user_data);
 * @endcode
 */ 
hal_audio_status_t hal_audio_register_stream_in_callback(hal_audio_stream_in_callback_t callback, void *user_data);

/**
 * @brief      Query the size of needed memory to be allocated for internal use in audio driver  
 * @param[out] memory_size is the amount of memory which audio driver needs for internal use (in byte)
 * @return     #HAL_AUDIO_STATUS_OK, if OK.
 * @note       The function should be called at least before #hal_audio_stream_in_start or #hal_audio_stream_out_start_enable to ensure enough memory can be used internally. 
 * @sa         #hal_audio_set_memory
 * @par        Example
 * Sample code please refer to @ref Driver_Usage_Chapter
 */
hal_audio_status_t hal_audio_get_memory_size(uint32_t *memory_size);

/**
 * @brief      Hand over allocated memory to audio driver 
 * @param[in]  memory is the pointer to allocated memory  
 * @return     #HAL_AUDIO_STATUS_OK, if OK.
 * @note       The function should be called after user allocates enough momory which size is at least greater than the size queried from #hal_audio_get_memory_size.
 * @sa         #hal_audio_restore_memory
 * @par        Example
 * Sample code please refer to @ref Driver_Usage_Chapter
 */
hal_audio_status_t hal_audio_set_memory(uint16_t *memory);

#ifdef __cplusplus
}
#endif

/** 
* @} 
* @}
*/
#endif /*HAL_AUDIO_MODULE_ENABLED*/
#endif /*__HAL_AUDIO_H__*/

