#include "Application.h"    // Application class header
#include <iostream>         // Standard I/O
#include <vector>           // Standard vector
#include "InputManager.h"
#include "ScreenManager.h"
#include "ImGuiLog.h"

Application::Application()
    : window(sf::VideoMode({ 1280, 720 }), "SFML ImGui Game"),
    circle(50.f), velocity(100.f, 60.f), debug_flag(false)
{
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    renderTexture = std::make_unique<sf::RenderTexture>();
    renderTexture->resize({ 1280, 720 });
    renderTexture->clear(sf::Color::Blue);
    circle.setFillColor(circle_color);
    circle.setPosition({ 100.f, 100.f });

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    ImGui::StyleColorsClassic();
}

Application::~Application() {
    ImGui::SFML::Shutdown();
}

void Application::Update() {
    while (window.isOpen()) {
        ProcessEvents();
        auto dt = deltaClock.restart();
        UpdateState(dt);
        Render();
    }
}

void Application::ProcessEvents() {
    while (auto event = window.pollEvent()) {
        ImGui::SFML::ProcessEvent(window, *event);
        if (event->is<sf::Event::Closed>()) window.close();
    }
}

void Application::UpdateState(const sf::Time& dt) {
    ImGui::SFML::Update(window, dt);
    InputManager::Instance().Update(window);
    // â~ÇÃà íuÇçXêV
    sf::Vector2f pos = circle.getPosition();
    pos += velocity * dt.asSeconds();

    // âÊñ í[Ç≈íµÇÀï‘ÇÈ
    if (pos.x < 0 || pos.x + circle.getRadius() * 2 > 1280) velocity.x = -velocity.x;
    if (pos.y < 0 || pos.y + circle.getRadius() * 2 > 720) velocity.y = -velocity.y;

    circle.setPosition(pos);

    if (InputManager::Instance().IsGetKey(sf::Keyboard::Key::F1)) {
        debug_flag = !debug_flag;
        std::cout << "debug_flag : " << (debug_flag ? "Debug Mode" : "Normal Mode") << std::endl;
    }
}

void Application::Render() {
    // RenderTextureÇ…ï`âÊ
    renderTexture->clear(sf::Color::Blue);
    renderTexture->draw(circle);
    renderTexture->display();

    // ÉEÉBÉìÉhÉEï`âÊ
    window.clear({ 64, 64, 64 });
    window.draw(sf::Sprite(renderTexture->getTexture()));  // ç≈êVÇÃ RenderTexture Çï`âÊ

    if (debug_flag) RenderImGui(); // ImGuiï`âÊ

    ImGui::SFML::Render(window);

    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();

    window.display();
}

void Application::RenderImGui() {
    // ImGui::ShowDemoWindow();
    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport()->ID);
    float color[4];
    ColorUtils::ToFloat4(circle_color, color);

    ImGui::Begin("Color Editor");
    if (ImGui::ColorEdit4("Color", color,
        ImGuiColorEditFlags_DisplayRGB |
        ImGuiColorEditFlags_PickerHueBar |
        ImGuiColorEditFlags_NoInputs)) {
        circle_color = ColorUtils::FromFloat4(color);
        circle.setFillColor(circle_color);
    }
    ImGui::End();

    ImGui::Begin("Debug Screen");
    ImTextureID texID = renderTexture->getTexture().getNativeHandle();
    ImGui::Image(texID, ImVec2(640, 360), ImVec2(0, 1), ImVec2(1, 0));  // UVÇè„â∫îΩì]
    InputManager::Instance().RenderImGui();
    ImGui::End();

}