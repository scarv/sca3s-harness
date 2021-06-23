/* Copyright (C) 2018 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#ifndef __KERNEL_H
#define __KERNEL_H

#include "util.h"

typedef uint8_t kernel_status_t;

#define KERNEL_STATUS_FAILURE ( 0 )
#define KERNEL_STATUS_SUCCESS ( 1 )

typedef enum   {
  KERNEL_DATA_TYPE_NONE, KERNEL_DATA_TYPE_I, KERNEL_DATA_TYPE_O, KERNEL_DATA_TYPE_IO
} kernel_data_type_t;

typedef struct {
  char* id; uint8_t* data; uint8_t* used; uint8_t size; kernel_data_type_t type;
} kernel_data_spec_t;

typedef struct {
  void            (*kernel_id)( char* x );

  kernel_status_t (*kernel_prologue)();
  kernel_status_t (*kernel         )();
  kernel_status_t (*kernel_epilogue)();
} kernel_func_spec_t;

extern           uint64_t kernel_tsc;

extern kernel_data_spec_t kernel_data_spec[];
extern kernel_func_spec_t kernel_func_spec;

#endif
