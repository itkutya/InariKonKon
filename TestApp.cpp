import InariKonKon;

class Menu final : public ikk::Scene
{
public:
    Menu() noexcept
    {
        if (const auto entity = this->createEntity(); entity)
        {
            const auto id = entity->getID();
            ikk::Print("Entity ID: {}", id);
        }
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
    app.add(Menu{});
    app.run();
    return 0;
}