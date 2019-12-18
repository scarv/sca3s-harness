# [SCA3S](https://github.com/scarv/sca3s): target implementation harness

<!--- -------------------------------------------------------------------- --->

[![Documentation](https://codedocs.xyz/scarv/sca3s-harness.svg)](https://codedocs.xyz/scarv/sca3s-harness)

<!--- -------------------------------------------------------------------- --->

*Acting as a component part of the wider
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

## Status

<!--- SCA3S shields -->
[![SCA3S acquire data](https://lab.scarv.org/api/shields/acquisition/scarv/sca3s-harness.svg?branch=master)](...)
[![SCA3S analyse data](https://lab.scarv.org/api/shields/analysis/scarv/sca3s-harness.svg?branch=master)](...)
<!--- SCA3S shields -->

<!--- -------------------------------------------------------------------- --->

## Organisation

```
├── bin                     - scripts (e.g., environment configuration)
├── build                   - working directory for build
└── src
    ├── docker              - source code for containers
    └── sca3s               - source code for SCA3S
        └── harness         - source code for SCA3S target implementation harness
            ├── board         - board  implementations
            ├── driver        - driver implementations
            ├── kernel        - kernel implementations
            └── share         - shared functionality
```

<!--- -------------------------------------------------------------------- --->

## Quickstart (with more detail in the [wiki](https://github.com/scarv/sca3s-harness/wiki))

1. Either

   1. provide a native build context by installing 
      associated pre-requisites, e.g.,

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

      and/or

   2. provide a Docker build context by installing 
      the 
      [Docker](https://www.docker.com)
      container platform.

2. Create a *copy* of the 
   [template repository](https://github.com/scarv/sca3s-harness)
   in your *own* account: we term this the working repository.
   Using the
   [GitHub](https://github.com)-based
   UI, 
   you can do so via *either* of two methods: either

   - [fork](https://help.github.com/en/articles/fork-a-repo) it,
     or
   - use it as a [template](https://help.github.com/en/articles/creating-a-repository-from-a-template).

   Either way, we assume
   `${REPO_WORK}`
   denotes a usable working repository URL from here on: 
   using the
   [GitHub](https://github.com)-based
   UI,
   you can copy-and-paste it (in HTTPS and SSH formats) via the button 
   labelled "clone or download".

3. Execute

   ```sh
   git clone ${REPO_WORK} ./sca3s-harness
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
  
      or just accept the default(s) per [`${REPO_HOME}/Makefile`](./Makefile).

   2. Optionally, 
      select the
      board
      and
      target implementation 
      types
      by setting the environment variables
      `BOARD`,
      and
      `KERNEL`,
      appropriately,
      e.g., via

      ```sh
      export BOARD="scale/lpc1313fbd48"
      export KERNEL="block"
      ```

      or just accept the default(s) per [`${REPO_HOME}/Makefile`](./Makefile).

5. Develop a target implementation in the working repository:

   1. edit

      ```sh
      ${REPO_HOME}/src/sca3s/harness/kernel/${KERNEL}/kernel_imp.h
      ```

      to specify parameters of the target implementation, 
      then

   2. edit

      ```sh
      ${REPO_HOME}/src/sca3s/harness/kernel/${KERNEL}/kernel_imp.c
      ```

      to complete the target implementation itself,

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
      | `make      clean-harness` | clean                  the target implementation                 |
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
         automatically; see below for a more detailed overview.

<!--- -------------------------------------------------------------------- --->

## Acknowledgements

This work has been supported in part 

- by EPSRC via grant 
  [EP/R012288/1](https://gow.epsrc.ukri.org/NGBOViewGrant.aspx?GrantRef=EP/R012288/1) (under the [RISE](https://www.ukrise.org) programme), 
  and 
- by the
  [AWS Cloud Credits for Research](https://aws.amazon.com/research-credits)
  programme.

<!--- -------------------------------------------------------------------- --->
