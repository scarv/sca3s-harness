/* Copyright (C) 2018 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#include "driver.h" 

driver_reg_desc_t* driver_reg = NULL;
driver_cmd_desc_t* driver_cmd = NULL;

char               driver_req[ 64 ];
char               driver_ack[ 64 ];

uint64_t           driver_tsc_init;
uint64_t           driver_tsc_fini;

driver_reg_desc_t* driver_reg_desc_find( char* hid ) {
  for( int i = 0; driver_reg[ i ].hid != NULL; i++ ) {    
    if( 0 == strcmp( hid, driver_reg[ i ].hid ) ) {
      return &driver_reg[ i ];
    }
  }

  return NULL;
}

driver_cmd_desc_t* driver_cmd_desc_find( char* hid ) {
  for( int i = 0; driver_cmd[ i ].hid != NULL; i++ ) {    
    if( 0 == strcmp( hid, driver_cmd[ i ].hid ) ) {
      return &driver_cmd[ i ];
    }
  }

  return NULL;
}

bool driver_reg_sizeof( char* ack, char* req[], int n ) {
  if( n == 1 ) {
    driver_reg_desc_t* f = driver_reg_desc_find( req[ 0 ] );

    if( NULL != f ) {
      *ack++ = itox( ( f->n >> 4 ) & 0xF );
      *ack++ = itox( ( f->n >> 0 ) & 0xF );

      *ack++ = '\x00'; return true;
    }
  }

  return false;
}

bool driver_reg_rd    ( char* ack, char* req[], int n ) {
  if( n == 1 ) {
    driver_reg_desc_t* f = driver_reg_desc_find( req[ 0 ] );

    if( NULL != f ) {
      return bytestostr( ack, f->ptr, f->n           ) == f->n;
    }
  }

  return false;
}

bool driver_reg_wr    ( char* ack, char* req[], int n ) {
  if( n == 2 ) {
    driver_reg_desc_t* f = driver_reg_desc_find( req[ 0 ] );

    if( NULL != f ) {
      return strtobytes(      f->ptr, f->n, req[ 1 ] ) == f->n;
    }
  }

  return false;
}

bool driver_tsc       ( char* ack, char* req[], int n ) {
  if( n == 0 ) {
    uint64_t tsc = board_tsc_diff( driver_tsc_init, 
                                   driver_tsc_fini );

    return bytestostr( ack, ( uint8_t* )( &tsc ), SIZEOF( tsc ) ) == SIZEOF( tsc );    
  }

  return false;
}

char* driver_rdln( char* x ) {
  char* p = x;

  while( true ) {
    *p = board_uart_rd();

    if( *p == '\x0D' ) {
      break;
    }
    
    p++;
  }

  *p = '\x00';

  return x;
}

char* driver_wrln( char* x ) {
  char* p = x;

  while( true ) {
    if( *p == '\x00' ) {
      break;
    }

    board_uart_wr( *p );

    p++;
  }

  board_uart_wr( '\x0D' );

  return x;
}

int driver( driver_reg_desc_t* __driver_reg,
            driver_cmd_desc_t* __driver_cmd ) {
  if( !board_init() ) {
    return -1;
  }

  driver_reg = __driver_reg;
  driver_cmd = __driver_cmd;

  while( true ) {
    char* cp[ 10 ] = { NULL }; int cn = 0;

    for( char* p = driver_rdln( driver_req ); true; p++ ) {
      if( cp[ cn ] == NULL ) {
        cp[ cn ] = p;
      }

      if( *p == '\x00' ) { //   eol
        cn++;       break;
      }
      if( *p == '\x20' ) { // space
        cn++; *p = '\x00';
      }
    }

    strcpy( driver_ack, "" );

    if( cn > 0 ) {
      driver_cmd_desc_t* f = driver_cmd_desc_find( cp[ 0 ] );

      if( f != NULL ) {
	if( f->ptr( driver_ack, cp + 1, cn - 1 ) ) {
          board_uart_wr( '+' ); driver_wrln( driver_ack );
        }
        else {
          board_uart_wr( '-' ); driver_wrln( driver_ack );
        }
      }
      else {
          board_uart_wr( '~' ); driver_wrln( driver_ack );
      }
    }
  }

  return 0;
}
