#pragma once

#include "../../common/Include.h"

namespace WS {

	struct Drawable {
		size_t pipelineIndex;
		size_t vertexBufferIndex;

		std::optional<size_t> indexBufferIndex;
	};

}; // WS