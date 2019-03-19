/* Copyright (C) 2018 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#ifndef __DRIVER_H
#define __DRIVER_H

#include "util.h"

#include "board.h"
#include "kernel.h"

typedef struct {
  char* hid; uint8_t* ptr; int n;
} driver_reg_desc_t;

typedef struct {
  char* hid; bool (*ptr)( char* ack, char* req[], int n );
} driver_cmd_desc_t;

extern uint64_t driver_tsc_init;
extern uint64_t driver_tsc_fini;

extern bool driver_tsc       ( char* ack, char* req[], int n );

extern bool driver_reg_sizeof( char* ack, char* req[], int n );
extern bool driver_reg_rd    ( char* ack, char* req[], int n );
extern bool driver_reg_wr    ( char* ack, char* req[], int n );

extern int  driver( driver_reg_desc_t* __driver_reg,
                    driver_cmd_desc_t* __driver_cmd );

#endif
