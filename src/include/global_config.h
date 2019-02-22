#ifndef DEBUG_HELPER_H__
#define DEBUG_HELPER_H__

#define DEBUG_PRINT(_OUTPUT)                                                   \
  std::cout << __FILE__ << ":" << __LINE__ << std::endl;                       \
  std::cout << __OUTPUT << std::endl;

#define ASSERT(_ASSERTION, _RETURN)                                            \
  if (_ASSERTION) {                                                            \
    DEBUG_PRINT(#_ASSERTION);                                                  \
    return _RETURN;                                                            \
  }

#endif
