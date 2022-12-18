#!/usr/bin/env bash

CODE_FILES="./src_app/*.cpp ./src_lib/*.cpp ./include/*.hpp ./test/unit/*.cpp"
CODE_FILES_PYTHON="./test/integral/*.py"

set -e pipefail

cppcheck --enable=all --suppress=missingIncludeSystem $CODE_FILES
clang-tidy $CODE_FILES -extra-arg=-std=c++2a -- -I./include
cpplint --extensions=cpp,hpp --filter=-whitespace/indent,-whitespace/comments,-runtime/references $CODE_FILES
pylint $CODE_FILES_PYTHON --disable=missing-module-docstring,missing-function-docstring,missing-class-docstring
