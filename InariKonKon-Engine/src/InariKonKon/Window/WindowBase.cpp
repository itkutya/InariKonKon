#include "InariKonKon/Window/WindowBase.hpp"

#include <format>

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#include "InariKonKon/Utilities/Log.hpp"
#include "InariKonKon/Graphics/OpenGL.hpp"

namespace ikk
{
	WindowBase::WindowBase(const std::u8string& title, const WindowBase::Settings settings) noexcept
		: m_title(title), m_settings(settings), m_window(this->create(title, settings))
	{
		if (this->m_window == nullptr)
			Log::push("Could not initialize window!", Log::Level::Fatal);

		glfwMakeContextCurrent(this->m_window);

		if (gladLoadGLContext(Context::getInstance().getContext(), glfwGetProcAddress) == false)
			Log::push("Could not initialize OpenGL!", Log::Level::Fatal);

		gl->Viewport(0, 0, settings.size.x, settings.size.y);

		this->setFPSLimit(settings.fpslimit);
		this->setVSync(settings.vsync);

		this->initWindowEvents();
	}

	WindowBase::~WindowBase() noexcept
	{
		if (this->m_window)
			glfwDestroyWindow(this->m_window);
	}

	const bool WindowBase::shouldClose() const noexcept
	{
		return glfwWindowShouldClose(this->m_window);
	}

	void WindowBase::handleEvents() const noexcept
	{
		glfwPollEvents();
	}

	void WindowBase::display() const noexcept
	{
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

	GLFWwindow* const WindowBase::create(const std::u8string& title, const WindowBase::Settings settings) const noexcept
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		return glfwCreateWindow(settings.size.x, settings.size.y, reinterpret_cast<const char*>(title.c_str()), NULL, NULL);
	}

	void WindowBase::initWindowEvents() noexcept
	{
		glfwSetWindowUserPointer(this->m_window, reinterpret_cast<void*>(this));

		static auto errorCallback = [](int id, const char* description) noexcept
			{
				Log::push(std::format("(id: {}): {}", id, description).c_str(), Log::Level::Error);
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
				gl->Viewport(0, 0, width, height);
			};
		glfwSetFramebufferSizeCallback(this->m_window, framebuffer_size_callback);
	}
}