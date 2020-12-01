cmake_minimum_required(VERSION 3.13)
project(EverySocketServer)

set(CMAKE_CXX_STANDARD 11)

if (WIN32)
    add_definitions(-D_WIN32_WINNT=0x0601)
endif ()

include(ExportHeader.cmake)
add_subdirectory(src)

add_executable(ESServer every_socket_server.cpp)

target_link_libraries(ESServer static_unit_lib init_lib
        log_lib config_lib listeners_lib socket_lib)

if (UNIX)
    target_link_libraries(ESServer pthread)
elseif (WIN32)
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        target_link_libraries(ESServer ws2_32 wsock32)
    endif ()
endif ()