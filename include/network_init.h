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

/**
 * @file network_init.h
 *
 */

#ifndef __WIFI_INIT_H__
#define __WIFI_INIT_H__


#include <stdint.h>
#include "lwip/netif.h"


#ifdef __cplusplus
extern "C" {
#endif

/**
* @brief This defines the IP ready callback handler. Call #register_ip_ready_callback() to register a handler, and it will be called on the moment a valid IP address is got after wifi connection is done
*
* @param[in] netif  is the IP information got, including IP address, mask and gateway.
*
*/
typedef void (*wifi_ip_ready_callback_t)(const struct netif *netif);

/**
* @brief This function initializes the network related modules
*
* @return >=0 the operation completed successfully, <0 the operation failed.
*/
void network_init(char** mac_addr);

/**
* @brief This function registers a callback and this callback will be called on the moment a valid IP address is got after wifi connection is done
* @param[in]  callback  is the target function to be called on right moment
*/
void wifi_register_ip_ready_callback(wifi_ip_ready_callback_t callback);

/**
* @note This api is only for internal use
*/
void ip_change_call_back(struct netif *netif);

/**
* @brief This function initializes the network related modules and DHCP.
*/
void network_full_init(void);

/**
* @note This api is only for internal use
*/
uint8_t wifi_set_opmode(uint8_t target_mode);


#ifdef __cplusplus
    }
#endif

#endif /* __WIFI_INIT_H__ */

