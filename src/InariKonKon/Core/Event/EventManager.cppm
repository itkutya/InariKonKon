module;

#include <utility>
#include <stack>

export module Core:EventManager;

import :Event;

import Singleton;

export namespace ikk
{
    class EventManager final : public Singleton<EventManager>
    {
        friend class Singleton<EventManager>;

        EventManager() noexcept = default;
    public:
        ~EventManager() noexcept = default;

        void emplace(Event&& event) noexcept;
        void pop() noexcept;

        [[nodiscard]] const Event& top() const noexcept;

        [[nodiscard]] bool isEmpty() const noexcept;
    private:
        std::stack<Event> m_events;
    };
}

namespace ikk
{
    void EventManager::emplace(Event&& event) noexcept
    {
        this->m_events.emplace(std::forward<Event>(event));
    }

    void EventManager::pop() noexcept
    {
        if (this->m_events.empty() == false)
            this->m_events.pop();
    }

    const Event& EventManager::top() const noexcept
    {
        return this->m_events.top();
    }

    bool EventManager::isEmpty() const noexcept
    {
        return this->m_events.empty();
    }
}