set(CTEST_SOURCE_DIRECTORY "/source")
set(CTEST_BINARY_DIRECTORY "/binary")

site_name(CTEST_SITE)
set(CTEST_BUILD_NAME "$ENV{BUILD_NAME}")

set(CTEST_CUSTOM_MAXIMUM_NUMBER_OF_WARNINGS 1000)
set(CTEST_CMAKE_GENERATOR "Ninja")

set(CTEST_COVERAGE_COMMAND "$ENV{CTEST_COVERAGE_COMMAND}")
set(CTEST_MEMORYCHECK_COMMAND "$ENV{CTEST_MEMORYCHECK_COMMAND}")
set(CTEST_MEMORYCHECK_TYPE "$ENV{CTEST_MEMORYCHECK_TYPE}")

include(ProcessorCount)
ProcessorCount(nproc)
if(NOT nproc EQUAL 0)
  set(test_args PARALLEL_LEVEL ${nproc})
endif()

ctest_start("Experimental")

if(EXISTS "/toolchain.cmake")
  ctest_configure(OPTIONS "-DCMAKE_TOOLCHAIN_FILE:FILEPATH=/toolchain.cmake")
else()
  ctest_configure()
endif()

ctest_build()

ctest_test(${test_args})

if(CTEST_COVERAGE_COMMAND)
  ctest_coverage()
endif()

if(CTEST_MEMORYCHECK_COMMAND OR CTEST_MEMORYCHECK_TYPE)
  ctest_memcheck(${test_args})
endif()

#ctest_submit()
