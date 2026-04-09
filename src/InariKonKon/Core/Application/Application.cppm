module;

#include <string_view>
#include <cstdint>
#include <memory>
#include <vector>

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

export module Core:Application;

import :EventManager;
import :Renderer;
import :Window;
import :Scene;

import Time;
import Clock;

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

        template<SceneType T>
        void add(T&& scene) noexcept;

        //TODO:
        //void remove(ID) noexcept;
    private:
        Window m_window;
        Clock m_deltaTime;

        std::vector<std::shared_ptr<Scene>> m_scenes;

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
            this->processEvents();
            this->update();
            this->render();
        }
    }

    template<SceneType T>
    void Application::add(T&& scene) noexcept
    {
        this->m_scenes.emplace_back(std::make_shared<T>(std::forward<T>(scene)));
    }

    void Application::processEvents() const noexcept
    {
        this->m_window.pollEvents();

        while (eventManager.isEmpty() == false)
        {
            const Event& event = eventManager.top();
            for (const std::shared_ptr<Scene>& layer : this->m_scenes)
                layer->onEvent(event);
            eventManager.pop();
        }
    }

    void Application::update() noexcept
    {
        const Time dt = this->m_deltaTime.restart();
        for (const std::shared_ptr<Scene>& layer : this->m_scenes)
            layer->onUpdate(dt);
    }

    void Application::render() const noexcept
    {
        for (const std::shared_ptr<Scene>& layer : this->m_scenes)
            layer->onRender(this->m_window);
        this->m_window.render();
    }
}