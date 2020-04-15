#pragma once

#include "../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

class WindowsImage : public ImageBase {
public:
    WindowsImage();
    WindowsImage(WindowsImage&& other);
    WindowsImage(const WindowsImage& other);
    WindowsImage(const char* filename);
    WindowsImage(const uint16_t width, const uint16_t height, const Coloru8& fillColor = { 255u,255u,255u,255u });

    virtual void Write(const char* filename) const override;
};

#endif // __WEISS__OS_WINDOWS