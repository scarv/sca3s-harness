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
  *             \c k of length \c n_k bytes (upto a maximum of \c KERNEL_SIZEOF_K),
  *             \c n of length \c n_n bytes (upto a maximum of \c KERNEL_SIZEOF_N),
  *             \c a of length \c n_a bytes (upto a maximum of \c KERNEL_SIZEOF_A),
  *             and 
  *             either
  *             \c m of length \c n_m bytes (upto a maximum of \c KERNEL_SIZEOF_M)
  *             or
  *             \c c of length \c n_c bytes (upto a maximum of \c KERNEL_SIZEOF_C)
  *             depending on the kernel mode.
  *
  * @note       The kernel output is:
  *             either
  *             \c c of length \c n_c bytes (upto a maximum of \c KERNEL_SIZEOF_C)
  *             or
  *             \c m of length \c n_m bytes (upto a maximum of \c KERNEL_SIZEOF_M)
  *             depending on the kernel mode.
  *
  * @note       The variable-length output
  *             requires that the kernel set
  *             either
  *             \c n_c (to reflect the number of bytes produced in \c c)
  *             or
  *             \c n_m (to reflect the number of bytes produced in \c m)
  *             depending on the kernel mode.
  *
  * @note       The variable-length output and input
  *             cannot be supported in non-interactive cases: in such cases
  *             the outputs and inputs are assumed to be of maximum length, 
  *             i.e.,
  *             \c k is assumed to have length \c KERNEL_SIZEOF_K bytes,
  *             \c n is assumed to have length \c KERNEL_SIZEOF_N bytes,
  *             \c a is assumed to have length \c KERNEL_SIZEOF_A bytes,
  *             \c m is assumed to have length \c KERNEL_SIZEOF_M bytes,
  *             and
  *             \c c is assumed to have length \c KERNEL_SIZEOF_C bytes.
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
