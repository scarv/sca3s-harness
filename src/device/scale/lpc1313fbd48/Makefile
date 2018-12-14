# Copyright (C) 2018 SCARV project <info@scarv.org>
#
# Use of this source code is restricted per the MIT license, a copy of which 
# can be found at https://opensource.org/licenses/MIT (or should be included 
# as LICENSE.txt within the associated archive or repository).

GCC_PREFIX  = arm-none-eabi-
GCC_PATHS   = $(patsubst %, -I %, ${INCLUDES}) -I ${DIR_BUILD}/scale-hw/target/lpc1313fbd48/build/include -L ${DIR_BUILD}/scale-hw/target/lpc1313fbd48/build/lib
GCC_FLAGS   = -Wall -std=c11 -mcpu=cortex-m3 -mthumb -nostartfiles -T ${DIR_BUILD}/scale-hw/target/lpc1313fbd48/build/lib/scale.ld
GCC_LIBS    = -lscale

TARGETS    += ${DIR_BUILD}/target.elf 
TARGETS    += ${DIR_BUILD}/target.bin 
TARGETS    += ${DIR_BUILD}/target.hex

deps-fetch :
	@git clone --reference ${CACHE}/scale-hw http://www.github.com/danpage/scale-hw.git ${DIR_BUILD}/scale-hw
deps-build :
	@make --no-builtin-rules -C ${DIR_BUILD}/scale-hw/target/lpc1313fbd48 all
deps-clean : 
	@make --no-builtin-rules -C ${DIR_BUILD}/scale-hw/target/lpc1313fbd48 clean

${DIR_BUILD}/%.o : %.c %.h
	@${GCC_PREFIX}gcc ${GCC_PATHS} ${GCC_FLAGS} -c -o ${@} $(filter %.c, ${^})

${DIR_BUILD}/%.elf ${DIR_BUILD}/%.map : ${KERNEL_OBJECTS} ${DEVICE_OBJECTS}
	@${GCC_PREFIX}gcc ${GCC_PATHS} ${GCC_FLAGS} -Wl,-Map=${DIR_BUILD}/${*}.map -o ${DIR_BUILD}/${*}.elf ${DIR_BUILD}/scale-hw/target/lpc1313fbd48/build/lib/crt0.o ${^} ${GCC_LIBS}
${DIR_BUILD}/%.bin                    : ${DIR_BUILD}/%.elf
	@${GCC_PREFIX}objcopy --gap-fill=0 -O binary ${<} ${@}
${DIR_BUILD}/%.hex                    : ${DIR_BUILD}/%.elf
	@${GCC_PREFIX}objcopy --gap-fill=0 -O ihex   ${<} ${@}

report  : ${TARGETS}
	@arm-none-eabi-readelf --wide --all $(filter %.elf, ${^})

program : ${TARGETS}
	@lpc21isp -wipe -hex $(filter %.hex, ${^}) ${USB} 9600 12000
