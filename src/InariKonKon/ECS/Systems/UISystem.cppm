export module UISystem;

import TransformComponent;
import ECS;
import UI;

import Rect;

import NonConstructible;

namespace ikk
{
    //TODO:
    //TransformComponent
    //Drawable
    //LayoutComponent (?)
    struct UILogic final : public NonConstructible
    {
        static void update(const Transform2D& transform, UI& uiComponent, Container& defaultContainer) noexcept
        {
            if (transform.isDisabled() == true || uiComponent.isDisabled() == true) return;

            UIElement& uiElement = uiComponent.getUIElement();

            if (uiElement.getContainer() == nullptr) uiElement.setContainer(defaultContainer);

            const Rectf uiBound = uiElement.getBound();
        }
    };
}

export namespace ikk
{
    using UISystem = System<&UILogic::update, Transform2D, UI>;
}