# [SCA3S](https://github.com/scarv/sca3s): target implementation harness

<!--- -------------------------------------------------------------------- --->

[![Build Status](https://travis-ci.com/scarv/sca3s-harness.svg)](https://travis-ci.com/scarv/sca3s-harness)
[![Documentation](https://codedocs.xyz/scarv/sca3s-harness.svg)](https://codedocs.xyz/scarv/sca3s-harness)

<!--- -------------------------------------------------------------------- --->

*Acting as a component part of the
[SCARV](https://www.scarv.org)
project,
SCA3S is a collection of resources that support the development 
and analysis of cryptographic implementations wrt.
[side-channel attack](https://en.wikipedia.org/wiki/Side-channel_attack):
mirroring the goals of SCARV, it places particular emphasis on analogue 
side-channels (e.g., power and EM) stemming from
[RISC-V](https://riscv.org)-based
platforms.
The main
[repository](https://github.com/scarv/sca3s)
acts as a general container for associated resources;
this specific submodule houses
a harness within which target implementations are developed.*

<!--- -------------------------------------------------------------------- --->

## Organisation

```
├── bin                    - scripts (e.g., environment configuration)
├── build                  - working directory for build
└── src
    ├── docker             - source code for containers
    └── sca3s              - source code for SCA3S
        └── harness        - source code for SCA3S harness
            ├── board        - board  implementations
            ├── driver       - driver implementations
            ├── kernel       - kernel implementations
            └── share        - shared functionality
```

<!--- -------------------------------------------------------------------- --->

## Quickstart

1. Either

   1. install associated pre-requisites, e.g.,

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

      thus supporting a native build context,
      and/or

   2. install the 
      [Docker](https://www.docker.com)
      container platform,
      thus supporting a Docker build context.

2. Create a *copy* of the 
   [template repository](https://github.com/scarv/sca3s-harness)
   in your *own* account: we term this the working repository.
   Using the
   [GitHub](https://github.com)-based
   interface, you can do so via *either* of two methods: either

   - [fork](https://help.github.com/en/articles/fork-a-repo) it,
     or
   - use it as a [template](https://help.github.com/en/articles/creating-a-repository-from-a-template).

   From here on, we assume your username is `${USER}` and the 
   working repository within that account is called `${WORK}`.

3. Execute

   ```sh
   git clone https://github.com/${USER}/${WORK}.git
   cd ./sca3s-harness
   source ./bin/conf.sh
   ```

   to clone and initialise the working repository,
   then configure the environment;
   for example, you should find that the environment variable
   `REPO_HOME`
   is set appropriately.

3. Perform various preparatory steps:

   1. Optionally,
      select the
      build context
      by setting the environment variable
      `CONTEXT`
      appropriately,
      e.g., via

      ```sh
      export CONTEXT="native"
      ```
  
      or just accept the default (per [`${REPO_HOME}/Makefile`](./Makefile)).

   2. Optionally, 
      select the
      board
      and
      target implementation (implying the driver and kernel)
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

      or just accept the default (per [`${REPO_HOME}/Makefile`](./Makefile)).

5. Develop a target implementation in the working repository:

   1. edit

      ```sh
      ${REPO_HOME}/src/sca3s/harness/kernel/${TARGET}/kernel.h
      ```

      to specify parameters of the implementation, 
      e.g., the block size,
      then

   2. edit

      ```sh
      ${REPO_HOME}/src/sca3s/harness/kernel/${TARGET}/kernel.c
      ```

      to complete the implementation itself, 
      e.g., the `kernel_enc` and/or `kernel_dec` functions,

   3. commit and push the result.

6. Either

   1. use the working repository  locally:
      use targets in the top-level `Makefile` to drive a set of
      common tasks, e.g.,

      | Command                   | Description
      | :------------------------ | :--------------------------------------------------------------- |
      | `make doc`                | build the [Doxygen](http://www.doxygen.nl)-based documentation   |
      | `make deps-fetch-harness` | fetch (i.e., download) the target implementation dependencies    |
      | `make deps-build-harness` | build                  the target implementation dependencies    |
      | `make      build-harness` | build                  the target implementation                 |
      | `make      clean`         | clean-up (e.g., remove everything built in `${REPO_HOME}/build`) |


   2. use the working repository remotely:
      go to
      [`sca3s.scarv.org`](https://sca3s.scarv.org),
      and either

      1. manually submit a job referencing the working repository,
         or
      2. activate
         [Continuous Integration (CI)](https://en.wikipedia.org/wiki/Continuous_integration)
         for the working repository, meaning a job will be submitted 
         automatically, e.g., per commit.

<!--- -------------------------------------------------------------------- --->

## Acknowledgements

This work has been supported in part by EPSRC via grant 
[EP/R012288/1](https://gow.epsrc.ukri.org/NGBOViewGrant.aspx?GrantRef=EP/R012288/1),
under the [RISE](http://www.ukrise.org) programme, and by the
[AWS Cloud Credits for Research](https://aws.amazon.com/research-credits)
program.

<!--- -------------------------------------------------------------------- --->
