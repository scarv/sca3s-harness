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

// ============================================================================

#define __INT(x)      #x
#define   INT(x) __INT(x)

#define __STR(x)      #x
#define   STR(x) __STR(x)

#define VERSION_MAJOR 0
#define VERSION_MINOR 1
#define VERSION_PATCH 0

#define VERSION       STR(VERSION_MAJOR) "." STR(VERSION_MINOR) "." STR(VERSION_PATCH)

// ----------------------------------------------------------------------------

#define SIZEOF(x) ( sizeof(x)     )
#define BITSOF(x) ( sizeof(x) * 8 )

#define SIZEOF_UINT8   1
#define SIZEOF_UINT16  2
#define SIZEOF_UINT32  4
#define SIZEOF_UINT64  8

#define BITSOF_UINT8   8
#define BITSOF_UINT16 16
#define BITSOF_UINT32 32
#define BITSOF_UINT64 64

// ----------------------------------------------------------------------------

extern int  xtoi( char x );
extern char itox( int  x );

extern int strtobytes( uint8_t* r, int n_r, const char* x );
extern int bytestostr( char* r, const uint8_t* x, int n_x );

// ============================================================================

#endif
