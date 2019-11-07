# Copyright (C) 2018 SCARV project <info@scarv.org>
#
# Use of this source code is restricted per the MIT license, a copy of which 
# can be found at https://opensource.org/licenses/MIT (or should be included 
# as LICENSE.txt within the associated archive or repository).

ifndef REPO_HOME
  $(error "execute 'source ./bin/conf.sh' to configure environment")
endif

# =============================================================================

# Set defaults for various required environment variables.

export CONTEXT ?= native

export BOARD   ?= scale/lpc1313fbd48
export DRIVER  ?= block
export CONF    ?=

# Include the Docker configuration: we need to specifically do this here, as
# it supports a) the Docker build context outright, plus b) any Docker-based
# targets within the native build context.

include ${REPO_HOME}/src/sca3s/harness/board/${BOARD}/conf.mk_docker

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

ifeq "${CONTEXT}" "docker"
%          :
	@docker run --rm --volume "${REPO_HOME}:/mnt/scarv/sca3s/harness" --env DOCKER_GID="$(shell id --group)" --env DOCKER_UID="$(shell id --user)" --env CONTEXT="native" --env BOARD="${BOARD}" --env DRIVER="${DRIVER}" ${DOCKER_FLAGS} ${DOCKER_REPO}:${DOCKER_TAG} ${*}
endif

ifeq "${CONTEXT}" "native"

%-docker  :
	@make --directory="${REPO_HOME}/src/docker"        ${*}
%-harness :
	@make --directory="${REPO_HOME}/src/sca3s/harness" ${*}

doc    : ${REPO_HOME}/Doxyfile
	@doxygen ${<}

update :
	@-git remote add upstream https://github.com/scarv/sca3s-harness.git
	@-git fetch upstream
	@-git merge upstream/master
	@-git push

clean  :
	@rm --force --recursive ${REPO_HOME}/build/*
endif

# =============================================================================
