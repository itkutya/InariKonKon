module;

#include <type_traits>

export module TypeUtils;

import NonConstructible;

export namespace ikk
{
    template<class T>
    struct Is final : public NonConstructible
    {
        template<class... Ts>
        struct AnyOf final : public NonConstructible
        {
            inline static constexpr bool value = (std::is_same<T, Ts>::value || ...);
        };
    };
}