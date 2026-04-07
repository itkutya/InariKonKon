module;

#include <string_view>
#include <cstdint>

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

export module Core:Mouse;

import :Input;

import NonConstructible;

export namespace ikk
{
    class Mouse final : public NonConstructible
    {
    public:
        enum struct [[nodiscard]] Button : std::uint8_t
        {
            Unknown = 0,
            Left,
            Right,
            Middle,
            Extra1,
            Extra2,
            Extra3,
            Extra4,
            Extra5
        };

        enum struct [[nodiscard]] Wheel : std::uint8_t
        {
            Unknown = 0,
            Horizontal,
            Vertical
        };

        using enum Button;

        [[nodiscard]] static constexpr std::string_view toString(Button button) noexcept;
        [[nodiscard]] static constexpr std::string_view toString(Wheel wheel) noexcept;
    private:
        [[nodiscard]] static constexpr std::int32_t toGLFWButton(Mouse::Button button) noexcept;
        [[nodiscard]] static constexpr Mouse::Button fromGLFWButton(std::int32_t button) noexcept;

        friend class EventCallbackFuncs;
    };
}

namespace ikk
{
    template<>
    struct isInputType<Mouse::Button> : std::true_type {};

    template<>
    struct isInputType<Mouse::Wheel> : std::true_type {};

    constexpr std::string_view Mouse::toString(Button button) noexcept
    {
        switch (button)
        {
            case Button::Unknown:   return "Unknown";
            case Button::Left:      return "Left";
            case Button::Right:     return "Right";
            case Button::Middle:    return "Middle";
            case Button::Extra1:    return "Extra 1";
            case Button::Extra2:    return "Extra 2";
            case Button::Extra3:    return "Extra 3";
            case Button::Extra4:    return "Extra 4";
            case Button::Extra5:    return "Extra 5";
        }
        return "Unknown";
    }

    constexpr std::string_view Mouse::toString(Wheel wheel) noexcept
    {
        switch (wheel)
        {
            case Wheel::Unknown:    return "Unknown";
            case Wheel::Vertical:   return "Vertical";
            case Wheel::Horizontal: return "Horizontal";
        }
        return "Unknown";
    }

    constexpr std::int32_t Mouse::toGLFWButton(Mouse::Button button) noexcept
    {
        switch (button)
        {
        case Button::Unknown:   return GLFW_KEY_UNKNOWN;
        case Button::Left:      return GLFW_MOUSE_BUTTON_LEFT;
        case Button::Right:     return GLFW_MOUSE_BUTTON_RIGHT;
        case Button::Middle:    return GLFW_MOUSE_BUTTON_MIDDLE;
        case Button::Extra1:    return GLFW_MOUSE_BUTTON_4;
        case Button::Extra2:    return GLFW_MOUSE_BUTTON_5;
        case Button::Extra3:    return GLFW_MOUSE_BUTTON_6;
        case Button::Extra4:    return GLFW_MOUSE_BUTTON_7;
        case Button::Extra5:    return GLFW_MOUSE_BUTTON_8;
        }
        return GLFW_KEY_UNKNOWN;
    }

    constexpr Mouse::Button Mouse::fromGLFWButton(std::int32_t button) noexcept
    {
        switch (button)
        {
        case GLFW_MOUSE_BUTTON_LEFT:    return Button::Left;
        case GLFW_MOUSE_BUTTON_RIGHT:   return Button::Right;
        case GLFW_MOUSE_BUTTON_MIDDLE:  return Button::Middle;
        case GLFW_MOUSE_BUTTON_4:       return Button::Extra1;
        case GLFW_MOUSE_BUTTON_5:       return Button::Extra2;
        case GLFW_MOUSE_BUTTON_6:       return Button::Extra3;
        case GLFW_MOUSE_BUTTON_7:       return Button::Extra4;
        case GLFW_MOUSE_BUTTON_8:       return Button::Extra5;
        default:                        return Button::Unknown;
        }
    }
}
