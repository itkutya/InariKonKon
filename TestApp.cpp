import InariKonKon;

class MenuLayer final : public ikk::Layer
{
public:
    MenuLayer() noexcept
    {
        ikk::Input.bind("Move Left", ikk::Keyboard::KeyCode::A);
        ikk::Input.bind("Move Up", ikk::Keyboard::KeyCode::A);
        ikk::Input.bind("Move Left", ikk::Keyboard::KeyCode::D);
        ikk::Input.onAction("Move Left",
            [](ikk::Keyboard::KeyCode keycode, ikk::Input::Action action) noexcept
            {
                ikk::Print("Keycode: {}", ikk::Keyboard::toString(keycode));
            });

        ikk::Input.bind("Move Left", ikk::Keyboard::toScanCode(ikk::Keyboard::KeyCode::A));
        ikk::Input.onAction("Move Left",
            [](ikk::Keyboard::ScanCode scancode, ikk::Input::Action action) noexcept
            {
                ikk::Print("ScanCode: {}", ikk::Keyboard::toString(ikk::Keyboard::toKeyCode(scancode)));
            });

        ikk::Input.bind("Shoot", ikk::Mouse::Left);
        ikk::Input.onAction("Shoot",
            [](ikk::Mouse::Button button, ikk::Input::Action action) noexcept
            {
                ikk::Print("Mouse button: {}", ikk::Mouse::toString(button));
            });

        ikk::Input.bind("Scroll", ikk::Mouse::Wheel::Vertical);
        ikk::Input.onAction("Scroll",
            [](ikk::Mouse::Wheel wheel, double delta) noexcept
            {
                ikk::Print("Mouse wheel: {}\tScroll delta: {}", ikk::Mouse::toString(wheel), delta);
            });
    }

    void onEvent(const ikk::Event& event) noexcept override
    {
    }

    void onUpdate(const ikk::Time& dt) noexcept override
    {
    }

    void onRender(const ikk::Window& window) const noexcept override
    {
    }
private:
};

int main()
{
    ikk::Application app{ u8"TestApp 生", 800, 600 };
    app.attach(MenuLayer{});
    app.run();
    return 0;
}