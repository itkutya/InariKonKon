import InariKonKon;

//TODO: VERY IMPORTANT!!!
// - MAKE REAL ERROR HANDLEING, THROWING EXCEPTIONS OR std::expected/std::optional

class Menu final : public ikk::Scene
{
public:
    explicit Menu(ikk::Application* application) noexcept
        : ikk::Scene(application)
    {
        ikk::Clock timer{};

        audio.loadFromFileAsync("/home/itkutya/Documents/c++/CLion/InariKonKonGameFramework/Resources/audio.mp3");

        tex.loadFromFileAsync("/home/itkutya/Documents/c++/CLion/InariKonKonGameFramework/Resources/osu_logo.png");

        tex.waitFor(ikk::seconds(0.1f));

        audio.play();

        while (tex.isLoading() == true)
            ikk::Print("No data");

        ikk::Resource::preloadFromFile<ikk::Texture>("Name", "Path");
        //auto temp = ikk::Resource<ikk::Texture>::get("Name");

        ikk::Print("Time it took: {}s", timer.getElapsedTime().asSeconds());
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
    ikk::Texture tex{};
    ikk::Audio audio{};
};

int main()
{
    ikk::Application app{ u8"TestApp 生", 800, 600 };
    app.addScene<Menu>();
    app.run();
    return 0;
}