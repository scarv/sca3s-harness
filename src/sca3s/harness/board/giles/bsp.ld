/* Copyright (C) 2018 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

MEMORY {
  ram (rwx) : ORIGIN = 0x00000000, LENGTH = 64K
}

ENTRY( __irq_table )

SECTIONS {
  . = 0x00000000;

  .text         : ALIGN( 16 ) {
    __head_text = .;
    *( .data.__irq_handler )
    *( .text.__irq_handler )
    *( .text*              )
    *( .text.*             )
    *( .rodata*            )
    *( .rodata.*           )
    . = ALIGN( 4 );
    __foot_text = .;
  } > ram

  .data         : ALIGN( 16 ) {
    __head_data = .;
    *( .data               )
    *( .data.*             )
    . = ALIGN( 4 );
    __foot_data = .;
  } > ram

  .bss          : ALIGN( 16 ) {
    __head_bss  = .;
    *( .bss                )
    *( .bss.*              )
    . = ALIGN( 4 );
    __foot_bss  = .;
  } > ram
}

PROVIDE( __tos = ORIGIN( ram ) + LENGTH( ram ) );
