/* Copyright (C) 2018 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#include "driver.h" 

char     driver_req[ 64 ];
char     driver_ack[ 64 ];

uint64_t driver_tsc_init;
uint64_t driver_tsc_fini;

DRIVER_COMMAND(driver_data_sizeof    ) {
  if( n == 1 ) {
    for( kernel_data_desc_t* desc = kernel_data_desc; desc->id != NULL; desc++ ) {    
      if( 0 == strcmp( desc->id, req[ 0 ] ) ) {
        uint32_t x = desc->size;

        return bytestostr( ack, ( uint8_t* )( &x ), SIZEOF( x ) ) == SIZEOF( x );
      }
    }
  }

  return false;
}

DRIVER_COMMAND(driver_data_rd        ) {
  if( n == 1 ) {
    if( 0 == strcmp( "tsc", req[ 0 ] ) ) {
        uint64_t x = board_tsc_diff( driver_tsc_init, 
                                     driver_tsc_fini );

        return bytestostr( ack, ( uint8_t* )( &x ), SIZEOF( x ) ) == SIZEOF( x );
    }
    else {
      for( kernel_data_desc_t* desc = kernel_data_desc; desc->id != NULL; desc++ ) {    
        if( 0 == strcmp( desc->id, req[ 0 ] ) ) {
          return bytestostr( ack, desc->ptr, desc->size           ) == desc->size;
        }
      }
    }
  }

  return false;
}

DRIVER_COMMAND(driver_data_wr         ) {
  if( n == 2 ) {
    if( 0 == strcmp( "tsc", req[ 0 ] ) ) {

    }
    else {
      for( kernel_data_desc_t* desc = kernel_data_desc; desc->id != NULL; desc++ ) {    
        if( 0 == strcmp( desc->id, req[ 0 ] ) ) {
          return strtobytes(      desc->ptr, desc->size, req[ 1 ] ) == desc->size;
        }
      }
    }
  }

  return false;
}

DRIVER_COMMAND(driver_kernel_id      ) {
  if( n == 0 ) {
    kernel_func_desc.kernel_id( ack ); return true;
  }

  return false;
}

#include <stdio.h>

DRIVER_COMMAND(driver_kernel_data    ) {
  if( n == 1 ) {
    bool f = false;

    for( kernel_data_desc_t* desc = kernel_data_desc; desc->id != NULL; desc++ ) {    
      if     ( ( req[ 0 ][ 0 ] == '<' ) && ( ( desc->type == KERNEL_DATA_TYPE_I ) || ( desc->type == KERNEL_DATA_TYPE_IO ) ) ) {
        if( f ) { strcat( ack, "," ); } strcat( ack, desc->id ); f = true;
      }
      else if( ( req[ 0 ][ 0 ] == '>' ) && ( ( desc->type == KERNEL_DATA_TYPE_O ) || ( desc->type == KERNEL_DATA_TYPE_IO ) ) ) {
        if( f ) { strcat( ack, "," ); } strcat( ack, desc->id ); f = true;
      }
    }

    return true;
  }

  return false;
}

DRIVER_COMMAND(driver_kernel_prologue) {
  if( n == 0 ) {
    DRIVER_EXECUTE( false, kernel_func_desc.kernel_prologue() );
  }

  return false;
}

DRIVER_COMMAND(driver_kernel         ) {
  if( n == 0 ) {
    DRIVER_EXECUTE(  true, kernel_func_desc.kernel()          );
  }

  return false;
}

DRIVER_COMMAND(driver_kernel_epilogue) {
  if( n == 0 ) {
    DRIVER_EXECUTE( false, kernel_func_desc.kernel_epilogue() );
  }

  return false;
}

DRIVER_COMMAND(driver_nop            ) {
  if( n == 0 ) {
    DRIVER_EXECUTE( false, true                               );
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

driver_command_t driver_command( char* command ) {
  if     ( 0 == strcmp( command, "?data"            ) ) {
    return driver_data_sizeof;
  }
  else if( 0 == strcmp( command, "<data"            ) ) {
    return driver_data_rd;
  }
  else if( 0 == strcmp( command, ">data"            ) ) {
    return driver_data_wr;
  }
  else if( 0 == strcmp( command, "?kernel_id"       ) ) {
    return driver_kernel_id;
  }
  else if( 0 == strcmp( command, "?kernel_data"     ) ) {
    return driver_kernel_data;
  }
  else if( 0 == strcmp( command, "!kernel_prologue" ) ) {
    return driver_kernel_prologue;
  }
  else if( 0 == strcmp( command, "!kernel"          ) ) {
    return driver_kernel;
  }
  else if( 0 == strcmp( command, "!kernel_epilogue" ) ) {
    return driver_kernel_epilogue;
  }
  else if( 0 == strcmp( command, "!nop"             ) ) {
    return driver_nop;
  }
  else {
    return NULL;
  }
}

int main( int argc, char* argv[] ) {
  if( !board_init() ) {
    return -1;
  }

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
      driver_command_t f = driver_command( cp[ 0 ] );

      if( f != NULL ) {
	if( f( driver_ack, cp + 1, cn - 1 ) ) {
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
