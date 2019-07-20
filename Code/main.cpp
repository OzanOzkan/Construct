//#define GLFW_INCLUDE_VULKAN
//#include <GLFW/glfw3.h>
//
//#include <iostream>
//#include <stdexcept>
//#include <functional>
//#include <cstdlib>
//#include <vector>
//#include <optional>
//#include <set>
//#include <algorithm>
//
//class HelloWorldApplication {
//
//	struct QueueFamilyIndices {
//		std::optional<uint32_t> graphicsFamily;
//		std::optional<uint32_t> presentFamily;
//
//		bool isComplete() {
//			return graphicsFamily.has_value() && presentFamily.has_value();
//		}
//	};
//
//	struct SwapChainSupportDetails {
//		VkSurfaceCapabilitiesKHR capabilities;
//		std::vector<VkSurfaceFormatKHR> formats;
//		std::vector<VkPresentModeKHR> presentModes;
//	};
//
//public:
//	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device) {
//		QueueFamilyIndices indices;
//
//		uint32_t queueFamilyCount = 0;
//		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
//
//		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
//		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());
//
//		int i = 0;
//		for (const auto& queueFamily : queueFamilies) {
//			if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
//				indices.graphicsFamily = i;
//
//				VkBool32 presentSupport = false;
//				vkGetPhysicalDeviceSurfaceSupportKHR(device, i, m_Surface, &presentSupport);
//
//				if (queueFamily.queueCount > 0 && presentSupport) {
//					indices.presentFamily = i;
//				}
//			}
//
//			if (indices.isComplete()) {
//				break;
//			}
//
//			i++;
//		}
//
//		return indices;
//	}
//
//	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device) {
//		SwapChainSupportDetails details;
//
//		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, m_Surface, &details.capabilities);
//
//		uint32_t formatCount;
//		vkGetPhysicalDeviceSurfaceFormatsKHR(device, m_Surface, &formatCount, nullptr);
//
//		if (formatCount != 0) {
//			details.formats.resize(formatCount);
//			vkGetPhysicalDeviceSurfaceFormatsKHR(device, m_Surface, &formatCount, details.formats.data());
//
//		}
//
//		uint32_t presentModeCount;
//		vkGetPhysicalDeviceSurfacePresentModesKHR(device, m_Surface, &presentModeCount, nullptr);
//
//		if (presentModeCount != 0) {
//			details.presentModes.resize(presentModeCount);
//			vkGetPhysicalDeviceSurfacePresentModesKHR(device, m_Surface, &presentModeCount, details.presentModes.data());
//		}
//		return details;
//	}
//
//	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats) {
//		for (const auto& availableFormat : availableFormats) {
//			if (availableFormat.format == VK_FORMAT_B8G8R8A8_UNORM && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
//				return availableFormat;
//			}
//		}
//
//		return availableFormats[0];
//	}
//
//	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes) {
//		VkPresentModeKHR bestMode = VK_PRESENT_MODE_FIFO_KHR;
//
//		for (const auto& availablePresentMode : availablePresentModes) {
//			if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
//				return availablePresentMode;
//			}
//			else if (availablePresentMode == VK_PRESENT_MODE_IMMEDIATE_KHR) {
//				bestMode = availablePresentMode;
//			}
//		}
//
//		return bestMode;
//	}
//
//	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities) {
//		if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
//			return capabilities.currentExtent;
//		}
//		else {
//			VkExtent2D actualExtent = { m_Width, m_Height };
//
//			actualExtent.width = std::max(capabilities.minImageExtent.width, std::min(capabilities.maxImageExtent.width, actualExtent.width));
//			actualExtent.height = std::max(capabilities.minImageExtent.height, std::min(capabilities.maxImageExtent.height, actualExtent.height));
//
//			return actualExtent;
//		}
//	}
//
//	VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
//		auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
//		if (func != nullptr) {
//			return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
//		}
//		else {
//			return VK_ERROR_EXTENSION_NOT_PRESENT;
//		}
//	}
//
//	void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
//		auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
//		if (func != nullptr) {
//			func(instance, debugMessenger, pAllocator);
//		}
//	}
//
//	void run() {
//		initWindow();
//		initVulkan();
//		checkValidationLayerSupport();
//		mainLoop();
//		cleanup();
//	}
//
//private:
//	void createVulkanInstance() {
//		std::cout << "HelloWorldApplication::createVulkanInstance()" << std::endl;
//
//		if (m_enableValidationLayers && !checkValidationLayerSupport()) {
//			throw std::runtime_error("Validation layers requested, but not availabe!");
//		}
//
//		VkApplicationInfo appInfo = {};
//		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
//		appInfo.pApplicationName = "Project O01";
//		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
//		appInfo.pEngineName = "No Engine";
//		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
//		appInfo.apiVersion = VK_API_VERSION_1_0;
//
//		// VkInstanceCreateInfo
//		VkInstanceCreateInfo createInfo = {};
//		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
//		createInfo.pApplicationInfo = &appInfo;
//
//		auto extensions = getRequiredExtensions();
//		createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());;
//		createInfo.ppEnabledExtensionNames = extensions.data();
//
//		createInfo.enabledLayerCount = 0;
//
//		if (m_enableValidationLayers) {
//			createInfo.enabledLayerCount = static_cast<uint32_t>(m_validationLayers.size());
//			createInfo.ppEnabledLayerNames = m_validationLayers.data();
//		}
//		else {
//			createInfo.enabledLayerCount = 0;
//		}
//		// ~VkInstanceCreateInfo
//
//		if (vkCreateInstance(&createInfo, nullptr, &m_vkInstance) != VK_SUCCESS)
//			throw std::runtime_error("Failed to create Vulkan instance!");
//		else
//			std::cout << "createVulkanInstance(): Vulkan instance created!" << std::endl;
//
//		uint32_t vkExtensionCount = 0;
//		vkEnumerateInstanceExtensionProperties(nullptr, &vkExtensionCount, nullptr);
//
//		std::vector<VkExtensionProperties> vkExtensions(vkExtensionCount);
//		vkEnumerateInstanceExtensionProperties(nullptr, &vkExtensionCount, vkExtensions.data());
//
//		std::cout << "Available Vulkan extensions: " << std::endl;
//
//		for (const auto& extension : vkExtensions) {
//			std::cout << "\t" << extension.extensionName << " ver " << extension.specVersion << std::endl;
//		}
//	}
//
//	void initVulkan() {
//		std::cout << "HelloWorldApplication::initVulkan()" << std::endl;
//		createVulkanInstance();
//		setupVulkanDebugMessenger();
//		createSurface();
//		pickPhysicalDevice();
//		createLogicalDevice();
//		createSwapChain();
//	}
//
//	void createSwapChain() {
//		SwapChainSupportDetails swapChainSupport = querySwapChainSupport(m_physicalDevice);
//
//		VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
//		VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
//		VkExtent2D extent = chooseSwapExtent(swapChainSupport.capabilities);
//
//		uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
//
//		if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
//			imageCount = swapChainSupport.capabilities.maxImageCount;
//		}
//
//		VkSwapchainCreateInfoKHR createInfo = {};
//		createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
//		createInfo.surface = m_Surface;
//		createInfo.minImageCount = imageCount;
//		createInfo.imageFormat = surfaceFormat.format;
//		createInfo.imageColorSpace = surfaceFormat.colorSpace;
//		createInfo.imageExtent = extent;
//		createInfo.imageArrayLayers = 1;
//		createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
//
//		QueueFamilyIndices indices = findQueueFamilies(m_physicalDevice);
//		uint32_t queueFamilyIndices[] = { indices.graphicsFamily.value(), indices.presentFamily.value() };
//
//		if (indices.graphicsFamily != indices.presentFamily) {
//			createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
//			createInfo.queueFamilyIndexCount = 2;
//			createInfo.pQueueFamilyIndices = queueFamilyIndices;
//		}
//		else {
//			createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
//			createInfo.queueFamilyIndexCount = 0; // Optional
//			createInfo.pQueueFamilyIndices = nullptr; // Optional
//		}
//
//		createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
//		createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
//		createInfo.presentMode = presentMode;
//		createInfo.clipped = VK_TRUE;
//		createInfo.oldSwapchain = VK_NULL_HANDLE;
//
//		if (vkCreateSwapchainKHR(m_Device, &createInfo, nullptr, &m_swapChain) != VK_SUCCESS) {
//			throw std::runtime_error("failed to create swap chain!");
//		}
//
//		vkGetSwapchainImagesKHR(m_Device, m_swapChain, &imageCount, nullptr);
//		m_swapChainImages.resize(imageCount);
//		vkGetSwapchainImagesKHR(m_Device, m_swapChain, &imageCount, m_swapChainImages.data());
//
//		m_swapChainImageFormat = surfaceFormat.format;
//		m_swapChainExtent = extent;
//	}
//
//	void createSurface() { 
//		if (glfwCreateWindowSurface(m_vkInstance, m_pWindow, nullptr, &m_Surface) != VK_SUCCESS) {
//			throw std::runtime_error("failed to create window surface!");
//		}
//	}
//
//	void createLogicalDevice() {
//		QueueFamilyIndices indices = findQueueFamilies(m_physicalDevice);
//
//		std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
//		std::set<uint32_t> uniqueQueueFamilies = { indices.graphicsFamily.value(), indices.presentFamily.value() };
//
//		float queuePriority = 1.0f;
//		for (uint32_t queueFamily : uniqueQueueFamilies) {
//			VkDeviceQueueCreateInfo queueCreateInfo = {};
//			queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
//			queueCreateInfo.queueFamilyIndex = queueFamily;
//			queueCreateInfo.queueCount = 1;
//			queueCreateInfo.pQueuePriorities = &queuePriority;
//			queueCreateInfos.push_back(queueCreateInfo);
//		}
//
//		VkPhysicalDeviceFeatures deviceFeatures = {};
//
//		VkDeviceCreateInfo createInfo = {};
//		createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
//		createInfo.pQueueCreateInfos = queueCreateInfos.data();
//		createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
//		createInfo.pEnabledFeatures = &deviceFeatures;
//		createInfo.enabledExtensionCount = static_cast<uint32_t>(m_deviceExtensions.size());
//		createInfo.ppEnabledExtensionNames = m_deviceExtensions.data();
//
//		if (m_enableValidationLayers) {
//			createInfo.enabledLayerCount = static_cast<uint32_t>(m_validationLayers.size());
//			createInfo.ppEnabledLayerNames = m_validationLayers.data();
//		}
//		else {
//			createInfo.enabledLayerCount = 0;
//		}
//
//		if (vkCreateDevice(m_physicalDevice, &createInfo, nullptr, &m_Device) != VK_SUCCESS) {
//			throw std::runtime_error("failed to create logical device!");
//		}
//
//		vkGetDeviceQueue(m_Device, indices.graphicsFamily.value(), 0, &m_graphicsQueue);
//		vkGetDeviceQueue(m_Device, indices.presentFamily.value(), 0, &m_presentQueue);
//	}
//
//	void pickPhysicalDevice() {
//		uint32_t deviceCount = 0;
//		vkEnumeratePhysicalDevices(m_vkInstance, &deviceCount, nullptr);
//
//		if (deviceCount == 0) {
//			throw std::runtime_error("failed to find GPUs with Vulkan support!");
//		}
//
//		std::vector<VkPhysicalDevice> devices(deviceCount);
//		vkEnumeratePhysicalDevices(m_vkInstance, &deviceCount, devices.data());
//
//		for (const auto& device : devices) {
//			if (isDeviceSuitable(device)) {
//				m_physicalDevice = device;
//				break;
//			}
//		}
//
//		if (m_physicalDevice == VK_NULL_HANDLE) {
//			throw std::runtime_error("failed to find a suitable GPU!");
//		}
//	}
//
//	bool checkDeviceExtensionSupport(VkPhysicalDevice device) {
//		uint32_t extensionCount;
//		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);
//
//		std::vector<VkExtensionProperties> availableExtensions(extensionCount);
//		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());
//
//		std::set<std::string> requiredExtensions(m_deviceExtensions.begin(), m_deviceExtensions.end());
//
//		for (const auto& extension : availableExtensions) {
//			requiredExtensions.erase(extension.extensionName);
//		}
//
//		return requiredExtensions.empty();
//	}
//
//	bool isDeviceSuitable(VkPhysicalDevice device) {
//		VkPhysicalDeviceProperties deviceProperties;
//		vkGetPhysicalDeviceProperties(device, &deviceProperties);
//
//		VkPhysicalDeviceFeatures deviceFeatures;
//		vkGetPhysicalDeviceFeatures(device, &deviceFeatures);
//
//		static int deviceCount = 0;
//		std::cout << "Available device #" << deviceCount << ": " << deviceProperties.deviceName << std::endl;
//		deviceCount++;
//
//		QueueFamilyIndices indices = findQueueFamilies(device);
//
//		bool extensionsSupported = checkDeviceExtensionSupport(device);
//
//		bool swapChainAdequate = false;
//		if (extensionsSupported) {
//			SwapChainSupportDetails swapChainSupport = querySwapChainSupport(device);
//			swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
//		}
//
//		return deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU 
//			&& deviceFeatures.geometryShader
//			&& indices.isComplete() 
//			&& swapChainAdequate
//			&& extensionsSupported;
//	}
//
//	void initWindow() {
//		glfwInit();
//
//		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
//		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
//
//		m_pWindow = glfwCreateWindow(m_Width, m_Height, "Project O01", nullptr, nullptr);
//	}
//
//	bool checkValidationLayerSupport() {
//		uint32_t layerCount;
//		vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
//
//		std::vector<VkLayerProperties> availableLayers(layerCount);
//		vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());
//
//		for (const auto& layerName : m_validationLayers) {
//			bool layerFound = false;
//
//			for (const auto& layerProperties : availableLayers) {
//				if (strcmp(layerName, layerProperties.layerName) == 0) {
//					layerFound = true;
//					break;
//				}
//			}
//		
//			if (!layerFound) {
//				return false;
//			}
//		}
//
//		return true;
//	}
//
//	void setupVulkanDebugMessenger() {
//		if (!m_enableValidationLayers) return;
//
//		VkDebugUtilsMessengerCreateInfoEXT createInfo = {};
//		createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
//		createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
//		createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
//		createInfo.pfnUserCallback = debugCallback;
//		createInfo.pUserData = nullptr;
//
//		if (CreateDebugUtilsMessengerEXT(m_vkInstance, &createInfo, nullptr, &m_vkDebugMessenger) != VK_SUCCESS) {
//			throw std::runtime_error("failed to set up debug messenger!");
//		}
//	}
//
//	std::vector<const char*> getRequiredExtensions() {
//		uint32_t glfwExtensionCount = 0;
//		const char** glfwExtensions;
//		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
//
//		std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
//
//		if (m_enableValidationLayers) {
//			extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
//		}
//
//		return extensions;
//	}
//
//	void mainLoop() {
//		while (!glfwWindowShouldClose(m_pWindow)) {
//			glfwPollEvents();
//		}
//	}
//
//	void cleanup() {
//		if (m_enableValidationLayers) {
//			DestroyDebugUtilsMessengerEXT(m_vkInstance, m_vkDebugMessenger, nullptr);
//		}
//
//		vkDestroySwapchainKHR(m_Device, m_swapChain, nullptr);
//		vkDestroyDevice(m_Device, nullptr);
//		vkDestroySurfaceKHR(m_vkInstance, m_Surface, nullptr);
//		vkDestroyInstance(m_vkInstance, nullptr);
//		glfwDestroyWindow(m_pWindow);
//		glfwTerminate();
//	}
//
//	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
//														VkDebugUtilsMessageTypeFlagsEXT messageType,
//														const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
//														void* pUserData) {
//		std::cerr << "HelloWorldApplication::debugCallback(): Validation layer: " << pCallbackData->pMessage << std::endl;
//
//		return VK_FALSE;
//	}
//
//private:
//	const int m_Width = 800;
//	const int m_Height = 600;
//	GLFWwindow * m_pWindow;
//	VkInstance m_vkInstance;
//	VkDebugUtilsMessengerEXT m_vkDebugMessenger;
//	VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
//	VkDevice m_Device;
//	VkQueue m_graphicsQueue;
//	VkSurfaceKHR m_Surface;
//	VkQueue m_presentQueue;
//	VkSwapchainKHR m_swapChain;
//	std::vector<VkImage> m_swapChainImages;
//	VkFormat m_swapChainImageFormat;
//	VkExtent2D m_swapChainExtent;
//
//	const std::vector<const char*> m_validationLayers = {
//		"VK_LAYER_KHRONOS_validation"
//	};
//
//	const std::vector<const char*> m_deviceExtensions = {
//		VK_KHR_SWAPCHAIN_EXTENSION_NAME
//	};
//
//#ifdef NDEBUG
//	const bool m_enableValidationLayers = false;
//#else
//	const bool m_enableValidationLayers = true;
//#endif
//};
//
//int main() 
//{
//	HelloWorldApplication app;
//
//	try {
//		app.run();
//	}
//	catch (const std::exception& e) {
//		std::cerr << e.what() << std::endl;
//		return EXIT_FAILURE;
//	}
//
//	return EXIT_SUCCESS;
//}

int main() {
	return 0;
}