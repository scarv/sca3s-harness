/* Copyright (C) 2018 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#include "util.h"

// ============================================================================

int  xtoi( char x ) {
  if      ( x >= '0' && x <= '9' ) {
    return ( ( int )( x ) - ( int )( '0' )      );
  }
  else if ( x >= 'a' && x <= 'f' ) {
    return ( ( int )( x ) - ( int )( 'a' ) + 10 );
  }
  else if ( x >= 'A' && x <= 'F' ) {
    return ( ( int )( x ) - ( int )( 'A' ) + 10 );
  }

  return -1;
}

char itox( int  x ) {
  if     ( x >=  0 && x <=  9 ) {
    return ( char )( ( int )( '0' ) + x       );
  }
  else if( x >= 10 && x <= 15 ) {
    return ( char )( ( int )( 'A' ) + x - 10  );
  }

  return '?';
}

// ----------------------------------------------------------------------------

len_t strtobytes( uint8_t* r, len_t n_r, const char* x ) {
  uint8_t t; len_t n_t = sizeof( len_t ), n_x = 0; 

  #define PARSE(c,s) {            \
    if( !isxdigit( t = *x++ ) ) { \
      if( t == c ) {              \
        break;                    \
      }                           \
      else {                      \
        return -1;                \
      }                           \
    }                             \
    else {                        \
      s;                          \
    }                             \
  }

  for( int i = 0; i < n_t; i++ ) {
    PARSE( '\x3A', n_x      |= ( uint8_t )( xtoi( t ) & 0xF ) << ( 4 + ( 8 * i ) ) );
    PARSE( '\x3A', n_x      |= ( uint8_t )( xtoi( t ) & 0xF ) << ( 0 + ( 8 * i ) ) );
  }

  if( n_x > n_r ) {
    return -1;
  }

  for( int i = 0; i < n_x; i++ ) {
    r[ i ] = 0;

    PARSE( '\x00',   r[ i ] |= ( uint8_t )( xtoi( t ) & 0xF ) << ( 4             ) );
    PARSE( '\x00',   r[ i ] |= ( uint8_t )( xtoi( t ) & 0xF ) << ( 0             ) );
  }

  if( *x != '\x00' ) {
    return -1;
  }

  #undef  PARSE

  return n_x;
}

len_t bytestostr( char* r, const uint8_t* x, len_t n_x ) {
  uint8_t t; len_t n_t = sizeof( len_t );

  while( n_t > 0 ) {
    if( n_x & ( 0xFF << ( 8 * ( n_t - 1 ) ) ) ) {
      break;
    }

    n_t--;
  }

  for( int i = 0; i < n_t; i++ ) {
    *r++ = itox( ( n_x      >> ( 4 + ( 8 * i ) ) ) & 0xF );
    *r++ = itox( ( n_x      >> ( 0 + ( 8 * i ) ) ) & 0xF );
  }

    *r++ = '\x3A';

  for( int i = 0; i < n_x; i++ ) {
    *r++ = itox( (   x[ i ] >> ( 4             ) ) & 0xF );
    *r++ = itox( (   x[ i ] >> ( 0             ) ) & 0xF );
  }

    *r++ = '\x00';

  return n_x;
}

// ============================================================================
