module;

#include <type_traits>
#include <cstdint>

export module Core:Scene;

import :Window;
import :Event;

import Time;

export namespace ikk
{
    class Application;

    class Scene
    {
    public:
        using ID = std::uint32_t;

        virtual ~Scene() noexcept = default;

        virtual void onEvent(const Event& event) noexcept = 0;
        virtual void onUpdate(const Time& dt) noexcept = 0;
        virtual void onRender(const Window& window) const noexcept = 0;

        virtual const ID& getID() const noexcept final;
    protected:
        explicit Scene(Application* application) noexcept;

        Scene(const Scene&) noexcept = default;
        Scene(Scene&&) noexcept = default;

        Scene& operator=(const Scene&) noexcept = default;
        Scene& operator=(Scene&&) noexcept = default;

        virtual const Application& getApplication() const noexcept final;
        virtual Application& getApplication() noexcept final;
    private:
        ID m_id = 0;
        Application* m_application = nullptr;
    };
}

namespace ikk
{
    template<class T>
    concept SceneType = std::is_base_of<Scene, T>::value;

    const Scene::ID& Scene::getID() const noexcept
    {
        return this->m_id;
    }

    Scene::Scene(Application* application) noexcept
        : m_id([] noexcept { static ID counter = 0; return ++counter; }()), m_application(application)
    {
    }

    const Application& Scene::getApplication() const noexcept
    {
        return *this->m_application;
    }

    Application& Scene::getApplication() noexcept
    {
        return *this->m_application;
    }
}