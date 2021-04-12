# Copyright (C) 2018 SCARV project <info@scarv.org>
#
# Use of this source code is restricted per the MIT license, a copy of which 
# can be found at https://opensource.org/licenses/MIT (or should be included 
# as LICENSE.txt within the associated archive or repository).

# =============================================================================

FROM ubuntu

ARG DATE
ARG BOARD

LABEL maintainer="SCARV project <info@scarv.org>" url="https://github.com/scarv/sca3s-harness" date="${DATE}" 

# -----------------------------------------------------------------------------

ENV DEBIAN_FRONTEND="noninteractive"

RUN apt-get --assume-yes --quiet update \
 && apt-get --assume-yes --quiet install apt-utils autoconf automake doxygen gcc git gosu make python sudo wget

# -----------------------------------------------------------------------------

ENV DEPS="/opt/scarv/sca3s/harness/board/${BOARD}/deps"
RUN mkdir --parents ${DEPS}

include(`Dockerfile.in')

COPY conf.mk_deps ${DEPS}/Makefile
RUN make --directory="${DEPS}" deps-fetch \
 && make --directory="${DEPS}" deps-patch \
 && make --directory="${DEPS}" deps-build

# -----------------------------------------------------------------------------

COPY ./entrypoint.sh /usr/sbin/entrypoint.sh
RUN chmod 755 /usr/sbin/entrypoint.sh
ENTRYPOINT [ "/usr/sbin/entrypoint.sh" ]

# =============================================================================
