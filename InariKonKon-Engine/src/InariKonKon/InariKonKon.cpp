#include "InariKonKon/InariKonKon.hpp"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

namespace ikk
{
	struct Libraries
	{
		inline static const Libraries init() noexcept
		{
			glfwInit();
			return {};
		}
	};

	static Libraries libs = Libraries::init();
}