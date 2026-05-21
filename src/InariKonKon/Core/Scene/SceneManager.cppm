module;

#include <memory>
#include <vector>
#include <ranges>

export module Core:SceneManager;

import :Scene;

export namespace ikk
{
    class SceneManager final
    {
    public:
        SceneManager() noexcept = default;

        SceneManager(const SceneManager&) noexcept = default;
        SceneManager(SceneManager&&) noexcept = default;

        SceneManager& operator=(const SceneManager&) noexcept = default;
        SceneManager& operator=(SceneManager&&) noexcept = default;

        ~SceneManager() noexcept = default;

        template<SceneType T, class... Args>
        void emplace(Args... args) noexcept;

        void removeUnnecessaryScenes() noexcept;

        [[nodiscard]] auto getActiveScenes() const noexcept;
    private:
        std::vector<std::shared_ptr<Scene>> m_scenes;
    };
}

namespace ikk
{
    template<SceneType T, class... Args>
    void SceneManager::emplace(Args... args) noexcept
    {
        this->m_scenes.emplace_back(std::make_shared<T>(std::forward<Args>(args)...));
    }

    void SceneManager::removeUnnecessaryScenes() noexcept
    {
        std::erase_if(this->m_scenes,
            [](const std::shared_ptr<Scene>& scene) noexcept
            {
                return scene->getState() == Scene::State::Deleted;
            });
    }

    auto SceneManager::getActiveScenes() const noexcept
    {
        return this->m_scenes | std::views::filter(
            [](const std::shared_ptr<Scene>& scene) noexcept
            {
                return scene->getState() == Scene::State::Active;
            });
    }
}