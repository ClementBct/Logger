#!/usr/bin/env bash

set -e

find Logger \( -iname "*.h" -o -iname "*.c" -o -iname "*.hpp" -o -iname "*.cpp" \) -exec clang-format -style=file -i {} \;