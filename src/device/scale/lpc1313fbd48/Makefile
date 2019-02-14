# Copyright (C) 2018 SCARV project <info@scarv.org>
#
# Use of this source code is restricted per the MIT license, a copy of which 
# can be found at https://opensource.org/licenses/MIT (or should be included 
# as LICENSE.txt within the associated archive or repository).

BSP         = ${DIR_BUILD}/scale-hw/target/lpc1313fbd48/build

-include ${BSP}/lib/scale.conf

GCC_PATHS  += -I ${BSP}/include -L ${BSP}/lib
GCC_FLAGS  += -T ${BSP}/lib/scale.ld
GCC_LIBS   += -lscale

TARGETS    += ${DIR_BUILD}/target.elf 
TARGETS    += ${DIR_BUILD}/target.bin 
TARGETS    += ${DIR_BUILD}/target.hex

deps-fetch :
	@git clone --reference-if-able ${CACHE}/scale-hw http://www.github.com/danpage/scale-hw.git ${DIR_BUILD}/scale-hw
deps-build :
	@make --no-builtin-rules -C ${DIR_BUILD}/scale-hw/target/lpc1313fbd48 all
deps-clean : 
	@make --no-builtin-rules -C ${DIR_BUILD}/scale-hw/target/lpc1313fbd48 clean

${DIR_BUILD}/%.o : %.c %.h
	@${GCC_PREFIX}gcc $(patsubst %, -I %, ${INCLUDES}) ${GCC_PATHS} ${GCC_FLAGS} ${SCALE_CONF} -c -o ${@} ${<}
${DIR_BUILD}/%.o : %.s %.h
	@${GCC_PREFIX}gcc $(patsubst %, -I %, ${INCLUDES}) ${GCC_PATHS} ${GCC_FLAGS} ${SCALE_CONF} -c -o ${@} ${<}
${DIR_BUILD}/%.o : %.S %.h
	@${GCC_PREFIX}gcc $(patsubst %, -I %, ${INCLUDES}) ${GCC_PATHS} ${GCC_FLAGS} ${SCALE_CONF} -c -o ${@} ${<}

${DIR_BUILD}/%.elf ${DIR_BUILD}/%.map : ${KERNEL_OBJECTS} ${DEVICE_OBJECTS}
	@${GCC_PREFIX}gcc $(patsubst %, -I %, ${INCLUDES}) ${GCC_PATHS} ${GCC_FLAGS} ${SCALE_CONF} -Wl,-Map=${DIR_BUILD}/${*}.map -o ${DIR_BUILD}/${*}.elf ${^} ${GCC_LIBS}
${DIR_BUILD}/%.bin                    : ${DIR_BUILD}/%.elf
	@${GCC_PREFIX}objcopy ${OBJCOPY_FLAGS} -O binary ${<} ${@}
${DIR_BUILD}/%.hex                    : ${DIR_BUILD}/%.elf
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

