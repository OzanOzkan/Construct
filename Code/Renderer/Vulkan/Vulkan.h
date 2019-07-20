#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vector>

class CVulkan {
public:
	void start();

protected:
	void initWindow();
	void createVulkanInstance();
	std::vector<const char*> getRequiredExtensions();
	bool checkValidationLayerSupport();

protected:
	const int m_width = 800;
	const int m_height = 600;
	const char* m_title = { "Project O01" };
	GLFWwindow * m_pWindow;
	VkInstance m_vkInstance;

#ifdef NDEBUG
	const bool m_enableValidationLayers = false;
#else
	const bool m_enableValidationLayers = true;
#endif

	const std::vector<const char*> m_validationLayers = {
		"VK_LAYER_KHRONOS_validation"
	};
};