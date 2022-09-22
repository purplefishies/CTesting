project(rxcpptest)
cmake_minimum_required(VERSION 3.22)

# find_package(rxcpp REQUIRED)
#find_library(RxCpp_Lib NAMES libRxCpp.so PATHS ${RxCpp_Lib_PATH})
#include(FindPackageHandleStandardArgs)

find_package(rxcpp REQUIRED)
MESSAGE( STATUS "rxcpp_INCLUDE_DIRS: " ${rxcpp_INCLUDE_DIR} )

find_package(range-v3 REQUIRED)
MESSAGE( STATUS "range-v3_INCLUDE_DIRS: " ${range-v3_INCLUDE_DIR} )
get_target_property(FOO range-v3-concepts INTERFACE_INCLUDE_DIRECTORIES )
message( "${FOO}" )

# get_cmake_property(_variableNames VARIABLES)
# list (SORT _variableNames)
# foreach (_variableName ${_variableNames})
#     message(STATUS "${_variableName}=${${_variableName}}")
# endforeach()

set(SOURCE_FILES main.cpp)
add_executable(example ${SOURCE_FILES})
target_include_directories(example PUBLIC rxcpp range-v3)
target_link_libraries(example rxcpp range-v3)
# get_property(dirs TARGET example  PROPERTY INCLUDE_DIRECTORIES)
# message("BAR ${dirs}")

