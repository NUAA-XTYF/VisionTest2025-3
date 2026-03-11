add_executable(q05 q05.cpp)
target_link_libraries(q05 PRIVATE test_utils)
add_test(NAME q05_structured_bindings COMMAND q05)
