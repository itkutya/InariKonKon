module;

#include <type_traits>
#include <limits>
#include <cmath>

export module  Number;

export namespace ikk
{
    template<class T>
    concept BasicNumber = std::is_arithmetic<T>::value == true && std::is_same<T, bool>::value == false;

    template<class T>
    concept Number = BasicNumber<T> || BasicNumber<typename T::Type>;

    template<Number T>
    [[nodiscard]] inline constexpr bool isZero(T value, T tolerance = std::numeric_limits<T>::epsilon()) noexcept
    {
        if constexpr (std::is_floating_point<T>::value)
            return std::abs(value) <= tolerance;
        else
            return value == T{0};
    }
}