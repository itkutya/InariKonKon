#include "InariKonKon/Window/WindowBase.hpp"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/gl.h"

namespace ikk
{
	WindowBase::WindowBase(const std::u8string& title) noexcept : m_title(title), m_window(this->create(title))
	{
	}

	const bool WindowBase::shouldClose() const noexcept
	{
		return glfwWindowShouldClose(this->m_window);
	}

	void WindowBase::setActive(const bool active) const noexcept
	{
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
		return 0;
	}

	void WindowBase::setFPSLimit(const std::uint32_t limit) noexcept
	{
	}

	const bool& WindowBase::isVSyncEnabled() const noexcept
	{
		return 0;
	}

	void WindowBase::setVSync(const bool vsync) noexcept
	{
	}

	const std::u8string& WindowBase::getTitle() const noexcept
	{
		return this->m_title;
	}

	void WindowBase::setTitle(const std::u8string& title) noexcept
	{
	}

	const float WindowBase::getAspectRatio() const noexcept
	{
		return 0.0f;
	}

	GLFWwindow* const WindowBase::create(const std::u8string& title) const noexcept
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		return glfwCreateWindow(500, 500, reinterpret_cast<const char*>(title.c_str()), NULL, NULL);
	}
}