module;

#include <type_traits>
#include <cstdint>

export module Extent;

import Clamped;

export namespace ikk
{
    struct [[nodiscard]] Pixel final
    {
        std::uint32_t value{};

        [[nodiscard]] constexpr operator std::uint32_t() const noexcept;
    };

    struct [[nodiscard]] Percentage final
    {
        Clamped<float, 0.f, 100.f> value{};

        [[nodiscard]] constexpr operator float() const noexcept;
    };

    template<class T>
    concept Unit = std::is_same<T, Pixel>::value || std::is_same<T, Percentage>::value;

    //TODO: Since this is templated when using in internaly
    //i should just use a different one that only stores pixel
    //data instead of percentage or something else...

    template<Unit T, Unit U>
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