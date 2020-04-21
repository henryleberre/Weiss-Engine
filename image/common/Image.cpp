#include "Image.h"

namespace WS       {
namespace Internal {

    [[nodiscard]] uint16_t ImageBase::GetWidth()                                 const { return this->m_width; }
    [[nodiscard]] uint16_t ImageBase::GetHeight()                                const { return this->m_height; }
    [[nodiscard]] uint32_t ImageBase::GetPixelCount()                            const { return this->m_nPixels; }
    [[nodiscard]] Coloru8* ImageBase::GetBuffer()                                const { return this->m_buff.get(); }
    [[nodiscard]] Coloru8  ImageBase::Sample(const uint16_t x, const uint16_t y) const { return this->m_buff[y * this->m_width + x]; }

    void ImageBase::Set(const uint16_t x, const uint16_t y, const Coloru8& color) { this->m_buff[y * this->m_width + x] = color; }

}; // Internal
}; // WS