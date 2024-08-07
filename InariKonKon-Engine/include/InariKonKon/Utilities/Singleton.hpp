#pragma once

#include "InariKonKon/Utilities/NonCopyable.hpp"

namespace ikk
{
	template<class T>
	class Singleton : public NonCopyable
	{
	public:
		virtual ~Singleton() noexcept = default;

		[[nodiscard]] inline static T& getInstance() noexcept
		{
			static T instance{};
			return instance;
		}
	protected:
		Singleton() noexcept = default;
	};
}