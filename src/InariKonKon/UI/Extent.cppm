module;

#include <cstdint>

export module Extent;

import TypeUtils;
import Clamped;

export namespace ikk
{
    struct [[nodiscard]] Pixel final
    {
        using Type = std::uint32_t;

        std::uint32_t value{};

        [[nodiscard]] constexpr operator std::uint32_t() const noexcept;
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
    concept Unit = Is<T>::template AnyOf<Pixel, Percentage, Fill, Shrink>::value;

    //TODO: Since this is templated when using in internaly
    //i should just use a different one that only stores pixel
    //data instead of percentage or something else...
    //This should only be used to calculate absolute stuff...

    template<Unit T = Fill, Unit U = Fill>
    struct [[nodiscard]] Extent final
    {
        T x{};
        U y{};
    };
}

namespace ikk
{
    constexpr Pixel::operator unsigned int() const noexcept
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
    return ikk::Pixel{ .value = static_cast<std::uint32_t>(value) };
}

export [[nodiscard]] inline constexpr ikk::Percentage operator""_p(long double value) noexcept
{
    return ikk::Percentage{ .value = static_cast<float>(value) };
}

export [[nodiscard]] inline constexpr ikk::Percentage operator""_p(unsigned long long value) noexcept
{
    return ikk::Percentage{ .value = static_cast<float>(value) };
}