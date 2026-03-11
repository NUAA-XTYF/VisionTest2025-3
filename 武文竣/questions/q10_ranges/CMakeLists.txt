add_executable(q10 q10.cpp)
target_link_libraries(q10 PRIVATE test_utils)
add_test(NAME q10_ranges COMMAND q10)
