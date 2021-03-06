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
 

#ifndef __HAL_EFUSE_H__
#define __HAL_EFUSE_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @file hal_efuse.h
 *
 * @brief see sys_efuse.c in DVT tree.
 */

#define HAL_EFUSE_WRITE_MAGIC (0x3735929054)

typedef enum
{
    HAL_EFUSE_OK,
    HAL_EFUSE_INVALID_PARAMETER,
    HAL_EFUSE_INVALID_MAGIC,
    HAL_EFUSE_INVALID_ACCESS
} hal_efuse_status_t;


/**
 * Write data into eFuse.
 *
 * Write <i>len</i> bytes of data in buffer <i>buf</i> into eFuse at the
 * specified address <i>addr</i>.
 *
 * @param addr  address to write to.
 * @param buf   the data sequence to be write into eFuse.
 * @param len   the length of the date.
 *
 * @retval HAL_EFUSE_OK if write succeeded.
 * @retval HAL_EFUSE_INVALID_PARAMETER buf is incorrect, address is not supported,
 *         or length is not supported.
 * @retval HAL_EFUSE_INVALID_MAGIC the magic is wrong.
 *
 * @note On MT7687, eFuse write/read unit is 16 bytes aligned, and 16 bytes
 *       date is required to be written into flash.
 */
hal_efuse_status_t hal_efuse_write(uint32_t magic, uint16_t addr, const uint8_t *buf, uint8_t len);


/**
 * Read data from eFuse.
 *
 * Read <i>len</i> bytes of data from specified address <i>addr</i> in eFuse
 * into buffer <i>buf</i>.
 *
 * @param addr  address to read from.
 * @param buf   keep the read data sequence into this buffer.
 * @param len   the length of the date.
 *
 * @retval HAL_EFUSE_OK if read succeeded.
 * @retval HAL_EFUSE_INVALID_PARAMETER buf is incorrect, address is not supported,
 *         or length is not supported.
 *
 * @note On MT7687, eFuse write/read unit is 16 bytes aligned, and 16 bytes
 *       date is required to be written into flash.

 */
hal_efuse_status_t hal_efuse_read(uint16_t addr, uint8_t *buf, uint8_t len);


#ifdef __cplusplus
}
#endif

#endif /* __HAL_EFUSE_H__ */

