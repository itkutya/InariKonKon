#include "InariKonKon/Graphics/RenderTarget.hpp"

#include "InariKonKon/Graphics/OpenGL.hpp"

namespace ikk
{
	void RenderTarget::clear(const Color clearColor) const noexcept
	{
		gl->ClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
		gl->Clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}
}