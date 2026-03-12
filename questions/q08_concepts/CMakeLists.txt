add_executable(q08 q08.cpp)
target_link_libraries(q08 PRIVATE test_utils)
add_test(NAME q08_concepts COMMAND q08)
