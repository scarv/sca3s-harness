#!/bin/bash

# Copyright (C) 2018 SCARV project <info@scarv.org>
#
# Use of this source code is restricted per the MIT license, a copy of which 
# can be found at https://opensource.org/licenses/MIT (or should be included 
# as LICENSE.txt within the associated archive or repository).

if [ -z "${DOCKER_GID}" ] ; then
  DOCKER_GID="1000"
fi 

if [ -z "${DOCKER_UID}" ] ; then
  DOCKER_UID="1000"
fi 

groupadd --gid ${DOCKER_GID} scarv ; useradd --gid ${DOCKER_GID} --uid ${DOCKER_UID} --no-user-group scarv

exec /usr/sbin/gosu scarv:scarv "${@}"
