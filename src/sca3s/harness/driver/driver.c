/* Copyright (C) 2018 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#include "driver.h" 

// ============================================================================

/** @brief      A temporary buffer used to store request         strings;
  *             note the fixed upper-bound on length of such strings.
  */

char          driver_req[ 64 ];

/** @brief      A temporary buffer used to store acknowledgement strings;
  *             note the fixed upper-bound on length of such strings.
  */

char          driver_ack[ 64 ];

// ----------------------------------------------------------------------------

/** @brief      A pointer to the function exit code, 
  *             which is pre-initialised to avoid having to search for and
  *             so locate it during execution of the driver.
  */

kernel_fec_t* driver_fec = NULL;

/** @brief      A pointer to the function cycle count,
  *             which is pre-initialised to avoid having to search for and
  *             so locate it during execution of the driver.
  */

kernel_fcc_t* driver_fcc = NULL;

// ============================================================================

/** @brief      Service a request of the form
  *             \verbatim ?data ${REGISTER}          \endverbatim
  *             i.e., query the allocated size (in bytes) of an identified data buffer.
  *
  * @param[out] \c ack the acknowledgement string.
  * @param[in]  \c req an array of strings capturing arguments of the request.
  * @param[in]  \c   n the length of the argument array \c req.
  *
  * @return     a flag indicating failure (\c false) or success (\c true).
  *
  * @note       An entry for the buffer identifier should be locatable within 
  *             \c kernel_data_spec.
  */

DRIVER_COMMAND(driver_data_typeof   ) {
  if( n != 1 ) {
    return false;
  }

  for( kernel_data_spec_t* spec = kernel_data_spec; spec->id != NULL; spec++ ) {    
    if( 0 == strcmp( spec->id, req[ 0 ] ) ) {
      if( spec->type & KERNEL_DATA_TYPE_I ) {
        strcat( ack, ">" );
      }
      if( spec->type & KERNEL_DATA_TYPE_O ) {
        strcat( ack, "<" );
      }
      if( spec->type & KERNEL_DATA_TYPE_V ) {
        strcat( ack, "#" );
      }
      if( spec->type & KERNEL_DATA_TYPE_S ) {
        strcat( ack, "$" );
      }

      return true;
    }
  }

  return false;
}

// ----------------------------------------------------------------------------

/** @brief      Service a request of the form
  *             \verbatim |data ${REGISTER}          \endverbatim
  *             i.e., query the allocated size (in bytes) of an identified data buffer.
  *
  * @param[out] \c ack the acknowledgement string.
  * @param[in]  \c req an array of strings capturing arguments of the request.
  * @param[in]  \c   n the length of the argument array \c req.
  *
  * @return     a flag indicating failure (\c false) or success (\c true).
  *
  * @note       An entry for the buffer identifier should be locatable within 
  *             \c kernel_data_spec.
  */

DRIVER_COMMAND(driver_data_sizeof   ) {
  if( n != 1 ) {
    return false;
  }

  for( kernel_data_spec_t* spec = kernel_data_spec; spec->id != NULL; spec++ ) {    
    if( 0 == strcmp( spec->id, req[ 0 ] ) ) {
      uint8_t t =                                                         ( spec->size );

      return bytestostr( ack, ( uint8_t* )( &t ), SIZEOF( t ) ) == SIZEOF( t );
    }
  }

  return false;
}

// ----------------------------------------------------------------------------

/** @brief      Service a request of the form
  *             \verbatim #data ${REGISTER}          \endverbatim
  *             i.e., query the used      size (in bytes) of an identified data buffer.
  *
  * @param[out] \c ack the acknowledgement string.
  * @param[in]  \c req an array of strings capturing arguments of the request.
  * @param[in]  \c   n the length of the argument array \c req.
  *
  * @return     a flag indicating failure (\c false) or success (\c true).
  *
  * @note       An entry for the buffer identifier should be locatable within 
  *             \c kernel_data_spec.
  */

DRIVER_COMMAND(driver_data_usedof   ) {
  if( n != 1 ) {
    return false;
  }

  for( kernel_data_spec_t* spec = kernel_data_spec; spec->id != NULL; spec++ ) {    
    if( 0 == strcmp( spec->id, req[ 0 ] ) ) {
      uint8_t t = ( spec->type & KERNEL_DATA_TYPE_V ) ? ( *spec->used ) : ( spec->size );

      return bytestostr( ack, ( uint8_t* )( &t ), SIZEOF( t ) ) == SIZEOF( t );
    }
  }

  return false;
}

// ----------------------------------------------------------------------------

/** @brief      Service a request of the form
  *             \verbatim >data ${REGISTER} ${VALUE} \endverbatim
  *             i.e., write an octet string into an identified data buffer.
  *
  * @param[out] \c ack the acknowledgement string.
  * @param[in]  \c req an array of strings capturing arguments of the request.
  * @param[in]  \c   n the length of the argument array \c req.
  *
  * @return     a flag indicating failure (\c false) or success (\c true).
  *
  * @note       An entry for the buffer identifier should be locatable within 
  *             \c kernel_data_spec.
  */

DRIVER_COMMAND(driver_data_wr       ) {
  if( n != 2 ) {
    return false;
  }

  for( kernel_data_spec_t* spec = kernel_data_spec; spec->id != NULL; spec++ ) {    
    if( 0 == strcmp( spec->id, req[ 0 ] ) ) {
      int t = strtobytes( spec->data,  spec->size, req[ 1 ] );

      if( ( t >= 0 ) && ( t <= spec->size ) ) {
        if( spec->type & KERNEL_DATA_TYPE_V ) {
          *spec->used = t;
        }

        return  true;
      }
      else {
        if( spec->type & KERNEL_DATA_TYPE_V ) {
          *spec->used = 0;
        }

        return false;
      }
    }
  }

  return false;
}

// ----------------------------------------------------------------------------

/** @brief      Service a request of the form
  *             \verbatim <data ${REGISTER}          \endverbatim
  *             i.e., read  an octet string from an identified data buffer.
  *
  * @param[out] \c ack the acknowledgement string.
  * @param[in]  \c req an array of strings capturing arguments of the request.
  * @param[in]  \c   n the length of the argument array \c req.
  *
  * @return     a flag indicating failure (\c false) or success (\c true).
  *
  * @note       An entry for the buffer identifier should be locatable within 
  *             \c kernel_data_spec.
  */

DRIVER_COMMAND(driver_data_rd       ) {
  if( n != 1 ) {
    return false;
  }

  for( kernel_data_spec_t* spec = kernel_data_spec; spec->id != NULL; spec++ ) {    
    if( 0 == strcmp( spec->id, req[ 0 ] ) ) {
      int t = 0;

      if( spec->type & KERNEL_DATA_TYPE_V ) {
        t = bytestostr( ack, spec->data, *spec->used );
      }
      else {
        t = bytestostr( ack, spec->data,  spec->size );
      }

      if( ( t >= 0 ) && ( t <= spec->size ) ) {
        return  true;
      }
      else {
        return false;
      }
    }
  }

  return false;
}

// ----------------------------------------------------------------------------

/** @brief      Service a request of the form
  *             \verbatim ?kernel_id       \endverbatim
  *             i.e., query the kernel identifier.
  *
  * @param[out] \c ack the acknowledgement string.
  * @param[in]  \c req an array of strings capturing arguments of the request.
  * @param[in]  \c   n the length of the argument array \c req.
  *
  * @return     a flag indicating failure (\c false) or success (\c true).
  */

DRIVER_COMMAND(driver_kernel_id     ) {
  if( n != 0 ) {
    return false;
  }

  kernel_func_spec.kernel_id( ack );

  return true;
}

// ----------------------------------------------------------------------------

/** @brief      Service a request of the form
  *             \verbatim >kernel_data     \endverbatim
  *             i.e., query the kernel writable data.
  *
  * @param[out] \c ack the acknowledgement string.
  * @param[in]  \c req an array of strings capturing arguments of the request.
  * @param[in]  \c   n the length of the argument array \c req.
  *
  * @return     a flag indicating failure (\c false) or success (\c true).
  */

DRIVER_COMMAND(driver_kernel_data_wr) {
  if( n != 0 ) {
    return false;
  }

  bool f = false;

  for( kernel_data_spec_t* spec = kernel_data_spec; spec->id != NULL; spec++ ) {    
    if( spec->type & KERNEL_DATA_TYPE_I ) {
      if( f ) { strcat( ack, "," ); } strcat( ack, spec->id ); f = true;
    }
  }

  return true;
}

// ----------------------------------------------------------------------------

/** @brief      Service a request of the form
  *             \verbatim <kernel_data     \endverbatim
  *             i.e., query the kernel readable data.
  *
  * @param[out] \c ack the acknowledgement string.
  * @param[in]  \c req an array of strings capturing arguments of the request.
  * @param[in]  \c   n the length of the argument array \c req.
  *
  * @return     a flag indicating failure (\c false) or success (\c true).
  */

DRIVER_COMMAND(driver_kernel_data_rd) {
  if( n != 0 ) {
    return false;
  }

  bool f = false;

  for( kernel_data_spec_t* spec = kernel_data_spec; spec->id != NULL; spec++ ) {    
    if( spec->type & KERNEL_DATA_TYPE_O ) {
      if( f ) { strcat( ack, "," ); } strcat( ack, spec->id ); f = true;
    }
  }

  return true;
}

// ----------------------------------------------------------------------------

/** @brief      Service a request of the form
  *             \verbatim !kernel          \endverbatim
  *             i.e., execute the kernel.
  *
  * @param[out] \c ack the acknowledgement string.
  * @param[in]  \c req an array of strings capturing arguments of the request.
  * @param[in]  \c   n the length of the argument array \c req.
  *
  * @return     a flag indicating failure (\c false) or success (\c true).
  */

DRIVER_COMMAND(driver_kernel        ) {
  int m = 0;

  if     ( n == 0 ) {
    m =     (      1   );
  }
  else if( n == 1 ) {
    m = atoi( req[ 0 ] );
  }
  else {
    return false;
  }

  for( int i = 0; i < m; i++ ) {
                  ( kernel_func_spec.kernel_prologue() );
    DRIVER_EXECUTE( kernel_func_spec.kernel()          );
                  ( kernel_func_spec.kernel_epilogue() );
  }

  return true;
}

// ----------------------------------------------------------------------------

/** @brief      Service a request of the form
  *             \verbatim !nop             \endverbatim
  *             i.e., execute a NOP (or empty, null) operation:
  *             a example use-case for this would be to correct for fixed
  *             overheads wrt. the function cycle count register.
  *
  * @param[out] \c ack the acknowledgement string.
  * @param[in]  \c req an array of strings capturing arguments of the request.
  * @param[in]  \c   n the length of the argument array \c req.
  *
  * @return     a flag indicating failure (\c false) or success (\c true).
  */

DRIVER_COMMAND(driver_nop           ) {
  int m = 0;

  if     ( n == 0 ) {
    m =     (      1   );
  }
  else if( n == 1 ) {
    m = atoi( req[ 0 ] );
  }
  else {
    return false;
  }

  for( int i = 0; i < m; i++ ) {
    DRIVER_EXECUTE( kernel_func_spec.nop()             );
  }

  return true;
}

// ============================================================================

/** @brief      Read  a line from the UART,
  *             respecting an EOL sematics based on use of CR only (i.e., no 
  *             associated LF).
  *
  * @param[out] \c x a string capturing the line read.
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

// ----------------------------------------------------------------------------

/** @brief      Write a line to   the UART, 
  *             respecting an EOL sematics based on use of CR only (i.e., no 
  *             associated LF).
  *
  * @param[in]  \c x a string capturing the line written.
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

// ============================================================================

/** @brief      Execute the driver, in either
  *             1) non-interactive mode,
  *                meaning all inputs and outputs are  statically defined
  *                (i.e.,              via the pre-processor),
  *                or
  *             1)     interactive mode
  *                meaning all inputs and outputs are dynamically defined
  *                (i.e., communicated via the          UART).
  *
  * @param[in]  \c argc the number of command line arguments
  * @param[in]  \c argv the           command line arguments
  *
  * @return     an exit code.
  */

int main( int argc, char* argv[] ) {
  if( !board_init() ) {
    return -1;
  }

  for( kernel_data_spec_t* spec = kernel_data_spec; spec->id != NULL; spec++ ) {    
    if     ( 0 == strcmp( spec->id, "fec" ) ) {
      driver_fec = ( kernel_fec_t* )( spec->data );
    }
    else if( 0 == strcmp( spec->id, "fcc" ) ) {
      driver_fcc = ( kernel_fcc_t* )( spec->data );
    }
  }

#if defined( DRIVER_NONINTERACTIVE )
  kernel_func_spec.kernel_prologue();
  board_trigger_wr(  true );
  kernel_func_spec.kernel();
  board_trigger_wr( false );
  kernel_func_spec.kernel_epilogue();
#else
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

      if     ( 0 == strcmp( cp[ 0 ], "?data"   ) ) {
        f = driver_data_typeof;
      }
      else if( 0 == strcmp( cp[ 0 ], "|data"   ) ) {
        f = driver_data_sizeof;
      }
      else if( 0 == strcmp( cp[ 0 ], "#data"   ) ) {
        f = driver_data_usedof;
      }
      else if( 0 == strcmp( cp[ 0 ], ">data"   ) ) {
        f = driver_data_wr;
      }
      else if( 0 == strcmp( cp[ 0 ], "<data"   ) ) {
        f = driver_data_rd;
      }
      else if( 0 == strcmp( cp[ 0 ], "?kernel" ) ) {
        f = driver_kernel_id;
      }
      else if( 0 == strcmp( cp[ 0 ], ">kernel" ) ) {
        f = driver_kernel_data_wr;
      }
      else if( 0 == strcmp( cp[ 0 ], "<kernel" ) ) {
        f = driver_kernel_data_rd;
      }
      else if( 0 == strcmp( cp[ 0 ], "!kernel" ) ) {
        f = driver_kernel;
      }
      else if( 0 == strcmp( cp[ 0 ], "!nop"    ) ) {
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
#endif

  return 0;
}

// ============================================================================
