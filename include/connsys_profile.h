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
 

#ifndef __CONNSYS_PROFILE_H__
#define __CONNSYS_PROFILE_H__

#include <stdint.h>

#define WIFI_PROFILE_PDA_HEADER_LEN     (12)

// copy from N9 wifi_uni_mac_7636/rom/include/iot/rt_bora.h
#define MAX_LEN_OF_SSID                 (32)

typedef struct _CIPHER_KEY 
{
    uint8_t   Key[16];            // right now we implement 4 keys, 128 bits max
    uint8_t   RxMic[8];           // make alignment 
    uint8_t   TxMic[8];
    uint8_t   TxTsc[6];           // 48bit TSC value
    uint8_t   RxTsc[6];           // 48bit TSC value
    uint8_t   CipherAlg;          // 0-none, 1:WEP64, 2:WEP128, 3:TKIP, 4:AES, 5:CKIP64, 6:CKIP128
    uint8_t   KeyLen; 
    uint8_t   BssId[6];
    uint8_t   Type;               // Indicate Pairwise/Group when reporting MIC error
} CIPHER_KEY;

typedef struct __attribute__ ((packed)) _CH_DESC_S
{
    unsigned char FirstChannel; 
    unsigned char NumOfCh;
    unsigned char ChannelProp; //0: Active, 1: Passive
    unsigned char Reserve; // 4-align and could be used to extend ChannelProp
} CH_DESC_T, *P_CH_DESC_T;

typedef struct _CH_LIST_S {
    unsigned char NumBGBandTriplet;
    unsigned char NumABandTriplet;
    CH_DESC_T Triplet[]; // BGBand Triplet followed by Aband Triplet
} CH_LIST_T, *P_CH_LIST_T;

typedef struct syscfg
{
    uint8_t OpMode;
    uint8_t CountryRegion;
    uint8_t CountryRegionABand;
    uint8_t CountryCode[4];
    uint8_t RadioOff;
    uint8_t DbgLevel;
    uint16_t RTSThreshold;
    uint16_t FragThreshold;

    uint8_t STA_LocalAdminMAC;
    uint8_t STA_IpAddr[4];
    uint8_t STA_MacAddr[6];
    uint8_t STA_Ssid[32];
    uint8_t STA_SsidLen;
	uint8_t STA_BssType;
	uint8_t STA_Channel;
	uint8_t STA_BW;
	uint8_t STA_WirelessMode;
	uint8_t STA_BADecline;
	uint8_t STA_AutoBA;
	uint8_t STA_HT_MCS;
	uint8_t STA_HT_BAWinSize;
	uint8_t STA_HT_GI;
	uint8_t STA_HT_PROTECT;
	uint8_t STA_HT_EXTCHA;
	uint8_t STA_WmmCapable;
	uint8_t STA_ListenInterval;
	uint8_t STA_AuthMode;
	uint8_t STA_EncrypType;
	uint8_t STA_WpaPsk[64];
	uint8_t STA_WpaPskLen;
	//uint8_t STA_Password[32];	
	uint8_t STA_PMK[32];
	uint8_t STA_PairCipher;
	uint8_t STA_GroupCipher;
	uint8_t STA_DefaultKeyId;
	//CIPHER_KEY STA_SharedKey[4];
	//uint8_t STA_SharedKeyLen[4];
	//uint8_t STA_SharedKeyIdx;
	uint8_t STA_PSMode;
	uint8_t STA_KeepAlivePeriod;

    uint8_t AP_LocalAdminMAC;
    uint8_t AP_IpAddr[4];
    uint8_t AP_MacAddr[6];
    uint8_t AP_Ssid[32];
    uint8_t AP_SsidLen;
	uint8_t AP_Channel;
	uint8_t AP_BW;
	uint8_t AP_WirelessMode;
	uint8_t AP_AutoBA;
	uint8_t AP_HT_MCS;
	uint8_t AP_HT_BAWinSize;
	uint8_t AP_HT_GI;
	uint8_t AP_HT_PROTECT;
	uint8_t AP_HT_EXTCHA;
	uint8_t AP_WmmCapable;
	uint8_t AP_DtimPeriod;
	uint8_t AP_HideSSID;
	uint8_t AP_AutoChannelSelect;
	uint8_t AP_AuthMode;
	uint8_t AP_EncrypType;
	uint8_t AP_WpaPsk[64];
	uint8_t AP_WpaPskLen;
	//uint8_t AP_Password[32];
	uint8_t AP_PMK[32];
	uint8_t AP_PairCipher;
	uint8_t AP_GroupCipher;
	uint8_t AP_DefaultKeyId;
	//CIPHER_KEY AP_SharedKey[4];
	//uint8_t AP_SharedKeyLen[4];
	//uint8_t AP_SharedKeyIdx;

    // "scan channel table" and "regulatory table"
    unsigned char bg_band_entry_num;
    CH_DESC_T bg_band_triple[10];
    unsigned char a_band_entry_num;
    CH_DESC_T a_band_triple[10];
	uint8_t AP_Bcn_disEn;
    uint8_t forwarding_zero_copy;
}__attribute__ ((packed)) syscfg_t;

typedef int (*connsys_wifi_profile_init_callback_t)(syscfg_t *cfg);
void connsys_register_wifi_profile_init(connsys_wifi_profile_init_callback_t callback);

#endif // #ifndef __CONNSYS_PROFILE_H__

