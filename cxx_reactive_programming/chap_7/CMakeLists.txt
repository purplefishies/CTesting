project(example)

cmake_minimum_required(VERSION 3.22)

find_package(rxcpp REQUIRED)

set(SRC example.cpp)
MESSAGE( STATUS "rxcpp_INCLUDE_DIRS: " ${rxcpp_INCLUDE_DIR} )


add_executable(example ${SRC})
target_include_directories(example PUBLIC rxcpp )
target_link_libraries(example rxcpp )

add_executable(example2 example2.cpp)
target_include_directories(example2 PUBLIC rxcpp )
target_link_libraries(example2 rxcpp )
