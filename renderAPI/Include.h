#pragma once

#include "common/Include.h"
//#include "vulkan/Include.h"
//#include "opengl/Include.h"
#include "directx11/Include.h"
#include "directx12/Include.h"

auto CreateRenderAPI(const RenderAPIName& renderAPIName);