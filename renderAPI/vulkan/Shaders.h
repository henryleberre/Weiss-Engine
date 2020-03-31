#pragma once

#include "internal/Device.h"
#include "../common/Include.h"
#include "../../common/Include.h"

class VulkanVertexShader {
private:
	VkShaderModule m_shaderModule;
	VkPipelineShaderStageCreateInfo m_stageCreateInfo;

	std::shared_ptr<VulkanDevice> m_pDevice;

public:
	VulkanVertexShader(const std::shared_ptr<VulkanDevice>& pDevice, const char* sourceFilename);
	~VulkanVertexShader();

	[[nodiscard]] VkShaderModule Get() const noexcept;
	[[nodiscard]] VkPipelineShaderStageCreateInfo GetVkPipelineShaderStageCreateInfo() const noexcept;

	operator VkShaderModule() const noexcept;
	operator VkPipelineShaderStageCreateInfo() const noexcept;
};

class VulkanPixelShader {
private:
	VkShaderModule m_shaderModule;
	VkPipelineShaderStageCreateInfo m_stageCreateInfo;

	std::shared_ptr<VulkanDevice> m_pDevice;

public:
	VulkanPixelShader(const std::shared_ptr<VulkanDevice>& pDevice, const char* sourceFilename);
	~VulkanPixelShader();

	[[nodiscard]] VkShaderModule Get() const noexcept;
	[[nodiscard]] VkPipelineShaderStageCreateInfo GetVkPipelineShaderStageCreateInfo() const noexcept;

	operator VkShaderModule() const noexcept;
	operator VkPipelineShaderStageCreateInfo() const noexcept;
};