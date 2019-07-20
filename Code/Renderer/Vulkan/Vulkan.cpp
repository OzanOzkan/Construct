#include "Vulkan.h"

#include <iostream>

void CVulkan::start()
{
	initWindow();
	createVulkanInstance();
}

void CVulkan::initWindow()
{
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	m_pWindow = glfwCreateWindow(m_width, m_height, m_title, nullptr, nullptr);
}

void CVulkan::createVulkanInstance() 
{
	std::cout << "CVulkan::createVulkanInstance()" << std::endl;

	if (m_enableValidationLayers && !checkValidationLayerSupport()) {
		throw std::runtime_error("Validation layers requested, but not availabe!");
	}

	VkApplicationInfo appInfo = {};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "Project O01";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "No Engine";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	// VkInstanceCreateInfo
	VkInstanceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;

	auto extensions = getRequiredExtensions();
	createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());;
	createInfo.ppEnabledExtensionNames = extensions.data();

	createInfo.enabledLayerCount = 0;

	if (m_enableValidationLayers) {
		createInfo.enabledLayerCount = static_cast<uint32_t>(m_validationLayers.size());
		createInfo.ppEnabledLayerNames = m_validationLayers.data();
	}
	else {
		createInfo.enabledLayerCount = 0;
	}
	// ~VkInstanceCreateInfo

	if (vkCreateInstance(&createInfo, nullptr, &m_vkInstance) != VK_SUCCESS)
		throw std::runtime_error("Failed to create Vulkan instance!");
	else
		std::cout << "createVulkanInstance(): Vulkan instance created!" << std::endl;

	uint32_t vkExtensionCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &vkExtensionCount, nullptr);

	std::vector<VkExtensionProperties> vkExtensions(vkExtensionCount);
	vkEnumerateInstanceExtensionProperties(nullptr, &vkExtensionCount, vkExtensions.data());

	std::cout << "Available Vulkan extensions: " << std::endl;

	for (const auto& extension : vkExtensions) {
		std::cout << "\t" << extension.extensionName << " ver " << extension.specVersion << std::endl;
	}
}

std::vector<const char*> CVulkan::getRequiredExtensions()
{
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

	if (m_enableValidationLayers) {
		extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	}

	return extensions;
}

bool CVulkan::checkValidationLayerSupport() {
	uint32_t layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

	std::vector<VkLayerProperties> availableLayers(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

	for (const auto& layerName : m_validationLayers) {
		bool layerFound = false;

		for (const auto& layerProperties : availableLayers) {
			if (strcmp(layerName, layerProperties.layerName) == 0) {
				layerFound = true;
				break;
			}
		}

		if (!layerFound) {
			return false;
		}
	}

	return true;
}