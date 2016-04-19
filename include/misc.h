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
 

#ifndef __MISC_H__
#define __MISC_H__


/* Sanity check the configuration. */
#define ALIGN_4BYTE(size)       (((size+3)/4) * 4)

#ifndef IS_ALIGN_4
#define IS_ALIGN_4(_value)          (((_value) & 0x3) ? FALSE : TRUE)
#define IS_NOT_ALIGN_4(_value)          (((_value) & 0x3) ? TRUE : FALSE)
#endif /* IS_ALIGN_4 */

#ifndef IS_NOT_ALIGN_4
#define IS_NOT_ALIGN_4(_value)          (((_value) & 0x3) ? TRUE : FALSE)
#endif /* IS_NOT_ALIGN_4 */

//---------------------------------------------------------------------------------------------------------------------------
/*! @function   BitArray
    @abstract   Macros for working with bit arrays.
    @discussion

    This treats bit numbers starting from the left so bit 0 is 0x80 in byte 0, bit 1 is 0x40 in bit 0,
    bit 8 is 0x80 in byte 1, etc. For example, the following ASCII art shows how the bits are arranged:

                                 1 1 1 1 1 1 1 1 1 1 2 2 2 2
    Bit      0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3
            +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
            |    x          |x              |  x           x| = 0x20 0x80 0x41 (bits 2, 8, 17, and 23).
            +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    Byte    0               1               2
*/
#define BIT_ARRAY_MIN_BYTES( ARRAY, N_BYTES )         os_memrlen( (ARRAY), (N_BYTES) )
#define BIT_ARRAY_MAX_BYTES( BITS )                   ( ( (BITS) + 7 ) / 8 )
#define BIT_ARRAY_MAX_BITS( ARRAY_BYTES )             ( (ARRAY_BYTES) * 8 )
#define BIT_ARRAY_CLEAR( ARRAY_PTR, ARRAY_BYTES )    os_memset( (ARRAY_PTR), 0, (ARRAY_BYTES) );
#define BIT_ARRAY_GET_BIT( PTR, LEN, BIT ) \
    ( ( (BIT) < BIT_ARRAY_MAX_BITS( (LEN) ) ) && ( (PTR)[ (BIT) / 8 ] & ( 1 << ( 7 - ( (BIT) & 7 ) ) ) ) )
#define BIT_ARRAY_SET_BIT( ARRAY, BIT )               ( (ARRAY)[ (BIT) / 8 ] |=  ( 1 << ( 7 - ( (BIT) & 7 ) ) ) )
#define BIT_ARRAY_CLEAR_BIT( ARRAY, BIT )             ( (ARRAY)[ (BIT) / 8 ] &= ~( 1 << ( 7 - ( (BIT) & 7 ) ) ) )

// ==== STRING SIZE UTILS ====
//---------------------------------------------------------------------------------------------------------------------------
/*! @defined    sizeof_string
    @abstract   Determines the size of a constant C string, excluding the null terminator.
*/
#define SIZEOF_STRING( X )      ( sizeof( ( X ) ) - 1 )

//---------------------------------------------------------------------------------------------------------------------------
/*! @defined    kSizeCString
    @abstract   Constant for describing the size of a null terminated string
*/
#define SIZE_C_STRING ( (size_t) -1 )

#define debug_print_assert(A,B,C,D,E,F, ...) printf("[WAC: %s:%s:%4d] **ASSERT** %s""\n", D ? D : "", F, E, C ? C : "", ##__VA_ARGS__)

//---------------------------------------------------------------------------------------------------------------------------
/*! @defined    require
    @abstract   Requires that an expression evaluate to true.
    @discussion
    
    If expression evalulates to false, this prints debugging information (actual expression string, file, line number, 
    function name, etc.) using the default debugging output method then jumps to a label.
*/

#if( !defined( require ) )
    #define require( X, LABEL )                                                                             \
        do                                                                                                  \
        {                                                                                                   \
            if( !(X) )                                                                          \
            {                                                                                               \
                debug_print_assert( 0, #X, NULL, __FILE__, __LINE__, __PRETTY_FUNCTION__ );                 \
                goto LABEL;                                                                                 \
            }                                                                                               \
                                                                                                            \
        }   while( 0 )
#endif

//---------------------------------------------------------------------------------------------------------------------------
/*! @defined    require_noerr_action_quiet
    @abstract   Require that an error code is noErr (0) with an action to execute otherwise.
    @discussion
    
    If the error code is non-0, this executes an action and jumps to a label. No debugging information is printed.
*/

#if( !defined( require_noerr_action_quiet ) )
    #define require_noerr_action_quiet( ERR, LABEL, ACTION )                                                \
        do                                                                                                  \
        {                                                                                                   \
            if( (ERR) != 0 )                                                                    \
            {                                                                                               \
                { ACTION; }                                                                                 \
                goto LABEL;                                                                                 \
            }                                                                                               \
                                                                                                            \
        }   while( 0 )
#endif

//---------------------------------------------------------------------------------------------------------------------------
/*! @defined    require_action
    @abstract   Requires that an expression evaluate to true with an action to execute otherwise.
    @discussion
    
    If expression evalulates to false, this prints debugging information (actual expression string, file, line number, 
    function name, etc.) using the default debugging output method then executes an action and jumps to a label.
*/

#if( !defined( require_action ) )
    #define require_action( X, LABEL, ACTION )                                                              \
        do                                                                                                  \
        {                                                                                                   \
            if( !(X) )                                                                          \
            {                                                                                               \
                debug_print_assert( 0, #X, NULL, __FILE__, __LINE__, __PRETTY_FUNCTION__ );                 \
                { ACTION; }                                                                                 \
                goto LABEL;                                                                                 \
            }                                                                                               \
                                                                                                            \
        }   while( 0 )
#endif


extern char * rstrtok(char * s,const char * ct);
extern void convert_string_to_hex_array(char *string, unsigned char *hex);
extern void hex_dump(char *str, unsigned char *pSrcBufVA, unsigned int SrcBufLen);
extern void hex_dump_limit_len(char *str, unsigned char *pSrcBufVA, unsigned int SrcBufLen, unsigned int limit_len);
extern char *uint64ToDecStr(uint64_t value);
extern void ignore_spaces_dash(char *pin_src, char *pin_dst);
#endif

