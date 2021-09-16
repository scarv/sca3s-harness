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

// ============================================================================

typedef bool (*driver_command_t)( char* ack, char* req[], int n );

#define DRIVER_COMMAND(f) bool f( char* ack, char* req[], int n )

#define DRIVER_EXECUTE(f) {                                       \
  board_trigger_wr(  true );                                      \
  board_cycle_t board_cycle_x = board_cycle_rd();                 \
  *driver_fec = f;                                                \
  board_cycle_t board_cycle_y = board_cycle_rd();                 \
  board_trigger_wr( false );                                      \
                                                                  \
  *driver_fcc = board_cycle_diff( board_cycle_x, board_cycle_y ); \
}

// ============================================================================

#endif
