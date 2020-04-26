#pragma once

#include "../../image/Include.h"
#include "../../common/Include.h"

namespace WS {

	class Texture {
	public:
		virtual void Update(const Image& image) = 0;
	};

};