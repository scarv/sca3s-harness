/* Copyright (C) 2018 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#include "kernel_imp.h"

#include "kernel_imp.h_harness"
#include "kernel_imp.c_harness"

// ============================================================================

/** @brief      Execute the kernel prologue, i.e.,
  *             any  pre-execution steps such as   allocation of memory.
  *
  * @return     a Boolean flag indicating success (\c true) or failure (\c false)
  *
  * @note       Execution of this function is excluded from the trigger period.
  */

bool kernel_prologue() {
  return true;
}

/** @brief      Execute the kernel itself.
  *
  * @return     a Boolean flag indicating success (\c true) or failure (\c false)
  *
  * @note       Execution of this function is included in   the trigger period.
  * @note       The  inputs are:
  *             \c x of length \c n_x bytes (upto a maximum of \c KERNEL_SIZEOF_X).
  *             The outputs are:
  *             \c r of length \c n_r bytes (upto a maximum of \c KERNEL_SIZEOF_R).
  *             As such, the function should
  *             consume and process \c n_x bytes in \c x, 
  *             then 
  *             set \c n_r to reflect the number of bytes produced in \c r.
  * @note       The variable length input and output behaviour outlined above
  *             cannot be supported in non-interactive cases.  In such cases,
  *             the inputs and outputs are assumed to be maximum length: 
  *             \c x is assumed to have length \c KERNEL_SIZEOF_X,
  *             and
  *             \c r is assumed to have length \c KERNEL_SIZEOF_R.
  */

bool kernel() {
  return true;
}

/** @brief      Execute the kernel epilogue, i.e.,
  *             any post-execution steps such as deallocation of memory.
  *
  * @return     a Boolean flag indicating success (\c true) or failure (\c false)
  *
  * @note       Execution of this function is excluded from the trigger period.
  */

bool kernel_epilogue() {
  return true;
}

// ============================================================================
