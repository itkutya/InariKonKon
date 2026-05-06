module;

#include <type_traits>

export module BasicResources;

export import Resource;
export import Texture;
export import Audio;

export namespace ikk
{
    template<class T>
    concept BasicResource = std::is_base_of<Resource, T>::value;
}