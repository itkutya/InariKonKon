import InariKonKon;

struct Velocity
{
    ikk::Vec3f velocity;
};

struct Position
{
    ikk::Vec3f position;
};

class Menu final : public ikk::Scene
{
public:
    explicit Menu(ikk::Application* application) noexcept
        : ikk::Scene(application)
    {
        ent1.addComponent<Position>(ikk::Vec3f{ 2.f, 5.f, 1.f });
        ent1.addComponent<Velocity>(ikk::Vec3f{ 0.f, 2.f, 5.f });
        ent2.addComponent<Position>(ikk::Vec3f{ 2.f, 5.f, 1.f });
        ent2.addComponent<Velocity>(ikk::Vec3f{ 0.f, 2.f, 5.f });
        ent3.addComponent<Position>(ikk::Vec3f{ 2.f, 5.f, 1.f });
        ent3.addComponent<Velocity>(ikk::Vec3f{ 0.f, 2.f, 5.f });
    }

    void onEvent(const ikk::Event& event) noexcept override
    {
    }

    void onUpdate(const ikk::Time& dt) noexcept override
    {
        using MoveSystem = ikk::System<Position, Velocity>;
        MoveSystem::update(
            [](const ikk::Entity& entity, Position& position, const Velocity& velocity, float dt) noexcept
            {
                auto& pos = position.position;
                const auto& vel = velocity.velocity;
                pos += (vel * dt);
                ikk::Print("Entity (ID: {}): Position: [x: {}, y: {}, z: {}]", entity.getID(), pos.x(), pos.y(), pos.z());
            }, dt.asSeconds());
    }

    void onRender(const ikk::Window& window) const noexcept override
    {
    }
private:
    ikk::Entity ent1{};
    ikk::Entity ent2{};
    ikk::Entity ent3{};
};

int main()
{
    ikk::Application app{ u8"TestApp 生", 800, 600 };
    app.addScene<Menu>();
    app.run();
    return 0;
}