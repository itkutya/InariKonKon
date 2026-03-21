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
    class Vulkan final : public Renderer::Type
    {
    public:
        explicit Vulkan(GLFWwindow* window) noexcept;

        Vulkan(const Vulkan&) noexcept = default;
        Vulkan(Vulkan&&) noexcept = default;

        Vulkan& operator=(const Vulkan&) noexcept = default;
        Vulkan& operator=(Vulkan&&) noexcept = default;

        ~Vulkan() noexcept;

        [[nodiscard]] bool isValid() const noexcept override;
    private:
        bool m_valid = false;

        vk::Instance m_instance;
        vk::SurfaceKHR m_surface;
    };
}

namespace ikk
{
    Vulkan::Vulkan(GLFWwindow* window) noexcept
    {
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

        const auto availableLayers = vk::enumerateInstanceLayerProperties();

        const std::vector<const char*> validationLayers = { "VK_LAYER_KHRONOS_validation" };
        const vk::InstanceCreateInfo createInfo
        {
            .pApplicationInfo = &appInfo,
            .enabledLayerCount = U32(validationLayers.size()),
            .ppEnabledLayerNames = validationLayers.data(),
            .enabledExtensionCount = glfwExtensionCount,
            .ppEnabledExtensionNames = glfwExtensions
        };

        if (vk::createInstance(&createInfo, nullptr, &m_instance) != vk::Result::eSuccess)
            return;

        VkSurfaceKHR rawSurface{};
        if (glfwCreateWindowSurface(static_cast<VkInstance>(m_instance), window, nullptr, &rawSurface) != VK_SUCCESS)
            return;

        m_surface = rawSurface;

        this->m_valid = true;
    }

    Vulkan::~Vulkan() noexcept
    {
        if (this->m_instance)
        {
            if (this->m_surface)
                this->m_instance.destroySurfaceKHR(this->m_surface);
            this->m_instance.destroy();
        }
    }

    bool Vulkan::isValid() const noexcept
    {
        return this->m_valid;
    }
}
