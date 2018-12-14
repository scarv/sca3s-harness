/* Copyright (C) 2018 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#ifndef __DEVICE_H
#define __DEVICE_H

#include "util.h"

extern bool    device_init();

extern bool    device_trigger_rd(        );
extern void    device_trigger_wr( bool x );

extern uint8_t device_uart_rd(           );
extern void    device_uart_wr( uint8_t x );

#endif
