/* Copyright (C) 2018 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */
                    .syntax  unified
                    .thumb
	
                    .extern    main

                    .extern    bsp_trigger_enable
                    .extern    bsp_trigger_unable
                    .extern    bsp_halt
	
                    .extern  __tos

// ============================================================================
	
                    .section .data.__irq_handler, "w"

                    .global  __irq_table

__irq_table:        .word    __tos             // 0x00000000 => Top of Stack    
                    .word    __irq_handler_rst // 0x00000004 => reset         handler 
                    .word    __irq_handler_nul // 0x00000008 => NMI           handler 
                    .word    __irq_handler_nul // 0x0000000C => Hard  fault   handler
                    .word    __irq_handler_nul // 0x00000010 => MMU   fault   handler
                    .word    __irq_handler_nul // 0x00000014 => Bus   fault   handler
                    .word    __irq_handler_nul // 0x00000018 => Usage fault   Handler
                    .word    __irq_handler_nul // 0x0000001C => reserved        
                    .word    __irq_handler_nul // 0x00000020 => reserved        
                    .word    __irq_handler_nul // 0x00000024 => reserved        
                    .word    __irq_handler_nul // 0x00000028 => reserved        
                    .word    __irq_handler_nul // 0x0000002C => SVC           handler 
                    .word    __irq_handler_nul // 0x00000030 => Debug monitor handler
                    .word    __irq_handler_nul // 0x00000034 => reserved        
                    .word    __irq_handler_nul // 0x00000038 => PendSV        handler 
                    .word    __irq_handler_nul // 0x0000003C => SysTick       handler 
  
// ----------------------------------------------------------------------------

                    .section .text.__irq_handler, "x"

                    .global  __irq_handler_nul
                    .thumb_func

__irq_handler_nul:  bl       bsp_halt          //         halt

                    .global  __irq_handler_rst
                    .thumb_func  

__irq_handler_rst:  bl        __start          // call __start

                    bl       bsp_halt          //         halt

// ============================================================================

                    .section .text.__start,       "x"	

                    .global  __start	
                    .thumb_func  
	
__start:            eors     r0, r0            // argc = 0
                    eors     r1, r1            // argv = NULL
  
                    bl           main          // call    main

                    bl       bsp_halt          //         halt
	
// ============================================================================
