#include "InariKonKon/Window/Window.hpp"

namespace ikk
{
	Window::Window(const std::u8string& title, const WindowBase::Settings settings) noexcept : WindowBase(title, settings)
	{
	}
}