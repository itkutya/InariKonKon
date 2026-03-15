module;

#include <string_view>
#include <cstdint>
#include <memory>
#include <vector>

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

export module Core:Application;

import :EventManager;
import :Window;
import :Layer;

import Time;
import Clock;

export namespace ikk
{
    class [[nodiscard]] Application final
    {
    public:
        [[nodiscard]] Application(std::u8string_view title, std::uint32_t width, std::uint32_t height) noexcept;

        Application(const Application&) noexcept = default;
        Application(Application&&) noexcept = default;

        Application& operator=(const Application&) noexcept = default;
        Application& operator=(Application&&) noexcept = default;

        ~Application() noexcept;

        void run() noexcept;

        template<LayerType T>
        void attach(T&& layer) noexcept;

        //void detach() noexcept;
    private:
        Window m_window;
        Clock m_deltaTime;

        std::vector<std::shared_ptr<Layer>> m_layers;

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

    Application::~Application() noexcept
    {
        glfwTerminate();
    }

    void Application::run() noexcept
    {
        while (!this->m_window.shouldClose())
        {
            this->processEvents();
            this->update();
            this->render();
        }
    }

    template<LayerType T>
    void Application::attach(T&& layer) noexcept
    {
        this->m_layers.emplace_back(std::make_shared<T>(std::forward<T>(layer)));
    }

    void Application::processEvents() const noexcept
    {
        this->m_window.pollEvents();

        EventManager& eventStack = EventManager::getInstance();
        while (eventStack.isEmpty() == false)
        {
            const Event& event = eventStack.top();
            for (const std::shared_ptr<Layer>& layer : this->m_layers)
                layer->onEvent(event);
            eventStack.pop();
        }
    }

    void Application::update() noexcept
    {
        const Time dt = this->m_deltaTime.restart();
        for (const std::shared_ptr<Layer>& layer : this->m_layers)
            layer->onUpdate(dt);
    }

    void Application::render() const noexcept
    {
        for (const std::shared_ptr<Layer>& layer : this->m_layers)
            layer->onRender(this->m_window);
    }
}
