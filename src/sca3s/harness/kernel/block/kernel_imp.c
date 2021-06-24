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

/** @brief      Execute the kernel prologue,
  *             e.g., any  pre-execution steps such as   allocation of memory.
  *
  * @return     an instance of \c kernel_fec_t, 
  *             e.g.,
  *             \c KERNEL_FEC_FAILURE to indicate failure
  *             or 
  *             \c KERNEL_FEC_SUCCESS to indicate success;
  *             this is captured in \c fec, the function exit code register.
  *
  * @note       Execution of this function is excluded from the trigger period.
  */

kernel_fec_t kernel_prologue() {
  return KERNEL_FEC_SUCCESS;
}

/** @brief      Execute the kernel itself.
  *
  * @return     an instance of \c kernel_fec_t, 
  *             e.g.,
  *             \c KERNEL_FEC_FAILURE to indicate failure
  *             or 
  *             \c KERNEL_FEC_SUCCESS to indicate success;
  *             this is captured in \c fec, the function exit code register.
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

kernel_fec_t kernel() {
  return KERNEL_FEC_SUCCESS;
}

/** @brief      Execute the kernel epilogue,
  *             e.g., any post-execution steps such as deallocation of memory.
  *
  * @return     an instance of \c kernel_fec_t, 
  *             e.g.,
  *             \c KERNEL_FEC_FAILURE to indicate failure
  *             or 
  *             \c KERNEL_FEC_SUCCESS to indicate success;
  *             this is captured in \c fec, the function exit code register.
  *
  * @note       Execution of this function is excluded from the trigger period.
  */

kernel_fec_t kernel_epilogue() {
  return KERNEL_FEC_SUCCESS;
}

// ============================================================================
