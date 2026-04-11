module;

#include <utility>

#include "entt/entity/registry.hpp"

export module ECS:Entity;

export namespace ikk
{
    class [[nodiscard]] Entity final
    {
    public:
        Entity(const Entity&) noexcept = default;
        Entity(Entity&&) noexcept = default;

        Entity& operator=(const Entity&) noexcept = default;
        Entity& operator=(Entity&&) noexcept = default;

        ~Entity() noexcept = default;

        [[nodiscard]] explicit operator bool() const noexcept;

        [[nodiscard]] bool isValid() const noexcept;
        [[nodiscard]] auto getID() const noexcept;

        template<class T, class... Args>
        void addComponent(Args&&... args) noexcept;

        [[nodiscard]] bool operator==(const Entity& other) const noexcept;
    private:
        entt::entity m_entity = entt::null;
        entt::registry* m_registry = nullptr;

        [[nodiscard]] explicit Entity(entt::entity entity, entt::registry& registry) noexcept;

        friend class EntityComponentSystem;

        template<class... Components>
        friend class System;
    };
}

namespace ikk
{
    Entity::Entity(entt::entity entity, entt::registry& registry) noexcept
        : m_entity(entity), m_registry(&registry)
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
        if (this->isValid() == false) return 0u;
        return entt::to_integral(this->m_entity);
    }

    bool Entity::operator==(const Entity& other) const noexcept
    {
        return this->m_entity == other.m_entity;
    }

    template<class T, class... Args>
    void Entity::addComponent(Args&&... args) noexcept
    {
        if (isValid() == false) return;
        this->m_registry->emplace<T>(this->m_entity, std::forward<Args>(args)...);
    }
}