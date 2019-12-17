/* Copyright (C) 2018 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#include "kernel_imp.h"

// ============================================================================

/** @ingroup    block_agnostic
  * @brief      A data buffer that houses the (externally supplied) randomness.
  */

uint8_t r[ KERNEL_SIZEOF_RND ];

/** @ingroup    block_agnostic
  * @brief      A data buffer that houses the cipher key.
  */

uint8_t k[ KERNEL_SIZEOF_KEY ];

/** @ingroup    block_agnostic
  * @brief      A data buffer that houses the  plaintext.
  */

uint8_t m[ KERNEL_SIZEOF_BLK ];

/** @ingroup    block_agnostic
  * @brief      A data buffer that houses the ciphertext.
  */

uint8_t c[ KERNEL_SIZEOF_BLK ];

/** @ingroup    block_agnostic
  * @brief      Generate a kernel identifier string.
  *
  * @param[out] x a (pointer to a) buffer into which the identifier string is copied
  *
  * @note       By convention, the identifier string constitutes a sequence 
  *             of colon-separated fields; to allow the string to be parsed, 
  *             the first two fields must be \c VERSION and \c KERNEL.
  */

void kernel_id( char* x ) {
#if   ( KERNEL_NAMEOF == KERNEL_NAMEOF_GENERIC )
#define __KERNEL_NAMEOF "generic"
#elif ( KERNEL_NAMEOF == KERNEL_NAMEOF_AES     )
#define __KERNEL_NAMEOF "aes"
#endif

#if   ( KERNEL_MODEOF == KERNEL_MODEOF_ENC     )
#define __KERNEL_MODEOF "enc"
#elif ( KERNEL_MODEOF == KERNEL_MODEOF_DEC     )
#define __KERNEL_MODEOF "dec"
#endif

  strcpy( x, VERSION ":" KERNEL ":" __KERNEL_NAMEOF "/" __KERNEL_MODEOF );
}

bool kernel_prologue();
bool kernel();
bool kernel_epilogue();

/** @ingroup    block_agnostic
  * @brief      A specification of the
  *             data buffers
  *             accessible within the kernel.
  *
  * @note       By setting \c .id equal to \c NULL, the entry will act as a
  *             terminator for the array; such a terminator entry must exist
  *             as the final entry.
  */

kernel_data_spec_t kernel_data_spec[] = {
  { .id =  "r", .ptr =    r, .size = SIZEOF( r ), .type = KERNEL_DATA_TYPE_I },
  { .id =  "k", .ptr =    k, .size = SIZEOF( k ), .type = KERNEL_DATA_TYPE_I },
#if   ( KERNEL_MODEOF == KERNEL_MODEOF_ENC )
  { .id =  "m", .ptr =    m, .size = SIZEOF( m ), .type = KERNEL_DATA_TYPE_I },
  { .id =  "c", .ptr =    c, .size = SIZEOF( c ), .type = KERNEL_DATA_TYPE_O },
#elif ( KERNEL_MODEOF == KERNEL_MODEOF_DEC )
  { .id =  "m", .ptr =    m, .size = SIZEOF( m ), .type = KERNEL_DATA_TYPE_O },
  { .id =  "c", .ptr =    c, .size = SIZEOF( c ), .type = KERNEL_DATA_TYPE_I },
#endif
  { .id = NULL, .ptr = NULL, .size =           0, .type =                  0 }
};

/** @ingroup    block_agnostic
  * @brief      A specification of the
  *             functions
  *             accessible within the kernel.
  */

kernel_func_spec_t kernel_func_spec   = {
  .kernel_id       = kernel_id,

  .kernel_prologue = kernel_prologue,
  .kernel          = kernel,
  .kernel_epilogue = kernel_epilogue
};

// ============================================================================

/** @ingroup    block_specific
  * @brief      Execute the kernel prologue, i.e.,
  *             any  pre-execution steps such as   allocation of memory.
  *
  * @return     a Boolean flag indicating success (\c true) or failure (\c false)
  *
  * @note       Execution of this function is excluded from the trigger period.
  */

bool kernel_prologue() {
  return true;
}

/** @ingroup    block_specific
  * @brief      Execute the kernel itself.
  *
  * @return     a Boolean flag indicating success (\c true) or failure (\c false)
  *
  * @note       Execution of this function is excluded from the trigger period.
  */

bool kernel() {
  return true;
}

/** @ingroup    block_specific
  * @brief      Execute the kernel epilogue, i.e.,
  *             any post-execution steps such as deallocation of memory.
  *
  * @return     a Boolean flag indicating success (\c true) or failure (\c false)
  *
  * @note       Execution of this function is excluded from the trigger period.
  */

bool kernel_epilogue() {
  return true;
}

// ============================================================================
