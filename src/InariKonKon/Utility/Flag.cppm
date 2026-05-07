module;

#include <type_traits>

export module Flag;

export namespace ikk
{
    template<class T> requires std::is_enum<T>::value
    class [[nodiscard]] Flag final
    {
        using UnderlyingType = typename std::underlying_type<T>::type;
    public:
        [[nodiscard]] constexpr Flag(T flags) noexcept;

        Flag(const Flag&) noexcept = default;
        Flag(Flag&&) noexcept = default;

        Flag& operator=(const Flag&) noexcept = default;
        Flag& operator=(Flag&&) noexcept = default;

        ~Flag() noexcept = default;

        [[nodiscard]] constexpr operator T() const noexcept;

        [[nodiscard]] constexpr Flag operator|(T flag) const noexcept;
        constexpr void operator|=(T flag) noexcept;

        [[nodiscard]] constexpr bool contains(T flag) const noexcept;
    private:
        T m_flags;
    };
}

namespace ikk
{
    template<class T> requires std::is_enum<T>::value
    constexpr Flag<T>::Flag(T flags) noexcept
        : m_flags(flags)
    {
    }

    template<class T> requires std::is_enum<T>::value
    constexpr Flag<T>::operator T() const noexcept
    {
        return this->m_flags;
    }

    template<class T> requires std::is_enum<T>::value
    constexpr Flag<T> Flag<T>::operator|(T flag) const noexcept
    {
        return Flag<T>{static_cast<T>(static_cast<UnderlyingType>(this->m_flags) | static_cast<UnderlyingType>(flag))};
    }

    template<class T> requires std::is_enum<T>::value
    constexpr void Flag<T>::operator|=(T flag) noexcept
    {
        const UnderlyingType v = static_cast<UnderlyingType>(this->m_flags) | static_cast<UnderlyingType>(flag);
        this->m_flags = static_cast<T>(v);
    }

    template<class T> requires std::is_enum<T>::value
    constexpr bool Flag<T>::contains(T flag) const noexcept
    {
        return static_cast<UnderlyingType>(static_cast<UnderlyingType>(this->m_flags) & static_cast<UnderlyingType>(flag)) == static_cast<UnderlyingType>(flag);
    }
}