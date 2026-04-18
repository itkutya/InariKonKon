export module ResourceManager;

import ThreadPool;
import Singleton;

export namespace ikk
{
    class ResourceManager final : public Singleton<ResourceManager>
    {
        friend class Singleton<ResourceManager>;

        ResourceManager() noexcept = default;
    public:
        ~ResourceManager() noexcept = default;

        const ThreadPool& getThreadPool() const noexcept;
        ThreadPool& getThreadPool() noexcept;
    private:
        ThreadPool m_threadPool{};
    };

    ResourceManager& resourceManager = ResourceManager::getInstance();
}

namespace ikk
{
    const ThreadPool& ResourceManager::getThreadPool() const noexcept
    {
        return this->m_threadPool;
    }

    ThreadPool& ResourceManager::getThreadPool() noexcept
    {
        return this->m_threadPool;
    }
}