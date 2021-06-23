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
  * @return     a Boolean flag indicating success (\c true) or failure (\c false).
  *
  * @note       Execution of this function is excluded from the trigger period.
  */

bool kernel_prologue() {
  return true;
}

/** @brief      Execute the kernel itself.
  *
  * @return     a Boolean flag indicating success (\c true) or failure (\c false).
  *
  * @note       Execution of this function is included in   the trigger period.
  *
  * @note       The kernel  input is:
  *             \c m of length \c n_m bytes (upto a maximum of \c KERNEL_SIZEOF_M).
  *
  * @note       The kernel output is:
  *             \c d of length \c n_d bytes (upto a maximum of \c KERNEL_SIZEOF_D).
  *
  * @note       The variable-length output
  *             requires that the kernel set
  *             \c n_d (to reflect the number of bytes produced in \c d).
  *
  * @note       The variable-length output and input
  *             cannot be supported in non-interactive cases: in such cases
  *             the outputs and inputs are assumed to be of maximum length,
  *             i.e.,
  *             \c m is assumed to have length \c KERNEL_SIZEOF_M bytes,
  *             and
  *             \c d is assumed to have length \c KERNEL_SIZEOF_D bytes.
  */

bool kernel() {
  return true;
}

/** @brief      Execute the kernel epilogue, i.e.,
  *             any post-execution steps such as deallocation of memory.
  *
  * @return     a Boolean flag indicating success (\c true) or failure (\c false).
  *
  * @note       Execution of this function is excluded from the trigger period.
  */

bool kernel_epilogue() {
  return true;
}

// ============================================================================
