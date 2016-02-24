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
 
#ifndef __HAL_CACHE_INTERNAL_H__
#define __HAL_CACHE_INTERNAL_H__

#ifdef HAL_CACHE_MODULE_ENABLED


#ifdef __cplusplus
extern "C" {
#endif

typedef union {
    struct {
        uint32_t MCEN: 1;                       /**< bit 0 */
        uint32_t MPEN: 1;
        uint32_t CNTEN0: 1;
        uint32_t CNTEN1: 1;
        uint32_t MPDEFEN: 1;
        uint32_t _reserved0: 2;
        uint32_t MDRF: 1;
        uint32_t CACHESIZE: 2;
        uint32_t _reserved1: 22;
    } b;
    uint32_t w;
} CACHE_CON_Type;

typedef uint32_t CACHE_REGION_EN_Type;

typedef union {
    struct {
        uint32_t _reserved0: 5;                 /**< bit 0 */
        uint32_t ATTR: 3;
        uint32_t C: 1;
        uint32_t _reserved1: 3;
        uint32_t BASEADDR: 20;
    } b;
    uint32_t w;
} CACHE_ENTRY_N_Type;

typedef union {
    struct {
        uint32_t _reserved0: 12;
        uint32_t BASEADDR: 20;
    } b;
    uint32_t w;
} CACHE_END_ENTRY_N_Type;

typedef struct {
    CACHE_ENTRY_N_Type cache_entry_n;
    CACHE_END_ENTRY_N_Type cache_end_entry_n;
} CACHE_ENTRY_Type;


extern CACHE_CON_Type g_cache_con;
extern CACHE_REGION_EN_Type g_cache_region_en;
extern CACHE_ENTRY_Type g_cache_entry[HAL_CACHE_REGION_MAX];

#define MTK_CACHE_LINE_SIZE 		(32)        /**< CACHE line size is 8-word(32-byte) */

typedef enum {
    CACHE_INVALIDATE_ALL_LINES = 1,
    CACHE_INVALIDATE_ONE_LINE_BY_ADDRESS = 2,
    CACHE_INVALIDATE_ONE_LINE_BY_SET_WAY = 4,
    CACHE_FLUSH_ALL_LINES = 9,
    CACHE_FLUSH_ONE_LINE_BY_ADDRESS = 10,
    CACHE_FLUSH_ONE_LINE_BY_SET_WAY = 12
} cache_line_command_t;


#ifdef __cplusplus
}
#endif

#endif /* HAL_CACHE_MODULE_ENABLED */
#endif /* __HAL_CACHE_INTERNAL_H__ */

