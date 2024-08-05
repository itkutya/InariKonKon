#pragma once

#include "InariKonKon/Utilities/Singleton.hpp"
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
		Window m_window{ u8"Title" };
	};
}