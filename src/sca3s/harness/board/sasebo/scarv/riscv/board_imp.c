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
  return scarvsoc_gpio_rd( SCARVSOC_GPIO0    );
}

void     board_trigger_wr( bool x ) {
         scarvsoc_gpio_wr( SCARVSOC_GPIO0, x );
}

uint8_t  board_uart_rd(           ) {
  return scarvsoc_uart_getc_b( SCARVSOC_UART0    );
}

void     board_uart_wr( uint8_t x ) {
         scarvsoc_uart_putc_b( SCARVSOC_UART0, x );
}

uint64_t board_tsc() {
  uint32_t x;

  asm volatile( "rdcycle %0" : "=r" (x) );

  return ( uint64_t )( x );
}

uint64_t board_tsc_diff( uint64_t x, uint64_t y ) {
  return x - y;
}
