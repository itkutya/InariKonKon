module;

#include "entt/entity/registry.hpp"

export module ECS:EntityComponentSystem;

import Singleton;

export namespace ikk
{
    class EntityComponentSystem final : public Singleton<EntityComponentSystem>
    {
        friend class Singleton<EntityComponentSystem>;

        EntityComponentSystem() noexcept = default;
    public:
        ~EntityComponentSystem() noexcept = default;

        [[nodiscard]] const auto& getRegistry() const noexcept;
        [[nodiscard]] auto& getRegistry() noexcept;
    private:
        entt::registry m_registry{};
    };

    EntityComponentSystem& ECS = EntityComponentSystem::getInstance();
}

namespace ikk
{
    const auto& EntityComponentSystem::getRegistry() const noexcept
    {
        return this->m_registry;
    }

    auto& EntityComponentSystem::getRegistry() noexcept
    {
        return this->m_registry;
    }
}