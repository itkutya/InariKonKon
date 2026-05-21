import InariKonKon;
import TransformComponent;

//TODO: VERY IMPORTANT!!!
// - MAKE REAL ERROR HANDLEING, THROWING EXCEPTIONS OR std::expected/std::optional

class Menu final : public ikk::Scene
{
public:
    explicit Menu(ikk::Application* application) noexcept
    {
        constexpr ikk::Extent e{};
        constexpr ikk::Extent e1{25_px, 12._p};
        constexpr ikk::Extent e2{25_px, 12_px};
        constexpr ikk::Extent e3{25._p, 12_p};

        ikk::Transform3D t{};
        ikk::Transform3D t2{ ikk::Vec3f{0.2f, 0.2f, 0.2f}};

        t2.setParent(t);

        t2.translateLocal({1.f, 0.f, 0.f});
        t2.translateGlobal({1.f, 2.f, 3.f});
        ikk::Mat4x4f mat = t2.getWorldMatrix();

        ikk::Vec4f v = ikk::Vec2i{2, 4};
        constexpr ikk::RotationDegf rot{.yaw = ikk::Degreef{2.f}, .pitch = ikk::Degreef{242.f}, .roll = ikk::Degreef{125.f}};
        btn.getTransform().rotateGlobal(rot.yaw);
        btn.getTransform().rotateLocal(rot.pitch);

        const ikk::Transform2D transform = btn.getTransform();
        const ikk::Mat3x3f transformMatrix = transform.getWorldMatrix();
        int i = 2;
        if (i == 3)
            this->destroy();
        else
            this->suspend();

        ikk::Theme theme{.color = ikk::Color::Miku };
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
    ikk::Button btn{"Text", {{ 25, 25 },{ 2, 6 }}, { .color = ikk::Color::Miku }};
};

int main()
{
    ikk::Application app{ u8"TestApp 生", 800, 600 };
    app.addScene<Menu>(&app);
    app.run();
    return 0;
}