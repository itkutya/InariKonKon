#pragma once

#include "InariKonKon/Graphics/RenderTarget.hpp"
#include "InariKonKon/Window/WindowBase.hpp"

namespace ikk
{
	class IKK_API Window final : public WindowBase, public RenderTarget
	{
	public:
		Window(const std::u8string& title) noexcept;

		Window(const Window&) noexcept = default;
		Window(Window&&) noexcept = default;

		Window& operator=(const Window&) noexcept = default;
		Window& operator=(Window&&) noexcept = default;

		~Window() noexcept = default;
	private:
	};
}