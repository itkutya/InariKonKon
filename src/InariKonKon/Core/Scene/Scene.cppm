module;

#include <type_traits>
#include <cstdint>

export module Core:Scene;

import :Window;
import :Event;

import IDCounter;
import Time;

export namespace ikk
{
    class Scene
    {
    public:
        using ID = std::uint32_t;

        enum struct State : std::uint8_t
        {
            Deleted, Suspended, Active
        };

        using enum State;

        virtual ~Scene() noexcept = default;

        virtual void onEvent(const Event& event) noexcept = 0;
        virtual void onUpdate(const Time& dt) noexcept = 0;
        virtual void onRender(const Window& window) const noexcept = 0;

        [[nodiscard]] virtual const ID& getID() const noexcept final;

        virtual void activate() noexcept final;
        virtual void suspend() noexcept final;
        virtual void destroy() noexcept final;

        [[nodiscard]] virtual const State& getState() const noexcept final;
    protected:
        explicit Scene() noexcept;

        Scene(const Scene&) noexcept = default;
        Scene(Scene&&) noexcept = default;

        Scene& operator=(const Scene&) noexcept = default;
        Scene& operator=(Scene&&) noexcept = default;
    private:
        State m_state = State::Active;
        ID m_id = 0;
    };

    template<class T>
    concept SceneType = std::is_base_of<Scene, T>::value;
}

namespace ikk
{
    const Scene::ID& Scene::getID() const noexcept
    {
        return this->m_id;
    }

    void Scene::activate() noexcept
    {
        this->m_state = State::Active;
    }

    void Scene::suspend() noexcept
    {
        this->m_state = State::Suspended;
    }

    void Scene::destroy() noexcept
    {
        this->m_state = State::Deleted;
    }

    const Scene::State& Scene::getState() const noexcept
    {
        return this->m_state;
    }

    Scene::Scene() noexcept
        : m_id(getNext<Scene::ID>())
    {
    }
}