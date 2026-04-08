module;

#include <cstdint>

export module ECS:Entity;

export namespace ikk
{
    class [[nodiscard]] Entity final
    {
    public:
        using ID = std::uint32_t;

        Entity(const Entity&) noexcept = default;
        Entity(Entity&&) noexcept = default;

        Entity& operator=(const Entity&) noexcept = default;
        Entity& operator=(Entity&&) noexcept = default;

        ~Entity() noexcept = default;

        [[nodiscard]] const ID& getID() const noexcept;
    protected:
        [[nodiscard]] explicit Entity() noexcept;
    private:
        ID m_id = 0;

        inline static ID s_counter = 0;

        friend class ECS;
    };
}

namespace ikk
{
    const Entity::ID& Entity::getID() const noexcept
    {
        return this->m_id;
    }

    Entity::Entity() noexcept
        : m_id(++s_counter)
    {
    }
}