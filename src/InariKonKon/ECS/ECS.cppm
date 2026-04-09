module;

export module ECS;

import Singleton;

export namespace ikk
{
    class ECS final : public Singleton<ECS>
    {
        friend class Singleton<ECS>;

        ECS() noexcept = default;
    public:
    private:
    };

    ECS& ECS = ECS::getInstance();
}

namespace ikk
{
}