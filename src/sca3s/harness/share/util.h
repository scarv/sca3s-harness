/* Copyright (C) 2018 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#ifndef __UTIL_H
#define __UTIL_H

#include <stdbool.h>
#include  <stdint.h>
#include  <stdlib.h>

#include  <string.h>
#include   <ctype.h>

#define SIZEOF(x) ( sizeof(x)     )
#define BITSOF(x) ( sizeof(x) * 8 )

extern int  xtoi( char x );
extern char itox( int  x );

extern int strtobytes( uint8_t* r, int n_r, const char* x );
extern int bytestostr( char* r, const uint8_t* x, int n_x );

#endif
