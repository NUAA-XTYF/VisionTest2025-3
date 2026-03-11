add_executable(q06 q06.cpp)
target_link_libraries(q06 PRIVATE test_utils)
add_test(NAME q06_optional_variant COMMAND q06)
