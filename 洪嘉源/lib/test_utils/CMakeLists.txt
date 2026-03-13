add_library(test_utils INTERFACE)
target_include_directories(test_utils INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(test_utils INTERFACE cxx_std_20)
