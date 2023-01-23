
project(range_test)
cmake_minimum_required(VERSION 3.22)


find_package(PkgConfig REQUIRED)
pkg_check_modules(GTEST REQUIRED gtest )


set(SRC rtest.cpp)

add_executable(rangetest ${SRC})

enable_testing()

message("FOO ${GTEST_INCLUDE_DIRS}")
target_include_directories(rangetest PUBLIC .)
target_compile_definitions(rangetest PUBLIC "-DSELF_TEST" )
target_include_directories(rangetest PUBLIC ${GTEST_INCLUDE_DIRS})
target_link_libraries( rangetest ${GTEST_LDFLAGS}  )

# Test case Gtest

#add_executable(rangetest_test ${SRC} )

add_test(NAME rangetest_test   COMMAND  rangetest )
set_tests_properties(rangetest_test PROPERTIES TIMEOUT 5)
