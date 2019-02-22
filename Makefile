# Copyright (C) 2018 SCARV project <info@scarv.org>
#
# Use of this source code is restricted per the MIT license, a copy of which 
# can be found at https://opensource.org/licenses/MIT (or should be included 
# as LICENSE.txt within the associated archive or repository).

export REPO_HOME := ${CURDIR}

       EMPTY     :=
       SPACE     := ${EMPTY} ${EMPTY}
       COLON     := :

       INCLUDES  +=            ${REPO_HOME}/src/device
       INCLUDES  +=            ${REPO_HOME}/src/device/${DEVICE}
       INCLUDES  +=            ${REPO_HOME}/src/driver
       INCLUDES  +=            ${REPO_HOME}/src/driver/${DRIVER}
       INCLUDES  +=            ${REPO_HOME}/src/kernel
       INCLUDES  +=            ${REPO_HOME}/src/kernel/${DRIVER}
       INCLUDES  +=            ${REPO_HOME}/src/share

DEVICE_SOURCES   += $(wildcard ${REPO_HOME}/src/device/*.c)
DEVICE_SOURCES   += $(wildcard ${REPO_HOME}/src/device/${DEVICE}/*.c)

DRIVER_SOURCES   += $(wildcard ${REPO_HOME}/src/driver/*.c)
DRIVER_SOURCES   += $(wildcard ${REPO_HOME}/src/driver/${DRIVER}/*.c)
DRIVER_SOURCES   += $(wildcard ${REPO_HOME}/src/kernel/*.c)
DRIVER_SOURCES   += $(wildcard ${REPO_HOME}/src/kernel/${DRIVER}/*.c)
DRIVER_SOURCES   += $(wildcard ${REPO_HOME}/src/share/*.c)

DEVICE_HEADERS   += $(wildcard ${REPO_HOME}/src/device/*.h)
DEVICE_HEADERS   += $(wildcard ${REPO_HOME}/src/device/${DEVICE}/*.h)

DRIVER_HEADERS   += $(wildcard ${REPO_HOME}/src/driver/*.h)
DRIVER_HEADERS   += $(wildcard ${REPO_HOME}/src/driver/${DRIVER}/*.h)
DRIVER_HEADERS   += $(wildcard ${REPO_HOME}/src/kernel*.h)
DRIVER_HEADERS   += $(wildcard ${REPO_HOME}/src/kernel/${DRIVER}/*.h)
DRIVER_HEADERS   += $(wildcard ${REPO_HOME}/src/share/*.h)

DEVICE_OBJECTS   += $(addprefix ${REPO_HOME}/build/, $(notdir $(patsubst %.c, %.o, ${DEVICE_SOURCES})))
DRIVER_OBJECTS   += $(addprefix ${REPO_HOME}/build/, $(notdir $(patsubst %.c, %.o, ${DRIVER_SOURCES})))

vpath %.h $(subst ${SPACE},${COLON},${INCLUDES})
vpath %.c $(subst ${SPACE},${COLON},${INCLUDES})

include ${REPO_HOME}/src/device/${DEVICE}/Makefile

build-device : ${DEVICE_OBJECTS}

build-driver : ${DRIVER_OBJECTS}

build-target :        ${TARGETS}

build        : build-device build-driver build-target

clean        :
	@rm -f ${DEVICE_OBJECTS} 
	@rm -f ${DRIVER_OBJECTS} 
	@rm -f        ${TARGETS}

spotless     : clean
	@rm -rf ./build/*
