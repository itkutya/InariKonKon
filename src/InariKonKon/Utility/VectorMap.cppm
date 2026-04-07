module;

#include <utility>
#include <vector>
#include <ranges>

export module VectorMap;

export namespace ikk
{
    template<class Key, class T>
    class VectorMap final
    {
    public:
        VectorMap() = default;

        VectorMap(const VectorMap&) = default;
        VectorMap(VectorMap&&) = default;

        VectorMap& operator=(const VectorMap&) = default;
        VectorMap& operator=(VectorMap&&) = default;

        ~VectorMap() = default;

        void insert(const Key& key, const T& value) noexcept;
        void remove(const Key& key) noexcept;

        bool contains(const Key& key) const noexcept;

        const T* find(const Key& key) const noexcept;
        T* find(const Key& key) noexcept;

        auto begin() const noexcept;
        auto begin() noexcept;

        auto end() const noexcept;
        auto end() noexcept;
    private:
        std::vector<std::pair<Key, T>> m_storage;
    };
}

namespace ikk
{
    template<class Key, class T>
    void VectorMap<Key, T>::insert(const Key& key, const T& value) noexcept
    {
        if (this->contains(key) == true) return;
        this->m_storage.emplace_back(std::make_pair(key, value));
    }

    template<class Key, class T>
    void VectorMap<Key, T>::remove(const Key& key) noexcept
    {
        std::erase_if(this->m_storage, [&key](const auto& pair) { return pair.first == key; });
    }

    template<class Key, class T>
    bool VectorMap<Key, T>::contains(const Key& key) const noexcept
    {
        return std::ranges::find_if(this->m_storage, [&key](const auto& pair){ return pair.first == key; }) != this->m_storage.end();
    }

    template<class Key, class T>
    const T* VectorMap<Key, T>::find(const Key& key) const noexcept
    {
        auto it = std::ranges::find_if(this->m_storage, [&key](const auto& pair) { return pair.first == key; });
        if (it == this->m_storage.end()) return nullptr;
        else return &it->second;
    }

    template<class Key, class T>
    T* VectorMap<Key, T>::find(const Key& key) noexcept
    {
        auto it = std::ranges::find_if(this->m_storage, [&key](const auto& pair) { return pair.first == key; });
        if (it == this->m_storage.end()) return nullptr;
        else return &it->second;
    }

    template<class Key, class T>
    auto VectorMap<Key, T>::begin() const noexcept
    {
        return this->m_storage.begin();
    }

    template<class Key, class T>
    auto VectorMap<Key, T>::begin() noexcept
    {
        return this->m_storage.begin();
    }

    template<class Key, class T>
    auto VectorMap<Key, T>::end() const noexcept
    {
        return this->m_storage.end();
    }

    template<class Key, class T>
    auto VectorMap<Key, T>::end() noexcept
    {
        return this->m_storage.end();
    }
}