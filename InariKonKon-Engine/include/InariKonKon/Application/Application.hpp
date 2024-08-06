#pragma once

#include <format>

#include "InariKonKon/Utilities/Singleton.hpp"
#include "InariKonKon/Utilities/Clock.hpp"
#include "InariKonKon/Window/Window.hpp"

namespace ikk
{
	class IKK_API Application final : public Singleton<Application>
	{
		friend class Singleton<Application>;
		Application() noexcept = default;
	public:
		~Application() noexcept = default;

		void run() noexcept;
	private:
		Window m_window{ WINDOW_TITLE };
		Clock m_clock{};

		void handleEvents() noexcept;
		void update(const Time& dt) noexcept;
		void display() const noexcept;
		void sleep(const std::uint32_t amountSeconds) const noexcept;
	};
}