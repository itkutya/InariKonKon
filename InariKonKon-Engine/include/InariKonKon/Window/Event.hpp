#pragma once

#include <cstdint>
#include <variant>

#include "InariKonKon/Utilities/Macros.hpp"

namespace ikk
{
	struct IKK_API Event final
	{
		struct WindowClosed final
		{
		};

		struct FrameBufferResized final
		{
			std::uint32_t width;
			std::uint32_t height;
		};

		template<class T>
		constexpr Event(const T data) noexcept;

		constexpr Event(const Event&) noexcept = default;
		constexpr Event(Event&&) noexcept = default;

		constexpr Event& operator=(const Event&) noexcept = default;
		constexpr Event& operator=(Event&&) noexcept = default;

		constexpr ~Event() noexcept = default;

		template<class T>
		[[nodiscard]] constexpr const bool is() const noexcept;

		template<class T>
		[[nodiscard]] constexpr const T* get() const noexcept;

		template<class T>
		[[nodiscard]] constexpr const T* getIf() const noexcept;
	private:
		struct Uninitialized final {};

		std::variant<
			Uninitialized,
			WindowClosed,
			FrameBufferResized
					> m_data;

		template <typename T, typename... Ts>
		[[nodiscard]] inline static constexpr bool isInParameterPack(const std::variant<Ts...>&)
		{
			return (std::is_same_v<T, Ts> || ...);
		}

		template <typename T>
		inline static constexpr bool isEventType = isInParameterPack<T>(decltype(m_data)());
	};

	template<class T>
	constexpr Event::Event(const T data) noexcept
	{
		static_assert(isEventType<T>, "class T must be a type of ikk::Event!");
		if constexpr (isEventType<T>)
			this->m_data = data;
		else
			this->m_data = Uninitialized{};
	}

	template<class T>
	constexpr const bool Event::is() const noexcept
	{
		static_assert(isEventType<T>, "class T must be a type of ikk::Event!");
		if constexpr (isEventType<T>)
			return std::holds_alternative<T>(this->m_data);
		else
			return false;
	}

	template<class T>
	constexpr const T* Event::get() const noexcept
	{
		static_assert(isEventType<T>, "class T must be a type of ikk::Event!");
		if constexpr (isEventType<T>)
			return std::get_if<T>(&this->m_data);
		else
			return nullptr;
	}

	template<class T>
	constexpr const T* Event::getIf() const noexcept
	{
		static_assert(isEventType<T>, "class T must be a type of ikk::Event!");
		if constexpr (isEventType<T>)
			return std::get_if<T>(&this->m_data);
		else
			return nullptr;
	}
}