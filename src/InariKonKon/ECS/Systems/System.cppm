module;

#include <type_traits>
#include <concepts>

#include "entt/entt.hpp"

export module ECS:System;

import :Entity;

import EntityComponentSystem;
import Component;

import NonConstructible;

export namespace ikk
{
    template<auto Func, ComponentType... Components>
    struct System final : public NonConstructible
    {
        template<class... Args> requires (std::invocable<decltype(Func), const Entity&, Components&..., Args&&...>)
        static void update(Args&&... args) noexcept(std::is_nothrow_invocable<decltype(Func), const Entity&, Components&..., Args&&...>::value);

        template<class... Args> requires (std::invocable<decltype(Func), Components&..., Args&&...>)
        static void update(Args&&... args) noexcept(std::is_nothrow_invocable<decltype(Func), Components&..., Args&&...>::value);
    };
}

namespace ikk
{
    template<auto Func, ComponentType... Components>
    template<class... Args> requires (std::invocable<decltype(Func), const Entity&, Components&..., Args&&...>)
    void System<Func, Components...>::update(Args&&... args) noexcept(std::is_nothrow_invocable<decltype(Func), const Entity&, Components&..., Args&&...>::value)
    {
        ECS.getRegistry().view<Components...>().each(
            [&](const entt::entity entity, Components&... components) noexcept
            {
                Func(Entity{ entity }, components..., std::forward<Args>(args)...);
            });
    }

    template<auto Func, ComponentType ... Components>
    template<class... Args> requires (std::invocable<decltype(Func), Components&..., Args&&...>)
    void System<Func, Components...>::update(Args&&... args) noexcept(std::is_nothrow_invocable<decltype(Func), Components&..., Args&&...>::value)
    {
        ECS.getRegistry().view<Components...>().each(
            [&](Components&... components) noexcept
            {
                Func(components..., std::forward<Args>(args)...);
            });
    }
}