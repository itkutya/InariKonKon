import InariKonKon;

class MenuLayer final : public ikk::Layer
{
public:
    MenuLayer() noexcept
    {
        //TODO: Error handeling...
        ikk::Input.bind("Move Left", ikk::Keyboard::KeyCode::A, ikk::Input::Press);
        ikk::Input.bind("Move Left", ikk::Keyboard::A);

        ikk::Input.onAction("Move Left",
            []() noexcept
            {
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