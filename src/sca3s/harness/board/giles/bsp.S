/* Copyright (C) 2018 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */
                    .syntax  unified
                    .thumb

// ============================================================================

                    .section .text.__bsp,         "x"

                    .global  bsp_trigger_enable   
                    .thumb_func
	
bsp_trigger_enable: svc      #1

                    bx       lr

                    .global  bsp_trigger_unable   
                    .thumb_func
	
bsp_trigger_unable: svc      #0

                    bx       lr

                    .global  bsp_halt
                    .thumb_func
	
bsp_halt:           bkpt     #0

// ============================================================================
