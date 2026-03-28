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
        vk::PhysicalDevice m_physicalDevice;
        vk::Device m_device;
        vk::Queue m_graphicsQueue;
        vk::Queue m_presentQueue;

        [[nodiscard]] bool createInstance(GLFWwindow* const window) noexcept;
        [[nodiscard]] bool createDebugMessenger() noexcept;
        [[nodiscard]] bool createSurface(GLFWwindow* const window) noexcept;
        [[nodiscard]] bool pickPhysicalDevice() noexcept;
        [[nodiscard]] bool createLogicalDevice() noexcept;

        [[nodiscard]] static bool checkLayerSupport(const std::vector<const char*>& layers) noexcept;
        [[nodiscard]] static std::vector<const char*> getRequiredExtensions() noexcept;
        [[nodiscard]] static constexpr vk::DebugUtilsMessengerCreateInfoEXT& getDebugMessengerInfo() noexcept;

        //TODO:
        /*
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
        if (this->pickPhysicalDevice() == false)                                        return;
        if (this->createLogicalDevice() == false)                                       return;
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
            if (this->m_device) this->m_device.destroy();
            if (this->m_surface) this->m_instance.destroySurfaceKHR(this->m_surface);
            if (this->m_debugMessenger) this->m_instance.destroyDebugUtilsMessengerEXT(this->m_debugMessenger);
            this->m_instance.destroy();
        }
    }

    bool Vulkan::isValid() const noexcept
    {
        return this->m_valid;
    }

    bool Vulkan::createInstance(GLFWwindow* const window) noexcept
    {
        vk::detail::DynamicLoader dl{};
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
        return BOOL(this->m_instance);
    }

    bool Vulkan::createDebugMessenger() noexcept
    {
        this->m_debugMessenger = this->m_instance.createDebugUtilsMessengerEXT(getDebugMessengerInfo());
        return BOOL(this->m_debugMessenger);
    }

    bool Vulkan::createSurface(GLFWwindow* const window) noexcept
    {
        if (VkSurfaceKHR temp; glfwCreateWindowSurface(this->m_instance, window, nullptr, &temp) == VK_SUCCESS)
            this->m_surface = temp;
        return BOOL(this->m_surface);
    }

    bool Vulkan::pickPhysicalDevice() noexcept
    {
        const std::vector<vk::PhysicalDevice> devices = this->m_instance.enumeratePhysicalDevices();
        if (devices.empty())
            return false;

        const auto rateDevice = [](const vk::PhysicalDevice& device) noexcept -> std::int32_t
        {
            const vk::PhysicalDeviceProperties properties = device.getProperties();
            const vk::PhysicalDeviceFeatures features = device.getFeatures();

            using RequimentFunc = bool(*)(const vk::PhysicalDeviceFeatures&) noexcept;
            constexpr const auto requirements = std::array<RequimentFunc, 2>
                {
                    [](const vk::PhysicalDeviceFeatures& f) noexcept -> bool { return f.tessellationShader; },
                    [](const vk::PhysicalDeviceFeatures& f) noexcept -> bool { return f.geometryShader; }
                };
            if (std::ranges::all_of(requirements, [&features](const auto& req) { return req(features); }) == false) return 0;

            using ScoringFunc = std::int32_t(*)(const vk::PhysicalDeviceProperties&) noexcept;
            constexpr const auto scoringRules = std::array<ScoringFunc, 2>
                {
                    [](const vk::PhysicalDeviceProperties& prop) noexcept -> std::int32_t { return prop.deviceType == vk::PhysicalDeviceType::eDiscreteGpu ? 1000 : 0; },
                    [](const vk::PhysicalDeviceProperties& prop) noexcept -> std::int32_t { return I32(prop.limits.maxImageDimension2D); }
                };
            return std::ranges::fold_left(scoringRules | std::views::transform([&properties](const auto& rule) noexcept { return rule(properties); }), 0, std::plus{});
        };

        using DeviceRank = std::pair<const vk::PhysicalDevice&, std::int32_t>;
        auto ranked = devices | std::views::transform(
            [&rateDevice](const vk::PhysicalDevice& device) { return DeviceRank{ device, rateDevice(device) }; });

        const auto compare = [](const DeviceRank& left, const DeviceRank& right) noexcept -> bool { return left.second < right.second; };
        auto best = std::ranges::max_element(ranked, compare);

        if (best == ranked.end())
            return false;

        auto&& [device, score] = *best;
        if (score <= 0)
            return false;

        this->m_physicalDevice = device;
        return BOOL(this->m_physicalDevice);
    }

    //TODO:
    bool Vulkan::createLogicalDevice() noexcept
    {
        const auto queueFamilies = m_physicalDevice.getQueueFamilyProperties();

        std::optional<std::uint32_t> graphicsFamily;
        std::optional<std::uint32_t> presentFamily;

        for (std::uint32_t i = 0; i < queueFamilies.size(); ++i)
        {
            if (queueFamilies[i].queueFlags & vk::QueueFlagBits::eGraphics)
                graphicsFamily = i;

            if (m_physicalDevice.getSurfaceSupportKHR(i, m_surface))
                presentFamily = i;

            if (graphicsFamily && presentFamily)
                break;
        }

        if (!graphicsFamily || !presentFamily)
            return false;

        // --- 2. Unique queue families ---
        std::vector<std::uint32_t> uniqueFamilies;

        uniqueFamilies.push_back(*graphicsFamily);
        if (*presentFamily != *graphicsFamily)
            uniqueFamilies.push_back(*presentFamily);

        // --- 3. Queue create infos (ranges-style) ---
        const float priority = 1.0f;

        std::vector<vk::DeviceQueueCreateInfo> queueCreateInfos;
        queueCreateInfos.reserve(uniqueFamilies.size());

        std::ranges::transform(
            uniqueFamilies,
            std::back_inserter(queueCreateInfos),
            [&](std::uint32_t family)
            {
                return vk::DeviceQueueCreateInfo{}
                    .setQueueFamilyIndex(family)
                    .setQueueCount(1)
                    .setPQueuePriorities(&priority);
            }
        );

        // --- 4. Device features ---
        vk::PhysicalDeviceFeatures deviceFeatures{};
        deviceFeatures.setSamplerAnisotropy(VK_TRUE);

        // --- 5. Required extensions ---
        const std::vector<const char*> deviceExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
        };

        // --- 6. Create device ---
        vk::DeviceCreateInfo createInfo{};
        createInfo
            .setQueueCreateInfos(queueCreateInfos)
            .setPEnabledFeatures(&deviceFeatures)
            .setPEnabledExtensionNames(deviceExtensions);

        try
        {
            m_device = m_physicalDevice.createDevice(createInfo);
        }
        catch (const vk::SystemError&)
        {
            return false;
        }

        // --- 7. Retrieve queues ---
        m_graphicsQueue = m_device.getQueue(*graphicsFamily, 0);
        m_presentQueue  = m_device.getQueue(*presentFamily, 0);

        return true;
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
        static const auto debugCallback = []([[maybe_unused]] vk::DebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
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
