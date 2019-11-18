cmake_minimum_required (VERSION 3.8)
project(compiler VERSION 0.0.1)
#Version Number
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )


#Global Options

option (COMP_DEBUG "Debug Mode on" ON)
option (BUILD_TEST "Build Testing" ON)

# set (CMAKE_CXX_FLAGS "-Wall -fsanitize=address")



add_executable(compiler src/main.cpp)
target_link_libraries(compiler compilerLib)


file(GLOB_RECURSE SRCS src/*/*.cpp)
file(GLOB_RECURSE HEADER src/include/*)

add_library(compilerLib SHARED ${SRCS})
target_include_directories(compilerLib
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/include>
  PUBLIC $<INSTALL_INTERFACE:include/mylib>)
set_target_properties(compilerLib PROPERTIES PUBLIC_HEADER "${HEADER}")

#test framework
#include(CTest)


install(TARGETS compilerLib
        EXPORT compiler
        # LIBRARY DESTINATION lib
        # ARCHIVE DESTINATION lib
        # RUNTIME DESTINATION bin
        PUBLIC_HEADER DESTINATION include/foo
        )



install(EXPORT compiler
        # FILE MyLibTargets.cmake
        # NAMESPACE MyLib::
        DESTINATION lib/cmake/MyLib
         )


# does the application run
#add_test (TutorialRuns tutorial 25)
find_package(GTest REQUIRED)
enable_testing()
include(CTest)
set(BUILD_TESTING On)

add_custom_target(testcode)


macro(Mytest testname src)
  if (BUILD_TEST)
    add_executable(${testname} EXCLUDE_FROM_ALL "${src}")
    target_link_libraries(${testname} gtest gtest_main)
    target_link_libraries(${testname} compilerLib)
    add_dependencies(testcode  ${testname})
    add_custom_command(TARGET ${testname}
      POST_BUILD
      COMMAND ${testname})
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

add_custom_target(check)
add_dependencies(check testcode )

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

add_custom_target(staticAnalysies)

file(GLOB_RECURSE ana2 "src/*.cpp" )
foreach(SRCFILE ${ana2})
  add_custom_command(
    TARGET staticAnalysies
    COMMAND  clang-tidy
    ${SRCFILE}
    -header-filter=.*,-${CMAKE_CURRENT_SOURCE_DIR}/external/GSL/include/*
    -warnings-as-errors=*
    -checks=-*,cppcoreguidelines*,clang-analyzer*
    --
    -I${CMAKE_CURRENT_SOURCE_DIR}/src/include/
    -I${CMAKE_CURRENT_SOURCE_DIR}/external/GSL/include/
    -std=c++14
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/external/CppCoreGuidelines/scripts/python/cpplint.py
    ${SRCFILE}

    COMMAND clang-check ${SRCFILE} -analyze
    --
    -I${CMAKE_CURRENT_SOURCE_DIR}/src/include/
    -I${CMAKE_CURRENT_SOURCE_DIR}/external/GSL/include/
    -std=c++14

    COMMAND cppcheck ${SRCFILE}
  )
endforeach()


file(GLOB_RECURSE ana "src/*.hpp" )
foreach(SRCFILE ${ana})
  add_custom_command(
    TARGET staticAnalysies
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/external/CppCoreGuidelines/scripts/python/cpplint.py
    ${SRCFILE}
  )
endforeach()


#add_dependencies(release staticAnalysies)
