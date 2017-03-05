#add_executable(main main.cpp)

set(SOURCE
  ${SOURCE}
  ${CMAKE_CURRENT_SOURCE_DIR}/tokenizer/tokenizer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/tokenizer/token.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/parser/AstParser.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/parser/AstElement.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/parser/AstTerm.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/parser/AstElementTree.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/parser/customElements/EleFunction.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/parser/customElements/EleStmtList.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/symboltable/symbolTable.cpp
PARENT_SCOPE
  )
