module;

#include <string_view>
#include <utility>
#include <cstdint>

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

export module Core:Window;

import :EventCallbackFuncs;
import :Renderer;
import :Vulkan;

import Utility;

export namespace ikk
{
    class [[nodiscard]] Window final
    {
    public:
        [[nodiscard]] Window(std::u8string_view title, std::uint32_t width, std::uint32_t height) noexcept;

        Window(const Window& other) noexcept;
        Window(Window&& other) noexcept;

        Window& operator=(const Window& other) noexcept;
        Window& operator=(Window&& other) noexcept;

        ~Window() noexcept;

        [[nodiscard]] bool shouldClose() const noexcept;

        void pollEvents() const noexcept;
        void render(const Color& clearColor) const noexcept;

        [[nodiscard]] const Renderer& getRenderer() const noexcept;
    private:
        GLFWwindow* m_window = nullptr;
        Renderer m_renderer{};

        void setupWindow() noexcept;
    };
}

namespace ikk
{
    Window::Window(std::u8string_view title, std::uint32_t width, std::uint32_t height) noexcept
    {
        if (glfwInit() == GLFW_FALSE)
            return;

        //TODO:
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        this->m_window = glfwCreateWindow(I32(width), I32(height), reinterpret_cast<const char*>(title.data()), nullptr, nullptr);
        this->m_renderer.create<Vulkan>(this->m_window);
        this->setupWindow();
    }

    Window::Window(const Window& other) noexcept
    {
        if (this != &other)
        {
            const char* title = glfwGetWindowTitle(other.m_window);
            int width, height;
            glfwGetWindowSize(other.m_window, &width, &height);
            this->m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
            this->m_renderer.create<Vulkan>(this->m_window);
            this->setupWindow();
        }
    }

    Window::Window(Window&& other) noexcept
        : m_window(std::exchange(other.m_window, nullptr)), m_renderer(std::move(other.m_renderer))
    {
    }

    Window& Window::operator=(const Window& other) noexcept
    {
        if (this != &other)
        {
            if (this->m_window != nullptr)
                glfwDestroyWindow(this->m_window);

            const char* title = glfwGetWindowTitle(other.m_window);
            int width, height;
            glfwGetWindowSize(other.m_window, &width, &height);
            this->m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
            this->m_renderer.create<Vulkan>(this->m_window);
            this->setupWindow();
        }
        return *this;
    }

    Window& Window::operator=(Window&& other) noexcept
    {
        if (this != &other)
        {
            if (this->m_window != nullptr)
                glfwDestroyWindow(this->m_window);

            this->m_window = std::exchange(other.m_window, nullptr);
            this->m_renderer = std::move(other.m_renderer);
        }
        return *this;
    }

    Window::~Window() noexcept
    {
        if (this->m_window != nullptr)
            glfwDestroyWindow(this->m_window);
        glfwTerminate();
    }

    bool Window::shouldClose() const noexcept
    {
        if (this->m_window == nullptr) return true;
        return BOOL(glfwWindowShouldClose(this->m_window));
    }

    void Window::pollEvents() const noexcept
    {
        if (this->m_window != nullptr) glfwPollEvents();
    }

    void Window::render(const Color& clearColor) const noexcept
    {
        this->m_renderer.beginRender(clearColor);
        //TODO: Draw stuff here...
        this->m_renderer.endRender();
    }

    const Renderer& Window::getRenderer() const noexcept
    {
        return this->m_renderer;
    }

    void Window::setupWindow() noexcept
    {
        if (this->m_window == nullptr) return;

        if (glfwRawMouseMotionSupported() == GLFW_TRUE)
            glfwSetInputMode(this->m_window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

        glfwSetWindowUserPointer(this->m_window, this);

        if constexpr (isDebug()) glfwSetErrorCallback(EventCallbackFuncs::errorCallback);
        glfwSetWindowCloseCallback(this->m_window, EventCallbackFuncs::windowClosedCallback);
        glfwSetWindowSizeCallback(this->m_window, EventCallbackFuncs::windowResizeCallback);
        glfwSetFramebufferSizeCallback(this->m_window, EventCallbackFuncs::framebufferResizeCallback);
        glfwSetWindowPosCallback(this->m_window, EventCallbackFuncs::windowPositionCallback);
        glfwSetWindowIconifyCallback(this->m_window, EventCallbackFuncs::windowIconifyCallback);
        glfwSetWindowMaximizeCallback(this->m_window, EventCallbackFuncs::windowMaximizeCallback);
        glfwSetWindowFocusCallback(this->m_window, EventCallbackFuncs::windowFocusCallback);
        glfwSetCursorEnterCallback(this->m_window, EventCallbackFuncs::cursorEnterCallback);
        glfwSetCharCallback(this->m_window, EventCallbackFuncs::characterCallback);
        glfwSetKeyCallback(this->m_window, EventCallbackFuncs::keyInputCallback);
        glfwSetMouseButtonCallback(this->m_window, EventCallbackFuncs::mouseButtonCallback);
        glfwSetScrollCallback(this->m_window, EventCallbackFuncs::mouseScrollCallback);
        glfwSetCursorPosCallback(this->m_window, EventCallbackFuncs::cursorPositionCallback);
        glfwSetWindowRefreshCallback(this->m_window, EventCallbackFuncs::windowRefreshCallback);
        glfwSetWindowContentScaleCallback(this->m_window, EventCallbackFuncs::windowContentScaleCallback);
        glfwSetDropCallback(this->m_window, EventCallbackFuncs::dropCallback);
        glfwSetMonitorCallback(EventCallbackFuncs::monitorCallback);
        glfwSetJoystickCallback(EventCallbackFuncs::joystickCallback);
    }
}