cmake_minimum_required(VERSION 3.2)

set(INCLUDE_DIRS . )

find_package(CMocka REQUIRED)

add_executable(example2 example2.c )
target_include_directories(example2 PUBLIC  ${CMOCKA_INCLUDE_DIR})
target_link_libraries(example2 ${CMOCKA_LIBRARY})

add_test(example2  ${CMAKE_CURRENT_BINARY_DIR}/example2 )

