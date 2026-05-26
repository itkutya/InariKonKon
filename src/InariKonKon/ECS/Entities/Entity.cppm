module;

#include <cstdint>

#include "entt/entt.hpp"

export module ECS:Entity;

import EntityComponentSystem;
import Component;

export namespace ikk
{
    class [[nodiscard]] Entity final
    {
    public:
        using ID = std::uint32_t;

        [[nodiscard]] Entity() noexcept;

        Entity(const Entity& other) noexcept;
        Entity(Entity&& other) noexcept;

        Entity& operator=(const Entity& other) noexcept;
        Entity& operator=(Entity&& other) noexcept;

        ~Entity() noexcept;

        [[nodiscard]] explicit operator bool() const noexcept;

        [[nodiscard]] bool isValid() const noexcept;
        [[nodiscard]] ID getID() const noexcept;

        template<ComponentType T, class... Args>
        void addComponent(Args&&... args) noexcept;

        //TODO: Error handeling...
        template<ComponentType T>
        const T& getComponent() const noexcept;
        template<ComponentType T>
        T& getComponent() noexcept;

        template<ComponentType T>
        [[nodiscard]] bool hasComponent() const noexcept;

        template<ComponentType T>
        void removeComponent() noexcept;

        [[nodiscard]] bool operator==(const Entity& other) const noexcept;
        [[nodiscard]] bool operator!=(const Entity& other) const noexcept;
    private:
        enum struct Mode : std::uint8_t
        {
            Owner, View
        };

        entt::entity m_entity = entt::null;
        Mode m_mode = Mode::Owner;

        [[nodiscard]] explicit Entity(entt::entity entity) noexcept;

        template<auto Func, ComponentType... Components>
        friend struct System;
    };
}

namespace ikk
{
    Entity::Entity() noexcept
        : m_entity(ECS.getRegistry().create())
    {
    }

    Entity::Entity(const Entity& other) noexcept
    {
        //TODO: Test if this breaks stuff...
        auto& registry = ECS.getRegistry();
        this->m_entity = registry.create();
        for(auto&& [id, storage] : registry.storage())
            if(storage.contains(other.m_entity) == true)
                storage.push(this->m_entity, storage.value(other.m_entity));
    }

    Entity::Entity(Entity&& other) noexcept
        : m_entity(other.m_entity)
    {
        other.m_entity = entt::null;
    }

    Entity& Entity::operator=(const Entity& other) noexcept
    {
        if (this != &other)
        {
            //TODO: Test if this breaks stuff...
            auto& registry = ECS.getRegistry();
            this->m_entity = registry.create();
            this->m_mode = Mode::Owner;
            for(auto&& [id, storage] : registry.storage())
                if(storage.contains(other.m_entity) == true)
                    storage.push(this->m_entity, storage.value(other.m_entity));
        }
        return *this;
    }

    Entity& Entity::operator=(Entity&& other) noexcept
    {
        if (this != &other)
        {
            this->m_entity = other.m_entity;
            this->m_mode = Mode::Owner;
            other.m_entity = entt::null;
        }
        return *this;
    }

    Entity::~Entity() noexcept
    {
        if (this->isValid() == true && this->m_mode == Mode::Owner)
            ECS.getRegistry().destroy(this->m_entity);
    }

    Entity::operator bool() const noexcept
    {
        return this->isValid();
    }

    bool Entity::isValid() const noexcept
    {
        return ECS.getRegistry().valid(this->m_entity);
    }

    Entity::ID Entity::getID() const noexcept
    {
        if (this->isValid() == false) return 0u;
        return entt::to_integral(this->m_entity);
    }

    bool Entity::operator==(const Entity& other) const noexcept
    {
        return this->m_entity == other.m_entity;
    }

    bool Entity::operator!=(const Entity& other) const noexcept
    {
        return this->m_entity != other.m_entity;
    }

    template<ComponentType T, class... Args>
    void Entity::addComponent(Args&&... args) noexcept
    {
        if (isValid() == false) return;
        ECS.getRegistry().emplace<T>(this->m_entity, std::forward<Args>(args)...);
    }

    template<ComponentType T>
    const T& Entity::getComponent() const noexcept
    {
        return ECS.getRegistry().get<T>(this->m_entity);
    }

    template<ComponentType T>
    T& Entity::getComponent() noexcept
    {
        return ECS.getRegistry().get<T>(this->m_entity);
    }

    template<ComponentType T>
    bool Entity::hasComponent() const noexcept
    {
        return ECS.getRegistry().all_of<T>(this->m_entity);
    }

    template<ComponentType T>
    void Entity::removeComponent() noexcept
    {
        ECS.getRegistry().remove<T>(this->m_entity);
    }

    Entity::Entity(entt::entity entity) noexcept
        : m_entity(entity), m_mode(Mode::View)
    {
    }
}