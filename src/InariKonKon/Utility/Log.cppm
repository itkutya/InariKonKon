module;

#include <string_view>
#include <utility>
#include <cstdint>
#include <chrono>

#include "fmt/core.h"
#include "fmt/chrono.h"
#include "fmt/std.h"

export module Log;

import NonCopyable;
import NonMovable;
import Utility;
import Flag;

export namespace ikk
{
    namespace Log
    {
        enum struct Level : std::uint8_t
        {
            Info = 0,
            Warning,
            Error,
            Fatal
        };

        enum struct Flags : std::uint32_t
        {
            None        = 0 << 0,
            Date        = 1 << 0,
            Severity    = 1 << 1,
            Debug       = 1 << 2,
            All         = None | Date | Severity
        };
    }

    template<Log::Level level = Log::Level::Info, Log::Flags flags = Log::Flags::All>
    class BasicLogger final : public NonCopyable, public NonMovable
    {
    public:
        template<class... Args>
        BasicLogger(fmt::format_string<Args...> fmt, Args&&... args) noexcept;

        ~BasicLogger() noexcept = default;
    private:
        [[nodiscard]] static constexpr std::string_view convertToString(Log::Level severety) noexcept;
    };

    template<Log::Level level = Log::Level::Info, Log::Flags flags = Log::Flags::All>
    using DebugPrint = BasicLogger<level, static_cast<Log::Flags>(std::to_underlying(flags) | std::to_underlying(Log::Flags::Debug))>;

    template<Log::Level level = Log::Level::Info, Log::Flags flags = Log::Flags::All>
    using Print = BasicLogger<level, flags>;
}

namespace ikk
{
    template<Log::Level level, Log::Flags flags>
    template<class... Args>
    BasicLogger<level, flags>::BasicLogger(fmt::format_string<Args...> fmt, Args&&... args) noexcept
    {
        const Flag<Log::Flags> flag{flags};

        if (isDebug() == false && flag.contains(Log::Flags::Debug) == true)
            return;

        fmt::memory_buffer buffer{};

        if (flag.contains(Log::Flags::Severity) == true)
            fmt::format_to(fmt::appender(buffer), "[{}] ", convertToString(level));

        if (flag.contains(Log::Flags::Date) == true)
        {
            const auto now = std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::system_clock::now());
            fmt::format_to(fmt::appender(buffer), "({:%EY.%Om.%Od. %OH:%OM:%OS}) ", now);
        }

        fmt::format_to(fmt::appender(buffer), ": ");

        fmt::format_to(fmt::appender(buffer), fmt, std::forward<Args>(args)...);
        fmt::println("{}", fmt::string_view(buffer.data(), buffer.size()));
    }

    template<Log::Level level, Log::Flags flags>
    constexpr std::string_view BasicLogger<level, flags>::convertToString(Log::Level severety) noexcept
    {
        switch (severety)
        {
            case Log::Level::Info:       return "INFO";
            case Log::Level::Warning:    return "WARNING";
            case Log::Level::Error:      return "ERROR";
            case Log::Level::Fatal:      return "FATAL";
        }
        return "UNKNOWN";
    }
}