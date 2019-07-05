# [SCA3S](https://github.com/scarv/sca3s): target implementation

<!--- -------------------------------------------------------------------- --->

[![Build Status](https://travis-ci.com/scarv/sca3s-target.svg)](https://travis-ci.com/scarv/sca3s-target)
[![Documentation](https://codedocs.xyz/scarv/sca3s-target.svg)](https://codedocs.xyz/scarv/sca3s-target)

<!--- -------------------------------------------------------------------- --->

*Acting as a component part of the
[SCARV](https://www.scarv.org)
project,
SCA3S is a collection of resources that support the development 
and analysis of cryptographic implementations wrt.
[side-channel attack](https://en.wikipedia.org/wiki/Side-channel_attack):
it places particular emphasis on analogue side-channels (e.g.,
power and EM) stemming from
[RISC-V](https://riscv.org)-based
platforms.
The main
[repository](https://github.com/scarv/sca3s)
acts as a general container for associated resources;
this specific submodule houses
a framework within which target implementations are developed.*

<!--- -------------------------------------------------------------------- --->

## Organisation

```
├── bin         - scripts (e.g., environment configuration)
├── build       - working directory for build
├── docker      - configuration for container
└── src         - source code
    ├── board     - board  implementations
    ├── driver    - driver implementations
    ├── kernel    - kernel implementations
    └── share     - shared functionality
```

<!--- -------------------------------------------------------------------- --->

## Quickstart

1. Either

   1. install any associated pre-requisites, e.g.,

      - a suitable
        compiler 
        and 
        programming 
        tool-chain,
        e.g., board-specific versions of
        [GCC](https://gcc.gnu.org)
        and
        [OpenOCD](http://openocd.org),
      - the
        [Doxygen](http://www.doxygen.nl)
        documentation generation system,

      or

   2. install the 
      [Docker](https://www.docker.com)
      container platform.

2. Go to the 
   [GitHub](https://github.com)-hosted
   repository
   [web-page](https://github.com/scarv/sca3s-target),
   and create a
   [fork](https://guides.github.com/activities/forking) 
   of it: doing so will create a copy of the repository in your *own* 
   account, the username for which we will assume is `${USER}`.

3. Execute

   ```sh
   git clone https://github.com/${USER}/sca3s-target.git
   cd ./sca3s-target
   source ./bin/conf.sh
   ```

   to clone and initialise the *forked* repository,
   then configure the environment;
   for example, you should find that the environment variable
   `REPO_HOME`
   is set appropriately.

4. Select the
   board and target implementation (implying the driver and kernel) types
   by setting the environment variables
   `BOARD`
   and
   `TARGET`
   appropriately,
   e.g., via

   ```sh
   export BOARD="scale/lpc1313fbd48"
   export TARGET="block"
   ```

   and, where appropriate, configure the target implementation 
   via the
   `CONF`
   environment variable, e.g.,

   ```sh
   export CONF="-Dfoo=bar"
   ```

5. Produce the target implementation in the *forked* repository:

   1. edit

      ```sh
      ${REPO_HOME}/src/kernel/${TARGET}/kernel.c
      ```

      to specify parameters of the implementation, 
      e.g., the block size,
      then

   2. edit

      ```sh
      ${REPO_HOME}/src/kernel/${TARGET}/kernel.c
      ```

      to complete the implementation itself, 
      e.g., the `kernel_enc` and/or `kernel_dec` functions,

   3. commit and push the result.

6. Either

   1. use the *forked* repository remotely:
      go to 
      [lab.scarv.org](https://lab.scarv.org),
      and submit a job referencing the forked repository, i.e.,

      ```sh
      https://github.com/${USER}/sca3s-target.git
      ```

      in order to acquire an associated trace set,
      or

   2. use the *forked* repository  locally:
      use targets in the top-level `Makefile` to drive a set of
      common tasks, e.g.,

      - execute
        either

        1. naively

           ```sh
           make doc
           ```
   
           or

        2. via the Docker container 
   
           ```sh
           make docker-docker
           ```

        to build the documentation,

      - execute
        either

        1. naively

           ```sh
           make deps-fetch 
           make deps-build
           ```

           or

        2. via the Docker container 

           ```sh
           make deps-fetch-docker
           make deps-build-docker
           ```

        then
        either 

        1. naively

           ```sh
           make build
           ```
   
           or

        2. via the Docker container 
   
           ```sh
           make build-docker
           ```

        to build the target implementation,

      - execute
        either

        1. naively

           ```sh
           make clean
           ```
   
           or

        2. via the Docker container 
   
           ```sh
           make clean-docker
           ```

        to clean-up
        (e.g., remove everything built in `${REPO_HOME}/build`).

<!--- -------------------------------------------------------------------- --->

## Acknowledgements

This work has been supported in part by EPSRC via grant 
[EP/R012288/1](https://gow.epsrc.ukri.org/NGBOViewGrant.aspx?GrantRef=EP/R012288/1),
under the [RISE](http://www.ukrise.org) programme.

<!--- -------------------------------------------------------------------- --->
