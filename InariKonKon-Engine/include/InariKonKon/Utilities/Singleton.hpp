#pragma once

#include "InariKonKon/Utilities/NonCopyable.hpp"

namespace ikk
{
	template<class T>
	class Singleton : public NonCopyable
	{
	public:
		virtual ~Singleton() noexcept = default;

		inline static void createInstance() noexcept
		{
			static T instance;
			ptr = &instance;
		}

		[[nodiscard]] inline static const T& getConstInstance() noexcept
		{
			if (ptr == nullptr)
				createInstance();
			return *ptr;
		}

		[[nodiscard]] inline static T& getInstance() noexcept
		{
			if (ptr == nullptr)
				createInstance();
			return *ptr;
		}
	private:
		inline static T* ptr = nullptr;

		Singleton() noexcept = default;
		friend T;
	};
}