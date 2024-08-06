#pragma once

#include <queue>

#include "InariKonKon/Utilities/Macros.hpp"
#include "InariKonKon/Window/Event.hpp"

namespace ikk
{
	class IKK_API EventManager final
	{
	public:
		void push(Event&& event) noexcept;
		void pop() noexcept;

		const std::queue<Event>& getEventQueue() const noexcept;
	private:
		std::queue<Event> m_events;
	};
}