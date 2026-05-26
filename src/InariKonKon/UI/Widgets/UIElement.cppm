module;

#include <variant>

export module UI:Element;

import :Component;
import :Container;

import TransformComponent;
import ECS;

import Rotation;
import Extent;
import Vector;
import Rect;

export namespace ikk
{
    class UIElement
    {
    public:
        UIElement(Extent position, Extent size) noexcept;

        UIElement(const UIElement&) noexcept = default;
        UIElement(UIElement&&) noexcept = default;

        UIElement& operator=(const UIElement&) noexcept = default;
        UIElement& operator=(UIElement&&) noexcept = default;

        virtual ~UIElement() noexcept = default;

        [[nodiscard]] virtual const Transform2D& getTransform() const noexcept final;
        [[nodiscard]] virtual const Extent& getPosition() const noexcept final;
        [[nodiscard]] virtual const Extent& getSize() const noexcept final;

        [[nodiscard]] virtual Rectf getBound(const Container& container) const noexcept final;
        [[nodiscard]] virtual Rectf getBound() const noexcept final;

        void setContainer(Container& container) noexcept;
        void removeContainer() noexcept;

        [[nodiscard]] virtual const Container* getContainer() const noexcept final;
        [[nodiscard]] virtual Container* getContainer() noexcept final;
    protected:
        [[nodiscard]] virtual const Entity& getEntity() const noexcept final;
        [[nodiscard]] virtual Entity& getEntity() noexcept final;
    private:
        Entity m_entity{};
        Extent m_position{};
        Extent m_size{};

        Container* m_container = nullptr;
    };
}

namespace ikk
{
    [[nodiscard]] float resolveUnit(const Extent::Unit& unit, float bound = 0) noexcept
    {
        struct [[nodiscard]] UnitResolver
        {
            float m_bound = 0.f;

            [[nodiscard]] float operator()(Pixel value) const noexcept
            {
                return value;
            }

            [[nodiscard]] float operator()(Percentage value) const noexcept
            {
                return this->m_bound * value;
            }

            [[nodiscard]] float operator()([[maybe_unused]] Fill) const noexcept
            {
                return this->m_bound;
            }

            [[nodiscard]] float operator()([[maybe_unused]] Shrink) const noexcept
            {
                return 0.f;
            }
        };
        return std::visit(UnitResolver{bound}, unit);
    }

    UIElement::UIElement(Extent position, Extent size) noexcept
        : m_position(position), m_size(size)
    {
        const Rectf bound = this->getBound();
        Vec2f pos = { bound.getLeft(), bound.getTop() };
        Vec2f ext = { bound.getWidth(), bound.getHeight() };
        //TODO: Ignore for now
        RotationDegf rot{};
        this->m_entity.addComponent<Transform2D>(pos, rot, ext);
        this->m_entity.addComponent<UI>(*this);
        //TODO:
        //Drawable component...
    }

    const Transform2D& UIElement::getTransform() const noexcept
    {
        return this->m_entity.getComponent<Transform2D>();
    }

    const Extent& UIElement::getPosition() const noexcept
    {
        return this->m_position;
    }

    const Extent& UIElement::getSize() const noexcept
    {
        return this->m_size;
    }

    Rectf UIElement::getBound(const Container& container) const noexcept
    {
        const Rectf containerBound = container.getBound();

        Rectf bound{};

        bound.getLeft() = resolveUnit(this->m_position.x, containerBound.getWidth());
        bound.getTop() = resolveUnit(this->m_position.y, containerBound.getHeight());

        bound.getWidth() = resolveUnit(this->m_size.x, containerBound.getWidth());
        bound.getHeight() = resolveUnit(this->m_size.y, containerBound.getHeight());

        return bound;
    }

    Rectf UIElement::getBound() const noexcept
    {
        if (this->m_container != nullptr) return this->getBound(*this->m_container);

        Rectf bound{};

        bound.getLeft() = resolveUnit(this->m_position.x);
        bound.getTop() = resolveUnit(this->m_position.y);

        bound.getWidth() = resolveUnit(this->m_size.x);
        bound.getHeight() = resolveUnit(this->m_size.y);

        return bound;
    }

    void UIElement::setContainer(Container& container) noexcept
    {
        if (this->m_container == &container) return;

        if (this->m_container != nullptr) this->m_container->removeChild(*this);

        this->m_container = &container;
        this->m_container->addChild(*this);
    }

    void UIElement::removeContainer() noexcept
    {
        if (this->m_container != nullptr) this->m_container->removeChild(*this);

        this->m_container = nullptr;
    }

    const Container* UIElement::getContainer() const noexcept
    {
        return this->m_container;
    }

    Container* UIElement::getContainer() noexcept
    {
        return this->m_container;
    }

    const Entity& UIElement::getEntity() const noexcept
    {
        return this->m_entity;
    }

    Entity& UIElement::getEntity() noexcept
    {
        return this->m_entity;
    }
}