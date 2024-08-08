#include "InariKonKon/Application/Scene.hpp"

namespace ikk
{
	void Scene::onLateUpdate(const Time& dt) noexcept
	{
	}

	const Scene::SceneID& Scene::getID() const noexcept
	{
		return this->m_id;
	}
}