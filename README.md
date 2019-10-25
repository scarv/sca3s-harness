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

## Quickstart

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
      `DRIVER`,
      appropriately,
      e.g., via

      ```sh
      export BOARD="scale/lpc1313fbd48"
      export DRIVER="block"
      ```

      or just accept the default(s) per [`${REPO_HOME}/Makefile`](./Makefile).

5. Develop a target implementation in the working repository:

   1. edit

      ```sh
      ${REPO_HOME}/src/sca3s/harness/kernel/${DRIVER}/kernel.h
      ```

      to specify parameters of the target implementation, 
      then

   2. edit

      ```sh
      ${REPO_HOME}/src/sca3s/harness/kernel/${DRIVER}/kernel.c
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
      | `make update`             | update working repository to match template repository           |
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

## Notes

- The 
  `CONTEXT`
  environment variable specifies the
  build context
  within which the build process is executed:

  | Context              | Description                                                                     |
  | :------------------- | :------------------------------------------------------------------------------ |
  | `native`             | The default, native build context                                               |
  | `docker`             | A containerised build context, offered by an architecture-specific Docker image |

  Note that:

  - Up to a point, it is reasonable to view this mechanism as somewhat
    over-engineered.  In a sense it is, but, equally, there *are* some
    important motivations for supporting it.
    For example, a pre-built, i.e., containerised, tool-chain will be
    uniform across both local and remote use-cases outlined above: if 
    you can build a target implementation locally via this mechanism, 
    you can be confident it will *also* build remotely.

  - Each architecture-specific Docker image is built using 
    the content housed in
    [`${REPO_HOME}/src/docker`](./src/docker).
    However,
    *there is no need to do this manually*: 
    a pre-built image can (and will) be pulled from
    [Docker Hub](https://cloud.docker.com/u/scarv)
    by the build process as needed.

- The 
  `BOARD`
  environment variable specifies the
  board 
  type:

  | Architecture         | Description                                                                     |
  | :------------------- | :------------------------------------------------------------------------------ |
  | `scale/lpc1313fbd48` | An ARM Cortex-M3 [SCALE](https://github.com/danpage/scale)                      |


- The 
  `DRIVER`
  environment variable specifies the
  target implementation 
  type:

  | Driver               | Kernel               | Description                                                                                                                                         |
  | :------------------- | :--------------------| :-------------------------------------------------------------------------------------------------------------------------------------------------- |
  | `block`              | `generic/enc`        | A   generic                                                           [block cipher](https://en.wikipedia.org/wiki/Block_cipher) in encryption mode |
  | `block`              | `generic/dec`        | A   generic                                                           [block cipher](https://en.wikipedia.org/wiki/Block_cipher) in decryption mode |
  | `block`              |     `aes/enc`        | The [AES](https://en.wikipedia.org/wiki/Advanced_Encryption_Standard) [block cipher](https://en.wikipedia.org/wiki/Block_cipher) in encryption mode |
  | `block`              |     `aes/dec`        | The [AES](https://en.wikipedia.org/wiki/Advanced_Encryption_Standard) [block cipher](https://en.wikipedia.org/wiki/Block_cipher) in decryption mode |

- Each 
  board
  requires several configuration files:

  1. `${REPO_HOME}/src/sca3s/harness/board/${BOARD}/Dockerfile.in`,
     which specifies a build script                        for the Docker build context,
  2. `${REPO_HOME}/src/sca3s/harness/board/${BOARD}/conf.mk_docker`,
     which specifies configuration, to the build system, about the Docker build context,
  3. `${REPO_HOME}/src/sca3s/harness/board/${BOARD}/conf.mk_target`
     which specifies configuration, to the build system, about the target implementation,
  4. `${REPO_HOME}/src/sca3s/harness/board/${BOARD}/conf.mk_deps`
     which specifies configuration, to the build system, about the target implementation dependencies.

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
