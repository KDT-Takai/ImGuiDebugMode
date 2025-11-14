//#include "ExampleScreen.h"
//
//class ExampleScreen : public ScreenBase {
//private:
//    sf::CircleShape circle{ 50.f };
//    sf::Vector2f velocity{ 100.f, 60.f };
//
//public:
//    ExampleScreen() {
//        circle.setFillColor(sf::Color::Yellow);
//        circle.setPosition({ 100.f, 100.f });
//    }
//
//    void Update(const sf::Time& dt) override {
//        sf::Vector2f pos = circle.getPosition();
//        pos += velocity * dt.asSeconds();
//
//        if (pos.x < 0 || pos.x + circle.getRadius() * 2 > 1280) velocity.x = -velocity.x;
//        if (pos.y < 0 || pos.y + circle.getRadius() * 2 > 720) velocity.y = -velocity.y;
//
//        circle.setPosition(pos);
//    }
//
//    void Render(sf::RenderTarget& target) override {
//        target.draw(circle);
//    }
//
//    void RenderImGui() override {
//        ImGui::Text("Circle Pos: %.1f, %.1f", circle.getPosition().x, circle.getPosition().y);
//    }
//};
