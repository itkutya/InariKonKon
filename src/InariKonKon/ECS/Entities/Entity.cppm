module;

#include "entt/entity/registry.hpp"

//TODO: This should not be part of Core...
export module Core:Entity;

export namespace ikk
{
    class [[nodiscard]] Entity final
    {
    public:
        //TODO:
        Entity(const Entity&) noexcept = default;
        Entity(Entity&&) noexcept = default;

        //TODO:
        Entity& operator=(const Entity&) noexcept = default;
        Entity& operator=(Entity&&) noexcept = default;

        //TODO: ?
        ~Entity() noexcept = default;

        [[nodiscard]] explicit operator bool() const noexcept;

        [[nodiscard]] bool isValid() const noexcept;
        [[nodiscard]] auto getID() const noexcept;

        template<class T>
        void addComponent(T&& component) noexcept;
    private:
        entt::entity m_entity = entt::null;
        entt::registry* m_registry = nullptr;

        [[nodiscard]] explicit Entity(entt::registry& registry) noexcept;

        friend class Scene;
    };
}

namespace ikk
{
    Entity::Entity(entt::registry& registry) noexcept
        : m_entity(registry.create()), m_registry(&registry)
    {
    }

    Entity::operator bool() const noexcept
    {
        return this->isValid();
    }

    bool Entity::isValid() const noexcept
    {
        return this->m_registry != nullptr && this->m_registry->valid(this->m_entity);
    }

    auto Entity::getID() const noexcept
    {
        return entt::to_integral(this->m_entity);
    }

    template<class T>
    void Entity::addComponent(T&& component) noexcept
    {
        if (isValid() == false) return;
        this->m_registry->emplace<T>(this->m_entity, std::forward<T>(component));
    }
}