# [`lab.scarv.org`](https://github.com/scarv/lab.scarv.org): target implementation

<!--- -------------------------------------------------------------------- --->

[![Build Status](https://travis-ci.com/scarv/lab-target.svg)](https://travis-ci.com/scarv/lab-target)
[![Documentation](https://codedocs.xyz/scarv/lab-target.svg)](https://codedocs.xyz/scarv/lab-target)

<!--- -------------------------------------------------------------------- --->

*Acting as a component part of the
[SCARV](https://www.scarv.org)
project,
`lab.scarv.org` is a collection of resources that support the
development and analysis of cryptographic implementations wrt.
[side-channel attack](https://en.wikipedia.org/wiki/Side-channel_attack):
it places particular emphasis on analogue side-channels (e.g.,
power and EM) stemming from
[RISC-V](https://riscv.org)-based
platforms.
The main
[repository](https://github.com/scarv/lab.scarv.org)
acts as a general container for associated resources;
this specific submodule houses
a framework within which target implementations are developed.*

<!--- -------------------------------------------------------------------- --->

## Organisation

```
├── bin         - scripts (e.g., environment configuration)
├── build       - working directory for build
└── src         - source code
    ├── device    - device implementations
    ├── driver    - driver implementations
    ├── kernel    - kernel implementations
    └── share     - shared functionality
```

<!--- -------------------------------------------------------------------- --->

## Quickstart

1. The main `lab.scarv.org`
   [repository](https://github.com/scarv/lab.scarv.org)
   houses some overarching documentation, which offers some
   context and explanation: it *might* be sensible to start
   by reading that.

2. Install any associated pre-requisites, e.g.,

   - a device-specific compiler and programming tool-chain,
     e.g., suitable versions of
     [GCC](https://gcc.gnu.org)
     and
     [OpenOCD](http://openocd.org),
   - the
     [Doxygen](http://www.doxygen.nl)
     documentation generation system.

3. Go to the 
   [GitHub](https://github.com)-hosted
   repository
   [web-page](https://github.com/scarv/lab-target),
   and create a
   [fork](https://guides.github.com/activities/forking) 
   of it: doing so will create a copy of the repository in your *own* 
   account, the username for which we will assume is `${USER}`.

4. Execute

   ```sh
   git clone https://github.com/${USER}/lab-target.git
   cd ./lab-target
   source ./bin/conf.sh
   ```

   to clone and initialise the *forked* repository,
   then configure the environment;
   for example, you should find that the environment variable
   `REPO_HOME`
   is set appropriately.

5. Select the device and target implementation (implying the driver 
   and kernel) types by setting the environment variables
   `DEVICE`
   and
   `TARGET`
   appropriately, 
   e.g., via

   ```
   export DEVICE="scale/lpc1313fbd48"
   export TARGET="block"
   ```

6. Produce the target implementation in the *forked* repository:

   1. edit

      ```
      ${REPO_HOME}/src/kernel/${TARGET}/kernel.c
      ```

      to specify parameters of the implementation, 
      e.g., the block size,
      then

   2. edit

      ```
      ${REPO_HOME}/src/kernel/${TARGET}/kernel.c
      ```

      to complete the implementation itself, 
      e.g., the `kernel_enc` and/or `kernel_dec` functions,

   3. commit and push the result.

7. Either

   1. use the *forked* repository remotely:
      go to 
      [lab.scarv.org](https://lab.scarv.org),
      and submit a job referencing the forked repository, i.e.,

      ```sh
      https://github.com/${USER}/lab-target.git
      ```

      in order to acquire an associated trace set,
      or

   2. use the *forked* repository  locally:
      use targets in the top-level `Makefile` to drive a set of
      common tasks, e.g.,

      - execute

        ```sh
        make doc
        ```

        to build the documentation,

      - execute

        ```sh
        make build
        ```

        to build the target implementation,

      - execute

        ```sh
        make program
        ```

        to program the device (assuming it is attached) with the 
        target implementation.

      - execute

        ```sh
        make clean
        ```

        to clean-up
        (e.g., remove everything built in `${REPO_HOME}/build`).

<!--- -------------------------------------------------------------------- --->

## Acknowledgements

This work has been supported in part by EPSRC via grant 
[EP/R012288/1](https://gow.epsrc.ukri.org/NGBOViewGrant.aspx?GrantRef=EP/R012288/1),
under the [RISE](http://www.ukrise.org) programme.

<!--- -------------------------------------------------------------------- --->
