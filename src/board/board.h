/* Copyright (C) 2018 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#ifndef __BOARD_H
#define __BOARD_H

#include "util.h"

/** @brief Initialise the board.
  *
  * @return       a flag indicating success (true) or failure (false) of the initialisation process
  */

extern bool     board_init();

/** @brief Read  the trigger signal.
  *
  * @return       the byte    read
  */

extern bool     board_trigger_rd(        );

/** @brief Write the trigger signal.
  *
  * @param[in]  x the byte    read
  */

extern void     board_trigger_wr( bool x );

/** @brief Read  a byte from the UART, 
  *        blocking until successful.
  *
  * @return       the byte    read
  */

extern uint8_t  board_uart_rd(           );

/** @brief Write a byte to   the UART, 
  *        blocking until successful.
  *
  * @param[in]  x the byte to write
  */

extern void     board_uart_wr( uint8_t x );

/** @brief Sample the TimeStamp Counter (TSC).
  *
  * @return       a TSC value
  */

extern uint64_t board_tsc();

/** @brief Compute the difference between two TSC values, allowing to
  *        abstract detail (e.g., an ascending or descending mode) of
  *        the TSC supported by a specific board.
  * 
  * @param[in]  x a TSC value sampled *before* execution of kernel
  * @param[in]  y a TSC value sampled *after*  execution of kernel
  * @return       the (absolute) difference between x and y
  */

extern uint64_t board_tsc_diff( uint64_t x, uint64_t y );

#endif
