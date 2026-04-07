module;

#include <filesystem>
#include <vector>

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

export module Core:EventCallbackFuncs;

import :InputManager;
import :EventManager;
import :GLFWMapper;
import :Event;
import :Input;

import NonConstructible;
import Log;
import Vec;

export namespace ikk
{
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
        Print<Log::Level::Error>("code: {}, description: {}", code, description);
    }

    void EventCallbackFuncs::windowClosedCallback(GLFWwindow* window) noexcept
    {
        auto* ptr = static_cast<Window*>(glfwGetWindowUserPointer(window));
        eventManager.emplace(WindowEvent::Closed{ .window = ptr });
    }

    void EventCallbackFuncs::windowResizeCallback(GLFWwindow* window, int width, int height) noexcept
    {
        auto* ptr = static_cast<Window*>(glfwGetWindowUserPointer(window));
        eventManager.emplace(WindowEvent::Resized{ .window = ptr, .width = U32(width), .height = U32(height) });
    }

    void EventCallbackFuncs::framebufferResizeCallback(GLFWwindow* window, int width, int height) noexcept
    {
        auto* ptr = static_cast<Window*>(glfwGetWindowUserPointer(window));
        eventManager.emplace(WindowEvent::FramebufferResized{
            .window = ptr, .width = U32(width), .height = U32(height)
        });
    }

    void EventCallbackFuncs::windowContentScaleCallback(GLFWwindow* window, float xscale, float yscale) noexcept
    {
        auto* ptr = static_cast<Window*>(glfwGetWindowUserPointer(window));
        eventManager.emplace(WindowEvent::ContentScale{ .window = ptr, .scale = Vec2f{ xscale, yscale } });
    }

    void EventCallbackFuncs::windowPositionCallback(GLFWwindow* window, int xpos, int ypos) noexcept
    {
        auto* ptr = static_cast<Window*>(glfwGetWindowUserPointer(window));
        eventManager.emplace(WindowEvent::Position{ .window = ptr, .position = Vec2i{ xpos, ypos } });
    }

    void EventCallbackFuncs::windowIconifyCallback(GLFWwindow* window, int iconified) noexcept
    {
        auto* ptr = static_cast<Window*>(glfwGetWindowUserPointer(window));
        if (iconified == GLFW_TRUE) eventManager.emplace(WindowEvent::Iconified{ .window = ptr });
        else if (iconified == GLFW_FALSE) eventManager.emplace(WindowEvent::UnIconified{ .window = ptr });
    }

    void EventCallbackFuncs::windowMaximizeCallback(GLFWwindow* window, int maximized) noexcept
    {
        auto* ptr = static_cast<Window*>(glfwGetWindowUserPointer(window));
        if (maximized == GLFW_TRUE) eventManager.emplace(WindowEvent::Maximized{ .window = ptr });
        else if (maximized == GLFW_FALSE) eventManager.emplace(WindowEvent::Minimized{ .window = ptr });
    }

    void EventCallbackFuncs::windowFocusCallback(GLFWwindow* window, int focused) noexcept
    {
        auto* ptr = static_cast<Window*>(glfwGetWindowUserPointer(window));
        if (focused == GLFW_TRUE) eventManager.emplace(WindowEvent::FocusGained{ .window = ptr });
        else if (focused == GLFW_FALSE) eventManager.emplace(WindowEvent::FocusLost{ .window = ptr });
    }

    void EventCallbackFuncs::windowRefreshCallback(GLFWwindow* window) noexcept
    {
        auto* ptr = static_cast<Window*>(glfwGetWindowUserPointer(window));
        eventManager.emplace(WindowEvent::Refreshed{ .window = ptr });
    }

    void EventCallbackFuncs::monitorCallback(GLFWmonitor* monitor, int event) noexcept
    {
        if (event == GLFW_CONNECTED) eventManager.emplace(Event::Monitor::Connected{
            .monitor = reinterpret_cast<Monitor*>(monitor)
        });
        else if (event == GLFW_DISCONNECTED) eventManager.emplace(Event::Monitor::Disconnected{
            .monitor = reinterpret_cast<Monitor*>(monitor)
        });
    }

    void EventCallbackFuncs::cursorEnterCallback(GLFWwindow* window, int entered) noexcept
    {
        auto* ptr = static_cast<Window*>(glfwGetWindowUserPointer(window));
        if (entered == GLFW_TRUE) eventManager.emplace(WindowEvent::CursorEntered{ .window = ptr });
        else if (entered == GLFW_FALSE) eventManager.emplace(WindowEvent::CursorLeft{ .window = ptr });
    }

    void EventCallbackFuncs::characterCallback([[maybe_unused]] GLFWwindow* window, unsigned int codepoint) noexcept
    {
        eventManager.emplace(InputEvent::Text{ .unicode = static_cast<char32_t>(codepoint) });
    }

    void EventCallbackFuncs::keyInputCallback([[maybe_unused]] GLFWwindow* window, int key, int scancode, int action, [[maybe_unused]] int mods) noexcept
    {
        //TODO: Fix later...
        if (auto& mapping = Keyboard::getScanCodeMapping(); mapping.contains(scancode) == false)
            mapping.emplace(scancode, GLFWMapper::fromGLFWKeyCode(key));

        const Keyboard::KeyCode keycode = GLFWMapper::fromGLFWKeyCode(key);
        const Input::Action state = GLFWMapper::fromGLFWAction(action);
        eventManager.emplace(InputEvent::Keyboard{ .keycode = keycode, .scancode = scancode, .state = state });
        Input.handleEvent(keycode, state);
    }

    void EventCallbackFuncs::mouseButtonCallback([[maybe_unused]] GLFWwindow* window, int button, int action, [[maybe_unused]] int mods) noexcept
    {
        const Mouse::Button mButton = GLFWMapper::fromGLFWButton(button);
        const Input::Action state = GLFWMapper::fromGLFWAction(action);
        eventManager.emplace(InputEvent::Mouse::Button{ .button = mButton, .state = state });
        Input.handleEvent(mButton, state);
    }

    void EventCallbackFuncs::mouseScrollCallback([[maybe_unused]] GLFWwindow* window, double xoffset, double yoffset) noexcept
    {
        if (xoffset != 0.0)
        {
            eventManager.emplace(InputEvent::Mouse::Wheel{ .wheel = Mouse::Wheel::Horizontal, .delta = xoffset });
            Input::getInstance().handleEvent(Mouse::Wheel::Horizontal, xoffset);
        }

        if (yoffset != 0.0)
        {
            eventManager.emplace(InputEvent::Mouse::Wheel{ .wheel = Mouse::Wheel::Vertical, .delta = yoffset });
            Input::getInstance().handleEvent(Mouse::Wheel::Vertical, yoffset);
        }
    }

    void EventCallbackFuncs::cursorPositionCallback([[maybe_unused]] GLFWwindow* window, double xpos, double ypos) noexcept
    {
        eventManager.emplace(InputEvent::Mouse::Move{ .position = { xpos, ypos } });
    }

    void EventCallbackFuncs::joystickCallback(int jid, int event) noexcept
    {
        if (event == GLFW_CONNECTED)
        {
            eventManager.emplace(InputEvent::Joystick::Connected{ .id = U32(jid) });
            inputManager.addJoystick(U32(jid));
        }
        else if (event == GLFW_DISCONNECTED)
        {
            eventManager.emplace(InputEvent::Joystick::Disconnected{ .id = U32(jid) });
            inputManager.removeJoystick(U32(jid));
        }
    }

    void EventCallbackFuncs::dropCallback(GLFWwindow* window, int count, const char** paths) noexcept
    {
        std::vector<std::filesystem::path> files{};
        files.reserve(static_cast<std::size_t>(count));
        for (std::size_t i = 0; i < static_cast<std::size_t>(count); ++i) files.emplace_back(paths[i]);

        auto* ptr = static_cast<Window*>(glfwGetWindowUserPointer(window));
        eventManager.emplace(WindowEvent::FileDropped{ .window = ptr, .paths = std::move(files) });
    }
}