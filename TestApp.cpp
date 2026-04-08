import InariKonKon;

class MenuLayer final : public ikk::Layer
{
public:
    MenuLayer() noexcept
    {
        const ikk::EntityHandle& entity = ikk::ECS.createEntity();
        ikk::ECS.destroyEntity(entity);
        auto ent = entity.get();
        if (ent.has_value())
        {
            if (entity.isValid())
                ikk::Print("Entity handle is valid!");
            auto id = (*ent)->getID();
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
    app.attach(MenuLayer{});
    app.run();
    return 0;
}