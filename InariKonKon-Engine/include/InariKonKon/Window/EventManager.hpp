#pragma once

#include <queue>

#include "InariKonKon/Utilities/Macros.hpp"
#include "InariKonKon/Window/Event.hpp"

namespace ikk
{
	class IKK_API EventManager final
	{
	public:
		EventManager() noexcept = default;

		EventManager(const EventManager&) noexcept = default;
		EventManager(EventManager&&) noexcept = default;

		EventManager& operator=(const EventManager&) noexcept = default;
		EventManager& operator=(EventManager&&) noexcept = default;

		~EventManager() noexcept = default;

		void push(Event&& event) noexcept;
		void pop() noexcept;

		const std::queue<Event>& getEventQueue() const noexcept;
	private:
		std::queue<Event> m_events;
	};
}