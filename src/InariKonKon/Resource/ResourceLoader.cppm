module;

#include <filesystem>

export module ResourceLoader;

import NonConstructible;

export namespace ikk
{
    class ResourceLoader final : public NonConstructible
    {
    public:
        enum struct State : std::uint8_t
        {
            Empty, Loading, Ready, Failed
        };

        template<class T>
        [[nodiscard]] static T load(const std::filesystem::path& path) noexcept;
    private:
    };
}

namespace ikk
{
    //TODO: Impl like this...
    template<>
    int ResourceLoader::load<int>(const std::filesystem::path& path) noexcept
    {
        return 1;
    }
}