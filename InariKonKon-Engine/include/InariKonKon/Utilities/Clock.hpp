#pragma once

#include "InariKonKon/Utilities/Time.hpp"

namespace ikk
{
	class IKK_API Clock final
	{
	public:
		Clock() noexcept = default;

		Clock(const Clock&) noexcept = default;
		Clock(Clock&&) noexcept = default;

		Clock& operator=(const Clock&) noexcept = default;
		Clock& operator=(Clock&&) noexcept = default;

		~Clock() noexcept = default;

		[[nodiscard]] const Time getElapsedTime() const noexcept;
		const Time restart() noexcept;
	private:
		std::chrono::steady_clock::time_point m_startPoint = std::chrono::steady_clock::now();
	};
}