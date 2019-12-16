/* Copyright (C) 2018 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#ifndef __KERNEL_IMP_H
#define __KERNEL_IMP_H

#include   "util.h"
#include "kernel.h"

// ============================================================================

/** \defgroup block_boilerplate
  * \defgroup block_imp
  */

/** @ingroup  block_boilerplate
  * @brief    An identifier for generic block cipher.
  */

#define KERNEL_NAMEOF_GENERIC ( 0 )

/** @ingroup  block_boilerplate
  * @brief    An identifier for AES     block cipher.
  */

#define KERNEL_NAMEOF_AES     ( 1 )

/** @ingroup  block_boilerplate
  * @brief    An identifier for encryption operation.
  */

#define KERNEL_MODEOF_ENC     ( 0 )

/** @ingroup  block_boilerplate
  * @brief    An identifier for decryption operation.
  */

#define KERNEL_MODEOF_DEC     ( 1 )

// ============================================================================

/** @ingroup  block_imp
  * @brief    The kernel name, e.g., 
  *           1) KERNEL_NAMEOF_GENERIC, for generic block cipher,
  *           2) KERNEL_NAMEOF_AES,     for AES     block cipher,
  *           3) ...
  */

#define KERNEL_NAMEOF     KERNEL_NAMEOF_GENERIC

/** @ingroup  block_imp
  * @brief    The kernel type, i.e., either
  *           1) KERNEL_MODEOF_ENC for encryption operation,
  *              or
  *           2) KERNEL_MODEOF_DEC for decryption operation.
  */

#define KERNEL_MODEOF     KERNEL_MODEOF_ENC

/** @ingroup  block_imp
  * @brief    Number of bytes of externally supplied randomness.
  */

#define KERNEL_SIZEOF_RND (  0 )

/** @ingroup  block_imp
  * @brief    Number of bytes in a cipher key.
  */

#define KERNEL_SIZEOF_KEY ( 16 )

/** @ingroup  block_imp
  * @brief    Number of bytes in a plaintext or ciphertext block.
  */

#define KERNEL_SIZEOF_BLK ( 16 )

// ============================================================================

#endif
