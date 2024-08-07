#pragma once

#include <memory>

#include "InariKonKon/Utilities/Singleton.hpp"
#include "InariKonKon/Utilities/Macros.hpp"

struct GladGLContext;

namespace ikk
{
	class IKK_API Context final : public Singleton<Context>
	{
		friend class Singleton<Context>;
		Context() noexcept;
	public:
		~Context() noexcept = default;

		const GladGLContext* const getContext() const noexcept;
		GladGLContext* const getContext() noexcept;
	private:
		std::shared_ptr<GladGLContext> m_context;
	};
}