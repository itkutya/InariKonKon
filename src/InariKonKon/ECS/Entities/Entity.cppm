module;

#include <cstdint>

export module ECS:Entity;

export namespace ikk
{
    class [[nodiscard]] Entity final
    {
    public:
        using ID = std::uint32_t;

        //TODO: Hide this somehow...
        [[nodiscard]] Entity() noexcept;

        Entity(const Entity&) noexcept = default;
        Entity(Entity&&) noexcept = default;

        Entity& operator=(const Entity&) noexcept = default;
        Entity& operator=(Entity&&) noexcept = default;

        ~Entity() noexcept = default;

        [[nodiscard]] const ID& getID() const noexcept;
    private:
        ID m_id = 0;
    };
}

namespace ikk
{
    const Entity::ID& Entity::getID() const noexcept
    {
        return this->m_id;
    }

    Entity::Entity() noexcept
        : m_id([] noexcept { static ID counter = 0; return ++counter; }())
    {
    }
}