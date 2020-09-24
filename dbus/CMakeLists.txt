

cmake_minimum_required(VERSION 3.2)

include_directories(${INCLUDE_DIRS})

find_library(SYSTEMD_LIBRARY NAMED systemd PATHS /lib/x86_64-linux-gnu/)


add_executable(wait_for_signal wait_for_signal.c)
target_link_libraries(wait_for_signal ${SYSTEMD_LIBRARY})



