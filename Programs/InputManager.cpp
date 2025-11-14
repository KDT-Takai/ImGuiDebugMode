#include "imgui.h"
#include "InputManager.h"
#include "ImGuiLog.h"

InputManager::InputManager() {
    nowKeyInput.fill(false);
    beforKeyInput.fill(false);
    nowMouseInput.fill(false);
    beforMouseInput.fill(false);
    mouseX = 0;
    mouseY = 0;
}

void InputManager::Update(const sf::RenderWindow& window) {
    // --- 前回の状態を保存 ---
    beforKeyInput = nowKeyInput;
    beforMouseInput = nowMouseInput;

    // --- 入力状態の更新のみ ---
    for (int i = 0; i < KEY_MAX; i++)
        nowKeyInput[i] = sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(i));

    for (int i = 0; i < MOUSE_BUTTON_MAX; i++)
        nowMouseInput[i] = sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(i));

    sf::Vector2i pos = sf::Mouse::getPosition(window);
    mouseX = pos.x;
    mouseY = pos.y;
}

void InputManager::RenderImGui() {
    ImGui::Begin("Input Debug");
    ImGui::Text("Mouse Position: (%.0f, %.0f)", (float)mouseX, (float)mouseY);
    ImGui::Separator();
    static std::vector<std::string> pressedKeys;
    static std::vector<std::string> pressedMouseButtons;
    bool newKeyLogged = false;
    bool newMouseLogged = false;
    // --- キー入力ログ ---
    ImGui::TextColored(ImVec4(0.8f, 0.9f, 1.0f, 1.0f), "Key Logs");
    ImGui::BeginChild("KeyLogChild", ImVec2(0, 120), true, ImGuiWindowFlags_HorizontalScrollbar);
    for (int i = 0; i < KEY_MAX; ++i) {
        if (nowKeyInput[i] && !beforKeyInput[i]) {
            pressedKeys.push_back(KeyToString(static_cast<sf::Keyboard::Key>(i)));
            newKeyLogged = true;
        }
    }
    for (const auto& keyName : pressedKeys) {
        ImGui::BulletText("%s", keyName.c_str());
    }
    // 新しいキーが追加されたら一番下へ
    if (newKeyLogged) ImGui::SetScrollHereY(1.0f);
    ImGui::EndChild();
    ImGui::Spacing();
    // --- マウス入力ログ ---
    ImGui::TextColored(ImVec4(0.9f, 0.8f, 0.8f, 1.0f), "Mouse Logs");
    ImGui::BeginChild("MouseLogChild", ImVec2(0, 100), true, ImGuiWindowFlags_HorizontalScrollbar);
    for (int i = 0; i < MOUSE_BUTTON_MAX; ++i) {
        if (nowMouseInput[i] && !beforMouseInput[i]) {
            pressedMouseButtons.push_back(MouseButtonToString(static_cast<sf::Mouse::Button>(i)));
            newMouseLogged = true;
        }
    }
    for (const auto& btn : pressedMouseButtons) {
        ImGui::BulletText("%s", btn.c_str());
    }
    // 新しいマウスログが追加されたら下へスクロール
    if (newMouseLogged) ImGui::SetScrollHereY(1.0f);
    ImGui::EndChild();
    ImGui::Spacing();
    if (ImGui::Button("Clear Logs")) {
        pressedKeys.clear();
        pressedMouseButtons.clear();
    }
    ImGui::End();
}

// 押した瞬間
bool InputManager::IsGetKey(sf::Keyboard::Key key) const {
    return nowKeyInput[static_cast<int>(key)] && !beforKeyInput[static_cast<int>(key)];
}

// 押されている間
bool InputManager::GetKey(sf::Keyboard::Key key) const {
    return nowKeyInput[static_cast<int>(key)];
}

// 長押し
bool InputManager::GetKeyRepeat(sf::Keyboard::Key key) const {
    return nowKeyInput[static_cast<int>(key)] && beforKeyInput[static_cast<int>(key)];
}

// マウス押した瞬間
bool InputManager::IsGetMouse(sf::Mouse::Button button) const {
    return nowMouseInput[static_cast<int>(button)] && !beforMouseInput[static_cast<int>(button)];
}

// マウス長押し
bool InputManager::GetMouseRepeat(sf::Mouse::Button button) const {
    return nowMouseInput[static_cast<int>(button)] && beforMouseInput[static_cast<int>(button)];
}

int InputManager::GetMouseX() const { return mouseX; }
int InputManager::GetMouseY() const { return mouseY; }
