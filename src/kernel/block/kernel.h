/* Copyright (C) 2018 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#ifndef __KERNEL_H
#define __KERNEL_H

#include "util.h"

#define KERNEL_SIZEOF_RND  0
#define KERNEL_SIZEOF_KEY 16
#define KERNEL_SIZEOF_BLK 16

extern void kernel_enc_init( uint8_t* k, uint8_t* r );
extern void kernel_dec_init( uint8_t* k, uint8_t* r );

extern void kernel_enc( uint8_t* c, uint8_t* m, uint8_t* k, uint8_t* r );
extern void kernel_dec( uint8_t* c, uint8_t* m, uint8_t* k, uint8_t* r );

#endif
