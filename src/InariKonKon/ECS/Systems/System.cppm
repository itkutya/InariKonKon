module;

#include <utility>

#include "entt/entity/registry.hpp"

export module ECS:System;

import :EntityComponentSystem;
import :Entity;

export namespace ikk
{
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
        static void update(Func&& func, Args&&... args) noexcept;
    private:
    };
}

namespace ikk
{
    template<class... Components>
    template<class Func, class... Args>
    void System<Components...>::update(Func&& func, Args&&... args) noexcept
    {
        auto view = ECS.getRegistry().view<Components...>();
        view.each([&func, &args...](const auto& entity, auto&... components) noexcept
        {
            Entity ent{ entity };
            std::forward<Func>(func)(ent, components..., std::forward<Args>(args)...);
            ent.m_entity = entt::null;
        });
    }
}