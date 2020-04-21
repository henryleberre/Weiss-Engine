#pragma once

#include "../../common/Include.h"

namespace WS {

    struct ShaderInputElement {
        const char* name;
        ShaderInputElementType type;
    };

    typedef std::bitset<2u> ShaderBindingType;

    constexpr const ShaderBindingType shaderBindingTypeVertexShader = std::bitset<2u>(1u << 0u);
    constexpr const ShaderBindingType shaderBindingTypePixelShader  = std::bitset<2u>(1u << 1u);
    constexpr const ShaderBindingType shaderBindingTypeBoth         = std::bitset<2u>((1u << 0u) | (1u << 1u));

};