#pragma once

#include "InariKonKon/Utilities/Clock.hpp"
#include "InariKonKon/Window/Window.hpp"

namespace ikk
{
	class IKK_API Application final
	{
		struct Engine
		{
			~Engine() noexcept;

			static const Engine init() noexcept;
		};
	public:
		Application() noexcept;

		Application(const Application&) noexcept = default;
		Application(Application&&) noexcept = default;

		Application& operator=(const Application&) noexcept = default;
		Application& operator=(Application&&) noexcept = default;

		~Application() noexcept = default;

		void run() noexcept;
	private:
		Engine m_engine;
		Window m_window;

		Clock m_clock{};

		void handleEvents() noexcept;
		void update(const Time& dt) noexcept;
		void display() const noexcept;
		void sleep(const std::uint32_t amountSeconds) const noexcept;
	};
}