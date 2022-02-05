# Copyright (C) 2018 SCARV project <info@scarv.org>
#
# Use of this source code is restricted per the MIT license, a copy of which 
# can be found at https://opensource.org/licenses/MIT (or should be included 
# as LICENSE.txt within the associated archive or repository).

ifndef REPO_HOME
  $(error "execute 'source ./bin/conf.sh' to configure environment")
endif
ifndef REPO_VERSION
  $(error "execute 'source ./bin/conf.sh' to configure environment")
endif

# =============================================================================

   EMPTY       :=
   SPACE       := ${EMPTY} ${EMPTY}
   COLON       := :

# -----------------------------------------------------------------------------

INCLUDES       +=            ${REPO_HOME}/src/sca3s/harness/share
 SOURCES       += $(wildcard ${REPO_HOME}/src/sca3s/harness/share/*.c)
 HEADERS       += $(wildcard ${REPO_HOME}/src/sca3s/harness/share/*.h)

INCLUDES       +=            ${REPO_HOME}/src/sca3s/harness/board
INCLUDES       +=            ${REPO_HOME}/src/sca3s/harness/board/${BOARD}
 SOURCES       += $(wildcard ${REPO_HOME}/src/sca3s/harness/board/*.c)
 SOURCES       += $(wildcard ${REPO_HOME}/src/sca3s/harness/board/${BOARD}/*.c)
 SOURCES       += $(wildcard ${REPO_HOME}/src/sca3s/harness/board/*.s)
 SOURCES       += $(wildcard ${REPO_HOME}/src/sca3s/harness/board/${BOARD}/*.s)
 SOURCES       += $(wildcard ${REPO_HOME}/src/sca3s/harness/board/*.S)
 SOURCES       += $(wildcard ${REPO_HOME}/src/sca3s/harness/board/${BOARD}/*.S)
 HEADERS       += $(wildcard ${REPO_HOME}/src/sca3s/harness/board/*.h)
 HEADERS       += $(wildcard ${REPO_HOME}/src/sca3s/harness/board/${BOARD}/*.h)

INCLUDES       +=            ${REPO_HOME}/src/sca3s/harness/kernel
INCLUDES       +=            ${REPO_HOME}/src/sca3s/harness/kernel/${KERNEL}
 SOURCES       += $(wildcard ${REPO_HOME}/src/sca3s/harness/kernel/*.c)
 SOURCES       += $(wildcard ${REPO_HOME}/src/sca3s/harness/kernel/${KERNEL}/*.c)
 HEADERS       += $(wildcard ${REPO_HOME}/src/sca3s/harness/kernel/*.h)
 HEADERS       += $(wildcard ${REPO_HOME}/src/sca3s/harness/kernel/${KERNEL}/*.h)

INCLUDES       += $(addprefix ${REPO_HOME}/src/sca3s/harness/kernel/${KERNEL}/, $(sort $(dir $(filter %.h, $(shell cat ${REPO_HOME}/src/sca3s/harness/kernel/${KERNEL}/kernel_imp.manifest)))))
 SOURCES       += $(addprefix ${REPO_HOME}/src/sca3s/harness/kernel/${KERNEL}/, $(sort       $(filter %.c, $(shell cat ${REPO_HOME}/src/sca3s/harness/kernel/${KERNEL}/kernel_imp.manifest)) ))
 SOURCES       += $(addprefix ${REPO_HOME}/src/sca3s/harness/kernel/${KERNEL}/, $(sort       $(filter %.s, $(shell cat ${REPO_HOME}/src/sca3s/harness/kernel/${KERNEL}/kernel_imp.manifest)) ))
 SOURCES       += $(addprefix ${REPO_HOME}/src/sca3s/harness/kernel/${KERNEL}/, $(sort       $(filter %.S, $(shell cat ${REPO_HOME}/src/sca3s/harness/kernel/${KERNEL}/kernel_imp.manifest)) ))
 HEADERS       += $(addprefix ${REPO_HOME}/src/sca3s/harness/kernel/${KERNEL}/, $(sort       $(filter %.h, $(shell cat ${REPO_HOME}/src/sca3s/harness/kernel/${KERNEL}/kernel_imp.manifest)) ))

INCLUDES       +=            ${REPO_HOME}/src/sca3s/harness/driver
 SOURCES       += $(wildcard ${REPO_HOME}/src/sca3s/harness/driver/*.c)
 HEADERS       += $(wildcard ${REPO_HOME}/src/sca3s/harness/driver/*.h)

include ${REPO_HOME}/src/sca3s/harness/board/${BOARD}/conf.mk_deps

    GCC_PATHS  +=
    GCC_FLAGS  += -DVERSION="${REPO_VERSION}" -DBOARD='"${BOARD}"' -DKERNEL='"${KERNEL}"' ${CONF}
    GCC_LIBS   +=

 OBJECTS       += $(addprefix ${REPO_HOME}/build/${BOARD}/, $(notdir $(patsubst %.c, %.o, $(filter %.c, ${SOURCES}))))
 OBJECTS       += $(addprefix ${REPO_HOME}/build/${BOARD}/, $(notdir $(patsubst %.s, %.o, $(filter %.s, ${SOURCES}))))
 OBJECTS       += $(addprefix ${REPO_HOME}/build/${BOARD}/, $(notdir $(patsubst %.S, %.o, $(filter %.S, ${SOURCES}))))

vpath %.h $(subst ${SPACE},${COLON},${INCLUDES})
vpath %.c $(subst ${SPACE},${COLON},${INCLUDES})
vpath %.s $(subst ${SPACE},${COLON},${INCLUDES})
vpath %.S $(subst ${SPACE},${COLON},${INCLUDES})

include ${REPO_HOME}/src/sca3s/harness/board/${BOARD}/conf.mk_target

# =============================================================================

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
	@rm --force --recursive ${REPO_HOME}/build/*

# =============================================================================
