import InariKonKon;

//TODO: VERY IMPORTANT!!!
// - MAKE REAL ERROR HANDLEING, THROWING EXCEPTIONS OR std::expected/std::optional

class Menu final : public ikk::Scene
{
public:
    explicit Menu(ikk::Application* application) noexcept
    {
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
    ikk::Button btn{"Text", { 25_px, 25_px },{ 2_p, 6_p }, { .color = ikk::Color::Miku }};
};

int main()
{
    ikk::Application app{ u8"TestApp 生", 800, 600 };
    app.addScene<Menu>(&app);
    app.run();
    return 0;
}