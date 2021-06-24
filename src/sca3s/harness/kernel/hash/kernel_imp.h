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
  *             1) KERNEL_NAMEOF_GENERIC   for generic
  *             2) KERNEL_NAMEOF_SHA_1     for SHA-1  
  *             3) KERNEL_NAMEOF_SHA_2_224 for SHA-224
  *             4) KERNEL_NAMEOF_SHA_2_256 for SHA-256
  *             5) KERNEL_NAMEOF_SHA_2_384 for SHA-384
  *             6) KERNEL_NAMEOF_SHA_2_512 for SHA-512
  *             7) ...
  */

#if !defined( KERNEL_NAMEOF     )
#define KERNEL_NAMEOF     ( KERNEL_NAMEOF_GENERIC )
#endif

// ----------------------------------------------------------------------------

/** @brief      Number of allocated bytes in register that contains the externally supplied randomness.
  */

#if !defined( KERNEL_SIZEOF_ESR )
#define KERNEL_SIZEOF_ESR (  0 )
#endif

/** @brief      Number of allocated bytes in register that contains the message.
  */

#if !defined( KERNEL_SIZEOF_M   )
#define KERNEL_SIZEOF_M   (  4 )
#endif

/** @brief      Number of allocated bytes in register that contains the  digest.
  */

#if !defined( KERNEL_SIZEOF_D   )
#define KERNEL_SIZEOF_D   (  4 )
#endif

// ============================================================================

#endif
