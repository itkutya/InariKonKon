module;

#include <type_traits>
#include <concepts>

export module Rotation;

import TypeUtils;
import Number;
import Angle;

export namespace ikk
{
    template<class T>
    concept RotationType = Is<T>::template AnyOf<Degree<float>, Degree<double>, Degree<long double>,
                                                 Radian<float>, Radian<double>, Radian<long double>>::value;

    template<RotationType T>
    struct [[nodiscard]] Rotation
    {
        T yaw{};
        T pitch{};
        T roll{};
    };

    template<std::floating_point T> using RotationDeg = Rotation<Degree<T>>;
    template<std::floating_point T> using RotationRad = Rotation<Radian<T>>;

    using RotationDegf = RotationDeg<float>;
    using RotationDegd = RotationDeg<double>;
    using RotationRadf = RotationRad<float>;
    using RotationRadd = RotationRad<double>;
}