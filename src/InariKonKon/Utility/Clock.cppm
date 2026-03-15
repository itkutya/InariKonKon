module;

#include <chrono>
#include <thread>

export module Clock;

import Time;

export namespace ikk
{
    class [[nodiscard]] Clock final
    {
    public:
        [[nodiscard]] Clock() noexcept = default;

        ~Clock() noexcept = default;

        Clock(const Clock&) noexcept = default;
        Clock(Clock&&) noexcept = default;

        Clock& operator=(const Clock&) noexcept = default;
        Clock& operator=(Clock&&) noexcept = default;

        void start() noexcept;
        void stop() noexcept;

        static void waitFor(const Time time) noexcept;

        [[nodiscard]] Time getElapsedTime() const noexcept;
        [[nodiscard]] bool isRunning() const noexcept;

        Time restart() noexcept;
        Time reset() noexcept;
    private:
        std::chrono::steady_clock::time_point m_startPoint  { std::chrono::steady_clock::now() };
        std::chrono::steady_clock::time_point m_stopPoint   {};
    };

    void Clock::start() noexcept
    {
        if (this->isRunning() == false)
        {
            this->m_startPoint += std::chrono::steady_clock::now() - this->m_stopPoint;
            this->m_stopPoint = {};
        }
    }

    void Clock::stop() noexcept
    {
        if (this->isRunning() == true)
            this->m_stopPoint = std::chrono::steady_clock::now();
    }

    void Clock::waitFor(const Time time) noexcept
    {
        std::this_thread::sleep_for(time.toDuration<std::chrono::microseconds>());
    }

    Time Clock::getElapsedTime() const noexcept
    {
        if (this->isRunning())
            return Time{ std::chrono::steady_clock::now() - this->m_startPoint };
        return Time{ this->m_stopPoint - this->m_startPoint };
    }

    bool Clock::isRunning() const noexcept
    {
        return this->m_stopPoint == std::chrono::steady_clock::time_point();
    }

    Time Clock::restart() noexcept
    {
        const Time elapsed = this->getElapsedTime();
        this->m_startPoint = std::chrono::steady_clock::now();
        this->m_stopPoint = {};
        return elapsed;
    }

    Time Clock::reset() noexcept
    {
        const Time elapsed = this->getElapsedTime();
        this->m_startPoint = std::chrono::steady_clock::now();
        this->m_stopPoint = this->m_startPoint;
        return elapsed;
    }
}