module;

#include <functional>
#include <tuple>

export module FunctionTraits;

export namespace ikk
{
    template<class T>
    struct FunctionTraits : FunctionTraits<decltype(&T::operator())> {};

    template<class ReturnType, class ClassType, class... Args>
    struct FunctionTraits<ReturnType(ClassType::*)(Args...)>
    {
        using ResultType = ReturnType;
        using ArgsTuple = std::tuple<Args...>;
        inline static constexpr std::size_t arity = sizeof...(Args);
    };

    template<class ReturnType, class ClassType, class... Args>
    struct FunctionTraits<ReturnType(ClassType::*)(Args...) const>
    {
        using ResultType = ReturnType;
        using ArgsTuple = std::tuple<Args...>;
        inline static constexpr std::size_t arity = sizeof...(Args);
    };

    template<class ReturnType, class ClassType, class... Args>
    struct FunctionTraits<ReturnType(ClassType::*)(Args...) noexcept>
    {
        using ResultType = ReturnType;
        using ArgsTuple = std::tuple<Args...>;
        inline static constexpr std::size_t arity = sizeof...(Args);
    };

    template<class ReturnType, class ClassType, class... Args>
    struct FunctionTraits<ReturnType(ClassType::*)(Args...) const noexcept>
    {
        using ResultType = ReturnType;
        using ArgsTuple = std::tuple<Args...>;
        inline static constexpr std::size_t arity = sizeof...(Args);
    };

    template<class ReturnType, class... Args>
    struct FunctionTraits<ReturnType(*)(Args...)>
    {
        using ResultType = ReturnType;
        using ArgsTuple = std::tuple<Args...>;
        inline static constexpr std::size_t arity = sizeof...(Args);
    };

    template<class ReturnType, class... Args>
    struct FunctionTraits<ReturnType(&)(Args...)>
    {
        using ResultType = ReturnType;
        using ArgsTuple = std::tuple<Args...>;
        inline static constexpr std::size_t arity = sizeof...(Args);
    };

    template<class ReturnType, class... Args>
    struct FunctionTraits<std::function<ReturnType(Args...)>>
    {
        using ResultType = ReturnType;
        using ArgsTuple = std::tuple<Args...>;
        inline static constexpr std::size_t arity = sizeof...(Args);
    };
}