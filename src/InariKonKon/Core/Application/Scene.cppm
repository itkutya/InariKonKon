module;

#include <type_traits>
#include <cstdint>

export module Core:Scene;

import :Window;
import :Event;

import Time;

export namespace ikk
{
    class Scene
    {
    public:
        using ID = std::uint32_t;

        virtual ~Scene() noexcept = default;

        virtual void onEvent(const Event& event) noexcept = 0;
        virtual void onUpdate(const Time& dt) noexcept = 0;
        virtual void onRender(const Window& window) const noexcept = 0;
    protected:
        Scene() noexcept;

        Scene(const Scene&) noexcept = default;
        Scene(Scene&&) noexcept = default;

        Scene& operator=(const Scene&) noexcept = default;
        Scene& operator=(Scene&&) noexcept = default;
    private:
        ID m_id = 0;
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
}