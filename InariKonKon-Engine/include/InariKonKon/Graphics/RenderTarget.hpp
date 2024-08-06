#pragma once

#include "InariKonKon/Utilities/Macros.hpp"
#include "InariKonKon/Utilities/Color.hpp"

namespace ikk
{
	class IKK_API RenderTarget
	{
	public:
		RenderTarget() noexcept = default;

		RenderTarget(const RenderTarget&) noexcept = default;
		RenderTarget(RenderTarget&&) noexcept = default;

		RenderTarget& operator=(const RenderTarget&) noexcept = default;
		RenderTarget& operator=(RenderTarget&&) noexcept = default;

		virtual ~RenderTarget() noexcept = default;
		
		virtual void setActive(const bool active = true) const noexcept final;

		virtual void clear(const Color clearColor = Color::Black) const noexcept;

		//template<DrawableType T, Projection P = Projection::None>
		//void draw(const T& drawable, const RenderState<P>& state = {}) const noexcept;
	private:
	};
}