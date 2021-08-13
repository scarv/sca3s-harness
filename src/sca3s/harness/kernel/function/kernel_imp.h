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
  *             - ...
  */

#if !defined( KERNEL_NAMEOF     )
#define KERNEL_NAMEOF     ( KERNEL_NAMEOF_GENERIC )
#endif

/** @brief      The kernel mode, e.g.,
  *             - KERNEL_MODEOF_DEFAULT   for default
  *             - ...
  */

#if !defined( KERNEL_MODEOF     )
#define KERNEL_MODEOF     ( KERNEL_MODEOF_DEFAULT )
#endif

// ----------------------------------------------------------------------------

/** @brief      Number of allocated bytes in register that contains the externally supplied randomness.
  */

#if !defined( KERNEL_SIZEOF_ESR )
#define KERNEL_SIZEOF_ESR (  0 )
#endif

/** @brief      Number of allocated bytes in register that contains the  input to   r = f( x ).
  */

#if !defined( KERNEL_SIZEOF_X )
#define KERNEL_SIZEOF_X   (  4 )
#endif

/** @brief      Number of allocated bytes in register that contains the output from r = f( x ).
  */

#if !defined( KERNEL_SIZEOF_R )
#define KERNEL_SIZEOF_R   (  4 )
#endif

// ============================================================================

#endif
