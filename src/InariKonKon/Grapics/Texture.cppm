module;

#include <filesystem>
#include <cstdint>
#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

export module Texture;

import NumericCasts;
import Resource;

export namespace ikk
{
    class [[nodiscard]] Texture final : public Resource
    {
    public:
        [[nodiscard]] Texture() noexcept = default;
        [[nodiscard]] explicit Texture(const std::filesystem::path& path) noexcept;

        Texture(const Texture&) noexcept = default;
        Texture(Texture&&) noexcept = default;

        Texture& operator=(const Texture&) noexcept = default;
        Texture& operator=(Texture&&) noexcept = default;

        ~Texture() noexcept = default;

        virtual void loadFromFile(const std::filesystem::path& path) noexcept override;
    private:
        std::uint32_t m_width = 0;
        std::uint32_t m_height = 0;
        std::uint32_t m_channels = 0;
        std::vector<std::uint8_t> m_data{};
    };
}

namespace ikk
{
    Texture::Texture(const std::filesystem::path& path) noexcept
    {
        this->loadFromFile(path);
    }

    void Texture::loadFromFile(const std::filesystem::path& path) noexcept
    {
        int width{};
        int height{};
        int channels{};

        stbi_uc* pixels = stbi_load(path.string().c_str(), &width, &height, &channels, 0);

        if (!pixels)
            return;

        this->m_width = U32(width);
        this->m_height = U32(height);
        this->m_channels = U32(channels);

        const std::size_t size = static_cast<std::size_t>(width) * static_cast<std::size_t>(height) * static_cast<std::size_t>(channels);

        this->m_data.assign(pixels, pixels + size);

        stbi_image_free(pixels);
    }
}