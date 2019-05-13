# Copyright (C) 2018 SCARV project <info@scarv.org>
#
# Use of this source code is restricted per the MIT license, a copy of which 
# can be found at https://opensource.org/licenses/MIT (or should be included 
# as LICENSE.txt within the associated archive or repository).

FROM ubuntu

ARG DATE

LABEL maintainer="SCARV project <info@scarv.org>" date="${DATE}" url="https://github.com/scarv/lab-target"

RUN apt-get --quiet --assume-yes update \
 && apt-get --quiet --assume-yes install apt-utils gosu sudo wget \
 && apt-get --quiet --assume-yes install make gcc git doxygen

RUN wget --quiet https://developer.arm.com/-/media/Files/downloads/gnu-rm/8-2018q4/gcc-arm-none-eabi-8-2018-q4-major-linux.tar.bz2 \
 && tar --extract --directory /opt --file gcc-arm-none-eabi-8-2018-q4-major-linux.tar.bz2 \
 && rm --force gcc-arm-none-eabi-8-2018-q4-major-linux.tar.bz2
ENV PATH "/opt/gcc-arm-none-eabi-8-2018-q4-major/bin:${PATH}"

COPY ./entrypoint.sh /usr/sbin/entrypoint.sh
RUN chmod 755 /usr/sbin/entrypoint.sh

ENTRYPOINT [ "/usr/sbin/entrypoint.sh" ]
