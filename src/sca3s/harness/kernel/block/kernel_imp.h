/* Copyright (C) 2018 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#ifndef __KERNEL_IMP_H
#define __KERNEL_IMP_H

// ============================================================================

/** @brief      The kernel name, e.g., 
  *             - KERNEL_NAMEOF_GENERIC   for generic
  *             - KERNEL_NAMEOF_AES       for AES    
  *             - ...
  */

#if !defined( KERNEL_NAMEOF     )
#define KERNEL_NAMEOF     KERNEL_NAMEOF_GENERIC
#endif

/** @brief      The kernel mode, e.g.,
  *             - KERNEL_MODEOF_DEFAULT   for default
  *             - KERNEL_MODEOF_ENC       for encryption
  *             - KERNEL_MODEOF_DEC       for decryption
  *             - ...
  */

#if !defined( KERNEL_MODEOF     )
#define KERNEL_MODEOF     KERNEL_MODEOF_DEFAULT
#endif

// ----------------------------------------------------------------------------

/** @brief      Number of allocated bytes in the register    that contains the externally supplied randomness.
  */

#if !defined( KERNEL_SIZEOF_ESR )
#define KERNEL_SIZEOF_ESR  0
#endif

/** @brief      Number of allocated bytes in the register    that contains the cipher key.
  */

#if !defined( KERNEL_SIZEOF_K   )
#define KERNEL_SIZEOF_K   16
#endif

/** @brief      Number of allocated bytes in the register    that contains the  plaintext data.
  */

#if !defined( KERNEL_SIZEOF_M   )
#define KERNEL_SIZEOF_M   16
#endif

/** @brief      Number of allocated bytes in the register    that contains the ciphertext data.
  */

#if !defined( KERNEL_SIZEOF_C   )
#define KERNEL_SIZEOF_C   16
#endif

// ============================================================================

#endif
