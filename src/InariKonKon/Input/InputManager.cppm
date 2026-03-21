module;

#include <vector>

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

export module InputManager;

import Singleton;
import Input;

export namespace ikk
{
    class InputManager final : public Singleton<InputManager>
    {
        friend class Singleton<InputManager>;

        InputManager() noexcept = default;
    public:
        ~InputManager() noexcept = default;

        void addJoystick(Joystick::ID id) noexcept;
        void removeJoystick(Joystick::ID id) noexcept;
    private:
        std::vector<PhysicalJoystick> m_connectedJoysticks;

        void checkForConnectedJoysticks() noexcept;

        [[nodiscard]] auto findJoystick(Joystick::ID id) const noexcept;
    };
}

namespace ikk
{
    void InputManager::checkForConnectedJoysticks() noexcept
    {
        for (Joystick::ID id = GLFW_JOYSTICK_1; id <= GLFW_JOYSTICK_16; ++id)
            if (PhysicalJoystick::isConnected(id) == true)
                this->addJoystick(id);
    }

    auto InputManager::findJoystick(Joystick::ID id) const noexcept
    {
        return std::ranges::find_if(this->m_connectedJoysticks, [&id](const auto& joystick){ return joystick.getID() == id; });
    }

    void InputManager::addJoystick(Joystick::ID id) noexcept
    {
        if (const auto found = this->findJoystick(id); found == this->m_connectedJoysticks.end())
            this->m_connectedJoysticks.emplace_back(id);
    }

    void InputManager::removeJoystick(Joystick::ID id) noexcept
    {
        if (const auto found = this->findJoystick(id); found != this->m_connectedJoysticks.end())
            this->m_connectedJoysticks.erase(found);
    }
}