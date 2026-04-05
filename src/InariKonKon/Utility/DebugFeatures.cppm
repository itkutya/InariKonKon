export module DebugFeatures;

export namespace ikk
{
    inline constexpr bool isDebug() noexcept
    {
#ifndef NDEBUG
        return true;
#else
        return false;
#endif
    }

    inline constexpr bool isRelease() noexcept
    {
        return !isDebug();
    }
}