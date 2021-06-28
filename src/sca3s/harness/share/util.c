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

int strtobytes( uint8_t* r, int n_r, const char* x ) {
  int n_x  = ( ( xtoi( *x++ ) & 0xF ) << 4 );
      n_x |= ( ( xtoi( *x++ ) & 0xF ) << 0 );

  if( n_x > n_r ) {
    return -1;
  }

  if( *x++ != ':' ) {
    return -1;
  }

  uint8_t t;

  for( int i = 0; i < n_x; i++ ) {
    r[ i ] = 0;

    if( ( t = *x++ ) != '\x00' ) {
      if( !isxdigit( t ) ) {
	break;
      }

      r[ i ] |= ( uint8_t )( xtoi( t ) & 0xF ) << 4;
    }
    if( ( t = *x++ ) != '\x00' ) {
      if( !isxdigit( t ) ) {
	break;
      }

      r[ i ] |= ( uint8_t )( xtoi( t ) & 0xF ) << 0;
    }
  }

  return n_x;
}

int bytestostr( char* r, const uint8_t* x, int n_x ) {
             *r++ = itox( ( n_x      >> 4 ) & 0xF );
             *r++ = itox( ( n_x      >> 0 ) & 0xF );

             *r++ = ':';

  for( int i = 0; i < n_x; i++ ) {
             *r++ = itox( (   x[ i ] >> 4 ) & 0xF );
             *r++ = itox( (   x[ i ] >> 0 ) & 0xF );
  }

             *r++ = '\x00';

  return n_x;
}

// ============================================================================
