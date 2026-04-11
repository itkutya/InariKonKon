module;

#include "entt/entity/registry.hpp"

export module ECS:EntityComponentSystem;

import Singleton;

import :Entity;

export namespace ikk
{
    class EntityComponentSystem final : public Singleton<EntityComponentSystem>
    {
        friend class Singleton<EntityComponentSystem>;

        EntityComponentSystem() noexcept = default;
    public:
        ~EntityComponentSystem() noexcept = default;

        [[nodiscard]] Entity createEntity() noexcept;

        void destroyEntity(const Entity& entity) noexcept;

        void clear() noexcept;
    private:
        entt::registry m_registry{};

        template<class... Args>
        friend class System;
    };

    EntityComponentSystem& ECS = EntityComponentSystem::getInstance();
}

namespace ikk
{
    Entity EntityComponentSystem::createEntity() noexcept
    {
        return Entity{ this->m_registry };
    }

    void EntityComponentSystem::destroyEntity(const Entity& entity) noexcept
    {
        this->m_registry.destroy(entity.m_entity);
    }

    void EntityComponentSystem::clear() noexcept
    {
        this->m_registry.clear();
    }
}