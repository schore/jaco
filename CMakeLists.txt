cmake_minimum_required (VERSION 2.6)
project(compiler)
#Version Number
set (Compiler_Version_Major 0)
set (Compiler_Version_Minor 0)


#Global Options

option (DEBUG "Debug Mode on" ON)
option (BUILD_TEST "Build Testing" ON)

#generate header file
configure_file (
  "${PROJECT_SOURCE_DIR}/src/include/global_config.h.in"
  "${PROJECT_BINARY_DIR}/include/global_config.h"
  )

include_directories("${PROJECT_SOURCE_DIR}/src/include")
add_subdirectory(src)

add_executable(compiler ${SOURCE})
#test framework
#include(CTest)


# does the application run
#add_test (TutorialRuns tutorial 25)

if (BUILD_TEST)
    enable_testing()
    add_subdirectory(test)
    add_executable(tokenizer_test
      ${TEST_SRC_TOKEN})
    target_link_libraries(tokenizer_test
        pthread)
    target_link_libraries(tokenizer_test
        gmock
        gmock_main)
    target_link_libraries(tokenizer_test
        gtest
        gtest_main)
    add_test(tokenizer-test tokenizer_test)
endif()
