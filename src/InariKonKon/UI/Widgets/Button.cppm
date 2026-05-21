module;

#include <string_view>

export module Button;

import UIBase;
import Theme;
import Rect;

export namespace ikk
{
    class [[nodiscard]] Button final : public UIBase
    {
    public:
        [[nodiscard]] explicit Button(std::string_view text, Rectu rect, const Theme& theme = Theme::Default()) noexcept;

        Button(const Button&) noexcept = default;
        Button(Button&&) noexcept = default;

        Button& operator=(const Button&) noexcept = default;
        Button& operator=(Button&&) noexcept = default;

        ~Button() noexcept = default;
    private:
    };
}

namespace ikk
{
    Button::Button(std::string_view text, Rectu rect, const Theme& theme) noexcept
        : UIBase(rect)
    {
    }
}