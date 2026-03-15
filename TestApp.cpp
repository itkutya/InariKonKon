import InariKonKon;

import Log;

class TestEvent : public ikk::EventListener<ikk::WindowEvent::Closed>
{
public:
    void onEvent(const ikk::WindowEvent::Closed& event) noexcept override
    {
        ikk::DebugPrint<ikk::Log::Level::Fatal>("GoodBye! {}", 123);
    }
};

class MenuLayer : public ikk::Layer
{
public:
    MenuLayer() noexcept
    {
        ikk::EventCallback<ikk::InputEvent::Mouse::Move>::add(
            [](const auto& event){ ikk::Print("Hello"); });
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
    TestEvent testEvent{};
};

int main()
{
    int *x = new int(10);
    ikk::Application app{ u8"TestApp 生", 800, 600 };
    app.attach(MenuLayer{});
    app.run();
    return 0;
}