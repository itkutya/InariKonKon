#pragma once

#define VERSION 1.01

#ifdef _DEBUG
	#define IKK_DEBUG
#else
	#define IKK_RELEASE
#endif

#ifdef _WIN32
	#ifdef _WIN64
		#define IKK_PLATFORM_WINDOWS
	#else
		#error "x86 Builds are not supported!"
	#endif
#else
static_assert(false, "Platform is not supported!");
#endif

#ifdef IKK_PLATFORM_WINDOWS
	#ifdef IKK_ENGINE
		#define IKK_API __declspec(dllexport)
	#else
		#define IKK_API __declspec(dllimport)
	#endif
#else
static_assert(false, "This engine only supports windows!");
#endif

#ifdef _MSC_VER
#pragma warning(disable : 4251)
#endif

#define EDITOR_WINDOW_TITLE reinterpret_cast<const char8_t*>(std::format("InariKonKon - Editor v{0:.2f}", VERSION).c_str())