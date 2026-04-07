import InariKonKon;

class MenuLayer final : public ikk::Layer
{
public:
    MenuLayer() noexcept
    {
        ikk::ThreadPool threadPool{};
        const auto t1 = threadPool.enqueue([]{ ikk::Print("Hello Threads!"); });
        threadPool.enqueue([]{ ikk::Print("Welcome Threads!"); });
        t1.wait();
        threadPool.enqueue([]{ ikk::Print("Goodbye Threads!"); });
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