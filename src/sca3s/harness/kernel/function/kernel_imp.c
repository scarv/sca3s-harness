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
  *             \c x, each element \c x[ i ] within which is of length \c n_x bytes (upto a maximum of \c KERNEL_SIZEOF_X).
  *
  * @note       The kernel output is:
  *             \c r, each element \c r[ i ] within which is of length \c n_r bytes (upto a maximum of \c KERNEL_SIZEOF_R).
  *
  * @note       The variable-length output
  *             requires that the kernel set
  *             \c n_r[ i ] (to reflect the number of bytes produced in \c r[ i ]).
  *
  * @note       The variable-length output and input
  *             cannot be supported in non-interactive cases: in such cases
  *             the outputs and inputs are assumed to be of maximum length,
  *             i.e.,
  *             \c x[ i ] is assumed to have length \c KERNEL_SIZEOF_X bytes,
  *             and
  *             \c r[ i ] is assumed to have length \c KERNEL_SIZEOF_R bytes.
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
