#ifndef DEBUG_HELPER_H_
#define DEBUG_HELPER_H_

#include <iostream>

#define DEBUG_PRINT( _OUTPUT) \
  std::cout << __FILE__ << ": line  " << __LINE__ << std::endl;\
  std::cout << _OUTPUT << std::endl;

#define ASSERT(_ASSUMPTION, _RETURN) \
  if(_ASSUMPTION) {\
    DEBUG_PRINT(# _ASSUMPTION);\
    return _RETURN;\
  }

#endif
