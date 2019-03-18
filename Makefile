# Copyright (C) 2018 SCARV project <info@scarv.org>
#
# Use of this source code is restricted per the MIT license, a copy of which 
# can be found at https://opensource.org/licenses/MIT (or should be included 
# as LICENSE.txt within the associated archive or repository).

ifndef DEVICE
  $(error "DEVICE environment variable undefined: aborting")
endif
ifndef TARGET
  $(error "TARGET environment variable undefined: aborting")
endif

       EMPTY    :=
       SPACE    := ${EMPTY} ${EMPTY}
       COLON    := :

       INCLUDES +=            ${REPO_HOME}/src/device
       INCLUDES +=            ${REPO_HOME}/src/device/${DEVICE}
       INCLUDES +=            ${REPO_HOME}/src/driver
       INCLUDES +=            ${REPO_HOME}/src/driver/${TARGET}
       INCLUDES +=            ${REPO_HOME}/src/kernel
       INCLUDES +=            ${REPO_HOME}/src/kernel/${TARGET}
       INCLUDES +=            ${REPO_HOME}/src/share

DEVICE_SOURCES  += $(wildcard ${REPO_HOME}/src/device/*.c)
DEVICE_SOURCES  += $(wildcard ${REPO_HOME}/src/device/${DEVICE}/*.c)

TARGET_SOURCES  += $(wildcard ${REPO_HOME}/src/driver/*.c)
TARGET_SOURCES  += $(wildcard ${REPO_HOME}/src/driver/${TARGET}/*.c)
TARGET_SOURCES  += $(wildcard ${REPO_HOME}/src/kernel/*.c)
TARGET_SOURCES  += $(wildcard ${REPO_HOME}/src/kernel/${TARGET}/*.c)
TARGET_SOURCES  += $(wildcard ${REPO_HOME}/src/share/*.c)

DEVICE_HEADERS  += $(wildcard ${REPO_HOME}/src/device/*.h)
DEVICE_HEADERS  += $(wildcard ${REPO_HOME}/src/device/${DEVICE}/*.h)

TARGET_HEADERS  += $(wildcard ${REPO_HOME}/src/driver/*.h)
TARGET_HEADERS  += $(wildcard ${REPO_HOME}/src/driver/${TARGET}/*.h)
TARGET_HEADERS  += $(wildcard ${REPO_HOME}/src/kernel*.h)
TARGET_HEADERS  += $(wildcard ${REPO_HOME}/src/kernel/${TARGET}/*.h)
TARGET_HEADERS  += $(wildcard ${REPO_HOME}/src/share/*.h)

DEVICE_OBJECTS  += $(addprefix ${REPO_HOME}/build/, $(notdir $(patsubst %.c, %.o, ${DEVICE_SOURCES})))
TARGET_OBJECTS  += $(addprefix ${REPO_HOME}/build/, $(notdir $(patsubst %.c, %.o, ${TARGET_SOURCES})))

vpath %.h $(subst ${SPACE},${COLON},${INCLUDES})
vpath %.c $(subst ${SPACE},${COLON},${INCLUDES})

include ${REPO_HOME}/src/device/${DEVICE}/Makefile

build-device : ${DEVICE_OBJECTS}

build-driver : ${TARGET_OBJECTS}

build-target :        ${TARGETS}

build        : build-device build-driver build-target

doc          : ${REPO_HOME}/Doxyfile
	@doxygen ${<}

clean        :
	@rm -rf ${REPO_HOME}/build/*
