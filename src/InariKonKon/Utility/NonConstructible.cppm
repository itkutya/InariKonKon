export module NonConstructible;

import NonCopyable;
import NonMovable;

export namespace ikk
{
    class NonConstructible : public NonCopyable, public NonMovable
    {
    public:
        constexpr NonConstructible() noexcept = delete;

        virtual constexpr ~NonConstructible() noexcept = default;
    private:
    };
}