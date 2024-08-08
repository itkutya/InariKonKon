#pragma once

#include <cstdint>

namespace ikk
{
	class Event;
	class Time;
	class Window;

	class Scene
	{
	public:
		typedef std::uint32_t SceneID;

		Scene() noexcept = default;

		Scene(const Scene&) noexcept = default;
		Scene(Scene&&) noexcept = default;

		Scene& operator=(const Scene&) noexcept = default;
		Scene& operator=(Scene&&) noexcept = default;

		virtual ~Scene() noexcept = default;

		virtual void onEvent(const Event& event) noexcept = 0;
		virtual void onUpdate(const Time& dt) noexcept = 0;
		virtual void onLateUpdate(const Time& dt) noexcept;
		virtual void onRender(const Window& window) const noexcept = 0;

		virtual const Scene::SceneID& getID() const noexcept final;
	private:
		Scene::SceneID m_id = 0;
	};
}