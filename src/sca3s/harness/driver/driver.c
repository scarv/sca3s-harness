/* Copyright (C) 2018 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#include "driver.h" 

/** @brief      A temporary buffer used to store request         strings;
  *             note the fixed upper-bound on length of such strings.
  */

char     driver_req[ 64 ];

/** @brief      A temporary buffer used to store acknowledgement strings;
  *             note the fixed upper-bound on length of such strings.
  */

char     driver_ack[ 64 ];

/** @brief      A temporary TSC value, sampled before a given operation.
  */

uint64_t driver_tsc_init;

/** @brief      A temporary TSC value, sampled after  a given operation.
  */

uint64_t driver_tsc_fini;

/** @brief      Service a request of the form
  *             \verbatim ?data <id> \endverbatim
  *             i.e., query the size (in bytes) of an identified data buffer.
  *
  * @param[out] ack the acknowledgement string
  * @param[in]  req an array of strings capturing arguments of the request
  * @param[in]    n the length of the argument array \c req
  *
  * @return     a Boolean flag indicating success (\c true) or failure (\c false)
  *
  * @note       An entry for the buffer identifier should be locatable within 
  *             \c kernel_data_desc; a special-case \c tsc identifies the TSC.
  */

DRIVER_COMMAND(driver_data_sizeof    ) {
  if( n == 1 ) {
    if( 0 == strcmp( "tsc", req[ 0 ] ) ) {
          uint32_t x = SIZEOF( uint64_t );

          return bytestostr( ack, ( uint8_t* )( &x ), SIZEOF( x ) ) == SIZEOF( x );
    }
    else {
      for( kernel_data_desc_t* desc = kernel_data_desc; desc->id != NULL; desc++ ) {    
        if( 0 == strcmp( desc->id, req[ 0 ] ) ) {
          uint32_t x = desc->size;

          return bytestostr( ack, ( uint8_t* )( &x ), SIZEOF( x ) ) == SIZEOF( x );
        }
      }
    }
  }

  return false;
}

/** @brief      Service a request of the form
  *             \verbatim <data <id> \endverbatim
  *             i.e., read  an octet string from an identified data buffer.
  *
  * @param[out] ack the acknowledgement string
  * @param[in]  req an array of strings capturing arguments of the request
  * @param[in]    n the length of the argument array \c req
  *
  * @return     a Boolean flag indicating success (\c true) or failure (\c false)
  *
  * @note       An entry for the buffer identifier should be locatable within 
  *             \c kernel_data_desc; a special-case \c tsc identifies the TSC.
  */

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

/** @brief      Service a request of the form
  *             \verbatim >data <id> <octet string> \endverbatim
  *             i.e., write an octet string into an identified data buffer.
  *
  * @param[out] ack the acknowledgement string
  * @param[in]  req an array of strings capturing arguments of the request
  * @param[in]    n the length of the argument array \c req
  *
  * @return     a Boolean flag indicating success (\c true) or failure (\c false)
  *
  * @note       An entry for the buffer identifier should be locatable within 
  *             \c kernel_data_desc; a special-case \c tsc identifies the TSC.
  */

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

/** @brief      Service a request of the form
  *             \verbatim ?kernel_id \endverbatim
  *             i.e., ...
  *
  * @param[out] ack the acknowledgement string
  * @param[in]  req an array of strings capturing arguments of the request
  * @param[in]    n the length of the argument array \c req
  *
  * @return     a Boolean flag indicating success (\c true) or failure (\c false)
  */

DRIVER_COMMAND(driver_kernel_id      ) {
  if( n == 0 ) {
    kernel_func_desc.kernel_id( ack ); return true;
  }

  return false;
}

#include <stdio.h>

/** @brief      Service a request of the form
  *             \verbatim ?kernel_data < \endverbatim
  *             or
  *             \verbatim ?kernel_data > \endverbatim
  *             i.e., ...
  *
  * @param[out] ack the acknowledgement string
  * @param[in]  req an array of strings capturing arguments of the request
  * @param[in]    n the length of the argument array \c req
  *
  * @return     a Boolean flag indicating success (\c true) or failure (\c false)
  */

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

/** @brief      Service a request of the form
  *             \verbatim !kernel_prologue \endverbatim
  *             i.e., execute the kernel prologue.
  *
  * @param[out] ack the acknowledgement string
  * @param[in]  req an array of strings capturing arguments of the request
  * @param[in]    n the length of the argument array \c req
  *
  * @return     a Boolean flag indicating success (\c true) or failure (\c false)
  */

DRIVER_COMMAND(driver_kernel_prologue) {
  if( n == 0 ) {
    DRIVER_EXECUTE( false, kernel_func_desc.kernel_prologue() );
  }

  return false;
}

/** @brief      Service a request of the form
  *             \verbatim !kernel \endverbatim
  *             i.e., execute the kernel.
  *
  * @param[out] ack the acknowledgement string
  * @param[in]  req an array of strings capturing arguments of the request
  * @param[in]    n the length of the argument array \c req
  *
  * @return     a Boolean flag indicating success (\c true) or failure (\c false)
  */

DRIVER_COMMAND(driver_kernel         ) {
  if( n == 0 ) {
    DRIVER_EXECUTE(  true, kernel_func_desc.kernel()          );
  }

  return false;
}

/** @brief      Service a request of the form
  *             \verbatim !kernel_epilogue \endverbatim
  *             i.e., execute the kernel epilogue.
  *
  * @param[out] ack the acknowledgement string
  * @param[in]  req an array of strings capturing arguments of the request
  * @param[in]    n the length of the argument array \c req
  *
  * @return     a Boolean flag indicating success (\c true) or failure (\c false)
  */

DRIVER_COMMAND(driver_kernel_epilogue) {
  if( n == 0 ) {
    DRIVER_EXECUTE( false, kernel_func_desc.kernel_epilogue() );
  }

  return false;
}

/** @brief      Service a request of the form
  *             \verbatim !nop \endverbatim
  *             i.e., execute a NOP (or empty, null) operation: this supports
  *             more accurate use of TSC values, in the sense that any fixed 
  *             overhead can be corrected for.
  *
  * @param[out] ack the acknowledgement string
  * @param[in]  req an array of strings capturing arguments of the request
  * @param[in]    n the length of the argument array \c req
  *
  * @return     a Boolean flag indicating success (\c true) or failure (\c false)
  */

DRIVER_COMMAND(driver_nop            ) {
  if( n == 0 ) {
    DRIVER_EXECUTE( false, true                               );
  }

  return false;
}

/** @brief      Read  a line from the UART,
  *             respecting an EOL sematics based on use of CR only (i.e., no 
  *             associated LF).
  *
  * @param[out] x a string capturing the line read
  *
  * @return     the string \c x.
  */

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

/** @brief      Write a line to   the UART, 
  *             respecting an EOL sematics based on use of CR only (i.e., no 
  *             associated LF).
  *
  * @param[in]  x a string capturing the line written
  *
  * @return     the string \c x.
  */

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
      driver_command_t f = NULL;

      if     ( 0 == strcmp( cp[ 0 ], "?data"            ) ) {
        f = driver_data_sizeof;
      }
      else if( 0 == strcmp( cp[ 0 ], "<data"            ) ) {
        f = driver_data_rd;
      }
      else if( 0 == strcmp( cp[ 0 ], ">data"            ) ) {
        f = driver_data_wr;
      }
      else if( 0 == strcmp( cp[ 0 ], "?kernel_id"       ) ) {
        f = driver_kernel_id;
      }
      else if( 0 == strcmp( cp[ 0 ], "?kernel_data"     ) ) {
        f = driver_kernel_data;
      }
      else if( 0 == strcmp( cp[ 0 ], "!kernel_prologue" ) ) {
        f = driver_kernel_prologue;
      }
      else if( 0 == strcmp( cp[ 0 ], "!kernel"          ) ) {
        f = driver_kernel;
      }
      else if( 0 == strcmp( cp[ 0 ], "!kernel_epilogue" ) ) {
        f = driver_kernel_epilogue;
      }
      else if( 0 == strcmp( cp[ 0 ], "!nop"             ) ) {
        f = driver_nop;
      }

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
