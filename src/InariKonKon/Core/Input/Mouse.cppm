module;

#include <string_view>
#include <cstdint>

export module Core:Mouse;

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
    };
}

namespace ikk
{
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
}