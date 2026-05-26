module;

#include <vector>
#include <ranges>
#include <array>

export module UI:Container;

import Layout;
import Extent;
import Theme;
import Rect;

export namespace ikk
{
    class UIElement;

    class Container final
    {
    public:
        explicit Container(Rectf bound) noexcept;

        Container(const Container&) noexcept = default;
        Container(Container&&) noexcept = default;

        Container& operator=(const Container&) noexcept = default;
        Container& operator=(Container&&) noexcept = default;

        ~Container() noexcept = default;

        void resize(Rectf newBound) noexcept;

        [[nodiscard]] const Rectf& getBound() const noexcept;
        [[nodiscard]] Rectf getContentArea() const noexcept;
    private:
        Rectf m_bound = {};
        Theme m_theme = {};
        Layout m_layout = {};
        std::array<float, 4> m_paddings = {};
        std::array<float, 4> m_margins = {};

        std::vector<UIElement*> m_children = {};

        void addChild(UIElement& child) noexcept;
        void removeChild(UIElement& child) noexcept;

        friend UIElement;
    };
}

namespace ikk
{
    Container::Container(Rectf bound) noexcept
        : m_bound(bound)
    {
    }

    void Container::resize(Rectf newBound) noexcept
    {
        this->m_bound = newBound;
    }

    const Rectf& Container::getBound() const noexcept
    {
        return this->m_bound;
    }

    Rectf Container::getContentArea() const noexcept
    {
        Rectf contentArea = this->m_bound;
        contentArea.getTop()    += this->m_paddings.at(0);
        contentArea.getWidth()  -= this->m_paddings.at(1);
        contentArea.getHeight() -= this->m_paddings.at(2);
        contentArea.getLeft()   += this->m_paddings.at(3);
        return contentArea;
    }

    void Container::addChild(UIElement& child) noexcept
    {
        if (std::ranges::find(this->m_children, &child) == this->m_children.end())
            this->m_children.emplace_back(&child);
    }

    void Container::removeChild(UIElement& child) noexcept
    {
        if (const auto it = std::ranges::find(this->m_children, &child); it != this->m_children.end())
            this->m_children.erase(it);
    }
}