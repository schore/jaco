#add_executable(main main.cpp)

set(SOURCE
  ${SOURCE}
  ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/tokenizer/tokenizer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/tokenizer/token/TokenIdentifier.cpp
  PARENT_SCOPE
  )
