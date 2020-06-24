/* Copyright (C) 2018 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#include "board_imp.h"

bool     board_init() {
  return  true;
}

bool     board_trigger_rd(        ) {
  return false;
}

void     board_trigger_wr( bool x ) {
  if( x ) {
    bsp_trigger_enable();
  }
  else {
    bsp_trigger_unable();
  }
}

uint8_t  board_uart_rd(           ) {
  return 0;
}

void     board_uart_wr( uint8_t x ) {

}

uint64_t board_tsc() {
  return 0;
}

uint64_t board_tsc_diff( uint64_t x, uint64_t y ) {
  return 0;
}
