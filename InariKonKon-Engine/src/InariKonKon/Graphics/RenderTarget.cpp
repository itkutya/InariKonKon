#include "InariKonKon/Graphics/RenderTarget.hpp"

namespace ikk
{
	void RenderTarget::setActive(const bool active) const noexcept
	{
	}

	void RenderTarget::clear(const Color clearColor) const noexcept
	{
		this->setActive();
		//gl->BindFramebuffer(GL_FRAMEBUFFER, 0);
		//gl->ClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
		//gl->Clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}