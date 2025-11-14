#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <array>
#include "Singleton.h"
#include "InputUtils.h"

class InputManager : public Singleton<InputManager> {
    friend class Singleton<InputManager>;
protected:
    InputManager();
public:
    void Update(const sf::RenderWindow& window);
    void RenderImGui();

    // キー入力関連
    bool IsGetKey(sf::Keyboard::Key key) const;     // 押した瞬間
    bool GetKey(sf::Keyboard::Key key) const;       // 押されている間
    bool GetKeyRepeat(sf::Keyboard::Key key) const; // 長押し

    // マウス入力関連
    bool IsGetMouse(sf::Mouse::Button button) const;
    bool GetMouseRepeat(sf::Mouse::Button button) const;

    int GetMouseX() const;
    int GetMouseY() const;
    
    
private:
    static constexpr int KEY_MAX = sf::Keyboard::KeyCount;
    static constexpr int MOUSE_BUTTON_MAX = sf::Mouse::ButtonCount;

    std::array<bool, KEY_MAX> nowKeyInput;
    std::array<bool, KEY_MAX> beforKeyInput;

    std::array<bool, MOUSE_BUTTON_MAX> nowMouseInput;
    std::array<bool, MOUSE_BUTTON_MAX> beforMouseInput;

    int mouseX, mouseY;

};
