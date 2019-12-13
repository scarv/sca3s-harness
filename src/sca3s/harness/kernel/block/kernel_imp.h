/* Copyright (C) 2018 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#ifndef __KERNEL_IMP_H
#define __KERNEL_IMP_H

#include "util.h"

#include "kernel.h"
#include "kernel_imp.h"

// ============================================================================

/** @brief The kernel name, e.g., 
  *        1) generic, for generic (or unknown) block cipher,
  *        2)     aes, for AES                  block cipher,
  *        3) ...
  */

#define KERNEL_NAMEOF     "generic"

/** @brief The kernel type, i.e., either
  *        1) KERNEL_TYPEOF_ENC for encryption,
  *           or
  *        2) KERNEL_TYPEOF_DEC for decryption.
  */

#define KERNEL_TYPEOF_ENC ( 0 )
#define KERNEL_TYPEOF_DEC ( 1 )

#define KERNEL_TYPEOF     KERNEL_TYPEOF_ENC

/** @brief Number of bytes of externally supplied randomness.
  */

#define KERNEL_SIZEOF_RND (  0 )

/** @brief Number of bytes in a cipher key.
  */

#define KERNEL_SIZEOF_KEY ( 16 )

/** @brief Number of bytes in a plaintext or ciphertext block.
  */

#define KERNEL_SIZEOF_BLK ( 16 )

// ============================================================================

#if   ( KERNEL_TYPEOF == KERNEL_TYPEOF_ENC )
#define KERNEL_ID KERNEL_NAMEOF "/" "enc"
#elif ( KERNEL_TYPEOF == KERNEL_TYPEOF_DEC )
#define KERNEL_ID KERNEL_NAMEOF "/" "dec"
#endif

extern kernel_data_desc_t kernel_data_desc[];
extern kernel_func_desc_t kernel_func_desc;

extern bool kernel_prologue();
extern bool kernel();
extern bool kernel_epilogue();

// ============================================================================

#endif
