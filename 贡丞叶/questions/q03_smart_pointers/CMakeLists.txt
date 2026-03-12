add_executable(q03 q03.cpp)
target_link_libraries(q03 PRIVATE test_utils)
add_test(NAME q03_smart_pointers COMMAND q03)
