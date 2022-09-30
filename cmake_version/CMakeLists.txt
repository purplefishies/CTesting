project(gitstuff)
cmake_minimum_required(VERSION 3.22)
include(version.cmake)




# Add a custom command that produces version.cpp, plus
# a dummy output that's not actually produced, in order
# to force version.cmake to always be re-run before the build
ADD_CUSTOM_COMMAND(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/version.cpp
           ${CMAKE_CURRENT_BINARY_DIR}/_version.cpp
    COMMAND ${CMAKE_COMMAND} -P
            ${CMAKE_CURRENT_SOURCE_DIR}/version.cmake)

add_executable(tmp tmp.cpp ${CMAKE_CURRENT_BINARY_DIR}/version.cpp)
