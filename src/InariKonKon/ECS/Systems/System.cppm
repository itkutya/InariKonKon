module;

#include <concepts>

#include "entt/entt.hpp"

export module ECS:System;

import :Entity;

import EntityComponentSystem;
import Component;

export namespace ikk
{
    template<ComponentType... Components>
    class System final
    {
    public:
        System() noexcept = default;

        System(const System&) noexcept = default;
        System(System&&) noexcept = default;

        System& operator=(const System&) noexcept = default;
        System& operator=(System&&) noexcept = default;

        ~System() noexcept = default;

        template<class Func, class... Args> requires (std::invocable<Func, const Entity&, Components&..., Args&&...>)
        static void update(Func&& func, Args&&... args) noexcept;
    private:
    };
}

namespace ikk
{
    template<ComponentType... Components>
    template<class Func, class... Args> requires (std::invocable<Func, const Entity&, Components&..., Args&&...>)
    void System<Components...>::update(Func&& func, Args&&... args) noexcept
    {
        ECS.getRegistry().view<Components...>().each(
            [&func, &args...](const entt::entity entity, auto&... components) noexcept
            {
                func(Entity{entity}, components..., args...);
            });
    }
}