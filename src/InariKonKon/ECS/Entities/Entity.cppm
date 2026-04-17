module;

#include <cstdint>

#include "entt/entity/registry.hpp"

export module ECS:Entity;

import :EntityComponentSystem;

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

        //TODO: Add other component stuff...
        template<class T, class... Args>
        void addComponent(Args&&... args) noexcept;

        [[nodiscard]] bool operator==(const Entity& other) const noexcept;
        [[nodiscard]] bool operator!=(const Entity& other) const noexcept;
    private:
        entt::entity m_entity = entt::null;

        [[nodiscard]] explicit Entity(entt::entity entity) noexcept;

        template<class... Components>
        friend class System;
    };
}

namespace ikk
{
    Entity::Entity() noexcept
        : m_entity(ECS.getRegistry().create())
    {
    }

    Entity::Entity(const Entity& other) noexcept
        : m_entity(ECS.getRegistry().create())
    {
        //TODO:
        //Copy other stuff...
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
            this->m_entity = ECS.getRegistry().create();
            //TODO:
            //Copy other stuff...
        }
        return *this;
    }

    Entity& Entity::operator=(Entity&& other) noexcept
    {
        if (this != &other)
        {
            this->m_entity = other.m_entity;
            other.m_entity = entt::null;
        }
        return *this;
    }

    Entity::~Entity() noexcept
    {
        if (this->isValid() == true)
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

    Entity::Entity(entt::entity entity) noexcept
        : m_entity(entity)
    {
    }

    template<class T, class... Args>
    void Entity::addComponent(Args&&... args) noexcept
    {
        if (isValid() == false) return;
        ECS.getRegistry().emplace<T>(this->m_entity, std::forward<Args>(args)...);
    }
}