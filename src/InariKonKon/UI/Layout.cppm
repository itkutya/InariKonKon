module;

#include <cstdint>

export module Layout;

import Flag;

export namespace ikk
{
    struct [[nodiscard]] Layout final
    {
        enum struct [[nodiscard]] Position : std::uint8_t
        {
            Middle      = 1 << 0,
            Top         = 1 << 1,
            Bottom      = 1 << 2,
            Left        = 1 << 3,
            Right       = 1 << 4,

            TopLeft     = Top | Left,
            TopRight    = Top | Right,

            MiddleLeft  = Middle | Left,
            MiddleRight = Middle | Right,

            BottomLeft  = Bottom | Left,
            BottomRight = Bottom | Right,

            All         = Top | Middle | Bottom | Left | Right,
        };

        enum struct [[nodiscard]] Direction : std::uint8_t
        {
            Horizontal,
            Vertical,

            Row     = Horizontal,
            Column  = Vertical,
        };

        using enum Position;
        using enum Direction;

        Flag<Position> position = Position::Middle;
        Direction direction     = Direction::Horizontal;
    };
}