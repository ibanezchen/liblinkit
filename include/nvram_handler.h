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

/*
 * nvram_handler.h
 *
 *  Created on: 2015/7/14
 *      Author: mtk04880
 */
#ifndef NVRAM_HANDLER_H_
#define NVRAM_HANDLER_H_

#ifdef __cplusplus
extern "C" {
#endif
/*Maximum of key length*/
#ifndef KEY_LEN_MAX
#define KEY_LEN_MAX (64)
#endif
/*Maximum of value length*/
#ifndef VALUE_LEN_MAX
#define VALUE_LEN_MAX (256)
#endif
/*Maximum of key numbers*/
#ifndef KEY_NUM_MAX
#define KEY_NUM_MAX	(128)
#endif

#define NVRAM_VER "0.4"
#define NVRAM_BUILD_DATE      __DATE__
#define NVRAM_BUILD_TIME      __TIME__

#define nvram_status_t long

enum{
	CMD_GET = 0,
	CMD_SET,
	CMD_COMMIT,
	CMD_ERASE,
	CMD_REINIT,
	CMD_SHOW,
	CMD_DIRECT_SET
};

typedef struct nvram_data_s{
	char fb[KEY_LEN_MAX];
	char key[KEY_LEN_MAX];
	char *value;
	uint16_t len;
	nvram_status_t *ret;
}nvram_data_t;

typedef struct nvram_job_s{
    uint8_t cmd;
    nvram_data_t node;
    void *wait_sema;
    nvram_status_t ret;
} nvram_job_t;


extern void* nvramQGet(void);
extern void* nvramSemGet(int);
extern nvram_status_t nvram_handler_init(void);
extern void prvNvramTask( void *pvParameters );
extern int nvram_task_create(void);
extern int init_status_get(void);

#endif
