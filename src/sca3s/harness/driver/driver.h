/* Copyright (C) 2018 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#ifndef __DRIVER_H
#define __DRIVER_H

#include   "util.h"
#include "kernel.h"
#include  "board.h"

typedef bool (*driver_command_t)( char* ack, char* req[], int n );

#define DRIVER_COMMAND(f) bool f( char* ack, char* req[], int n )

#define DRIVER_EXECUTE(x,f) {    \
  if( x ) {                      \
    board_trigger_wr(  true );   \
  }                              \
                                 \
  driver_tsc_init = board_tsc(); \
  bool r = f;                    \
  driver_tsc_fini = board_tsc(); \
                                 \
  if( x ) {                      \
    board_trigger_wr( false );   \
  }                              \
                                 \
  return r;                      \
}

#endif
