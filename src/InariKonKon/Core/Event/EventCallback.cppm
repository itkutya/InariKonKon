module;

#include <functional>
#include <utility>
#include <vector>

export module Core:EventCallback;

import NonConstructible;

export namespace ikk
{
    class Event;

    template<class T>
    class EventCallback : public NonConstructible
    {
    public:
        using CallbackFunc = std::function<void(const T&)>;

        static void add(CallbackFunc&& callable) noexcept;

        //TODO: Add remove func somehow...
    private:
        inline static std::vector<CallbackFunc> s_eventCallabacks;

        [[nodiscard]] static const std::vector<CallbackFunc>& getCallbacks() noexcept;

        friend Event;
    };
}

namespace ikk
{
    template<class T>
    void EventCallback<T>::add(CallbackFunc&& callable) noexcept
    {
        s_eventCallabacks.emplace_back(std::forward<decltype(callable)>(callable));
    }

    template<class T>
    const std::vector<typename EventCallback<T>::CallbackFunc>& EventCallback<T>::getCallbacks() noexcept
    {
        return s_eventCallabacks;
    }
}