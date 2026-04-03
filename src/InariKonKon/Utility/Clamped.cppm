module;

#include <algorithm>
#include <cstdint>
#include <limits>

export module Clamped;

import Math;

export namespace ikk
{
    template<Number T>
    struct DefaultClampedRange
    {
        inline static constexpr T min = std::numeric_limits<T>::min();
        inline static constexpr T max = std::numeric_limits<T>::max();
    };

    template<>
    struct DefaultClampedRange<float>
    {
        inline static constexpr float min = 0.f;
        inline static constexpr float max = 1.f;
    };

    template<>
    struct DefaultClampedRange<double>
    {
        inline static constexpr double min = 0.0;
        inline static constexpr double max = 1.0;
    };

    template<>
    struct DefaultClampedRange<long double>
    {
        inline static constexpr long double min = 0.0L;
        inline static constexpr long double max = 1.0L;
    };

    template<Number T, T Min = DefaultClampedRange<T>::min, T Max = DefaultClampedRange<T>::max>
    class [[nodiscard]] Clamped final
    {
    public:
        using Type = T;

        [[nodiscard]] constexpr Clamped() noexcept;
        [[nodiscard]] constexpr Clamped(T value) noexcept;

        constexpr Clamped(const Clamped&) noexcept = default;
        constexpr Clamped(Clamped&&) noexcept = default;

        constexpr Clamped& operator=(const Clamped&) noexcept = default;
        constexpr Clamped& operator=(Clamped&&) noexcept = default;

        template<T OtherMin, T OtherMax>
        explicit constexpr Clamped(const Clamped<T, OtherMin, OtherMax>& other) noexcept;
        template<T OtherMin, T OtherMax>
        explicit constexpr Clamped(Clamped<T, OtherMin, OtherMax>&& other) noexcept;

        template<T OtherMin, T OtherMax>
        constexpr Clamped& operator=(const Clamped<T, OtherMin, OtherMax>& other) noexcept;
        template<T OtherMin, T OtherMax>
        constexpr Clamped& operator=(Clamped<T, OtherMin, OtherMax>&& other) noexcept;

        template<Number U, U OtherMin, U OtherMax> requires (std::is_convertible<U, T>::value)
        explicit constexpr Clamped(const Clamped<U, OtherMin, OtherMax>& other) noexcept;
        template<Number U, U OtherMin, U OtherMax> requires (std::is_convertible<U, T>::value)
        explicit constexpr Clamped(Clamped<U, OtherMin, OtherMax>&& other) noexcept;

        template<Number U, U OtherMin, U OtherMax> requires (std::is_convertible<U, T>::value)
        constexpr Clamped& operator=(const Clamped<U, OtherMin, OtherMax>& other) noexcept;
        template<Number U, U OtherMin, U OtherMax> requires (std::is_convertible<U, T>::value)
        constexpr Clamped& operator=(Clamped<U, OtherMin, OtherMax>&& other) noexcept;

        constexpr ~Clamped() noexcept = default;

        [[nodiscard]] constexpr Clamped operator+(const Clamped& value) const noexcept;
        [[nodiscard]] constexpr Clamped operator-(const Clamped& value) const noexcept;
        [[nodiscard]] constexpr Clamped operator*(const Clamped& value) const noexcept;
        [[nodiscard]] constexpr Clamped operator/(const Clamped& value) const noexcept;

        constexpr Clamped& operator+=(const Clamped& value) noexcept;
        constexpr Clamped& operator-=(const Clamped& value) noexcept;
        constexpr Clamped& operator*=(const Clamped& value) noexcept;
        constexpr Clamped& operator/=(const Clamped& value) noexcept;

        [[nodiscard]] constexpr bool operator==(const Clamped& value) const noexcept;
        [[nodiscard]] constexpr bool operator!=(const Clamped& value) const noexcept;
        [[nodiscard]] constexpr bool operator<=(const Clamped& value) const noexcept;
        [[nodiscard]] constexpr bool operator>=(const Clamped& value) const noexcept;
        [[nodiscard]] constexpr bool operator<(const Clamped& value) const noexcept;
        [[nodiscard]] constexpr bool operator>(const Clamped& value) const noexcept;

        [[nodiscard]] constexpr Clamped operator+(T value) const noexcept;
        [[nodiscard]] constexpr Clamped operator-(T value) const noexcept;
        [[nodiscard]] constexpr Clamped operator*(T value) const noexcept;
        [[nodiscard]] constexpr Clamped operator/(T value) const noexcept;

        constexpr Clamped& operator+=(T value) noexcept;
        constexpr Clamped& operator-=(T value) noexcept;
        constexpr Clamped& operator*=(T value) noexcept;
        constexpr Clamped& operator/=(T value) noexcept;

        [[nodiscard]] constexpr bool operator==(T value) const noexcept;
        [[nodiscard]] constexpr bool operator!=(T value) const noexcept;
        [[nodiscard]] constexpr bool operator<=(T value) const noexcept;
        [[nodiscard]] constexpr bool operator>=(T value) const noexcept;
        [[nodiscard]] constexpr bool operator<(T value) const noexcept;
        [[nodiscard]] constexpr bool operator>(T value) const noexcept;

        [[nodiscard]] explicit constexpr operator T() const noexcept;

        [[nodiscard]] constexpr T value() const noexcept;
    private:
        T m_value{};

        template<Number U, U OtherMin, U OtherMax> requires (std::is_convertible<U, T>::value)
        constexpr T convertValueFromOtherRange(U other) const noexcept;
    };
}

namespace ikk
{
    template<Number T, T Min, T Max>
    constexpr Clamped<T, Min, Max>::Clamped() noexcept
        : m_value(Min)
    {
    }

    template<Number T, T Min, T Max>
    constexpr Clamped<T, Min, Max>::Clamped(T value) noexcept
        : m_value(std::clamp(value, Min, Max))
    {
    }

    template<Number T, T Min, T Max>
    template<T OtherMin, T OtherMax>
    constexpr Clamped<T, Min, Max>::Clamped(const Clamped<T, OtherMin, OtherMax>& other) noexcept
        : m_value(convertValueFromOtherRange<T, OtherMin, OtherMax>(other.value()))
    {
    }

    template<Number T, T Min, T Max>
    template<T OtherMin, T OtherMax>
    constexpr Clamped<T, Min, Max>::Clamped(Clamped<T, OtherMin, OtherMax>&& other) noexcept
        : m_value(convertValueFromOtherRange<T, OtherMin, OtherMax>(other.value()))
    {
    }

    template<Number T, T Min, T Max>
    template<T OtherMin, T OtherMax>
    constexpr Clamped<T, Min, Max>& Clamped<T, Min, Max>::operator=(const Clamped<T, OtherMin, OtherMax>& other) noexcept
    {
        this->m_value = this->convertValueFromOtherRange<T, OtherMin, OtherMax>(other.value());
        return *this;
    }

    template<Number T, T Min, T Max>
    template<T OtherMin, T OtherMax>
    constexpr Clamped<T, Min, Max>& Clamped<T, Min, Max>::operator=(Clamped<T, OtherMin, OtherMax>&& other) noexcept
    {
        this->m_value = this->convertValueFromOtherRange<T, OtherMin, OtherMax>(other.value());
        return *this;
    }

    template <Number T, T Min, T Max>
    template <Number U, U OtherMin, U OtherMax> requires (std::is_convertible<U, T>::value)
    constexpr Clamped<T, Min, Max>::Clamped(const Clamped<U, OtherMin, OtherMax>& other) noexcept
        : m_value(convertValueFromOtherRange<U, OtherMin, OtherMax>(other.value()))
    {
    }

    template <Number T, T Min, T Max>
    template <Number U, U OtherMin, U OtherMax> requires (std::is_convertible<U, T>::value)
    constexpr Clamped<T, Min, Max>::Clamped(Clamped<U, OtherMin, OtherMax>&& other) noexcept
        : m_value(convertValueFromOtherRange<U, OtherMin, OtherMax>(other.value()))
    {
    }

    template <Number T, T Min, T Max>
    template <Number U, U OtherMin, U OtherMax> requires (std::is_convertible<U, T>::value)
    constexpr Clamped<T, Min, Max>& Clamped<T, Min, Max>::operator=(const Clamped<U, OtherMin, OtherMax>& other) noexcept
    {
        this->m_value = this->convertValueFromOtherRange<U, OtherMin, OtherMax>(other.value());
        return *this;
    }

    template <Number T, T Min, T Max>
    template <Number U, U OtherMin, U OtherMax> requires (std::is_convertible<U, T>::value)
    constexpr Clamped<T, Min, Max>& Clamped<T, Min, Max>::operator=(Clamped<U, OtherMin, OtherMax>&& other) noexcept
    {
        this->m_value = this->convertValueFromOtherRange<U, OtherMin, OtherMax>(other.value());
        return *this;
    }

    template<Number T, T Min, T Max>
    constexpr Clamped<T, Min, Max> Clamped<T, Min, Max>::operator+(const Clamped<T, Min, Max>& value) const noexcept
    {
        return Clamped<T, Min, Max>{ std::clamp(this->m_value + value.value(), Min, Max) };
    }

    template<Number T, T Min, T Max>
    constexpr Clamped<T, Min, Max> Clamped<T, Min, Max>::operator-(const Clamped<T, Min, Max>& value) const noexcept
    {
        return Clamped<T, Min, Max>{ std::clamp(this->m_value - value.value(), Min, Max) };
    }

    template<Number T, T Min, T Max>
    constexpr Clamped<T, Min, Max> Clamped<T, Min, Max>::operator*(const Clamped<T, Min, Max>& value) const noexcept
    {
        return Clamped<T, Min, Max>{ std::clamp(this->m_value * value.value(), Min, Max) };
    }

    template<Number T, T Min, T Max>
    constexpr Clamped<T, Min, Max> Clamped<T, Min, Max>::operator/(const Clamped<T, Min, Max>& value) const noexcept
    {
        return Clamped<T, Min, Max>{ std::clamp(this->m_value / value.value(), Min, Max) };
    }

    template<Number T, T Min, T Max>
    constexpr Clamped<T, Min, Max>& Clamped<T, Min, Max>::operator+=(const Clamped<T, Min, Max>& value) noexcept
    {
        this->m_value = std::clamp(this->m_value + value.value(), Min, Max);
        return *this;
    }

    template<Number T, T Min, T Max>
    constexpr Clamped<T, Min, Max>& Clamped<T, Min, Max>::operator-=(const Clamped<T, Min, Max>& value) noexcept
    {
        this->m_value = std::clamp(this->m_value - value.value(), Min, Max);
        return *this;
    }

    template<Number T, T Min, T Max>
    constexpr Clamped<T, Min, Max>& Clamped<T, Min, Max>::operator*=(const Clamped<T, Min, Max>& value) noexcept
    {
        this->m_value = std::clamp(this->m_value * value.value(), Min, Max);
        return *this;
    }

    template<Number T, T Min, T Max>
    constexpr Clamped<T, Min, Max>& Clamped<T, Min, Max>::operator/=(const Clamped<T, Min, Max>& value) noexcept
    {
        this->m_value = std::clamp(this->m_value / value.value(), Min, Max);
        return *this;
    }

    template<Number T, T Min, T Max>
    constexpr bool Clamped<T, Min, Max>::operator==(const Clamped<T, Min, Max>& value) const noexcept
    {
        return this->m_value.value() == value.value();
    }

    template<Number T, T Min, T Max>
    constexpr bool Clamped<T, Min, Max>::operator!=(const Clamped<T, Min, Max>& value) const noexcept
    {
        return this->m_value.value() != value.value();
    }

    template<Number T, T Min, T Max>
    constexpr bool Clamped<T, Min, Max>::operator<=(const Clamped<T, Min, Max>& value) const noexcept
    {
        return this->m_value.value() <= value.value();
    }

    template<Number T, T Min, T Max>
    constexpr bool Clamped<T, Min, Max>::operator>=(const Clamped<T, Min, Max>& value) const noexcept
    {
        return this->m_value.value() >= value.value();
    }

    template<Number T, T Min, T Max>
    constexpr bool Clamped<T, Min, Max>::operator<(const Clamped<T, Min, Max>& value) const noexcept
    {
        return this->m_value.value() < value.value();
    }

    template<Number T, T Min, T Max>
    constexpr bool Clamped<T, Min, Max>::operator>(const Clamped<T, Min, Max>& value) const noexcept
    {
        return this->m_value.value() > value.value();
    }

    template<Number T, T Min, T Max>
    constexpr Clamped<T, Min, Max> Clamped<T, Min, Max>::operator+(T value) const noexcept
    {
        return Clamped<T, Min, Max>{ std::clamp(this->m_value + value, Min, Max) };
    }

    template<Number T, T Min, T Max>
    constexpr Clamped<T, Min, Max> Clamped<T, Min, Max>::operator-(T value) const noexcept
    {
        return Clamped<T, Min, Max>{ std::clamp(this->m_value - value, Min, Max) };
    }

    template<Number T, T Min, T Max>
    constexpr Clamped<T, Min, Max> Clamped<T, Min, Max>::operator*(T value) const noexcept
    {
        return Clamped<T, Min, Max>{ std::clamp(this->m_value * value, Min, Max) };
    }

    template<Number T, T Min, T Max>
    constexpr Clamped<T, Min, Max> Clamped<T, Min, Max>::operator/(T value) const noexcept
    {
        return Clamped<T, Min, Max>{ std::clamp(this->m_value / value, Min, Max) };
    }

    template<Number T, T Min, T Max>
    constexpr Clamped<T, Min, Max>& Clamped<T, Min, Max>::operator+=(T value) noexcept
    {
        this->m_value = std::clamp(this->m_value + value, Min, Max);
        return *this;
    }

    template<Number T, T Min, T Max>
    constexpr Clamped<T, Min, Max>& Clamped<T, Min, Max>::operator-=(T value) noexcept
    {
        this->m_value = std::clamp(this->m_value - value, Min, Max);
        return *this;
    }

    template<Number T, T Min, T Max>
    constexpr Clamped<T, Min, Max>& Clamped<T, Min, Max>::operator*=(T value) noexcept
    {
        this->m_value = std::clamp(this->m_value * value, Min, Max);
        return *this;
    }

    template<Number T, T Min, T Max>
    constexpr Clamped<T, Min, Max>& Clamped<T, Min, Max>::operator/=(T value) noexcept
    {
        this->m_value = std::clamp(this->m_value / value, Min, Max);
        return *this;
    }

    template<Number T, T Min, T Max>
    constexpr bool Clamped<T, Min, Max>::operator==(T value) const noexcept
    {
        return this->m_value == value;
    }

    template<Number T, T Min, T Max>
    constexpr bool Clamped<T, Min, Max>::operator!=(T value) const noexcept
    {
        return this->m_value != value;
    }

    template<Number T, T Min, T Max>
    constexpr bool Clamped<T, Min, Max>::operator<=(T value) const noexcept
    {
        return this->m_value <= value;
    }

    template<Number T, T Min, T Max>
    constexpr bool Clamped<T, Min, Max>::operator>=(T value) const noexcept
    {
        return this->m_value >= value;
    }

    template<Number T, T Min, T Max>
    constexpr bool Clamped<T, Min, Max>::operator<(T value) const noexcept
    {
        return this->m_value < value;
    }

    template<Number T, T Min, T Max>
    constexpr bool Clamped<T, Min, Max>::operator>(T value) const noexcept
    {
        return this->m_value > value;
    }

    template <Number T, T Min, T Max>
    constexpr Clamped<T, Min, Max>::operator T() const noexcept
    {
        return this->m_value;
    }

    template<Number T, T Min, T Max>
    constexpr T Clamped<T, Min, Max>::value() const noexcept
    {
        return this->m_value;
    }

    template<Number T, T Min, T Max>
    template<Number U, U OtherMin, U OtherMax> requires (std::is_convertible<U, T>::value)
    constexpr T Clamped<T, Min, Max>::convertValueFromOtherRange(U other) const noexcept
    {
        using Common = std::common_type_t<T, U, std::int64_t>;

        const Common otherRange = static_cast<Common>(OtherMax) - static_cast<Common>(OtherMin);
        const Common range      = static_cast<Common>(Max) - static_cast<Common>(Min);

        if (otherRange == 0) return Min;

        Common value = ((static_cast<Common>(other) - static_cast<Common>(OtherMin)) * range) / otherRange + static_cast<Common>(Min);
        value = std::clamp(value, static_cast<Common>(Min), static_cast<Common>(Max));

        return static_cast<T>(value);
    }
}

export namespace std
{
    template<ikk::Number T, T Min, T Max>
    struct numeric_limits<ikk::Clamped<T, Min, Max>>
    {
    public:
        static constexpr bool is_specialized = true;

        static constexpr T min() noexcept
        {
            return Min;
        }

        static constexpr T max() noexcept
        {
            return Max;
        }

        static constexpr T lowest() noexcept
        {
            return std::numeric_limits<T>::lowest();
        }

        static constexpr int digits = std::numeric_limits<T>::digits;
        static constexpr int digits10 = std::numeric_limits<T>::digits10;

        static constexpr bool is_signed = std::is_signed<T>::value;
        static constexpr bool is_integer = std::is_integral<T>::value;
        static constexpr bool is_exact = std::is_integral<T>::value;
        static constexpr bool is_bounded = true;

        static constexpr bool has_infinity = true;
        static constexpr T infinity() noexcept
        {
            return std::numeric_limits<T>::infinity();
        }
    };
}