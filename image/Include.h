#pragma once

#include "../common/Include.h"

/* 
 * We use a per platform image loading system to use
 * their platform's preexisting libraries
 */

#include "common/Include.h"
#include "windows/Include.h"

#ifdef __WEISS__OS_WINDOWS

typedef WindowsImage Image;

#endif // __WEISS__OS_WINDOWS