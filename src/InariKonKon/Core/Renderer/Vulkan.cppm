module;

#include <ranges>

#define VULKAN_HPP_NO_CONSTRUCTORS
#define VULKAN_HPP_DISPATCH_LOADER_DYNAMIC 1
#include "vulkan/vulkan.hpp"

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

export module Core:Vulkan;

import :Renderer;

import DebugFeatures;
import NumericCasts;
import Shader;
import Log;

export namespace ikk
{
    class Vulkan final : public Renderer::Type
    {
    public:
        explicit Vulkan(GLFWwindow* window) noexcept;

        //TODO:
        Vulkan(const Vulkan& other) noexcept = default;
        //TODO:
        Vulkan(Vulkan&& other) noexcept = default;

        //TODO:
        Vulkan& operator=(const Vulkan& other) noexcept = default;
        //TODO:
        Vulkan& operator=(Vulkan&& other) noexcept = default;

        ~Vulkan() noexcept;

        [[nodiscard]] bool isValid() const noexcept override;

        void beginRender(const Color& clearColor) noexcept override;
        void endRender() noexcept override;
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
        vk::SwapchainKHR m_swapChain;
        std::vector<vk::Image> m_swapChainImages;
        vk::Format m_swapChainImageFormat = vk::Format::eUndefined;
        vk::Extent2D m_swapChainExtent;
        std::vector<vk::ImageView> m_swapchainImageViews;
        vk::RenderPass m_renderPass;
        vk::PipelineLayout m_pipelineLayout;
        vk::Pipeline m_graphicsPipeline;
        std::vector<vk::Framebuffer> m_framebuffers;
        vk::CommandPool m_commandPool;
        std::vector<vk::CommandBuffer> m_commandBuffers;
        std::vector<vk::Semaphore> m_imageAvailableSemaphores;
        std::vector<vk::Semaphore> m_renderFinishedSemaphores;
        std::vector<vk::Fence> m_inFlightFences;

        std::optional<std::uint32_t> m_graphicsFamily;
        std::optional<std::uint32_t> m_presentFamily;

        std::size_t m_currentFrame = 0;
        std::uint32_t m_imageIndex = 0;

        [[nodiscard]] bool createInstance(GLFWwindow* window) noexcept;
        [[nodiscard]] bool createDebugMessenger() noexcept;
        [[nodiscard]] bool createSurface(GLFWwindow* window) noexcept;
        [[nodiscard]] bool pickPhysicalDevice() noexcept;
        [[nodiscard]] bool createLogicalDevice() noexcept;
        [[nodiscard]] bool createSwapChain(GLFWwindow* window) noexcept;
        [[nodiscard]] bool createImageViews() noexcept;
        [[nodiscard]] bool createRenderPass() noexcept;
        [[nodiscard]] bool createGraphicsPipeline() noexcept;
        [[nodiscard]] bool createFramebuffers() noexcept;
        [[nodiscard]] bool createCommandPool() noexcept;
        [[nodiscard]] bool createCommandBuffers() noexcept;
        [[nodiscard]] bool createSyncObjects() noexcept;

        [[nodiscard]] static bool checkLayerSupport(const std::span<const char* const>& layers) noexcept;
        [[nodiscard]] static std::vector<const char*> getRequiredExtensions() noexcept;
        [[nodiscard]] static constexpr vk::DebugUtilsMessengerCreateInfoEXT& getDebugMessengerInfo() noexcept;

        struct SwapChainSupportDetails
        {
            vk::SurfaceCapabilitiesKHR capabilities;
            std::vector<vk::SurfaceFormatKHR> formats;
            std::vector<vk::PresentModeKHR> presentModes;
        };

        [[nodiscard]] static SwapChainSupportDetails querySwapChainSupport(const vk::PhysicalDevice& device, const vk::SurfaceKHR& surface) noexcept;
        [[nodiscard]] static vk::SurfaceFormatKHR chooseSurfaceFormat(const std::vector<vk::SurfaceFormatKHR>& formats) noexcept;
        [[nodiscard]] static vk::PresentModeKHR choosePresentMode(const std::vector<vk::PresentModeKHR>& presentModes) noexcept;
        [[nodiscard]] static vk::Extent2D chooseExtent(const vk::SurfaceCapabilitiesKHR& capabilities, GLFWwindow* window) noexcept;
    };
}

namespace ikk
{
    Vulkan::Vulkan(GLFWwindow* window) noexcept
    {
        if (glfwVulkanSupported() == GLFW_FALSE)                                        return;
        if (this->createInstance(window) == false)                                      return;
        if (s_enableValidationLayers == true && this->createDebugMessenger() == false)  return;
        if (this->createSurface(window) == false)                                       return;
        if (this->pickPhysicalDevice() == false)                                        return;
        if (this->createLogicalDevice() == false)                                       return;
        if (this->createSwapChain(window) == false)                                     return;
        if (this->createImageViews() == false)                                          return;
        if (this->createRenderPass() == false)                                          return;
        if (this->createGraphicsPipeline() == false)                                    return;
        if (this->createFramebuffers() == false)                                        return;
        if (this->createCommandPool() == false)                                         return;
        if (this->createCommandBuffers() == false)                                      return;
        if (this->createSyncObjects() == false)                                         return;
        this->m_valid = true;
    }

    Vulkan::~Vulkan() noexcept
    {
        if (this->m_instance)
        {
            this->m_device.waitIdle();

            for (std::size_t i = 0; i < this->m_renderFinishedSemaphores.size(); ++i)
            {
                if (this->m_renderFinishedSemaphores.at(i)) this->m_device.destroySemaphore(this->m_renderFinishedSemaphores.at(i));
                if (this->m_imageAvailableSemaphores.at(i)) this->m_device.destroySemaphore(this->m_imageAvailableSemaphores.at(i));
                if (this->m_inFlightFences.at(i)) this->m_device.destroyFence(this->m_inFlightFences.at(i));
            }
            if (this->m_commandPool) this->m_device.destroyCommandPool(this->m_commandPool);
            for (const vk::Framebuffer& fb : this->m_framebuffers) this->m_device.destroyFramebuffer(fb);
            if (this->m_graphicsPipeline) this->m_device.destroyPipeline(this->m_graphicsPipeline);
            if (this->m_pipelineLayout) this->m_device.destroyPipelineLayout(this->m_pipelineLayout);
            if (this->m_renderPass) this->m_device.destroyRenderPass(this->m_renderPass);
            for (const vk::ImageView& view : this->m_swapchainImageViews) this->m_device.destroyImageView(view);
            if (this->m_swapChain) this->m_device.destroySwapchainKHR(this->m_swapChain);
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

    //TODO:
    void Vulkan::beginRender(const Color& clearColor) noexcept
    {
        vk::Result result = this->m_device.waitForFences(1, &this->m_inFlightFences[this->m_currentFrame], VK_TRUE, UINT64_MAX);
        if (result != vk::Result::eSuccess) return;

        result = this->m_device.resetFences(1, &this->m_inFlightFences[this->m_currentFrame]);
        if (result != vk::Result::eSuccess) return;

        const vk::ResultValue<uint32_t> nextImage = this->m_device.acquireNextImageKHR(
            this->m_swapChain,
            UINT64_MAX,
            this->m_imageAvailableSemaphores[this->m_currentFrame],
            nullptr
        );

        this->m_imageIndex = nextImage.value;

        vk::CommandBufferBeginInfo beginInfo{};
        this->m_commandBuffers[this->m_imageIndex].begin(beginInfo);

        const vk::ClearValue color{std::array<float, 4>{
            F32(clearColor.r) / F32(std::numeric_limits<std::uint8_t>::max()),
            F32(clearColor.g) / F32(std::numeric_limits<std::uint8_t>::max()),
            F32(clearColor.b) / F32(std::numeric_limits<std::uint8_t>::max()),
            F32(clearColor.a) / F32(std::numeric_limits<std::uint8_t>::max()) }};

        vk::RenderPassBeginInfo renderPassInfo{};
        renderPassInfo.renderPass = this->m_renderPass;
        renderPassInfo.framebuffer = this->m_framebuffers[this->m_imageIndex];
        renderPassInfo.renderArea.offset = {0, 0};
        renderPassInfo.renderArea.extent = this->m_swapChainExtent;
        renderPassInfo.clearValueCount = 1;
        renderPassInfo.pClearValues = &color;

        this->m_commandBuffers[this->m_imageIndex].beginRenderPass(renderPassInfo, vk::SubpassContents::eInline);
        this->m_commandBuffers[this->m_imageIndex].bindPipeline(vk::PipelineBindPoint::eGraphics, this->m_graphicsPipeline);

        // const vk::Viewport viewport{0.0f, 0.0f,
        //                       F32(this->m_swapChainExtent.width),
        //                       F32(this->m_swapChainExtent.height),
        //                       0.0f, 1.0f};
        // this->m_commandBuffers[imageIndex].setViewport(0, viewport);
        //
        // const vk::Rect2D scissor{{0,0}, this->m_swapChainExtent};
        // this->m_commandBuffers[imageIndex].setScissor(0, scissor);
    }

    //TODO:
    void Vulkan::endRender() noexcept
    {
        this->m_commandBuffers[this->m_imageIndex].endRenderPass();
        this->m_commandBuffers[this->m_imageIndex].end();

        vk::Semaphore waitSemaphores[] = { this->m_imageAvailableSemaphores[this->m_imageIndex] };
        vk::Semaphore signalSemaphores[] = { this->m_renderFinishedSemaphores[this->m_imageIndex] };
        vk::PipelineStageFlags waitStages[] = {vk::PipelineStageFlagBits::eColorAttachmentOutput};

        vk::SubmitInfo submitInfo{};
        submitInfo.waitSemaphoreCount = 1;
        submitInfo.pWaitSemaphores = waitSemaphores;
        submitInfo.pWaitDstStageMask = waitStages;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &this->m_commandBuffers[this->m_imageIndex];
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = signalSemaphores;

        this->m_graphicsQueue.submit(submitInfo, this->m_inFlightFences[this->m_currentFrame]);

        vk::PresentInfoKHR presentInfo{};
        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pWaitSemaphores = signalSemaphores;
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = &this->m_swapChain;
        presentInfo.pImageIndices = &this->m_imageIndex;

        if (this->m_presentQueue.presentKHR(presentInfo) != vk::Result::eSuccess) return;

        this->m_currentFrame = (this->m_currentFrame + 1) % this->m_swapChainImages.size();
    }

    bool Vulkan::createInstance(GLFWwindow* window) noexcept
    {
        const vk::detail::DynamicLoader dl{};
        const auto getProc = dl.getProcAddress<PFN_vkGetInstanceProcAddr>("vkGetInstanceProcAddr");
        VULKAN_HPP_DEFAULT_DISPATCHER.init(getProc);

        constexpr std::array validationLayers = { "VK_LAYER_KHRONOS_validation" };
        if (s_enableValidationLayers == true && checkLayerSupport(std::span{validationLayers}) == false)
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

    bool Vulkan::createSurface(GLFWwindow* window) noexcept
    {
        if (VkSurfaceKHR temp; glfwCreateWindowSurface(this->m_instance, window, nullptr, &temp) == VK_SUCCESS)
            this->m_surface = temp;
        return BOOL(this->m_surface);
    }

    bool Vulkan::pickPhysicalDevice() noexcept
    {
        const auto devices = this->m_instance.enumeratePhysicalDevices();
        if (devices.empty()) return false;

        const auto rateDevice = [](const vk::PhysicalDevice& device) noexcept -> std::int32_t
        {
            const vk::PhysicalDeviceProperties properties = device.getProperties();
            const vk::PhysicalDeviceFeatures features = device.getFeatures();

            using RequimentFunc = bool(*)(const vk::PhysicalDeviceFeatures&) noexcept;
            constexpr const auto requirements = std::array<RequimentFunc, 2>
                {
                    //TODO:
                    [](const vk::PhysicalDeviceFeatures& f) noexcept -> bool { return f.tessellationShader; },
                    [](const vk::PhysicalDeviceFeatures& f) noexcept -> bool { return f.geometryShader; }
                };
            if (std::ranges::all_of(requirements, [&features](const auto& req) { return req(features); }) == false) return 0;

            using ScoringFunc = std::int32_t(*)(const vk::PhysicalDeviceProperties&) noexcept;
            constexpr const auto scoringRules = std::array<ScoringFunc, 2>
                {
                    //TODO:
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

        if (best == ranked.end()) return false;

        auto&& [device, score] = *best;
        if (score <= 0) return false;

        this->m_physicalDevice = device;
        return BOOL(this->m_physicalDevice);
    }

    bool Vulkan::createLogicalDevice() noexcept
    {
        const auto queueFamilies = this->m_physicalDevice.getQueueFamilyProperties();

        for (std::uint32_t i = 0; i < queueFamilies.size(); ++i)
        {
            if (queueFamilies.at(i).queueFlags & vk::QueueFlagBits::eGraphics) this->m_graphicsFamily = i;
            if (this->m_physicalDevice.getSurfaceSupportKHR(i, this->m_surface)) this->m_presentFamily = i;
            if (this->m_graphicsFamily && this->m_presentFamily) break;
        }

        if (!this->m_graphicsFamily || !this->m_presentFamily) return false;

        std::vector<std::uint32_t> uniqueFamilies;
        uniqueFamilies.emplace_back(this->m_graphicsFamily.value());
        if (this->m_presentFamily.value() != this->m_graphicsFamily.value())
            uniqueFamilies.emplace_back(this->m_presentFamily.value());

        std::vector<vk::DeviceQueueCreateInfo> queueCreateInfos;
        queueCreateInfos.reserve(uniqueFamilies.size());
        std::ranges::transform(uniqueFamilies, std::back_inserter(queueCreateInfos),
            [](std::uint32_t family) noexcept
            {
                static constexpr float priority = 1.0f;
                return vk::DeviceQueueCreateInfo{}
                    .setQueueFamilyIndex(family)
                    .setQueueCount(1)
                    .setPQueuePriorities(&priority);
            });

        //TODO:
        vk::PhysicalDeviceFeatures deviceFeatures{};
        deviceFeatures.setSamplerAnisotropy(VK_TRUE);
        deviceFeatures.setTessellationShader(VK_TRUE);

        constexpr std::array<const char*, 1> deviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

        vk::DeviceCreateInfo createInfo{};
        createInfo
            .setQueueCreateInfos(queueCreateInfos)
            .setPEnabledFeatures(&deviceFeatures)
            .setPEnabledExtensionNames(deviceExtensions);

        this->m_device = this->m_physicalDevice.createDevice(createInfo);

        if (!this->m_device) return false;

        this->m_graphicsQueue = this->m_device.getQueue(this->m_graphicsFamily.value(), 0);
        this->m_presentQueue  = this->m_device.getQueue(this->m_presentFamily.value(), 0);

        if (!this->m_graphicsQueue || !this->m_presentQueue) return false;

        return true;
    }

    bool Vulkan::createSwapChain(GLFWwindow* window) noexcept
    {
        const auto [capabilities,
                    surfaceFormats,
                    presentModes] = querySwapChainSupport(this->m_physicalDevice, this->m_surface);
        if (surfaceFormats.empty() || presentModes.empty()) return false;

        const auto [format, colorSpace] = chooseSurfaceFormat(surfaceFormats);
        const vk::PresentModeKHR presentMode = choosePresentMode(presentModes);
        const vk::Extent2D extent = chooseExtent(capabilities, window);

        std::uint32_t imageCount = capabilities.minImageCount + 1;
        if (capabilities.maxImageCount > 0 && imageCount > capabilities.maxImageCount)
            imageCount = capabilities.maxImageCount;

        const auto graphicsFamily = this->m_graphicsFamily.value();
        const auto presentFamily  = this->m_presentFamily.value();

        std::array<std::uint32_t, 2> queueFamilyIndices = { graphicsFamily, presentFamily };

        vk::SwapchainCreateInfoKHR createInfo{};
        createInfo
            .setSurface(this->m_surface)
            .setMinImageCount(imageCount)
            .setImageFormat(format)
            .setImageColorSpace(colorSpace)
            .setImageExtent(extent)
            .setImageArrayLayers(1)
            .setImageUsage(vk::ImageUsageFlagBits::eColorAttachment);

        if (graphicsFamily != presentFamily)
            createInfo
                .setImageSharingMode(vk::SharingMode::eConcurrent)
                .setQueueFamilyIndices(queueFamilyIndices);
        else
            createInfo.setImageSharingMode(vk::SharingMode::eExclusive);

        createInfo
            .setPreTransform(capabilities.currentTransform)
            .setCompositeAlpha(vk::CompositeAlphaFlagBitsKHR::eOpaque)
            .setPresentMode(presentMode)
            .setClipped(true)
            .setOldSwapchain(nullptr);

        this->m_swapChain = this->m_device.createSwapchainKHR(createInfo);

        if (!this->m_swapChain) return false;

        this->m_swapChainImages = this->m_device.getSwapchainImagesKHR(this->m_swapChain);

        this->m_swapChainImageFormat = format;
        this->m_swapChainExtent = extent;

        return true;
    }

    bool Vulkan::createImageViews() noexcept
    {
        this->m_swapchainImageViews.resize(this->m_swapChainImages.size());

        for (std::size_t i = 0; i < this->m_swapChainImages.size(); i++)
        {
            const vk::Image& image = this->m_swapChainImages.at(i);

            vk::ImageViewCreateInfo createInfo{};
            createInfo.image = image;
            createInfo.viewType = vk::ImageViewType::e2D;
            createInfo.format = this->m_swapChainImageFormat;
            createInfo.components =
            {
                vk::ComponentSwizzle::eIdentity,
                vk::ComponentSwizzle::eIdentity,
                vk::ComponentSwizzle::eIdentity,
                vk::ComponentSwizzle::eIdentity
            };
            createInfo.subresourceRange =
            {
                vk::ImageAspectFlagBits::eColor,
                0, 1,
                0, 1
            };

            this->m_swapchainImageViews.at(i) = this->m_device.createImageView(createInfo);
            if (!this->m_swapchainImageViews.at(i)) return false;
        }
        return true;
    }

    bool Vulkan::createRenderPass() noexcept
    {
        vk::AttachmentDescription colorAttachment{};
        colorAttachment.format = this->m_swapChainImageFormat;
        colorAttachment.samples = vk::SampleCountFlagBits::e1;
        colorAttachment.loadOp = vk::AttachmentLoadOp::eClear;
        colorAttachment.storeOp = vk::AttachmentStoreOp::eStore;
        colorAttachment.initialLayout = vk::ImageLayout::eUndefined;
        colorAttachment.finalLayout = vk::ImageLayout::ePresentSrcKHR;

        vk::AttachmentReference colorRef{};
        colorRef.attachment = 0;
        colorRef.layout = vk::ImageLayout::eColorAttachmentOptimal;

        vk::SubpassDescription subpass{};
        subpass.pipelineBindPoint = vk::PipelineBindPoint::eGraphics;
        subpass.colorAttachmentCount = 1;
        subpass.pColorAttachments = &colorRef;

        vk::SubpassDependency dependency{};
        dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
        dependency.dstSubpass = 0;
        dependency.srcStageMask = vk::PipelineStageFlagBits::eColorAttachmentOutput;
        dependency.dstStageMask = vk::PipelineStageFlagBits::eColorAttachmentOutput;
        dependency.dstAccessMask = vk::AccessFlagBits::eColorAttachmentWrite;

        vk::RenderPassCreateInfo renderPassInfo{};
        renderPassInfo.attachmentCount = 1;
        renderPassInfo.pAttachments = &colorAttachment;
        renderPassInfo.subpassCount = 1;
        renderPassInfo.pSubpasses = &subpass;
        renderPassInfo.dependencyCount = 1;
        renderPassInfo.pDependencies = &dependency;

        this->m_renderPass = this->m_device.createRenderPass(renderPassInfo);
        if (!this->m_renderPass) return false;
        return true;
    }

    bool Vulkan::createGraphicsPipeline() noexcept
    {
        //TODO:
        VertexShader vertexShader{std::string_view{R"(
            #version 450

            void main()
            {
                gl_Position = vec4(0.0, 0.0, 0.0, 1.0);
            }
            )"}};
        FragmentShader fragmentShader{std::string_view{R"(
            #version 450

            layout(location = 0) out vec4 outColor;

            void main()
            {
                outColor = vec4(1.0);
            }
            )"}};

        const auto createVulkanShaderModule = []<Shader::Type T>(const vk::Device& device, const BasicShader<T>& shader) noexcept
        {
            const std::vector<std::uint32_t> code = shader.convertToSPIRV();

            vk::ShaderModuleCreateInfo createInfo{};
            createInfo.codeSize = code.size() * sizeof(std::uint32_t);
            createInfo.pCode = code.data();

            vk::ShaderModule shaderModule = device.createShaderModule(createInfo);
            return shaderModule;
        };

        vk::ShaderModule vertModule = createVulkanShaderModule(this->m_device, vertexShader);
        vk::ShaderModule fragModule = createVulkanShaderModule(this->m_device, fragmentShader);

        if (!fragModule || !vertModule) return false;

        vk::PipelineShaderStageCreateInfo vertStage{};
        vertStage.stage = vk::ShaderStageFlagBits::eVertex;
        vertStage.module = vertModule;
        vertStage.pName = "main";

        vk::PipelineShaderStageCreateInfo fragStage{};
        fragStage.stage = vk::ShaderStageFlagBits::eFragment;
        fragStage.module = fragModule;
        fragStage.pName = "main";

        vk::PipelineShaderStageCreateInfo stages[] = { vertStage, fragStage };

        vk::PipelineVertexInputStateCreateInfo vertexInput{};
        vk::PipelineInputAssemblyStateCreateInfo inputAssembly{};
        inputAssembly.topology = vk::PrimitiveTopology::eTriangleList;

        vk::Viewport viewport{ 0, 0,
            F32(this->m_swapChainExtent.width),
            F32(this->m_swapChainExtent.height),
            0.0f, 1.0f };

        vk::Rect2D scissor{ {0, 0}, this->m_swapChainExtent };

        vk::PipelineViewportStateCreateInfo viewportState{};
        viewportState.viewportCount = 1;
        viewportState.pViewports = &viewport;
        viewportState.scissorCount = 1;
        viewportState.pScissors = &scissor;

        vk::PipelineRasterizationStateCreateInfo rasterizer{};
        rasterizer.polygonMode = vk::PolygonMode::eFill;
        rasterizer.lineWidth = 1.0f;
        rasterizer.cullMode = vk::CullModeFlagBits::eBack;
        rasterizer.frontFace = vk::FrontFace::eClockwise;

        vk::PipelineMultisampleStateCreateInfo multisampling{};
        multisampling.rasterizationSamples = vk::SampleCountFlagBits::e1;

        vk::PipelineColorBlendAttachmentState colorBlendAttachment{};
        colorBlendAttachment.colorWriteMask =
            vk::ColorComponentFlagBits::eR |
            vk::ColorComponentFlagBits::eG |
            vk::ColorComponentFlagBits::eB |
            vk::ColorComponentFlagBits::eA;

        vk::PipelineColorBlendStateCreateInfo colorBlending{};
        colorBlending.attachmentCount = 1;
        colorBlending.pAttachments = &colorBlendAttachment;

        vk::PipelineLayoutCreateInfo layoutInfo{};
        this->m_pipelineLayout = this->m_device.createPipelineLayout(layoutInfo);

        if (!this->m_pipelineLayout) return false;

        vk::GraphicsPipelineCreateInfo pipelineInfo{};
        pipelineInfo.stageCount = 2;
        pipelineInfo.pStages = stages;
        pipelineInfo.pVertexInputState = &vertexInput;
        pipelineInfo.pInputAssemblyState = &inputAssembly;
        pipelineInfo.pViewportState = &viewportState;
        pipelineInfo.pRasterizationState = &rasterizer;
        pipelineInfo.pMultisampleState = &multisampling;
        pipelineInfo.pColorBlendState = &colorBlending;
        pipelineInfo.layout = this->m_pipelineLayout;
        pipelineInfo.renderPass = this->m_renderPass;
        pipelineInfo.subpass = 0;

        this->m_graphicsPipeline = this->m_device.createGraphicsPipeline(nullptr, pipelineInfo).value;

        if (!this->m_graphicsPipeline) return false;

        //TODO: RAII
        this->m_device.destroyShaderModule(vertModule);
        this->m_device.destroyShaderModule(fragModule);
        return true;
    }

    bool Vulkan::createFramebuffers() noexcept
    {
        this->m_framebuffers.resize(this->m_swapchainImageViews.size());

        for (std::size_t i = 0; i < this->m_swapchainImageViews.size(); ++i)
        {
            const vk::ImageView attachments[] = { this->m_swapchainImageViews.at(i) };

            vk::FramebufferCreateInfo info{};
            info.renderPass = this->m_renderPass;
            info.attachmentCount = 1;
            info.pAttachments = attachments;
            info.width = this->m_swapChainExtent.width;
            info.height = this->m_swapChainExtent.height;
            info.layers = 1;

            this->m_framebuffers.at(i) = this->m_device.createFramebuffer(info);
            if (!this->m_framebuffers.at(i)) return false;
        }
        return true;
    }

    bool Vulkan::createCommandPool() noexcept
    {
        vk::CommandPoolCreateInfo poolInfo{};
        poolInfo.flags = vk::CommandPoolCreateFlagBits::eResetCommandBuffer;
        poolInfo.queueFamilyIndex = this->m_graphicsFamily.value();

        this->m_commandPool = this->m_device.createCommandPool(poolInfo);
        if (!this->m_commandPool) return false;
        return true;
    }

    bool Vulkan::createCommandBuffers() noexcept
    {
        this->m_commandBuffers.resize(this->m_framebuffers.size());

        vk::CommandBufferAllocateInfo allocInfo{};
        allocInfo.commandPool = this->m_commandPool;
        allocInfo.level = vk::CommandBufferLevel::ePrimary;
        allocInfo.commandBufferCount = U32(this->m_commandBuffers.size());

        this->m_commandBuffers = this->m_device.allocateCommandBuffers(allocInfo);
        if (!this->m_commandBuffers.at(0)) return false;
        return true;
    }

    bool Vulkan::createSyncObjects() noexcept
    {
        const std::size_t MAX_FRAMES_IN_FLIGHT = this->m_swapChainImages.size();
        this->m_imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
        this->m_renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
        this->m_inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);

        //vk::SemaphoreCreateInfo semInfo{};
        vk::FenceCreateInfo fenceInfo{};
        fenceInfo.flags = vk::FenceCreateFlagBits::eSignaled;
        for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; ++i)
        {
            this->m_imageAvailableSemaphores.at(i) = this->m_device.createSemaphore({});
            if (!this->m_imageAvailableSemaphores.at(i)) return false;

            this->m_renderFinishedSemaphores.at(i) = this->m_device.createSemaphore({});
            if (!this->m_renderFinishedSemaphores.at(i)) return false;

            this->m_inFlightFences.at(i) = this->m_device.createFence(fenceInfo);
            if (!this->m_inFlightFences.at(i)) return false;
        }
        return true;
    }

    bool Vulkan::checkLayerSupport(const std::span<const char* const>& layers) noexcept
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

    Vulkan::SwapChainSupportDetails Vulkan::querySwapChainSupport(const vk::PhysicalDevice& device, const vk::SurfaceKHR& surface) noexcept
    {
        SwapChainSupportDetails details;
        details.capabilities = device.getSurfaceCapabilitiesKHR(surface);
        details.formats = device.getSurfaceFormatsKHR(surface);
        details.presentModes = device.getSurfacePresentModesKHR(surface);
        return details;
    }

    vk::SurfaceFormatKHR Vulkan::chooseSurfaceFormat(const std::vector<vk::SurfaceFormatKHR>& formats) noexcept
    {
        if (formats.size() == 1 && formats.at(0).format == vk::Format::eUndefined)
            return { vk::Format::eB8G8R8A8Srgb, vk::ColorSpaceKHR::eSrgbNonlinear };

        const auto preferred = std::ranges::find_if(formats,
                [](const vk::SurfaceFormatKHR& format)
                {
                    return format.format == vk::Format::eB8G8R8A8Srgb &&
                           format.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear;
                });
        return preferred != formats.end() ? *preferred : formats.front();
    }

    vk::PresentModeKHR Vulkan::choosePresentMode(const std::vector<vk::PresentModeKHR>& presentModes) noexcept
    {
        const auto it = std::ranges::find(presentModes, vk::PresentModeKHR::eMailbox);
        return it != presentModes.end() ? *it : vk::PresentModeKHR::eFifo;
    }

    vk::Extent2D Vulkan::chooseExtent(const vk::SurfaceCapabilitiesKHR& capabilities, GLFWwindow* window) noexcept
    {
        if (capabilities.currentExtent.width != std::numeric_limits<std::uint32_t>::max()) return capabilities.currentExtent;

        int width, height;
        glfwGetFramebufferSize(window, &width, &height);

        while (width == 0 || height == 0)
        {
            glfwGetFramebufferSize(window, &width, &height);
            glfwWaitEvents();
        }

        vk::Extent2D actualExtent{ U32(width), U32(height) };
        actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
        actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);
        return actualExtent;
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