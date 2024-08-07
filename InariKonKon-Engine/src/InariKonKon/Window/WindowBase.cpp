#include "InariKonKon/Window/WindowBase.hpp"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#include "InariKonKon/Utilities/Log.hpp"

namespace ikk
{
	WindowBase::WindowBase(const std::u8string& title, const WindowBase::Settings settings) noexcept : m_title(title), m_settings(settings), m_window(this->create(title))
	{
		if (this->m_window == nullptr)
			Log::push("Could not initialize window!", Log::Level::Fatal);

		this->setActive();

		this->setFPSLimit(settings.fpslimit);
		this->setVSync(settings.vsync);

		this->initWindowEvents();
	}

	const bool WindowBase::shouldClose() const noexcept
	{
		return glfwWindowShouldClose(this->m_window);
	}

	void WindowBase::setActive(const bool active) const noexcept
	{
		if (active)
			glfwMakeContextCurrent(this->m_window);
		else
			glfwMakeContextCurrent(nullptr);
	}

	void WindowBase::handleEvents() const noexcept
	{
		this->setActive();
		glfwPollEvents();
	}

	void WindowBase::display() const noexcept
	{
		this->setActive();
		glfwSwapBuffers(this->m_window);
	}

	const std::uint32_t& WindowBase::getFPSLimit() const noexcept
	{
		return this->m_settings.fpslimit;
	}

	void WindowBase::setFPSLimit(const std::uint32_t limit) noexcept
	{
		this->m_settings.fpslimit = limit;
		this->m_settings.vsync = (limit != 0) ? false : this->m_settings.vsync;
		glfwSwapInterval(this->m_settings.vsync);
	}

	const bool& WindowBase::isVSyncEnabled() const noexcept
	{
		return this->m_settings.vsync;
	}

	void WindowBase::setVSync(const bool vsync) noexcept
	{
		this->m_settings.fpslimit = (vsync == true) ? 0 : this->m_settings.fpslimit;
		this->m_settings.vsync = vsync;
		glfwSwapInterval(this->m_settings.vsync);
	}

	const std::u8string& WindowBase::getTitle() const noexcept
	{
		return this->m_title;
	}

	void WindowBase::setTitle(const std::u8string& title) noexcept
	{
		this->m_title = title;
		glfwSetWindowTitle(this->m_window, reinterpret_cast<const char*>(title.c_str()));
	}

	const float WindowBase::getAspectRatio() const noexcept
	{
		return static_cast<float>(this->m_settings.size.x) / static_cast<float>(this->m_settings.size.y);
	}

	const glm::uvec2& WindowBase::getSize() const noexcept
	{
		return this->m_settings.size;
	}

	void WindowBase::setSize(const glm::uvec2 size) noexcept
	{
		this->m_settings.size = size;
		glfwSetWindowSize(this->m_window, size.x, size.y);
	}

	const EventManager& WindowBase::getEventManager() const noexcept
	{
		return this->m_eventManager;
	}

	EventManager& WindowBase::getEventManager() noexcept
	{
		return this->m_eventManager;
	}

	GLFWwindow* const WindowBase::create(const std::u8string& title) const noexcept
	{
		return glfwCreateWindow(500, 500, reinterpret_cast<const char*>(title.c_str()), NULL, NULL);
	}

	void WindowBase::initWindowEvents() noexcept
	{
		glfwSetWindowUserPointer(this->m_window, reinterpret_cast<void*>(this));

		static auto errorCallback = [](int id, const char* description) noexcept
			{
				Log::push(std::format("ERROR ({}): {}", id, description).c_str(), Log::Level::Error);
			};
		glfwSetErrorCallback(errorCallback);

		static auto window_close_callback = [](GLFWwindow* window) noexcept
			{
				WindowBase* handler = reinterpret_cast<WindowBase*>(glfwGetWindowUserPointer(window));
				handler->getEventManager().push(Event{ Event::WindowClosed{} });
			};
		glfwSetWindowCloseCallback(this->m_window, window_close_callback);

		static auto framebuffer_size_callback = [](GLFWwindow* window, int width, int height) noexcept
			{
				WindowBase* handler = reinterpret_cast<WindowBase*>(glfwGetWindowUserPointer(window));
				handler->getEventManager().push(Event{ Event::FrameBufferResized{ static_cast<std::uint32_t>(width), static_cast<std::uint32_t>(height) } });
			};
		glfwSetFramebufferSizeCallback(this->m_window, framebuffer_size_callback);

		static auto monitor_callback = [](GLFWmonitor* monitor, int event) noexcept
			{
				if (event == GLFW_CONNECTED)
				{
					//handler->getEventManager().push({});
				}
				else if (event == GLFW_DISCONNECTED)
				{
					//handler->getEventManager().push({});
				}
			};
		glfwSetMonitorCallback(monitor_callback);

		static auto key_callback = [](GLFWwindow* window, int key, int scancode, int action, int mods) noexcept
			{
				WindowBase* handler = reinterpret_cast<WindowBase*>(glfwGetWindowUserPointer(window));
				handler->setActive();
				//handler->getEventManager().push({});
			};
		glfwSetKeyCallback(this->m_window, key_callback);
	}
}