module;

#include "entt/entity/registry.hpp"

export module ECS;

export import :Entity;
export import :System;

import Singleton;

export namespace ikk
{
    class ECS final : public Singleton<ECS>
    {
        friend class Singleton<ECS>;

        ECS() noexcept = default;
    public:
        ~ECS() noexcept = default;

        [[nodiscard]] Entity createEntity() noexcept;

        void destroyEntity(const Entity& entity) noexcept;
    private:
        entt::registry m_registry{};
    };

    ECS& ECS = ECS::getInstance();
}

namespace ikk
{
    Entity ECS::createEntity() noexcept
    {
        return Entity{ this->m_registry };
    }

    void ECS::destroyEntity(const Entity& entity) noexcept
    {
        this->m_registry.destroy(entity.m_entity);
    }
}