#add_executable(main main.cpp)

set(TEST_SRC_TOKEN
  ${TEST_SRC_TOKEN}
  ${CMAKE_CURRENT_SOURCE_DIR}/tokenizer/tokenizerTest.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/tokenizer/tokenIntTest.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/tokenizer/tokenDoubleTest.cpp
  PARENT_SCOPE
)
