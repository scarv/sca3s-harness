# Copyright (C) 2018 SCARV project <info@scarv.org>
#
# Use of this source code is restricted per the MIT license, a copy of which 
# can be found at https://opensource.org/licenses/MIT (or should be included 
# as LICENSE.txt within the associated archive or repository).

BSP        = ${REPO_HOME}/build/scale-hw/target/lpc1313fbd48/build

-include ${BSP}/lib/scale.conf

GCC_PATHS += -I ${BSP}/include -L ${BSP}/lib
GCC_FLAGS += -T ${BSP}/lib/scale.ld
GCC_LIBS  += -lscale

TARGETS   += ${REPO_HOME}/build/target.elf 
TARGETS   += ${REPO_HOME}/build/target.bin 
TARGETS   += ${REPO_HOME}/build/target.hex

deps-fetch :
	@git clone --reference-if-able ${CACHE}/scale-hw http://www.github.com/danpage/scale-hw.git ${REPO_HOME}/build/scale-hw
deps-build :
	@make --no-builtin-rules -C ${REPO_HOME}/build/scale-hw/target/lpc1313fbd48 all
deps-clean : 
	@make --no-builtin-rules -C ${REPO_HOME}/build/scale-hw/target/lpc1313fbd48 clean

${REPO_HOME}/build/%.o : %.c %.h
	@${GCC_PREFIX}gcc $(patsubst %, -I %, ${INCLUDES}) ${GCC_PATHS} ${GCC_FLAGS} ${SCALE_CONF} -c -o ${@} ${<}
${REPO_HOME}/build/%.o : %.s %.h
	@${GCC_PREFIX}gcc $(patsubst %, -I %, ${INCLUDES}) ${GCC_PATHS} ${GCC_FLAGS} ${SCALE_CONF} -c -o ${@} ${<}
${REPO_HOME}/build/%.o : %.S %.h
	@${GCC_PREFIX}gcc $(patsubst %, -I %, ${INCLUDES}) ${GCC_PATHS} ${GCC_FLAGS} ${SCALE_CONF} -c -o ${@} ${<}

${REPO_HOME}/build/%.elf ${REPO_HOME}/build/%.map : ${DEVICE_OBJECTS} ${TARGET_OBJECTS}
	@${GCC_PREFIX}gcc $(patsubst %, -I %, ${INCLUDES}) ${GCC_PATHS} ${GCC_FLAGS} ${SCALE_CONF} -Wl,-Map=${REPO_HOME}/build/${*}.map -o ${REPO_HOME}/build/${*}.elf ${^} ${GCC_LIBS}
${REPO_HOME}/build/%.bin                          : ${REPO_HOME}/build/%.elf
	@${GCC_PREFIX}objcopy ${OBJCOPY_FLAGS} -O binary ${<} ${@}
${REPO_HOME}/build/%.hex                          : ${REPO_HOME}/build/%.elf
	@${GCC_PREFIX}objcopy ${OBJCOPY_FLAGS} -O ihex   ${<} ${@}

report  : ${TARGETS}
	@arm-none-eabi-readelf --wide --all $(filter %.elf, ${^})

program : ${TARGETS}
	@openocd -f interface/jlink.cfg                             \
                 -c "transport select swd"                          \
                 -f    target/lpc13xx.cfg                           \
                 -c       "init"                                    \
                 -c "reset init"                                    \
                 -c "flash write_image erase $(filter %.hex, ${^})" \
	         -c "reset  run"                                    \
                 -c "shutdown"

