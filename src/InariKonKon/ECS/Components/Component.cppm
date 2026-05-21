module;

#include <type_traits>

export module Component;

export namespace ikk
{
    class Component
    {
    public:
        Component() noexcept = default;

        Component(const Component&) noexcept = default;
        Component(Component&&) noexcept = default;

        Component& operator=(const Component&) noexcept = default;
        Component& operator=(Component&&) noexcept = default;

        virtual ~Component() noexcept = default;

        [[nodiscard]] virtual bool isEnabled() const noexcept final;
        [[nodiscard]] virtual bool isDisabled() const noexcept final;

        virtual void disable() noexcept final;
        virtual void enable() noexcept final;
    private:
        [[no_unique_address]] bool m_enabled = true;
    };

    template<typename T>
    concept ComponentType = std::is_base_of<Component, T>::value;
}

namespace ikk
{
    bool Component::isEnabled() const noexcept
    {
        return this->m_enabled;
    }

    bool Component::isDisabled() const noexcept
    {
        return !this->m_enabled;
    }

    void Component::disable() noexcept
    {
        this->m_enabled = false;
    }

    void Component::enable() noexcept
    {
        this->m_enabled = true;
    }
}