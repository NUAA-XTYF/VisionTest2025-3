add_executable(q09 q09.cpp)
target_link_libraries(q09 PRIVATE test_utils)
add_test(NAME q09_modern_class COMMAND q09)
