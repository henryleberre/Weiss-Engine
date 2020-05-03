#include "RenderPipeline.h"

namespace WS       {
namespace Internal {
namespace VK       {

	VKRenderPipeline& VKRenderPipeline::operator=(VKRenderPipeline&& other)
	{
		this->m_layout = other.m_layout;
		other.m_layout = VK_NULL_HANDLE;

		this->m_pipeline = other.m_pipeline;
		other.m_pipeline = VK_NULL_HANDLE;

		this->m_pDevice = other.m_pDevice;
	}

	VKRenderPipeline::VKRenderPipeline(const VKDevice& device, const VKSwapChain& swapChain, const RenderPipelineDesc& pipelineDesc,
									   std::vector<ConstantBuffer*>& pConstantBuffers, std::vector<Texture*> pTextures, std::vector<VKTextureSampler*> pTextureSamplers)
		: m_pDevice(&device)
	{
		const VkShaderModule vertexShaderModule = VKRenderPipeline::CreateShaderModule(device, pipelineDesc.vsFilename);
		const VkShaderModule pixelShaderModule  = VKRenderPipeline::CreateShaderModule(device, pipelineDesc.psFilename);

		VkPipelineShaderStageCreateInfo vertShaderStageInfo{};
		vertShaderStageInfo.sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		vertShaderStageInfo.stage  = VK_SHADER_STAGE_VERTEX_BIT;
		vertShaderStageInfo.module = vertexShaderModule;
		vertShaderStageInfo.pName  = "main";

		VkPipelineShaderStageCreateInfo fragShaderStageInfo{};
		fragShaderStageInfo.sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		fragShaderStageInfo.stage  = VK_SHADER_STAGE_FRAGMENT_BIT;
		fragShaderStageInfo.module = pixelShaderModule;
		fragShaderStageInfo.pName  = "main";

		const VkPipelineShaderStageCreateInfo shaderStages[] = { vertShaderStageInfo, fragShaderStageInfo };

		VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
		vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		vertexInputInfo.vertexBindingDescriptionCount = 0;
		vertexInputInfo.pVertexBindingDescriptions    = nullptr;
		vertexInputInfo.vertexAttributeDescriptionCount = 0;
		vertexInputInfo.pVertexAttributeDescriptions    = nullptr;

		VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
		inputAssembly.sType    = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		inputAssembly.primitiveRestartEnable = VK_FALSE;

		VkViewport viewport{};
		viewport.x = 0.0f;
		viewport.y = 0.0f;
		viewport.width  = (float)swapChain.GetImageExtent().width;
		viewport.height = (float)swapChain.GetImageExtent().height;
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;

		VkRect2D scissor{};
		scissor.offset = { 0, 0 };
		scissor.extent = swapChain.GetImageExtent();

		VkPipelineViewportStateCreateInfo viewportState{};
		viewportState.sType         = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		viewportState.viewportCount = 1;
		viewportState.pViewports    = &viewport;
		viewportState.scissorCount  = 1;
		viewportState.pScissors     = &scissor;

		VkPipelineRasterizationStateCreateInfo rasterizer{};
		rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		rasterizer.depthClampEnable = VK_FALSE;
		rasterizer.rasterizerDiscardEnable = VK_FALSE;
		rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
		rasterizer.lineWidth   = 1.0f;
		rasterizer.cullMode  = VK_CULL_MODE_BACK_BIT;
		rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
		rasterizer.depthBiasEnable = VK_FALSE;
		rasterizer.depthBiasConstantFactor = 0.0f;
		rasterizer.depthBiasClamp          = 0.0f;
		rasterizer.depthBiasSlopeFactor    = 0.0f;

		VkPipelineMultisampleStateCreateInfo multisampling{};
		multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		multisampling.sampleShadingEnable = VK_FALSE;
		multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
		multisampling.minSampleShading = 1.0f;
		multisampling.pSampleMask = nullptr;
		multisampling.alphaToCoverageEnable = VK_FALSE;
		multisampling.alphaToOneEnable = VK_FALSE;

		VkPipelineColorBlendAttachmentState colorBlendAttachment{};
		colorBlendAttachment.blendEnable = VK_TRUE;
		colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
		colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
		colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
		colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
		colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
		colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;

		VkPipelineColorBlendStateCreateInfo colorBlending{};
		colorBlending.sType           = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		colorBlending.logicOpEnable   = VK_FALSE;
		colorBlending.logicOp         = VK_LOGIC_OP_COPY;
		colorBlending.attachmentCount = 1;
		colorBlending.pAttachments    = &colorBlendAttachment;
		colorBlending.blendConstants[0] = 0.0f;
		colorBlending.blendConstants[1] = 0.0f;
		colorBlending.blendConstants[2] = 0.0f;
		colorBlending.blendConstants[3] = 0.0f;

		VkDynamicState dynamicStates[] = {
			VK_DYNAMIC_STATE_VIEWPORT
		};

		VkPipelineDynamicStateCreateInfo dynamicState{};
		dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
		dynamicState.dynamicStateCount = sizeof(dynamicStates) / sizeof(VkDynamicState);
		dynamicState.pDynamicStates    = dynamicStates;

		VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
		pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutInfo.setLayoutCount = 0;
		pipelineLayoutInfo.pSetLayouts = nullptr;
		pipelineLayoutInfo.pushConstantRangeCount = 0;
		pipelineLayoutInfo.pPushConstantRanges = nullptr;

		if (FAILED(vkCreatePipelineLayout(device, &pipelineLayoutInfo, nullptr, &this->m_layout)))
			throw std::runtime_error("failed to create pipeline layout!");


		VkGraphicsPipelineCreateInfo pipelineInfo{};
		pipelineInfo.sType      = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		pipelineInfo.stageCount = sizeof(shaderStages) / sizeof(VkPipelineShaderStageCreateInfo);
		pipelineInfo.pStages    = shaderStages;
		pipelineInfo.pVertexInputState = &vertexInputInfo;
		pipelineInfo.pInputAssemblyState = &inputAssembly;
		pipelineInfo.pViewportState = &viewportState;
		pipelineInfo.pRasterizationState = &rasterizer;
		pipelineInfo.pMultisampleState = &multisampling;
		pipelineInfo.pDepthStencilState = nullptr; // Optional
		pipelineInfo.pColorBlendState = &colorBlending;
		pipelineInfo.pDynamicState = nullptr; // Optional
		pipelineInfo.layout     = this->m_layout;
		pipelineInfo.renderPass = VKRenderPipeline::m_colorRenderPass;
		pipelineInfo.subpass    = 0;
		pipelineInfo.basePipelineHandle = VK_NULL_HANDLE; // Optional
		pipelineInfo.basePipelineIndex = -1; // Optional

		if (VK_FAILED(vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &this->m_pipeline)))
			throw std::runtime_error("[VULKAN] Failed To Create Pipeline");

		vkDestroyShaderModule(device, vertexShaderModule, nullptr);
		vkDestroyShaderModule(device, pixelShaderModule,  nullptr);
	}

	VKRenderPipeline::~VKRenderPipeline()
	{
		vkDestroyPipeline(*this->m_pDevice, this->m_pipeline, nullptr);
		vkDestroyPipelineLayout(*this->m_pDevice, this->m_layout, nullptr);
	}

	void VKRenderPipeline::CreateRenderPasses(const VKDevice& device, const VKSwapChain& swapChain)
	{
		VkAttachmentDescription colorAttachment{};
		colorAttachment.format  = swapChain.GetFormat().format;
		colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
		colorAttachment.loadOp  = VK_ATTACHMENT_LOAD_OP_CLEAR;
		colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
		colorAttachment.stencilLoadOp  = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		colorAttachment.finalLayout   = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

		VkAttachmentReference colorAttachmentRef{};
		colorAttachmentRef.attachment = 0;
		colorAttachmentRef.layout     = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

		VkSubpassDescription subpass{};
		subpass.pipelineBindPoint    = VK_PIPELINE_BIND_POINT_GRAPHICS;
		subpass.colorAttachmentCount = 1;
		subpass.pColorAttachments    = &colorAttachmentRef;

		VkRenderPassCreateInfo renderPassInfo{};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		renderPassInfo.attachmentCount = 1;
		renderPassInfo.pAttachments    = &colorAttachment;
		renderPassInfo.subpassCount    = 1;
		renderPassInfo.pSubpasses      = &subpass;

		if (VK_FAILED(vkCreateRenderPass(device, &renderPassInfo, nullptr, &VKRenderPipeline::m_colorRenderPass)))
			throw std::runtime_error("[VULKAN] Failed To Create Render Pass");
	}

	VkShaderModule VKRenderPipeline::CreateShaderModule(const VKDevice& device, const char* filename)
	{
		std::ifstream file(filename, std::ios::ate | std::ios::binary);

		if (!file.is_open())
			throw std::runtime_error("[VULKAN] Failed To Open Binary Shader File");

		std::vector<char> contents(file.tellg());
		file.seekg(0);
		file.read(contents.data(), contents.size());
		file.close();

		VkShaderModuleCreateInfo createInfo{};
		createInfo.sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		createInfo.codeSize = contents.size();
		createInfo.pCode    = reinterpret_cast<const uint32_t*>(contents.data());

		VkShaderModule shaderModule;
		if (VK_FAILED(vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule)))
			throw std::runtime_error("[VULKAN] Failed To Create Shader Module");

		return shaderModule;
	}

	VkRenderPass VKRenderPipeline::m_colorRenderPass = VK_NULL_HANDLE;

}; // VK
}; // Internal
}; // WS