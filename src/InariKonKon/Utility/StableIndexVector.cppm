module;

#include <cstddef>
#include <vector>

export module StableIndexVector;

export namespace ikk
{
    template<class T>
    class [[nodiscard]] StableIndexVector final
    {
    public:
        [[nodiscard]] StableIndexVector() noexcept = default;

        StableIndexVector(const StableIndexVector&) noexcept = default;
        StableIndexVector(StableIndexVector&&) noexcept = default;

        StableIndexVector& operator=(const StableIndexVector&) noexcept = default;
        StableIndexVector& operator=(StableIndexVector&&) noexcept = default;

        ~StableIndexVector() noexcept = default;

        [[nodiscard]] std::size_t insert(const T& value) noexcept;
        template<class... Args>
        [[nodiscard]] std::size_t emplace(Args&&... args) noexcept;

        void erase(std::size_t index) noexcept;

        const T& at(std::size_t index) const noexcept;
        T& at(std::size_t index) noexcept;

        [[nodiscard]] std::size_t getValidityID(std::size_t index) const noexcept;
        [[nodiscard]] bool isValid(std::size_t index, std::size_t validityID) const noexcept;

        [[nodiscard]] auto begin() const noexcept;
        [[nodiscard]] auto begin() noexcept;

        [[nodiscard]] auto end() const noexcept;
        [[nodiscard]] auto end() noexcept;
    private:
        struct Metadata
        {
            std::size_t rid = 0;
            std::size_t validity_id = 0;
        };

        std::vector<T> m_data;
        std::vector<Metadata> m_metadata;
        std::vector<std::size_t> m_indexes;

        std::size_t getFreeSlot() noexcept;
        std::size_t getFreeID() noexcept;
    };
}

namespace ikk
{
    template<class T>
    std::size_t StableIndexVector<T>::insert(const T& value) noexcept
    {
        const std::size_t id = this->getFreeSlot();
        this->m_data.emplace_back(value);
        return id;
    }

    template<class T>
    template<class... Args>
    std::size_t StableIndexVector<T>::emplace(Args&&... args) noexcept
    {
        const std::size_t id = this->getFreeSlot();
        this->m_data.emplace_back(std::forward<Args>(args)...);
        return id;
    }

    template<class T>
    void StableIndexVector<T>::erase(std::size_t index) noexcept
    {
        const std::size_t data_id      = this->m_indexes[index];
        const std::size_t last_data_id = this->m_data.size() - 1;
        const std::size_t last_id      = this->m_metadata[last_data_id].rid;

        ++this->m_metadata[data_id].validity_id;

        std::swap(this->m_data[data_id], this->m_data[last_data_id]);
        std::swap(this->m_metadata[data_id], this->m_metadata[last_data_id]);
        std::swap(this->m_indexes[index], this->m_indexes[last_id]);

        this->m_data.pop_back();
    }

    template<class T>
    const T& StableIndexVector<T>::at(std::size_t index) const noexcept
    {
        return this->m_data.at(this->m_indexes.at(index));
    }

    template<class T>
    T& StableIndexVector<T>::at(std::size_t index) noexcept
    {
        return this->m_data.at(this->m_indexes.at(index));
    }

    template<class T>
    std::size_t StableIndexVector<T>::getValidityID(std::size_t index) const noexcept
    {
        return this->m_metadata[this->m_indexes[index]].validity_id;
    }

    template<class T>
    bool StableIndexVector<T>::isValid(std::size_t index, std::size_t validityID) const noexcept
    {
        return validityID == this->m_metadata[this->m_indexes[index]].validity_id;
    }

    template<class T>
    auto StableIndexVector<T>::begin() const noexcept
    {
        return this->m_data.begin();
    }

    template<class T>
    auto StableIndexVector<T>::begin() noexcept
    {
        return this->m_data.begin();
    }

    template<class T>
    auto StableIndexVector<T>::end() const noexcept
    {
        return this->m_data.end();
    }

    template<class T>
    auto StableIndexVector<T>::end() noexcept
    {
        return this->m_data.end();
    }

    template<class T>
    std::size_t StableIndexVector<T>::getFreeSlot() noexcept
    {
        const std::size_t id = this->getFreeID();
        this->m_indexes[id] = this->m_data.size();
        return id;
    }

    template<class T>
    std::size_t StableIndexVector<T>::getFreeID() noexcept
    {
        if (this->m_metadata.size() > this->m_data.size())
        {
            ++this->m_metadata[this->m_data.size()].validity_id;
            return this->m_metadata[this->m_data.size()].rid;
        }
        const std::size_t new_id = this->m_data.size();
        this->m_metadata.emplace_back(new_id, 0 );
        this->m_indexes.emplace_back(new_id);
        return new_id;
    }
}