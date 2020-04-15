#pragma once

#include "../math/Include.h"
#include "../../common/Include.h"

class ImageBase {
protected:
    std::unique_ptr<Coloru8[]> m_buff;

    uint16_t m_width = 0, m_height = 0;
    uint32_t m_nPixels = 0;

public:
    ImageBase();
    ImageBase(const uint16_t width, const uint16_t height, Coloru8 fillColor = { 255u,255u,255u,255u });

    [[nodiscard]] uint16_t GetWidth()      const;
    [[nodiscard]] uint16_t GetHeight()     const;
    [[nodiscard]] uint32_t GetPixelCount() const;
    [[nodiscard]] Coloru8* GetBuffer()     const;
    [[nodiscard]] Coloru8  Sample(const uint16_t x, const uint16_t y) const;

    void Set(const uint16_t x, const uint16_t y, const Coloru8& color);
};