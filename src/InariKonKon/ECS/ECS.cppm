module;

#include <cstddef>

export module ECS;

export import :EntityHandle;
export import :Entity;

import StableIndexVector;
import Singleton;

export namespace ikk
{
    class ECS final : public Singleton<ECS>
    {
        friend class Singleton<ECS>;

        ECS() noexcept = default;
    public:
        //TODO: This should be part of scene class, since scenes should own all entities created within...
        [[nodiscard]] EntityHandle createEntity() noexcept;

        void destroyEntity(const EntityHandle& entity) noexcept;
    private:
        StableIndexVector<Entity> m_entities;
    };

    ECS& ECS = ECS::getInstance();
}

namespace ikk
{
    EntityHandle ECS::createEntity() noexcept
    {
        const std::size_t id = this->m_entities.insert(Entity{});
        return EntityHandle{ id, this->m_entities.getValidityID(id), &this->m_entities };
    }

    void ECS::destroyEntity(const EntityHandle& entity) noexcept
    {
        if (const auto& ent = entity.get(); ent.has_value())
            this->m_entities.erase(entity.m_index);
    }
}