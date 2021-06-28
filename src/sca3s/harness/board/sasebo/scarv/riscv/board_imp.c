/* Copyright (C) 2018 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#include "board_imp.h"

// ============================================================================

bool board_init() {
  return  true;
}

// ----------------------------------------------------------------------------

void board_trigger_wr( bool x ) {
         scarvsoc_gpio_wr( SCARVSOC_GPIO0, x );
}

bool board_trigger_rd() {
  return scarvsoc_gpio_rd( SCARVSOC_GPIO0    );
}

// ----------------------------------------------------------------------------

void    board_uart_wr( uint8_t x ) {
         scarvsoc_uart_putc_b( SCARVSOC_UART0, x );
}

uint8_t board_uart_rd() {
  return scarvsoc_uart_getc_b( SCARVSOC_UART0    );
}

// ----------------------------------------------------------------------------

void          board_cycle_wr( board_cycle_t x ) {

}

board_cycle_t board_cycle_rd() {
  uint64_t t, cycle_lo = 0, cycle_hi = 0;

  __asm__ __volatile__( "1: rdcycleh %0    ;"
                        "   rdcycle  %1    ;"
                        "   rdcycleh %2    ;"
                        "   bne %0, %2, 1b ;" : "=r" (t), "=r" (cycle_lo), "=r" (cycle_hi) );

  return ( ( board_cycle_t )( cycle_lo ) <<  0 ) |
         ( ( board_cycle_t )( cycle_hi ) << 32 ) ;
}

board_cycle_t board_cycle_diff( board_cycle_t x, board_cycle_t y ) {
  return x - y;
}

// ============================================================================
