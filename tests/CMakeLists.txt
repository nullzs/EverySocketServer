project(test_units)

set(CMAKE_CXX_STANDARD 11)

aux_source_directory(. TEST_SRC)

add_executable(test_all ${TEST_SRC})

target_link_libraries(test_all frame_decoder_lib  static_unit_lib)