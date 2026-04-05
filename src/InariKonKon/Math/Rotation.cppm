module;

#include <type_traits>
#include <concepts>

export module Rotation;

import Number;
import Angle;

export namespace ikk
{
    template<template<class> class T, std::floating_point F> requires (std::is_same<T<F>, Degree<F>>::value || std::is_same<T<F>, Radian<F>>::value)
    struct [[nodiscard]] Rotation
    {
        T<F> yaw{};
        T<F> pitch{};
        T<F> roll{};
    };

    template<Number T> using RotationDeg = Rotation<Degree, T>;
    template<Number T> using RotationRad = Rotation<Radian, T>;

    using RotationDegf = RotationDeg<float>;
    using RotationDegd = RotationDeg<double>;
    using RotationRadf = RotationRad<float>;
    using RotationRadd = RotationRad<double>;
}