module;

#include <filesystem>
#include <vector>

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

export module Core:EventCallbackFuncs;

import :EventManager;
import :Event;

import NonConstructible;
import InputManager;
import Conversion;
import Utility;
import Input;
import Vec;

export namespace ikk
{
    class Monitor;
    class Window;

    class EventCallbackFuncs final : public NonConstructible
    {
        static void errorCallback(int code, const char* description) noexcept;

        static void windowClosedCallback(GLFWwindow* window) noexcept;

        static void windowResizeCallback(GLFWwindow* window, int width, int height) noexcept;

        static void framebufferResizeCallback(GLFWwindow* window, int width, int height) noexcept;

        static void windowContentScaleCallback(GLFWwindow* window, float xscale, float yscale) noexcept;

        static void windowPositionCallback(GLFWwindow* window, int xpos, int ypos) noexcept;

        static void windowIconifyCallback(GLFWwindow* window, int iconified) noexcept;

        static void windowMaximizeCallback(GLFWwindow* window, int maximized) noexcept;

        static void windowFocusCallback(GLFWwindow* window, int focused) noexcept;

        static void windowRefreshCallback(GLFWwindow* window) noexcept;

        static void monitorCallback(GLFWmonitor* monitor, int event) noexcept;

        static void cursorEnterCallback(GLFWwindow* window, int entered) noexcept;

        static void characterCallback(GLFWwindow* window, unsigned int codepoint) noexcept;

        static void keyInputCallback(GLFWwindow* window, int key, int scancode, int action, int mods) noexcept;

        static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) noexcept;

        static void mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset) noexcept;

        static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos) noexcept;

        static void joystickCallback(int jid, int event) noexcept;

        static void dropCallback(GLFWwindow* window, int count, const char** paths) noexcept;

        friend class Window;
    };
}

namespace ikk
{
    void EventCallbackFuncs::errorCallback(int code, const char* description) noexcept
    {
    }

    void EventCallbackFuncs::windowClosedCallback(GLFWwindow* window) noexcept
    {
        auto* ptr = static_cast<Window*>(glfwGetWindowUserPointer(window));
        EventManager::getInstance().emplace(WindowEvent::Closed{ .window = ptr });
    }

    void EventCallbackFuncs::windowResizeCallback(GLFWwindow* window, int width, int height) noexcept
    {
        auto* ptr = static_cast<Window*>(glfwGetWindowUserPointer(window));
        EventManager::getInstance().emplace(WindowEvent::Resized{ .window = ptr, .width = U32(width), .height = U32(height) });
    }

    void EventCallbackFuncs::framebufferResizeCallback(GLFWwindow* window, int width, int height) noexcept
    {
        auto* ptr = static_cast<Window*>(glfwGetWindowUserPointer(window));
        EventManager::getInstance().emplace(WindowEvent::FramebufferResized{ .window = ptr, .width = U32(width), .height = U32(height) });
    }

    void EventCallbackFuncs::windowContentScaleCallback(GLFWwindow* window, float xscale, float yscale) noexcept
    {
        auto* ptr = static_cast<Window*>(glfwGetWindowUserPointer(window));
        EventManager::getInstance().emplace(WindowEvent::ContentScale{ .window = ptr, .scale = Vec2f{ xscale, yscale } });
    }

    void EventCallbackFuncs::windowPositionCallback(GLFWwindow* window, int xpos, int ypos) noexcept
    {
        auto* ptr = static_cast<Window*>(glfwGetWindowUserPointer(window));
        EventManager::getInstance().emplace(WindowEvent::Position{ .window = ptr, .position = Vec2i{ xpos, ypos } });
    }

    void EventCallbackFuncs::windowIconifyCallback(GLFWwindow* window, int iconified) noexcept
    {
        auto* ptr = static_cast<Window*>(glfwGetWindowUserPointer(window));
        if (iconified == GLFW_TRUE)
            EventManager::getInstance().emplace(WindowEvent::Iconified{ .window = ptr });
        else if (iconified == GLFW_FALSE)
            EventManager::getInstance().emplace(WindowEvent::UnIconified{ .window = ptr });
    }

    void EventCallbackFuncs::windowMaximizeCallback(GLFWwindow* window, int maximized) noexcept
    {
        auto* ptr = static_cast<Window*>(glfwGetWindowUserPointer(window));
        if (maximized == GLFW_TRUE)
            EventManager::getInstance().emplace(WindowEvent::Maximized{ .window = ptr });
        else if (maximized == GLFW_FALSE)
            EventManager::getInstance().emplace(WindowEvent::Minimized{ .window = ptr });
    }

    void EventCallbackFuncs::windowFocusCallback(GLFWwindow* window, int focused) noexcept
    {
        auto* ptr = static_cast<Window*>(glfwGetWindowUserPointer(window));
        if (focused == GLFW_TRUE)
            EventManager::getInstance().emplace(WindowEvent::FocusGained{ .window = ptr });
        else if (focused == GLFW_FALSE)
            EventManager::getInstance().emplace(WindowEvent::FocusLost{ .window = ptr });
    }

    void EventCallbackFuncs::windowRefreshCallback(GLFWwindow* window) noexcept
    {
        auto* ptr = static_cast<Window*>(glfwGetWindowUserPointer(window));
        EventManager::getInstance().emplace(WindowEvent::Refreshed{ .window = ptr });
    }

    void EventCallbackFuncs::monitorCallback(GLFWmonitor* monitor, int event) noexcept
    {
        if (event == GLFW_CONNECTED)
            EventManager::getInstance().emplace(Event::Monitor::Connected{ .monitor = reinterpret_cast<Monitor*>(monitor) });
        else if (event == GLFW_DISCONNECTED)
            EventManager::getInstance().emplace(Event::Monitor::Disconnected{ .monitor = reinterpret_cast<Monitor*>(monitor) });
    }

    void EventCallbackFuncs::cursorEnterCallback(GLFWwindow* window, int entered) noexcept
    {
        auto* ptr = static_cast<Window*>(glfwGetWindowUserPointer(window));
        if (entered == GLFW_TRUE)
            EventManager::getInstance().emplace(WindowEvent::CursorEntered{ .window = ptr });
        else if (entered == GLFW_FALSE)
            EventManager::getInstance().emplace(WindowEvent::CursorLeft{ .window = ptr });
    }

    void EventCallbackFuncs::characterCallback(GLFWwindow* window, unsigned int codepoint) noexcept
    {
        EventManager::getInstance().emplace(InputEvent::Text{ .unicode = static_cast<char32_t>(codepoint) });
    }

    void EventCallbackFuncs::keyInputCallback(GLFWwindow* window, int key, int scancode, int action, int mods) noexcept
    {
        //TODO: Fix later...
        if (auto& mapping = Keyboard::getScanCodeMapping(); mapping.contains(scancode) == false)
            mapping.emplace(scancode, Conversion::fromGLFWKeyCode(key));

        const Keyboard::KeyCode keycode = Conversion::fromGLFWKeyCode(key);
        const Input::State state = Conversion::fromGLFWAction(action);
        EventManager::getInstance().emplace(InputEvent::Keyboard{ .keycode = keycode, .scancode = scancode, .state = state });
    }

    void EventCallbackFuncs::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) noexcept
    {
        const Mouse::Button mButton = Conversion::fromGLFWButton(button);
        const Input::State state = Conversion::fromGLFWAction(action);
        EventManager::getInstance().emplace(InputEvent::Mouse::Button{ .button = mButton, .state = state });
    }

    void EventCallbackFuncs::mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset) noexcept
    {
        if (xoffset != 0)
            EventManager::getInstance().emplace(InputEvent::Mouse::Wheel{ .wheel = Mouse::Wheel::Horizontal, .delta = xoffset });

        if (yoffset != 0)
            EventManager::getInstance().emplace(InputEvent::Mouse::Wheel{ .wheel = Mouse::Wheel::Vertical, .delta = yoffset });
    }

    void EventCallbackFuncs::cursorPositionCallback(GLFWwindow* window, double xpos, double ypos) noexcept
    {
        EventManager::getInstance().emplace(InputEvent::Mouse::Move{ .position = { xpos, ypos } });
    }

    void EventCallbackFuncs::joystickCallback(int jid,  int event) noexcept
    {
        if (event == GLFW_CONNECTED)
        {
            EventManager::getInstance().emplace(InputEvent::Joystick::Connected{ .id = U32(jid) });
            InputManager::getInstance().addJoystick(jid);
        }
        else if (event == GLFW_DISCONNECTED)
        {
            EventManager::getInstance().emplace(InputEvent::Joystick::Disconnected{ .id = U32(jid) });
            InputManager::getInstance().removeJoystick(jid);
        }
    }

    void EventCallbackFuncs::dropCallback(GLFWwindow* window, int count, const char** paths) noexcept
    {
        std::vector<std::filesystem::path> files{};
        files.reserve(static_cast<std::size_t>(count));
        for (std::size_t i = 0; i < static_cast<std::size_t>(count); ++i)
            files.emplace_back(paths[i]);

        auto* ptr = static_cast<Window*>(glfwGetWindowUserPointer(window));
        EventManager::getInstance().emplace(WindowEvent::FileDropped{ .window = ptr, .paths = std::move(files) });
    }
}