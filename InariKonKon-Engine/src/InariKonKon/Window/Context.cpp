#include "InariKonKon/Window/Context.hpp"

#include "glad/gl.h"

namespace ikk
{
	Context::Context() noexcept : m_context(std::make_shared<GladGLContext>())
	{
	}

	const GladGLContext* const Context::getContext() const noexcept
	{
		return this->m_context.get();
	}

	GladGLContext* const Context::getContext() noexcept
	{
		return this->m_context.get();
	}
}