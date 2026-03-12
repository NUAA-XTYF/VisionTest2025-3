add_executable(q07 q07.cpp)
target_link_libraries(q07 PRIVATE test_utils)
add_test(NAME q07_constexpr COMMAND q07)
