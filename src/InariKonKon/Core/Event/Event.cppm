module;

#include <type_traits>
#include <filesystem>
#include <optional>
#include <variant>
#include <vector>

export module Core:Event;

import :EventCallback;
import :EventListener;
import :Keyboard;
import :Joystick;
import :Mouse;
import :Input;

import NonConstructible;
import Flag;
import Vec;

template<typename T, typename Variant>
struct isVariantMember;

template<typename T, typename... Ts>
struct isVariantMember<T, std::variant<Ts...>> : std::disjunction<std::is_same<T, Ts>...> {};

export namespace ikk
{
    class Monitor;
    class Window;

    class [[nodiscard]] Event final
    {
    public:
        struct Window final : public NonConstructible
        {
            struct Closed
            {
                ikk::Window* window = nullptr;
            };

            struct Resized
            {
                ikk::Window* window = nullptr;
                std::uint32_t width = 0u;
                std::uint32_t height = 0u;
            };

            struct FramebufferResized
            {
                ikk::Window* window = nullptr;
                std::uint32_t width = 0u;
                std::uint32_t height = 0u;
            };

            struct Position
            {
                ikk::Window* window = nullptr;
                Vec2i position = {};
            };

            struct UnIconified
            {
                ikk::Window* window = nullptr;
            };

            struct Iconified
            {
                ikk::Window* window = nullptr;
            };

            struct Minimized
            {
                ikk::Window* window = nullptr;
            };

            struct Maximized
            {
                ikk::Window* window = nullptr;
            };

            struct FocusLost
            {
                ikk::Window* window = nullptr;
            };

            struct FocusGained
            {
                ikk::Window* window = nullptr;
            };

            struct CursorEntered
            {
                ikk::Window* window = nullptr;
            };

            struct CursorLeft
            {
                ikk::Window* window = nullptr;
            };

            struct ContentScale
            {
                ikk::Window* window = nullptr;
                Vec2f scale = {};
            };

            struct Refreshed
            {
                ikk::Window* window = nullptr;
            };

            struct FileDropped
            {
                ikk::Window* window = nullptr;
                std::vector<std::filesystem::path> paths = {};
            };
        };

        struct Monitor final : public NonConstructible
        {
            struct Connected
            {
                ikk::Monitor* monitor = nullptr;
            };

            struct Disconnected
            {
                ikk::Monitor* monitor = nullptr;
            };
        };

        struct Input final : public NonConstructible
        {
            struct Text
            {
                char32_t unicode;
            };

            struct Keyboard
            {
                ikk::Keyboard::KeyCode  keycode;
                ikk::Keyboard::ScanCode scancode;
                ikk::Input::Action       state;
            };

            struct Mouse final : public NonConstructible
            {
                struct Button
                {
                    ikk::Mouse::Button  button;
                    ikk::Input::Action   state;
                };

                struct Wheel
                {
                    ikk::Mouse::Wheel   wheel;
                    double              delta;
                };

                struct Move
                {
                    Vec2d position;
                };
            };

            struct Joystick final : public NonConstructible
            {
                struct Connected
                {
                    ikk::Joystick::ID id;
                };

                struct Disconnected
                {
                    ikk::Joystick::ID id;
                };

                struct Button
                {
                    ikk::Joystick::ID       id;
                    ikk::Joystick::Button   button;
                    ikk::Input::Action       state;
                };

                struct Axis
                {
                    ikk::Joystick::ID   id;
                    ikk::Joystick::Axis axis;
                    ikk::Input::Action   state;
                };

                struct Hat
                {
                    ikk::Joystick::ID           id;
                    Flag<ikk::Joystick::Hat>    hat;
                    ikk::Input::Action           state;
                };
            };
        };

        using Types = std::variant<
            Window::Closed,
            Window::Resized,
            Window::FramebufferResized,
            Window::Position,
            Window::UnIconified,
            Window::Iconified,
            Window::Minimized,
            Window::Maximized,
            Window::FocusLost,
            Window::FocusGained,
            Window::CursorEntered,
            Window::CursorLeft,
            Window::ContentScale,
            Window::Refreshed,
            Window::FileDropped,
            Monitor::Connected,
            Monitor::Disconnected,
            Input::Text,
            Input::Keyboard,
            Input::Mouse::Button,
            Input::Mouse::Wheel,
            Input::Mouse::Move,
            Input::Joystick::Connected,
            Input::Joystick::Disconnected,
            Input::Joystick::Button,
            Input::Joystick::Axis,
            Input::Joystick::Hat>;

        template<class T> requires (isVariantMember<std::decay_t<T>, Types>::value == true)
        [[nodiscard]] Event(T&& type) noexcept;

        Event(const Event&) noexcept = default;
        Event(Event&&) noexcept = default;

        Event& operator=(const Event&) noexcept = default;
        Event& operator=(Event&&) noexcept = default;

        ~Event() noexcept = default;

        template<class T> requires (isVariantMember<std::decay_t<T>, Types>::value == true)
        [[nodiscard]] bool is() const noexcept;

        template<class T> requires (isVariantMember<std::decay_t<T>, Types>::value == true)
        [[nodiscard]] std::optional<T> get() const noexcept;
    private:
        Types m_data;

        void notify() const noexcept;
    };

    using WindowEvent = Event::Window;
    using InputEvent = Event::Input;
}

namespace ikk
{
    template<class T> requires (isVariantMember<std::decay_t<T>, Event::Types>::value == true)
    Event::Event(T&& type) noexcept
        : m_data(std::forward<T>(type))
    {
        this->notify();
    }

    template<class T> requires (isVariantMember<std::decay_t<T>, Event::Types>::value == true)
    bool Event::is() const noexcept
    {
        return std::holds_alternative<T>(this->m_data);
    }

    template<class T> requires (isVariantMember<std::decay_t<T>, Event::Types>::value == true)
    std::optional<T> Event::get() const noexcept
    {
        if (this->is<T>())
            return std::optional<T>{ std::get<T>(this->m_data) };
        return std::optional<T>{ std::nullopt };
    }

    void Event::notify() const noexcept
    {
        static const auto dispatchEvent = []<class T>(const T& event) noexcept requires (isVariantMember<std::decay_t<T>, Event::Types>::value == true)
        {
            for (EventListener<T>* listener : EventListener<T>::getListeners())
                listener->onEvent(event);

            for (const typename EventCallback<T>::CallbackFunc& callback : EventCallback<T>::getCallbacks())
                callback(event);
        };
        std::visit(dispatchEvent, this->m_data);
    }
}