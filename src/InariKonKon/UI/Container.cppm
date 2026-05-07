module;

#include <ranges>
#include <vector>
#include <array>

export module Container;

import UIBase;
import Layout;
import Extent;
import Theme;
import Rect;

export namespace ikk
{
    class Container
    {
    public:
        void setChild(UIBase* child) noexcept;
    private:
        Rectu m_rect = {};
        Theme m_theme = {};
        Layout m_layout = {};
        std::vector<UIBase*> m_children = {};
        std::array<float, 4> m_paddings = {};
        std::array<float, 4> m_margins = {};
    };
}

namespace ikk
{
    void Container::setChild(UIBase* child) noexcept
    {
        if (std::ranges::find(this->m_children, child) == this->m_children.end())
            this->m_children.emplace_back(child);
        //TODO:
        //Report error...
    }
}

//Does not need to call .draw(), just create it, if you don't want to draw it --> .disable() it
// (?) .setPanel(&panel) if you want to set a specific panel and ignore the default panel (the main window).

// UI element size & position stuff:
// - Margin  (between every object)
// - Padding (between border & contnent) (?)
// - Array 4 becouse left, right, top, bottom...
//
// Set per panel ---> Can only have 1 per panel & can't change mid calculation
// Panels are just "sub-windows"