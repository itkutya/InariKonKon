export module UIBase;

export namespace ikk
{
    class UIBase
    {
    public:
        UIBase() noexcept = default;

        UIBase(const UIBase&) noexcept = default;
        UIBase(UIBase&&) noexcept = default;

        UIBase& operator=(const UIBase&) noexcept = default;
        UIBase& operator=(UIBase&&) noexcept = default;

        virtual ~UIBase() noexcept = default;

        virtual void disable() noexcept;
        virtual void enable() noexcept;
    private:
        bool m_enabled = true;
    };
}

namespace ikk
{
    void UIBase::disable() noexcept
    {
        this->m_enabled = false;
    }

    void UIBase::enable() noexcept
    {
        this->m_enabled = true;
    }
}