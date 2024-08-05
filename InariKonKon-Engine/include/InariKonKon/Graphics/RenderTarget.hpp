#pragma once

#include "InariKonKon/Utilities/Macros.hpp"

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
	private:
	};
}