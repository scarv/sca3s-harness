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

export CONTEXT           ?= native

export BOARD             ?= giles
export KERNEL            ?= block
export CONF              ?=

export DEPS              ?= ${REPO_HOME}/build/${BOARD}/deps

# -----------------------------------------------------------------------------

export TRACE_COUNT_MAJOR ?= 1
export TRACE_COUNT_MINOR ?= 1

# -----------------------------------------------------------------------------

export DOCKER_REPO       ?= scarv/sca3s-harness.$(subst /,-,${BOARD})
export DOCKER_TAG        ?= ${REPO_VERSION}
export DOCKER_FLAGS      ?= 

export DOCKER_FLAGS      += --env        DOCKER_GID="$(shell id --group)" 
export DOCKER_FLAGS      += --env        DOCKER_UID="$(shell id --user)" 

export DOCKER_FLAGS      += --env           CONTEXT="native" 

export DOCKER_FLAGS      += --env             BOARD="${BOARD}" 
export DOCKER_FLAGS      += --env            KERNEL="${KERNEL}" 
export DOCKER_FLAGS      += --env              CONF="${CONF}" 

export DOCKER_FLAGS      += --env TRACE_COUNT_MAJOR="${TRACE_COUNT_MAJOR}" 
export DOCKER_FLAGS      += --env TRACE_COUNT_MINOR="${TRACE_COUNT_MINOR}"

# =============================================================================

# Define targets to drive build process, depending on CONTEXT (i.e., on the 
# selected build context):
#
# 1. For the Docker build context, defer everything to the Docker container 
#    (i.e., execute make on the same target *within* the container).
#
# 2. For the native build context, 
#
#    - deal with various specific, global targets (e.g., documentation), or
#    - defer to the appropriate sub-Makefile for everything else.

# -----------------------------------------------------------------------------

ifeq "${CONTEXT}" "docker"
%          :
	@docker run --rm --volume "${REPO_HOME}:/mnt/scarv/sca3s/harness" ${DOCKER_FLAGS} ${DOCKER_REPO}:${DOCKER_TAG} ${*}
endif

# -----------------------------------------------------------------------------

ifeq "${CONTEXT}" "native"
%-docker   :
	@make --directory="${REPO_HOME}/src/docker"        ${*}
%-harness  :
	@make --directory="${REPO_HOME}/src/sca3s/harness" ${*}

update     :
	@${REPO_HOME}/bin/update.sh --current
update-all :
	@${REPO_HOME}/bin/update.sh --all

doxygen    : ${REPO_HOME}/Doxyfile
	@doxygen ${<}

spotless   :
	@rm --force --recursive ${REPO_HOME}/build/*
endif

# =============================================================================
