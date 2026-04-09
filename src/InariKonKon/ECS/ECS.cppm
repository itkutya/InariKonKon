module;

#include "entt/entity/registry.hpp"

export module ECS;

export import :Entity;

import Singleton;

export namespace ikk
{
    class ECS final : public Singleton<ECS>
    {
        friend class Singleton<ECS>;

        ECS() noexcept = default;
    public:
        [[nodiscard]] virtual Entity createEntity() noexcept final;

        virtual void destroyEntity(const Entity& entity) noexcept final;
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