cmake_minimum_required(VERSION 3.9)
project(Test)

include(CTestUseLaunchers)
enable_testing()

add_executable(main main.c)

add_test(NAME main COMMAND main)
set_tests_properties(main PROPERTIES PASS_REGULAR_EXPRESSION "hello")
