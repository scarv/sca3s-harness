# Copyright (C) 2018 SCARV project <info@scarv.org>
#
# Use of this source code is restricted per the MIT license, a copy of which 
# can be found at https://opensource.org/licenses/MIT (or should be included 
# as LICENSE.txt within the associated archive or repository).

# =============================================================================

${REPO_HOME}/build/${BOARD}/docker/Dockerfile     : ${REPO_HOME}/src/docker/Dockerfile
	@m4 --include="${REPO_HOME}/src/docker" --include="${REPO_HOME}/src/sca3s/harness/board/${BOARD}" ${<} > ${@}
${REPO_HOME}/build/${BOARD}/docker/entrypoint.sh  : ${REPO_HOME}/src/docker/entrypoint.sh
	@m4 --include="${REPO_HOME}/src/docker" --include="${REPO_HOME}/src/sca3s/harness/board/${BOARD}" ${<} > ${@}

${REPO_HOME}/build/${BOARD}/docker/conf.mk_target : ${REPO_HOME}/src/sca3s/harness/board/${BOARD}/conf.mk_target
	@m4 --include="${REPO_HOME}/src/docker" --include="${REPO_HOME}/src/sca3s/harness/board/${BOARD}" ${<} > ${@}
${REPO_HOME}/build/${BOARD}/docker/conf.mk_deps   : ${REPO_HOME}/src/sca3s/harness/board/${BOARD}/conf.mk_deps
	@m4 --include="${REPO_HOME}/src/docker" --include="${REPO_HOME}/src/sca3s/harness/board/${BOARD}" ${<} > ${@}

BUILD_FILES  = ${REPO_HOME}/build/${BOARD}/docker/Dockerfile
BUILD_FILES += ${REPO_HOME}/build/${BOARD}/docker/entrypoint.sh

BUILD_FILES += ${REPO_HOME}/build/${BOARD}/docker/conf.mk_target
BUILD_FILES += ${REPO_HOME}/build/${BOARD}/docker/conf.mk_deps

BUILD_PATHS  = ${REPO_HOME}/build/${BOARD}/docker

${BUILD_PATHS} :
	@mkdir --parents ${@}

${CLEAN_PATHS} :
	@rm --force --recursive ${@}

# =============================================================================

build : ${BUILD_PATHS} ${BUILD_FILES}
	@docker build --tag ${DOCKER_REPO}:${DOCKER_TAG} --build-arg DATE="$(shell date -u +'%d/%m/%Y-%H:%M:%SZ')" --build-arg BOARD="${BOARD}" ${REPO_HOME}/build/${BOARD}/docker

clean : ${CLEAN_PATHS}
	@docker images | grep ${DOCKER_REPO} | grep ${DOCKER_TAG} | tr --squeeze-repeats ' ' | cut --delimiter=' ' --fields=3 | uniq | xargs --no-run-if-empty docker rmi --force && rm --force --recursive ${BUILD_PATHS}

push  :
	@docker push ${DOCKER_REPO}:${DOCKER_TAG}

pull  :
	@docker pull ${DOCKER_REPO}:${DOCKER_TAG}

# =============================================================================
