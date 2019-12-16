/* Copyright (C) 2018 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#ifndef __KERNEL_H
#define __KERNEL_H

#include "util.h"

typedef enum   {
  KERNEL_DATA_TYPE_I, KERNEL_DATA_TYPE_O, KERNEL_DATA_TYPE_IO
} kernel_data_type_t;

typedef struct {
  char* id; uint8_t* ptr; int size; kernel_data_type_t type;
} kernel_data_desc_t;

typedef struct {
  void (*kernel_id)( char* x );

  bool (*kernel_prologue)();
  bool (*kernel         )();
  bool (*kernel_epilogue)();
} kernel_func_desc_t;

extern kernel_data_desc_t kernel_data_desc[];
extern kernel_func_desc_t kernel_func_desc;

#endif
