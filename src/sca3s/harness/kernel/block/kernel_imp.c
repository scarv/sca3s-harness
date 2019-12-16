/* Copyright (C) 2018 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#include "kernel_imp.h"

// ============================================================================

/** @ingroup  block_boilerplate
  * @brief    A buffer that houses the randomness.
  */

uint8_t r[ KERNEL_SIZEOF_RND ];

/** @ingroup  block_boilerplate
  * @brief    A buffer that houses the cipher key.
  */

uint8_t k[ KERNEL_SIZEOF_KEY ];

/** @ingroup  block_boilerplate
  * @brief    A buffer that houses the  plaintext.
  */

uint8_t m[ KERNEL_SIZEOF_BLK ];

/** @ingroup  block_boilerplate
  * @brief    A buffer that houses the ciphertext.
  */

uint8_t c[ KERNEL_SIZEOF_BLK ];

void kernel_id( char* x ) {
#if   ( KERNEL_NAMEOF == KERNEL_NAMEOF_GENERIC )
#define __KERNEL_NAMEOF "generic"
#elif ( KERNEL_NAMEOF == KERNEL_NAMEOF_AES     )
#define __KERNEL_NAMEOF "aes"
#endif

#if   ( KERNEL_TYPEOF == KERNEL_TYPEOF_ENC     )
#define __KERNEL_TYPEOF "enc"
#elif ( KERNEL_TYPEOF == KERNEL_TYPEOF_DEC     )
#define __KERNEL_TYPEOF "dec"
#endif

  strcpy( x, VERSION ":" KERNEL ":" __KERNEL_NAMEOF "/" __KERNEL_TYPEOF );
}

bool kernel_prologue();
bool kernel();
bool kernel_epilogue();

kernel_data_desc_t kernel_data_desc[] = {
  {  "r",    r, SIZEOF( r ), KERNEL_DATA_TYPE_I },
  {  "k",    k, SIZEOF( k ), KERNEL_DATA_TYPE_I },
#if   ( KERNEL_TYPEOF == KERNEL_TYPEOF_ENC )
  {  "m",    m, SIZEOF( m ), KERNEL_DATA_TYPE_I },
  {  "c",    c, SIZEOF( c ), KERNEL_DATA_TYPE_O },
#elif ( KERNEL_TYPEOF == KERNEL_TYPEOF_DEC )
  {  "m",    m, SIZEOF( m ), KERNEL_DATA_TYPE_O },
  {  "c",    c, SIZEOF( c ), KERNEL_DATA_TYPE_I },
#endif
  { NULL, NULL,           0,                  0 }
};

kernel_func_desc_t kernel_func_desc   = {
  .kernel_id       = kernel_id,

  .kernel_prologue = kernel_prologue,
  .kernel          = kernel,
  .kernel_epilogue = kernel_epilogue
};

// ============================================================================

/** @ingroup  block_imp
  * @brief    Execute the kernel prologue.
  * 
  * @return a Boolean flag indicating success (true) or failure (false)
  */

bool kernel_prologue() {
  return true;
}

/** @ingroup  block_imp
  * @brief    Execute the kernel.
  * 
  * @return a Boolean flag indicating success (true) or failure (false)
  */

bool kernel() {
  return true;
}

/** @ingroup  block_imp
  * @brief    Execute the kernel epilogue.
  * 
  * @return a Boolean flag indicating success (true) or failure (false)
  */

bool kernel_epilogue() {
  return true;
}

// ============================================================================
