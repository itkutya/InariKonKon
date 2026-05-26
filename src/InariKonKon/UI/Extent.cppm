module;

#include <variant>

export module Extent;

import TypeUtils;
import Clamped;

export namespace ikk
{
    struct [[nodiscard]] Pixel final
    {
        using Type = float;

        Type value{};

        [[nodiscard]] constexpr operator Type() const noexcept;
    };

    struct [[nodiscard]] Percentage final
    {
        using Type = float;

        Clamped<float, 0.f, 100.f> value{};

        [[nodiscard]] constexpr operator float() const noexcept;
    };

    struct Fill
    {
        using Type = void;
    };

    struct Shrink
    {
        using Type = void;
    };

    template<class T>
    concept UnitType = Is<T>::template AnyOf<Pixel, Percentage, Fill, Shrink>::value;

    struct [[nodiscard]] Extent final
    {
        using Unit = std::variant<Pixel, Percentage, Fill, Shrink>;

        Unit x = Fill{};
        Unit y = Fill{};
    };
}

namespace ikk
{
    constexpr Pixel::operator Type() const noexcept
    {
        return this->value;
    }

    constexpr Percentage::operator float() const noexcept
    {
        return this->value;
    }
}

export [[nodiscard]] inline constexpr ikk::Pixel operator""_px(unsigned long long value) noexcept
{
    return ikk::Pixel{ .value = static_cast<ikk::Pixel::Type>(value) };
}

export [[nodiscard]] inline constexpr ikk::Percentage operator""_p(long double value) noexcept
{
    return ikk::Percentage{ .value = static_cast<float>(value) };
}

export [[nodiscard]] inline constexpr ikk::Percentage operator""_p(unsigned long long value) noexcept
{
    return ikk::Percentage{ .value = static_cast<float>(value) };
}