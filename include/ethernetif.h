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
 
#ifndef __ETHERNETIF_H
#define __ETHERNETIF_H


#include <stdint.h>

#include <lwip/pbuf.h>
#include "ethernet_filter.h"


typedef enum {
    STA_IP_MODE_STATIC   = 0,
    STA_IP_MODE_DHCP     = 1
} sta_ip_mode_t;

typedef enum _ENUM_DATA_HANDLE_T {
    DATA_HANDLE_LWIP = 0,
    DATA_HANDLE_RX_FILTER
} ENUM_DATA_HANDLE_T;

/**
 * The task function called by net task. Used to simulate incoming packet
 * from SDIO interface port 0 or 1.
 */
void ethernetif_input_sim(uint32_t arg1, uint32_t arg2, uint32_t arg3);
void ethernetif_init_callback(void);
void register_eapol_rx_socket(int eapol_rx_socket);
void unregister_eapol_rx_socket();
void register_eapol_rx_socket_dual_intf(int eapol_rx_socket, int eapol_rx_socket_second);
void unregister_eapol_rx_socket_dual_intf(int eapol_rx_socket, int eapol_rx_socket_second);
int ethernet_raw_pkt_sender(unsigned char *buf, unsigned int len, struct netif *netif);

void low_level_set_mac_addr(struct netif *netif, unsigned char *mac_addr);
#if defined(MTK_BSP_LOOPBACK_ENABLE)
unsigned int loopback_start();
void loopback_start_set(unsigned int start);
#endif
void ethernetif_init(
    sta_ip_mode_t   sta_ip_mode,
    unsigned char   *sta_mac_addr,
    unsigned char   *ap_mac_addr,
	ip4_addr_t *ipaddr0, ip4_addr_t *netmask0, ip4_addr_t *gw0,
	ip4_addr_t *ipaddr1, ip4_addr_t *netmask1, ip4_addr_t *gw1);

#endif /* __ETHERNETIF_H */

