module;

#include <cstdint>

export module Core:Renderer;

export namespace ikk
{
    class Renderer
    {
    public:
        enum struct [[nodiscard]] Type : std::uint8_t
        {
            None, Vulkan
        };

        virtual ~Renderer() noexcept = default;

        [[nodiscard]] virtual bool isValid() const noexcept = 0;
    protected:
        Renderer() noexcept = default;

        Renderer(const Renderer&) noexcept = default;
        Renderer(Renderer&&) noexcept = default;

        Renderer& operator=(const Renderer&) noexcept = default;
        Renderer& operator=(Renderer&&) noexcept = default;
    private:
    };
}