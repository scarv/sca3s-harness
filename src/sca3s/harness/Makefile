# Copyright (C) 2018 SCARV project <info@scarv.org>
#
# Use of this source code is restricted per the MIT license, a copy of which 
# can be found at https://opensource.org/licenses/MIT (or should be included 
# as LICENSE.txt within the associated archive or repository).

# =============================================================================

   EMPTY :=
   SPACE := ${EMPTY} ${EMPTY}
   COLON := :

INCLUDES +=            ${REPO_HOME}/src/sca3s/harness/share
 SOURCES += $(wildcard ${REPO_HOME}/src/sca3s/harness/share/*.c)
 HEADERS += $(wildcard ${REPO_HOME}/src/sca3s/harness/share/*.h)

INCLUDES +=            ${REPO_HOME}/src/sca3s/harness/board
INCLUDES +=            ${REPO_HOME}/src/sca3s/harness/board/${BOARD}
 SOURCES += $(wildcard ${REPO_HOME}/src/sca3s/harness/board/*.c)
 SOURCES += $(wildcard ${REPO_HOME}/src/sca3s/harness/board/${BOARD}/*.c)
 HEADERS += $(wildcard ${REPO_HOME}/src/sca3s/harness/board/*.h)
 HEADERS += $(wildcard ${REPO_HOME}/src/sca3s/harness/board/${BOARD}/*.h)

INCLUDES +=            ${REPO_HOME}/src/sca3s/harness/driver
INCLUDES +=            ${REPO_HOME}/src/sca3s/harness/driver/${TARGET}
 SOURCES += $(wildcard ${REPO_HOME}/src/sca3s/harness/driver/*.c)
 SOURCES += $(wildcard ${REPO_HOME}/src/sca3s/harness/driver/${TARGET}/*.c)
 HEADERS += $(wildcard ${REPO_HOME}/src/sca3s/harness/driver/*.h)
 HEADERS += $(wildcard ${REPO_HOME}/src/sca3s/harness/driver/${TARGET}/*.h)

INCLUDES +=            ${REPO_HOME}/src/sca3s/harness/kernel
INCLUDES +=            ${REPO_HOME}/src/sca3s/harness/kernel/${TARGET}
 SOURCES += $(wildcard ${REPO_HOME}/src/sca3s/harness/kernel/*.c)
 SOURCES += $(wildcard ${REPO_HOME}/src/sca3s/harness/kernel/${TARGET}/*.c)
 HEADERS += $(wildcard ${REPO_HOME}/src/sca3s/harness/kernel*.h)
 HEADERS += $(wildcard ${REPO_HOME}/src/sca3s/harness/kernel/${TARGET}/*.h)

 OBJECTS += $(addprefix ${REPO_HOME}/build/${BOARD}/, $(notdir $(patsubst %.c, %.o, ${SOURCES})))

vpath %.h $(subst ${SPACE},${COLON},${INCLUDES})
vpath %.c $(subst ${SPACE},${COLON},${INCLUDES})

# =============================================================================

# Include the per board configuration for target implementation plus any
# dependencies it has.

include ${REPO_HOME}/src/sca3s/harness/board/${BOARD}/conf.mk_deps
include ${REPO_HOME}/src/sca3s/harness/board/${BOARD}/conf.mk_target

# Construct a definitive list of built files, plus their associated paths
# to allow pre-creation of an appropriate directory structure (note that
# use of sort is required to remove duplicates). 

BUILD_FILES    = ${OBJECTS}
BUILD_FILES   += ${TARGETS}

BUILD_PATHS    = $(sort $(foreach FILE,${BUILD_FILES},$(dir ${FILE})))

# Define targets for built files not otherwise catered for.

${BUILD_PATHS} :
	@mkdir --parents ${@}

${CLEAN_PATHS} :
	@rm --force --recursive ${@}

# Define targets to drive build process.

build : ${BUILD_PATHS} ${BUILD_FILES}

clean :
	@rm -rf ${REPO_HOME}/build/*

# =============================================================================
