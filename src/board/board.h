/* Copyright (C) 2018 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#ifndef __BOARD_H
#define __BOARD_H

#include "util.h"

extern bool     board_init();

extern bool     board_trigger_rd(        );
extern void     board_trigger_wr( bool x );

extern uint8_t  board_uart_rd(           );
extern void     board_uart_wr( uint8_t x );

extern uint64_t board_tsc();

extern uint64_t board_tsc_diff( uint64_t x, uint64_t y );

#endif
