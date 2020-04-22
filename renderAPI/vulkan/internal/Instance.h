#pragma once

#include "ObjectWrapper.h"
#include "../../common/Include.h"

namespace WS       {
namespace Internal {
namespace VK       {
	
	typedef VKObjectWrapper<VkInstance> VKInstanceObjectWrapper;

	class VKInstance : public VKInstanceObjectWrapper {
	public:
		VKInstance();
		VKInstance(const char* appName);

		~VKInstance();
	};

}; // VK
}; // Internal
}; // WS