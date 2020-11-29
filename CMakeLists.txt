cmake_minimum_required(VERSION 3.13)
project(EverySocketServer)

set(CMAKE_CXX_STANDARD 11)

include(ExportHeader.cmake)
add_subdirectory(src)

add_executable(ESServer every_socket_server.cpp)

target_link_libraries(ESServer static_unit_lib log_lib)
