# Copyright (C) 2018 SCARV project <info@scarv.org>
#
# Use of this source code is restricted per the MIT license, a copy of which 
# can be found at https://opensource.org/licenses/MIT (or should be included 
# as LICENSE.txt within the associated archive or repository).

IMAGE = scarv/lab-target:0.1.0

build :
	@docker build --tag ${IMAGE} --file ./Dockerfile .
push  :
	@docker push ${IMAGE}
pull  :
	@docker pull ${IMAGE}

run   :
	@docker run --env DOCKER_GID=$(id --group) --env DOCKER_UID=$(id --user) --interactive --tty --rm ${IMAGE} bash
