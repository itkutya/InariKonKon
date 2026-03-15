module;

#include <type_traits>

export module Flag;

export namespace ikk
{
    template<class T> requires std::is_enum<T>::value
    class [[nodiscard]] Flag final
    {
    public:
        [[nodiscard]] constexpr Flag(T flags) noexcept;

        Flag(const Flag&) noexcept = default;
        Flag(Flag&&) noexcept = default;

        Flag& operator=(const Flag&) noexcept = default;
        Flag& operator=(Flag&&) noexcept = default;

        ~Flag() noexcept = default;

        [[nodiscard]] constexpr operator T() const noexcept;

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
    constexpr bool Flag<T>::contains(T flag) const noexcept
    {
        using U = std::underlying_type<T>::type;
        return (static_cast<U>(this->m_flags) & static_cast<U>(flag)) == static_cast<U>(flag);
    }
}