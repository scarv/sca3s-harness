/* Copyright (C) 2018 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#include "driver_imp.h"

uint8_t reg_k[ KERNEL_SIZEOF_KEY ];
uint8_t reg_r[ KERNEL_SIZEOF_RND ];
uint8_t reg_m[ KERNEL_SIZEOF_BLK ];
uint8_t reg_c[ KERNEL_SIZEOF_BLK ];

#define WRAPPER(f,x)                        \
  bool f( char* ack, char* req[], int n ) { \
    if( n == 0 ) {                          \
      x return true;                        \
    }                                       \
                                            \
    return false;                           \
  }

#define TRIGGER(  x)          \
  device_trigger_wr(  true ); \
  x                           \
  device_trigger_wr( false ); 

WRAPPER( driver_id,       strcpy( ack, DRIVER_TYPE ":" DRIVER_VERSION ":" STR(KERNEL_SIZEOF_RND) "," STR(KERNEL_SIZEOF_KEY) "," STR(KERNEL_SIZEOF_BLK) ); )

WRAPPER( driver_enc_init,          kernel_enc_init(               reg_k, reg_r );   )
WRAPPER( driver_dec_init,          kernel_dec_init(               reg_k, reg_r );   )
WRAPPER( driver_enc,      TRIGGER( kernel_enc     ( reg_c, reg_m, reg_k, reg_r ); ) )
WRAPPER( driver_dec,      TRIGGER( kernel_dec     ( reg_m, reg_c, reg_k, reg_r ); ) )

int main( int argc, char* argv[] ) {
  driver_reg_desc_t reg_desc[] = { 
    { .hid = "k",           .ptr = reg_k, .n = sizeof( reg_k ) },
    { .hid = "r",           .ptr = reg_r, .n = sizeof( reg_r ) },
    { .hid = "m",           .ptr = reg_m, .n = sizeof( reg_m ) },
    { .hid = "c",           .ptr = reg_c, .n = sizeof( reg_c ) },
     
    { .hid = NULL                                              } 
  };
          
  driver_cmd_desc_t cmd_desc[] = { 
    { .hid = "?reg",      .ptr = &driver_reg_sizeof            },
    { .hid = "<reg",      .ptr = &driver_reg_rd                },
    { .hid = ">reg",      .ptr = &driver_reg_wr                },

    { .hid = "?id",       .ptr = &driver_id                    },

    { .hid = "!enc_init", .ptr = &driver_enc_init              },
    { .hid = "!dec_init", .ptr = &driver_dec_init              },
    { .hid = "!enc",      .ptr = &driver_enc                   },
    { .hid = "!dec",      .ptr = &driver_dec                   },
  
    { .hid = NULL                                              }
  } ;

  return driver( reg_desc, cmd_desc );
}
