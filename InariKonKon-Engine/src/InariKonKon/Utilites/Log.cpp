#include "InariKonKon/Utilities/Log.hpp"

#include <print>
#include <cassert>
#include <chrono>
#include <format>

namespace ikk
{
	inline static constexpr const bool contains(const Log::Flags flags, const Log::Flags effect) noexcept
	{
		return (flags & effect) == effect;
	}

	void Log::push(const std::string_view comment, const Log::Level level, const Log::Flags flags) noexcept
	{
		s_logs.emplace(Log::Info{ .comment = comment.data(), .level = level });

		std::string temp{};

		if (contains(flags, Log::Flags::PrintTimePoint))
			temp += std::format("{:%Y/%m/%d %H:%M}", std::chrono::system_clock::now()) + " | ";

		if (contains(flags, Log::Flags::PrintLogLevel))
		{
			switch (level)
			{
			case Log::Level::Fatal:
				temp += "FATAL ERROR | ";
				break;
			case Log::Level::Error:
				temp += "ERROR | ";
				break;
			case Log::Level::Warning:
				temp += "WARNING | ";
				break;
			case Log::Level::Info:
				temp += "INFO | ";
				break;
			}
		}

		temp += comment;

		if (std::to_underlying(level) <= std::to_underlying(s_level) || contains(flags, Log::Flags::ForcePrintToConsole))
			std::print("{}", temp);

		if (level == Log::Level::Fatal)
			assert(false && "Fatal erro has occured! See logs to get more information...");
	}

	void Log::setLevel(const Log::Level level) noexcept
	{
		s_level = level;
	}

	const Log::Level& Log::getLevel() noexcept
	{
		return s_level;
	}

	const std::queue<Log::Info>& Log::getLogs() noexcept
	{
		return s_logs;
	}
}