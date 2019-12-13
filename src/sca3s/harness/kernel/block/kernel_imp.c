/* Copyright (C) 2018 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#include "kernel_imp.h"

// ============================================================================

uint8_t k[ KERNEL_SIZEOF_KEY ];
uint8_t m[ KERNEL_SIZEOF_BLK ];
uint8_t c[ KERNEL_SIZEOF_BLK ];
uint8_t r[ KERNEL_SIZEOF_RND ];

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
  .kernel_prologue = kernel_prologue,
  .kernel          = kernel,
  .kernel_epilogue = kernel_epilogue
};

// ============================================================================

bool kernel_prologue() {
  return true;
}

bool kernel() {
  return true;
}

bool kernel_epilogue() {
  return true;
}

// ============================================================================
