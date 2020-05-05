#pragma once

#include "SceneNode.h"

namespace WS       {
namespace Internal {

	class Scene {
	private:
		std::unique_ptr<SceneNode*> m_pRootNode;

	public:
		Scene() = default;
	};

}; // Internal
}; // WS