module;

#include <utility>
#include <vector>

export module VectorMap;

export namespace ikk
{
    template<class T, class Key>
    class VectorMap
    {
    public:
        VectorMap() = default;

        VectorMap(const VectorMap&) = default;
        VectorMap(VectorMap&&) = default;
        VectorMap& operator=(const VectorMap&) = default;
        VectorMap& operator=(VectorMap&&) = default;

        virtual ~VectorMap() = default;
    private:
        std::vector<std::pair<T, Key>> m_storage;
    };
}

namespace ikk
{
}
