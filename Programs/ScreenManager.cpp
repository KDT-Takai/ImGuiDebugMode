//#include "ScreenManager.h"
//
//ScreenManager::ScreenManager() {
//    renderTexture = std::make_unique<sf::RenderTexture>();
//    renderTexture->resize({ 1280, 720 });
//}
//
//void ScreenManager::ChangeScreen(std::unique_ptr<ScreenBase> next) {
//    screen = std::move(next);
//}
//
//void ScreenManager::Update(const sf::Time& dt) {
//    if (screen) screen->Update(dt);
//}
//
//void ScreenManager::Render(std::unique_ptr<sf::RenderTexture>& target) {
//    void ScreenManager::Render(sf::RenderTexture * &target) {
//        if (!screen) return;
//
//        renderTexture->clear(sf::Color::Blue);
//        screen->Render(*renderTexture);
//        renderTexture->display();
//
//        // Application 側に渡す（ポインタ参照で代入）
//        target = renderTexture.get();
//
//        if (debugMode) {
//            screen->RenderImGui();
//        }
//    }
//
//
//void ScreenManager::ToggleDebug() {
//    debugMode = !debugMode;
//}
//
//sf::RenderTexture& ScreenManager::GetRenderTexture() {
//    return *renderTexture;
//}
