module;

#include <type_traits>
#include <cstddef>
#include <cstdint>

export module Core:Scene;

import :Window;
import :Event;

import StableIndexVector;
import Time;
import ECS;

export namespace ikk
{
    //TODO: Make every class that has to be inherited from name the same like IScene, or something like that...
    class Scene
    {
    public:
        using ID = std::uint32_t;

        virtual ~Scene() noexcept = default;

        virtual void onEvent(const Event& event) noexcept = 0;
        virtual void onUpdate(const Time& dt) noexcept = 0;
        virtual void onRender(const Window& window) const noexcept = 0;

        [[nodiscard]] virtual EntityHandle createEntity() noexcept final;

        virtual void destroyEntity(const EntityHandle& entity) noexcept final;
    protected:
        Scene() noexcept;

        Scene(const Scene&) noexcept = default;
        Scene(Scene&&) noexcept = default;

        Scene& operator=(const Scene&) noexcept = default;
        Scene& operator=(Scene&&) noexcept = default;
    private:
        ID m_id;
        StableIndexVector<Entity> m_entities;
    };
}

namespace ikk
{
    template<class T>
    concept SceneType = std::is_base_of<Scene, T>::value;

    Scene::Scene() noexcept
        : m_id([] noexcept { static ID counter = 0; return ++counter; }())
    {
    }

    EntityHandle Scene::createEntity() noexcept
    {
        const std::size_t id = this->m_entities.emplace();
        return EntityHandle{ id, this->m_entities.getValidityID(id), &this->m_entities };
    }

    void Scene::destroyEntity(const EntityHandle& entity) noexcept
    {
        if (const auto& ent = entity.get(); ent.has_value())
            this->m_entities.erase(entity.getIndex());
    }
}