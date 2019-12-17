/* Copyright (C) 2018 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#include "kernel_imp.h"

// ============================================================================

/** @ingroup    generic_specific
  * @brief      Generate a kernel identifier string.
  *
  * @param[out] x a (pointer to a) buffer into which the identifier string is copied
  *
  * @note       By convention, the identifier string constitutes a sequence 
  *             of colon-separated fields; to allow the string to be parsed, 
  *             the first two fields must be \c VERSION and \c KERNEL.
  */

void kernel_id( char* x ) {
  strcpy( x, VERSION ":" KERNEL );
}

bool kernel_prologue();
bool kernel();
bool kernel_epilogue();

kernel_data_spec_t kernel_data_spec[] = {
  { .id = NULL, .ptr = NULL, .size = 0, .type = 0 } 
};

/** @ingroup    generic_specific
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

/** @ingroup    generic_specific
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

/** @ingroup    generic_specific
  * @brief      Execute the kernel itself.
  *
  * @return     a Boolean flag indicating success (\c true) or failure (\c false)
  *
  * @note       Execution of this function is excluded from the trigger period.
  */

bool kernel() {
  return true;
}

/** @ingroup    generic_specific
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
