module;

#include <filesystem>
#include <future>
#include <thread>
#include <chrono>
#include <atomic>

export module Resource;

import ResourceManager;
import ResourceLoader;

import Clock;
import Time;

export namespace ikk
{
    template<class T>
    class Resource final
    {
    public:
        Resource() noexcept = default;
        explicit Resource(const std::filesystem::path& path) noexcept;

        Resource(const Resource&) noexcept = delete;
        Resource(Resource&&) noexcept = default;

        Resource& operator=(const Resource&) noexcept = delete;
        Resource& operator=(Resource&&) noexcept = default;

        ~Resource() noexcept = default;

        explicit operator const T&() const noexcept;
        explicit operator T&() noexcept;

        const T& operator->() const noexcept;
        T& operator->() noexcept;

        void load(const std::filesystem::path& path) noexcept;
        void loadAsync(const std::filesystem::path& path) noexcept;

        [[nodiscard]] bool isReady() const noexcept;

        void waitFor(const Time& time) const noexcept;
    private:
        T m_data{};
        std::atomic<ResourceLoader::State> m_state = ResourceLoader::State::Empty;
    };
}

namespace ikk
{
    template<class T>
    Resource<T>::Resource(const std::filesystem::path& path) noexcept
        : m_data(ResourceLoader::load<T>(path))
    {
    }

    template<class T>
    Resource<T>::operator const T&() const noexcept
    {
        return this->m_data;
    }

    template<class T>
    Resource<T>::operator T&() noexcept
    {
        return this->m_data;
    }

    template<class T>
    const T& Resource<T>::operator->() const noexcept
    {
        return this->m_data;
    }

    template<class T>
    T& Resource<T>::operator->() noexcept
    {
        return this->m_data;
    }

    template<class T>
    void Resource<T>::load(const std::filesystem::path& path) noexcept
    {
        this->m_state = ResourceLoader::State::Loading;
        this->m_data = ResourceLoader::load<T>(path);
        this->m_state = ResourceLoader::State::Ready;
    }

    template<class T>
    void Resource<T>::loadAsync(const std::filesystem::path& path) noexcept
    {
        this->m_state = ResourceLoader::State::Loading;
        resourceManager.getThreadPool().enqueue(
            [path, this] noexcept
            {
                T result = ResourceLoader::load<T>(path);
                this->m_data = std::move(result);
                this->m_state = ResourceLoader::State::Ready;
            });
    }

    template<class T>
    bool Resource<T>::isReady() const noexcept
    {
        return this->m_state == ResourceLoader::State::Ready;
    }

    template<class T>
    void Resource<T>::waitFor(const Time& time) const noexcept
    {
        Clock clock{};
        while (clock.getElapsedTime() <= time)
        {
            if (this->isReady() == true) return;
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }
}