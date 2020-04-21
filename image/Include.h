#pragma once

#include "../common/Include.h"

/* 
 * We use a per platform image loading system to use
 * their platform's preexisting libraries
 */

#include "common/Include.h"
#include "windows/Include.h"

#ifdef __WEISS__OS_WINDOWS

namespace WS {

    typedef Internal::WIN::WindowsImage Image;

};

#endif // __WEISS__OS_WINDOWS