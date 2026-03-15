module;

#include <type_traits>

export module Singleton;

import NonCopyable;
import NonMovable;

export namespace ikk
{
    template<class T>
    class Singleton : public NonCopyable, public NonMovable
    {
        static_assert(std::is_class<T>::value == true, "T must be a class type");
    public:
        virtual ~Singleton() noexcept = default;

        [[nodiscard]] static T& getInstance() noexcept;
    protected:
        Singleton() noexcept = default;
    };

    template<class T>
    T& Singleton<T>::getInstance() noexcept
    {
        static T instance;
        return instance;
    }
}