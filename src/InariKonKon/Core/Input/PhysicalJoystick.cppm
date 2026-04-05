module;

#include <string_view>
#include <cstdint>

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

export module Core:PhysicalJoystick;

import :Joystick;
import :Input;

import NumericCasts;

export namespace ikk
{
    class [[nodiscard]] PhysicalJoystick final
    {
    public:
        explicit PhysicalJoystick(Joystick::ID id, float threshold = 0.1f) noexcept;

        PhysicalJoystick(const PhysicalJoystick&) noexcept = default;
        PhysicalJoystick(PhysicalJoystick&&) noexcept = default;

        PhysicalJoystick& operator=(const PhysicalJoystick&) noexcept = default;
        PhysicalJoystick& operator=(PhysicalJoystick&&) noexcept = default;

        ~PhysicalJoystick() noexcept = default;

        [[nodiscard]] bool operator==(const PhysicalJoystick& other) const noexcept;
        [[nodiscard]] bool operator!=(const PhysicalJoystick& other) const noexcept;

        [[nodiscard]] const Joystick::ID& getID() const noexcept;

        [[nodiscard]] static bool isConnected(Joystick::ID id) noexcept;

        [[nodiscard]] Input::Action getJoystickButtonState(Joystick::Button button) const noexcept;
        [[nodiscard]] float getJoystickAxisValue(Joystick::Axis axis) const noexcept;
        [[nodiscard]] bool getJoystickHatState(std::uint32_t id, Joystick::Hat hat) const noexcept;
    private:
        Joystick::ID m_id = 0;

        std::string_view m_name = {};

        std::int32_t m_joystickAxesCount = 0;
        std::int32_t m_joystickButtonCount = 0;
        std::int32_t m_joystickHatCount = 0;

        float m_threshold = 0.1f;

        bool m_isGamepadInputAvailable = false;

        const std::uint8_t* m_buttons = nullptr;
        const float* m_axes = nullptr;
        const std::uint8_t* m_hats = nullptr;
    };
}

namespace ikk
{
    PhysicalJoystick::PhysicalJoystick(Joystick::ID id, float threshold) noexcept
        : m_id(id), m_name(glfwGetJoystickName(I32(id))), m_threshold(threshold),
          m_isGamepadInputAvailable(glfwJoystickIsGamepad(I32(id)))
    {
        this->m_buttons = glfwGetJoystickButtons(I32(this->m_id), &this->m_joystickButtonCount);
        this->m_axes = glfwGetJoystickAxes(I32(this->m_id), &this->m_joystickAxesCount);
        this->m_hats = glfwGetJoystickHats(I32(this->m_id), &this->m_joystickHatCount);

        if (this->m_isGamepadInputAvailable)
            this->m_name = glfwGetGamepadName(I32(this->m_id));

        glfwSetJoystickUserPointer(I32(this->m_id), this);
    }

    bool PhysicalJoystick::operator==(const PhysicalJoystick& other) const noexcept
    {
        return this->m_id == other.m_id;
    }

    bool PhysicalJoystick::operator!=(const PhysicalJoystick& other) const noexcept
    {
        return this->m_id != other.m_id;
    }

    const Joystick::ID& PhysicalJoystick::getID() const noexcept
    {
        return this->m_id;
    }

    bool PhysicalJoystick::isConnected(Joystick::ID id) noexcept
    {
        return glfwJoystickPresent(I32(id)) == GLFW_TRUE;
    }

    Input::Action PhysicalJoystick::getJoystickButtonState(Joystick::Button button) const noexcept
    {
        const std::int32_t index = Joystick::toGLFWButton(button);

        if (this->m_isGamepadInputAvailable)
            if (GLFWgamepadstate state{}; glfwGetGamepadState(I32(this->m_id), &state) != GLFW_FALSE)
                return state.buttons[index] == GLFW_PRESS ? Input::Action::Press : Input::Action::Release;

        if (this->m_joystickButtonCount < index)
            return Input::Action::Unknown;

        return this->m_buttons[index] == GLFW_PRESS ? Input::Action::Press : Input::Action::Release;
    }

    float PhysicalJoystick::getJoystickAxisValue(Joystick::Axis axis) const noexcept
    {
        const std::int32_t index = Joystick::toGLFWAxis(axis);

        if (this->m_isGamepadInputAvailable)
            if (GLFWgamepadstate state{}; glfwGetGamepadState(I32(this->m_id), &state) != GLFW_FALSE)
                return state.axes[index];

        if (this->m_joystickAxesCount < index)
            return 0.f;

        return this->m_axes[index];
    }

    bool PhysicalJoystick::getJoystickHatState(std::uint32_t id, Joystick::Hat hat) const noexcept
    {
        const std::int32_t index = Joystick::toGLFWHat(hat);

        if (this->m_joystickHatCount < index)
            return false;

        return this->m_hats[id] & index;
    }
}