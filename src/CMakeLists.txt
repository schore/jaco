#add_executable(main main.cpp)

set(SOURCE
  ${SOURCE}
  ${CMAKE_CURRENT_SOURCE_DIR}/tokenizer/tokenizer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/tokenizer/token.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/parser/AstParser.cpp
 PARENT_SCOPE
  )
