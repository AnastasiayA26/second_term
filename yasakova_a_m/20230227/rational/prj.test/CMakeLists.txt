add_executable(test test.cpp)
target_link_libraries(test rational doctest::doctest)
add_test(NAME rational_test COMMAND test)