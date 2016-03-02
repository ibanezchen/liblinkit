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
 

#ifndef __INBAND_QUEUE_H__
#define __INBAND_QUEUE_H__

#include "type_def.h"


#define CFG_INBAND_CMD_RSP_WAIT_TIME_VAL 5000 /* unit is ms */
#define CFG_INBAND_CMD_RSP_WAIT_PERIOD_VAL 10 /* unit is ms */


#define DBG_INBAND(FEATURE, _Fmt) \
        {                                       \
            if (g_inband_debug_feature & FEATURE)   \
            {               \
                printf _Fmt; \
            }   \
        }

#define INBAND_DBG_MAIN   (1<<0)


typedef struct _DL_LIST
{
	struct _DL_LIST *Next;
	struct _DL_LIST *Prev;
	struct _DL_LIST *CurrentList;

}DL_LIST, *PDL_LIST;


typedef enum _ENUM_INBNAD_HANDLE_T {
    INBAND_HANDLE_NON_HANDLE = 0,
    INBAND_HANDLE_RSP,
    INBAND_HANDLE_EVENT_HANDLER
} ENUM_INBNAD_HANDLE_T;





typedef int (*P_INBAND_RSP_HANDLER)(unsigned int, unsigned int, unsigned int);

typedef struct __CONNSYS_INBAND_REQ
{
    DL_LIST list; /* used for rsp queue */
    UINT8 cmd_id;
    UINT8 seq;
    UINT16 in_len;
    UINT8 *in_buf;
    UINT16 out_len;
    UINT8 *out_buf;
    void *wait_sema; /* if not null => need wait */
    P_INBAND_RSP_HANDLER rsp_handler;
    UINT8 need_rsp;
    UINT8 is_head; /* used for DL_LIST head */
    UINT8 ret_status; /* record return status */
    UINT8 is_query; /* used for query cmd, in-band header: ucReserved = 1 to indicate query */
    UINT8 completed; /* used for busy looping case, instead of wait_semaphore */
	UINT8 is_ext_cmd; /* for EXT in-band-cmd */
} CONNSYS_INBAND_REQ_T, *P_CONNSYS_INBAND_REQ_T;

typedef void (* inband_handle_func_t)(void* pkt_ptr, unsigned char *payload, unsigned int len);

struct inband_callback_func {
    inband_handle_func_t  handle_func_callback;
};

long inband_cmd_init();
uint8_t inband_cli_flags(uint8_t len, char *param[]);
int inband_send_query_cmd(unsigned char cmd_id, unsigned char *buf, ssize_t len, unsigned char *ret_buf, ssize_t out_len, unsigned char is_from_isr, unsigned char is_ext_cmd);
int inband_send_execute_cmd(unsigned char cmd_id, unsigned char *buf, ssize_t len, unsigned char is_from_isr, unsigned char is_ext_cmd);
int inband_evt_handler(void* pkt_ptr, unsigned char *payload, unsigned int len);
void show_n9_assert(void);
void inband_register_handle_func_callback(inband_handle_func_t func);
void inband_handle_func_body(void* pkt_ptr, unsigned char *payload, unsigned int len);
uint8_t inband_cli_handler(uint8_t len, char *param[]);


#endif /* INBAND_QUEUE */

