# Copyright (C) 2018 SCARV project <info@scarv.org>
#
# Use of this source code is restricted per the MIT license, a copy of which 
# can be found at https://opensource.org/licenses/MIT (or should be included 
# as LICENSE.txt within the associated archive or repository).

FROM ubuntu

LABEL maintainer="SCARV project <info@scarv.org>"

RUN apt-get --assume-yes --quiet update && apt-get --assume-yes --quiet install gosu make git gcc doxygen wget

RUN wget --quiet https://developer.arm.com/-/media/Files/downloads/gnu-rm/8-2018q4/gcc-arm-none-eabi-8-2018-q4-major-linux.tar.bz2 && tar --extract --directory /opt --file gcc-arm-none-eabi-8-2018-q4-major-linux.tar.bz2 && rm --force gcc-arm-none-eabi-8-2018-q4-major-linux.tar.bz2
ENV PATH "/opt/gcc-arm-none-eabi-8-2018-q4-major/bin:${PATH}"

COPY ./entrypoint.sh /usr/sbin/entrypoint.sh
RUN chmod 755 /usr/sbin/entrypoint.sh

ENTRYPOINT [ "/usr/sbin/entrypoint.sh" ]
