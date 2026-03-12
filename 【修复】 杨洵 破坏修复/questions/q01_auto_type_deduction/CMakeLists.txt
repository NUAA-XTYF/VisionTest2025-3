add_executable(q01 q01.cpp)
target_link_libraries(q01 PRIVATE test_utils)
add_test(NAME q01_auto_type_deduction COMMAND q01)
