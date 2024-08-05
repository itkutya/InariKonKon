#include "InariKonKon/InariKonKon.hpp"

#include <exception>
#include <print>

int main()
{
	try
	{
		ikk::Application::createInstance();
		ikk::Application::getInstance().run();
	}
	catch (const std::exception& e)
	{
		std::print("{}", e.what());
	}
	return 0;
}