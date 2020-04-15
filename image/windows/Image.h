#pragma once

#include "../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

class WindowsImage : public ImageBase {
public:
    WindowsImage(const char* filename);
};

#endif // __WEISS__OS_WINDOWS