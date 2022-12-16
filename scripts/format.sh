#!/usr/bin/env bash

CODE_FILES="./src_app/*.cpp ./src_lib/*.cpp ./include/*.hpp ./test/unit/*.cpp"
CODE_FILES_PYTHON="./test/integral/*.py"

set -e pipefail

clang-format -i $CODE_FILES
autopep8 --in-place $CODE_FILES_PYTHON
