module;

#include <string_view>
#include <cstdint>
#include <memory>

export module Core:Application;

import :SceneManager;
import :EventManager;
import :Renderer;
import :Window;

//TODO: Something with these...
import TransformComponent;
import UIComponent;
import UISystem;
import ECS;

import Print;
import Clock;
import Time;

export namespace ikk
{
    class [[nodiscard]] Application final
    {
    public:
        //TODO: Application should have a different constructor then window...
        [[nodiscard]] Application(std::u8string_view title, std::uint32_t width, std::uint32_t height) noexcept;

        Application(const Application&) noexcept = default;
        Application(Application&&) noexcept = default;

        Application& operator=(const Application&) noexcept = default;
        Application& operator=(Application&&) noexcept = default;

        ~Application() noexcept = default;

        void run() noexcept;

        template<SceneType T, class... Args>
        void addScene(Args... args) noexcept;
    private:
        Window m_window;
        Clock m_deltaTime;
        SceneManager m_sceneManager;

        void processEvents() const noexcept;
        void update() noexcept;
        void render() const noexcept;
    };
}

namespace ikk
{
    Application::Application(std::u8string_view title, std::uint32_t width, std::uint32_t height) noexcept
        : m_window(title, width, height)
    {
        this->m_deltaTime.restart();
    }

    void Application::run() noexcept
    {
        while (this->m_window.shouldClose() == false && this->m_window.getRenderer()->isValid() == true)
        {
            this->m_sceneManager.removeUnnecessaryScenes();
            this->processEvents();
            this->update();
            this->render();
        }
    }

    template<SceneType T, class... Args>
    void Application::addScene(Args... args) noexcept
    {
        this->m_sceneManager.emplace<T>(std::forward<Args>(args)...);
    }

    void Application::processEvents() const noexcept
    {
        this->m_window.pollEvents();
        while (eventManager.isEmpty() == false)
        {
            const Event& event = eventManager.top();
            for (const std::shared_ptr<Scene>& scene : this->m_sceneManager.getActiveScenes())
                scene->onEvent(event);
            eventManager.pop();
        }
    }

    void Application::update() noexcept
    {
        const Time dt = this->m_deltaTime.restart();
        for (const std::shared_ptr<Scene>& scene : this->m_sceneManager.getActiveScenes())
            scene->onUpdate(dt);

        //TODO:
        UISystem::update([](const Entity& entity, const Transform2D& transform, const UI& uiComponent) noexcept
            {
                if (transform.isDisabled() == true || uiComponent.isDisabled() == true) return;

                Print("Mouse pos:\n\tx: {}\n\ty: {}", Mouse::getPosition().x(), Mouse::getPosition().y());
                Print("Mouse wheel factors:\n\tx: {}\n\ty: {}", Mouse::getWheelPosition(Mouse::Wheel::Horizontal), Mouse::getWheelPosition(Mouse::Wheel::Vertical));
            });
    }

    void Application::render() const noexcept
    {
        for (const std::shared_ptr<Scene>& scene : this->m_sceneManager.getActiveScenes())
            scene->onRender(this->m_window);
        this->m_window.render();
    }
}