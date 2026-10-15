#!/bin/bash

# SPDX-FileCopyrightText: Copyright 2026 Rogier van Dalen
#
# SPDX-License-Identifier: Apache-2.0

# Run clang-tidy (configured in .clang-tidy and test/.clang-tidy) on each
# header and source file, or on the files given as arguments.
#
# compile_commands.json has no entries for the headers in include/, so
# clang-tidy would borrow the command for a test file and check that instead.
# Instead, pass the compiler flags explicitly, with the include directories of
# the dependencies that Bazel fetches.
#
# Files are checked in parallel, but the output for each file is shown
# together.
# All files are checked even if some fail.

set -euo pipefail

cd "$(dirname "$0")/.."

# Make sure the dependencies of the library and the tests are available.
bazel fetch //...
external="$(bazel info output_base)/external"

flags=(-xc++ -std=c++17 -Iinclude)
for directory in "${external}"/boost.*+/include; do
    flags+=(-isystem "${directory}")
done
# On macOS, a clang-tidy that is not Apple's needs to be told where the
# standard library is.
if command -v xcrun >/dev/null; then
    flags+=(-isysroot "$(xcrun --show-sdk-path)")
fi

if [[ $# -gt 0 ]]; then
    printf '%s\n' "$@"
else
    find include test -name '*.hpp' -o -name '*.cpp' | sort
fi |
    # Collect the output for each file, and print it in one go.
    xargs -P "$(getconf _NPROCESSORS_ONLN)" -I {} bash -c '
        output=$(clang-tidy --quiet "$0" -- "${@}" 2>&1) && status=0 || status=$?
        if [[ -n ${output} ]]; then printf "%s\n" "${output}"; fi
        exit ${status}' {} "${flags[@]}"
