#include "InariKonKon/Application/Application.hpp"

#include <thread>
#include <print>

namespace ikk
{
	void Application::run() noexcept
	{
		this->m_clock.restart();
		while (this->m_window.shouldClose() == false)
		{
			const Time& dt = this->m_clock.restart();

			this->handleEvents();
			this->update(dt);
			this->display();
		}
	}

	void Application::handleEvents() noexcept
	{
		this->m_window.handleEvents();
		EventManager& eventManager = this->m_window.getEventManager();
		for (; eventManager.getEventQueue().empty() == false; eventManager.pop())
			/*this->m_sceneManager.dispatchEvent(eventQueue.front())*/;
	}

	void Application::update(const Time& dt) noexcept
	{
	}

	void Application::display() const noexcept
	{
		this->m_window.clear();
		//
		this->m_window.display();

		if (const std::uint32_t limit = this->m_window.getFPSLimit(); limit > 0)
			this->sleep(limit);
	}

	void Application::sleep(const std::uint32_t amountSeconds) const noexcept
	{
		const std::int64_t targetFPS = static_cast<std::int64_t>(1000000LL / amountSeconds);
		const std::int64_t sleepTime = targetFPS - this->m_clock.getElapsedTime().asMicroseconds();
		if (sleepTime > 0)
			std::this_thread::sleep_for(std::chrono::microseconds(sleepTime));
	}
}