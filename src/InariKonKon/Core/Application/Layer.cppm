module;

#include <type_traits>

export module Core:Layer;

import :Window;
import :Event;

import Time;

export namespace ikk
{
    class Layer
    {
    public:
        Layer() noexcept = default;

        Layer(const Layer&) noexcept = default;
        Layer(Layer&&) noexcept = default;

        Layer& operator=(const Layer&) noexcept = default;
        Layer& operator=(Layer&&) noexcept = default;

        virtual ~Layer() noexcept = default;

        virtual void onEvent(const Event& event) noexcept = 0;
        virtual void onUpdate(const Time& dt) noexcept = 0;
        virtual void onRender(const Window& window) const noexcept = 0;
    private:
    };

    template<class T>
    concept LayerType = std::is_base_of<Layer, T>::value;
}