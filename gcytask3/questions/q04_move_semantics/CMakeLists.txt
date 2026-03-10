add_executable(q04 q04.cpp)
target_link_libraries(q04 PRIVATE test_utils)
add_test(NAME q04_move_semantics COMMAND q04)
