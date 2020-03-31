#include "Shaders.h"

VulkanVertexShader::VulkanVertexShader(const std::shared_ptr<VulkanDevice>& pDevice, const char* sourceFilename)
	: m_pDevice(pDevice)
{
	std::ifstream fileStream(sourceFilename);
	std::string   sourceCode((std::istreambuf_iterator<char>(fileStream)), (std::istreambuf_iterator<char>()));

	VkShaderModuleCreateInfo createInfo = {};
	createInfo.sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo.codeSize = sourceCode.size();
	createInfo.pCode    = reinterpret_cast<const uint32_t*>(sourceCode.c_str());

	if (vkCreateShaderModule(this->m_pDevice->Get(), &createInfo, nullptr, &this->m_shaderModule) != VK_SUCCESS)
		throw std::runtime_error("[VULKAN] Failed To Create Shader Module");

	VkPipelineShaderStageCreateInfo shaderStageCreateInfo = {};
	shaderStageCreateInfo.sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	shaderStageCreateInfo.stage  = VK_SHADER_STAGE_VERTEX_BIT;
	shaderStageCreateInfo.module = this->m_shaderModule;
	shaderStageCreateInfo.pName  = "main";

	this->m_stageCreateInfo = shaderStageCreateInfo;
}

VulkanVertexShader::~VulkanVertexShader()
{
	vkDestroyShaderModule(this->m_pDevice->Get(), this->m_shaderModule, nullptr);
}

[[nodiscard]] VkShaderModule VulkanVertexShader::Get() const noexcept
{
	return this->m_shaderModule;
}

[[nodiscard]] VkPipelineShaderStageCreateInfo VulkanVertexShader::GetVkPipelineShaderStageCreateInfo() const noexcept
{
	return this->m_stageCreateInfo;
}

VulkanVertexShader::operator VkShaderModule() const noexcept
{
	return this->m_shaderModule;
}

VulkanVertexShader::operator VkPipelineShaderStageCreateInfo() const noexcept
{
	return this->m_stageCreateInfo;
}



VulkanPixelShader::VulkanPixelShader(const std::shared_ptr<VulkanDevice>& pDevice, const char* sourceFilename)
	: m_pDevice(pDevice)
{
	std::ifstream fileStream(sourceFilename);
	std::string   sourceCode((std::istreambuf_iterator<char>(fileStream)), (std::istreambuf_iterator<char>()));

	VkShaderModuleCreateInfo createInfo = {};
	createInfo.sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo.codeSize = sourceCode.size();
	createInfo.pCode    = reinterpret_cast<const uint32_t*>(sourceCode.c_str());

	if (vkCreateShaderModule(this->m_pDevice->Get(), &createInfo, nullptr, &this->m_shaderModule) != VK_SUCCESS)
		throw std::runtime_error("[VULKAN] Failed To Create Shader Module");

	VkPipelineShaderStageCreateInfo shaderStageCreateInfo = {};
	shaderStageCreateInfo.sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	shaderStageCreateInfo.stage  = VK_SHADER_STAGE_FRAGMENT_BIT;
	shaderStageCreateInfo.module = this->m_shaderModule;
	shaderStageCreateInfo.pName  = "main";

	this->m_stageCreateInfo = shaderStageCreateInfo;
}

VulkanPixelShader::~VulkanPixelShader()
{
	vkDestroyShaderModule(this->m_pDevice->Get(), this->m_shaderModule, nullptr);
}

[[nodiscard]] VkShaderModule VulkanPixelShader::Get() const noexcept
{
	return this->m_shaderModule;
}

[[nodiscard]] VkPipelineShaderStageCreateInfo VulkanPixelShader::GetVkPipelineShaderStageCreateInfo() const noexcept
{
	return this->m_stageCreateInfo;
}

VulkanPixelShader::operator VkShaderModule() const noexcept
{
	return this->m_shaderModule;
}

VulkanPixelShader::operator VkPipelineShaderStageCreateInfo() const noexcept
{
	return this->m_stageCreateInfo;
}