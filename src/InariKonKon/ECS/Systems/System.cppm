module;

#include <utility>

#include "entt/entity/registry.hpp"

export module ECS:System;

import :EntityComponentSystem;
import :Entity;

export namespace ikk
{
    //TODO: Concepts...
    template<class... Components>
    class System final
    {
    public:
        System() noexcept = default;

        System(const System&) noexcept = default;
        System(System&&) noexcept = default;

        System& operator=(const System&) noexcept = default;
        System& operator=(System&&) noexcept = default;

        ~System() noexcept = default;

        template<class Func, class... Args>
        void update(Func&& func, Args&&... args) const noexcept;
    private:
    };
}

namespace ikk
{
    template<class... Components>
    template<class Func, class... Args>
    void System<Components...>::update(Func&& func, Args&&... args) const noexcept
    {
        auto view = ECS.m_registry.view<Components...>();
        view.each([&func, &args...](const auto& entity, auto&... components)
        {
            std::forward<Func>(func)(Entity{entity, ECS.m_registry}, components..., std::forward<Args>(args)...);
        });
    }
}