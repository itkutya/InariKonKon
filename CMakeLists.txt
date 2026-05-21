cmake_minimum_required(VERSION 4.1.0)

project(InariKonKonGameFramework VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)

add_library(InariKonKonGameFramework STATIC)

file(GLOB_RECURSE MODULE_INTERFACES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cppm")
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
target_sources(${CMAKE_PROJECT_NAME} PUBLIC FILE_SET cxx_modules TYPE CXX_MODULES BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/src/" FILES ${MODULE_INTERFACES})
target_sources(${CMAKE_PROJECT_NAME} PUBLIC "${SOURCE_FILES}")

include(FetchContent)

FetchContent_Declare(glfw GIT_REPOSITORY https://github.com/glfw/glfw.git GIT_TAG master)
FetchContent_MakeAvailable(glfw)

FetchContent_Declare(fmt GIT_REPOSITORY https://github.com/fmtlib/fmt.git GIT_TAG main)
FetchContent_MakeAvailable(fmt)

FetchContent_Declare(entt GIT_REPOSITORY https://github.com/skypjack/entt.git GIT_TAG main)
FetchContent_MakeAvailable(entt)

FetchContent_Declare(miniaudio GIT_REPOSITORY https://github.com/mackron/miniaudio.git GIT_TAG master)
FetchContent_MakeAvailable(miniaudio)

set(STEAMAUDIO_ROOT ${CMAKE_SOURCE_DIR}/external/steamaudio)
include_directories(${STEAMAUDIO_ROOT}/include)
#TODO:
if (WIN32)
    set(STEAMAUDIO_LIB ${STEAMAUDIO_ROOT}/lib/windows-x64/phonon.lib)
elseif (UNIX)
    set(STEAMAUDIO_LIB ${STEAMAUDIO_ROOT}/lib/linux-x64/libphonon.so)
endif ()

FetchContent_Declare(stb GIT_REPOSITORY https://github.com/nothings/stb.git GIT_TAG master)
FetchContent_MakeAvailable(stb)

find_package(Vulkan REQUIRED shaderc_combined)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE glfw fmt::fmt EnTT::EnTT Vulkan::Vulkan Vulkan::shaderc_combined miniaudio ${STEAMAUDIO_LIB} stb)
target_compile_options(InariKonKonGameFramework PRIVATE -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion -Wnull-dereference -Wdouble-promotion -Wformat=2)

add_executable(TestApp TestApp.cpp)
target_link_libraries(TestApp InariKonKonGameFramework)
target_compile_options(TestApp PRIVATE -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion -Wnull-dereference -Wdouble-promotion -Wformat=2)