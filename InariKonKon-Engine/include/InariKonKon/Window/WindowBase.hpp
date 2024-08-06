#pragma once

#include <string>

#include "InariKonKon/Utilities/Macros.hpp"
#include "glm/vec2.hpp"

struct GLFWwindow;

namespace ikk
{
	class IKK_API WindowBase
	{
	public:
		struct Settings final
		{
			glm::uvec2 size = { 0, 0 };
			std::uint32_t fpslimit = 0;
			bool vsync = true;
			bool fullscreen = false;
		};

		WindowBase(const std::u8string& title, const WindowBase::Settings settings = {}) noexcept;

		WindowBase(const WindowBase&) noexcept = default;
		WindowBase(WindowBase&&) noexcept = default;

		WindowBase& operator=(const WindowBase&) noexcept = default;
		WindowBase& operator=(WindowBase&&) noexcept = default;

		virtual ~WindowBase() noexcept = default;

		[[nodiscard]] virtual const bool shouldClose() const noexcept final;

		virtual void setActive(const bool active = true) const noexcept final;

		virtual void handleEvents() const noexcept final;
		virtual void display() const noexcept final;

		[[nodiscard]] virtual const std::uint32_t& getFPSLimit() const noexcept final;
		virtual void setFPSLimit(const std::uint32_t limit) noexcept final;

		[[nodiscard]] virtual const bool& isVSyncEnabled() const noexcept final;
		virtual void setVSync(const bool vsync) noexcept final;

		[[nodiscard]] virtual const std::u8string& getTitle() const noexcept final;
		virtual void setTitle(const std::u8string& title) noexcept final;

		[[nodiscard]] virtual const float getAspectRatio() const noexcept final;
		//[[nodiscard]] const vec2u& getSize() const noexcept;
		//void setSize(const vec2u size) noexcept;
	private:
		std::u8string m_title;
		WindowBase::Settings m_settings;
		GLFWwindow* m_window = nullptr;
		/*
		friend class Application;
		[[nodiscard]] const std::queue<Event>& getEventQueue() const noexcept;
		[[nodiscard]] std::queue<Event>& getEventQueue() noexcept;
		*/

		GLFWwindow* const create(const std::u8string& title) const noexcept;
		void initWindowEvents() noexcept;
	};
}