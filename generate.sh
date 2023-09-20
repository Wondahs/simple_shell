#!/usr/bin/env bash

set -e

SCRIPTDIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOTDIR="$(cd "${SCRIPTDIR}/.." && pwd)"

set -x

# Explanation text
echo "# Contributors to the project" > "${ROOTDIR}/AUTHORS"
echo "# This file lists all contributors to the repository." >> "${ROOTDIR}/AUTHORS"
echo "# See hack/generate-authors.sh to make modifications." >> "${ROOTDIR}/AUTHORS"
echo "" >> "${ROOTDIR}/AUTHORS"

# List of contributors
git log --format='%aN <%aE>' | LC_ALL=C.UTF-8 sort -uf >> "${ROOTDIR}/AUTHORS"

set +x
