module;

#include <string_view>
#include <cstdint>

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

export module Core:Joystick;

import NonConstructible;

export namespace ikk
{
    class Joystick final : public NonConstructible
    {
    public:
        using ID = std::uint32_t;

        enum struct [[nodiscard]] Button : std::uint8_t
        {
            Unknown = 0,
            A,
            B,
            X,
            Y,
            LBumper,
            RBumper,
            Back,
            Start,
            Guide,
            LThump,
            RThump,
            Up,
            Down,
            Right,
            Left
        };

        enum struct [[nodiscard]] Axis : std::uint8_t
        {
            Unknown = 0,
            LX,
            LY,
            RX,
            RY,
            LTrigger,
            RTrigger
        };

        enum struct [[nodiscard]] Hat : std::uint8_t
        {
            Unknown     = 0 << 0,
            Center      = 1 << 0,
            Up          = 1 << 1,
            Right       = 1 << 2,
            Down        = 1 << 3,
            Left        = 1 << 4,
            UpRight     = Up | Right,
            UpLeft      = Up | Left,
            DownRight   = Down | Right,
            DownLeft    = Down | Left
        };

        using enum Button;

        [[nodiscard]] static constexpr std::string_view toString(Button button) noexcept;
        [[nodiscard]] static constexpr std::string_view toString(Axis axis) noexcept;
        [[nodiscard]] static constexpr std::string_view toString(Hat hat) noexcept;
    private:
        [[nodiscard]] static constexpr Button fromGLFWButton(std::int32_t button) noexcept;
        [[nodiscard]] static constexpr Axis fromGLFWAxis(std::int32_t axis) noexcept;
        [[nodiscard]] static constexpr Hat fromGLFWHat(std::int32_t hat) noexcept;

        [[nodiscard]] static constexpr std::int32_t toGLFWButton(Button button) noexcept;
        [[nodiscard]] static constexpr std::int32_t toGLFWAxis(Axis axis) noexcept;
        [[nodiscard]] static constexpr std::int32_t toGLFWHat(Hat hat) noexcept;

        friend class PhysicalJoystick;
    };
}

namespace ikk
{
    constexpr std::string_view Joystick::toString(Button button) noexcept
    {
        switch (button)
        {
        case Button::Unknown:   return "Unknown";
        case Button::A:         return "A";
        case Button::B:         return "B";
        case Button::X:         return "X";
        case Button::Y:         return "Y";
        case Button::LBumper:   return "Left Bumper";
        case Button::RBumper:   return "Right Bumper";
        case Button::Back:      return "Back";
        case Button::Start:     return "Start";
        case Button::Guide:     return "Guide";
        case Button::LThump:    return "Left Thump";
        case Button::RThump:    return "Right Thump";
        case Button::Up:        return "DPAD Up";
        case Button::Down:      return "DPAD Down";
        case Button::Right:     return "DPAD Right";
        case Button::Left:      return "DPAD Left";
        }
        return "Unknown";
    }

    constexpr std::string_view Joystick::toString(Axis axis) noexcept
    {
        switch (axis)
        {
        case Axis::Unknown:     return "Unknown";
        case Axis::LX:          return "Left X";
        case Axis::LY:          return "Left Y";
        case Axis::RX:          return "Right X";
        case Axis::RY:          return "Right Y";
        case Axis::LTrigger:    return "Left Trigger";
        case Axis::RTrigger:    return "Right Trigger";
        }
        return "Unknown";
    }

    constexpr std::string_view Joystick::toString(Hat hat) noexcept
    {
        switch (hat)
        {
        case Hat::Unknown:      return "Unknown";
        case Hat::Center:       return "Centered";
        case Hat::Up:           return "Up";
        case Hat::Right:        return "Right";
        case Hat::Down:         return "Down";
        case Hat::Left:         return "Left";
        case Hat::UpRight:      return "Up & Right";
        case Hat::UpLeft:       return "Up & Left";
        case Hat::DownRight:    return "Down & Right";
        case Hat::DownLeft:     return "Down & Left";
        default:                return "Unknown";
        }
    }

    constexpr Joystick::Button Joystick::fromGLFWButton(std::int32_t button) noexcept
    {
        switch (button)
        {
        case GLFW_GAMEPAD_BUTTON_A:             return Button::A;
        case GLFW_GAMEPAD_BUTTON_B:             return Button::B;
        case GLFW_GAMEPAD_BUTTON_X:             return Button::X;
        case GLFW_GAMEPAD_BUTTON_Y:             return Button::Y;
        case GLFW_GAMEPAD_BUTTON_LEFT_BUMPER:   return Button::LBumper;
        case GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER:  return Button::RBumper;
        case GLFW_GAMEPAD_BUTTON_BACK:          return Button::Back;
        case GLFW_GAMEPAD_BUTTON_START:         return Button::Start;
        case GLFW_GAMEPAD_BUTTON_GUIDE:         return Button::Guide;
        case GLFW_GAMEPAD_BUTTON_LEFT_THUMB:    return Button::LThump;
        case GLFW_GAMEPAD_BUTTON_RIGHT_THUMB:   return Button::RThump;
        case GLFW_GAMEPAD_BUTTON_DPAD_UP:       return Button::Up;
        case GLFW_GAMEPAD_BUTTON_DPAD_DOWN:     return Button::Down;
        case GLFW_GAMEPAD_BUTTON_DPAD_RIGHT:    return Button::Right;
        case GLFW_GAMEPAD_BUTTON_DPAD_LEFT:     return Button::Left;
        default:                                return Button::Unknown;
        }
    }

    constexpr Joystick::Axis Joystick::fromGLFWAxis(std::int32_t axis) noexcept
    {
        switch (axis)
        {
        case GLFW_GAMEPAD_AXIS_LEFT_X:          return Axis::LX;
        case GLFW_GAMEPAD_AXIS_LEFT_Y:          return Axis::LY;
        case GLFW_GAMEPAD_AXIS_RIGHT_X:         return Axis::RX;
        case GLFW_GAMEPAD_AXIS_RIGHT_Y:         return Axis::RY;
        case GLFW_GAMEPAD_AXIS_LEFT_TRIGGER:    return Axis::LTrigger;
        case GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER:   return Axis::RTrigger;
        default:                                return Axis::Unknown;
        }
    }

    constexpr Joystick::Hat Joystick::fromGLFWHat(std::int32_t hat) noexcept
    {
        switch (hat)
        {
        case GLFW_HAT_CENTERED:     return Hat::Center;
        case GLFW_HAT_UP:           return Hat::Up;
        case GLFW_HAT_RIGHT:        return Hat::Right;
        case GLFW_HAT_DOWN:         return Hat::Down;
        case GLFW_HAT_LEFT:         return Hat::Left;
        case GLFW_HAT_RIGHT_UP:     return Hat::UpRight;
        case GLFW_HAT_LEFT_UP:      return Hat::UpLeft;
        case GLFW_HAT_RIGHT_DOWN:   return Hat::DownRight;
        case GLFW_HAT_LEFT_DOWN:    return Hat::DownLeft;
        default:                    return Hat::Unknown;
        }
    }

    constexpr std::int32_t Joystick::toGLFWButton(Button button) noexcept
    {
        switch (button)
        {
        case Button::Unknown:   return GLFW_KEY_UNKNOWN;
        case Button::A:         return GLFW_GAMEPAD_BUTTON_A;
        case Button::B:         return GLFW_GAMEPAD_BUTTON_B;
        case Button::X:         return GLFW_GAMEPAD_BUTTON_X;
        case Button::Y:         return GLFW_GAMEPAD_BUTTON_Y;
        case Button::LBumper:   return GLFW_GAMEPAD_BUTTON_LEFT_BUMPER;
        case Button::RBumper:   return GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER;
        case Button::Back:      return GLFW_GAMEPAD_BUTTON_BACK;
        case Button::Start:     return GLFW_GAMEPAD_BUTTON_START;
        case Button::Guide:     return GLFW_GAMEPAD_BUTTON_GUIDE;
        case Button::LThump:    return GLFW_GAMEPAD_BUTTON_LEFT_THUMB;
        case Button::RThump:    return GLFW_GAMEPAD_BUTTON_RIGHT_THUMB;
        case Button::Up:        return GLFW_GAMEPAD_BUTTON_DPAD_UP;
        case Button::Down:      return GLFW_GAMEPAD_BUTTON_DPAD_DOWN;
        case Button::Right:     return GLFW_GAMEPAD_BUTTON_DPAD_RIGHT;
        case Button::Left:      return GLFW_GAMEPAD_BUTTON_DPAD_LEFT;
        }
        return GLFW_KEY_UNKNOWN;
    }

    constexpr std::int32_t Joystick::toGLFWAxis(Axis axis) noexcept
    {
        switch (axis)
        {
        case Axis::Unknown:     return GLFW_KEY_UNKNOWN;
        case Axis::LX:          return GLFW_GAMEPAD_AXIS_LEFT_X;
        case Axis::LY:          return GLFW_GAMEPAD_AXIS_LEFT_Y;
        case Axis::RX:          return GLFW_GAMEPAD_AXIS_RIGHT_X;
        case Axis::RY:          return GLFW_GAMEPAD_AXIS_RIGHT_Y;
        case Axis::LTrigger:    return GLFW_GAMEPAD_AXIS_LEFT_TRIGGER;
        case Axis::RTrigger:    return GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER;
        }
        return GLFW_KEY_UNKNOWN;
    }

    constexpr std::int32_t Joystick::toGLFWHat(Hat hat) noexcept
    {
        switch (hat)
        {
        case Hat::Unknown:      return GLFW_KEY_UNKNOWN;
        case Hat::Center:       return GLFW_HAT_CENTERED;
        case Hat::Up:           return GLFW_HAT_UP;
        case Hat::Right:        return GLFW_HAT_RIGHT;
        case Hat::Down:         return GLFW_HAT_DOWN;
        case Hat::Left:         return GLFW_HAT_LEFT;
        case Hat::UpRight:      return GLFW_HAT_RIGHT_UP;
        case Hat::UpLeft:       return GLFW_HAT_LEFT_UP;
        case Hat::DownRight:    return GLFW_HAT_RIGHT_DOWN;
        case Hat::DownLeft:     return GLFW_HAT_LEFT_DOWN;
        default:                return GLFW_KEY_UNKNOWN;
        }
    }
}