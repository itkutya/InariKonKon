module;

#include <optional>
#include <memory>

export module ECS:EntityHandle;

import :Entity;

import StableIndexVector;

export namespace ikk
{
    class [[nodiscard]] EntityHandle final
    {
    public:
        [[nodiscard]] EntityHandle(std::size_t index, std::size_t validityID, StableIndexVector<Entity>* data) noexcept;

        EntityHandle(const EntityHandle&) noexcept = default;
        EntityHandle(EntityHandle&&) noexcept = default;

        EntityHandle& operator=(const EntityHandle&) noexcept = default;
        EntityHandle& operator=(EntityHandle&&) noexcept = default;

        ~EntityHandle() noexcept = default;

        [[nodiscard]] std::optional<Entity*> get() const noexcept;

        [[nodiscard]] bool isValid() const noexcept;
    private:
        std::size_t m_index;
        std::size_t m_validityID;
        StableIndexVector<Entity>* m_data;

        friend class ECS;
        friend class StableIndexVector<Entity>;
    };
}

namespace ikk
{
    EntityHandle::EntityHandle(std::size_t index, std::size_t validityID, StableIndexVector<Entity>* data) noexcept
        : m_index(index), m_validityID(validityID), m_data(data)
    {
    }

    std::optional<Entity*> EntityHandle::get() const noexcept
    {
        if (this->m_data == nullptr || this->isValid() == false) return std::nullopt;
        return &this->m_data->at(this->m_index);
    }

    bool EntityHandle::isValid() const noexcept
    {
        if (this->m_data == nullptr) return false;
        return this->m_data->isValid(this->m_index, this->m_validityID);
    }
}
