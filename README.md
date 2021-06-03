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
SCA3A is, more specifically, pitched as offering
"side-channel analysis as a service":
it allows users to acquire and analyse side-channel data-sets which stem 
from execution of their implementation, without (necessarily) owning or 
operating the associated infrastructure.
Mirroring the goals of SCARV, it places particular emphasis on analogue 
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
├── extern                  - external resources (e.g., submodules)
│   └── wiki                  - submodule: scarv/sca3s-harness.wiki
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

2. Follow the recommended
   [workflow](https://github.com/scarv/sca3s-harness/wiki/Workflow),
   which, roughly speaking, involves the following steps:

   1. enroll (via the [SCA3S web-based interface](https://sca3s.scarv.org)),
   2. create user repository,
   3. clone  user repository,
   4. develop target implementation,
   5. build   target implementation,
   6. commit  target implementation,
   7. use     target implementation.

<!--- -------------------------------------------------------------------- --->

## Questions?

- read the
  [wiki](https://github.com/scarv/sca3s-harness/wiki),
- raise an
  [issue](https://github.com/scarv/sca3s-harness/issues),
- raise a
  [pull request](https://github.com/scarv/sca3s-harness/pulls),
- drop us an 
  [email](mailto:sca3s@scarv.org).

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
