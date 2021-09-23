/* Copyright (C) 2018 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#ifndef __BOARD_H
#define __BOARD_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "util.h"

// ============================================================================

/** @brief      Initialise the board.
  *
  * @return       a flag indicating failure (\c false) or success (\c true).
  */

extern bool          board_init();

// ----------------------------------------------------------------------------

/** @brief      Write the trigger signal.
  *
  * @param[in]  x the value to write.
  */

extern void          board_trigger_wr( bool x );

/** @brief      Read  the trigger signal.
  *
  * @return       the value     read.
  */

extern bool          board_trigger_rd();

// ----------------------------------------------------------------------------

/** @brief      Write a byte to   the UART, 
  *             blocking until successful.
  *
  * @param[in]  x the value to write.
  */

extern void          board_uart_wr( uint8_t x );

/** @brief      Read  a byte from the UART, 
  *             blocking until successful.
  *
  * @return       the value     read.
  */

extern uint8_t       board_uart_rd();

// ----------------------------------------------------------------------------

/** @brief      A type to represent cycle counter values.
  */

typedef uint64_t board_cycle_t;

/** @brief      Write to   the cycle counter.
  *
  * @param[in]  \c x the value to write.
  */

extern void          board_cycle_wr( board_cycle_t x );

/** @brief      Read  from the cycle counter.
  *
  * @return          the value     read.
  */

extern board_cycle_t board_cycle_rd();

/** @brief      Compute the difference between two cycle counter values, and
  *             so allow details (e.g., ascending or descending mode) of the 
  *             cycle counter supported by a specific board to be abstracted.
  * 
  * @param[in]  \c x the cycle counter value sampled *before* execution of kernel.
  * @param[in]  \c y the cycle counter value sampled *after*  execution of kernel.
  *
  * @return     the (absolute) difference between \c x and \c y.
  */

extern board_cycle_t board_cycle_diff( board_cycle_t x, board_cycle_t y );

// ============================================================================

#endif
