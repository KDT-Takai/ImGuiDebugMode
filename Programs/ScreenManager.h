//#pragma once
//#include <memory>
//#include <SFML/Graphics.hpp>
//#include "Singleton.h"
//#include "ScreenBase.h"
//
//class ScreenManager : public Singleton<ScreenManager> {
//    friend class Singleton<ScreenManager>;
//
//private:
//    std::unique_ptr<ScreenBase> screen;
//    std::unique_ptr<sf::RenderTexture> renderTexture;
//    bool debugMode = true;
//
//    ScreenManager();  // コンストラクタは Singleton からのみ呼ばれる
//
//public:
//    ~ScreenManager() = default;
//
//    void ChangeScreen(std::unique_ptr<ScreenBase> next);
//    void Update(const sf::Time& dt);
//    void Render(std::unique_ptr<sf::RenderTexture>& target);
//
//    void ToggleDebug();
//    sf::RenderTexture& GetRenderTexture();
//};
