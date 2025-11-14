#pragma once
#include "imgui.h"
#include <vector>
#include <string>
#include <cstdarg>
#include "Singleton.h"

class ImGuiLog : public Singleton<ImGuiLog> {
    friend class Singleton<ImGuiLog>;
public:
    // ログ追加（タグ指定）
    void AddLog(const std::string& tag, const char* fmt, ...) {
        char buf[1024];
        va_list args;
        va_start(args, fmt);
        vsnprintf(buf, sizeof(buf), fmt, args);
        va_end(args);
        logs[tag].emplace_back(buf);
        scrollToBottom[tag] = true;
        // 初めてのタグなら表示ONに
        if (visible.find(tag) == visible.end())
            visible[tag] = true;
    }

    // 描画
    void Draw(const char* title = "Logs") {
        if (!ImGui::Begin(title)) { ImGui::End(); return; }
        // タグごとの表示切替ボタン
        for (auto& pair : logs) {
            const std::string& tag = pair.first;
            if (ImGui::Button((tag + std::string(" Log")).c_str())) {
                visible[tag] = !visible[tag];
            }
            ImGui::SameLine(); // ボタンを横並び
        }
        ImGui::NewLine();
        ImGui::Separator();
        // タグごとのログ描画（横並び）
        bool first = true;
        for (auto& pair : logs) {
            const std::string& tag = pair.first;
            std::vector<std::string>& logList = pair.second;
            if (!visible[tag]) continue;

            if (!first) ImGui::SameLine(); // 横に並べる
            first = false;

            ImGui::BeginChild((tag + "Child").c_str(), ImVec2(300, 150), true, ImGuiWindowFlags_HorizontalScrollbar);
            ImGui::Text("[%s]", tag.c_str());
            for (auto& line : logList)
                ImGui::TextUnformatted(line.c_str());
            if (scrollToBottom[tag]) {
                ImGui::SetScrollHereY(1.0f);
                scrollToBottom[tag] = false;
            }
            ImGui::EndChild();
        }
        if (ImGui::Button("Clear All")) logs.clear();
        ImGui::End();
    }
private:
    std::unordered_map<std::string, std::vector<std::string>> logs;
    std::unordered_map<std::string, bool> scrollToBottom;
    std::unordered_map<std::string, bool> visible; // タグごとの表示ON/OFF
};