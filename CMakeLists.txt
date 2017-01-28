cmake_minimum_required (VERSION 2.6)
project(compiler)
#Version Number
set (Compiler_Version_Major 0)
set (Compiler_Version_Minor 0)


#Global Options

option (DEBUG "Debug Mode on" ON)

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

macro (do_test arg result)
  add_test (TutorialComp${arg} tutorial ${arg})
  set_tests_properties (TutorialComp${arg}
    PROPERTIES PASS_REGULAR_EXPRESSION ${result})
endmacro (do_test)

#do_test(25 "25 is 5")
#do_test(-25 "-25 is 0")
