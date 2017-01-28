#ifndef DEBUG_HELPER_H_
#define DEBUG_HELPER_H_

#include <iostream>

#define DEBUG_PRINT()

#define ASSERT(_REQUIREMENT, _ERR_RETURN) \
  if(_REQUIREMENT) {\
    DEBUG_PRINT(_REQUIREMENT)\
    return _ERR_RETURN;\
  }

#endif
