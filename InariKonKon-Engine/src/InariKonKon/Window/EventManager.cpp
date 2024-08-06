#include "InariKonKon/Window/EventManager.hpp"

namespace ikk
{
	void EventManager::push(Event&& event) noexcept
	{
		this->m_events.emplace(std::move(event));
	}

	void EventManager::pop() noexcept
	{
		this->m_events.pop();
	}

	const std::queue<Event>& EventManager::getEventQueue() const noexcept
	{
		return this->m_events;
	}
}