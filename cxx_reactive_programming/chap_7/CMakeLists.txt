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

add_executable(from_containers from_containers.cpp)
target_include_directories(from_containers PUBLIC rxcpp )
target_link_libraries(from_containers rxcpp )


add_executable(from_scratch from_scratch.cpp)
target_include_directories(from_scratch PUBLIC rxcpp )
target_link_libraries(from_scratch rxcpp )


add_executable(from_scratch2 from_scratch2.cpp)
target_include_directories(from_scratch2 PUBLIC rxcpp )
target_link_libraries(from_scratch2 rxcpp )


add_executable(concat concat.cpp)
target_include_directories(concat PUBLIC rxcpp )
target_link_libraries(concat rxcpp )

add_executable(combine_latest combine_latest.cpp)
target_include_directories(combine_latest PUBLIC rxcpp )
target_link_libraries(combine_latest rxcpp )


add_executable(average average.cpp)
target_include_directories(average PUBLIC rxcpp )
target_link_libraries(average rxcpp )


add_executable(thread_example thread_example.cpp)
target_include_directories(thread_example PUBLIC rxcpp )
target_link_libraries(thread_example rxcpp pthread)

add_executable(thread_example2 thread_example2.cpp)
target_include_directories(thread_example2 PUBLIC rxcpp )
target_link_libraries(thread_example2 rxcpp pthread)
