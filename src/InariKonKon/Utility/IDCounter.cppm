module;

#include <concepts>

export module IDCounter;

export namespace ikk
{
    template<std::integral T>
    [[nodiscard]] inline T getNext() noexcept
    {
        static T id{};
        return ++id;
    }
}