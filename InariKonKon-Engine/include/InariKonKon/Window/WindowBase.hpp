#pragma once

#include <string>

#include "glm/vec2.hpp"

#include "InariKonKon/Window/EventManager.hpp"
#include "InariKonKon/Utilities/Macros.hpp"

struct GLFWwindow;

namespace ikk
{
	class IKK_API WindowBase
	{
	public:
		struct Settings final
		{
			glm::uvec2 size = { 1024, 800 };
			std::uint32_t fpslimit = 0;
			bool vsync = true;
			bool fullscreen = false;
		};

		WindowBase(const std::u8string& title, const WindowBase::Settings settings = {}) noexcept;

		WindowBase(const WindowBase&) noexcept = default;
		WindowBase(WindowBase&&) noexcept = default;

		WindowBase& operator=(const WindowBase&) noexcept = default;
		WindowBase& operator=(WindowBase&&) noexcept = default;

		virtual ~WindowBase() noexcept;

		[[nodiscard]] virtual const bool shouldClose() const noexcept final;

		virtual void handleEvents() const noexcept final;
		virtual void display() const noexcept final;

		[[nodiscard]] virtual const std::uint32_t& getFPSLimit() const noexcept final;
		virtual void setFPSLimit(const std::uint32_t limit) noexcept final;

		[[nodiscard]] virtual const bool& isVSyncEnabled() const noexcept final;
		virtual void setVSync(const bool vsync) noexcept final;

		[[nodiscard]] virtual const std::u8string& getTitle() const noexcept final;
		virtual void setTitle(const std::u8string& title) noexcept final;

		[[nodiscard]] virtual const float getAspectRatio() const noexcept final;
		[[nodiscard]] const glm::uvec2& getSize() const noexcept;
		void setSize(const glm::uvec2 size) noexcept;
	protected:
		friend class Application;
		[[nodiscard]] virtual const EventManager& getEventManager() const noexcept;
		[[nodiscard]] virtual EventManager& getEventManager() noexcept;
	private:
		std::u8string m_title;
		WindowBase::Settings m_settings;
		GLFWwindow* m_window = nullptr;

		EventManager m_eventManager{};

		GLFWwindow* const create(const std::u8string& title, const WindowBase::Settings settings) const noexcept;
		void initWindowEvents() noexcept;
	};
}