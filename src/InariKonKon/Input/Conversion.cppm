module;

#include <cstdint>

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

export module Conversion;

import NonConstructible;
import Input;

export namespace ikk
{
    //TODO: Rename to something else...
    class Conversion : public NonConstructible
    {
    public:
        [[nodiscard]] static constexpr Input::State fromGLFWAction(std::int32_t action) noexcept;
        [[nodiscard]] static constexpr std::int32_t toGLFWAction(Input::State type) noexcept;

        [[nodiscard]] static constexpr std::int32_t toGLFWKeyCode(Keyboard::KeyCode keycode) noexcept;
        [[nodiscard]] static constexpr Keyboard::KeyCode fromGLFWKeyCode(std::int32_t keycode) noexcept;

        [[nodiscard]] static constexpr std::int32_t toGLFWButton(Mouse::Button button) noexcept;
        [[nodiscard]] static constexpr Mouse::Button fromGLFWButton(std::int32_t button) noexcept;
    };
}

namespace ikk
{
    constexpr Input::State Conversion::fromGLFWAction(std::int32_t action) noexcept
    {
        switch (action)
        {
            case GLFW_PRESS:    return Input::State::Press;
            case GLFW_RELEASE:  return Input::State::Release;
            case GLFW_REPEAT:   return Input::State::Repeat;
            default:            return Input::State::Unknown;
        }
    }

    constexpr std::int32_t Conversion::toGLFWAction(Input::State type) noexcept
    {
        switch (type)
        {
            case Input::State::Unknown:    return GLFW_KEY_UNKNOWN;
            case Input::State::Press:      return GLFW_PRESS;
            case Input::State::Release:    return GLFW_RELEASE;
            case Input::State::Repeat:     return GLFW_REPEAT;
        }
        return GLFW_KEY_UNKNOWN;
    }

    constexpr std::int32_t Conversion::toGLFWKeyCode(Keyboard::KeyCode keycode) noexcept
    {
        switch (keycode)
        {
            case Keyboard::KeyCode::Unknown:              return GLFW_KEY_UNKNOWN;
            case Keyboard::KeyCode::A:                    return GLFW_KEY_A;
            case Keyboard::KeyCode::B:                    return GLFW_KEY_B;
            case Keyboard::KeyCode::C:                    return GLFW_KEY_C;
            case Keyboard::KeyCode::D:                    return GLFW_KEY_D;
            case Keyboard::KeyCode::E:                    return GLFW_KEY_E;
            case Keyboard::KeyCode::F:                    return GLFW_KEY_F;
            case Keyboard::KeyCode::G:                    return GLFW_KEY_G;
            case Keyboard::KeyCode::H:                    return GLFW_KEY_H;
            case Keyboard::KeyCode::I:                    return GLFW_KEY_I;
            case Keyboard::KeyCode::J:                    return GLFW_KEY_J;
            case Keyboard::KeyCode::K:                    return GLFW_KEY_K;
            case Keyboard::KeyCode::L:                    return GLFW_KEY_L;
            case Keyboard::KeyCode::M:                    return GLFW_KEY_M;
            case Keyboard::KeyCode::N:                    return GLFW_KEY_N;
            case Keyboard::KeyCode::O:                    return GLFW_KEY_O;
            case Keyboard::KeyCode::P:                    return GLFW_KEY_P;
            case Keyboard::KeyCode::Q:                    return GLFW_KEY_Q;
            case Keyboard::KeyCode::R:                    return GLFW_KEY_R;
            case Keyboard::KeyCode::S:                    return GLFW_KEY_S;
            case Keyboard::KeyCode::T:                    return GLFW_KEY_T;
            case Keyboard::KeyCode::U:                    return GLFW_KEY_U;
            case Keyboard::KeyCode::V:                    return GLFW_KEY_V;
            case Keyboard::KeyCode::W:                    return GLFW_KEY_W;
            case Keyboard::KeyCode::X:                    return GLFW_KEY_X;
            case Keyboard::KeyCode::Y:                    return GLFW_KEY_Y;
            case Keyboard::KeyCode::Z:                    return GLFW_KEY_Z;
            case Keyboard::KeyCode::Num1:                 return GLFW_KEY_1;
            case Keyboard::KeyCode::Num2:                 return GLFW_KEY_2;
            case Keyboard::KeyCode::Num3:                 return GLFW_KEY_3;
            case Keyboard::KeyCode::Num4:                 return GLFW_KEY_4;
            case Keyboard::KeyCode::Num5:                 return GLFW_KEY_5;
            case Keyboard::KeyCode::Num6:                 return GLFW_KEY_6;
            case Keyboard::KeyCode::Num7:                 return GLFW_KEY_7;
            case Keyboard::KeyCode::Num8:                 return GLFW_KEY_8;
            case Keyboard::KeyCode::Num9:                 return GLFW_KEY_9;
            case Keyboard::KeyCode::Num0:                 return GLFW_KEY_0;
            case Keyboard::KeyCode::Enter:                return GLFW_KEY_ENTER;
            case Keyboard::KeyCode::Escape:               return GLFW_KEY_ESCAPE;
            case Keyboard::KeyCode::Backspace:            return GLFW_KEY_BACKSPACE;
            case Keyboard::KeyCode::Tab:                  return GLFW_KEY_TAB;
            case Keyboard::KeyCode::Space:                return GLFW_KEY_SPACE;
            case Keyboard::KeyCode::Hyphen:               return GLFW_KEY_MINUS;
            case Keyboard::KeyCode::Equal:                return GLFW_KEY_EQUAL;
            case Keyboard::KeyCode::LBracket:             return GLFW_KEY_LEFT_BRACKET;
            case Keyboard::KeyCode::RBracket:             return GLFW_KEY_RIGHT_BRACKET;
            case Keyboard::KeyCode::Backslash:            return GLFW_KEY_BACKSLASH;
            case Keyboard::KeyCode::Semicolon:            return GLFW_KEY_SEMICOLON;
            case Keyboard::KeyCode::Apostrophe:           return GLFW_KEY_APOSTROPHE;
            case Keyboard::KeyCode::Grave:                return GLFW_KEY_GRAVE_ACCENT;
            case Keyboard::KeyCode::Comma:                return GLFW_KEY_COMMA;
            case Keyboard::KeyCode::Period:               return GLFW_KEY_PERIOD;
            case Keyboard::KeyCode::Slash:                return GLFW_KEY_SLASH;
            case Keyboard::KeyCode::F1:                   return GLFW_KEY_F1;
            case Keyboard::KeyCode::F2:                   return GLFW_KEY_F2;
            case Keyboard::KeyCode::F3:                   return GLFW_KEY_F3;
            case Keyboard::KeyCode::F4:                   return GLFW_KEY_F4;
            case Keyboard::KeyCode::F5:                   return GLFW_KEY_F5;
            case Keyboard::KeyCode::F6:                   return GLFW_KEY_F6;
            case Keyboard::KeyCode::F7:                   return GLFW_KEY_F7;
            case Keyboard::KeyCode::F8:                   return GLFW_KEY_F8;
            case Keyboard::KeyCode::F9:                   return GLFW_KEY_F9;
            case Keyboard::KeyCode::F10:                  return GLFW_KEY_F10;
            case Keyboard::KeyCode::F11:                  return GLFW_KEY_F11;
            case Keyboard::KeyCode::F12:                  return GLFW_KEY_F12;
            case Keyboard::KeyCode::F13:                  return GLFW_KEY_F13;
            case Keyboard::KeyCode::F14:                  return GLFW_KEY_F14;
            case Keyboard::KeyCode::F15:                  return GLFW_KEY_F15;
            case Keyboard::KeyCode::F16:                  return GLFW_KEY_F16;
            case Keyboard::KeyCode::F17:                  return GLFW_KEY_F17;
            case Keyboard::KeyCode::F18:                  return GLFW_KEY_F18;
            case Keyboard::KeyCode::F19:                  return GLFW_KEY_F19;
            case Keyboard::KeyCode::F20:                  return GLFW_KEY_F20;
            case Keyboard::KeyCode::F21:                  return GLFW_KEY_F21;
            case Keyboard::KeyCode::F22:                  return GLFW_KEY_F22;
            case Keyboard::KeyCode::F23:                  return GLFW_KEY_F23;
            case Keyboard::KeyCode::F24:                  return GLFW_KEY_F24;
            case Keyboard::KeyCode::CapsLock:             return GLFW_KEY_CAPS_LOCK;
            case Keyboard::KeyCode::PrintScreen:          return GLFW_KEY_PRINT_SCREEN;
            case Keyboard::KeyCode::ScrollLock:           return GLFW_KEY_SCROLL_LOCK;
            case Keyboard::KeyCode::Pause:                return GLFW_KEY_PAUSE;
            case Keyboard::KeyCode::Insert:               return GLFW_KEY_INSERT;
            case Keyboard::KeyCode::Home:                 return GLFW_KEY_HOME;
            case Keyboard::KeyCode::PageUp:               return GLFW_KEY_PAGE_UP;
            case Keyboard::KeyCode::Delete:               return GLFW_KEY_DELETE;
            case Keyboard::KeyCode::End:                  return GLFW_KEY_END;
            case Keyboard::KeyCode::PageDown:             return GLFW_KEY_PAGE_DOWN;
            case Keyboard::KeyCode::Right:                return GLFW_KEY_RIGHT;
            case Keyboard::KeyCode::Left:                 return GLFW_KEY_LEFT;
            case Keyboard::KeyCode::Down:                 return GLFW_KEY_DOWN;
            case Keyboard::KeyCode::Up:                   return GLFW_KEY_UP;
            case Keyboard::KeyCode::NumLock:              return GLFW_KEY_NUM_LOCK;
            case Keyboard::KeyCode::NumpadDivide:         return GLFW_KEY_KP_DIVIDE;
            case Keyboard::KeyCode::NumpadMultiply:       return GLFW_KEY_KP_MULTIPLY;
            case Keyboard::KeyCode::NumpadMinus:          return GLFW_KEY_KP_SUBTRACT;
            case Keyboard::KeyCode::NumpadPlus:           return GLFW_KEY_KP_ADD;
            case Keyboard::KeyCode::NumpadEqual:          return GLFW_KEY_KP_EQUAL;
            case Keyboard::KeyCode::NumpadEnter:          return GLFW_KEY_KP_ENTER;
            case Keyboard::KeyCode::NumpadDecimal:        return GLFW_KEY_KP_DECIMAL;
            case Keyboard::KeyCode::Numpad1:              return GLFW_KEY_KP_1;
            case Keyboard::KeyCode::Numpad2:              return GLFW_KEY_KP_2;
            case Keyboard::KeyCode::Numpad3:              return GLFW_KEY_KP_3;
            case Keyboard::KeyCode::Numpad4:              return GLFW_KEY_KP_4;
            case Keyboard::KeyCode::Numpad5:              return GLFW_KEY_KP_5;
            case Keyboard::KeyCode::Numpad6:              return GLFW_KEY_KP_6;
            case Keyboard::KeyCode::Numpad7:              return GLFW_KEY_KP_7;
            case Keyboard::KeyCode::Numpad8:              return GLFW_KEY_KP_8;
            case Keyboard::KeyCode::Numpad9:              return GLFW_KEY_KP_9;
            case Keyboard::KeyCode::Numpad0:              return GLFW_KEY_KP_0;
            case Keyboard::KeyCode::Menu:                 return GLFW_KEY_MENU;
            case Keyboard::KeyCode::LControl:             return GLFW_KEY_LEFT_CONTROL;
            case Keyboard::KeyCode::LShift:               return GLFW_KEY_LEFT_SHIFT;
            case Keyboard::KeyCode::LAlt:                 return GLFW_KEY_LEFT_ALT;
            case Keyboard::KeyCode::LSystem:              return GLFW_KEY_LEFT_SUPER;
            case Keyboard::KeyCode::RControl:             return GLFW_KEY_RIGHT_CONTROL;
            case Keyboard::KeyCode::RShift:               return GLFW_KEY_RIGHT_SHIFT;
            case Keyboard::KeyCode::RAlt:                 return GLFW_KEY_RIGHT_ALT;
            case Keyboard::KeyCode::RSystem:              return GLFW_KEY_RIGHT_SUPER;
            case Keyboard::KeyCode::LaunchApplication1:   return GLFW_KEY_WORLD_1;
            case Keyboard::KeyCode::LaunchApplication2:   return GLFW_KEY_WORLD_2;
        }
        return GLFW_KEY_UNKNOWN;
    }

    constexpr Keyboard::KeyCode Conversion::fromGLFWKeyCode(std::int32_t keycode) noexcept
    {
        switch (keycode)
        {
            case GLFW_KEY_UNKNOWN:              return Keyboard::KeyCode::Unknown;
            case GLFW_KEY_A:                    return Keyboard::KeyCode::A;
            case GLFW_KEY_B:                    return Keyboard::KeyCode::B;
            case GLFW_KEY_C:                    return Keyboard::KeyCode::C;
            case GLFW_KEY_D:                    return Keyboard::KeyCode::D;
            case GLFW_KEY_E:                    return Keyboard::KeyCode::E;
            case GLFW_KEY_F:                    return Keyboard::KeyCode::F;
            case GLFW_KEY_G:                    return Keyboard::KeyCode::G;
            case GLFW_KEY_H:                    return Keyboard::KeyCode::H;
            case GLFW_KEY_I:                    return Keyboard::KeyCode::I;
            case GLFW_KEY_J:                    return Keyboard::KeyCode::J;
            case GLFW_KEY_K:                    return Keyboard::KeyCode::K;
            case GLFW_KEY_L:                    return Keyboard::KeyCode::L;
            case GLFW_KEY_M:                    return Keyboard::KeyCode::M;
            case GLFW_KEY_N:                    return Keyboard::KeyCode::N;
            case GLFW_KEY_O:                    return Keyboard::KeyCode::O;
            case GLFW_KEY_P:                    return Keyboard::KeyCode::P;
            case GLFW_KEY_Q:                    return Keyboard::KeyCode::Q;
            case GLFW_KEY_R:                    return Keyboard::KeyCode::R;
            case GLFW_KEY_S:                    return Keyboard::KeyCode::S;
            case GLFW_KEY_T:                    return Keyboard::KeyCode::T;
            case GLFW_KEY_U:                    return Keyboard::KeyCode::U;
            case GLFW_KEY_V:                    return Keyboard::KeyCode::V;
            case GLFW_KEY_W:                    return Keyboard::KeyCode::W;
            case GLFW_KEY_X:                    return Keyboard::KeyCode::X;
            case GLFW_KEY_Y:                    return Keyboard::KeyCode::Y;
            case GLFW_KEY_Z:                    return Keyboard::KeyCode::Z;
            case GLFW_KEY_1:                    return Keyboard::KeyCode::Num1;
            case GLFW_KEY_2:                    return Keyboard::KeyCode::Num2;
            case GLFW_KEY_5:                    return Keyboard::KeyCode::Num5;
            case GLFW_KEY_3:                    return Keyboard::KeyCode::Num3;
            case GLFW_KEY_6:                    return Keyboard::KeyCode::Num6;
            case GLFW_KEY_4:                    return Keyboard::KeyCode::Num4;
            case GLFW_KEY_7:                    return Keyboard::KeyCode::Num7;
            case GLFW_KEY_8:                    return Keyboard::KeyCode::Num8;
            case GLFW_KEY_9:                    return Keyboard::KeyCode::Num9;
            case GLFW_KEY_0:                    return Keyboard::KeyCode::Num0;
            case GLFW_KEY_ENTER:                return Keyboard::KeyCode::Enter;
            case GLFW_KEY_ESCAPE:               return Keyboard::KeyCode::Escape;
            case GLFW_KEY_BACKSPACE:            return Keyboard::KeyCode::Backspace;
            case GLFW_KEY_TAB:                  return Keyboard::KeyCode::Tab;
            case GLFW_KEY_SPACE:                return Keyboard::KeyCode::Space;
            case GLFW_KEY_MINUS:                return Keyboard::KeyCode::Hyphen;
            case GLFW_KEY_EQUAL:                return Keyboard::KeyCode::Equal;
            case GLFW_KEY_LEFT_BRACKET:         return Keyboard::KeyCode::LBracket;
            case GLFW_KEY_RIGHT_BRACKET:        return Keyboard::KeyCode::RBracket;
            case GLFW_KEY_BACKSLASH:            return Keyboard::KeyCode::Backslash;
            case GLFW_KEY_SEMICOLON:            return Keyboard::KeyCode::Semicolon;
            case GLFW_KEY_APOSTROPHE:           return Keyboard::KeyCode::Apostrophe;
            case GLFW_KEY_GRAVE_ACCENT:         return Keyboard::KeyCode::Grave;
            case GLFW_KEY_COMMA:                return Keyboard::KeyCode::Comma;
            case GLFW_KEY_PERIOD:               return Keyboard::KeyCode::Period;
            case GLFW_KEY_SLASH:                return Keyboard::KeyCode::Slash;
            case GLFW_KEY_F1:                   return Keyboard::KeyCode::F1;
            case GLFW_KEY_F2:                   return Keyboard::KeyCode::F2;
            case GLFW_KEY_F3:                   return Keyboard::KeyCode::F3;
            case GLFW_KEY_F4:                   return Keyboard::KeyCode::F4;
            case GLFW_KEY_F5:                   return Keyboard::KeyCode::F5;
            case GLFW_KEY_F6:                   return Keyboard::KeyCode::F6;
            case GLFW_KEY_F7:                   return Keyboard::KeyCode::F7;
            case GLFW_KEY_F8:                   return Keyboard::KeyCode::F8;
            case GLFW_KEY_F9:                   return Keyboard::KeyCode::F9;
            case GLFW_KEY_F10:                  return Keyboard::KeyCode::F10;
            case GLFW_KEY_F11:                  return Keyboard::KeyCode::F11;
            case GLFW_KEY_F12:                  return Keyboard::KeyCode::F12;
            case GLFW_KEY_F13:                  return Keyboard::KeyCode::F13;
            case GLFW_KEY_F14:                  return Keyboard::KeyCode::F14;
            case GLFW_KEY_F15:                  return Keyboard::KeyCode::F15;
            case GLFW_KEY_F16:                  return Keyboard::KeyCode::F16;
            case GLFW_KEY_F17:                  return Keyboard::KeyCode::F17;
            case GLFW_KEY_F18:                  return Keyboard::KeyCode::F18;
            case GLFW_KEY_F19:                  return Keyboard::KeyCode::F19;
            case GLFW_KEY_F20:                  return Keyboard::KeyCode::F20;
            case GLFW_KEY_F21:                  return Keyboard::KeyCode::F21;
            case GLFW_KEY_F22:                  return Keyboard::KeyCode::F22;
            case GLFW_KEY_F23:                  return Keyboard::KeyCode::F23;
            case GLFW_KEY_F24:                  return Keyboard::KeyCode::F24;
            case GLFW_KEY_CAPS_LOCK:            return Keyboard::KeyCode::CapsLock;
            case GLFW_KEY_PRINT_SCREEN:         return Keyboard::KeyCode::PrintScreen;
            case GLFW_KEY_SCROLL_LOCK:          return Keyboard::KeyCode::ScrollLock;
            case GLFW_KEY_PAUSE:                return Keyboard::KeyCode::Pause;
            case GLFW_KEY_INSERT:               return Keyboard::KeyCode::Insert;
            case GLFW_KEY_HOME:                 return Keyboard::KeyCode::Home;
            case GLFW_KEY_PAGE_UP:              return Keyboard::KeyCode::PageUp;
            case GLFW_KEY_DELETE:               return Keyboard::KeyCode::Delete;
            case GLFW_KEY_END:                  return Keyboard::KeyCode::End;
            case GLFW_KEY_PAGE_DOWN:            return Keyboard::KeyCode::PageDown;
            case GLFW_KEY_RIGHT:                return Keyboard::KeyCode::Right;
            case GLFW_KEY_LEFT:                 return Keyboard::KeyCode::Left;
            case GLFW_KEY_DOWN:                 return Keyboard::KeyCode::Down;
            case GLFW_KEY_UP:                   return Keyboard::KeyCode::Up;
            case GLFW_KEY_NUM_LOCK:             return Keyboard::KeyCode::NumLock;
            case GLFW_KEY_KP_DIVIDE:            return Keyboard::KeyCode::NumpadDivide;
            case GLFW_KEY_KP_MULTIPLY:          return Keyboard::KeyCode::NumpadMultiply;
            case GLFW_KEY_KP_SUBTRACT:          return Keyboard::KeyCode::NumpadMinus;
            case GLFW_KEY_KP_ADD:               return Keyboard::KeyCode::NumpadPlus;
            case GLFW_KEY_KP_EQUAL:             return Keyboard::KeyCode::NumpadEqual;
            case GLFW_KEY_KP_ENTER:             return Keyboard::KeyCode::NumpadEnter;
            case GLFW_KEY_KP_DECIMAL:           return Keyboard::KeyCode::NumpadDecimal;
            case GLFW_KEY_KP_1:                 return Keyboard::KeyCode::Numpad1;
            case GLFW_KEY_KP_2:                 return Keyboard::KeyCode::Numpad2;
            case GLFW_KEY_KP_3:                 return Keyboard::KeyCode::Numpad3;
            case GLFW_KEY_KP_4:                 return Keyboard::KeyCode::Numpad4;
            case GLFW_KEY_KP_5:                 return Keyboard::KeyCode::Numpad5;
            case GLFW_KEY_KP_6:                 return Keyboard::KeyCode::Numpad6;
            case GLFW_KEY_KP_7:                 return Keyboard::KeyCode::Numpad7;
            case GLFW_KEY_KP_8:                 return Keyboard::KeyCode::Numpad8;
            case GLFW_KEY_KP_9:                 return Keyboard::KeyCode::Numpad9;
            case GLFW_KEY_KP_0:                 return Keyboard::KeyCode::Numpad0;
            case GLFW_KEY_MENU:                 return Keyboard::KeyCode::Menu;
            case GLFW_KEY_LEFT_CONTROL:         return Keyboard::KeyCode::LControl;
            case GLFW_KEY_LEFT_SHIFT:           return Keyboard::KeyCode::LShift;
            case GLFW_KEY_LEFT_ALT:             return Keyboard::KeyCode::LAlt;
            case GLFW_KEY_LEFT_SUPER:           return Keyboard::KeyCode::LSystem;
            case GLFW_KEY_RIGHT_CONTROL:        return Keyboard::KeyCode::RControl;
            case GLFW_KEY_RIGHT_SHIFT:          return Keyboard::KeyCode::RShift;
            case GLFW_KEY_RIGHT_ALT:            return Keyboard::KeyCode::RAlt;
            case GLFW_KEY_RIGHT_SUPER:          return Keyboard::KeyCode::RSystem;
            case GLFW_KEY_WORLD_1:              return Keyboard::KeyCode::LaunchApplication1;
            case GLFW_KEY_WORLD_2:              return Keyboard::KeyCode::LaunchApplication2;
            default:                            return Keyboard::KeyCode::Unknown;
        }
    }

    constexpr std::int32_t Conversion::toGLFWButton(Mouse::Button button) noexcept
    {
        switch (button)
        {
            case Mouse::Button::Unknown:   return GLFW_KEY_UNKNOWN;
            case Mouse::Button::Left:      return GLFW_MOUSE_BUTTON_LEFT;
            case Mouse::Button::Right:     return GLFW_MOUSE_BUTTON_RIGHT;
            case Mouse::Button::Middle:    return GLFW_MOUSE_BUTTON_MIDDLE;
            case Mouse::Button::Extra1:    return GLFW_MOUSE_BUTTON_4;
            case Mouse::Button::Extra2:    return GLFW_MOUSE_BUTTON_5;
            case Mouse::Button::Extra3:    return GLFW_MOUSE_BUTTON_6;
            case Mouse::Button::Extra4:    return GLFW_MOUSE_BUTTON_7;
            case Mouse::Button::Extra5:    return GLFW_MOUSE_BUTTON_8;
        }
        return GLFW_KEY_UNKNOWN;
    }

    constexpr Mouse::Button Conversion::fromGLFWButton(std::int32_t button) noexcept
    {
        switch (button)
        {
            case GLFW_MOUSE_BUTTON_LEFT:    return Mouse::Button::Left;
            case GLFW_MOUSE_BUTTON_RIGHT:   return Mouse::Button::Right;
            case GLFW_MOUSE_BUTTON_MIDDLE:  return Mouse::Button::Middle;
            case GLFW_MOUSE_BUTTON_4:       return Mouse::Button::Extra1;
            case GLFW_MOUSE_BUTTON_5:       return Mouse::Button::Extra2;
            case GLFW_MOUSE_BUTTON_6:       return Mouse::Button::Extra3;
            case GLFW_MOUSE_BUTTON_7:       return Mouse::Button::Extra4;
            case GLFW_MOUSE_BUTTON_8:       return Mouse::Button::Extra5;
            default:                        return Mouse::Button::Unknown;
        }
    }
}