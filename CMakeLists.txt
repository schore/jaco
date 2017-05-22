cmake_minimum_required (VERSION 2.6)
project(compiler)
#Version Number
set (Compiler_Version_Major 0)
set (Compiler_Version_Minor 0)


#Global Options

option (COMP_DEBUG "Debug Mode on" ON)
option (BUILD_TEST "Build Testing" ON)

#generate header file
configure_file (
  "${PROJECT_SOURCE_DIR}/src/include/global_config.h.in"
  "${PROJECT_BINARY_DIR}/include/global_config.h"
  )

if (COMP_DEBUG)
  set(CMAKE_BUILD_TYPE Debug)
endif()

include_directories("${PROJECT_SOURCE_DIR}/src/include")
include_directories("${PROJECT_SOURCE_DIR}/external/GSL/include")
add_subdirectory(src)

add_executable(compiler ./src/main.cpp)
target_link_libraries(compiler compilerLib)

add_library(compilerLib ${SOURCE})
#test framework
#include(CTest)


# does the application run
#add_test (TutorialRuns tutorial 25)
find_package(GTest REQUIRED)
enable_testing()
include_directories(${GTEST_INCLUDE_DIRS})

add_custom_target(testcode)


macro(Mytest testname src)
  if (BUILD_TEST)
    add_executable(${testname} EXCLUDE_FROM_ALL "${src}")
    target_link_libraries(${testname} pthread)
    target_link_libraries(${testname} ${GTEST_BOTH_LIBRARIES})
    target_link_libraries(${testname} compilerLib)
    add_dependencies(testcode  ${testname}) 
    add_test(${testname} ${testname})
  endif()
endmacro(Mytest)

Mytest(Tokenizer "test/tokenizer/tokenizerTest.cpp")
Mytest(TokenInt  "test/tokenizer/tokenIntTest.cpp")
Mytest(TokenDouble "test/tokenizer/tokenDoubleTest.cpp")
Mytest(TokenOperator "test/tokenizer/tokenOperatorTest.cpp")
Mytest(TokenKeyword "test/tokenizer/keywordidentifier.cpp")
Mytest(ParserFunc "test/parser/functionTest.cpp")
Mytest(SymbolTable "test/symboltable.cpp")
Mytest(FunctionElement "test/parser/functionCustomElement.cpp")


# add a target to generate API documentation with Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
add_custom_target(doc
${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
COMMENT "Generating API documentation with Doxygen" VERBATIM
)
endif(DOXYGEN_FOUND)

add_custom_target(release)
add_dependencies(release doc compiler testcode)
