#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "imgui.h"
#include "imgui-SFML.h"
#include <ImGuizmo.h>
#include <iostream>
#include <cstdint>
class Application {
public:

    Application();
    ~Application();
    void Update();

private:

    sf::Clock deltaClock;
    sf::RenderWindow window;
    // ÉwÉbÉ_Å[
    std::unique_ptr<sf::RenderTexture> renderTexture;
    bool debug_flag;
    // â~óp
    sf::CircleShape circle;
    sf::Color circle_color = { 255, 128, 0, 255 };
    sf::Vector2f velocity;


    void ProcessEvents();
    void UpdateState(const sf::Time& dt);
    void Render();
    void RenderImGui();

};

namespace ColorUtils {

    inline void ToFloat4(const sf::Color& color, float out[4]) {
        out[0] = static_cast<float>(color.r) / 255.f;
        out[1] = static_cast<float>(color.g) / 255.f;
        out[2] = static_cast<float>(color.b) / 255.f;
        out[3] = static_cast<float>(color.a) / 255.f;
    }

    inline sf::Color FromFloat4(const float in[4]) {
        return sf::Color(
            static_cast<std::uint8_t>(in[0] * 255.f),
            static_cast<std::uint8_t>(in[1] * 255.f),
            static_cast<std::uint8_t>(in[2] * 255.f),
            static_cast<std::uint8_t>(in[3] * 255.f)
        );
    }

}