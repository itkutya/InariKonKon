export module UI:Component;

import Component;

//TODO:
//Layout specific stuff...
//Transform offset, for animation stuff...
//Idk...
export namespace ikk
{
    class UIElement;

    class UI final : public Component
    {
    public:
        explicit UI(UIElement& ui) noexcept;

        UI(const UI&) noexcept = default;
        UI(UI&&) noexcept = default;

        UI& operator=(const UI&) noexcept = default;
        UI& operator=(UI&&) noexcept = default;

        ~UI() noexcept = default;

        [[nodiscard]] const UIElement& getUIElement() const noexcept;
        [[nodiscard]] UIElement& getUIElement() noexcept;
    private:
        UIElement* m_element = nullptr;
    };
}

namespace ikk
{
    UI::UI(UIElement& ui) noexcept
        : m_element(&ui)
    {
    }

    const UIElement& UI::getUIElement() const noexcept
    {
        return *this->m_element;
    }

    UIElement& UI::getUIElement() noexcept
    {
        return *this->m_element;
    }
}