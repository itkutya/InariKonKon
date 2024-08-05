#pragma once

#include "InariKonKon/Utilities/Macros.hpp"

namespace ikk
{
	class IKK_API NonCopyable
	{
	public:
		NonCopyable() noexcept = default;

		NonCopyable(const NonCopyable&) noexcept = delete;
		NonCopyable(NonCopyable&&) noexcept = delete;

		NonCopyable& operator=(const NonCopyable&) noexcept = delete;
		NonCopyable& operator=(NonCopyable&&) noexcept = delete;

		virtual ~NonCopyable() noexcept = default;
	private:
	};
}