module;

#include <string_view>
#include <functional>
#include <cstdint>
#include <vector>
#include <string>

export module Core:Input;

import Singleton;

export namespace ikk
{
    class Input final : public Singleton<Input>
    {
        friend class Singleton<Input>;

        Input() noexcept = default;
    public:
        using Callback = std::function<void()>;

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

        //TODO:
        template<class T>
        void bind(std::string&& name, T input, Action action = Action::Press) noexcept;

        void onAction(const std::string& name, Callback&& func) noexcept;
    private:
        std::vector<std::string> m_actions;
        std::vector<Callback> m_callbacks;

        template<class T>
        void handleEvent(T input, Action action) noexcept;

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

    template <class T>
    void Input::bind(std::string&& name, T input, Action action) noexcept
    {
        this->m_actions.emplace_back(std::move(name));
    }

    void Input::onAction(const std::string& name, Callback&& func) noexcept
    {
        this->m_callbacks.emplace_back(std::move(func));
    }

    template <class T>
    void Input::handleEvent(T input, Action action) noexcept
    {
    }
}