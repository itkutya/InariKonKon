module;

#include <optional>

export module Theme;

import Texture;
import Color;

export namespace ikk
{
    struct [[nodiscard]] Theme final
    {
        [[nodiscard]] static const Theme& Default() noexcept;
        static void setDefault(const Theme& theme) noexcept;

        std::optional<Color> color              = Default().color;
        std::optional<Color> outlineColor       = Default().outlineColor;
        std::optional<float> outlineThickness   = Default().outlineThickness;
        std::optional<float> cornerRadius       = Default().cornerRadius;
        std::optional<Texture> texture          = Default().texture;
        //TODO: Font
        std::optional<Color> textColor          = Default().textColor;
    };
}

namespace ikk
{
    inline static Theme defaultTheme =
        {
            .color = Color::Miku,
            .outlineColor = Color::Black,
            .outlineThickness = 0.0f,
            .cornerRadius = 0.0f,
            .texture = std::nullopt,
            .textColor = Color::Black
        };

    const Theme& Theme::Default() noexcept
    {
        return defaultTheme;
    }

    void Theme::setDefault(const Theme& theme) noexcept
    {
        defaultTheme = theme;
    }
}