#include "InariKonKon/InariKonKon.hpp"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#include "InariKonKon/Utilities/Log.hpp"

namespace ikk
{
	struct Libraries
	{
		inline static const Libraries init() noexcept
		{
			if (glfwInit() == GLFW_FALSE)
				Log::push("Cannot initialize GLFW!", Log::Level::Fatal);

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			return {};
		}
	};

	static Libraries libs = Libraries::init();
}