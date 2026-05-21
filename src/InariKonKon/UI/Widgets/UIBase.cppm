export module UIBase;

import TransformComponent;
import UIComponent;
import ECS;

import NumericCasts;
import Rotation;
import Vector;
import Rect;

export namespace ikk
{
    class UIBase
    {
    public:
        explicit UIBase(Rectu rect) noexcept;

        UIBase(const UIBase&) noexcept = default;
        UIBase(UIBase&&) noexcept = default;

        UIBase& operator=(const UIBase&) noexcept = default;
        UIBase& operator=(UIBase&&) noexcept = default;

        virtual ~UIBase() noexcept = default;

        [[nodiscard]] virtual const Transform2D& getTransform() const noexcept final;
        [[nodiscard]] virtual Transform2D& getTransform() noexcept final;
    private:
        Entity m_entity{};
    };
}

namespace ikk
{
    UIBase::UIBase(Rectu rect) noexcept
    {
        Vec2f position = { F32(rect.getLeft()), F32(rect.getTop()) };
        RotationDegf rotation = {};
        Vec2f size = { F32(rect.getWidth()), F32(rect.getHeight()) };

        this->m_entity.addComponent<Transform2D>(position, rotation, size);
        this->m_entity.addComponent<UI>();
        //this->m_entity.addComponent<Drawable>();
    }

    const Transform2D& UIBase::getTransform() const noexcept
    {
        return this->m_entity.getComponent<Transform2D>();
    }

    Transform2D& UIBase::getTransform() noexcept
    {
        return this->m_entity.getComponent<Transform2D>();
    }
}