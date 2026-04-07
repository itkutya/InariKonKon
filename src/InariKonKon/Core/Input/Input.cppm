module;

#include <type_traits>
#include <string_view>
#include <functional>
#include <utility>
#include <cstdint>
#include <string>
#include <ranges>
#include <tuple>

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

export module Core:Input;

import FunctionTraits;
import Singleton;
import VectorMap;

namespace ikk
{
    template<typename T>
    struct isInputType : std::false_type {};

    template<class T>
    concept InputType = isInputType<T>::value;
}

export namespace ikk
{
    class Input final : public Singleton<Input>
    {
        friend class Singleton<Input>;

        Input() noexcept = default;
    public:
        template<InputType T, class... Args>
        using Callback = std::function<void(T, Args...)>;

        enum struct [[nodiscard]] Action : std::int8_t
        {
            Unknown = 0,
            Press,
            Release,
            Repeat
        };

        using enum Action;

        ~Input() noexcept = default;

        [[nodiscard]] static constexpr std::string_view toString(Action type) noexcept;

        template<InputType T>
        void bind(const std::string& name, T input) noexcept;

        template<class FuncType>
        void onAction(const std::string& name, FuncType&& func) noexcept;
    private:
        template<InputType T>
        VectorMap<std::string, std::vector<T>>& getBindins() const noexcept;

        template<InputType T, class... Args>
        VectorMap<std::string, Callback<T, Args...>>& getCallbacks() const noexcept;

        template<InputType T, class... Args>
        void handleEvent(T input, Args&&... action) noexcept;

        [[nodiscard]] static constexpr Input::Action fromGLFWAction(std::int32_t action) noexcept;
        [[nodiscard]] static constexpr std::int32_t toGLFWAction(Input::Action type) noexcept;

        friend class EventCallbackFuncs;
    };

    inline Input& Input = Input::getInstance();
}

namespace ikk
{
    constexpr std::string_view Input::toString(Action type) noexcept
    {
        switch (type)
        {
            case Action::Unknown:    return "Unknown";
            case Action::Press:      return "Press";
            case Action::Release:    return "Release";
            case Action::Repeat:     return "Repeat";
        }
        return "Unknown";
    }

    template<InputType T>
    void Input::bind(const std::string& name, T input) noexcept
    {
        auto& bindings = this->getBindins<T>();
        std::vector<T>* found = bindings.find(name);
        if (found == nullptr)
            bindings.insert(name, std::vector<T>{input});
        else
        {
            for (const auto& i : (*found)) if (i == input) return;
            found->emplace_back(input);
        }
    }

    template<class FuncType>
    void Input::onAction(const std::string& name, FuncType&& func) noexcept
    {
        using Traits = FunctionTraits<std::decay_t<FuncType>>;
        [this]<typename F, typename... Args>(const std::string& n, F&& f, [[maybe_unused]] std::tuple<Args...>)
        {
            static_assert(std::is_invocable<FuncType, Args...>::value == true, "Input.onAction must be invokable");
            if (auto& callbacks = this->getCallbacks<Args...>(); callbacks.find(n) == nullptr)
                callbacks.insert(n, std::forward<F>(f));
        }(name, std::forward<FuncType>(func), typename Traits::ArgsTuple{});
    }

    template<InputType T>
    VectorMap<std::string, std::vector<T>>& Input::getBindins() const noexcept
    {
        static VectorMap<std::string, std::vector<T>> instance{};
        return instance;
    }

    template<InputType T, class... Args>
    VectorMap<std::string, Input::Callback<T, Args...>>& Input::getCallbacks() const noexcept
    {
        static VectorMap<std::string, Input::Callback<T, Args...>> instance{};
        return instance;
    }

    template<InputType T, class... Args>
    void Input::handleEvent(T input, Args&&... action) noexcept
    {
        const auto& bindings = this->getBindins<T>();
        const auto it = std::ranges::find_if(bindings,
            [&input](const auto& pair)
            {
                for (const auto& i : pair.second) if (i == input) return true;
                return false;
            });

        if (it == bindings.end())
            return;

        const auto& callbacks = this->getCallbacks<T, typename std::decay<Args>::type...>();
        if (const auto* callback = callbacks.find(it->first); callback != nullptr)
            (*callback)(input, std::forward<Args>(action)...);
    }

    constexpr Input::Action Input::fromGLFWAction(std::int32_t action) noexcept
    {
        switch (action)
        {
        case GLFW_PRESS:    return Action::Press;
        case GLFW_RELEASE:  return Action::Release;
        case GLFW_REPEAT:   return Action::Repeat;
        default:            return Action::Unknown;
        }
    }

    constexpr std::int32_t Input::toGLFWAction(Input::Action type) noexcept
    {
        switch (type)
        {
        case Action::Unknown:    return GLFW_KEY_UNKNOWN;
        case Action::Press:      return GLFW_PRESS;
        case Action::Release:    return GLFW_RELEASE;
        case Action::Repeat:     return GLFW_REPEAT;
        }
        return GLFW_KEY_UNKNOWN;
    }
}