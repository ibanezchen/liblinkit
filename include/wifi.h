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

#ifndef __WIFI_H__
#define __WIFI_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define	IF_NAME_SIZE	16

#define IW_WPAS_APCLI_RELOAD_FLAG           0x0102 //align N9

#define	IW_SYS_EVENT_FLAG_START             0x0200
#define	IW_ASSOC_EVENT_FLAG                 0x0200
#define	IW_DISASSOC_EVENT_FLAG              0x0201
#define	IW_DEAUTH_EVENT_FLAG                0x0202
#define IW_MIC_ERROR_EVENT_FLAG             0x0209
#define IW_STA_LINKUP_EVENT_FLAG            0x020F
#define IW_STA_LINKDOWN_EVENT_FLAG          0x0210
#define IW_SCAN_COMPLETED_EVENT_FLAG        0x0211
#define IW_CANCEL_REMAIN_ON_CHANNEL_FLAG    0x0212
#define IW_TX_ACTION_STATUS_EVENT_FLAG      0x0213
#define IW_RX_ACTION_FRAME_EVENT_FLAG       0x0214




#define IW_CUSTOM_EVENT_FLAG                0x8C02
#define IW_ASSOCREQ_IE_EVENT_FLAG 	        0x8C07
#define IW_REASSOCREQ_IE_EVENT_FLAG         0x8C0A

typedef struct {
  int32_t		value;
  uint8_t		fixed;
  uint8_t		disabled;
  uint16_t		flags;
} iw_param_t;

typedef struct {
  int32_t		m;
  int16_t		e;
  uint8_t		i;
  uint8_t       flags;
} iw_freq_t;

typedef struct {
    void *pointer;
    uint16_t length;
    uint16_t flags;
} iw_point_t;

typedef struct {
	uint8_t 	sa_family;
	int8_t		sa_data[14];
}sockaddr;

struct	__attribute__ ((packed))	iw_quality
{
	uint8_t		qual;
	uint8_t		level;
	uint8_t		noise;
	uint8_t		updated;
};

typedef union {
    char		name[IF_NAME_SIZE];
    iw_point_t  essid;
    iw_param_t	nwid;
    iw_freq_t	freq;
    iw_param_t	sens;
    iw_param_t	bitrate;
    iw_param_t	txpower;
    iw_param_t  rts;
    iw_param_t  frag;
    uint32_t    mode;
    iw_param_t  retry;
    iw_point_t  encoding;
    iw_param_t  power;
    struct iw_quality  qual;
    sockaddr	ap_addr;
    sockaddr	addr;
    iw_point_t  data;
    iw_param_t  param;
} iwreq_data_t;

#ifdef __cplusplus
	}
#endif


#endif	/* __WIFI_H__ */
