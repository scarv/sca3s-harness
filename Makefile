# Copyright (C) 2018 SCARV project <info@scarv.org>
#
# Use of this source code is restricted per the MIT license, a copy of which 
# can be found at https://opensource.org/licenses/MIT (or should be included 
# as LICENSE.txt within the associated archive or repository).

include Makefile.conf

export DIR_SRC   := ${CURDIR}/src
export DIR_BUILD := ${CURDIR}/build

       EMPTY     :=
       SPACE     := ${EMPTY} ${EMPTY}
       COLON     := :

       INCLUDES  +=            ${DIR_SRC}/share
       INCLUDES  +=            ${DIR_SRC}/kernel
       INCLUDES  +=            ${DIR_SRC}/kernel/${KERNEL}
       INCLUDES  +=            ${DIR_SRC}/driver
       INCLUDES  +=            ${DIR_SRC}/driver/${KERNEL}
       INCLUDES  +=            ${DIR_SRC}/device
       INCLUDES  +=            ${DIR_SRC}/device/${DEVICE}

KERNEL_SOURCES   += $(wildcard ${DIR_SRC}/share/*.c)
KERNEL_SOURCES   += $(wildcard ${DIR_SRC}/kernel/*.c)
KERNEL_SOURCES   += $(wildcard ${DIR_SRC}/kernel/${KERNEL}/*.c)
KERNEL_SOURCES   += $(wildcard ${DIR_SRC}/driver/*.c)
KERNEL_SOURCES   += $(wildcard ${DIR_SRC}/driver/${KERNEL}/*.c)
DEVICE_SOURCES   += $(wildcard ${DIR_SRC}/device/*.c)
DEVICE_SOURCES   += $(wildcard ${DIR_SRC}/device/${DEVICE}/*.c)

KERNEL_HEADERS   += $(wildcard ${DIR_SRC}/share/*.h)
KERNEL_HEADERS   += $(wildcard ${DIR_SRC}/kernel*.h)
KERNEL_HEADERS   += $(wildcard ${DIR_SRC}/kernel/${KERNEL}/*.h)
KERNEL_HEADERS   += $(wildcard ${DIR_SRC}/driver/*.h)
KERNEL_HEADERS   += $(wildcard ${DIR_SRC}/driver/${KERNEL}/*.h)
DEVICE_HEADERS   += $(wildcard ${DIR_SRC}/device/*.h)
DEVICE_HEADERS   += $(wildcard ${DIR_SRC}/device/${DEVICE}/*.h)

KERNEL_OBJECTS   += $(addprefix ${DIR_BUILD}/, $(notdir $(patsubst %.c, %.o, ${KERNEL_SOURCES})))
DEVICE_OBJECTS   += $(addprefix ${DIR_BUILD}/, $(notdir $(patsubst %.c, %.o, ${DEVICE_SOURCES})))

vpath %.h $(subst ${SPACE},${COLON},${INCLUDES})
vpath %.c $(subst ${SPACE},${COLON},${INCLUDES})

include ${DIR_SRC}/device/${DEVICE}/Makefile

build-kernel : ${KERNEL_OBJECTS}

build-device : ${DEVICE_OBJECTS}

build-target :        ${TARGETS}

build        : deps-fetch deps-build build-kernel build-device build-target

clean        :
	@rm -f ${KERNEL_OBJECTS} 
	@rm -f ${DEVICE_OBJECTS} 
	@rm -f        ${TARGETS}

spotless     : clean
	@rm -rf ./build/*
