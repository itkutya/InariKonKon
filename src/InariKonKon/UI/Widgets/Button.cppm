module;

#include <string_view>

export module Button;

import UI;

export namespace ikk
{
    class [[nodiscard]] Button final : public UIElement
    {
    public:
        [[nodiscard]] explicit Button(std::string_view text, Extent position, Extent size, const Theme& theme = Theme::Default()) noexcept;

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
    Button::Button(std::string_view text, Extent position, Extent size, const Theme& theme) noexcept
        : UIElement(position, size)
    {
    }
}