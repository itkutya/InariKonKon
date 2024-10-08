#include "InariKonKon/InariKonKon.hpp"

#include <exception>
#include <print>

#include "InariKonKon/EditorScene.hpp"

int main()
{
	try
	{
		ikk::Application app{};
		app.run();
	}
	catch (const std::exception& e)
	{
		std::print("{}", e.what());
	}
	return 0;
}