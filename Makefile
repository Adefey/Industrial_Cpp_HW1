SHELL=/bin/bash #-e pipefail

all: format check build_lib build_app build_unit_test run_unit_test run_integral_test make_unit_test_report cleanup

format:
	./scripts/format.sh

check:
	./scripts/check.sh

build_lib:
	cd src_lib && \
	cmake CMakeLists.txt && \
	cmake --build .
	mv src_lib/libcalculator.a lib/

build_app:
	cd src_app && \
	cmake CMakeLists.txt && \
	cmake --build .
	mv src_app/Exe test/integral/

build_unit_test:
	cd test/unit && \
	cmake CMakeLists.txt && \
	cmake --build .

run_unit_test:
	cd test/unit && \
	valgrind ./UnitTest

run_integral_test:
	cd test/integral && \
	python integral_test.py

make_unit_test_report:
	lcov -t test/unit -o test/unit/coverage_report.info -c -d test/unit
	genhtml -o test/unit/coverage_report test/unit/coverage_report.info

cleanup:
	rm -r src_lib/CMakeFiles src_lib/Makefile src_lib/CMakeCache.txt src_lib/cmake_install.cmake
	rm -r src_app/CMakeFiles src_app/Makefile src_app/CMakeCache.txt src_app/cmake_install.cmake
	rm -r test/unit/CMakeFiles test/unit/Makefile test/unit/CMakeCache.txt test/unit/cmake_install.cmake test/unit/coverage_report.info
