#pragma once

#include <cstdint>
#include <algorithm>

#include <InariKonKon/Utilities/Macros.hpp>

#define UINT8_MAX_IN_FLOAT static_cast<float>(UINT8_MAX)

namespace ikk
{
	struct Color final
	{
		constexpr Color() noexcept = default;
		inline constexpr Color(const float r, const float g, const float b, const float a = 1.f) noexcept
			: r(std::clamp(r, 0.f, 1.f)), g(std::clamp(g, 0.f, 1.f)), b(std::clamp(b, 0.f, 1.f)), a(std::clamp(a, 0.f, 1.f)) {}
		inline constexpr Color(const std::uint8_t r, const std::uint8_t g, const std::uint8_t b, const std::uint8_t a = UINT8_MAX) noexcept
			:	r(std::clamp(r / UINT8_MAX_IN_FLOAT, 0.f, 1.f)), g(std::clamp(g / UINT8_MAX_IN_FLOAT, 0.f, 1.f)),
				b(std::clamp(b / UINT8_MAX_IN_FLOAT, 0.f, 1.f)), a(std::clamp(a / UINT8_MAX_IN_FLOAT, 0.f, 1.f)) {}
		inline explicit constexpr Color(std::uint32_t hex) noexcept
			:	r(std::clamp(((hex >> 24) & 0xFF) / UINT8_MAX_IN_FLOAT, 0.f, 1.f)),
				g(std::clamp(((hex >> 16) & 0xFF) / UINT8_MAX_IN_FLOAT, 0.f, 1.f)),
				b(std::clamp(((hex >> 8)  & 0xFF) / UINT8_MAX_IN_FLOAT, 0.f, 1.f)),
				a(std::clamp(( hex        & 0xFF) / UINT8_MAX_IN_FLOAT, 0.f, 1.f)) {}

		constexpr Color(const Color&) noexcept = default;
		constexpr Color(Color&&) noexcept = default;

		constexpr Color& operator=(const Color&) noexcept = default;
		constexpr Color& operator=(Color&&) noexcept = default;

		constexpr ~Color() noexcept = default;

		[[nodiscard]] inline static constexpr const std::uint32_t ColorToUInt32(const Color color) noexcept
		{
			return	static_cast<std::uint32_t>(
				static_cast<std::uint8_t>(color.r * UINT8_MAX) << 24 |
				static_cast<std::uint8_t>(color.g * UINT8_MAX) << 16 |
				static_cast<std::uint8_t>(color.b * UINT8_MAX) << 8  |
				static_cast<std::uint8_t>(color.a * UINT8_MAX));
		}

		float r = 0.f;
		float g = 0.f;
		float b = 0.f;
		float a = 1.f;

		static const Color White;
		static const Color Black;
		static const Color Red;
		static const Color Green;
		static const Color Blue;
		static const Color Yellow;
		static const Color Magenta;
		static const Color Cyan;
		static const Color Transparent;
	};

	inline constexpr Color Color::White			{ 1.f, 1.f, 1.f };
	inline constexpr Color Color::Black			{ 0.f, 0.f, 0.f };
	inline constexpr Color Color::Red			{ 1.f, 0.f, 0.f };
	inline constexpr Color Color::Green			{ 0.f, 1.f, 0.f };
	inline constexpr Color Color::Blue			{ 0.f, 0.f, 1.f };
	inline constexpr Color Color::Yellow		{ 1.f, 1.f, 0.f };
	inline constexpr Color Color::Magenta		{ 1.f, 0.f, 1.f };
	inline constexpr Color Color::Cyan			{ 0.f, 1.f, 1.f };
	inline constexpr Color Color::Transparent	{ 0.f, 0.f, 0.f, 0.f };
}