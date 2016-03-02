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
 * @file wifi_api.h
 *
 * WiFi processor configure / setting for STA operations
 *
 * @author  Michael Rong
 * @version 2015/04/24 Initial
 * @version 2015/06/03 API alternation and Doxygen warning fix.
 */

#ifndef __WIFI_INBAND_H__
#define __WIFI_INBAND_H__

#include "stdint.h"
#include "type_def.h"
#include "wifi_api.h"


#ifdef __cplusplus
extern "C" {
#endif

#define WIFI_APPLE_IE_MAX_LENGTH          (256)

/** @brief Enable wake on wireless or not.
*/
typedef struct {
    bool enable; /**< 0: disable, 1:enable */
} wifi_wow_enable_t;

/** @brief Wake up host by magic packet.
*/
typedef struct {
    uint8_t bss_index; /**< BSS Index (BIT(0) enable for BSSID0, BIT(1) enable for BSSID1, BIT(2) enable for BSSID2, BIT(3) enable for BSSID3) */
    bool enable; /**< 0: disable, 1:enable the magic packet filter */
} wifi_wow_magic_packet_t;

/** @brief Wake up host on receiving packet with specific pattern.
*/
typedef struct {
    uint8_t bitmap_mask[16]; /**< 16 bytes of Bitmap mask, each bit of bitmap_mask[] use to mask corresponding byte of bitmap_pattern[] */
    uint8_t bitmap_pattern[128]; /**< 128 bytes of Bitmap pattern */
} wifi_wow_bitmap_pattern_t;

/** @brief ARP offloading.
*/
typedef struct {
    uint8_t ip_address[4]; /**< e.g.192.168.0.11-->ip_address[]={192, 168, 0, 11} */
} wifi_wow_arp_offload_t;

/** @brief Re-key offloading.
*/
typedef struct {
    uint8_t ptk[64]; /**< 64 bytes Pairwise Transient Key */
} wifi_wow_rekey_offload_t;

/** @brief Manage power state.
*/
typedef struct {
    uint8_t power_manage_number;
    uint8_t power_manage_state;
} wifi_power_manage_state_t;

#define MAX_WEP_KEY_SIZE_CM4 32
typedef struct _wep_key_cm4 {
	uint8_t ucdefault_key_id;
	uint8_t auckey_0[MAX_WEP_KEY_SIZE_CM4];
	uint8_t uckey_0_len;
	uint8_t auckey_1[MAX_WEP_KEY_SIZE_CM4];
	uint8_t uckey_1_len;
	uint8_t auckey_2[MAX_WEP_KEY_SIZE_CM4];
	uint8_t uckey_2_len;
	uint8_t auckey_3[MAX_WEP_KEY_SIZE_CM4];
	uint8_t uckey_3_len;
} wep_key_cm4_t;

typedef enum _extra_ie_type {
    WIFI_EXTRA_WPS_BEACON_IE = 0,
    WIFI_EXTRA_WPS_PROBE_REQ_IE = 1,
    WIFI_EXTRA_WPS_PROBE_RSP_IE = 2,
    WIFI_EXTRA_WPS_ASSOC_REQ_IE = 3,
    WIFI_EXTRA_WPS_ASSOC_RSP_IE = 4,
#ifdef MTK_WIFI_DIRECT_ENABLE
    WIFI_EXTRA_P2P_BEACON_IE = 5,
    WIFI_EXTRA_P2P_PROBE_REQ_IE = 6,
    WIFI_EXTRA_P2P_PROBE_RSP_IE = 7,
    WIFI_EXTRA_P2P_ASSOC_REQ_IE = 8,
    WIFI_EXTRA_P2P_ASSOC_RSP_IE = 9,
#endif /*MTK_WIFI_DIRECT_ENABLE*/
} extra_ie_type_t;

typedef struct _extra_ie {
	uint8_t port;
	uint8_t type; /* extra_ie_type */
	uint8_t rsv[2];
	uint32_t extra_ie_len;
#ifndef __CC_ARM
	uint8_t extra_ie[0];
#else
	uint8_t extra_ie[];
#endif
} extra_ie_t;

typedef enum _wifi_tx_mode_t {
    WIFI_MODE_CCK = 0,
    WIFI_MODE_OFDM,
    WIFI_MODE_HTMIX,
    WIFI_MODE_HTGREENFIELD,
    WIFI_MODE_VHT,
    WIFI_MODE_MAX
} wifi_tx_mode_t;


#ifdef MTK_WIFI_DIRECT_ENABLE
typedef struct _P2P_LISTEN_PARAM{
                uint8_t  channel;
                uint8_t  ucReserved;
                uint16_t ListenDuration;                              //in milliseconds
}P2P_LISTEN_PARAM;
#endif /*MTK_WIFI_DIRECT_ENABLE*/

typedef struct _txd_param {
    uint8_t frame_protected; /* 0/1: Disable/Enable protection */
    uint8_t ack_required;           /* 0/1: Disable/Enable ACK */
    uint8_t rate_fixed;       /* 0/1: Disable/Enable Fixed rate */
    uint8_t tx_mode;    /*  0: MODE_CCK, 1: MODE_OFDM, 2: MODE_HTMIX, 3: MODE_HTGREENFIELD, 4: MODE_VHT  */
    uint8_t mcs;   /* Note 1 */
    uint8_t retry_count;    /* 0: No Retry, 1-30: Retry count, 31: Unlimited Retry count  */
    uint8_t reserved[2];
} txd_param_t;

/**
* @brief Get/Set WiFi Operation Mode.
*
* @param [IN]flag_set
* @param [OUT]mode
* @param 0x01 WIFI_MODE_STA_ONLY
* @param 0x02 WIFI_MODE_AP_ONLY
* @param 0x03 WIFI_MODE_DUAL
*
* @return  >=0 means success, <0 means fail
*/
int32_t wifi_inband_opmode(uint8_t flag_set, uint8_t *mode);

/**
* @brief Configure bandwidth.
*
* @param [IN]flag_set
* @param [IN]port
* @param [IN/OUT] bandwidth  IOT_CMD_CBW_20MHZ, IOT_CMD_CBW_40MHZ , IOT_CMD_CBW_2040MHZ are supported
*
* @return >=0 means success, <0 means fail
*
* @note Default value will be HT_20
*/
int32_t wifi_inband_bandwidth(uint8_t flag_set, uint8_t port, uint8_t *bandwidth);

/**
* @brief Get/Set the current channel for STA wireless port.
*
* @param [IN]flag_set
* @param [IN]port
* @param [IN/OUT] channel I1~14 are supported for 2.4G only product
*
* @return >=0 means success, <0 means fail
*/
int32_t wifi_inband_channel(uint8_t flag_set, uint8_t port, uint8_t *channel);

/**
* @brief Register the handler to receive 802.11 raw packet from network processor .
* @      and the network processor begin to indicate 802.11 raw packet with RXWI
* @param [IN] enable/disable
*
* @return >=0 means success, <0 means fail
*/
int32_t wifi_inband_set_raw_pkt(uint8_t enable);

#if 0
/**
* @brief Get/Set WiFi Interface MAC Address.
*
* @param [IN]flag_set
* @param [IN]port
* @param [IN/OUT]address
* @param MAC Address
*
* @return  >=0 means success, <0 means fail
*/
int32_t wifi_inband_mac_address(uint8_t flag_set, uint8_t port, uint8_t *address);
#endif

/**
* @brief Get/Set WiFi SSID.
*
* @param [IN]flag_set
* @param [IN]port
* @param 0 STA
* @param 1 AP
* @param [IN/OUT]ssid SSID
* @param [IN/OUT]ssid_len Length of SSID
*
* @return  >=0 means success, <0 means fail
*/
int32_t wifi_inband_ssid(uint8_t flag_set, uint8_t port, uint8_t *ssid, uint8_t *ssid_length);

/**
* @brief Get/Set WiFi BSSID.
*
* @param [IN]flag_set
* @param [IN/OUT]bssid BSSID
*
* @return  >=0 means success, <0 means fail
* @note Only used for WIFI_PORT_STA
*/
int32_t wifi_inband_bssid(uint8_t flag_set, uint8_t *bssid);

/**
* @brief Get/Set WiFi Wireless Mode
*
* @param [IN]flag_set
* @param [IN]port
* @param [IN/OUT]mode
* @param  1 legacy 11B only
* @param 2 legacy 11A only
* @param 3 legacy 11A/B/G mixed
* @param 4 legacy 11G only
* @param 5 11ABGN mixed
* @param 6 11N only in 2.4G
* @param 7 11GN mixed
* @param 8 11AN mixed
* @param 9 11BGN mixed
* @param 10 11AGN mixed
*
*/
int32_t wifi_inband_wireless_mode(uint8_t flag_set, uint8_t port, uint8_t *mode);

/**
* @brief Get/Set WiFi Country Region
*
* @param [IN]flag_set
* @param [IN]band
* @param 0 2.4G
* @param 1 5G
*
* @param [IN/OUT]region
* @region: (2.4G)
* @param  0   CH1-11
* @param  1   CH1-13
* @param  2   CH10-11
* @param  3   CH10-13
* @param  4   CH14
* @param  5   CH1-14 all active scan
* @param  6   CH3-9
* @param  7   CH5-13
* @param
* @param  region: (5G)
* @param  0   CH36, 40, 44, 48, 52, 56, 60, 64, 149, 153, 157, 161, 165
* @param  1   CH36, 40, 44, 48, 52, 56, 60, 64, 100, 104, 108, 112, 116, 120, 124, 128, 132, 136, 140
* @param  2   CH36, 40, 44, 48, 52, 56, 60, 64
* @param  3   CH52, 56, 60, 64, 149, 153, 157, 161
* @param  4   CH149, 153, 157, 161, 165
* @param  5   CH149, 153, 157, 161
* @param  6   CH36, 40, 44, 48
* @param  7   CH36, 40, 44, 48, 52, 56, 60, 64, 100, 104, 108, 112, 116, 120, 124, 128, 132, 136, 140, 149, 153, 157, 161, 165
* @param  8   CH52, 56, 60, 64
* @param  9   CH36, 40, 44, 48, 52, 56, 60, 64, 100, 104, 108, 112, 116, 132, 136, 140, 149, 153, 157, 161, 165
* @param  10   CH36, 40, 44, 48, 149, 153, 157, 161, 165
* @param  11   CH36, 40, 44, 48, 52, 56, 60, 64, 100, 104, 108, 112, 116, 120, 149, 153, 157, 161
*/
int32_t wifi_inband_country_region(uint8_t flag_set, uint8_t band, uint8_t *region);


/**
* @brief Get/Set WiFi DTIM Interval
*
* @param [IN]flag_set
* @param [IN/OUT]interval 1 ~ 255
*
* @return  >=0 means success, <0 means fail
*
*/
int32_t wifi_inband_dtim_interval(uint8_t flag_set, uint8_t *interval);

/**
* @brief Get/Set WiFi Listen Interval
*
* @param [IN]flag_set
* @param [IN/OUT]interval 1 ~ 255
*
*/
int32_t wifi_inband_listen_interval(uint8_t flag_set, uint8_t *interval);


/**
* @brief Get/Set WiFi Radio ON/OFF
*
* @param [IN]flag_set
* @param [IN/OUT]onoff
* @param 0 OFF
* @param 1 ON
*
* @return  >=0 means success, <0 means fail
*
* @note in MODE_Dual, both WiFi interface radio will be turn on/off at the same time
*/
int32_t wifi_inband_radio_on(uint8_t flag_set, uint8_t *onoff);


/**
* @brief Set the authentication mode for the target AP
*
* @param [IN]authmode
* @param 0 OPEN
* @param 1 SHARED
* @param 2 WEPAUTO
* @param 3 WPA
* @param 4 WPAPSK
* @param 5 WPANONE
* @param 6 WPA2
* @param 7 WPA2PSK
* @param 8 WPA1WPA2
* @param 9 WPA1PSKWPA2PSK
*
* @return >=0 means success, <0 means fail
* @note Default to OPEN
*/
int32_t wifi_inband_set_auth_mode(uint8_t port, uint8_t authmode);

/**
* @brief Set the encryption method for the target AP
*
* @parameter
*   [IN] encryption method index:
*         1 NONE
*         0 WEP
*         4 TKIP
*         6 AES
*         TKIPAES
* @return >=0 means success, <0 means fail
* @note Default to NONE
*/
int32_t wifi_inband_set_encryption(uint8_t port, uint8_t encryption);

/**
* @brief Set WiFi WEP Keys
*
* @param [IN]wep_key_cm4_t
*
* @return >=0 means success, <0 means fail
*/
int32_t wifi_inband_set_wep_key(uint8_t port, wep_key_cm4_t *wep_keys);

/**
* @brief Set WiFi PTK Keys
*
* @param [IN]keys
*
* @return >=0 means success, <0 means fail
*/
int32_t wifi_inband_set_PTK_key(uint8_t port, uint8_t *keys);


/**
* @brief Disconnect the current connection
*
* @parameter address
* @return >=0 means success, <0 means fail
* @note if WIFI_PORT_STA or PORT_APCLI, it  will back to scan state once disconnect from AP
* @note if WIFI_PORT_AP, send the disconnected STA's mac address as parameter.
*/
int32_t wifi_inband_disconnect(uint8_t port, uint8_t *address);

/**
* @brief Get the current STA port link up / link down status of the connection
*
* @parameter None
* @return >=0 means success, the status will be:
*               WIFI_STATUS_LINK_DISCONNECTED(0) and
*               WIFI_STATUS_LINK_CONNECTED(1),
*               <0 means fail
* @note WIFI_STATUS_LINK_DISCONNECTED indicates STA may in IDLE/ SCAN/ CONNECTING state
*/
int32_t wifi_inband_get_link_status(uint8_t *link_status);

/**
* @brief Get WiFi Associated Station List
*
* @param [OUT]station_list
*
* @return Number of associated stations will be returned
*/
int32_t wifi_inband_get_station_list(uint8_t *number, wifi_sta_list_t *station_list);

/**
* @brief Get the max number of the supported stations in ap mode or dual mode.
*
* @param [OUT]sta_number The max number of the supported stations will be returned
*
* @return  >=0 means success, <0 means fail
*
*/
int32_t wifi_inband_get_max_station_number(uint8_t *sta_number);


/**
* @brief Star WiFi Scanning
*
* @param [IN]ssid SSID
* @param [IN]ssid_length Length of SSID
* @param [IN]bssid BSSID
* @param [IN]scan_mode
* @param 0 full
* @param 1 partial
* @param [IN]scan_option
* @param 0: active (passive in regulatory channel)
* @param 1: passive in all channel
* @param 2: force_active (active in all channel)
*
* @return  >=0 means success, <0 means fail
*
* @note When SSID/BSSID specified (not NULL)
* @note 1. ProbeReq carries SSID (for Hidden AP)
* @note 2. Scan Table always keeps the APs of this specified SSID/BSSID
*/
int32_t wifi_inband_start_scan(uint8_t *ssid, uint8_t ssid_length, uint8_t *bssid, uint8_t scan_mode, uint8_t scan_option);

/**
* @brief Stop WiFi Scanning
*
* @return  >=0 means success, <0 means fail
*/
int32_t wifi_inband_stop_scan(void);

#ifdef MTK_WIFI_DIRECT_ENABLE
/**
* @brief Start WiFi p2p listen procedure (remain_on_channel)
*
* @return  >=0 means success, <0 means fail
*/
int32_t wifi_inband_p2p_listen(P2P_LISTEN_PARAM* remain_on_channel_param);
#endif /*MTK_WIFI_DIRECT_ENABLE*/

/**
* @brief Configure packet format wanted to be received
*
* @param [IN/OUT]filter defined in  wifi_rx_filter_t
*
* @return >=0 means success, <0 means fail
*/
int32_t wifi_inband_rx_filter(uint8_t flag_set, uint32_t *filter);

/**
* @brief Set/Get MTK Smart Connection Filter
*
* @param [IN]flag_set
* @param [IN/OUT]enable
*
* @return  >=0 means success, <0 means fail
*/
int32_t wifi_inband_smart_connection(uint8_t flag_set, uint8_t  *enable);

/**
* @brief Inform N9 to do ApStop
*
* @return >=0 means success, <0 means fail
*/
int32_t wifi_inband_set_ap_stop(void);

/**
* @brief Inform N9 to do ApStart
*
* @return >=0 means success, <0 means fail
*/
int32_t wifi_inband_set_ap_start(void);

/**
* @brief Set WiFi Extra IE
*
* @param [IN]port
* @param 0 AP
* @param 1 AP Client
* @param 2 STA
* @param [IN]ie_type
* @param [IN]extra_ie
* @param [IN]extra_ie_len
*
* @return  >=0 means success, <0 means fail
*/
int32_t wifi_inband_set_extra_ie(uint8_t port, uint8_t ie_type, uint8_t *extra_ie, uint32_t extra_le_len);

/**
* @brief Get the rssi of the connected AP
*
* @parameter None
*
* @return  >=0 means success, <0 means fail
*/
int32_t wifi_inband_get_rssi(int8_t *rssi);

/**
* @brief Inform N9 to configure PSMode
* @param [IN] ps mode
*
* @return >=0 means success, <0 means fail
*/
int32_t wifi_inband_set_ps_mode(uint8_t ps_mode);

/****************************************************************************/

/**
 * Defines the macro for EFUSE address space.
 */
typedef enum
{
    EFUSE_ADDR_SPACE_LOGICAL  = 0,
    EFUSE_ADDR_SPACE_PHYSICAL = 1
} efuse_address_space_t;


#define EFUSE_WRITE_MAGIC   (0xFEEDBABE)


/**
 * get the number of available blocks in eFuse.
 */
int32_t wifi_inband_get_efuse_free(uint32_t *free_blocks);

/**
 * Read eFuse.
 */
int32_t wifi_inband_get_efuse(efuse_address_space_t space,
                              uint16_t              address,
                              uint8_t               *buffer);

/**
 * magic number has to be EFUSE_WRITE_MAGIC.
 */
int32_t wifi_inband_set_efuse(efuse_address_space_t space,
                              uint16_t              address,
                              const uint8_t         *buffer,
                              uint8_t               len,
                              uint32_t              magic);


/**
 * query the needed blocks for writing eFuse content.
 */
int32_t wifi_inband_query_efuse(efuse_address_space_t space,
                                uint16_t              address,
                                const uint8_t         *buffer,
                                uint8_t               len,
                                uint8_t               *ok,
                                uint8_t               *used,
                                uint8_t               *noop,
                                uint8_t               *reuse);

/****************************************************************************/

/**
* @brief Update Apple Device IE
*
* @param[in] is_unconfigured is this device unconfigured.
*
* @return  >=0 means success, <0 means fail
*/
int32_t wifi_update_apple_ie(uint8_t is_unconfigured);

/**
* @brief Enable / Disable Apple Air Play
*
* @param[in] enable
*
* @return  >=0 means success, <0 means fail
*/
int32_t wifi_enable_air_play(uint8_t enable);

/**
* @brief Init WIFI module and wait for ready.
*
* @return  >=0 means success, <0 means fail
*/
int32_t wifi_config_init(void);
int32_t wifi_inband_tx_raw(uint8_t *payload, uint32_t len, txd_param_t *txd_param);

#ifdef MTK_WIFI_CONFIGURE_FREE_ENABLE
typedef enum wifi_inband_packet_type_e
{
    WIFI_BEACON_PACKET_TYPE_ID,                 /**< beacon                     */
    WIFI_PROBE_REQUEST_PACKET_TYPE_ID,          /**< probe request              */
    WIFI_PROBE_RESPONSE_PACKET_TYPE_ID,         /**< probe response             */
    WIFI_ASSOCIATION_REQUEST_PACKET_TYPE_ID,    /**< assoication request        */
    WIFI_ASSOCIATION_RESPONSE_PACKET_TYPE_ID,   /**< clear assoication response */
    WIFI_PACKET_TYPE_CLEAR_ALL_ID               /**< clear all packets          */
} wifi_inband_packet_type_t;

typedef enum wifi_inband_port_id_e
{
    WIFI_INBAND_APCLI_STA_PORT = 0,
    WIFI_INBAND_AP_PORT
} wifi_inband_port_id_t;

int32_t wifi_inband_set_ie(wifi_inband_packet_type_t   packet_type,
                           wifi_inband_port_id_t       port,
                           uint16_t                    ie_length,
                           uint8_t                     *ie_body);
#endif /* MTK_WIFI_CONFIGURE_FREE_ENABLE */

#ifdef __cplusplus
}
#endif

#endif /* WIFI_API */

