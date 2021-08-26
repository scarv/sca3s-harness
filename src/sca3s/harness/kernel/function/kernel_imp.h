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
#define KERNEL_NAMEOF     KERNEL_NAMEOF_GENERIC
#endif

/** @brief      The kernel mode, e.g.,
  *             - KERNEL_MODEOF_DEFAULT   for default
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

/** @brief      Number of allocated bytes in the register(s) that contains the  input to   r = f( x ).
  */

#if !defined( KERNEL_SIZEOF_X )
#define KERNEL_SIZEOF_X    4
#endif

/** @brief      Number of allocated bytes in the register(s) that contains the output from r = f( x ).
  */

#if !defined( KERNEL_SIZEOF_R )
#define KERNEL_SIZEOF_R    4
#endif

// ----------------------------------------------------------------------------

/** @brief      Number of elements in \c x, i.e., the number of  input registers (implying registers \c x[ 0 ] through to \c x[ KERNEL_ELEMOF_X - 1 ] are available), up to a maximum of 8 .
  */

#define KERNEL_ELEMOF_X    1

/** @brief      Number of elements in \c r, i.e., the number of output registers (implying registers \c r[ 0 ] through to \c r[ KERNEL_ELEMOF_R - 1 ] are available), up to a maximum of 8.
  */

#define KERNEL_ELEMOF_R    1

// ----------------------------------------------------------------------------

/** @brief      Type of the 0th  input register `x0` (represented concretly by `x[ 0 ]`) when available.
  */

#define KERNEL_TYPEOF_X0  KERNEL_DATA_TYPE_I

/** @brief      Type of the 1st  input register `x1` (represented concretly by `x[ 1 ]`) when available.
  */

#define KERNEL_TYPEOF_X1  KERNEL_DATA_TYPE_I

/** @brief      Type of the 2nd  input register `x2` (represented concretly by `x[ 2 ]`) when available.
  */

#define KERNEL_TYPEOF_X2  KERNEL_DATA_TYPE_I

/** @brief      Type of the 3rd  input register `x3` (represented concretly by `x[ 3 ]`) when available.
  */

#define KERNEL_TYPEOF_X3  KERNEL_DATA_TYPE_I

/** @brief      Type of the 4th  input register `x4` (represented concretly by `x[ 4 ]`) when available.
  */

#define KERNEL_TYPEOF_X4  KERNEL_DATA_TYPE_I

/** @brief      Type of the 5th  input register `x5` (represented concretly by `x[ 5 ]`) when available.
  */

#define KERNEL_TYPEOF_X5  KERNEL_DATA_TYPE_I

/** @brief      Type of the 6th  input register `x6` (represented concretly by `x[ 6 ]`) when available.
  */

#define KERNEL_TYPEOF_X6  KERNEL_DATA_TYPE_I

/** @brief      Type of the 7th  input register `x7` (represented concretly by `x[ 7 ]`) when available.
  */

#define KERNEL_TYPEOF_X7  KERNEL_DATA_TYPE_I

/** @brief      Type of the 0th output register `r0` (represented concretly by `r[ 0 ]`) when available.
  */

#define KERNEL_TYPEOF_R0  KERNEL_DATA_TYPE_O

/** @brief      Type of the 1st output register `r1` (represented concretly by `r[ 1 ]`) when available.
  */

#define KERNEL_TYPEOF_R1  KERNEL_DATA_TYPE_O

/** @brief      Type of the 2nd output register `r2` (represented concretly by `r[ 2 ]`) when available.
  */

#define KERNEL_TYPEOF_R2  KERNEL_DATA_TYPE_O

/** @brief      Type of the 3rd output register `r3` (represented concretly by `r[ 3 ]`) when available.
  */

#define KERNEL_TYPEOF_R3  KERNEL_DATA_TYPE_O

/** @brief      Type of the 4th output register `r4` (represented concretly by `r[ 4 ]`) when available.
  */

#define KERNEL_TYPEOF_R4  KERNEL_DATA_TYPE_O

/** @brief      Type of the 5th output register `r5` (represented concretly by `r[ 5 ]`) when available.
  */

#define KERNEL_TYPEOF_R5  KERNEL_DATA_TYPE_O

/** @brief      Type of the 6th output register `r6` (represented concretly by `r[ 6 ]`) when available.
  */

#define KERNEL_TYPEOF_R6  KERNEL_DATA_TYPE_O

/** @brief      Type of the 7th output register `r7` (represented concretly by `r[ 7 ]`) when available.
  */

#define KERNEL_TYPEOF_R7  KERNEL_DATA_TYPE_O

// ============================================================================

#endif
