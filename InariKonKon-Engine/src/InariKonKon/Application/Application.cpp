#include "InariKonKon/Application/Application.hpp"

namespace ikk
{
	void Application::run() noexcept
	{
		while (this->m_window.shouldClose() == false)
		{
			this->m_window.handleEvents();
			this->m_window.display();
		}
	}
}