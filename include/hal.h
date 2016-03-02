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
 
#ifndef __HAL_H__
#define __HAL_H__

/** 
 * @addtogroup HAL
 * @{
 *  
 * @section HAL_Overview_1_Chapter	HAL modules acronyms definition and list
 * 
 * |Acronyms                         |Definition                                                                 |
 * |------------------------------|------------------------------------------------------------------------|
 * |\b ACCDET               | Accessory detector
 * |\b ADC                  | Analog-to-digital converter
 * |\b AES                  | Advanced Encryption Standard
 * |\b CMSIS                | Cortex Microcontroller Software Interface Standard
 * |\b CTP                  | Capacitive Touch Panel              
 * |\b EINT                 | External interrupt
 * |\b GDMA                 | General direct memory access
 * |\b GPC                  | General purpose counter
 * |\b GPIO                 | General purpose Input Output
 * |\b GPT                  | General purpose timer
 * |\b I2C                  | Inter-integrated circuit
 * |\b I2S                  | Inter-integrated sound
 * |\b LCD                  | Liquid Crystal Display
 * |\b LCM                  | LCD Module
 * |\b MD5                  | Message-Digest Algorithm
 * |\b MPU                  | Memory protect unit
 * |\b PWM                  | Pulse Width Modulation
 * |\b RTC                  | Real time controller
 * |\b SD                   | Secure Digital Memory Card
 * |\b SDIO                 | Secure Digital Input and Output
 * |\b SHA                  | Secure Hash Algorithm
 * |\b SPI                  | Serial Peripheral interface
 * |\b UART                 | Universal asynchronous receiver/transmitter
 * |\b WDT                  | Watchdog timer
 * |\b TRNG                 | True random number generator
 *
 * @section HAL_Overview_2_Chapter	Overview of HAL drivers
 * 
 * - \b Introduction.\n
 *   The HAL is a hardware abstraction layer on MTK IOT chip. The MTK IOT HAL driver is an embedded software platform, ensuring maximized portability across MTK IOT portfolio.\n
 *   The HAL driver includes:\n
 *   - Drivers for the peripheral modules, such as UART\I2C.\n
 *   - Drivers for part of the system modules, such as CACHE\MPU\FLASH.\n
 *   - Public HAL interface of the modules.\n
 *   .
 *   The HAL driver has standard and advanced features and is easy to use. It makes the upper hardware abstraction layer portable.\n
 *   The HAL layer provides a generic set of APIs (application programming interfaces) to interact with the upper layer (application, middleware and OS).The APIs are MTK IOT standard interface, so the upper layer written with the HAL API is portable across the MTK platforms.\n
 *   The HAL driver covers rich modules, including all peripheral modules, such as UART, I2C etc. It also includes the part of system modules, such as CACHE, MPU, FLASH, etc. Every module has a rich set of interfaces to enable the application to use the chip set very well. For example, the application can use the UART in polling mode or in interrupt mode (UART DMA mode).\n
 *   The HAL complies to the general naming convention and common coding style. Each module of the HAL has its distinctive folder structure along with good examples.
 *
 * - \b HAL \b driver \b architecture.\n
 * The HAL driver architecture is as follows:\n\r
 * @image html hal_overview_driver_architecture.png
 *
 * - \b HAL \b and \b user-application \b files.\n
 *  - \b HAL \b folder \b structure.\n
 *    The HAL module folder structure is as follows:
 * @image html hal_overview_folder_structure.png \n
 *    - Driver: All common driver files, such as board driver\HAL driver and CMSIS etc.\n
 *    - Driver/board: The driver files that are associated with the board, such as CTP or LCM.\n
 *    - Driver/chip/inc: The public files of the HAL.\n
 *    - Driver/chip/mt****: The driver files that are associated with the chip, such as UART, I2C, GPT, PWM, WDT etc.\n
 *    - Driver/CMSIS: The files that are associated with CMSIS-CORE.\n
 *
 *  - \b File \b inclusion \b model.\n
 *@image html hal_overview_file_inclusion_model.png \n
 * \n
 * \n
 *
 *
 *
 * @section HAL_Overview_3_Chapter	 HAL Driver Model
 * Some of the drivers can operate in multiple modes: polling, interrupt.
 * The UART HAL driver, for example, can operate in polling and interrupt modes during data communication. The polling mode is suitable for read and write operation of small amount of data in low frequency. The interrupt mode is suitable for read and write operation of small amount of data in high frequency. In UART DMA mode, for example, an interrupt is triggered once the DMA completes.
 * - \b Polling \b mode \b architecture.\n
 *   Most of the driver modules support the polling mode, which is the basic feature in HAL.\n
 *   For example, we can setup a time delay with hal_gpt_delay_us() in the GPT. The GPT HAL driver will poll the GPT hardware when the time delay is reached.\n
 *   The polling mode driver architecture is as follows:
 *   @image html hal_overview_driver_polling_architecture.png \n
 *
 * - \b Interrupt \b mode \b architecture.\n
 *   To improve the portability, the HAL drivers hide the OS dependence, by preventing the upper layer from calling the OS level services directly. The HAL drivers use the interrupt handler to provide the upper layer with the callback mechanism.
 *
 *   To use the interrupt handler of a driver module, a callback should be registered with the interrupt handler. When the interrupt occurs, the callback will be invoked in CM4 handler mode.
 *   With the interrupt mode (UART DMA mode) of the UART, for example, we call the API of hal_uart_send_dma() to send data. The UART HAL driver will copy the data to DMA buffer and start DMA operation, and the hal_uart_send_dma() returns straight away. At the same time, the DMA is sending data to UART hardware. When the DMA operation completes, the DMA interrupt will be issued. The UART HAL driver will invoke the user callback in interrupt handler. So that we know the data has been sent out by the UART.
 *   Another example of the interrupt is the GPT interrupt mode. We call the API of hal_gpt_start_timer_ms() to start a timer. When the timer expires, the GPT hardware will issue an interrupt. Then the GPT HAL driver will invoke the user callback in interrupt handler. So that we know the timer is expired.
 *   The interrupt mode driver architecture is as follows:
 *   @image html hal_overview_interrupt_mode_architecture.png \n
 *
 * @}
 */


#include "hal_feature_config.h"

/***************************************************************************** 
* module header file include
*****************************************************************************/

#ifdef HAL_ADC_MODULE_ENABLED
    #include "hal_adc.h"
#endif

#ifdef HAL_AES_MODULE_ENABLED
    #include "hal_aes.h"
#endif

#ifdef HAL_DES_MODULE_ENABLED
    #include "hal_des.h"
#endif

#ifdef HAL_AUDIO_MODULE_ENABLED
    #include "hal_audio.h"
#endif

#ifdef HAL_CACHE_MODULE_ENABLED
    #include "hal_cache.h"
#endif

#ifdef HAL_DES_MODULE_ENABLED
    #include "hal_des.h"
#endif

#ifdef HAL_EINT_MODULE_ENABLED
    #include "hal_eint.h"
#endif

#ifdef HAL_FLASH_MODULE_ENABLED
    #include "hal_flash.h"
#endif

#ifdef HAL_GDMA_MODULE_ENABLED
    #include "hal_gdma.h"
#endif

#ifdef HAL_GPC_MODULE_ENABLED
    #include "hal_gpc.h"
#endif

#ifdef HAL_GPIO_MODULE_ENABLED
    #include "hal_gpio.h"
#endif

#ifdef HAL_GPT_MODULE_ENABLED
    #include "hal_gpt.h"
#endif

#ifdef HAL_I2C_MASTER_MODULE_ENABLED
    #include "hal_i2c_master.h"
#endif

#ifdef HAL_I2S_MODULE_ENABLED
    #include "hal_i2s.h"
#endif

#ifdef HAL_IRRX_MODULE_ENABLED
    #include "hal_irrx.h"
#endif

#ifdef HAL_IRTX_MODULE_ENABLED
    #include "hal_irtx.h"
#endif

#ifdef HAL_ISINK_MODULE_ENABLED
    #include "hal_isink.h"
#endif

#ifdef HAL_KEYPAD_MODULE_ENABLED
    #include "hal_keypad.h"
#endif

#ifdef HAL_MD5_MODULE_ENABLED
    #include "hal_md5.h"
#endif

#ifdef HAL_MPU_MODULE_ENABLED
    #include "hal_mpu.h"
#endif

#ifdef HAL_NVIC_MODULE_ENABLED
    #include "hal_nvic.h"
#endif

#ifdef HAL_PWM_MODULE_ENABLED
    #include "hal_pwm.h"
#endif

#ifdef HAL_RTC_MODULE_ENABLED
    #include "hal_rtc.h"
#endif

#ifdef HAL_SD_MODULE_ENABLED
    #include "hal_sd.h"
#endif

#ifdef HAL_SDIO_MODULE_ENABLED
    #include "hal_sdio.h"
#endif

#ifdef HAL_SHA_MODULE_ENABLED
    #include "hal_sha.h"
#endif

#ifdef HAL_SPI_MASTER_MODULE_ENABLED
    #include "hal_spi_master.h"
#endif

#ifdef HAL_SPI_SLAVE_MODULE_ENABLED
    #include "hal_spi_slave.h"
#endif

#ifdef HAL_TRNG_MODULE_ENABLED
    #include "hal_trng.h"
#endif

#ifdef HAL_UART_MODULE_ENABLED
    #include "hal_uart.h"
#endif

#ifdef HAL_WDT_MODULE_ENABLED
    #include "hal_wdt.h"
#endif



#ifdef __cplusplus
    extern "C" {
#endif


#ifdef __cplusplus
}
#endif

#endif /* __HAL_H__ */ 

