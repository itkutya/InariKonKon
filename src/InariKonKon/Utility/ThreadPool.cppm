module;

#include <condition_variable>
#include <functional>
#include <vector>
#include <thread>
#include <future>
#include <memory>
#include <atomic>
#include <queue>
#include <mutex>

export module ThreadPool;

import NonCopyable;
import NonMovable;

export namespace ikk
{
    class ThreadPool final : public NonCopyable, public NonMovable
    {
    public:
        explicit ThreadPool(std::size_t maxThreadCount = std::thread::hardware_concurrency()) noexcept;

        ~ThreadPool() noexcept;

        template<class F, class... Args>
        std::future<typename std::invoke_result<F, Args...>::type> enqueue(F&& f, Args&&... args) noexcept;
    private:
        std::vector<std::thread> m_threads;

        std::queue<std::function<void()>> m_tasks;

        std::mutex m_queueMutex;
        std::condition_variable m_condition;
        std::atomic<bool> m_stop = false;
    };
}

namespace ikk
{
    ThreadPool::ThreadPool(std::size_t maxThreadCount) noexcept
    {
        this->m_threads.reserve(maxThreadCount);

        for (std::size_t i = 0; i < maxThreadCount; i++)
        {
            this->m_threads.emplace_back(
                [this] noexcept
                {
                    while (true)
                    {
                        std::function<void()> task;
                        {
                            std::unique_lock<std::mutex> lock(this->m_queueMutex);
                            this->m_condition.wait(lock, [this] noexcept
                            {
                                return this->m_stop || !this->m_tasks.empty();
                            });

                            if (this->m_stop && this->m_tasks.empty()) return;

                            task = std::move(this->m_tasks.front());
                            this->m_tasks.pop();
                        }
                        task();
                    }
                });
        }
    }

    template<class F, class... Args>
    std::future<typename std::invoke_result<F, Args...>::type> ThreadPool::enqueue(F&& f, Args&&... args) noexcept
    {
        using ReturnType = std::invoke_result<F, Args...>::type;
        auto task = std::make_shared<std::packaged_task<ReturnType()>>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));

        std::future<ReturnType> res = task->get_future();
        {
            std::unique_lock<std::mutex> lock(this->m_queueMutex);
            if (this->m_stop) return {};

            this->m_tasks.emplace([task] noexcept { (*task)(); });
        }
        this->m_condition.notify_one();
        return res;
    }

    ThreadPool::~ThreadPool() noexcept
    {
        this->m_stop = true;
        this->m_condition.notify_all();
        for (std::thread& thread : this->m_threads) thread.join();
    }
}
