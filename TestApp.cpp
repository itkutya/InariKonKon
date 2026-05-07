import InariKonKon;

//TODO: VERY IMPORTANT!!!
// - MAKE REAL ERROR HANDLEING, THROWING EXCEPTIONS OR std::expected/std::optional

class Menu final : public ikk::Scene
{
public:
    explicit Menu(ikk::Application* application) noexcept
        : ikk::Scene(application)
    {
        ikk::Percentage f{ .value = 2.f };
        ikk::Extent ext{ .x = 55._p, .y = 266_px };
        ikk::Print("Extent:\n\tx: {}\n\ty: {}", ext.x.value.value(), ext.y.value);
        float impl = f;
        unsigned int v = ext.y;
        float ff = ext.x;
        int I = 2;
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
    //            Displayed Text  Position     Size          Button theme stuff
    //ikk::Button btn{"Text",    {25%, 25%}, {2%, 6%}, { .color = ikk::Color::Miku }};
};

int main()
{
    ikk::Application app{ u8"TestApp 生", 800, 600 };
    app.addScene<Menu>();
    app.run();
    return 0;
}