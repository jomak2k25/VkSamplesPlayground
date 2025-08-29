#pragma once
/*
 * Vulkan Example - Rendering a glTF model using hardware accelerated ray tracing example (for proper transparency, this sample does frame accumulation)
 *
 * Copyright (C) 2023-2025 by Sascha Willems - www.saschawillems.de
 *
 * This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
 */

#include "VulkanRaytracingSample.h"
#define VK_GLTF_MATERIAL_IDS
#include "VulkanglTFModel.h"

 // World Positions, Normals, Ambient Occlusion Result
constexpr int g_numAdditionalImages = 3;

class VulkanExample : public VulkanRaytracingSample
{
public:
	AccelerationStructure bottomLevelAS{};
	AccelerationStructure topLevelAS{};

	StorageImage additionalStorageImages[g_numAdditionalImages];

	vks::Buffer vertexBuffer;
	vks::Buffer indexBuffer;
	uint32_t indexCount{ 0 };
	vks::Buffer transformBuffer;

	struct GeometryNode {
		uint64_t vertexBufferDeviceAddress;
		uint64_t indexBufferDeviceAddress;
		int32_t textureIndexBaseColor;
		int32_t textureIndexOcclusion;
	};
	vks::Buffer geometryNodesBuffer;

	std::vector<VkRayTracingShaderGroupCreateInfoKHR> shaderGroups{};
	struct ShaderBindingTables {
		ShaderBindingTable raygen;
		ShaderBindingTable miss;
		ShaderBindingTable hit;
	} shaderBindingTables;

	vks::Texture2D texture;

	struct UniformData {
		glm::mat4 viewInverse;
		glm::mat4 projInverse;
		uint32_t frame{ 0 };
	} uniformData;
	std::array<vks::Buffer, maxConcurrentFrames> uniformBuffers;

	VkPipeline pipeline{ VK_NULL_HANDLE };
	VkPipelineLayout pipelineLayout{ VK_NULL_HANDLE };
	VkDescriptorSetLayout descriptorSetLayout{ VK_NULL_HANDLE };
	std::array<VkDescriptorSet, maxConcurrentFrames> descriptorSets{};

	vkglTF::Model model;

	VkPhysicalDeviceDescriptorIndexingFeaturesEXT physicalDeviceDescriptorIndexingFeatures{};

	VulkanExample();

	~VulkanExample();

	void createAccelerationStructureBuffer(AccelerationStructure& accelerationStructure, VkAccelerationStructureBuildSizesInfoKHR buildSizeInfo);

	//	Create the bottom level acceleration structure that contains the scene's actual geometry (vertices, triangles)
	void createBottomLevelAccelerationStructure();

	//	The top level acceleration structure contains the scene's object instances
	void createTopLevelAccelerationStructure();

	//	Create the Shader Binding Tables that binds the programs and top-level acceleration structure
	void createShaderBindingTables();

	//	Create our ray tracing pipeline
	void createRayTracingPipeline();
	//	Create the descriptor sets used for the ray tracing dispatch
	void createDescriptorSets();
	//	Create the uniform buffer used to pass matrices to the ray tracing ray generation shader
	void createUniformBuffer();
	//	If the window has been resized, we need to recreate the storage image and it's descriptor
	void handleResize();

	void updateUniformBuffers();

	void getEnabledFeatures();

	void loadAssets();

	void createAdditionalStorageImages();

	void setupStorageImage(VkFormat format, VkExtent3D extent, StorageImage& outImage);

	void prepare();

	void buildCommandBuffer();

	virtual void render();
};
