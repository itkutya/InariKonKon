module;

#include <memory>

export module Core:Renderer;

import Color;

export namespace ikk
{
    class [[nodiscard]] Renderer final
    {
    public:
        class Type
        {
        public:
            virtual ~Type() noexcept = default;

            [[nodiscard]] virtual bool isValid() const noexcept = 0;

            virtual void beginRender(const Color& clearColor) noexcept = 0;
            virtual void endRender() noexcept = 0;
        protected:
            Type() noexcept = default;

            Type(const Type&) noexcept = default;
            Type(Type&&) noexcept = default;

            Type& operator=(const Type&) noexcept = default;
            Type& operator=(Type&&) noexcept = default;
        private:
        };

        Renderer() noexcept = default;

        Renderer(const Renderer&) noexcept = default;
        Renderer(Renderer&&) noexcept = default;

        Renderer& operator=(const Renderer&) noexcept = default;
        Renderer& operator=(Renderer&&) noexcept = default;

        ~Renderer() noexcept = default;

        template<class T, class... Args> requires (std::is_base_of<Renderer::Type, T>::value)
        void create(Args&&... args) noexcept;

        [[nodiscard]] const std::shared_ptr<Type>& get() const noexcept;
        [[nodiscard]] std::shared_ptr<Type>& get() noexcept;
    private:
        std::shared_ptr<Type> m_renerer = nullptr;
    };
}

namespace ikk
{
    template<class T, class... Args> requires (std::is_base_of<Renderer::Type, T>::value)
    void Renderer::create(Args&&... args) noexcept
    {
        this->m_renerer = std::make_shared<T>(std::forward<Args>(args)...);
    }

    const std::shared_ptr<Renderer::Type>& Renderer::get() const noexcept
    {
        return this->m_renerer;
    }

    std::shared_ptr<Renderer::Type>& Renderer::get() noexcept
    {
        return this->m_renerer;
    }
}