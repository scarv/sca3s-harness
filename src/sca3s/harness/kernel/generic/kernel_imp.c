/* Copyright (C) 2018 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#include "kernel_imp.h"

// ============================================================================

void kernel_id( char* x ) {
  strcpy( x, VERSION ":" KERNEL );
}

bool kernel_prologue();
bool kernel();
bool kernel_epilogue();

kernel_data_desc_t kernel_data_desc[] = {
  { NULL, NULL, 0, 0 }
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
