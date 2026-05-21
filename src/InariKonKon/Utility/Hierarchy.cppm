module;

#include <vector>
#include <ranges>

export module Hierarchy;

export namespace ikk
{
    template<class T>
    class Hierarchy
    {
    public:
        virtual ~Hierarchy() noexcept = default;

        const T* getParent() const noexcept;
        const std::vector<T*>& getChildren() const noexcept;

        void setParent(T& parent) noexcept;
        void removeParent() noexcept;

        void addChild(T& child) noexcept;
        void removeChild(T& child) noexcept;
    protected:
        Hierarchy() noexcept;

        Hierarchy(const Hierarchy&) noexcept = default;
        Hierarchy(Hierarchy&&) noexcept = default;

        Hierarchy& operator=(const Hierarchy&) noexcept = default;
        Hierarchy& operator=(Hierarchy&&) noexcept = default;

        T* getParent() noexcept;
        std::vector<T*>& getChildren() noexcept;
    private:
        T* m_parent = nullptr;
        std::vector<T*> m_children;

        const T& self() const noexcept;
        T& self() noexcept;
    };
}

namespace ikk
{
    template<class T>
    Hierarchy<T>::Hierarchy() noexcept
    {
        static_assert(std::derived_from<T, Hierarchy<T>>);
    }

    template<class T>
    const T* Hierarchy<T>::getParent() const noexcept
    {
        return this->m_parent;
    }

    template<class T>
    T* Hierarchy<T>::getParent() noexcept
    {
        return this->m_parent;
    }

    template<class T>
    std::vector<T*>& Hierarchy<T>::getChildren() noexcept
    {
        return this->m_children;
    }

    template<class T>
    const std::vector<T*>& Hierarchy<T>::getChildren() const noexcept
    {
        return this->m_children;
    }

    template<class T>
    void Hierarchy<T>::setParent(T& parent) noexcept
    {
        if (this->m_parent == &parent) return;

        for (T* p = &parent; p != nullptr; p = p->getParent())
            if (p == &this->self()) return;

        if (this->m_parent != nullptr)
            static_cast<Hierarchy<T>*>(this->m_parent)->removeChild(this->self());
        this->m_parent = &parent;
        parent.addChild(this->self());
    }

    template<class T>
    void Hierarchy<T>::removeParent() noexcept
    {
        if (this->m_parent != nullptr)
            static_cast<Hierarchy<T>*>(this->m_parent)->removeChild(this->self());
        this->m_parent = nullptr;
    }

    template<class T>
    void Hierarchy<T>::addChild(T& child) noexcept
    {
        if (std::ranges::find(this->m_children, &child) == this->m_children.end())
        {
            if (child.getParent() != nullptr)
                static_cast<Hierarchy<T>*>(&child)->removeParent();

            static_cast<Hierarchy<T>*>(&child)->m_parent = &this->self();
            this->m_children.emplace_back(&child);
        }
    }

    template<class T>
    void Hierarchy<T>::removeChild(T& child) noexcept
    {
        if (auto it = std::ranges::find(this->m_children, &child); it != this->m_children.end())
        {
            static_cast<Hierarchy<T>*>(*it)->m_parent = nullptr;
            this->m_children.erase(it);
        }
    }

    template<class T>
    const T& Hierarchy<T>::self() const noexcept
    {
        return *static_cast<const T*>(this);
    }

    template<class T>
    T& Hierarchy<T>::self() noexcept
    {
        return *static_cast<T*>(this);
    }
}
