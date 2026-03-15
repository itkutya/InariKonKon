module;

#include <ranges>
#include <vector>

export module Core:EventListener;

export namespace ikk
{
    class Event;

    template<class T>
    class EventListener
    {
    public:
        virtual ~EventListener() noexcept;

        virtual void onEvent(const T& event) noexcept = 0;

        virtual void add() noexcept final;
        virtual void remove() noexcept final;
    protected:
        explicit EventListener(bool autoAdd = true) noexcept;

        EventListener(const EventListener& other) noexcept;
        EventListener(EventListener&& other) noexcept;

        EventListener& operator=(const EventListener& other) noexcept;
        EventListener& operator=(EventListener&& other) noexcept;
    private:
        inline static std::vector<EventListener<T>*> s_listeners;

        [[nodiscard]] static const std::vector<EventListener<T>*>& getListeners() noexcept;

        friend Event;
    };
}

namespace ikk
{
    template<class T>
    EventListener<T>::~EventListener() noexcept
    {
        this->remove();
    }

    template<class T>
    void EventListener<T>::add() noexcept
    {
        if (const auto found = std::ranges::find(s_listeners, this); found != s_listeners.end())
            return;

        s_listeners.emplace_back(this);
    }

    template<class T>
    void EventListener<T>::remove() noexcept
    {
        std::erase(s_listeners, this);
    }

    template<class T>
    EventListener<T>::EventListener(bool autoAdd) noexcept
    {
        if (autoAdd)
            this->add();
    }

    template<class T>
    EventListener<T>::EventListener(const EventListener& other) noexcept
    {
        if (this != &other)
            this->add();
    }

    template<class T>
    EventListener<T>::EventListener(EventListener&& other) noexcept
    {
        if (this != &other)
        {
            this->add();
            other.remove();
        }
    }

    template<class T>
    EventListener<T>& EventListener<T>::operator=(const EventListener& other) noexcept
    {
        if (this != &other)
            this->add();
        return *this;
    }

    template<class T>
    EventListener<T>& EventListener<T>::operator=(EventListener&& other) noexcept
    {
        if (this != &other)
        {
            this->add();
            other.remove();
        }
        return *this;
    }

    template<class T>
    const std::vector<EventListener<T>*>& EventListener<T>::getListeners() noexcept
    {
        return s_listeners;
    }
}