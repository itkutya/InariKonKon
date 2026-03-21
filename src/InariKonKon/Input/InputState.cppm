module;

#include <string_view>
#include <cstdint>

export module Input:InputState;

import NonConstructible;

export namespace ikk
{
    class Input final : public NonConstructible
    {
    public:
        enum struct [[nodiscard]] State : std::int8_t
        {
            Unknown = 0,
            Press,
            Release,
            Repeat
        };

        [[nodiscard]] static constexpr std::string_view toString(State type) noexcept;
    };
}

namespace ikk
{
    constexpr std::string_view Input::toString(State type) noexcept
    {
        switch (type)
        {
            case State::Unknown:    return "Unknown";
            case State::Press:      return "Press";
            case State::Release:    return "Release";
            case State::Repeat:     return "Repeat";
        }
        return "Unknown";
    }
}