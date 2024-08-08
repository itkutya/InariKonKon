#pragma once

#include <unordered_map>
#include <memory>

#include "InariKonKon/Application/Scene.hpp"

namespace ikk
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
	private:
		std::unordered_map<Scene::SceneID, std::shared_ptr<Scene>> m_scenes;
	};
}