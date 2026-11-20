#!/bin/sh
set -eu

# Usage: CC=clang ./compile.sh -g -O0
project_dir=$(CDPATH='' cd -- "$(dirname -- "$0")" && pwd -P)
build_dir=$(mktemp -d "$project_dir/.vx-build.XXXXXX")
trap 'rm -f -- "$build_dir/vx"; rmdir -- "$build_dir"' EXIT
trap 'exit 1' HUP INT TERM

# Keep the previous executable until the new build is ready.
"${CC:-gcc}" -Wall -Wextra -pedantic -I "$project_dir/include" \
    "$project_dir/src/main.c" "$project_dir/src/source.c" \
    "$@" -o "$build_dir/vx"

if [ ! -f "$build_dir/vx" ] || [ ! -x "$build_dir/vx" ]; then
    printf '%s\n' 'compile.sh: the compiler did not produce an executable.' >&2
    exit 1
fi

mv -f -- "$build_dir/vx" "$project_dir/"
