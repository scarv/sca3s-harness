# Copyright (C) 2018 SCARV project <info@scarv.org>
#
# Use of this source code is restricted per the MIT license, a copy of which 
# can be found at https://opensource.org/licenses/MIT (or should be included 
# as LICENSE.txt within the associated archive or repository).

ifndef BOARD
  $(error "BOARD environment variable undefined: aborting")
endif
ifndef TARGET
  $(error "TARGET environment variable undefined: aborting")
endif

       EMPTY    :=
       SPACE    := ${EMPTY} ${EMPTY}
       COLON    := :

       INCLUDES +=            ${REPO_HOME}/src/board
       INCLUDES +=            ${REPO_HOME}/src/board/${BOARD}
       INCLUDES +=            ${REPO_HOME}/src/driver
       INCLUDES +=            ${REPO_HOME}/src/driver/${TARGET}
       INCLUDES +=            ${REPO_HOME}/src/kernel
       INCLUDES +=            ${REPO_HOME}/src/kernel/${TARGET}
       INCLUDES +=            ${REPO_HOME}/src/share

 BOARD_SOURCES  += $(wildcard ${REPO_HOME}/src/board/*.c)
 BOARD_SOURCES  += $(wildcard ${REPO_HOME}/src/board/${BOARD}/*.c)

TARGET_SOURCES  += $(wildcard ${REPO_HOME}/src/driver/*.c)
TARGET_SOURCES  += $(wildcard ${REPO_HOME}/src/driver/${TARGET}/*.c)
TARGET_SOURCES  += $(wildcard ${REPO_HOME}/src/kernel/*.c)
TARGET_SOURCES  += $(wildcard ${REPO_HOME}/src/kernel/${TARGET}/*.c)
TARGET_SOURCES  += $(wildcard ${REPO_HOME}/src/share/*.c)

 BOARD_HEADERS  += $(wildcard ${REPO_HOME}/src/board/*.h)
 BOARD_HEADERS  += $(wildcard ${REPO_HOME}/src/board/${BOARD}/*.h)

TARGET_HEADERS  += $(wildcard ${REPO_HOME}/src/driver/*.h)
TARGET_HEADERS  += $(wildcard ${REPO_HOME}/src/driver/${TARGET}/*.h)
TARGET_HEADERS  += $(wildcard ${REPO_HOME}/src/kernel*.h)
TARGET_HEADERS  += $(wildcard ${REPO_HOME}/src/kernel/${TARGET}/*.h)
TARGET_HEADERS  += $(wildcard ${REPO_HOME}/src/share/*.h)

 BOARD_OBJECTS  += $(addprefix ${REPO_HOME}/build/, $(notdir $(patsubst %.c, %.o,  ${BOARD_SOURCES})))
TARGET_OBJECTS  += $(addprefix ${REPO_HOME}/build/, $(notdir $(patsubst %.c, %.o, ${TARGET_SOURCES})))

vpath %.h $(subst ${SPACE},${COLON},${INCLUDES})
vpath %.c $(subst ${SPACE},${COLON},${INCLUDES})

include ${REPO_HOME}/src/board/${BOARD}/Makefile

build-board  :  ${BOARD_OBJECTS}

build-driver : ${TARGET_OBJECTS}

build-target :        ${TARGETS}

build        : build-board build-driver build-target

doc          : ${REPO_HOME}/Doxyfile
	@doxygen ${<}

all          : deps-fetch deps-build build

clean        :
	@rm -rf ${REPO_HOME}/build/*
