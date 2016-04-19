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
 * WIFI processor configuration / settings for the STA operations.
 *
 */

 /**@addtogroup WIFI
 * @{
 * This section introduces the WIFI driver APIs including terms and acronyms, supported features,
 * software architecture, details on how to use this driver, WIFI function groups, enumerations,
 * structures and functions. The WIFI APIs are divided into three categories:
 * Profile, Configure and Connect.
 *
 * Profile APIs are used to get/set the
 * profile in NVRAM, NVRAM is an area on the flash. The profile settings can be read by
 * WIFI profile get APIs. The profile settings can be used to initialize the WIFI
 * driver configuration at system boot up. There are many profile sections in the NVRAM, such as:
 * STA, AP, common. Use the same profile section for #WIFI_PORT_STA/#WIFI_PORT_APCLI.
 * The new profile settings can be stored in the flash only by calling
 * wifi_profile_commit_setting() API followed by WIFI profile set APIs.
 *
 * Configure APIs are used to get and set the WIFI driver configuration. In most cases they take effect
 * immediately, but there are some configuration APIs that only take
 * effect by calling wifi_config_reload_setting() API, such as: \n
 * wifi_config_set_pmk() \n
 * wifi_config_set_security_mode() \n
 * wifi_config_set_ssid() \n
 * wifi_config_set_wep_key() \n
 * wifi_config_set_wpa_psk_key() \n
 * The configure APIs use in-band mechanism (in-band is a mechanism used for WIFI driver and WIFI Firmware communication),
 * thus these APIs must be called after OS task scheduler is started to make sure an in-band task is running.
 * The function #wifi_config_register_rx_handler() registers wifi_rx_handler() to manage the raw packet. There is a limitation calling this handler as it's using an in-band mechanism,
 * it's restricted to call any in-band functions like WIFI configure or WIFI connect APIs in wifi_rx_handler().
 *
 * The connect APIs are used to manage the link status, such as: disconnect AP, disconnect the station, get the link status, get the station list, start/stop scan.
 * Register event handler for scan/connect/disconnect event. The connect APIs use an in-band mechanism, thus these APIs must be called after the OS Task
 * scheduler is started, to make sure an in-band task is running.
 *
 * @section HAL_ADC_Terms_Chapter Terms and acronyms
 *
 * Terms                         |Details                                                                 |
 * ------------------------------|------------------------------------------------------------------------|
 * \b STA                        | In station (STA) mode the device operates as a client that connects to a WIFI access point.|
 * \b AP                         | In Access Point (AP) mode other devices can connect to the WIFI access point.|
 * \b APCLI                      | In AP Client (APCLI) mode the Access Point becomes a wireless client for another AP.|
 * \b DTIM                       | Delivery Traffic Indication Message (DTIM) is how the AP (wireless router) warns its clients that it is about to transmit the multicast (and broadcast*) frames it queued up since the previous DTIM. For more information, please refer to <a href="https://en.wikipedia.org/wiki/Delivery_traffic_indication_message">introduction to DTIM in Wikipedia</a>. |
 * \b MCS                        | Modulation and Coding Set (MCS) implies the packet data rate. For more information, please refer to <a href="https://en.wikipedia.org/wiki/Link_adaptation">introduction to MCS in Wikipedia</a>.|
 * \b WPS                        | Wi-Fi Protected Setup(WPS) is a network security standard to create a secure wireless home network. For more information, please refer to <a href="https://en.wikipedia.org/wiki/Wi-Fi_Protected_Setup">introduction to WPS in Wikipedia</a>.|
 * \b PIN                        | Personal indentification number(PIN) is a method of WPS, has to be read from either a sticker or display on the new wireless device. This PIN must then be entered at the "representant" of the network, usually the network's AP. Alternately, a PIN provided by the AP may be entered into the new device. This method is the mandatory baseline mode and everything must support it. The Wi-Fi direct specification supersedes this requirement by stating that all devices with a keypad or display must support the PIN method.|
 * \b PBC                        | Push button (PBC) is a method of WPS. For more information, please refer to <a herf="https://en.wikipedia.org/wiki/Wi-Fi_Protected_Setup">introduction to PBC in Wikipedia</a>.|
 * \b STBC                       | Space-time Block Code (STBC) used in wireless telecommunications. Space-time block coding is a technique used in wireless communications to transmit multiple copies of a data stream across a number of antennas and to exploit the various received versions of the data to improve the reliability of data-transfer. For more information, please refer to <a href="https://en.wikipedia.org/wiki/Space%E2%80%93time_block_code">introduction to STBC in Wikipedia</a>.|
 * \b FCS                        | Frame Check Sequence (FCS) refers to the extra error-detecting code added to a frame in a communications protocol. For more information, please refer to <a href="https://en.wikipedia.org/wiki/Frame_check_sequence">introduction to FCS in Wikipedia</a>.|
 * \b Broadcast                  | A communication where a piece of information is sent from one point to all other points.|
 * \b Multicast                  | A communication where a piece of information is sent from one or more points to a set of other points.|
 * \b RTS                        | Request to Send (RTS) is IEEE 802.11 control signal is an optional mechanism used by the 802.11 wireless networking protocol to reduce frame collisions. For more information, please refer to <a href="https://en.wikipedia.org/wiki/RTS/CTS">introduction to RTS in Wikipedia</a>.|
 * \b CTS                        | Clear to Send (CTS) is IEEE 802.11 control signal is an optional mechanism used by the 802.11 wireless networking protocols to reduce frame collisions. For more information, please refer to <a href="https://en.wikipedia.org/wiki/RTS/CTS">introduction to CTS in Wikipedia</a>.|
 * \b RSSI                       | Received Signal Strength Indication (RSSI). For more information, please refer to <a href="https://en.wikipedia.org/wiki/Received_signal_strength_indication">introduction to RSSI in Wikipedia</a>. |
 * \b Beacon                     | Beacon frame is one of the management frames in IEEE 802.11 based WLANs.|
 * \b WPA                        | Wi-Fi Protected Access (WPA) is a wireless encryption standard. For more information, please refer to <a href="https://en.wikipedia.org/wiki/Wi-Fi_Protected_Access">introduction to WPA in Wikipedia</a>.|
 * \b WPS                        | Wi-Fi Protected Setup (WPS) is a network security standard. For more information, please refer to <a href="https://en.wikipedia.org/wiki/Wi-Fi_Protected_Setup">introduction to WPS in Wikipedia</a>.|
 * \b OPMODE                     | Operate Mode (OPMODE) is STA/AP/APCLI.|
 * \b PSK                        | Pre-shared key (PSK) is a method to set encryption keys. For more information, please refer to <a href="https://en.wikipedia.org/wiki/Pre-shared_key">introduction to PSK in Wikipedia</a>.|
 * \b PMK                        | Pair-wise Master Key (PMK) is calculated from PSK.|
 * \b WEP                        | Wired Equivalent Privacy (WEP) is a wireless network security standard. For more information, please refer to <a href="https://en.wikipedia.org/wiki/Wired_Equivalent_Privacy">introduction to WEP in Wikipedia</a>.|
 * \b WOW                        | Wake on Wireless (WOW) is a technology that allows remote wake-up of workstations from a standby power state to facilitate device management. |
 * \b TKIP                       | Temporal Key Integrity Protocol (TKIP) is an algorithm used to secure wireless computer networks. For more information, please refer to <a href="https://en.wikipedia.org/wiki/Temporal_Key_Integrity_Protocol">introduction to TKIP in Wikipedia</a>.|
 * \b AES                        | Advanced Encryption Standard process (AES) is a 'symmetric block cipher' for encrypting texts which can be decrypted with the original encryption key. For more information, please refer to <a href="https://en.wikipedia.org/wiki/Advanced_Encryption_Standard">introduction to AES in Wikipedia</a>.|
 * \b NVRAM                      | Non-volatile random-access memory (NVRAM) is random-access memory that retains its information when power is turned off (non-volatile). For more information, please refer to <a href="https://en.wikipedia.org/wiki/Non-volatile_random-access_memory">introduction to NVRAM in Wikipedia</a>.|
 * \b PHY                        | PHY of the Open system Interconnection(OSI) model and refers to the circuitry required to implement physical layer functions. For more information, please refer to <a href="https://en.wikipedia.org/wiki/PHY_(chip)">introduction to PHY in Wikipedia</a>.|
 * \b BSS                        | The basic service set (BSS) provides the basic building-block of an 802.11 wireless LAN. For more information, please refer to <a href="https://en.wikipedia.org/wiki/Service_set_%28802.11_network%29">introduction to 802.11 network in Wikipedia</a>.|
 * \b IBSS                       | With 802.11, one can set up an ad hoc network of client devices without a controlling access point; the result is called an IBSS (independent BSS). For more information, please refer to <a href="https://en.wikipedia.org/wiki/Service_set_%28802.11_network%29">introduction to 802.11 network in Wikipedia</a>.|
 * \b MCS                        | Modulation and Coding Scheme (MCS) is related to the maximum data rate and robustness of data transmission. For more information, please refer to <a href="https://en.wikipedia.org/wiki/Link_adaptation">introduction to Link adaptation in Wikipedia</a>.|
 * \b LDPC                       | In information theory, a low-density parity-check (LDPC) code is a linear error correcting code, a method of transmitting a message over a noisy transmission channel. For more information, please refer to <a href="https://en.wikipedia.org/wiki/Low-density_parity-check_code">introduction to Low-density parity-check code in Wikipedia</a>.|
 * \b GI                         | In telecommunications, guard intervals (GI) are used to ensure that distinct transmissions do not interfere with one another. For more information, please refer to <a href="https://en.wikipedia.org/wiki/Guard_interval">introduction to Guard interval in Wikipedia</a>.|
 * \b MPDU                       | MPDU stands for MAC protocol data unit.|
 * \b TSC                        | TKIP uses a per-MPDU TKIP sequence counter (TSC) to sequence the MPDUs it sends. The receiver drops MPDUs received out of order, i.e., not received with increasing sequence numbers.|
 *
 */

#ifndef __WIFI_API_H__
#define __WIFI_API_H__

#include "stdint.h"
#include "stdbool.h"


#ifdef __cplusplus
extern "C" {
#endif

/**@defgroup WIFI_DEFINE Define
* @{
*/

/**@brief The maximum length of SSID.
*/
#define WIFI_MAX_LENGTH_OF_SSID             (32)

/**@brief MAC address length.
*/
#define WIFI_MAC_ADDRESS_LENGTH             (6)

/**
* @brief Length of 802.11 MAC header.
*/
#define WIFI_LENGTH_802_11                  (24)

/**@brief Timestamp length in a frame header.
*/
#define WIFI_TIMESTAMP_LENGTH               (8)

/**@brief Beacon interval length in a frame header.
*/
#define WIFI_BEACON_INTERVAL_LENGTH         (2)

/**@brief Length of capability information in a frame header.
*/
#define WIFI_CAPABILITY_INFO_LENGTH         (2)

/**@brief The Maximum number of stations that can
* connect to 7687 in SoftAP mode.
*/
#define WIFI_MAX_NUMBER_OF_STA  			(16)

/**@brief The maximum length of pass-phase used in WPA-PSK and WPA2-PSK encryption types.
*/
#define WIFI_LENGTH_PASSPHRASE  			(64)

/**@brief The maximum length of PMK used in WPA-PSK and WPA2-PSK encryption types.
*/
#define WIFI_LENGTH_PMK                     (32)

/**@brief The macro specifies the AP buffer in a profile.
*/
#define WIFI_PROFILE_BUFFER_AP              "AP"

/**@brief The macro specifies the STA buffer in a profile.
*/
#define WIFI_PROFILE_BUFFER_STA             "STA"

/**@brief The macro specifies the common buffer in a profile.
*/
#define WIFI_PROFILE_BUFFER_COMMON          "common"

/**@brief The macro specifies the maximum length of each entity stored
* in the NVRAM. Allocate a buffer of this length so that the NVRAM profile
* entity won't overflow.
*/
#define WIFI_PROFILE_BUFFER_LENGTH          (128)

/**@brief Specifies 2.4GHz band.
*/
#define WIFI_BAND_2_4_G                     (0)

/**@brief Specifies 5GHz band.
*/
#define WIFI_BAND_5_G                       (1)


/**@brief The event ID to indicate the link is disconnected.
*/
#define WIFI_STATUS_LINK_DISCONNECTED       (0)

/**@brief The event ID to indicate the link is connected.
*/
#define WIFI_STATUS_LINK_CONNECTED          (1)

/**@brief The RX filter indicates the packet to drop.
*/
#define WIFI_DEFAULT_IOT_RX_FILTER  (BIT(WIFI_RX_FILTER_DROP_RTS) | \
                                     BIT(WIFI_RX_FILTER_DROP_CTS) | \
                                     BIT(WIFI_RX_FILTER_DROP_CTRL_RSV) | \
                                     BIT(WIFI_RX_FILTER_DROP_PROBE_REQ) | \
                                     BIT(WIFI_RX_FILTER_DROP_VER_NOT_0) | \
                                     BIT(WIFI_RX_FILTER_DROP_STBC_BCN_BC_MC) |\
                                     BIT(WIFI_RX_FILTER_DROP_FCS_ERR) | \
                                     BIT(WIFI_RX_FILTER_RM_FRAME_REPORT_EN))

/**@brief Specifies 20MHz bandwidth in the 2.4GHz band.
*/
#define WIFI_IOT_COMMAND_CONFIG_BANDWIDTH_20MHZ       (0x00)

/**@brief Specifies 40MHz bandwidth in the 2.4GHz band.
*/
#define WIFI_IOT_COMMAND_CONFIG_BANDWIDTH_40MHZ       (0x01)

/**@brief Specifies 20MHz | 40MHz bandwidth in the 2.4GHz band.
*/
#define WIFI_IOT_COMMAND_CONFIG_BANDWIDTH_2040MHZ     (WIFI_IOT_COMMAND_CONFIG_BANDWIDTH_20MHZ|WIFI_IOT_COMMAND_CONFIG_BANDWIDTH_40MHZ)


/**
* @brief Station operation mode. Station mode represents MT7687 works as a Wi-Fi client.
*/
#define WIFI_MODE_STA_ONLY      (1)

/**
* @brief SoftAP operation mode. In Access Point (AP) mode, other client devices can connect to the WIFI access point.
*/
#define WIFI_MODE_AP_ONLY       (2)

/**
* @brief Station and AP concurrent mode. This mode isn't supported at the time of writing. Support plan is underway, please check back for updates.
*/
#define WIFI_MODE_DUAL          (3)

/**
* @brief This macro defines the monitoring mode. In this mode it can sniffer
* the WIFI packet in the air given the specific channel and bandwidth.
* It's used to enter a hybrid mode and handle a raw packet.
* Call #wifi_config_register_rx_handler() to register a raw packet handler
* once this operating mode is set.
*/
#define WIFI_MODE_MONITOR       (4)

/**
* @brief Support WiFi Direct Feature
*/
#define WIFI_MODE_P2P_ONLY          (5)
/**
* @brief Specifies the STA operation.
*/
#define WIFI_PORT_STA           (0)

/**
* @brief Specifies the AP client operation.
*/
#define WIFI_PORT_APCLI	        WIFI_PORT_STA

/**
* @brief Specifies the AP operation.
*/
#define WIFI_PORT_AP            (1)

#define WIFI_NUMBER_WEP_KEYS     (4)    /**<  The group number of WEP keys. */
#define WIFI_MAX_WEP_KEY_LENGTH  (26)   /**<  The maximum length of each WEP key. */

#define WIFI_INIT_TIME_OUT      1000    /**<  Initial Wi-Fi timeout 1000ms. */

/**
* @brief The length of device information used for WPS.
*/
#define WIFI_WPS_MAX_LENGTH_DEVICE_NAME     (32)
#define WIFI_WPS_MAX_LENGTH_MANUFACTURER    (64)
#define WIFI_WPS_MAX_LENGTH_MODEL_NAME      (32)
#define WIFI_WPS_MAX_LENGTH_MODEL_NUMBER    (32)
#define WIFI_WPS_MAX_LENGTH_SERIAL_NUMBER   (32)

/**
* @}
*/


/**@defgroup WIFI_ENUM Enumeration
* @{
*/
/**@brief This enumeration defines the supported events generated by the WIFI driver. The event will be sent to the upper layer handler registered in #wifi_connection_register_event_handler().
*/
typedef enum {
    WIFI_EVENT_IOT_CONNECTED = 0,               /**< Connected event. */
    WIFI_EVENT_IOT_SCAN_COMPLETE,               /**< Scan completed event.*/
    WIFI_EVENT_IOT_DISCONNECTED,                /**< Disconnected event.*/
    WIFI_EVENT_IOT_PORT_SECURE,                 /**< Secure event, mainly processed in supplicant. It can be used at the DHCP start.*/
    WIFI_EVENT_IOT_REPORT_BEACON_PROBE_RESPONSE,/**< Sends notification, if beacon or probe request is received.*/
    WIFI_EVENT_IOT_WPS_COMPLETE,                /**< Credential event, Sends notification when WPS process is done.*/
    WIFI_EVENT_MAX_NUMBER
} wifi_event_t;

/** @brief This enumeration defines the RX filter register’s bitmap. Each bit indicates a specific drop frame.
*/
typedef enum {
    WIFI_RX_FILTER_DROP_STBC_BCN_BC_MC,       /**< bit 0   Drops the STBC beacon/BC/MC frames. */
    WIFI_RX_FILTER_DROP_FCS_ERR,              /**< bit 1   Drops the FCS error frames. */
    WIFI_RX_FILTER_RESERVED,                  /**< bit 2   A reserved bit, not used. */
    WIFI_RX_FILTER_DROP_VER_NOT_0,            /**< bit 3   Drops the version field of Frame Control field. It cannot be 0. */
    WIFI_RX_FILTER_DROP_PROBE_REQ,            /**< bit 4   Drops the probe request frame. */
    WIFI_RX_FILTER_DROP_MC_FRAME,             /**< bit 5   Drops multicast frame. */
    WIFI_RX_FILTER_DROP_BC_FRAME,             /**< bit 6   Drops broadcast frame. */
    WIFI_RX_FILTER_RM_FRAME_REPORT_EN = 12,   /**< bit 12  Enables report frames. */
    WIFI_RX_FILTER_DROP_CTRL_RSV,             /**< bit 13  Drops reserved definition control frames. */
    WIFI_RX_FILTER_DROP_CTS,                  /**< bit 14  Drops CTS frames. */
    WIFI_RX_FILTER_DROP_RTS,                  /**< bit 15  Drops RTS frames. */
    WIFI_RX_FILTER_DROP_DUPLICATE,            /**< bit 16  Drops duplicate frames. */
    WIFI_RX_FILTER_DROP_NOT_MY_BSSID,         /**< bit 17  Drops not my BSSID frames. */
    WIFI_RX_FILTER_DROP_NOT_UC2ME,            /**< bit 18  Drops not unicast to me frames. */
    WIFI_RX_FILTER_DROP_DIFF_BSSID_BTIM,      /**< bit 19  Drops different BSSID TIM (Traffic Indication Map) Broadcast frame. */
    WIFI_RX_FILTER_DROP_NDPA                  /**< bit 20  Drops the NDPA or not. */
} wifi_rx_filter_t;


/** @brief This enumeration defines the command ID from Host to Wi-Fi firmware.
*/
typedef enum {
    WIFI_COMMAND_ID_IOT_OWN_MAC_ADDRESS = 0xd0,   /**< 0xd0 (Set / Query) */
    WIFI_COMMAND_ID_IOT_SSID,                     /**< 0xd1 (Set / Query) */
    WIFI_COMMAND_ID_IOT_BSSID,                    /**< 0xd2 (Set / Query) */
    WIFI_COMMAND_ID_IOT_BANDWIDTH,                /**< 0xd3 (Set / Query) */
    WIFI_COMMAND_ID_IOT_SET_DISCONNECT,           /**< 0xd4 (Set) */
    WIFI_COMMAND_ID_IOT_GET_LINK_STATUS,          /**< 0xd5 (Query) */
    WIFI_COMMAND_ID_IOT_GET_PROFILE,              /**< 0xd6 (Query) */
    WIFI_COMMAND_ID_IOT_START_SCAN,               /**< 0xd7 (Set) */
    WIFI_COMMAND_ID_IOT_STOP_SCAN,                /**< 0xd8 (Set) */
    WIFI_COMMAND_ID_IOT_GET_SCAN_LIST,            /**< 0xd9 (Query) */
    WIFI_COMMAND_ID_IOT_RX_FILTER,                /**< 0xda (Set) */
    WIFI_COMMAND_ID_IOT_CHANNEL,                  /**< 0xdb (Set / Query) */
    WIFI_COMMAND_ID_IOT_80211_TO_HOST,            /**< 0xdc (Set) */
    WIFI_COMMAND_ID_IOT_SWITCH_MODE,              /**< 0xdd (Set) */
    WIFI_COMMAND_ID_IOT_SET_SECURITY,			  /**< 0xde (Set), used in E1 EVB */
    WIFI_COMMAND_ID_IOT_SET_KEY = WIFI_COMMAND_ID_IOT_SET_SECURITY,	    /**< 0xde (Set), used in E2 EVB */
    WIFI_COMMAND_ID_IOT_EXTENSION = WIFI_COMMAND_ID_IOT_SET_SECURITY,	/**< 0xde (Set), used in E2 EVB */
} wifi_command_id_t;

/** @brief This enumeration defines the extension command ID from Host to Wi-Fi firmware.
*/
typedef enum {
    WIFI_COMMAND_ID_EXTENSION_DEBUG_LEVEL = 0x1,           /**< 0x1 (Set / Query) */
    WIFI_COMMAND_ID_EXTENSION_SET_AUTH_MODE ,              /**< 0x2 (Set)         */
    WIFI_COMMAND_ID_EXTENSION_SET_ENCRYPT_TYPE,            /**< 0x3 (Set)         */
    WIFI_COMMAND_ID_EXTENSION_SET_WEP_KEY,                 /**< 0x4 (Set)         */
    WIFI_COMMAND_ID_EXTENSION_WIRELESS_MODE,               /**< 0x5 (Set / Query) */
    WIFI_COMMAND_ID_EXTENSION_COUNTRY_REGION,              /**< 0x6 (Set / Query) */
    WIFI_COMMAND_ID_EXTENSION_RADIO_ON_OFF,                /**< 0x7 (Set / Query) */
    WIFI_COMMAND_ID_EXTENSION_DTIM_INTERVAL,               /**< 0x8 (Set / Query) */
    WIFI_COMMAND_ID_EXTENSION_LISTEN_INTERVAL,             /**< 0x9 (Set / Query) */
    WIFI_COMMAND_ID_EXTENSION_GET_STA_LIST,                /**< 0xA (Query)       */
    WIFI_COMMAND_ID_EXTENSION_SMART_CONNECTION_FILTER,     /**< 0xB (Set / Query) */
    WIFI_COMMAND_ID_EXTENSION_WOW_ENABLE,                  /**< 0x0C (Set/Query)  */
    WIFI_COMMAND_ID_EXTENSION_WOW_MAGIC_PACKET,            /**< 0x0D (Set/Query)  */
    WIFI_COMMAND_ID_EXTENSION_WOW_BITMAP_PATTERN,          /**< 0x0E (Set/Query)  */
    WIFI_COMMAND_ID_EXTENSION_WOW_ARP_OFFLOAD,             /**< 0x0F (Set/Query)  */
    WIFI_COMMAND_ID_EXTENSION_WOW_REKEY_OFFLOAD,           /**< 0x10 (Set/Query)  */
    WIFI_COMMAND_ID_EXTENSION_AP_STOP,                     /**< 0x11 (Set)   */
    WIFI_COMMAND_ID_EXTENSION_AP_START,                    /**< 0x12 (Set)   */
    WIFI_COMMAND_ID_EXTENSION_POWER_MANAGE_STATE,          /**< 0x13 (set)   */
    WIFI_COMMAND_ID_EXTENSION_GET_MAX_STA_NUMBER,          /**< 0x14 (Query) */
    WIFI_COMMAND_ID_EXTENSION_SET_EXTRA_IE,                /**< 0x15 (Set)   */
    WIFI_COMMAND_ID_EXTENSION_UPDATE_HOMEKIT_IE,           /**< 0x16 (Set)   */
    WIFI_COMMAND_ID_EXTENSION_ENABLE_AIRPLAY,              /**< 0x17 (Set)   */
    WIFI_COMMAND_ID_EXTENSION_GET_CONNECTED_AP_RSSI,       /**< 0x18 (Query) */
    WIFI_COMMAND_ID_EXTENSION_SET_PSMODE,                  /**< 0x19 (Set)   */
    WIFI_COMMAND_ID_EXTENSION_EFUSE,                       /**< 0x1A (Set/Query)  */
    WIFI_COMMAND_ID_EXTENSION_TX_RAW,                      /**< 0x1B (Send raw packet) */
    WIFI_COMMAND_ID_EXTENSION_P2P_LISTEN,                  /**< 0x1C (Set)  */
    WIFI_COMMAND_ID_EXTENSION_MBSSID,                      /**< 0x1d (mbssid placeholder) */
    WIFI_COMMAND_ID_EXTENSION_SET_TX_POWER,                /**< 0x1e (settxpower placeholder) */
    WIFI_COMMAND_ID_EXTENSION_SET_IE,                      /**< 0x1f (Set)   */
} wifi_extension_command_id_t;

/** @brief This enumeration defines the wireless authentication mode to indicate the Wi-Fi device’s authentication attribute.
*/
typedef enum {
    WIFI_AUTH_MODE_OPEN = 0,                        /**< Open mode     */
    WIFI_AUTH_MODE_SHARED,                          /**< Not supported */
    WIFI_AUTH_MODE_AUTO_WEP,                        /**< Not supported */
    WIFI_AUTH_MODE_WPA,                             /**< Not supported */
    WIFI_AUTH_MODE_WPA_PSK,                         /**< WPA_PSK       */
    WIFI_AUTH_MODE_WPA_None,                        /**< Not supported */
    WIFI_AUTH_MODE_WPA2,                            /**< Not supported */
    WIFI_AUTH_MODE_WPA2_PSK,                        /**< WPA2_PSK      */
    WIFI_AUTH_MODE_WPA_WPA2,                        /**< Not supported */
    WIFI_AUTH_MODE_WPA_PSK_WPA2_PSK,                /**< Mixture mode  */
} wifi_auth_mode_t;

/** @brief This enumeration defines the wireless encryption type to indicate the Wi-Fi device’s encryption attribute.
*/
typedef enum {
    WIFI_ENCRYPT_TYPE_WEP_ENABLED = 0,                                              /**< WEP encryption type  */
    WIFI_ENCRYPT_TYPE_ENCRYPT1_ENABLED = WIFI_ENCRYPT_TYPE_WEP_ENABLED,             /**< WEP encryption type  */
    WIFI_ENCRYPT_TYPE_WEP_DISABLED = 1,                                             /**< No encryption     */
    WIFI_ENCRYPT_TYPE_ENCRYPT_DISABLED = WIFI_ENCRYPT_TYPE_WEP_DISABLED,            /**< No encryption     */
    WIFI_ENCRYPT_TYPE_WEP_KEY_ABSENT = 2,                                           /**< Not supported     */
    WIFI_ENCRYPT_TYPE_ENCRYPT_KEY_ABSENT = WIFI_ENCRYPT_TYPE_WEP_KEY_ABSENT,        /**< Not supported     */
    WIFI_ENCRYPT_TYPE_WEP_NOT_SUPPORTED = 3,                                        /**< Not supported     */
    WIFI_ENCRYPT_TYPE_ENCRYPT_NOT_SUPPORTED = WIFI_ENCRYPT_TYPE_WEP_NOT_SUPPORTED,  /**< Not supported     */
    WIFI_ENCRYPT_TYPE_TKIP_ENABLED = 4,                                             /**< TKIP encryption   */
    WIFI_ENCRYPT_TYPE_ENCRYPT2_ENABLED = WIFI_ENCRYPT_TYPE_TKIP_ENABLED,            /**< TKIP encryption   */
    WIFI_ENCRYPT_TYPE_AES_ENABLED = 6,                                              /**< AES encryption    */
    WIFI_ENCRYPT_TYPE_ENCRYPT3_ENABLED = WIFI_ENCRYPT_TYPE_AES_ENABLED,             /**< Not supported     */
    WIFI_ENCRYPT_TYPE_AES_KEY_ABSENT = 7,                                           /**< Not supported     */
    WIFI_ENCRYPT_TYPE_TKIP_AES_MIX = 8,                                             /**< TKIP or AES mix   */
    WIFI_ENCRYPT_TYPE_ENCRYPT4_ENABLED = WIFI_ENCRYPT_TYPE_TKIP_AES_MIX,            /**< TKIP or AES mix   */
    WIFI_ENCRYPT_TYPE_TKIP_AES_KEY_ABSENT = 9,                                      /**< Not supported     */
    WIFI_ENCRYPT_TYPE_GROUP_WEP40_ENABLED = 10,                                     /**< Not supported     */
    WIFI_ENCRYPT_TYPE_GROUP_WEP104_ENABLED = 11,                                    /**< Not supported     */
#ifdef WAPI_SUPPORT
    WIFI_ENCRYPT_TYPE_ENCRYPT_SMS4_ENABLED,                                         /**< WPI SMS4 support  */
#endif /* WAPI_SUPPORT */
}wifi_encrypt_type_t;


/** @brief This enumeration defines the wireless physical mode.
*/
typedef enum {
    WIFI_PHY_11BG_MIXED = 0,     /**<  0, 2.4GHz band, supported */
    WIFI_PHY_11B,                /**<  1, 2.4GHz band, supported */
    WIFI_PHY_11A,                /**<  2, 5GHz band, supported*/
    WIFI_PHY_11ABG_MIXED,        /**<  3, both 2.4G and 5G band, supported */
    WIFI_PHY_11G,                /**<  4, 2.4GHz band, supported */
    WIFI_PHY_11ABGN_MIXED,       /**<  5, both 2.4G and 5G band, supported */
    WIFI_PHY_11N_2_4G,           /**<  6, 11n-only with 2.4GHz band, supported */
    WIFI_PHY_11GN_MIXED,         /**<  7, 2.4GHz band, supported */
    WIFI_PHY_11AN_MIXED,         /**<  8, 5GHz band, supported */
    WIFI_PHY_11BGN_MIXED,        /**<  9, 2.4GHz band, supported */
    WIFI_PHY_11AGN_MIXED,        /**< 10, both 2.4G and 5G band, supported */
    WIFI_PHY_11N_5G,             /**< 11, 11n-only with 5GHz band, supported*/
} wifi_phy_mode_t;

/** @brief This enumeration defines wireless security cipher suits.
*/
typedef enum {
	WIFI_CIPHER_NONE        = 0,    /**< None cipher   */
	WIFI_CIPHER_WEP64       = 1,    /**< WEP64 cipher  */
	WIFI_CIPHER_WEP128      = 2,    /**< WEP128 cipher */
	WIFI_CIPHER_TKIP        = 3,    /**< TKIP cipher   */
	WIFI_CIPHER_AES         = 4,    /**< AES cipher    */
	WIFI_CIPHER_CKIP64      = 5,    /**< CKIP64 cipher */
	WIFI_CIPHER_CKIP128     = 6,    /**< CKIP128 cipher*/
	WIFI_CIPHER_CKIP152     = 7,    /**< CKIP152 cipher*/
	WIFI_CIPHER_SMS4        = 8,    /**< SMS4 cipher   */
	WIFI_CIPHER_WEP152      = 9,    /**< WEP152 cipher */
	WIFI_CIPHER_BIP         = 10,   /**< BIP cipher    */
	WIFI_CIPHER_WAPI        = 11,   /**< WAPI cipher   */
	WIFI_CIPHER_TKIP_NO_MIC = 12,   /**< TKIP_NO_MIC cipher */
} wifi_security_cipher_suits_t;


/**
* @}
*/

/**@defgroup WIFI_TYPEDEF Typedef
* @{
*/
/**
* @brief This defines the Wi-Fi event handler. Call #wifi_connection_register_event_handler() to register a handler, when the WIFI driver generates an event and sends it to the handler.
* @param[in] event  is an optional event to register.
*
* Value                         |Definition                                                              |
* ------------------------------|------------------------------------------------------------------------|
* \b 0                          | #WIFI_EVENT_IOT_CONNECTED|
* \b 1                          | #WIFI_EVENT_IOT_SCAN_COMPLETE|
* \b 2                          | #WIFI_EVENT_IOT_DISCONNECTED|
* \b 3                          | #WIFI_EVENT_IOT_PORT_SECURE|
* \b 4                          | #WIFI_EVENT_IOT_REPORT_BEACON_PROBE_RESPONSE|
* \b 5                          | #WIFI_EVENT_IOT_WPS_COMPLETE|
*
*
* @param[in] payload  is the payload for the event.
*                     When the event is WIFI_EVENT_IOT_CONNECTED in AP mode, payload is the connected STA's MAC address.
*                     When the event is WIFI_EVENT_IOT_CONNECTED in STA mode, payload is the connected AP's BSSID.
* @param[in] length is the length of a packet.
*
* @return The return value is reserved and it is ignored.
*/
typedef int32_t (* wifi_event_handler_t)(wifi_event_t event, uint8_t *payload, uint32_t length);


/**
* @brief This is only for compatibility purpose, so that applications implemented with the former API can work with the updated API.
*/
typedef wifi_event_handler_t wifi_event_handler;


/**
* @brief This defines the 802.11 RX raw packet handler. Call #wifi_config_register_rx_handler() to register a handler, then the network processor will deliver the packets to the handler function instead of sending them to the IP stack.
* @param[in] payload  is the packet payload.
* @param[in] length is the packet length.
*
* @return  1: handled, and the packet won't be processed by other tasks 0: not handled, it will be processed by the other tasks.
*/
typedef int32_t (* wifi_rx_handler_t)(uint8_t *payload, uint32_t length);

/**
* @}
*/


/**@defgroup WIFI_STRUCT Structure
* @{
*/

/** @brief Wi-Fi WEP keys.
*/
typedef struct {
	/**
	 * @brief wep_key - there are four WEP keys.
	 */
	uint8_t wep_key[WIFI_NUMBER_WEP_KEYS][WIFI_MAX_WEP_KEY_LENGTH];

	/**
	 *@brief wep_key_length - WEP key lengths.
	 */
	uint8_t wep_key_length[WIFI_NUMBER_WEP_KEYS];

	/**
     * @brief wep_tx_key_index - Default key index for TX frames using WEP.
	 */
	uint8_t wep_tx_key_index;
} wifi_wep_key_t;


/** @brief Wi-Fi profile entity.
*/
typedef struct {
    uint8_t ssid[WIFI_MAX_LENGTH_OF_SSID];          /**< Stores the predefined SSID.  */
    uint8_t ssid_length;                            /**< The length of SSID.         */
    uint8_t mac_address[WIFI_MAC_ADDRESS_LENGTH];   /**< MAC address of the STA.     */
    uint8_t wireless_mode;                          /**< Please refer to the definition of #wifi_phy_mode_t.    */
    uint8_t channel;                                /**< The channel used.                    */
    uint8_t bandwidth;                              /**< The bandwidth is 20MHz or 40MHz.     */
    uint8_t mcs;                                    /**< Defines the packet data rate.        */
    uint8_t auth_mode;                              /**< Please refer to the definition of #wifi_auth_mode_t.   */
    uint8_t encrypt_mode;                           /**< Please refer to the definition of #wifi_encrypt_type_t.*/
} wifi_profile_t;


/** @brief This defines the scanned AP’s information.
*/
typedef struct {
    uint8_t  is_valid;                         /**< Indicates whether the scanned item is valid or not. */
    int8_t   rssi;                             /**< Records the RSSI value when probe response is received. */
    uint8_t  ssid[WIFI_MAX_LENGTH_OF_SSID];    /**< Stores the predefined SSID. */
    uint8_t  ssid_length;                      /**< The length of SSID. */
    uint8_t  bssid[WIFI_MAC_ADDRESS_LENGTH];   /**< AP's MAC address. */
    uint8_t  channel;                          /**< The channel used. */
    uint8_t  central_channel;                  /**< The center channel in 40MHz bandwidth. */
    bool     is_wps_supported;                 /**< Indicates whether WPS is supported or not. 1: WPS is supported, 0: WPS is not supported. */
    wifi_auth_mode_t     auth_mode;            /**< Please refer to the definition of #wifi_auth_mode_t. */
    wifi_encrypt_type_t  encrypt_type;         /**< Please refer to the definition of #wifi_encrypt_type_t. */
    bool     is_hidden;                        /**< Indicates the SSID is hidden or not. 1: hidden SSID, 0: not hidden SSID. */
    uint8_t  bss_type;                         /**< Indicates the type of BSS. 0: IBSS 1: Infrastructure. */
    uint16_t beacon_interval;                  /**< Indicates the beacon interval. */
    uint16_t capability_info;                  /**< The Capability Information field contains a number of subfields that are used to indicate requested or advertised optional capabilities. */
} wifi_scan_list_item_t;

/** @brief This defines a link to the scanned AP list.
*/
typedef struct {
    wifi_scan_list_item_t ap_data;  /**< The data of an AP in the scanned result, stored in a linked list. Please refer to the definition of #wifi_scan_list_item_t.*/
    struct _wifi_scan_list_t *next; /**< Next item in the list.*/
} wifi_scan_list_t;

/** @brief The RSSI sample is a measurement of the power present in a received radio signal.
*/
typedef struct {
    int8_t          last_rssi;             /**< The latest received RSSI.     */
    uint8_t         reserved;              /**< Reserved.               */
    int16_t         average_rssi;          /**< 8 times of the average RSSI.*/
} wifi_rssi_sample_t;


/** @brief Specifies the Wi-Fi transmit settings, including MCS, LDPC, bandwidth, short-GI algorithms, STBC and others.
*/
typedef union {
                struct {
                        uint16_t mcs:6;                      /**< Implies the data rate. */
                        uint16_t ldpc:1;                     /**< Checks if a low-density parity-check code is adopted. */
                        uint16_t bandwidth:2;                /**< Decides the bandwidth. */
                        uint16_t short_gi:1;                 /**< Checks if short-GI algorithms are applied. */
                        uint16_t stbc:1;                     /**< Checks if a space-time code is adopted.    */
                        uint16_t external_tx_beam_forming:1; /**< Checks if an external buffer is adopted.   */
                        uint16_t internal_tx_beam_forming:1; /**< Checks if an internal buffer is adopted.   */
                        uint16_t mode:3;
                } field;
                uint16_t word;
} wifi_transmit_setting_t;

/** @brief Specifies the Wi-Fi station items, including the Wi-Fi transmit settings, the RSSI sample, MAC address, power save mode, bandwidth and keep alive status.
*/
typedef struct {
    wifi_transmit_setting_t last_tx_rate;            /**< The latest TX rate.  */
    uint16_t reserved_one;                           /**< For padding.   */
    wifi_transmit_setting_t last_rx_rate;            /**< The latest RX rate.  */
    uint16_t reserved_two;                           /**< For padding.   */
    wifi_rssi_sample_t rssi_sample;	                 /**< The RSSI sample.   */
    uint8_t mac_address[WIFI_MAC_ADDRESS_LENGTH];    /**< Station MAC address.     */
    uint8_t power_save_mode;                         /**< Station power save mode. */
    uint8_t bandwidth;                               /**< Negotiation bandwidth.   */
    uint8_t keep_alive;                              /**< Keep alive status.       */
    uint8_t reserved[3];                             /**< For padding.             */
} wifi_sta_list_t;

/** @brief Indicates the detailed cipher information.
*/
typedef struct {
    uint8_t   key[16];            /**< Four keys are implemented, with a maximum length of 128bits.*/
    uint8_t   rx_mic[8];          /**< Make an alignment.  */
    uint8_t   tx_mic[8];
    uint8_t   tx_tsc[6];          /**< 48bit TSC value. */
    uint8_t   rx_tsc[6];          /**< 48bit TSC value. */
    uint8_t   cipher_type;        /**< 0:none, 1:WEP64, 2:WEP128, 3:TKIP, 4:AES, 5:CKIP64, 6:CKIP128.*/
    uint8_t   key_length;         /**< Key length for each key, 0: entry is invalid.*/
    uint8_t   bssid[6];           /**< AP's MAC address. */
    uint8_t   type;               /**< Indicates a pairwise/Group when reporting an MIC error.*/
} wifi_cipher_key_t;

#ifdef MTK_WIFI_WPS_ENABLE
/**
* @brief Represents the device information used for WPS.
*/
typedef struct {
    char device_name[WIFI_WPS_MAX_LENGTH_DEVICE_NAME];          /**< Device name, up to 32 octets encoded in UTF-8. */
    char manufacturer[WIFI_WPS_MAX_LENGTH_MANUFACTURER];        /**< Device manufacturer, up to 64 ASCII characters . */
    char model_name[WIFI_WPS_MAX_LENGTH_MODEL_NAME];            /**< Model name, up to 32 ASCII characters. */
    char model_number[WIFI_WPS_MAX_LENGTH_MODEL_NUMBER];        /**< Model number, up to 32 ASCII characters. */
    char serial_number[WIFI_WPS_MAX_LENGTH_SERIAL_NUMBER];      /**< Device serial number, up to 32 characters. */
} wifi_wps_device_info_t;

/**
* @brief Represents the credentials used for WPS.
*/
typedef struct {
    uint8_t  ssid[WIFI_MAX_LENGTH_OF_SSID];   /**< Stores Registrar network SSID. */
    uint32_t ssid_len;                        /**< The length of Registrar network SSID. */
    wifi_auth_mode_t     auth_mode;           /**< Please refer to the definition of #wifi_auth_mode_t. */
    wifi_encrypt_type_t  encrypt_type;        /**< Please refer to the definition of #wifi_encrypt_type_t. */
    uint8_t  key_index;                       /**< The WEP key inndex.*/
    uint8_t  key[WIFI_LENGTH_PASSPHRASE];     /**< The key. */
    uint32_t key_length;                      /**< The length of the key.*/
} wifi_wps_credential_info_t;

#endif //end of MTK_WIFI_WPS_ENABLE

/**
*@}
*/


/**
* @brief This function receives the wireless operation mode of the WIFI driver.
*
* @param[out]  mode indicates the operation mode.
*
* Value                         |Definition                                                              |
* ------------------------------|------------------------------------------------------------------------|
* \b 0x01                       | #WIFI_MODE_STA_ONLY|
* \b 0x02                       | #WIFI_MODE_AP_ONLY|
* \b 0x03                       | #WIFI_MODE_DUAL|
* \b 0x04                       | #WIFI_MODE_MONITOR|
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*/
int32_t wifi_config_get_opmode(uint8_t *mode);

/**
* @brief This function sets the WIFI operation mode and it takes effect immediately.
*
* @param[in] mode indicates operation mode that can be set.
*
* Value                         |Definition                                                              |
* ------------------------------|------------------------------------------------------------------------|
* \b 0x01                       | #WIFI_MODE_STA_ONLY|
* \b 0x02                       | #WIFI_MODE_AP_ONLY|
* \b 0x03                       | #WIFI_MODE_DUAL|
* \b 0x04                       | #WIFI_MODE_MONITOR|
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*
* @note Set WIFI operate mode will RESET all the configuration in the WIFI driver (including supplicant and firmware) set by previous WIFI Configure APIs.
*/
int32_t wifi_config_set_opmode(uint8_t mode);

/**
* @brief This function gets the MAC address of a specific wireless port used by the WIFI driver.
*
* @param[in] port indicates the WIFI port that the function will operate on.
*
* Value                         |Definition                                                              |
* ------------------------------|------------------------------------------------------------------------|
* \b #WIFI_PORT_STA             | STA|
* \b #WIFI_PORT_APCLI           | AP Client|
* \b #WIFI_PORT_AP              | AP|
*
* @param[out]  address is the MAC address (6 Bytes).
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*/
int32_t wifi_config_get_mac_address(uint8_t port, uint8_t *address);

#if 0
/**
* @brief This function sets the MAC address of a specific wireless port used by the WIFI driver.
*
* @param[in] port indicates the WIFI port that the function will operate on.
*
* Value                         |Definition                                                              |
* ------------------------------|------------------------------------------------------------------------|
* \b 0                          | STA / AP Client|
* \b 1                          | AP |
*
* @param[in] address is MAC address (6 Bytes)
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*/
int32_t wifi_config_set_mac_address(uint8_t port, uint8_t *address);
#endif

/**
* @brief This function gets the SSID and SSID length of a specific wireless port used by the WIFI driver.
*
* @param[in] port indicates the WIFI port that the function will operate on.
*
* Value                         |Definition                                                              |
* ------------------------------|------------------------------------------------------------------------|
* \b #WIFI_PORT_STA             | STA|
* \b #WIFI_PORT_APCLI           | AP Client|
* \b #WIFI_PORT_AP              | AP|
*
* @param[out]  ssid is the SSID content. In STA mode, SSID is the target AP's SSID;\n
*                       In SoftAP mode, the SSID indicates the device's own SSID.
* @param[out]  ssid_length is the length of SSID
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*/
int32_t wifi_config_get_ssid(uint8_t port, uint8_t *ssid, uint8_t *ssid_length);

/**
* @brief This function sets the SSID and SSID length that WIFI driver uses for a specific wireless port.
* This operation only takes effect after #wifi_config_reload_setting() is called.
*
* @param[in] port indicates the WIFI port that the function will operate on.
*
* Value                         |Definition                                                              |
* ------------------------------|------------------------------------------------------------------------|
* \b #WIFI_PORT_STA             | STA|
* \b #WIFI_PORT_APCLI           | AP Client|
* \b #WIFI_PORT_AP              | AP|
*
* @param[in] ssid is the SSID content. If #WIFI_PORT_STA or #WIFI_PORT_APCLI, the SSID indicates the target AP's SSID.
*                       If WIFI_PORT_AP, the SSID indicates the device's own SSID.
* @param[in] ssid_length is the length of SSID, the maximum is 32 Bytes.
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*/
int32_t wifi_config_set_ssid(uint8_t port, uint8_t *ssid, uint8_t ssid_length);

/**
* @brief This function sets the bandwidth configuration that the WIFI driver uses for a specific wireless port.
* This operation takes effect immediately.
*
* @param[in] port indicates the WIFI port that the function will operate on.
*
* Value                         |Definition                                                              |
* ------------------------------|------------------------------------------------------------------------|
* \b #WIFI_PORT_STA             | STA|
* \b #WIFI_PORT_APCLI           | AP Client|
* \b #WIFI_PORT_AP              | AP|
*
* @param[in]  bandwidth is the wireless bandwidth.
*
* Value                                                |Definition                                                                 |
* -----------------------------------------------------|-------------------------------------------------|
* \b #WIFI_IOT_COMMAND_CONFIG_BANDWIDTH_20MHZ          | 20MHz |
* \b #WIFI_IOT_COMMAND_CONFIG_BANDWIDTH_40MHZ          | 40MHz |
* \b #WIFI_IOT_COMMAND_CONFIG_BANDWIDTH_2040MHZ        | 20 or 40MHz |
*
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*
* @note    The default value is #WIFI_IOT_COMMAND_CONFIG_BANDWIDTH_20MHZ.
*/
int32_t wifi_config_set_bandwidth(uint8_t port, uint8_t bandwidth);

/**
* @brief   This function gets the bandwidth configuration that the WIFI driver uses for a specific wireless port.
*
* @param[in] port indicates the WIFI port that the function will operate on.
*
* Value                         |Definition                                                              |
* ------------------------------|------------------------------------------------------------------------|
* \b #WIFI_PORT_STA             | STA|
* \b #WIFI_PORT_APCLI           | AP Client|
* \b #WIFI_PORT_AP              | AP|
*
* @param[out]   bandwidth is the wireless bandwidth.
*
* Value                                                  |Definition                                     |
* -------------------------------------------------------|-----------------------------------------------|
* \b #WIFI_IOT_COMMAND_CONFIG_BANDWIDTH_20MHZ            | 20MHz |
* \b #WIFI_IOT_COMMAND_CONFIG_BANDWIDTH_40MHZ            | 40MHz |
* \b #WIFI_IOT_COMMAND_CONFIG_BANDWIDTH_2040MHZ          | 20 or 40MHz |
*
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*
* @note    The default value is #WIFI_IOT_COMMAND_CONFIG_BANDWIDTH_20MHZ.
*/
int32_t wifi_config_get_bandwidth(uint8_t port, uint8_t *bandwidth);

/**
* @brief This function sets the channel number that the WIFI driver uses for a specific wireless port.
* The STA remains idle on a specified channel. Call #wifi_config_set_channel().
* in a station mode while the device is disconnected from the AP, then the device will scan and change the channel in a loop.
* This operation takes effect immediately in station mode, in AP mode, it'll take effect after calling #wifi_config_reload_setting().
* @param[in] port indicates the WIFI port that the function will operate on.
*
* Value                         |Definition                                                              |
* ------------------------------|------------------------------------------------------------------------|
* \b #WIFI_PORT_STA             | STA|
* \b #WIFI_PORT_APCLI           | AP Client|
* \b #WIFI_PORT_AP              | AP|
*
* @param[in] channel    is the channel number that the WIFI driver uses for a specific wireless port.
*                       The channel number range is 1~14 for 2.4GHz. The specific channel number is determined
*                       by country region settings in the profile.
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*/
int32_t wifi_config_set_channel(uint8_t port, uint8_t channel);

/**
* @brief This function gets the channel number that the WIFI driver uses for a specific wireless port.
*
* @param[in] port indicates the WIFI port that the function will operate on.
*
* Value                         |Definition                                                              |
* ------------------------------|------------------------------------------------------------------------|
* \b #WIFI_PORT_STA             | STA|
* \b #WIFI_PORT_APCLI           | AP Client|
* \b #WIFI_PORT_AP              | AP|
*
* @param[out]  channel    is the channel number that the WIFI driver uses for a specific wireless port.
*                         The channel number range is 1~14 for 2.4GHz. The specific channel number is determined
*                         by country region settings in the profile.
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*/
int32_t wifi_config_get_channel(uint8_t port, uint8_t *channel);


/**
* @brief This function gets the wireless mode that the WIFI driver uses for a specific wireless port.
*
* @param[in] port indicates the WIFI port that the function will operate on.
*
* Value                         |Definition                                                              |
* ------------------------------|------------------------------------------------------------------------|
* \b #WIFI_PORT_STA             | STA|
* \b #WIFI_PORT_APCLI           | AP Client|
* \b #WIFI_PORT_AP              | AP|
*
* @param[out]  mode  is the wireless mode. For more information, please refer to #wifi_phy_mode_t.
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*/
int32_t wifi_config_get_wireless_mode(uint8_t port, wifi_phy_mode_t *mode);


/**
* @brief This function gets the wireless mode that the WIFI driver uses for a specific wireless port.
* This operation takes effect immediately.
*
* @param[in] port indicates the WIFI port that the function will operate on.
*
* Value                         |Definition                                                              |
* ------------------------------|------------------------------------------------------------------------|
* \b #WIFI_PORT_STA             | STA|
* \b #WIFI_PORT_APCLI           | AP Client|
* \b #WIFI_PORT_AP              | AP|
*
* @param[in] mode  is the wireless mode. For more information, please refer to #wifi_phy_mode_t.
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*/
int32_t wifi_config_set_wireless_mode(uint8_t port, wifi_phy_mode_t mode);


/**
* @brief This function gets the country region that the WIFI driver uses for a specific wireless port.
* Various world regions have allocated different amounts of frequency space
* around 2.4GHz for Wi-Fi communication and some of them have fewer or more channels
* available than others. The region setting ensures that your router enables
* using the WIFI channels valid only in user's location.
*
* @param[in] band indicates the WIFI bandwidth that the function will operate on.
*
* Value                         |Definition                                                              |
* ------------------------------|------------------------------------------------------------------------|
* \b #WIFI_BAND_2_4_G           | 2.4GHz|
* \b #WIFI_BAND_5_G             | 5GHz|
*
* @param[out]  region  indicates different channels in 2.4GHz and 5GHz.
* @param  region: (2.4GHz) the channel list for different regions in 2.4GHz.
*
* Value                         |Definition                                                              |
* ------------------------------|------------------------------------------------------------------------|
* \b 0                          | CH1-11 active scan|
* \b 1                          | CH1-13 active scan|
* \b 2                          | CH10-11 active scan|
* \b 3                          | CH10-13 active scan|
* \b 4                          | CH14 active scan|
* \b 5                          | CH1-14 all active scan|
* \b 6                          | CH3-9 active scan|
* \b 7                          | CH5-13 active scan|
* \b 31                         | CH1-11 active scan, CH12-14 passive scan|
* \b 32                         | CH1-11 active scan, CH12-13 passive scan|
* \b 33                         | CH1-14 all active scan|
* @param  region: (5GHz)  the channel list for different regions in 5GHz.
*
* Value                         |Definition                                                              |
* ------------------------------|------------------------------------------------------------------------|
* \b 0                          | CH36-64 active scan, CH149-165 active scan|
* \b 1                          | CH36-64 active scan, CH100-140 active scan|
* \b 2                          | CH36-64 active scan|
* \b 3                          | CH52-64 active scan, CH149-161 active scan|
* \b 4                          | CH149-165 active scan|
* \b 5                          | CH149-161 active scan|
* \b 6                          | CH36-48 active scan|
* \b 7                          | CH36-64 active scan, CH100-140 active scan, CH149-165 active scan|
* \b 8                          | CH52-64 active scan|
* \b 9                          | CH36-64 active scan, CH100-116 active scan, CH132-140 active scan, CH149-165 active scan|
* \b 10                         | CH36-48 active scan, CH149-165 active scan|
* \b 11                         | CH36-64 active scan, CH100-120 active scan, CH149-161 active scan|
* \b 12                         | CH36-64 active scan, CH100-140 active scan|
* \b 13                         | CH52-64 active scan, CH100-140 active scan, CH149-161 active scan|
* \b 14                         | CH36-64 active scan, CH100-116 active scan, CH136-140 active scan, CH149-165 active scan|
* \b 15                         | CH149-173 active scan|
* \b 16                         | CH52-64 active scan, CH149-165 active scan|
* \b 17                         | CH36-48 active scan, CH149-161 active scan|
* \b 18                         | CH36-64 active scan, CH100-116 active scan, CH132-140 active scan|
* \b 19                         | CH56-64 active scan, CH100-140 active scan, CH149-161 active scan|
* \b 20                         | CH36-64 active scan, CH100-124 active scan, CH149-161 active scan|
* \b 21                         | CH36-64 active scan, CH100-140 active scan, CH149-161 active scan|
* \b 22                         | CH36-64 active scan|
* \b 30                         | CH36-48 active scan, CH52-64 passive scan, CH100-140 passive scan, CH149-165 active scan|
* \b 31                         | CH52-64 passive scan, CH100-140 passive scan, CH149-165 active scan|
* \b 32                         | CH36-48 active scan, CH52-64 passive scan, CH100-140 passive scan, CH149-161 active scan|
* \b 33                         | CH36-48 active scan, CH52-64 passive scan, CH100-140 passive scan|
* \b 34                         | CH36-48 active scan, CH52-64 passive scan, CH149-165 active scan|
* \b 35                         | CH36-48 active scan, CH52-64 passive scan|
* \b 36                         | CH36-48 active scan, CH100-140 passive scan, CH149-165 active scan|
* \b 37                         | CH36-48 active scan, CH52-64 passive scan, CH149-165 active scan, CH173 active scan|
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*/
int32_t wifi_config_get_country_region(uint8_t band, uint8_t  *region);

/**
* @brief This function sets the country region that the WIFI driver uses for a specific wireless port.
* Various world regions have allocated different amounts of frequency space
* around 2.4GHz for Wi-Fi and some of them have fewer or more channels
* available than others. The region setting ensures that the router enables
* using the Wi-Fi channels valid only in user's location.
*
* @param[in] band  indicates the Wi-Fi bandwidth to operate on.
*
* Value                         |Definition                                                              |
* ------------------------------|------------------------------------------------------------------------|
* \b #WIFI_BAND_2_4_G           | 2.4GHz|
* \b #WIFI_BAND_5_G             | 5GHz|
*
* @param[in] region  indicates different channels in 2.4GHz and 5GHz.
* @param  region: (2.4GHz)  the channel list for different regions in 2.4GHz.
*
* Value                         |Definition                                                              |
* ------------------------------|------------------------------------------------------------------------|
* \b 0                          | CH1-11 active scan|
* \b 1                          | CH1-13 active scan|
* \b 2                          | CH10-11 active scan|
* \b 3                          | CH10-13 active scan|
* \b 4                          | CH14 active scan|
* \b 5                          | CH1-14 all active scan|
* \b 6                          | CH3-9 active scan|
* \b 7                          | CH5-13 active scan|
* \b 31                         | CH1-11 active scan, CH12-14 passive scan|
* \b 32                         | CH1-11 active scan, CH12-13 passive scan|
* \b 33                         | CH1-14 all active scan|
* @param  region: (5GHz)  the channel list for different regions in 5GHz.
*
* Value                         |Definition                                                              |
* ------------------------------|------------------------------------------------------------------------|
* \b 0                          | CH36-64 active scan, CH149-165 active scan|
* \b 1                          | CH36-64 active scan, CH100-140 active scan|
* \b 2                          | CH36-64 active scan|
* \b 3                          | CH52-64 active scan, CH149-161 active scan|
* \b 4                          | CH149-165 active scan|
* \b 5                          | CH149-161 active scan|
* \b 6                          | CH36-48 active scan|
* \b 7                          | CH36-64 active scan, CH100-140 active scan, CH149-165 active scan|
* \b 8                          | CH52-64 active scan|
* \b 9                          | CH36-64 active scan, CH100-116 active scan, CH132-140 active scan, CH149-165 active scan|
* \b 10                         | CH36-48 active scan, CH149-165 active scan|
* \b 11                         | CH36-64 active scan, CH100-120 active scan, CH149-161 active scan|
* \b 12                         | CH36-64 active scan, CH100-140 active scan|
* \b 13                         | CH52-64 active scan, CH100-140 active scan, CH149-161 active scan|
* \b 14                         | CH36-64 active scan, CH100-116 active scan, CH136-140 active scan, CH149-165 active scan|
* \b 15                         | CH149-173 active scan|
* \b 16                         | CH52-64 active scan, CH149-165 active scan|
* \b 17                         | CH36-48 active scan, CH149-161 active scan|
* \b 18                         | CH36-64 active scan, CH100-116 active scan, CH132-140 active scan|
* \b 19                         | CH56-64 active scan, CH100-140 active scan, CH149-161 active scan|
* \b 20                         | CH36-64 active scan, CH100-124 active scan, CH149-161 active scan|
* \b 21                         | CH36-64 active scan, CH100-140 active scan, CH149-161 active scan|
* \b 22                         | CH36-64 active scan|
* \b 30                         | CH36-48 active scan, CH52-64 passive scan, CH100-140 passive scan, CH149-165 active scan|
* \b 31                         | CH52-64 passive scan, CH100-140 passive scan, CH149-165 active scan|
* \b 32                         | CH36-48 active scan, CH52-64 passive scan, CH100-140 passive scan, CH149-161 active scan|
* \b 33                         | CH36-48 active scan, CH52-64 passive scan, CH100-140 passive scan|
* \b 34                         | CH36-48 active scan, CH52-64 passive scan, CH149-165 active scan|
* \b 35                         | CH36-48 active scan, CH52-64 passive scan|
* \b 36                         | CH36-48 active scan, CH100-140 passive scan, CH149-165 active scan|
* \b 37                         | CH36-48 active scan, CH52-64 passive scan, CH149-165 active scan, CH173 active scan|
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*
*/
int32_t wifi_config_set_country_region(uint8_t band, uint8_t region);

/**
* @brief This function gets the DTIM interval used in the WIFI driver in SoftAP mode.
* Depending on the value set in the SoftAP mode, the AP will buffer
* broadcast and multicast data and let clients know when to wake up to
* receive those data.
*
* @param[out]  interval 1 ~ 255 beacons interval. According to the 802.11
* standards, a Delivery Traffic Indication Map (DTIM) period value is a number
* that determines how often a beacon frame includes a Delivery Traffic
* Indication Message, and this number is included in each beacon frame. A DTIM
* is included in beacon frames, according to the DTIM period, to notify the
* client devices whether the access point has buffered broadcast and/or
* multicast data are waiting for them. Following a beacon frame that includes a DTIM,
* the access point will release any existing buffered broadcast and/or multicast data.
* \n
* Since beacon frames are sent using the mandatory 802.11 carrier sense multiple
* access/collision avoidance (CSMA/CA) algorithm, the access point must wait
* if a client device is sending a frame when the beacon frame is to be sent. As a
* result, the actual time between beacons may be longer than the beacon interval.
* Client devices that awaken from power-save mode may find that they have to wait
* longer than expected to receive the next beacon frame. Client devices, however,
* compensate for this inaccuracy by utilizing the timestamp found within the
* beacon frame.
* \n
* The 802.11 standards define a power-save mode for client devices. In
* power-save mode, a client device may choose to sleep for one or more beacon
* intervals waking for beacon frames that include DTIMs. When the DTIM period
* is 2, a client device in power-save mode will awaken to receive every other
* beacon frame. Upon entering power-save mode, a client device will transmit a
* notification to the access point, so that the access point will know how to
* handle unicast traffic destined for the client device. The client device will
* begin to sleep according to the DTIM period.
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*
*/
int32_t wifi_config_get_dtim_interval(uint8_t *interval);

/**
* @brief This function sets the DTIM interval used in the WIFI driver in SoftAP mode.
* Depending on the value set in the SoftAP mode, the AP will buffer
* broadcast and multicast data and let clients know when to wake up to
* receive those data.
* This operation takes effect immediately.
*
* @param[out]  interval is the number in a range of 1 ~ 255 beacon intervals. According to the 802.11
* standards, a Delivery Traffic Indication Map (DTIM) period value is a number
* that determines how often a beacon frame includes a Delivery Traffic
* Indication Message, and this number is included in each beacon frame. A DTIM
* is included in beacon frames, according to the DTIM period, to indicate to the
* client devices whether the access point has buffered broadcast and/or
* multicast data waiting for them. Following a beacon frame that includes a DTIM,
* the access point will release any existing buffered broadcast and/or multicast data.
* \n
* Since beacon frames are sent using the mandatory 802.11 carrier sense multiple
* access/collision avoidance (CSMA/CA) algorithm, the access point must wait
* if a client device is sending a frame when the beacon is to be sent. As a
* result, the actual time between beacons may be longer than the beacon interval.
* Client devices that awaken from power-save mode may find that they have to wait
* longer than expected to receive the next beacon frame. Client devices, however,
* compensate for this inaccuracy by utilizing the timestamp found within the
* beacon frame.
* \n
* The 802.11 standards define a power-save mode for client devices. In
* power-save mode, a client device may choose to sleep for one or more beacon
* intervals waking for beacon frames that include DTIMs. When the DTIM period
* is 2, a client device in power-save mode will awaken to receive every other
* beacon frame. Upon entering power-save mode, a client device will transmit a
* notification to the access point, so that the access point will know how to
* handle unicast traffic destined for the client device. The client device will
* begin to sleep according to the DTIM period.
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*/
int32_t wifi_config_set_dtim_interval(uint8_t interval);

/**
* @brief This function gets the beacon listen interval used in the WIFI driver in a station mode.
* Depending on the timing set in the station, the station in power saving mode
* resumes to listen to the beacon and receives
* buffered packets from AP if the TIM element in beacon frame indicates AP has stored packets for specific station.
*
* @param[out]  interval is the beacon's interval in a range from 1 to 255. The beacon's interval is usually 100 times the unit (100*1.024 ms), which means, the listen interval range is around (1~255) * 102.4ms.
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*
*/
int32_t wifi_config_get_listen_interval(uint8_t *interval);

/**
* @brief This function sets the beacon listen interval used in the WIFI driver in a station mode.
* Depending on the timing set in the Station, the station in power saving mode
* resumes to listen to the beacon and receives
* buffered packets from AP if the TIM element in beacon frame indicates AP has stored packets for specific station.
* This operation takes effect immediately. This is not supported yet. It should be supported in SDK v1.0.0.
*
* @param[in] interval is the beacon's interval in a range from 1 to 255. The beacon's interval is usually 100 times the unit (100*1.024 ms), which means, the listen interval range is around (1~255) * 102.4ms.
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*/
int32_t wifi_config_set_listen_interval(uint8_t interval);

#if 0
/**
* @brief This function gets the Wi-Fi Power Save mode, only for the STA mode.
*
* @param[out]  power_save_mode
* @param 1 CAM: CAM (Constantly Awake Mode) is a power saving mode
*               that keeps the radio powered up continuously to
*               ensure there is a minimal lag in response time.
*               This power saving setting consumes the most power
*               but offers the highest throughput.
* @param 2 FAST_POWERSAVE: Fast is a power saving mode that
*               switches between power saving and CAM modes,
*               depending on the network traffic.
*               For example, it switches to CAM when receiving
*               a large number of packets and switches back to power saving mode
*               after the packets have been retrieved.
*               Fast is recommended when power consumption and throughput
*               are a concern.
* @param 3 LEGACY_POWERSAVE: The access point buffers incoming messages
*               for the radio. The radio occasionally 'wakes up' to
*               determine if any buffered messages are waiting and then
*               returns to sleep mode after it requests each message.
*               This setting conserves the most power but also provides
*               the lowest throughput. It is recommended for radios where
*               power consumption is the most important concern.
*               (such as small battery-operating devices).
* @return  >=0 the operation completed successfully, <0 the operation failed.
*
*/
int32_t wifi_config_get_power_save_mode(uint8_t *power_save_mode);

/**
* @brief Set the Wi-Fi Power Save mode, only for the STA mode.
* This is not supported yet.
*
* @param[in] power_save_mode
* @param 1 CAM: CAM (Constantly Awake Mode) is a power saving mode
*               that keeps the radio powered up continuously to
*               ensure there is a minimal lag in response time.
*               This power saving setting consumes the most power
*               but offers the highest throughput.
* @param 2 FAST_POWERSAVE: Fast is a power saving mode that
*               switches between power saving and CAM modes,
*               depending on the network traffic.
*               For example, it switches to CAM when receiving
*               a large number of packets and switches back to power saving mode
*               after the packets have been retrieved.
*               Fast is recommended when power consumption and throughput
*               are a concern.
* @param 3 LEGACY_POWERSAVE: The access point buffers incoming messages
*               for the radio. The radio occasionally 'wakes up' to
*               determine if any buffered messages are waiting and then
*               returns to sleep mode after it requests each message.
*               This setting conserves the most power but also provides
*               the lowest throughput. It is recommended for radios where
*               power consumption is the most important concern.
*               (such as small battery-operating devices).
* @return  >=0 the operation completed successfully, <0 the operation failed.
*
*/
int32_t wifi_config_set_power_save_mode(uint8_t power_save_mode);
#endif

/**
* @brief This function gets the authentication and encryption modes used in the WIFI driver for a specific wireless port.
*
* @param[in] port indicates the WIFI port that the function will operate on.
*
* Value                         |Definition                                                              |
* ------------------------------|------------------------------------------------------------------------|
* \b #WIFI_PORT_STA             | STA|
* \b #WIFI_PORT_APCLI           | AP Client|
* \b #WIFI_PORT_AP              | AP|
*
* @param[out]  auth_mode is the authentication mode. For details about this parameter, please refer to
* #wifi_auth_mode_t.
* @param[out]  encrypt_type is the encryption mode. For details about this parameter, please refer to
* #wifi_encrypt_type_t.
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*/
int32_t wifi_config_get_security_mode(uint8_t port, wifi_auth_mode_t *auth_mode, wifi_encrypt_type_t *encrypt_type);

/**
* @brief This function sets the authentication and encryption modes used in the WIFI driver for a specific wireless port.
* This operation only takes effect after wifi_config_reload_setting() is called.
*
* @param[in] port indicates the WIFI port that the function will operate on.
*
* Value                         |Definition                                                              |
* ------------------------------|------------------------------------------------------------------------|
* \b #WIFI_PORT_STA             | STA|
* \b #WIFI_PORT_APCLI           | AP Client|
* \b #WIFI_PORT_AP              | AP|
*
* @param[in] auth_mode is the authentication mode. For details about this parameter, please refer to
* #wifi_auth_mode_t.
* @param[in] encrypt_type is the encryption mode. For details about this parameter, please refer to
* #wifi_encrypt_type_t.
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*/
int32_t wifi_config_set_security_mode(uint8_t port, wifi_auth_mode_t auth_mode, wifi_encrypt_type_t encrypt_type);

/**
* @brief This function gets the password of WPA-PSK or WPA2-PSK encryption type used in the WIFI driver for a specific wireless port.
*
* @param[in] port indicates the WIFI port that the function will operate on.
*
* Value                         |Definition                                                              |
* ------------------------------|------------------------------------------------------------------------|
* \b #WIFI_PORT_STA             | STA|
* \b #WIFI_PORT_APCLI           | AP Client|
* \b #WIFI_PORT_AP              | AP|
*
* @param[out]  passphrase is 8 ~ 63 bytes ASCII or 64 bytes hexadecimal.
* @param[out]  passphrase_length is the length range around 8 ~ 64.
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*/
int32_t wifi_config_get_wpa_psk_key(uint8_t port, uint8_t *passphrase, uint8_t *passphrase_length);

/**
* @brief This function sets the password of WPA-PSK or WPA2-PSK encryption type used in the WIFI driver for a specific wireless port.
* This operation only takes effect after #wifi_config_reload_setting() is called.  If user called the
* following two APIs in a sequence, #wifi_config_set_pmk(), #wifi_config_set_wpa_psk_key(), only the last
* one will take effect. Once #wifi_config_reload_setting() is called after #wifi_config_set_wpa_psk_key(),
* the user can get the related PMK value by calling #wifi_config_get_pmk(). The PMK value is calculated
* using the PSK data.
*
* @param[in] port indicates the WIFI port that the function will operate on.
*
* Value                         |Definition                                                              |
* ------------------------------|------------------------------------------------------------------------|
* \b #WIFI_PORT_STA             | STA|
* \b #WIFI_PORT_APCLI           | AP Client|
* \b #WIFI_PORT_AP              | AP|
*
* @param[in] passphrase is 8 ~ 63 bytes ASCII or 64 bytes hexadecimal.
* @param[in] passphrase_length is the length range around 8 ~ 64.
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*/
int32_t wifi_config_set_wpa_psk_key(uint8_t port, uint8_t *passphrase, uint8_t passphrase_length);

/**
* @brief This function gets the PMK used in the WIFI driver for a specific wireless port.
* @param[in] port indicates the WIFI port that the function will operate on.
*
* Value                         |Definition                                                              |
* ------------------------------|------------------------------------------------------------------------|
* \b #WIFI_PORT_STA             | STA|
* \b #WIFI_PORT_APCLI           | AP Client|
* \b #WIFI_PORT_AP              | AP|
*
* @param[out]  pmk is pairwise master key, the shared secret key used in the
* IEEE 802.11 protocol.
*
* @return >=0 the operation completed successfully, <0 the operation failed.
*/
int32_t wifi_config_get_pmk(uint8_t port, uint8_t *pmk);

/**
* @brief This function sets the PMK used in the WIFI driver for a specific wireless port. This operation
* only takes effect after #wifi_config_reload_setting() is called. If user have called the following
* two APIs,  #wifi_config_set_pmk() or #wifi_config_set_wpa_psk_key(), only the last one will take effect.
* Once #wifi_config_reload_setting() is called after  #wifi_config_set_wpa_psk_key(), the user can get
* the related PMK value by calling #wifi_config_get_pmk(). The PMK value is calculated using the PSK data.
* The PSK should be ignored, if both PMK and PSK are available.
*
* @param[in] port indicates the WIFI port that the function will operate on.
*
* Value                         |Definition                                                              |
* ------------------------------|------------------------------------------------------------------------|
* \b #WIFI_PORT_STA             | STA|
* \b #WIFI_PORT_APCLI           | AP Client|
* \b #WIFI_PORT_AP              | AP|
*
* @param[out]  pmk is a pointer to the PMK buffer with a length of 32 Bytes.
* PMK is used in WPA-PSK or WPA2-PSK encryption type and the PMK length is 32Bytes.
*
* @return >=0 the operation completed successfully, <0 the operation failed.
*/
int32_t wifi_config_set_pmk(uint8_t port, uint8_t *pmk);

/**
* @brief This function gets the WEP key group used in the WIFI driver for a specific wireless port.
* @param[in] port indicates the WIFI port that the function will operate on.
*
* Value                         |Definition                                                              |
* ------------------------------|------------------------------------------------------------------------|
* \b #WIFI_PORT_STA             | STA|
* \b #WIFI_PORT_APCLI           | AP Client|
* \b #WIFI_PORT_AP              | AP|
*
* @param[out]  wep_keys is WEP keys. For more details, please refer to #wifi_wep_key_t.
*
* @return >=0 the operation completed successfully, <0 the operation failed.
*/
int32_t wifi_config_get_wep_key(uint8_t port, wifi_wep_key_t *wep_keys);

/**
* @brief This function sets the WEP key group used in the WIFI driver for a specific wireless port.
* This operation only takes effect after #wifi_config_reload_setting() is called.
*
* @param[in] port indicates the WIFI port that the function will operate on.
*
* Value                         |Definition                                                              |
* ------------------------------|------------------------------------------------------------------------|
* \b #WIFI_PORT_STA             | STA|
* \b #WIFI_PORT_APCLI           | AP Client|
* \b #WIFI_PORT_AP              | AP|
*
* @param[in] wep_keys is WEP keys. For more details, please refer to #wifi_wep_key_t.
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*/
int32_t wifi_config_set_wep_key(uint8_t port, wifi_wep_key_t *wep_keys);

/**
* @brief This function informs the wpa_supplicant to reload the configuration and applies the
* configurations settings of the Wi-Fi configure APIs. This function is applied to
* the following APIs: #wifi_config_set_ssid(), #wifi_config_set_security_mode(),
* #wifi_config_set_wpa_psk_key(), #wifi_config_set_wep_key(), #wifi_config_set_pmk().
* In wireless station mode, device will use the new configuration and start to scan
* and connect the target AP router. In wireless AP mode, device will load the new
* SSID and encryption information.
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*/
int32_t wifi_config_reload_setting(void);

/**
* @brief This function registers a handler to receive 802.11 raw packets from a network processor.
* @brief Once the handler is registered, the network processor doesn't send the packets
* to IP stack but delivers to the handler function.
* The raw packet includes received packet information header, 802.11 header and data. Usually, this API
* cooperates with RX filter set APIs; either #wifi_config_set_rx_filter() or #wifi_config_set_smart_connection_filter()
* , or both of them, to deal with specifically formatted RX packets.
*
* @param[in] wifi_rx_handler is the handler routine. For more information, please refer to #wifi_rx_handler_t.
* There is a limitation to use the handler that's based on the in-band mechanism.
* Calls to any in-band functions such as WIFI configure or WIFI connection API in wifi_rx_handler() are prohibited.
*
* @return >=0 the operation completed successfully, <0 the operation failed.
*
*/
int32_t wifi_config_register_rx_handler(wifi_rx_handler_t wifi_rx_handler);

/**
 * @brief This function unregisters the handler to receive 802.11 raw packets from network processor.
 * @brief Once the handler is unregistered, the network processor will send the packets to the IP stack.
 *
 * @param[in] None
 *
 * @return >=0 the operation completed successfully, <0 the operation failed.
 *
 */
int32_t wifi_config_unregister_rx_handler();

/**
* @brief This function gets the WIFI RX filter used in the WIFI driver. The RX filter setting provides
* the packet format to be received, such as broadcast, multicast or unicast frames to me.
*
* @param[out] flag is defined in #wifi_rx_filter_t.
* @return  >=0 the operation completed successfully, <0 the operation failed.
*/
int32_t wifi_config_get_rx_filter(uint32_t  *flag);

/**
* @brief This function sets the WIFI RX filter used in the WIFI driver. The RX filter setting provides
* the packet format to be received, such as broadcast, multicast,
* unicast frames to me. This operation takes effect immediately.
*
* @param[in] flag is defined in #wifi_rx_filter_t.
*
* @return >=0 the operation completed successfully, <0 the operation failed.
*
* @note The default value is #WIFI_DEFAULT_IOT_RX_FILTER.
*/
int32_t wifi_config_set_rx_filter(uint32_t flag);

/**
* @brief This function gets MediaTek Smart Connection RX Filter used in the WIFI driver.
* When MediaTek Smart Connection filter is enabled, the data frames with
* ToDS=1, A3=multicast address will be received and delivered to the
* RX filter handler,  other frames will be dropped.
* Call #wifi_config_set_rx_filter() to receive other frames.
*
* @param[out]  flag indicates if the smart connection function is enabled or disabled.
*
* Value                         |Definition                                                              |
* ------------------------------|------------------------------------------------------------------------|
* \b 0                          | DISABLE|
* \b 1                          | ENABLE|
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*/
int32_t wifi_config_get_smart_connection_filter(uint8_t *flag);

/**
* @brief This function sets MediaTek Smart Connection RX Filter used in the WIFI driver.
* This operation takes effect immediately.
* When MediaTek smart connection filter is enabled, MediaTek Smart Connection packets will be delivered to the RX queue directly,
* the other packets will be delivered to the RX filter. For more information, please refer to #wifi_config_set_rx_filter().
*
* @param[in] flag is the parameter set to enable or disable smart connection function.
*
* Value                         |Definition                                                              |
* ------------------------------|------------------------------------------------------------------------|
* \b 0                          | DISABLE|
* \b 1                          | ENABLE|
*
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*/
int32_t wifi_config_set_smart_connection_filter(uint8_t flag);

/**
* @brief This function gets the radio status of the WIFI driver.
*
* @param[out]  on_off indicates the WIFI radio is on or off.
*
* Value                         |Definition                                                              |
* ------------------------------|------------------------------------------------------------------------|
* \b 0                          | OFF the WIFI radio is turned off, and WIFI TX/RX is disabled.|
* \b 1                          | ON the WIFI radio is turned on, and WIFI TX/RX is enabled.|
*
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*
* @note In dual mode, both WIFI interface and WIFI radio are turned on/off at the same time.
*/
int32_t wifi_config_get_radio(uint8_t *on_off);

/**
* @brief This function sets the radio status of the WIFI driver. This operation takes effect immediately.
*
* @param[in] on_off indicates the WIFI radio is on or off.
*
* Value                         |Definition                                                              |
* ------------------------------|------------------------------------------------------------------------|
* \b 0                          | OFF the WIFI radio is turned off, and WIFI TX/RX is disabled|
* \b 1                          | ON the WIFI radio is turned on, and WIFI TX/RX is enabled|
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*
* @note In dual mode, both WIFI interface and WIFI radio are turned on/off at the same time.
*/
int32_t wifi_config_set_radio(uint8_t on_off);

/**
* @brief This function disconnects the current connection. It takes effect immediately. The device
* switches to scan state to scan and connect to an AP router with an existing Wi-Fi
* configuration. This API is available only in a station mode.
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*
*/
int32_t wifi_connection_disconnect_ap();

/**
* @brief This function disconnects specific station's connection, and takes effect immediately. This
* API is available only in an AP mode.
*
* @param[in] address is station's MAC address.
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*/
int32_t wifi_connection_disconnect_sta(uint8_t *address);

/**
* @brief This function gets the current STA port's link up / link down connection status.
*
* @param[out]  link_status
* @param ##WIFI_STATUS_LINK_DISCONNECTED
* @param ##WIFI_STATUS_LINK_CONNECTED
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*
* @note #WIFI_STATUS_LINK_DISCONNECTED indicates station may be in
*       IDLE/ SCAN/ CONNECTING state.
*/
int32_t wifi_connection_get_link_status(uint8_t *link_status);

/**
* @brief This function initializes the scan table to the driver.
*
* @param[in] ap_list is a pointer of the user buffer where the further scanned AP list will be stored.
* @param[in] max_count is the maximum number of ap_list can be stored.
*
* @return   >=0 the operation completed successfully, <0 the operation failed.
*
* @note #wifi_connection_scan_init() should be called before calling #wifi_connection_start_scan(), and it should be called only once to initialize one scan.
* @note When the scan is done, the scanned AP list is already stored in #ap_list with descending order according to RSSI.
*/
int32_t wifi_connection_scan_init(wifi_scan_list_item_t *ap_list, uint32_t max_count);

/**
* @brief This function deinitializes the scan table.
*
* @return  >=0 means deinit success, <0 means deinit failed.
*
* @note When the scan is finished, #wifi_connection_scan_deinit() should be called to unload the buffer from the driver. After that, the data in the #ap_list can be processed by user applications safely, and then another scan can be initialized by calling #wifi_connection_scan_init().
*/
int32_t wifi_connection_scan_deinit(void);

/**
* @brief This function starts WIFI Scanning.
*
* @param[in] ssid is specified to scan. If SSID is NULL, scan all APs based on channel tables. Scan with SSID is to find hidden APs.
* @param[in] ssid_len is the length of the SSID.
* @param[in] bssid is specified to scan. If BSSID is NULL, scan all APs based on channel tables. Scan with BSSID is to send unicast probe request.
* @param[in] scan_mode is scan mode that can be either a full scan or a partial scan.
*
* Value                         |Definition                                                              |
* ------------------------------|------------------------------------------------------------------------|
* \b 0                          | Full|
* \b 1                          | Partial, it's expected to use in SoftAP mode and keep stations online.|
*
* In the partial scan mode, it starts to scan in the following method.
* If AP is currently on channel 5, it jumps to channels (1, 2) to scan,
* and then back to channel 5. After that it scans the channels (3, 4).
* The number of channels it scans each time is specified in the implementation.
* @param[in] scan_option selects scan options based on one of the following: active scan, passive scan or force active scan.
*
* Value                         |Definition                                                              |
* ------------------------------|------------------------------------------------------------------------|
* \b 0                          | Active scan, (Passive in regulatory channels). The channels that will be scanned are decided by the product's country and region. A probe request will be sent to each of these channels.|
* \b 1                          | Passive in all channels. Receives and processes the beacon. No probe request is sent.|
* \b 2                          | Force active (active in all channels). Forced to active scan in all channels. A probe request will be sent to each of these channels.|
*
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*
* @note If the SSID/BSSID is specified (not NULL).
* @note 1. Probe Request carries SSID (for Hidden AP).
* @note 2. Scan table always keeps the APs of the specified SSID/BSSID.
* @note 3. The station mode supports all scan modes and options.
* @note 4. The AP mode supports only the partial scan mode.
*/
int32_t wifi_connection_start_scan(uint8_t *ssid, uint8_t ssid_length, uint8_t *bssid, uint8_t scan_mode, uint8_t scan_option );

/**
* @brief This function stops the Wi-Fi Scanning triggered by #wifi_connection_start_scan(). If the device in station mode cannot connect to an AP, it keeps scanning till it connects to the target AP.
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*/
int32_t wifi_connection_stop_scan(void);

/**
* @brief This function parses the beacon or probe request packets.
*
* @param[in] pbuf  is a pointer to indicate the payload of beacon or probe request packets.
* @param[in] len is the length of packet's payload.
* @param[out]  ap_data is the buffer to store AP information received from beacon or probe request packet parse result.
* @return  <0 means parse failed, =0 means success.
*/
int32_t wifi_connection_parse_beacon(uint8_t *pbuf, uint32_t len, wifi_scan_list_item_t *ap_data);

/**
* @brief This function gets the station list associated with the Wi-Fi, only for SoftAP mode.
*
* @param[out]  sta_list is defined in #wifi_sta_list_t that includes station information such as RSSI, bandwidth, channel, MAC and TX rate.
* @param[out]  number returns the number of associated stations.
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*
*/
int32_t wifi_connection_get_sta_list(uint8_t *number, wifi_sta_list_t *sta_list);

/**
* @brief This function gets the maximum number of the supported stations in AP mode or dual mode.
*
* @param[out]  sta_number returns the maximum number of the supported stations.
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*
*/
int32_t wifi_connection_get_max_sta_number(uint8_t *sta_number);

/**
* @brief This function gets the RSSI of the connected AP. It's only used for STA mode and while the station is connected to the AP.
*
* @param[out]  rssi returns the RSSI of the connected AP.
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*
*
*/
int32_t wifi_connection_get_rssi(int8_t *rssi);

/**
* @brief This function registers the WIFI event handler. Each event can register multiple event handlers with maximum number of 16.
* In AP/STA mode, the scan stops automatically when the scan cycle is finished
* and SCAN COMPLETE event is triggered;\n
* In AP mode, once the device is disconnected from the station,  a DISCONNECT event with station's
* MAC address is triggered;\n
* In AP mode, once the station connects to the device, CONNECT event with station's
* MAC address is triggered;\n
* In STA mode, once the device disconnects from the AP, DISCONNECT event with BSSID is triggered;\n
* In STA mode, once the device connect to the AP, CONNECT event with BSSID is triggered.\n
*
* @param[in] event is the event ID. For more details, please refer to #wifi_event_t.
*
* Value                         |Definition                                                              |
* ------------------------------|------------------------------------------------------------------------|
* \b 0                          | #WIFI_EVENT_IOT_CONNECTED|
* \b 1                          | #WIFI_EVENT_IOT_SCAN_COMPLETE|
* \b 2                          | #WIFI_EVENT_IOT_DISCONNECTED|
* \b 3                          | #WIFI_EVENT_IOT_PORT_SECURE|
* \b 4                          | #WIFI_EVENT_IOT_REPORT_BEACON_PROBE_RESPONSE|
*
* @param[in] handler is the event handler. For more details, please refer to #wifi_event_handler_t.
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*/
int32_t wifi_connection_register_event_handler(wifi_event_t event, wifi_event_handler_t handler);

/**
* @brief This is only for compatibility purpose, so that applications implemented with the former API can work with the updated API.
*/
int32_t wifi_connection_register_event_notifier(uint8_t event, wifi_event_handler_t notifier);

/**
* @brief This function unregisters WIFI event handler. The function #wifi_connection_register_event_handler() registers an event and matches it with the corresponding event handler. For the event behavior, please refer to #wifi_connection_register_event_handler().
*
* @param[in] event is the event ID. For more details, please refer to #wifi_event_t for more details.
*
* Value                         |Definition                                                              |
* ------------------------------|------------------------------------------------------------------------|
* \b 0                          | #WIFI_EVENT_IOT_CONNECTED|
* \b 1                          | #WIFI_EVENT_IOT_SCAN_COMPLETE|
* \b 2                          | #WIFI_EVENT_IOT_DISCONNECTED|
* \b 3                          | #WIFI_EVENT_IOT_PORT_SECURE|
* \b 4                          | #WIFI_EVENT_IOT_REPORT_BEACON_PROBE_RESPONSE|
*
* @param[in] handler is the event handler. For more details, please refer to #wifi_event_handler_t.
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*/
int32_t wifi_connection_unregister_event_handler(wifi_event_t event, wifi_event_handler_t handler);

/**
* @brief This is only for compatibility purpose, so that applications implemented with the former API can work with the updated API.
*/
int32_t wifi_connection_unregister_event_notifier(uint8_t event, wifi_event_handler_t notifier);

/**
* @brief This function stores the operation mode in the NVRAM profile. \n
* NVRAM is an area on the flash memory. The profile is read to initialize the system at boot up.
* Call #wifi_profile_commit_setting() to commit the dirty profile to the flash for the APIs set with a WIFI profile.
*
* @param[in] mode indicates operation mode that can be set.
*
* Value                         |Definition                                                              |
* ------------------------------|------------------------------------------------------------------------|
* \b 0x01                       | #WIFI_MODE_STA_ONLY|
* \b 0x02                       | #WIFI_MODE_AP_ONLY|
* \b 0x03                       | #WIFI_MODE_DUAL|
* \b 0x04                       | #WIFI_MODE_MONITOR|
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*
* @note Use this function will reset the entire configuration set by previous WIFI Configure APIs.
*/
int32_t wifi_profile_set_opmode(uint8_t mode);

/**
* @brief This function gets the operation mode from a profile in the NVRAM.
*
* @param[out]  mode indicates operation mode in the NVRAM.
*
* Value                         |Definition                                                              |
* ------------------------------|------------------------------------------------------------------------|
* \b 0x01                       | #WIFI_MODE_STA_ONLY|
* \b 0x02                       | #WIFI_MODE_AP_ONLY|
* \b 0x03                       | #WIFI_MODE_DUAL|
* \b 0x04                       | #WIFI_MODE_MONITOR|
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*/
int32_t wifi_profile_get_opmode(uint8_t *mode);

/**
* @brief This function stores the channel in the NVRAM profile. For a specific wireless port and #WIFI_PORT_STA / #WIFI_PORT_APCLI use the same profile section.
* NVRAM is an area on the flash memory. The profile is read to initialize the system at boot up.
* Call #wifi_profile_commit_setting() to commit the dirty profile to the flash for the APIs set with a WIFI profile.
*
* @param[in] port indicates the WIFI port that the function will operate on.
*
* Value                         |Definition                                                              |
* ------------------------------|------------------------------------------------------------------------|
* \b #WIFI_PORT_STA             | STA|
* \b #WIFI_PORT_APCLI           | AP Client|
* \b #WIFI_PORT_AP              | AP|
*
* @param[in] channel    is the channel number used in the WIFI driver for a specific wireless port.
*                       The channel number range is about 1~14 for 2.4GHz. The specific channel number is determined
*                       by country region.
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*/
int32_t wifi_profile_set_channel(uint8_t port, uint8_t channel);

/**
* @brief This function gets the channel from the NVRAM profile. For a specific wireless port and #WIFI_PORT_STA / #WIFI_PORT_APCLI use the same profile section.
*
* @param[in] port indicates the WIFI port that the function will operate on.
*
* Value                         |Definition                                                              |
* ------------------------------|------------------------------------------------------------------------|
* \b #WIFI_PORT_STA             | STA|
* \b #WIFI_PORT_APCLI           | AP Client|
* \b #WIFI_PORT_AP              | AP|
*
* @param[out]  channel    is the channel number used in the WIFI driver for a specific wireless port.
*                         The channel number range is about 1~14 for 2.4GHz. The specific channel number is determined
*                         by country region.
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*/
int32_t wifi_profile_get_channel (uint8_t port, uint8_t *channel);

/**
* @brief This function stores bandwidth in the NVRAM profile. \n
* For a specific wireless port and #WIFI_PORT_STA / #WIFI_PORT_APCLI use the same profile section.
* NVRAM is an area on the flash memory. The profile is read to initialize the system at boot time.
* Call #wifi_profile_commit_setting() to commit the dirty profile to the flash for the APIs set with a WIFI profile.
*
* @param[in] port indicates the WIFI port that the function will operate on.
*
* Value                         |Definition                                                              |
* ------------------------------|------------------------------------------------------------------------|
* \b #WIFI_PORT_STA             | STA|
* \b #WIFI_PORT_APCLI           | AP Client|
* \b #WIFI_PORT_AP              | AP|
*
* @param[in] bandwidth is the wireless bandwidth.
*
* Value                                                       |Definition                                |
* ------------------------------------------------------------|------------------------------------------|
* \b #WIFI_IOT_COMMAND_CONFIG_BANDWIDTH_20MHZ                 | 20MHz |
* \b #WIFI_IOT_COMMAND_CONFIG_BANDWIDTH_40MHZ                 | 40MHz |
* \b #WIFI_IOT_COMMAND_CONFIG_BANDWIDTH_2040MHZ               | 20 or 40MHz |
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*
* @note    The default value is #WIFI_IOT_COMMAND_CONFIG_BANDWIDTH_20MHZ.
*/
int32_t wifi_profile_set_bandwidth(uint8_t port, uint8_t bandwidth);

/**
* @brief  This function gets bandwidth from the NVRAM profile. For a specific wireless port and #WIFI_PORT_STA / #WIFI_PORT_APCLI use the same profile section.
*
* @param[in] port indicates the WIFI port that the function will operate on.
*
* Value                         |Definition                                                              |
* ------------------------------|------------------------------------------------------------------------|
* \b #WIFI_PORT_STA             | STA|
* \b #WIFI_PORT_APCLI           | AP Client|
* \b #WIFI_PORT_AP              | AP|
*
* @param[out]  bandwidth is the wireless bandwidth.
*
* Value                                                        |Definition                               |
* -------------------------------------------------------------|-----------------------------------------|
* \b #WIFI_IOT_COMMAND_CONFIG_BANDWIDTH_20MHZ                  | 20MHz |
* \b #WIFI_IOT_COMMAND_CONFIG_BANDWIDTH_40MHZ                  | 40MHz |
* \b #WIFI_IOT_COMMAND_CONFIG_BANDWIDTH_2040MHZ                | 20 or 40MHz |
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*
* @note    The default value is #WIFI_IOT_COMMAND_CONFIG_BANDWIDTH_20MHZ.
*/
int32_t wifi_profile_get_bandwidth(uint8_t port, uint8_t *bandwidth);

/**
* @brief This function gets WIFI interface MAC address from the NVRAM profile.
*
* @param[in] port indicates the WIFI port that the function will operate on.
*
* Value                         |Definition                                                              |
* ------------------------------|------------------------------------------------------------------------|
* \b #WIFI_PORT_STA             | STA|
* \b #WIFI_PORT_APCLI           | AP Client|
* \b #WIFI_PORT_AP              | AP|
*
* @param[out]  address is the MAC address (6 bytes).
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*/
int32_t  wifi_profile_get_mac_address(uint8_t port, uint8_t *address);

/**
* @brief This function sets WIFI interface MAC address in the NVRAM profile. For a specific wireless port,
* #WIFI_PORT_STA / #WIFI_PORT_APCLI use the same profile section. Currently, in AP mode, WIFI driver
* also use MAC address in STA profile section. NVRAM is an area on the flash memory.
* The profile is read to initialize the system at boot time.
* Call #wifi_profile_commit_setting() to commit the dirty profile to the flash for the APIs set with a WIFI profile.
* Note that there is no corresponding wifi_config_set_mac_address(), because MAC
* address cannot be modified dynamically.
*
* @param[in] port indicates the WIFI port which the function will operate to.
*
* Value                         |Definition                                                              |
* ------------------------------|------------------------------------------------------------------------|
* \b #WIFI_PORT_STA             | STA|
* \b #WIFI_PORT_APCLI           | AP Client|
* \b #WIFI_PORT_AP              | AP|
*
* @param[in] address is the buffer indicates the MAC Address, 6bytes length.
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*/
int32_t wifi_profile_set_mac_address(uint8_t port, uint8_t *address);

/**
* @brief This function stores the SSID in the NVRAM profile. \n
* For a specific wireless port, #WIFI_PORT_STA / #WIFI_PORT_APCLI use the same profile section.
* NVRAM is an area on the flash memory. The profile is read to initialize the system at boot time.
* Call #wifi_profile_commit_setting() to commit the dirty profile to the flash for the APIs set with a WIFI profile.
*
* @param[in] port indicates the WIFI port that the function will operate on.
*
* Value                         |Definition                                                              |
* ------------------------------|------------------------------------------------------------------------|
* \b #WIFI_PORT_STA             | STA|
* \b #WIFI_PORT_APCLI           | AP Client|
* \b #WIFI_PORT_AP              | AP|
*
* @param[in] ssid is the SSID content. If #WIFI_PORT_STA or #WIFI_PORT_APCLI, the SSID indicate the target AP's SSID.
* If #WIFI_PORT_AP, the SSID indicates the device's own SSID.
* @param[in] ssid_length is the length of SSID, the maximum is 32 Bytes.
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*/
int32_t wifi_profile_set_ssid(uint8_t port, uint8_t *ssid ,uint8_t ssid_length);

/**
* @brief This function gets SSID from the NVRAM profile. For a specific wireless port, #WIFI_PORT_STA / #WIFI_PORT_APCLI use the same profile section.
*
* @param[in] port indicates the WIFI port that the function will operate on.
*
* Value                         |Definition                                                              |
* ------------------------------|------------------------------------------------------------------------|
* \b #WIFI_PORT_STA             | STA|
* \b #WIFI_PORT_APCLI           | AP Client|
* \b #WIFI_PORT_AP              | AP|
*
* @param[out]  ssid is the SSID content. If #WIFI_PORT_STA or #WIFI_PORT_APCLI, the SSID indicates the target AP's SSID.
* If #WIFI_PORT_AP, the SSID indicates the device's own SSID.
* @param[out]  ssid_length is the length of SSID, the maximum is 32 Bytes.
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*/
int32_t wifi_profile_get_ssid(uint8_t port, uint8_t *ssid, uint8_t *ssid_length);

/**
* @brief This function stores the WIFI Wireless Mode in the NVRAM profile. \n
* For a specific wireless port, #WIFI_PORT_STA / #WIFI_PORT_APCLI use the same profile section.
* NVRAM is an area on the flash memory. The profile is read to initialize the system at boot time.
* Call #wifi_profile_commit_setting() to commit the dirty profile to the flash for the APIs set with a WIFI profile.
*
* @param[in] port indicates the WIFI port that the function will operate on.
*
* Value                         |Definition                                                              |
* ------------------------------|------------------------------------------------------------------------|
* \b #WIFI_PORT_STA             | STA|
* \b #WIFI_PORT_APCLI           | AP Client|
* \b #WIFI_PORT_AP              | AP|
*
* @param[in] mode  is wireless mode. For more details, please refer to #wifi_phy_mode_t.
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*/
int32_t wifi_profile_set_wireless_mode(uint8_t port, wifi_phy_mode_t mode);

/**
* @brief This function gets WIFI wireless mode from the NVRAM profile. For a specific wireless port, #WIFI_PORT_STA / #WIFI_PORT_APCLI use the same profile section.
*
* @param[in] port indicates the WIFI port that the function will operate on.
*
* Value                         |Definition                                                              |
* ------------------------------|------------------------------------------------------------------------|
* \b #WIFI_PORT_STA             | STA|
* \b #WIFI_PORT_APCLI           | AP Client|
* \b #WIFI_PORT_AP              | AP|
*
* @param[out]  mode is wireless mode. For more details, please refer to #wifi_phy_mode_t.
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*/
int32_t wifi_profile_get_wireless_mode(uint8_t port, wifi_phy_mode_t *mode);

/**
* @brief This function stores WIFI authentication mode and encryption type in the NVRAM profile.
* For a specific wireless port, #WIFI_PORT_STA / #WIFI_PORT_APCLI use the same profile section.
* NVRAM is an area on the flash memory. The profile is read to initialize the system
* at boot time. Call #wifi_profile_commit_setting() to
* commit the dirty profile to the flash for the APIs set with a WIFI profile.
*
* @param[in] port indicates the WIFI port which the function will operate to.
*
* Value                         |Definition                                                              |
* ------------------------------|------------------------------------------------------------------------|
* \b #WIFI_PORT_STA             | STA|
* \b #WIFI_PORT_APCLI           | AP Client|
* \b #WIFI_PORT_AP              | AP|
*
* @param[out]  auth_mode is authentication mode. For more details, please refer to #wifi_auth_mode_t.
* @param[out]  encrypt_type is encryption type. For more details, please refer to #wifi_encrypt_type_t.
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*/
int32_t wifi_profile_set_security_mode(uint8_t port, wifi_auth_mode_t auth_mode, wifi_encrypt_type_t encrypt_type);

/**
* @brief This function gets WIFI authentication mode and encryption type from the NVRAM profile. For a specific wireless port, #WIFI_PORT_STA / #WIFI_PORT_APCLI use the same profile section.
*
* @param[in] port indicates the WIFI port that the function will operate on.
*
* Value                         |Definition                                                              |
* ------------------------------|------------------------------------------------------------------------|
* \b #WIFI_PORT_STA             | STA|
* \b #WIFI_PORT_APCLI           | AP Client|
* \b #WIFI_PORT_AP              | AP|
*
* @param[out]  auth_mode is authentication mode. For more details, please refer to #wifi_auth_mode_t.
* @param[out]  encrypt_type is encryption type. For more details, please refer to #wifi_encrypt_type_t.
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*/
int32_t wifi_profile_get_security_mode(uint8_t port, wifi_auth_mode_t *auth_mode, wifi_encrypt_type_t *encrypt_type);

/**
* @brief This function stores the WIFI WPAPSK/WPA2PSK passphrase in the NVRAM profile. \n
* For a specific wireless port, #WIFI_PORT_STA / #WIFI_PORT_APCLI use the same profile section.
* NVRAM is an area on the flash memory. The profile is read to initialize the system
* at boot time. Call #wifi_profile_commit_setting() to
* commit the dirty profile to the flash for the APIs set with a WIFI profile.
* PMK is preferred if PSK and PMK exist simultaneously.
*
*
* @param[in] port indicates the WIFI port that the function will operate on.
*
* Value                         |Definition                                                              |
* ------------------------------|------------------------------------------------------------------------|
* \b #WIFI_PORT_STA             | STA|
* \b #WIFI_PORT_APCLI           | AP Client|
* \b #WIFI_PORT_AP              | AP|
*
* @param[in] passphrase is 8 ~ 63 bytes ASCII or 64 bytes hexadecimal.
* @param[in] passphrase_length is the length range around 8 ~ 64.
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*/
int32_t wifi_profile_set_wpa_psk_key(uint8_t port, uint8_t *passphrase, uint8_t passphrase_length);

/**
* @brief This function gets WIFI WPAPSK/WPA2PSK passphrase from the NVRAM profile. For a specific wireless port, #WIFI_PORT_STA / #WIFI_PORT_APCLI use the same profile section.
*
* @param[in] port indicates the WIFI port that the function will operate on.
*
* Value                         |Definition                                                              |
* ------------------------------|------------------------------------------------------------------------|
* \b #WIFI_PORT_STA             | STA|
* \b #WIFI_PORT_APCLI           | AP Client|
* \b #WIFI_PORT_AP              | AP|
*
* @param[out]  passphrase is 8 ~ 63 bytes ASCII or 64 bytes hexadecimal.
* @param[out]  passphrase_length is the length range around 8 ~ 64.
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*/
int32_t wifi_profile_get_wpa_psk_key(uint8_t port, uint8_t *passphrase, uint8_t *passphrase_length);

/**
* @brief This function stores the PMK key in the NVRAM profile. For a specific wireless port, #WIFI_PORT_STA / #WIFI_PORT_APCLI use the same profile section.
* NVRAM is an area on the flash memory. The profile is read to initialize the system
* at boot time. Call #wifi_profile_commit_setting() to
* commit the dirty profile to the flash for the APIs set with a WIFI profile.
* PMK is preferred if PSK and PMK exist simultaneously.
*
* @param[in] port indicates the WIFI port that the function will operate on.
*
* Value                         |Definition                                                              |
* ------------------------------|------------------------------------------------------------------------|
* \b #WIFI_PORT_STA             | STA|
* \b #WIFI_PORT_APCLI           | AP Client|
* \b #WIFI_PORT_AP              | AP|
*
* @param[in] pmk is Pairwise Master Key, the shared secret key used in the
* IEEE 802.11 protocol.
*
* @return >=0 the operation completed successfully, <0 the operation failed.
*/
int32_t wifi_profile_set_pmk(uint8_t port, uint8_t *pmk);

/**
* @brief This function gets the PMK key from the NVRAM profile.
* @param[in] port indicates the WIFI port that the function will operate on.
*
* Value                         |Definition                                                              |
* ------------------------------|------------------------------------------------------------------------|
* \b #WIFI_PORT_STA             | STA|
* \b #WIFI_PORT_APCLI           | AP Client|
* \b #WIFI_PORT_AP              | AP|
*
* @param[out]  pmk is Pairwise Master Key, the shared secret key used in the
* IEEE 802.11 protocol.
*
* @return >=0 the operation completed successfully, <0 the operation failed.
*/
int32_t wifi_profile_get_pmk(uint8_t port, uint8_t *pmk);

/**
* @brief This function stores WIFI WEP Keys in the NVRAM profile. For a specific wireless port,
* #WIFI_PORT_STA / #WIFI_PORT_APCLI use the same profile section.
* NVRAM is an area on the flash memory. The profile is read to initialize the system
* at boot time. Call #wifi_profile_commit_setting() to commit the dirty profile to the flash for the APIs set with a WIFI profile.
*
* @param[in] port indicates the WIFI port that the function will operate on.
*
* Value                         |Definition                                                              |
* ------------------------------|------------------------------------------------------------------------|
* \b #WIFI_PORT_STA             | STA|
* \b #WIFI_PORT_APCLI           | AP Client|
* \b #WIFI_PORT_AP              | AP|
*
* @param[in] wep_keys is WEP keys. For more details, please refer to #wifi_wep_key_t.
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*/
int32_t wifi_profile_set_wep_key(uint8_t port, wifi_wep_key_t *wep_keys);

/**
* @brief This function gets WIFI WEP Keys from the NVRAM profile. For a specific wireless port, #WIFI_PORT_STA / #WIFI_PORT_APCLI use the same profile section.
* @param[in] port indicates the WIFI port that the function will operate on.
*
* Value                         |Definition                                                              |
* ------------------------------|------------------------------------------------------------------------|
* \b #WIFI_PORT_STA             | STA|
* \b #WIFI_PORT_APCLI           | AP Client|
* \b #WIFI_PORT_AP              | AP|
*
* @param[out]  wep_keys is WEP keys. For more details, please refer to #wifi_wep_key_t.
*
* @return >=0 the operation completed successfully, <0 the operation failed.
*/
int32_t wifi_profile_get_wep_key(uint8_t port, wifi_wep_key_t *wep_keys);

/**
* @brief This function gets WIFI country region used in the WIFI driver.
* Various world regions have allocated different amounts of frequency space
* around 2.4GHz for WIFI and some of them have fewer or more channels
* available than others. The region setting ensures that your router will only
* let you use the WIFI channels valid in your location.
*
* @param[in] band  indicates the WIFI bandwidth that the function will operate on.
*
* Value                         |Definition                                                              |
* ------------------------------|------------------------------------------------------------------------|
* \b #WIFI_BAND_2_4_G           | 2.4GHz|
* \b #WIFI_BAND_5_G             | 5GHz|
*
* @param[out]  region  is the region code that relates to the channel list. For more details, please refer to #wifi_config_set_country_region().
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*/
int32_t wifi_profile_get_country_region(uint8_t band, uint8_t  *region);

/**
* @brief This function sets WIFI Country Region in the NVRAM Profile.
* Various world regions have allocated different amounts of frequency space
* around 2.4GHz for WIFI and so some of them have fewer or more channels
* available than others. The region setting ensures that your router will only
* let you use the WIFI channels valid in your location.
* NVRAM is an area on the flash memory. The profile is read to initialize the system
* at boot time. Call #wifi_profile_commit_setting() to commit the dirty profile to the flash for the APIs set with a WIFI profile.
*
* @param[in] band indicates the WIFI bandwidth that the function will operate on.
*
* Value                         |Definition                                                              |
* ------------------------------|------------------------------------------------------------------------|
* \b #WIFI_BAND_2_4_G           | 2.4GHz|
* \b #WIFI_BAND_5_G             | 5GHz|
*
* @param[in] region is the region code that relates to the channel list. For more details, please refer to #wifi_config_set_country_region().
 *
* @return  >=0 the operation completed successfully, <0 the operation failed.
*/
int32_t wifi_profile_set_country_region(uint8_t band, uint8_t region);

/**
* @brief This function gets WIFI DTIM interval from the NVRAM profile.
*
* @param[out]  interval is the number range around 1 ~ 255 beacon's interval. For more details, please refer to #wifi_config_set_dtim_interval().
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*
*/
int32_t wifi_profile_get_dtim_interval(uint8_t *interval);

/**
* @brief This function sets WIFI DTIM interval in the NVRAM profile. This API is only for STA mode.
* NVRAM is an area on the flash memory. The profile is read to initialize the system
* at boot time. Call #wifi_profile_commit_setting() to
* commit the dirty profile to the flash for the APIs set with a WIFI profile.
*
* @param[in] interval is the number range around 1 ~ 255 beacon's interval. For more details, please refer to #wifi_config_set_dtim_interval().
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*/
int32_t wifi_profile_set_dtim_interval(uint8_t interval);

/**
* @brief This function gets WIFI Listen Interval from the NVRAM profile.
*
* @param[out]  interval is the number range around 1 ~ 255 beacon's interval. The beacon's interval is usually
* 100 times the unit (100*1.024 ms), which means, the DTIM interval range is around (1~255) * 102.4ms.
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*
*/
int32_t wifi_profile_get_listen_interval(uint8_t *interval);

/**
* @brief This function sets WIFI Listen Interval in the NVRAM profile. This API is only for STA mode.
* NVRAM is an area on the flash memory. The profile is read to initialize the system
* at boot time. Call #wifi_profile_commit_setting() to
* commit the dirty profile to the flash for the APIs set with a WIFI profile.
*
* @param[in] interval is the number range around 1 ~ 255 beacon's interval.
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*/
int32_t wifi_profile_set_listen_interval(uint8_t interval);

/**
* @brief This function stores WIFI power save mode in the NVRAM profile. \n
* NVRAM is an area on the flash memory. The profile is read to initialize the system
* at boot time. Call #wifi_profile_commit_setting() to
* commit the dirty profile to the flash for the APIs set with a WIFI profile.
*
* @param[in] power_save_mode indicates three power save mode below.
*
* Value                       |Definition                                                                |
* ----------------------------|--------------------------------------------------------------------------|
* \b 1                        | CAM: CAM (Constantly Awake Mode) is a power save mode that keeps the radio powered up continuously to ensure there is a minimal lag in response time. This power save setting consumes the most power but offers the highest throughput.|
* \b 2                        | FAST_POWERSAVE: Fast is a power save mode that switches between power saving and CAM modes, depending on the network traffic. For example, it switches to CAM when receiving a large number of packets and switches back to PS mode after the packets have been retrieved. Fast is recommended when power consumption and throughput are a concern.|
* \b 3                        | LEGACY_POWERSAVE: the access point buffers incoming messages for the radio. The radio occasionally 'wakes up' to determine if any buffered messages are waiting and then returns to sleep mode after it requests each message. This setting conserves the most power but also provides the lowest throughput. It is recommended for radios in which power consumption is the most important (such as small battery-operating devices).|
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*
*/
int32_t wifi_profile_set_power_save_mode(uint8_t power_save_mode);

/**
* @brief This function gets WIFI Power Save mode from the NVRAM profile. This profile setting only be load when system boot up.
*
* @param[out]  power_save_mode is the three power save mode can be set.
*
* Value                       |Definition                                                                |
* ----------------------------|--------------------------------------------------------------------------|
* \b 1                        | CAM: CAM (Constantly Awake Mode) is a power save mode that keeps the radio powered up continuously to ensure there is a minimal lag in response time. This power save setting consumes the most power but offers the highest throughput.|
* \b 2                        | FAST_POWERSAVE: is a power save mode that switches between power saving and CAM modes, depending on the network traffic. For example, it switches to CAM when receiving a large number of packets and switches back to PS mode after the packets have been retrieved. Fast is recommended when power consumption and throughput are a concern.|
* \b 3                        | LEGACY_POWERSAVE: is the access point buffers incoming messages for the radio. The radio occasionally 'wakes up' to determine if any buffered messages are waiting and then returns to sleep mode after it requests each message. This setting conserves the most power but also provides the lowest throughput. It is recommended for radios in which power consumption is the most important (such as small battery-operating devices).|
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*
*/
int32_t wifi_profile_get_power_save_mode(uint8_t *power_save_mode);

/**
* @brief This function commits all dirty settings in the NVRAM profile.
*
* @param[in]  profile_section  is the parameter only for "STA", "AP", "common".
*
* Value                         |Definition                                                              |
* ------------------------------|------------------------------------------------------------------------|
* \b STA                        | Write the setting about the station in NVRAM profile.|
* \b AP                         | Write the setting about the AP in NVRAM profile.|
* \b common                     | Write the OPMODE in NVRAM profile.|
*
* @return >=0 the operation completed successfully, <0 the operation failed.
*/
int32_t wifi_profile_commit_setting(char * profile_section);

/**
* @brief This function gets profile stored in NVRAM profile. For a specific wireless port, #WIFI_PORT_STA / #WIFI_PORT_APCLI use the same profile section.
*
* @param[in] port indicates the WIFI port that the function will operate on.
*
* Value                         |Definition                                                              |
* ------------------------------|------------------------------------------------------------------------|
* \b #WIFI_PORT_STA             | STA|
* \b #WIFI_PORT_APCLI           | AP Client|
* \b #WIFI_PORT_AP              | AP|
*
* @param[out]  profile is WIFI profile. For more details, please refer to #wifi_profile_t.
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*/
int32_t wifi_profile_get_profile(uint8_t port, wifi_profile_t *profile);

#ifdef MTK_WIFI_WPS_ENABLE
/**
* @brief This function gets the pin code of a specific wireless port, the pin code may be different for each function call.
* This function is only available when device is running in station mode or in AP mode.
*
* @param[in] port indicates the Wi-Fi port that the function will operate on.
*
* Value                         |Definition                                                              |
* ------------------------------|------------------------------------------------------------------------|
* \b #WIFI_PORT_STA             | STA|
* \b #WIFI_PORT_AP              | AP|
*
* @param[out]  pin_code is the pin code with 8 ASCII characters.
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*/
int32_t wifi_wps_config_get_pin_code(uint8_t port, uint8_t* pin_code);

/**
* @brief This function tiggers a WPS PBC process.
* This function is only available when the device is in station mode or AP mode.
* If port is #WIFI_PORT_AP, the device acts as a registrar and the BSSID should be NULL. The registrar will send a credential to enrollee after WPS successfully completes.
* If port is #WIFI_PORT_STA, the device acts as an enrollee. The enrollee will give the credentials from registrar and connect to the AP, then store the credential into the NVRAM using Wi-Fi profile APIs. The credentials include the SSID, #wifi_wep_key_t, authentication mode, encryption type and the PSK key.
* The BSSID is optional when port is set to #WIFI_PORT_STA.
* When the BSSID is set, enrollee will only complete the WPS process with the specific AP having the same BSSID.
* When the BSSID is NULL, enrollee will do the WPS process with the AP on which the PBC starts at the same time.
* If there are two or more APs working on WPS PBC, the process will fail according to the specifications.
* This function is only available when device is running in station mode or AP mode.
*
* @param[in] port indicates the Wi-Fi port that the function will operate on.
*
* Value                         |Definition                                                              |
* ------------------------------|------------------------------------------------------------------------|
* \b #WIFI_PORT_STA             | STA|
* \b #WIFI_PORT_AP              | AP|

* @param[in]  bssid is the target AP's MAC address, it should be NULL the port is set to #WIFI_PORT_AP.
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*/
int32_t wifi_wps_connection_by_pbc(uint8_t port, uint8_t *bssid);

/**
* @brief This function tiggers the WPS PIN process.
* If port is #WIFI_PORT_AP, the device is a registrar. In the WPS this condition, the BSSID should be NULL, and the pin is the target enrollee's pin code. The registrar will send the credentials to enrollee after WPS process completes successfully.
* If port is #WIFI_PORT_STA, the device is an enrollee. The enrollee credentials from registrar and connects the AP, then store the credential and the PSK into NVRAM provides by Wi-Fi profile APIs.The provide credentials include the SSID, #wifi_wep_key_t, authentication mode, encryption type and the PSK key.
* The BSSID is mandatory when port is set to #WIFI_PORT_STA.
* Get the pin_code by calling the #wifi_config_wps_get_pin_code().
* This function is only available when device is running in station mode or AP mode.
*
* @param[in] port indicates the Wi-Fi port that the function will operate on.
*
* Value                         |Definition                                                              |
* ------------------------------|------------------------------------------------------------------------|
* \b #WIFI_PORT_STA             | STA|
* \b #WIFI_PORT_AP              | AP|

* @param[in]  bssid is the target AP's MAC address, it should be NULL while the port is #WIFI_PORT_AP.
*
* @param[in]  pin_code is the enrollee's pin code with 8 ASCII characters,
*             when the device is an enrollee, the pin_code should be generated by #wifi_config_wps_get_pin_code(), the registrar should input the same pin code.
*             when the device is a registrar, the pin_code should be the enrollee's pin code that's transmitted to the registrar using keypad, UI or other interfaces.
* @return  >=0 the operation completed successfully, <0 the operation failed.
*/
int32_t wifi_wps_connection_by_pin(uint8_t port, uint8_t *bssid, uint8_t *pin_code);

/**
* @brief This function sets the WPS device information.
*
* @param[in] device_info indicates the device informaton. For more details, please refer to #wifi_wps_device_info_t.
*            device_information needs to be set each time before starting the WPS process.
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*/
int32_t wifi_wps_config_set_device_info(wifi_wps_device_info_t *device_info);

/**
* @brief This function gets the WPS device information.
*
* @param[out] device_info indicates the device informaton. For more details, please refer to #wifi_wps_device_info_t.
*             device_information can read back by this API after set.
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*/
int32_t wifi_wps_config_get_device_info(wifi_wps_device_info_t *device_info);

/**
* @brief This function controls the auto connection behavior after the WPS credential information is received by the Enrollee.
*
* @param[in] auto_connection set the auto_connection to true to enable auto connection, otherwise set it to false.
*                   When auto connection is enabled, the Enrollee will automatically connect to the target AP obtained from the WPS credential information after WPS process is complete.
*                   When auto connection is disabled, the Enrollee will not automatically connect to the target AP after the WPS process is complete.
*
* Value           |Definition                                                |
* ------------------------------|------------------------------------------------------------------------|
* \b  true        |Enable WI-FI auto connection.|
* \b  false       |Disable WI-FI auto connection.|
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*
* @note    Auto connection is enabled by default.
*/
int32_t wifi_wps_config_set_auto_connection(bool auto_connection);

/**
* @brief This function gets auto connection configuration.
*
* @param[out] auto_connection indicates whether auto connection is enabled or disabled.
*
* Value           |Definition                                                |
* ----------------|------------------------------------------------------------------------|
* \b  true        |Auto connection is enabled and the Enrollee will automatically connect to the target AP got from the WPS credential information after WPS process is done.|
* \b  false       |Auto connection is disabled and the Enrollee will not automatically connect to the target AP.|
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*/
int32_t wifi_wps_config_get_auto_connection(bool *auto_connection);

#endif //end of MTK_WIFI_WPS_ENABLE

/**
* @brief This function sends a raw Wi-Fi packet over the air.
*
* @param[in] raw_packet is a pointer to the raw packet which is a complete 802.11 packet including the 802.11 header and the payload.
* @param[in] length is the length of the raw packet in #raw_packet.
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*/
int32_t wifi_connection_send_raw_packet(uint8_t *raw_packet, uint32_t length);


#ifdef __cplusplus
}
#endif

/**
*@}
*/
#endif /* WIFI_API */

