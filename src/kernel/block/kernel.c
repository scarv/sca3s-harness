/* Copyright (C) 2018 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#include "kernel.h"

void kernel_enc_init( uint8_t* k, uint8_t* r ) {

}

void kernel_dec_init( uint8_t* k, uint8_t* r ) {

}

void kernel_enc( uint8_t* c, uint8_t* m, uint8_t* k, uint8_t* r ) {
  for( int i = 0; i < 16; i++ ) {
    c[ i ] = m[ i ] ^ k[ i ];
  }
}

void kernel_dec( uint8_t* c, uint8_t* m, uint8_t* k, uint8_t* r ) {

}
