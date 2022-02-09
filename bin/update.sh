#!/bin/bash

# Copyright (C) 2019 SCARV project <info@scarv.org>
#
# Use of this source code is restricted per the MIT license, a copy of which
# can be found at https://opensource.org/licenses/MIT (or should be included
# as LICENSE.txt within the associated archive or repository).

if [ -z ${REPO_HOME} ] ; then
  echo "REPO_HOME environment variable undefined: aborting" ; exit
fi

CURRENT=$(git -C ${REPO_HOME} branch --show-current)

while [[ ${#} -gt 0 ]] ; do
  case ${1} in
    -a|--all)
      for BRANCH in $(git -C ${REPO_HOME} branch --format '%(refname:short)') ; do
        git -C ${REPO_HOME} checkout ${BRANCH}
        git -C ${REPO_HOME} pull --allow-unrelated-histories https://github.com/scarv/sca3s-harness.git sca3s
      done
      shift
      ;;
    -c|--current)
        git -C ${REPO_HOME} pull --allow-unrelated-histories https://github.com/scarv/sca3s-harness.git sca3s
      shift
      ;;
  esac
done

git checkout ${CURRENT}
