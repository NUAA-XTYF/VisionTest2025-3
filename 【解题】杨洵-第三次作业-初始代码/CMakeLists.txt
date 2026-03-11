cmake_minimum_required(VERSION 3.20)
project(ModernCppQuestions CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()

add_subdirectory(lib/test_utils)
add_subdirectory(questions)
