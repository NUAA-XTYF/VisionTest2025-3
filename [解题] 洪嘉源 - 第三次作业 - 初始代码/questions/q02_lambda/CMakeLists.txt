add_executable(q02 q02.cpp)
target_link_libraries(q02 PRIVATE test_utils)
add_test(NAME q02_lambda COMMAND q02)
