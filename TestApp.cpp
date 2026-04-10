import InariKonKon;

struct Velocity
{
    ikk::Vec3f velocity;
};

class Menu final : public ikk::Scene
{
public:
    Menu() noexcept
    {
        auto& ent = this->createEntity();
        bool valid = ent.isValid();
        if (ent)
            ikk::Print("Entity ID: {}", ent.getID());
        //this->destroyEntity(ent);
        if (ent)
            ikk::Print("Entity is still alive!");

        ent.addComponent<Velocity>();
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