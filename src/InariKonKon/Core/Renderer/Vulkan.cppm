module;

#define VULKAN_HPP_NO_CONSTRUCTORS
#include "vulkan/vulkan.hpp"

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

export module Core:Vulkan;

import :Renderer;

import Utility;

export namespace ikk
{
    class Vulkan final : public Renderer
    {
    public:
        explicit Vulkan(GLFWwindow* window) noexcept;

        Vulkan(const Vulkan&) noexcept = delete;
        Vulkan(Vulkan&&) noexcept = default;

        Vulkan& operator=(const Vulkan&) noexcept = delete;
        Vulkan& operator=(Vulkan&&) noexcept = default;

        ~Vulkan() noexcept = default;

        [[nodiscard]] bool isValid() const noexcept override;
    private:
        bool m_valid = false;

        vk::UniqueInstance m_instance;
        vk::UniqueSurfaceKHR m_surface;
    };
}

namespace ikk
{
    Vulkan::Vulkan(GLFWwindow* window) noexcept
    {
        this->m_valid = false;

        if (glfwVulkanSupported() == GLFW_FALSE)
            return;

        //TODO: Init vulkan stuff...
        const char* appName = glfwGetWindowTitle(window);
        const vk::ApplicationInfo appInfo
            {
                .pApplicationName = appName,
                .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
                .pEngineName = "InariKonKon",
                .engineVersion = VK_MAKE_VERSION(1, 0, 0),
                .apiVersion = VK_API_VERSION_1_4
            };

        std::uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
        const std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

        vk::InstanceCreateInfo createInfo
            {
                .pApplicationInfo = &appInfo,
                .enabledExtensionCount = static_cast<std::uint32_t>(extensions.size()),
                .ppEnabledExtensionNames = extensions.data()
            };
        //TODO: Can't find VK_LAYER_KHRONOS_validation
        const std::vector<const char*> validationLayers = { "VK_LAYER_KHRONOS_validation" };
        if constexpr (isDebug())
        {
            createInfo.enabledExtensionCount = static_cast<std::uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();
        }

        this->m_instance = vk::createInstanceUnique(createInfo);
        if (!this->m_instance)
            return;

        VkSurfaceKHR tempSurface;
        if (glfwCreateWindowSurface(this->m_instance.get(), window, nullptr, &tempSurface) != VK_SUCCESS)
            return;
        this->m_surface = vk::UniqueSurfaceKHR(tempSurface, this->m_instance.get());



        this->m_valid = true;
    }

    bool Vulkan::isValid() const noexcept
    {
        return this->m_valid;
    }
}
