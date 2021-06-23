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
  *             \c k of length \c KERNEL_SIZEOF_K bytes,
  *             and
  *             either
  *             \c m of length \c KERNEL_SIZEOF_M bytes
  *             or 
  *             \c c of length \c KERNEL_SIZEOF_C bytes
  *             depending on the kernel mode.
  *
  * @note       The kernel output is:
  *             either
  *             \c c of length \c KERNEL_SIZEOF_C bytes
  *             or 
  *             \c m of length \c KERNEL_SIZEOF_M bytes
  *             depending on the kernel mode.
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
