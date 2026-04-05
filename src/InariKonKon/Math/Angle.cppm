module;

#include <concepts>
#include <numbers>

export module Angle;

export namespace ikk
{
    template<std::floating_point T>
    struct [[nodiscard]] Degree final
    {
        using Type = T;
        T value = 0.f;
    };

    using Degreef = Degree<float>;
    using Degreed = Degree<double>;

    template<std::floating_point T>
    struct [[nodiscard]] Radian final
    {
        using Type = T;
        T value = 0.f;
    };

    using Radianf = Radian<float>;
    using Radiand = Radian<double>;

    template<std::floating_point T>
    [[nodiscard]] inline constexpr Degree<T> toDegree(Radian<T> rad) noexcept
    {
        return Degree<T>{ .value = rad.value * (static_cast<T>(180.f) / std::numbers::pi_v<T>) };
    }

    template<std::floating_point T>
    [[nodiscard]] inline constexpr Radian<T> toRadian(Degree<T> deg) noexcept
    {
        return Radian<T>{ .value = deg.value * (std::numbers::pi_v<T> / static_cast<T>(180.f)) };
    }
}