# Copyright (C) 2018 SCARV project <info@scarv.org>
#
# Use of this source code is restricted per the MIT license, a copy of which 
# can be found at https://opensource.org/licenses/MIT (or should be included 
# as LICENSE.txt within the associated archive or repository).

# =============================================================================

open_hw_manager

connect_hw_server -url localhost:3121
refresh_hw_server
current_hw_target [get_hw_targets]
open_hw_target

current_hw_device [lindex [get_hw_devices] 0]
refresh_hw_device -update_hw_probes false [lindex [get_hw_devices] 0]

set bfpath [lindex $argv 0]
puts $bfpath
set_property PROGRAM.FILE $bfpath [lindex [get_hw_devices] 0]

program_hw_devices [lindex [get_hw_devices] 0]
refresh_hw_device [lindex [get_hw_devices] 0]

exit

# =============================================================================
