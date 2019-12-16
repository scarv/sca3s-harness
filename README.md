# [SCA3S](https://github.com/scarv/sca3s): target implementation harness

<!--- -------------------------------------------------------------------- --->

[![Documentation](https://codedocs.xyz/scarv/sca3s-harness.svg)](https://codedocs.xyz/scarv/sca3s-harness)
<!--- SCA3S shields -->
<!--- SCA3S shields -->

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

## Notes

- Not all targets in the top-level `Makefile` are listed above.  Extra
  cases include the following, which, for example, relate to management 
  of the working repository:

  - `repo-merge`
    merges changes in the template repository into working repository;
    doing so is important, in so far as a "stale" working repository
    may be rejected when used via
    [`sca3s.scarv.org`](https://sca3s.scarv.org).
    
  - `repo-install`
    performs any (post-clone) installation of content into the working
    repository.  An example is the pre-commit
    [hook](https://git-scm.com/book/en/v2/Customizing-Git-Git-Hooks)
    (i.e., `${REPO_HOME}/.git/hooks/pre-commit`) which updates
    `${REPO_HOME}/README.md`
    to ensure any status icons (or [shields](https://shields.io)) are
    displayed for the correct branch in the working repository; doing
    so is important, for example, to accurately reflect the working 
    repository status when used via
    [`sca3s.scarv.org`](https://sca3s.scarv.org).

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

  - Using the 
    `native`
    build context implies
    a) the tool-chain,
       and
    b) any software dependencies (e.g., libraries)
    need to be installed manually.
    Building a target implementation is therefore achived by executing

    ```sh
    make CONTEXT="native"      clean-harness
    make CONTEXT="native" deps-fetch-harness
    make CONTEXT="native" deps-build-harness
    make CONTEXT="native"      build-harness
    ```

    assuming your `PATH` environment variable captures the tool-chain:
    the second and third steps will fetch (or download) and build the
    software dependencies for you.

  - Using the 
    `docker`
    build context implies
    a) the tool-chain,
       and
    b) any software dependencies (e.g., libraries)
    are installed within the associated container.
    Building a target implementation is therefore achived by executing

    ```sh
    make CONTEXT="docker"      clean-harness
    make CONTEXT="docker"      build-harness
    ```

    alone.

- The 
  `BOARD`
  environment variable specifies the
  board 
  type:

  | `BOARD`                                                                     | Description                                                                                                                                         |
  | :-------------------------------------------------------------------------- | :-------------------------------------------------------------------------------------------------------------------------------------------------- |
  | `native`                                                                    | A hardware-agnostic, "simulated" board allowing a natively executable target implementation (e.g., for testing and debugging purposes)              |
  | `scale/atmega328p`                                                          | An [SCALE](https://github.com/danpage/scale-hw/target/atmega328p)      Atmel [AVR       ](https://en.wikipedia.org/wiki/AVR_microcontrollers) board |
  | `scale/lpc1114fn28`                                                         | An [SCALE](https://github.com/danpage/scale-hw/target/lpc1114fn28)     ARM   [Cortex-M0 ](https://en.wikipedia.org/wiki/ARM_Cortex-M)         board |
  | `scale/lpc1313fbd48`                                                        | An [SCALE](https://github.com/danpage/scale-hw/target/lpc1313fbd48)    ARM   [Cortex-M3 ](https://en.wikipedia.org/wiki/ARM_Cortex-M)         board |
  | `scale/lpc812m101jdh16`                                                     | An [SCALE](https://github.com/danpage/scale-hw/target/lpc812m101jdh16) ARM   [Cortex-M0+](https://en.wikipedia.org/wiki/ARM_Cortex-M)         board |

- The 
  `KERNEL`
  environment variable specifies the
  target implementation 
  type:

  | `KERNEL`                | `KERNEL_NAMEOF`         | `KERNEL_MODEOF`         | Description                                                                                                                                         |
  | :---------------------- | :---------------------- | :---------------------- | :-------------------------------------------------------------------------------------------------------------------------------------------------- |
  | `generic`               |                         |                         | A   generic                                                           function                                                                      |
  | `block`                 | `generic`               | `KERNEL_MODEOF_ENC`     | A   generic                                                           [block cipher](https://en.wikipedia.org/wiki/Block_cipher) in encryption mode |
  | `block`                 | `generic`               | `KERNEL_MODEOF_DEC`     | A   generic                                                           [block cipher](https://en.wikipedia.org/wiki/Block_cipher) in decryption mode |
  | `block`                 | `aes`                   | `KERNEL_MODEOF_ENC`     | The [AES](https://en.wikipedia.org/wiki/Advanced_Encryption_Standard) [block cipher](https://en.wikipedia.org/wiki/Block_cipher) in encryption mode |
  | `block`                 | `aes`                   | `KERNEL_MODEOF_DEC`     | The [AES](https://en.wikipedia.org/wiki/Advanced_Encryption_Standard) [block cipher](https://en.wikipedia.org/wiki/Block_cipher) in decryption mode |

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

- The file
  `${REPO_HOME}/sca3s.json`
  configures application of 
  [Continuous Integration (CI)](https://en.wikipedia.org/wiki/Continuous_integration)
  per the above.

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
