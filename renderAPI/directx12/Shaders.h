#pragma once

#include "internal/Include.h"
#include "../common/Include.h"
#include "../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

class DirectX12VertexShader {
public:
	DirectX12VertexShader();

	void Bind();
};

class DirectX12PixelShader {
public:
	DirectX12PixelShader();

	void Bind();
};

#endif // __WEISS__OS_WINDOWS