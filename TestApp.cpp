import InariKonKon;

class Menu final : public ikk::Scene
{
public:
    explicit Menu(ikk::Application* application) noexcept
        : ikk::Scene(application)
    {
        ikk::test();
        tex.loadAsync("");

        tex.waitFor(ikk::seconds(0.f));

        while (tex.isReady() == false)
            ikk::Print("No data");

        ikk::Print("{}", ikk::I32(tex));
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
    ikk::Resource<int> tex{};
};

int main()
{
    ikk::Application app{ u8"TestApp 生", 800, 600 };
    app.addScene<Menu>();
    app.run();
    return 0;
}