#pragma once

#include "../math/Include.h"
#include "../../common/Include.h"

/* Any child class shall have the following constructors :
 * - Image()
 * - Image(Image&& other)
 * - Image(const Image& other)
 * - Image(const char* filename)
 * - Image(const uint16_t width, const uint16_t height, const Coloru8& fillColor = { 255u,255u,255u,255u })
 */
class ImageBase {
protected:
    std::unique_ptr<Coloru8[]> m_buff;

    uint16_t m_width = 0, m_height = 0;
    uint32_t m_nPixels = 0;

public:
    [[nodiscard]] uint16_t GetWidth()      const;
    [[nodiscard]] uint16_t GetHeight()     const;
    [[nodiscard]] uint32_t GetPixelCount() const;
    [[nodiscard]] Coloru8* GetBuffer()     const;
    [[nodiscard]] Coloru8  Sample(const uint16_t x, const uint16_t y) const;

    void Set(const uint16_t x, const uint16_t y, const Coloru8& color);

    virtual void Write(const char* filename) const = 0;
};