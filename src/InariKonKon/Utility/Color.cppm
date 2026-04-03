module;

#include <type_traits>
#include <cstdint>
#include <limits>

export module Color;

import Utility;
import Clamped;
import Math;

export namespace ikk
{
    template<Number T>
    struct [[nodiscard]] BasicColor final
    {
        struct [[nodiscard]] Channel final
        {
            using Type = T;

            [[nodiscard]] constexpr Channel() noexcept = default;
            [[nodiscard]] constexpr Channel(T value) noexcept;

            constexpr Channel(const Channel&) noexcept = default;
            constexpr Channel(Channel&&) noexcept = default;

            constexpr Channel& operator=(const Channel&) noexcept = default;
            constexpr Channel& operator=(Channel&&) noexcept = default;

            constexpr ~Channel() noexcept = default;

            [[nodiscard]] constexpr operator T() const noexcept;

            T value = 0;
        };

        [[nodiscard]] constexpr BasicColor() noexcept = default;
        [[nodiscard]] constexpr BasicColor(T r, T g, T b, T a = std::numeric_limits<T>::max()) noexcept;

        constexpr BasicColor(const BasicColor&) noexcept = default;
        constexpr BasicColor(BasicColor&&) noexcept = default;

        constexpr BasicColor& operator=(const BasicColor&) noexcept = default;
        constexpr BasicColor& operator=(BasicColor&&) noexcept = default;

        constexpr ~BasicColor() noexcept = default;

        Channel r = {};
        Channel g = {};
        Channel b = {};
        Channel a = { std::numeric_limits<T>::max() };

        static const BasicColor White;
        static const BasicColor Black;
        static const BasicColor Red;
        static const BasicColor Green;
        static const BasicColor Blue;
        static const BasicColor Yellow;
        static const BasicColor Magenta;
        static const BasicColor Cyan;
        static const BasicColor CornflowerBlue;
        static const BasicColor Transparent;

        static const BasicColor Miku;
        static const BasicColor Teto;
        static const BasicColor Rin;
    };

    using Colorf = BasicColor<Clamped<float, 0.f, 1.f>>;
    using Coloru8 = BasicColor<std::uint8_t>;

    using Color = Coloru8;
}

namespace ikk
{
    template <Number T>
    constexpr BasicColor<T>::Channel::Channel(T value) noexcept
        : value(value)
    {
    }

    template <Number T>
    constexpr BasicColor<T>::Channel::operator T() const noexcept
    {
        return value;
    }

    template <Number T>
    constexpr BasicColor<T>::BasicColor(T r, T g, T b, T a) noexcept
        : r(r), g(g), b(b), a(a)
    {
    }

    //TODO: Work on this for a bit more, it works for now...
    template<Number T>
    inline constexpr T convert(std::uint8_t value) noexcept
    {
        Clamped<std::uint8_t> temp{value};
        if constexpr (std::is_class<T>::value == true)
            return T{temp};
        else
        {
            Clamped<T> clamped{temp};
            return T{clamped.value()};
        }
    }

    template<Number T>
    inline constexpr BasicColor<T> BasicColor<T>::White             { convert<T>(0xFF), convert<T>(0xFF), convert<T>(0xFF) };
    template<Number T>
    inline constexpr BasicColor<T> BasicColor<T>::Black             { convert<T>(0x00), convert<T>(0x00), convert<T>(0x00) };
    template<Number T>
    inline constexpr BasicColor<T> BasicColor<T>::Red               { convert<T>(0xFF), convert<T>(0x00), convert<T>(0x00) };
    template<Number T>
    inline constexpr BasicColor<T> BasicColor<T>::Green             { convert<T>(0x00), convert<T>(0xFF), convert<T>(0x00) };
    template<Number T>
    inline constexpr BasicColor<T> BasicColor<T>::Blue              { convert<T>(0x00), convert<T>(0x00), convert<T>(0xFF) };
    template<Number T>
    inline constexpr BasicColor<T> BasicColor<T>::Yellow            { convert<T>(0xFF), convert<T>(0xFF), convert<T>(0x00) };
    template<Number T>
    inline constexpr BasicColor<T> BasicColor<T>::Magenta           { convert<T>(0xFF), convert<T>(0x00), convert<T>(0xFF) };
    template<Number T>
    inline constexpr BasicColor<T> BasicColor<T>::Cyan              { convert<T>(0x00), convert<T>(0xFF), convert<T>(0xFF) };
    template<Number T>
    inline constexpr BasicColor<T> BasicColor<T>::Transparent       { convert<T>(0x00), convert<T>(0x00), convert<T>(0x00), convert<T>(0x00) };

    template<Number T>
    inline constexpr BasicColor<T> BasicColor<T>::CornflowerBlue    { convert<T>(0x64), convert<T>(0x95), convert<T>(0xED) };
    template<Number T>
    inline constexpr BasicColor<T> BasicColor<T>::Miku              { convert<T>(0x39), convert<T>(0xC5), convert<T>(0xBB) };
    template<Number T>
    inline constexpr BasicColor<T> BasicColor<T>::Teto              { convert<T>(0xE3), convert<T>(0x42), convert<T>(0x34) };
    template<Number T>
    inline constexpr BasicColor<T> BasicColor<T>::Rin               { convert<T>(0xFF), convert<T>(0xD7), convert<T>(0x00) };
}