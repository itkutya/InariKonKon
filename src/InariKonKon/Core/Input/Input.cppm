module;

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

export namespace ikk
{
    class Input final : public Singleton<Input>
    {
        friend class Singleton<Input>;

        Input() noexcept = default;
    public:
        template<class InputType, class... Args>
        using Callback = std::function<void(InputType, Args...)>;

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

        template<class InputType>
        void bind(const std::string& name, InputType input) noexcept;

        template<class FuncType>
        void onAction(const std::string& name, FuncType&& func) noexcept;
    private:
        template<class InputType>
        VectorMap<std::string, std::vector<InputType>>& getBindins() const noexcept;

        template<class InputType, class... Args>
        VectorMap<std::string, Callback<InputType, Args...>>& getCallbacks() const noexcept;

        template<class InputType, class... Args>
        void handleEvent(InputType input, Args&&... action) noexcept;

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

    template<class InputType>
    void Input::bind(const std::string& name, InputType input) noexcept
    {
        auto& bindings = this->getBindins<InputType>();
        auto* found = bindings.find(name);
        if (found == nullptr)
            bindings.insert(name, std::vector<InputType>{input});
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
            if (auto& callbacks = this->getCallbacks<Args...>(); callbacks.find(n) == nullptr)
                callbacks.insert(n, std::forward<F>(f));
        }(name, std::forward<FuncType>(func), typename Traits::ArgsTuple{});
    }

    template<class InputType>
    VectorMap<std::string, std::vector<InputType>>& Input::getBindins() const noexcept
    {
        static VectorMap<std::string, std::vector<InputType>> instance{};
        return instance;
    }

    template<class InputType, class... Args>
    VectorMap<std::string, Input::Callback<InputType, Args...>>& Input::getCallbacks() const noexcept
    {
        static VectorMap<std::string, Input::Callback<InputType, Args...>> instance{};
        return instance;
    }

    template<class InputType, class... Args>
    void Input::handleEvent(InputType input, Args&&... action) noexcept
    {
        const auto& bindings = this->getBindins<InputType>();
        const auto it = std::ranges::find_if(bindings,
            [&input](const auto& pair)
            {
                for (const auto& i : pair.second) if (i == input) return true;
                return false;
            });

        if (it == bindings.end())
            return;

        const auto& callbacks = this->getCallbacks<InputType, typename std::decay<Args>::type...>();
        if (const auto* callback = callbacks.find(it->first); callback != nullptr)
            (*callback)(input, std::forward<Args>(action)...);
    }

    constexpr Input::Action Input::fromGLFWAction(std::int32_t action) noexcept
    {
        switch (action)
        {
        case GLFW_PRESS:    return Input::Action::Press;
        case GLFW_RELEASE:  return Input::Action::Release;
        case GLFW_REPEAT:   return Input::Action::Repeat;
        default:            return Input::Action::Unknown;
        }
    }

    constexpr std::int32_t Input::toGLFWAction(Input::Action type) noexcept
    {
        switch (type)
        {
        case Input::Action::Unknown:    return GLFW_KEY_UNKNOWN;
        case Input::Action::Press:      return GLFW_PRESS;
        case Input::Action::Release:    return GLFW_RELEASE;
        case Input::Action::Repeat:     return GLFW_REPEAT;
        }
        return GLFW_KEY_UNKNOWN;
    }
}