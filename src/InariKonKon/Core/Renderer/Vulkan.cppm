module;

#include <ranges>

#define VULKAN_HPP_NO_CONSTRUCTORS
#define VULKAN_HPP_DISPATCH_LOADER_DYNAMIC 1
#include "vulkan/vulkan.hpp"

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

export module Core:Vulkan;

import :Renderer;

import Utility;
import Log;

export namespace ikk
{
    class Vulkan final : public Renderer::Type
    {
    public:
        explicit Vulkan(GLFWwindow* const window) noexcept;

        Vulkan(const Vulkan& other) noexcept;
        Vulkan(Vulkan&& other) noexcept;

        Vulkan& operator=(const Vulkan& other) noexcept;
        Vulkan& operator=(Vulkan&& other) noexcept;

        ~Vulkan() noexcept;

        [[nodiscard]] bool isValid() const noexcept override;
    private:
        bool m_valid = false;

        inline static constexpr bool s_enableValidationLayers = isDebug();

        vk::Instance m_instance;
        vk::DebugUtilsMessengerEXT m_debugMessenger;
        vk::SurfaceKHR m_surface;

        [[nodiscard]] bool createInstance(GLFWwindow* const window) noexcept;
        [[nodiscard]] bool createDebugMessenger() noexcept;
        [[nodiscard]] bool createSurface(GLFWwindow* const window) noexcept;

        [[nodiscard]] static bool checkLayerSupport(const std::vector<const char*>& layers) noexcept;
        [[nodiscard]] static std::vector<const char*> getRequiredExtensions() noexcept;
        [[nodiscard]] static constexpr vk::DebugUtilsMessengerCreateInfoEXT& getDebugMessengerInfo() noexcept;

        //TODO:
        /*
        pickPhysicalDevice();
        createLogicalDevice();
        createSwapChain();
        createImageViews();
        createRenderPass();
        createGraphicsPipeline();
        createFramebuffers();
        createCommandPool();
        createCommandBuffers();
        createSyncObjects();
        */
    };
}

namespace ikk
{
    Vulkan::Vulkan(GLFWwindow* const window) noexcept
    {
        if (glfwVulkanSupported() == GLFW_FALSE)                                        return;
        if (this->createInstance(window) == false)                                      return;
        if (s_enableValidationLayers == true && this->createDebugMessenger() == false)  return;
        if (this->createSurface(window) == false)                                       return;

        this->m_valid = true;
    }

    Vulkan::Vulkan(const Vulkan& other) noexcept
    {
        //TODO:
    }

    Vulkan::Vulkan(Vulkan&& other) noexcept
    {
        //TODO:
    }

    Vulkan& Vulkan::operator=(const Vulkan& other) noexcept
    {
        //TODO:
        return *this;
    }

    Vulkan& Vulkan::operator=(Vulkan&& other) noexcept
    {
        //TODO:
        return *this;
    }

    Vulkan::~Vulkan() noexcept
    {
        if (this->m_instance)
        {
            if (this->m_surface)
                this->m_instance.destroySurfaceKHR(this->m_surface);

            if (this->m_debugMessenger)
                this->m_instance.destroyDebugUtilsMessengerEXT(this->m_debugMessenger);

            this->m_instance.destroy();
        }
    }

    bool Vulkan::isValid() const noexcept
    {
        return this->m_valid;
    }

    bool Vulkan::createInstance(GLFWwindow* const window) noexcept
    {
        vk::detail::DynamicLoader dl;
        auto getProc = dl.getProcAddress<PFN_vkGetInstanceProcAddr>("vkGetInstanceProcAddr");
        VULKAN_HPP_DEFAULT_DISPATCHER.init(getProc);

        const std::vector<const char*> validationLayers = { "VK_LAYER_KHRONOS_validation" };
        if (s_enableValidationLayers == true && checkLayerSupport(validationLayers) == false)
            return false;

        const char* appName = glfwGetWindowTitle(window);
        const vk::ApplicationInfo appInfo
        {
            .pApplicationName = appName,
            .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
            .pEngineName = "InariKonKon",
            .engineVersion = VK_MAKE_VERSION(1, 0, 0),
            .apiVersion = VK_API_VERSION_1_4
        };

        const std::vector<const char*> extensions = getRequiredExtensions();
        const vk::InstanceCreateInfo createInfo
        {
            .pNext = (s_enableValidationLayers == true) ? &getDebugMessengerInfo() : nullptr,
            .pApplicationInfo = &appInfo,
            .enabledLayerCount = (s_enableValidationLayers == true) ? U32(validationLayers.size()) : 0,
            .ppEnabledLayerNames = (s_enableValidationLayers == true) ? validationLayers.data() : nullptr,
            .enabledExtensionCount = U32(extensions.size()),
            .ppEnabledExtensionNames = extensions.data()
        };

        this->m_instance = vk::createInstance(createInfo);
        VULKAN_HPP_DEFAULT_DISPATCHER.init(this->m_instance);
        return this->m_instance;
    }

    bool Vulkan::createDebugMessenger() noexcept
    {
        this->m_debugMessenger = this->m_instance.createDebugUtilsMessengerEXT(getDebugMessengerInfo());
        return this->m_debugMessenger;
    }

    bool Vulkan::createSurface(GLFWwindow* const window) noexcept
    {
        if (VkSurfaceKHR temp; glfwCreateWindowSurface(this->m_instance, window, nullptr, &temp) == VK_SUCCESS)
            this->m_surface = temp;
        return this->m_surface;
    }

    bool Vulkan::checkLayerSupport(const std::vector<const char*>& layers) noexcept
    {
        const auto availableLayers = vk::enumerateInstanceLayerProperties();

        const auto foundCount = std::ranges::count_if(layers,
            [&availableLayers](std::string_view layer) noexcept
            {
                return std::ranges::any_of(availableLayers,
                    [layer](const vk::LayerProperties& prop) noexcept
                    {
                        return layer == prop.layerName;
                    });
            });

        return static_cast<std::size_t>(foundCount) == layers.size();
    }

    std::vector<const char*> Vulkan::getRequiredExtensions() noexcept
    {
        std::uint32_t count = 0;
        const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&count);

        std::vector<const char*> extensions(glfwExtensions, glfwExtensions + count);

        if constexpr (s_enableValidationLayers == true)
            extensions.emplace_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

        return extensions;
    }

    constexpr vk::DebugUtilsMessengerCreateInfoEXT& Vulkan::getDebugMessengerInfo() noexcept
    {
        static auto debugCallback = []([[maybe_unused]] vk::DebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                       [[maybe_unused]] vk::DebugUtilsMessageTypeFlagsEXT messageType,
                                       [[maybe_unused]] const vk::DebugUtilsMessengerCallbackDataEXT* pCallbackData,
                                       [[maybe_unused]] void* pUserData) noexcept -> VKAPI_ATTR vk::Bool32 VKAPI_CALL
        {
            switch (messageSeverity)
            {
            case vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose: [[fallthrough]];
            case vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo:
                Print<Log::Level::Info>("Validation Layer: {}", pCallbackData->pMessage);
                break;
            case vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning:
                Print<Log::Level::Warning>("Validation Layer: {}", pCallbackData->pMessage);
                break;
            case vk::DebugUtilsMessageSeverityFlagBitsEXT::eError:
                Print<Log::Level::Error>("Validation Layer: {}", pCallbackData->pMessage);
                break;
            }
            return VK_FALSE;
        };

        static vk::DebugUtilsMessengerCreateInfoEXT debugCreateInfo
        {
            .messageSeverity =
                vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose |
                vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning |
                vk::DebugUtilsMessageSeverityFlagBitsEXT::eError,
            .messageType =
                vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral |
                vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation |
                vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance,
            .pfnUserCallback = debugCallback,
            .pUserData = nullptr
        };
        return debugCreateInfo;
    }
}
