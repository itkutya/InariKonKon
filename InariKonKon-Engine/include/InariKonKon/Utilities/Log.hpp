#pragma once

#include <cstdint>
#include <string_view>
#include <string>
#include <queue>
#include <utility>
#include <chrono>

#include "InariKonKon/Utilities/Macros.hpp"

namespace ikk
{
	class IKK_API Log final
	{
	public:
		enum class Level : std::uint8_t
		{
			Fatal = 0,
			Error,
			Warning,
			Info
		};

		enum class Flags : std::uint32_t
		{
			ForcePrintToConsole	= 1 << 0,
			PrintLogLevel		= 1 << 1,
			PrintTimePoint		= 1 << 2,

			Default				= PrintLogLevel | PrintTimePoint,

			All					= ForcePrintToConsole | PrintLogLevel | PrintTimePoint
		};

		struct Info
		{
			std::chrono::system_clock::time_point time = std::chrono::system_clock::now();
			std::string comment;
			Log::Level level;
		};

		Log(const Log&) noexcept = delete;
		Log(Log&&) noexcept = delete;

		Log& operator=(const Log&) noexcept = delete;
		Log& operator=(Log&&) noexcept = delete;

		~Log() noexcept = default;

		static void push(const std::string_view comment, const Log::Level level = Log::Level::Warning, const Log::Flags flags = Log::Flags::Default) noexcept;

		static void setLevel(const Log::Level level) noexcept;
		[[nodiscard]] static const Log::Level& getLevel() noexcept;

		[[nodiscard]] static const std::queue<Log::Info>& getLogs() noexcept;
	private:
		inline static std::queue<Log::Info> s_logs;
		inline static Log::Level s_level = Log::Level::Warning;

		Log() noexcept = default;
	};

	[[nodiscard]] inline constexpr Log::Flags operator| (const Log::Flags l, const Log::Flags r)
	{
		return static_cast<Log::Flags>(std::to_underlying(l) | std::to_underlying(r));
	}

	[[nodiscard]] inline constexpr Log::Flags operator& (const Log::Flags l, const Log::Flags r)
	{
		return static_cast<Log::Flags>(std::to_underlying(l) & std::to_underlying(r));
	}
}

#define IKK_INFO(x)		ikk::Log::push(x, ikk::Log::Level::Info)
#define IKK_WARNING(x)	ikk::Log::push(x, ikk::Log::Level::Warning)
#define IKK_ERROR(x)	ikk::Log::push(x, ikk::Log::Level::Error)
#define IKK_FATAL(x)	ikk::Log::push(x, ikk::Log::Level::Fatal)