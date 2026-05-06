module;

#include <filesystem>
#include <cstdint>
#include <thread>
#include <chrono>
#include <atomic>

export module Resource;

import ResourceManager;

import VectorMap;
import Clock;
import Time;

export namespace ikk
{
    class Resource
    {
    public:
        enum struct State : std::uint8_t
        {
            Loading, Ready
        };

        virtual ~Resource() noexcept = default;

        virtual void loadFromFile(const std::filesystem::path& path) noexcept = 0;
        virtual void loadFromFileAsync(const std::filesystem::path& path) noexcept final;

        [[nodiscard]] virtual bool isLoading() const noexcept final;

        virtual void wait() const noexcept final;
        virtual void waitFor(const Time& time) const noexcept final;

        template<class T>
        static void preloadFromFile(const std::string& name, const std::filesystem::path& path) noexcept;
    protected:
        Resource() noexcept = default;

        Resource(const Resource& other) noexcept;
        Resource(Resource&& other) noexcept;

        Resource& operator=(const Resource& other) noexcept;
        Resource& operator=(Resource&& other) noexcept;
    private:
        std::atomic<State> m_state = State::Ready;

        template<class T>
        static VectorMap<std::string, T>& getPreloadedResources() noexcept;
    };
}

namespace ikk
{
    void Resource::loadFromFileAsync(const std::filesystem::path& path) noexcept
    {
        this->m_state.store(Resource::State::Loading, std::memory_order::relaxed);
        resourceManager.getThreadPool().enqueue(
            [path, this] noexcept
            {
                this->loadFromFile(path);
                this->m_state.store(Resource::State::Ready, std::memory_order::release);
                this->m_state.notify_all();
            });
    }

    bool Resource::isLoading() const noexcept
    {
        return this->m_state.load(std::memory_order::acquire) == Resource::State::Loading;
    }

    void Resource::wait() const noexcept
    {
        while (this->isLoading() == true) this->m_state.wait(Resource::State::Loading, std::memory_order::relaxed);
    }

    void Resource::waitFor(const Time& time) const noexcept
    {
        Clock clock{};
        while (clock.getElapsedTime() <= time)
        {
            if (this->isLoading() == false) return;
            std::this_thread::sleep_for(std::chrono::microseconds(1));
        }
    }

    Resource::Resource(const Resource& other) noexcept
    {
        if (this != &other)
        {
            other.wait();
            this->wait();
            this->m_state.store(Resource::State::Ready, std::memory_order::release);
        }
    }

    Resource::Resource(Resource&& other) noexcept
    {
        if (this != &other)
        {
            other.wait();
            this->wait();
            this->m_state.store(Resource::State::Ready, std::memory_order::release);
        }
    }

    Resource& Resource::operator=(const Resource& other) noexcept
    {
        if (this != &other)
        {
            other.wait();
            this->wait();
            this->m_state.store(Resource::State::Ready, std::memory_order::release);
        }
        return *this;
    }

    Resource& Resource::operator=(Resource&& other) noexcept
    {
        if (this != &other)
        {
            other.wait();
            this->wait();
            this->m_state.store(Resource::State::Ready, std::memory_order::release);
        }
        return *this;
    }

    template<class T>
    void Resource::preloadFromFile(const std::string& name, const std::filesystem::path& path) noexcept
    {
        VectorMap<std::string, T>& preloadedResources = getPreloadedResources<T>();
        auto& resource = preloadedResources.emplace(name, T{});
        resource.second.loadFromFileAsync(path);
    }

    template<class T>
    VectorMap<std::string, T>& Resource::getPreloadedResources() noexcept
    {
        static VectorMap<std::string, T> preloadedResources{};
        return preloadedResources;
    }
}