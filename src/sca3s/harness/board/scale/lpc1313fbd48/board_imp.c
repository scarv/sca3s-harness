/* Copyright (C) 2018 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#include "board_imp.h"

bool     board_init() {
  scale_conf_t scale_conf = {
    .clock_type        = SCALE_CLOCK_TYPE_EXT,
    .clock_freq_source = SCALE_CLOCK_FREQ_16MHZ,
    .clock_freq_target = SCALE_CLOCK_FREQ_16MHZ,

    .tsc               = true
  };

  return scale_init( &scale_conf );
}

bool     board_trigger_rd(        ) {
  return scale_gpio_rd( SCALE_GPIO_PIN_TRG    );
}

void     board_trigger_wr( bool x ) {
         scale_gpio_wr( SCALE_GPIO_PIN_TRG, x );
}

uint8_t  board_uart_rd(           ) {
  return scale_uart_rd( SCALE_UART_MODE_BLOCKING    );
}

void     board_uart_wr( uint8_t x ) {
         scale_uart_wr( SCALE_UART_MODE_BLOCKING, x );
}

uint64_t board_tsc() {
  return ( uint64_t )( scale_tsc() );
}

uint64_t board_tsc_diff( uint64_t x, uint64_t y ) {
  if( x >= y )  {
    return                               ( x - y );
  }
  else {
    #if defined( LPC13XX_SYSTICK_56BIT )
    return ( ( uint64_t )( 1 ) << 56 ) - ( y - x );
    #else
    return ( ( uint64_t )( 1 ) << 26 ) - ( y - x );
    #endif
  }
}
